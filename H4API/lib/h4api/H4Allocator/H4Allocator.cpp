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

#include "H4Allocator.hpp"

namespace h4
{
	_H4API_ PVOID H4Allocator::operator new(const size_t sz)
	{
		return F_malloc(sz);
	}
	_H4API_ VOID H4Allocator::operator delete(const PVOID block)
	{
		F_delete(block);
	}
	_H4API_ PVOID H4Allocator::operator new[](const size_t sz)
	{
		return F_malloc(sz);
	}
	_H4API_ VOID H4Allocator::operator delete[](const PVOID block)
	{
		F_delete(block);
	}
}