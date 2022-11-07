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

#include "H4Functions.hpp"

namespace h4
{
	_H4API_ BOOL8 LoadResourceFile(LPCSTR name)
	{
		return CDECL_1(BOOL8, 0x7FF910, name);
	}
	_H4API_ VOID LoadResourcesFromDirectory(LPCSTR directory)
	{
		CDECL_1(VOID, 0x7FF070, directory);
	}
}
namespace h4e
{
	_H4API_ BOOL8 LoadResourceFile(LPCSTR name)
	{
		return THISCALL_1(BOOL8, 0x619E20, name);
	}
	_H4API_ VOID LoadResourcesFromDirectory(LPCSTR directory)
	{
		THISCALL_1(VOID, 0x6193E0, directory);
	}
}
