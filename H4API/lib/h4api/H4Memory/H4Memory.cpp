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

#include "H4Memory.hpp"

namespace h4
{
	_H4API_ H4Protect::H4Protect(UINT32 address, UINT32 size) :
		m_address(address),
		m_size(size),
		m_old_protect()
	{
		m_protect_edited = VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, PAGE_EXECUTE_WRITECOPY, &m_old_protect);
	}
	_H4API_ H4Protect::~H4Protect()
	{
		if (m_protect_edited)
			VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, m_old_protect, &m_old_protect);
	}
	_H4API_ BOOL H4Protect::CanWrite()
	{
		return m_protect_edited;
	}
	_H4API_ PUCHAR H4Patcher::Memmem(PUCHAR haystack, size_t hlen, PUCHAR needle, size_t nlen)
	{
		PUCHAR p = haystack;
		size_t plen = hlen;

		if (!nlen)
			return nullptr;

		const UCHAR needle_first = *static_cast<unsigned char*>(needle);

		while (plen >= nlen && ((p = static_cast<unsigned char*>(memchr(p, needle_first, plen - nlen + 1)))))
		{
			if (!memcmp(p, needle, nlen))
				return p;
			p++;
			plen = hlen - (p - haystack);
		}

		return nullptr;
	}
	_H4API_ UINT32 H4Patcher::FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset)
	{
		if (!address)
			return NULL;

		UINT32 p = reinterpret_cast<UINT32>(H4Patcher::Memmem(address, max_search_length, needle, needle_length));
		if (p)
			p += offset;
		return p;
	}

	_H4API_ VOID H4Patcher::NakedHook5(UINT32 start, VOID* function)
	{
		H4Protect protect(start, 5);
		if (protect.CanWrite())
		{
			ByteAt(start) = H4Patcher::jmp;
			DwordAt(start + 1) = reinterpret_cast<UINT32>(function) - start - 5;
		}
	}
}