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

}


