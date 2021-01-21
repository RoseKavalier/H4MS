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
#include "H4Memory.inl"

namespace h4
{
	_H4API_ H4Protect::H4Protect(UINT32 address, UINT32 size) :
		m_address(address),
		m_size(size),
		m_oldProtect()
	{
		m_protectEdited = VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, PAGE_EXECUTE_WRITECOPY, &m_oldProtect);
	}
	_H4API_ H4Protect::~H4Protect()
	{
		if (m_protectEdited)
			VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, m_oldProtect, &m_oldProtect);
	}
	_H4API_ BOOL H4Protect::CanWrite()
	{
		return m_protectEdited;
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

	_H4API_ BOOL H4Patcher::NakedHook5(UINT32 address, H4NakedFunction function)
	{
		H4Protect protect(address, 5);
		if (protect.CanWrite())
		{
			ByteAt(address) = H4Patcher::JMP;
			DwordAt(address + 1) = reinterpret_cast<UINT32>(function) - address - 5;
			return TRUE;
		}
		return FALSE;
	}
	_H4API_ BOOL H4Patcher::NakedHook(UINT32 address, H4NakedFunction function, UINT32 total_bytes)
	{
		if (total_bytes < 5)
			return FALSE;
		H4Protect protect(address, total_bytes);
		if (protect.CanWrite())
		{
			ByteAt(address) = H4Patcher::JMP;
			DwordAt(address + 1) = reinterpret_cast<UINT32>(function) - address - 5;
			for (UINT32 i = 5; i < total_bytes; ++i)
				ByteAt(address + i) = H4Patcher::NOP;
			return TRUE;
		}
		return FALSE;
	}

	_H4API_ BOOL H4Patcher::BytePatch(ADDRESS address, UINT8 value)
	{
		return WriteValue(address, value);
	}

	_H4API_ BOOL H4Patcher::CharPatch(ADDRESS address, INT8 value)
	{
		return WriteValue(address, value);
	}

	_H4API_ BOOL H4Patcher::WordPatch(ADDRESS address, UINT16 value)
	{
		return WriteValue(address, value);
	}

	_H4API_ BOOL H4Patcher::ShortPatch(ADDRESS address, INT16 value)
	{
		return WriteValue(address, value);
	}

	_H4API_ BOOL H4Patcher::DwordPatch(ADDRESS address, UINT32 value)
	{
		return WriteValue(address, value);
	}

	_H4API_ BOOL H4Patcher::IntPatch(ADDRESS address, INT32 value)
	{
		return WriteValue(address, value);
	}

	_H4API_ BOOL H4Patcher::FloatPatch(ADDRESS address, FLOAT value)
	{
		return WriteValue(address, value);
	}

	_H4API_ BOOL H4Patcher::DoublePatch(ADDRESS address, DOUBLE value)
	{
		return WriteValue(address, value);
	}
}