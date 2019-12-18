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

#ifndef _H4ALLOCATOR_HPP_
#define _H4ALLOCATOR_HPP_

#include "../H4_Core.hpp"
#include "../H4_Base.hpp"

namespace h4
{
	// * a base structure to let H4 structures use 
	// * h4 operators new, delete, new[], delete[]	
	struct H4Allocator
	{
		PVOID operator new(const size_t sz);
		VOID  operator delete(const PVOID block);
		PVOID operator new[](const size_t sz);
		VOID  operator delete[](const PVOID block);
	};

	// * an allocator to simulate h4's new & delete on objects
	template <typename T>
	struct H4ObjectAllocator
	{
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;

		H4ObjectAllocator() noexcept;
		// * allocates memory
		T* allocate(size_t number) const noexcept;
		// * deallocates memory
		VOID deallocate(T* block) const noexcept;
		// * calls default constructor
		VOID construct(T* block) const noexcept;
		// * calls constructor with argument
		VOID construct(T* block, const T& value) const noexcept;
		// * calls default destructor
		VOID destroy(T* block) const noexcept;

		template <typename U>
		H4ObjectAllocator(const H4ObjectAllocator<U>&) noexcept;
		template <typename U>
		bool operator==(const H4ObjectAllocator<U>&) const noexcept;
		template <typename U>
		bool operator!=(const H4ObjectAllocator<U>&) const noexcept;
	};

	// * an allocator to similate use of h4's new[] & delete[] on arrays
	template <typename T>
	struct H4ArrayAllocator
	{
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
	private:
		size_t* GetArrayBase(T* block) const noexcept;
		size_t GetArraySize(T* block) const noexcept;
	public:
		H4ArrayAllocator() noexcept;
		// * allocates memory
		T* allocate(size_t number) const noexcept;
		// * deallocates memory
		VOID deallocate(T* block) const noexcept;
		// * calls default constructor
		VOID construct(T* block) const noexcept;
		// * calls constructor with argument
		VOID construct(T* block, const T& value) const noexcept;
		// * calls default destructor
		VOID destroy(T* block) const noexcept;

		template <typename U>
		H4ArrayAllocator(const H4ArrayAllocator<U>&) noexcept;
		template <typename U>
		bool operator==(const H4ArrayAllocator<U>&) const noexcept;
		template <typename U>
		bool operator!=(const H4ArrayAllocator<U>&) const noexcept;
	};
}

#endif /* #define _H4ALLOCATOR_HPP_ */