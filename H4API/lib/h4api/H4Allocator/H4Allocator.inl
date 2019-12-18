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

#ifndef _H4ALLOCATOR_INL_
#define _H4ALLOCATOR_INL_

#include "H4Allocator.hpp"

namespace h4
{
	template<typename T>
	inline H4ObjectAllocator<T>::H4ObjectAllocator() noexcept
	{
	}
	template<typename T>
	inline T * H4ObjectAllocator<T>::allocate(size_t number) const noexcept
	{
		return reinterpret_cast<T*>(F_malloc(number * sizeof(T)));
	}
	template<typename T>
	inline VOID H4ObjectAllocator<T>::deallocate(T * block) const noexcept
	{
		F_delete(reinterpret_cast<PVOID>(block));
	}
	template<typename T>
	inline VOID H4ObjectAllocator<T>::construct(T * block) const noexcept
	{
		new(reinterpret_cast<PVOID>(block)) T();
	}
	template<typename T>
	inline VOID H4ObjectAllocator<T>::construct(T * block, const T & value) const noexcept
	{
		new(reinterpret_cast<PVOID>(block)) T(value);
	}
	template<typename T>
	inline VOID H4ObjectAllocator<T>::destroy(T * block) const noexcept
	{
		block->~T();
	}

	template<typename T>
	inline size_t * H4ArrayAllocator<T>::GetArrayBase(T * block) const noexcept
	{
		reinterpret_cast<size_t*>(block);
		return block - 1;
	}
	template<typename T>
	inline size_t H4ArrayAllocator<T>::GetArraySize(T * block) const noexcept
	{
		return *GetArrayBase();
	}
	template<typename T>
	inline H4ArrayAllocator<T>::H4ArrayAllocator() noexcept
	{
	}
	template<typename T>
	inline T * H4ArrayAllocator<T>::allocate(size_t number) const noexcept
	{
		size_t* block = reinterpret_cast<size_t*>(F_malloc(number * sizeof(T) + sizeof(size_t)));
		*block = number;
		return reinterpret_cast<T*>(block + 1);
	}
	template<typename T>
	inline VOID H4ArrayAllocator<T>::deallocate(T * block) const noexcept
	{
		F_delete(reinterpret_cast<PVOID>(GetArrayBase()));
	}
	template<typename T>
	inline VOID H4ArrayAllocator<T>::construct(T * block) const noexcept
	{
		size_t number = GetArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			new(reinterpret_cast<PVOID>(block)) T();
			++block;
		}
	}
	template<typename T>
	inline VOID H4ArrayAllocator<T>::construct(T * block, const T & value) const noexcept
	{
		size_t number = GetArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			new(reinterpret_cast<PVOID>(block)) T(value);
			++block;
		}
	}
	template<typename T>
	inline VOID H4ArrayAllocator<T>::destroy(T * block) const noexcept
	{
		size_t number = GetArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			block->~T();
			++block;
		}
	}

	template<typename T>
	template<typename U>
	inline H4ObjectAllocator<T>::H4ObjectAllocator(const H4ObjectAllocator<U>&) noexcept
	{
	}
	template<typename T>
	template<typename U>
	inline bool H4ObjectAllocator<T>::operator==(const H4ObjectAllocator<U>&) const noexcept
	{
		return TRUE;
	}
	template<typename T>
	template<typename U>
	inline bool H4ObjectAllocator<T>::operator!=(const H4ObjectAllocator<U>&) const noexcept
	{
		return FALSE;
	}

	template<typename T>
	template<typename U>
	inline H4ArrayAllocator<T>::H4ArrayAllocator(const H4ArrayAllocator<U>&) noexcept
	{
	}

	template<typename T>
	template<typename U>
	inline bool H4ArrayAllocator<T>::operator==(const H4ArrayAllocator<U>&) const noexcept
	{
		return true;
	}

	template<typename T>
	template<typename U>
	inline bool H4ArrayAllocator<T>::operator!=(const H4ArrayAllocator<U>&) const noexcept
	{
		return false;
	}
}

#endif /* #define _H4ALLOCATOR_INL_ */