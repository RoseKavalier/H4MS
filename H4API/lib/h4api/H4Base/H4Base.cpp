//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-18                        //
//                      Last edit: 2019-12-18                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H4Base.hpp"

namespace h4
{
	_H4API_ PVOID F_malloc(UINT size)
	{
		return CDECL_1(PVOID, 0x8D98A0, size);
	}

	_H4API_ VOID F_delete(PVOID obj)
	{
		if (obj)
			CDECL_1(VOID, 0x8DBD90, obj);
	}

	_H4API_ VOID H4Error::ShowError(LPCSTR message, LPCSTR title)
	{
		MessageBoxA(nullptr, message, title, MB_OK | MB_ICONERROR);
	}
	_H4API_ BOOL H4Error::ShowErrorChoice(LPCSTR message, LPCSTR title)
	{
		return MessageBoxA(nullptr, message, title, MB_OKCANCEL | MB_ICONERROR) == IDOK;
	}
	_H4API_ VOID H4Error::_ShowError(LPCWSTR message, LPCWSTR title)
	{
		MessageBoxW(nullptr, message, title, MB_OK | MB_ICONERROR);
	}
	_H4API_ BOOL H4Error::_ShowErrorChoice(LPCWSTR message, LPCWSTR title)
	{
		return MessageBoxW(nullptr, message, title, MB_OKCANCEL | MB_ICONERROR);
	}
	_H4API_ BOOL H4Bitfield::GetState(INT32 position) const
	{
		INT32 index = position >> 5;
		INT32 pos = position & 0x1F;
		INT32 value = 1 << pos;
		return ((&m_bf)[index]) & value;
	}
	_H4API_ VOID H4Bitfield::SetState(INT32 position, BOOL state)
	{
		INT32 index = position >> 5;
		INT32 pos = position & 0x1F;
		INT32 value = 1 << pos;
		if (state)
			((&m_bf)[index]) |= value;
		else
			((&m_bf)[index]) &= ~value;
	}
	_H4API_ VOID H4Bitfield::Set(UINT32 value)
	{
		m_bf = value;
	}
	_H4API_ UINT H4Bitfield::Get() const
	{
		return m_bf;
	}

	_H4API_ H4Version::H4Version() : m_version(GameVersion::UNKNOWN)
	{
		IMAGE_DOS_HEADER* pDOSHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(0x400000);
		IMAGE_NT_HEADERS* pNTHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>((reinterpret_cast<BYTE*>(pDOSHeader) + pDOSHeader->e_lfanew));
		DWORD entry = pNTHeaders->OptionalHeader.AddressOfEntryPoint;

		switch (entry)
		{
		case 0x31D600:
			m_version = GameVersion::EDITOR;
			break;
		case 0x56FEC0:
			m_version = GameVersion::GAME;
			break;
		case 0x4E3981:
			m_version = GameVersion::UNPATCHED_GAME;
			break;
		case 0x262F66:
			m_version = GameVersion::UNPATCHED_EDITOR;
		default:
			break;
		}
	}

	_H4API_ H4Version::GameVersion H4Version::version() const
	{
		return m_version;
	}

	_H4API_ BOOL8 H4Version::game() const
	{
		return m_version == GameVersion::GAME || m_version == GameVersion::UNPATCHED_GAME;
	}

	_H4API_ BOOL8 H4Version::editor() const
	{
		return m_version == GameVersion::EDITOR || m_version == GameVersion::UNPATCHED_EDITOR;
	}

}


