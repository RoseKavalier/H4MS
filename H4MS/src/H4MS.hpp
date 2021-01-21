#pragma once

#include "stdafx.h"
#include "logger.hpp"
#include <ThirdParty/json.hpp>
using nlohmann::json;

namespace mod
{
	static constexpr LPCSTR JSON_ADDRESS = u8"address";
	static constexpr LPCSTR JSON_EDITOR  = u8"editor";
	static constexpr LPCSTR JSON_GAME    = u8"game";
	static constexpr LPCSTR JSON_NAME    = u8"name";
	static constexpr LPCSTR JSON_TYPE    = u8"type";
	static constexpr LPCSTR JSON_VALUE   = u8"value";

	struct Mod
	{
		std::string name;
		bool game;
		bool editor;
	};

	void from_json(const json& j, Mod& m)
	{
		j.at(JSON_NAME).get_to(m.name);
		j.at(JSON_GAME).get_to(m.game);
		j.at(JSON_EDITOR).get_to(m.editor);
	}
	void to_json(json& j, const Mod& m)
	{
		j = json{ {JSON_NAME, m.name}, {JSON_GAME, m.game}, {JSON_EDITOR, m.editor} };
	}

	struct Info
	{
		TString name;
		HMODULE hmodule;
	};

	struct Patch
	{
		enum class Type
		{
			byte,
			word,
			dword,
			floating_point,
			decimal_floating_point,
			inline_string,
			string,
			hex_patch,
			undefined,
		};

		Type        type;
		DWORD       address;
		BYTE        byte;
		WORD        word;
		DWORD       dword;
		FLOAT       floating_point;
		DOUBLE      decimal_floating_point;
		std::string text_string;

		Patch() : type(Type::undefined) {}
	};

	struct StringPatch
	{
		DWORD address;
		std::string text_string;
	};

	void from_json(const json& j, Patch& p)
	{
		std::string type;
		j.at(JSON_ADDRESS).get_to(p.address);
		j.at(JSON_TYPE).get_to(type);

		switch (type[0])
		{
		case 'b':
			p.type = Patch::Type::byte;
			j.at(JSON_VALUE).get_to(p.byte);
			break;
		case 'w':
			p.type = Patch::Type::word;
			j.at(JSON_VALUE).get_to(p.word);
			break;
		case 'd':
			if (type[1] == 'w')
			{
				p.type = Patch::Type::dword;
				j.at(JSON_VALUE).get_to(p.dword);
			}
			else if (type[1] == 'o')
			{
				p.type = Patch::Type::decimal_floating_point;
				j.at(JSON_VALUE).get_to(p.decimal_floating_point);
			}
			break;
		case 'f':
			p.type = Patch::Type::floating_point;
			j.at(JSON_VALUE).get_to(p.floating_point);
			break;
		case 'i':
			p.type = Patch::Type::inline_string;
			j.at(JSON_VALUE).get_to(p.text_string);
			break;
		case 's':
			p.type = Patch::Type::string;
			j.at(JSON_VALUE).get_to(p.text_string);
			break;
		case 'h':
			p.type = Patch::Type::hex_patch;
			j.at(JSON_VALUE).get_to(p.text_string);
			for (auto& c : p.text_string)
				c = std::toupper(c);
			break;
		default:
			break;
		}
	}

	void to_json(json& j, const Patch& p)
	{
		//TODO implementation
	}
}

class H4MSPlugin : public Plugin
{
	// ansi plugin name, required by patcher_x86
	static constexpr LPCSTR PLUGIN_NAME  = "H4MS";

	// utf8 strings for logging
	static constexpr LPCSTR CONFIG_INCORRECT         = u8"h4ms_config.json is incorrectly set up.";
	static constexpr LPCSTR CONFIG_PATCHES_FAILED    = u8"Failed to apply patch at ";
	static constexpr LPCSTR CONFIG_LIBRARIES_FORMAT  = u8"Unexpected \"libraries\" format in config.json.";
	static constexpr LPCSTR CONFIG_PATCHES_FORMAT    = u8"Unexpected \"patches\" format in config.json.";
	static constexpr LPCSTR JSON_ASSETS              = u8"assets";
	static constexpr LPCSTR JSON_LIBRARIES           = u8"libraries";
	static constexpr LPCSTR JSON_PATCHES             = u8"patches";
	static constexpr LPCSTR LOAD_LIBRARY_FAILED      = u8"Failed to load library: ";
	static constexpr LPCSTR OPEN_CONFIG_FILE         = u8"Unable to open config [";
	static constexpr LPCSTR PLUGIN_CONFIG_INCORRECT  = u8"config.json is incorrectly set up.";
	static constexpr LPCSTR PLUGIN_CONFIG_FAILED     = u8"Could not read \"Config.json\".";
	static constexpr LPCSTR PLUGIN_DIRECTORY_FAILED  = u8"Could not set directory for plugin.";
	static constexpr LPCSTR ASSETS_DIRECTORY_FAILED  = u8"Could not access \"Assets\" directory for plugin.";
	static constexpr LPCSTR PLUGINS_DIRECTORY_FAILED = u8"Failed to set directory to plugins directory: ";
	static constexpr LPCSTR LOADING_RESOURCE_FAILED  = u8"Failed to load the specified resource [";

	// TCHAR strings for debug
	static constexpr LPCTSTR ASSETS_DIR        = _T("Assets");
	static constexpr LPCTSTR CONFIG_FILE       = _T("h4ms_config.json");
	static constexpr LPCTSTR DEBUG_DIRECTORY   = _T("debug");
	static constexpr LPCTSTR DLL_TYPE          = _T("*.dll");
	static constexpr LPCTSTR FAILED_DIRECTORY  = _T("Could not get app directory.");
	static constexpr LPCTSTR FAILED_LAUNCH     = _T("Could not launch Heroes4.");
	static constexpr LPCTSTR MAIN_HOOK_FAILED  = _T("Could not create MainHook!");
	static constexpr LPCTSTR PLUGIN_CONFIG     = _T("config.json");
	static constexpr LPCTSTR PLUGINS_DIR       = _T("Plugins\\");
	static constexpr LPCTSTR RESOURCE_TYPE     = _T("*.h4r");
	static constexpr LPCTSTR UNSUPPORTED_EXE   = _T("Not a supported executable.");


public:
	H4MSPlugin() : Plugin()
	{
		Plugin::Status status = Init(PLUGIN_NAME);
		if (status != Plugin::Status::Success)
			ShowError(PLUGIN_NAME, status);
		else
			Start();
	}
	int MainHook();
private:
	bool ApplyPatch(const mod::Patch& p);
	bool CreateLogger();
	bool GetDir();
	bool Load(const std::string& mod_name);
	void Log(LPCSTR utf8);
	void Log(const std::string& utf8);
	void LogDebug(LPCSTR utf8);
	void LogDebug(const std::string& utf8);
	void LogPluginError(const std::string& name, const std::exception& e);
	void PluginAssets(const std::string& plugin_name);
	void PluginLibraries(const json& libraries, const std::string& plugin_name);
	void PluginPatches(const json& patches, const std::string& plugin_name);
	void Start();
	void StartGame();
	void StartEditor();

	h4::H4Version                 m_exe;
	TString                       m_directory;
	std::unique_ptr<Logger>       m_logger;
	std::vector<mod::Mod>         m_plugins;
	std::vector<mod::Info>        m_libraries;
	std::vector<mod::StringPatch> m_patchStrings;
};

H4MSPlugin& GetPlugin();