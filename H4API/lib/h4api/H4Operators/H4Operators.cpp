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

#include "H4Operators.hpp"

#pragma warning(push)
#pragma warning(disable:4595) /* disable 'operator new': non-member operator new or delete functions may not be declared inline warning */

_H4API_ PVOID operator new(const size_t size)
{
	return h4::F_malloc(size);
}

_H4API_ VOID operator delete(PVOID block)
{
	if (block)
		h4::F_delete(block);
}

_H4API_ PVOID operator new[](const size_t size)
{
	return h4::F_malloc(size);
}

_H4API_ VOID operator delete[](PVOID block)
{
	if (block)
		h4::F_delete(block);
}
#pragma warning(pop) /* #pragma warning(disable:4595) */