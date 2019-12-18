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

#ifndef _H4MEMORY_INL_
#define _H4MEMORY_INL_

#include "H4Memory.hpp"

namespace h4
{
	template<typename T>
	inline H4Patcher::WriteValue<T>::WriteValue(const UINT address, const T value)
	{
		H4Protect protect(address, sizeof(T));
		if (protect.CanWrite())
			*reinterpret_cast<T*>(address) = value;
	}

	template<typename T, size_t size>
	inline H4Patcher::WriteValues<T, size>::WriteValues(const UINT address, const T(&value)[size])
	{
		H4Protect protect(address, sizeof(T) * size);
		if (protect.CanWrite())
			for (size_t i = 0; i < size; ++i)
				reinterpret_cast<T*>(address)[i] = value[i];
	}

	template<size_t size>
	inline VOID H4Patcher::HexPatch(const UINT address, const BYTE(&value)[size])
	{
		WriteValues<BYTE, size>(address, value);
	}

}

#endif /* #define _H4MEMORY_INL_ */