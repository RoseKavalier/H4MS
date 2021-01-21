#include "stdafx.h"
#include "H4MS.hpp"
#include "Path.hpp"
#include <ThirdParty/json.hpp>

H4MSPlugin h4ms;

H4MSPlugin& GetPlugin()
{
	return h4ms;
}

int __stdcall _HH_WinMain(
	HiHook* h,
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	const bool result = h4ms.MainHook();
	return STDCALL_4(int, h->GetDefaultFunc(), hInstance, hPrevInstance, lpCmdLine, nShowCmd);
}

bool H4MSPlugin::ApplyPatch(const mod::Patch & p)
{
	switch (p.type)
	{
	case mod::Patch::Type::byte:
		return nullptr != WriteByte(p.address, p.byte);
	case mod::Patch::Type::word:
		return nullptr != WriteWord(p.address, p.word);
	case mod::Patch::Type::dword:
		return nullptr != WriteDword(p.address, p.dword);
	case mod::Patch::Type::floating_point:
		return nullptr != m_instance->Write(p.address, _ptr_(&p.floating_point), sizeof(p.floating_point));
	case mod::Patch::Type::decimal_floating_point:
		return nullptr != m_instance->Write(p.address, _ptr_(&p.decimal_floating_point), sizeof(p.decimal_floating_point));
	case mod::Patch::Type::inline_string:
		return nullptr != m_instance->Write(p.address, _ptr_(p.text_string.c_str()), p.text_string.length() + 1);
	case mod::Patch::Type::string:
	{
		const size_t sz = m_patchStrings.size();
		const bool is_full = m_patchStrings.capacity() == sz;
		mod::StringPatch sp;
		sp.address = p.address;
		sp.text_string = p.text_string;
		m_patchStrings.push_back(std::move(sp));

		if (!is_full)
			return nullptr != WriteDword(p.address, reinterpret_cast<_ptr_>(m_patchStrings.back().text_string.data()));
		else // vector reallocation, update old patches
		{
			for (size_t i = 0; i < sz; ++i)
			{
				auto& it = m_patchStrings[i];
				Write(it.address, it.text_string.data());
			}
			return nullptr != WriteDword(p.address, reinterpret_cast<_ptr_>(m_patchStrings.back().text_string.data()));
		}
	}
	case mod::Patch::Type::hex_patch:
		return nullptr != WriteHexPatch(p.address, p.text_string.c_str());
	default:
		return false;
	}
}

bool H4MSPlugin::CreateLogger()
{
	if (nullptr == m_logger.get())
	{
		CreateDirectory((m_directory + DEBUG_DIRECTORY).c_str(), NULL);
		m_logger = std::make_unique<Logger>(m_directory);
		return m_logger.get() != nullptr;
	}
	else
		return true;
}

bool H4MSPlugin::GetDir()
{
	m_directory = Path::CurrentDirectory();
	return !m_directory.empty();
}

bool H4MSPlugin::Load(const std::string & plugin_name)
{
	try
	{
		DirectoryChanger dir(utf8_to_tstring(plugin_name));
		if (!dir.IsModified())
			throw std::exception(PLUGIN_DIRECTORY_FAILED);

		// config file is absolutely required!
		CFile f;
		if (!f.OpenToRead(PLUGIN_CONFIG, true))
			throw std::exception(PLUGIN_CONFIG_FAILED);
		json config = json::parse(f.begin(), f.end());
		if (!config.is_object())
			throw std::exception(PLUGIN_CONFIG_INCORRECT);
		if (config.contains(JSON_PATCHES))
			PluginPatches(config[JSON_PATCHES], plugin_name);
		if (config.contains(JSON_ASSETS) && config[JSON_ASSETS].get<bool>())
			PluginAssets(plugin_name);
		if (config.contains(JSON_LIBRARIES))
			PluginLibraries(config[JSON_LIBRARIES], plugin_name);
		else
		{
			Path p(DLL_TYPE);
			for (auto& it : p)
			{
				try
				{
					auto hmodule = LoadLibrary(it.FileName());
					if (hmodule)
						m_libraries.push_back({ it.FileName(), hmodule });
					else
						throw std::exception((LOAD_LIBRARY_FAILED + tstring_to_utf8(it.FileName())).c_str());
				}
				catch (const std::exception& ex)
				{
					LogPluginError(plugin_name, ex);
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		LogPluginError(plugin_name, e);
		return false;
	}
	return true;
}

void H4MSPlugin::Log(LPCSTR utf8)
{
	if (CreateLogger())
		m_logger->log(utf8);
}

void H4MSPlugin::Log(const std::string & utf8)
{
	if (CreateLogger())
		m_logger->log(utf8);
}

void H4MSPlugin::LogDebug(LPCSTR utf8)
{
	if (CreateLogger())
		m_logger->log_debug(utf8);
}

void H4MSPlugin::LogDebug(const std::string & utf8)
{
	if (CreateLogger())
		m_logger->log_debug(utf8);
}

void H4MSPlugin::LogPluginError(const std::string & name, const std::exception & e)
{
	if (CreateLogger())
		m_logger->plugin_error(name, e);
}


int H4MSPlugin::MainHook()
{
	try
	{
		TString config_path = m_directory + CONFIG_FILE;
		CFile f;
		if (!f.OpenToRead(config_path, true))
		{
			CreateLogger();
			Log(OPEN_CONFIG_FILE + tstring_to_utf8(config_path) + u8"]");
			return EXEC_DEFAULT;
		}
		json config = json::parse(f.begin(), f.end());
		if (!config.is_array())
		{
			CreateLogger();
			Log(CONFIG_INCORRECT);
			return EXEC_DEFAULT;
		}
		config.get_to(m_plugins);

		const TString plugin_dir = m_directory + PLUGINS_DIR;
		DirectoryChanger dir(plugin_dir);
		if (!dir.IsModified())
			throw std::exception(std::string(PLUGINS_DIRECTORY_FAILED + tstring_to_utf8(plugin_dir)).c_str());

		for (const auto& it : m_plugins)
		{
			if ((it.game && m_exe.game()) || (it.editor && m_exe.editor()))
			{
				Load(it.name);

			}
		}
	}
	catch (const std::exception& e)
	{
		Log(e.what());
	}

	return EXEC_DEFAULT;
}

void H4MSPlugin::PluginAssets(const std::string & plugin_name)
{
	try
	{
		DirectoryChanger dir(ASSETS_DIR);
		if (!dir.IsModified())
			throw std::exception(ASSETS_DIRECTORY_FAILED);

		Path directory(RESOURCE_TYPE);

		/*
		 * load all *.h4r
		 * H4 uses ansi functions so converting back to be safe
		 */
		for (auto& it : directory)
		{
			try
			{
				std::string file_name(tstring_to_ansi(it.FileName())); // h4 requires ansi style
				if (m_exe.game())
				{
					if (!h4::LoadResourceFile(file_name.c_str()))
					{
						std::string utf8_error(LOADING_RESOURCE_FAILED + file_name + u8"]");
						throw std::exception(utf8_error.c_str());
					}
				}
				else if (m_exe.editor())
				{
					if (!h4e::LoadResourceFile(file_name.c_str()))
					{
						std::string utf8_error(LOADING_RESOURCE_FAILED + file_name + u8"]");
						throw std::exception(utf8_error.c_str());
					}
				}
			}
			catch (const std::exception& e)
			{
				LogPluginError(plugin_name, e);
			}
		}

		/*
		 * load all *.h4d
		 * These functions do not return fail/success so no error report for now
		 * Eventually could double check what was actually loaded vs what's in the assets folder
		 */
		if (m_exe.game())
			h4::LoadResourcesFromDirectory(".");
		else if (m_exe.editor())
			h4e::LoadResourcesFromDirectory(".");

	}
	catch (const std::exception& e)
	{
		LogPluginError(plugin_name, e);
	}

}

void H4MSPlugin::PluginLibraries(const json & libraries, const std::string & plugin_name)
{
	try
	{
		if (!libraries.is_array())
			throw std::exception(CONFIG_PATCHES_FORMAT);

		for (auto& it : libraries)
		{
			std::string dll_utf8;
			it.get_to(dll_utf8);
			TString dll_name = utf8_to_tstring(dll_utf8);
			auto hmodule = LoadLibrary(dll_name.c_str());
			if (hmodule)
				m_libraries.push_back({ dll_name, hmodule });
			else
				throw std::exception((LOAD_LIBRARY_FAILED + dll_utf8).c_str());
		}
	}
	catch (const std::exception& e)
	{
		LogPluginError(plugin_name, e);
	}
}

void H4MSPlugin::PluginPatches(const json & patches, const std::string & plugin_name)
{
	if (!patches.is_object())
		throw std::exception(CONFIG_PATCHES_FORMAT);

	for (auto& it : patches)
	{
		try
		{
			mod::Patch p;
			it.get_to(p);
			if (!ApplyPatch(p))
			{
				std::string address;
				it[mod::JSON_ADDRESS].get_to(address);
				throw std::exception((CONFIG_PATCHES_FAILED + address).c_str());
			}
		}
		catch (const std::exception& e)
		{
			LogPluginError(plugin_name, e);
		}
	}
}

void H4MSPlugin::Start()
{
	if (!GetDir())
	{
		SHOW_ERROR(FAILED_DIRECTORY);
		return;
	}

	if (m_exe.game())
		StartGame();
	else if (m_exe.editor())
		StartEditor();
	else
		SHOW_ERROR(UNSUPPORTED_EXE);
}

void H4MSPlugin::StartGame()
{
	if (!Hook(0x8E3A5C, Call, Stdcall, ::_HH_WinMain))
		SHOW_ERROR(MAIN_HOOK_FAILED);
	if (!WordPatch(0x8E39E2, 0x0875))
		SHOW_ERROR(FAILED_LAUNCH);
}

void H4MSPlugin::StartEditor()
{
	if (!Hook(0x663041, Call, Stdcall, ::_HH_WinMain))
		SHOW_ERROR(MAIN_HOOK_FAILED);
	if (!WordPatch(0x663029, 0x0674))
		SHOW_ERROR(FAILED_LAUNCH);
}