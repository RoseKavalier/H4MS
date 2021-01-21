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
	inline BOOL H4Patcher::WriteValue(ADDRESS address, const T value)
	{
		H4Protect protect(address, sizeof(T));
		if (!protect.CanWrite())
			return FALSE;
		ValueAt<T>(address) = value;
		return TRUE;
	}

	template<typename T, size_t size>
	inline BOOL H4Patcher::WriteValues(const UINT address, const T(&value)[size])
	{
		H4Protect protect(address, sizeof(T) * size);
		if (!protect.CanWrite())
			return FALSE;
		for (size_t i = 0; i < size; ++i)
			ValueAt<T>(address + i) = value[i];
		return TRUE;
	}

	template<typename T>
	inline BOOL H4Patcher::AddressOfPatch(const UINT address, const T & data)
	{
		return DwordPatch(address, AddressOf(data));
	}

	template<typename Address, typename Type, size_t size>
	typename inline std::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4, BOOL>::type
		H4Patcher::AddressOfPatch(const Address(&address)[size], const Type& data)
	{
		for (size_t i = 0; i < size; ++i)
			if (!DwordPatch(address[i], AddressOf(data)))
				return FALSE;
		return TRUE;

		std::addressof(address);
	}

	template<typename T>
	inline BOOL H4Patcher::ObjectPatch(T & reference, T data)
	{
		return WriteValue<T>(AddressOf(reference), data);
	}

	template<size_t size>
	inline BOOL H4Patcher::HexPatch(const UINT address, const BYTE(&value)[size])
	{
		return WriteValues<BYTE, size>(address, value);
	}	
}

#endif /* #define _H4MEMORY_INL_ */