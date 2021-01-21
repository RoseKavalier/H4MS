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

#ifndef _H4MEMORY_HPP_
#define _H4MEMORY_HPP_

#include "../H4_Core.hpp"
#include "../H4_Base.hpp"

namespace h4
{
	// * raii virtual protect
	class H4Protect
	{
		UINT32 m_address;
		UINT32 m_size;
		DWORD  m_oldProtect;
		BOOL   m_protectEdited;
	public:
		_H4API_ H4Protect(UINT32 address, UINT32 size);
		_H4API_ ~H4Protect();
		BOOL CanWrite();
	};

	// * perform operations on loaded memory
	namespace H4Patcher
	{
		enum mnemonics
		{
			INC_EAX    = 0x40,
			INC_ECX    = 0x41,
			INC_EDX    = 0x42,
			INC_EBX    = 0x43,
			INC_ESP    = 0x44,
			INC_EBP    = 0x45,
			INC_ESI    = 0x46,
			INC_EDI    = 0x47,
			DEC_EAX    = 0x48,
			DEC_ECX    = 0x49,
			DEC_EDX    = 0x4A,
			DEC_EBX    = 0x4B,
			DEC_ESP    = 0x4C,
			DEC_EBP    = 0x4D,
			DEC_ESI    = 0x4E,
			DEC_EDI    = 0x4F,
			PUSH_EAX   = 0x50,
			PUSH_ECX   = 0x51,
			PUSH_EDX   = 0x52,
			PUSH_EBX   = 0x53,
			PUSH_ESP   = 0x54,
			PUSH_EBP   = 0x55,
			PUSH_ESI   = 0x56,
			PUSH_EDI   = 0x57,
			POP_EAX    = 0x58,
			POP_ECX    = 0x59,
			POP_EDX    = 0x5A,
			POP_EBX    = 0x5B,
			POP_ESP    = 0x5C,
			POP_EBP    = 0x5D,
			POP_ESI    = 0x5E,
			POP_EDI    = 0x5F,
			PUSHAD     = 0x60,
			POPAD      = 0x61,
			PUSH_DWORD = 0x68,
			PUSH_BYTE  = 0x6A,
			SHORT_JO   = 0x70,
			SHORT_JNO  = 0x71,
			SHORT_JB   = 0x72,
			SHORT_JNB  = 0x73,
			SHORT_JZ   = 0x74,
			SHORT_JNZ  = 0x75,
			SHORT_JNA  = 0x76,
			SHORT_JA   = 0x77,
			SHORT_JS   = 0x78,
			SHORT_JNS  = 0x79,
			SHORT_JP   = 0x7A,
			SHORT_JNP  = 0x7B,
			SHORT_JL   = 0x7C,
			SHORT_JGE  = 0x7D, // JNL
			SHORT_JNG  = 0x7E,
			SHORT_JG   = 0x7F,
			NOP        = 0x90,
			PUSHFD     = 0x9C,
			POPFD      = 0x9D,
			CALL       = 0xE8,
			JMP        = 0xE9,
			SHORT_JMP  = 0xEB,
			_RETN_     = 0xC3,
			_RETNX_    = 0xC2,

			FAR_JO     = 0x0F80,
			FAR_JNO    = 0x0F81,
			FAR_JB     = 0x0F82,
			FAR_JNB    = 0x0F83,
			FAR_JZ     = 0x0F84,
			FAR_JNZ    = 0x0F85,
			FAR_JNA    = 0x0F86,
			FAR_JA     = 0x0F87,
			FAR_JS     = 0x0F88,
			FAR_JNS    = 0x0F89,
			FAR_JP     = 0x0F8A,
			FAR_JNP    = 0x0F8B,
			FAR_JL     = 0x0F8C,
			FAR_JNL    = 0x0F8D,
			FAR_JNG    = 0x0F8E,
			FAR_JG     = 0x0F8F,
			CALL_DWORD = 0x15FF,
		};

		/**
		 * @brief finds the first byte sequence in a specified region
		 *
		 * @param haystack region in which to look for
		 * @param hlen the length of the memory region to search
		 * @param needle byte sequence to search for
		 * @param nlen how many bytes are in the needle
		 * @return PUCHAR address that matches needle, as a pointer. nullptr if not found
		 */
		_H4API_ PUCHAR Memmem(PUCHAR haystack, size_t hlen, PUCHAR needle, size_t nlen);
		/**
		 * @brief performs Memmem operation to find first byte sequence in a specified region
		 *
		 * @param address starting search point
		 * @param max_search_length maximum bytes to search through
		 * @param needle byte sequence to search for
		 * @param needle_length how many bytes are in the needle
		 * @param offset how many bytes to shift the found needle location by
		 * @return UINT32 location in the region, matching the needle and shifted by \p offset. nullptr if not found
		 */
		_H4API_ UINT32 FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset);

#ifndef _H4API_NAKED_FUNCTION_
#define _H4API_NAKED_FUNCTION_ VOID __declspec(naked)
#endif

		/**
		 * @brief only works for opcode length 5, most basic hook there is.
		 * you are also in charge of overwritten assembly
		 * @param address where to place hook
		 * @param function _H4API_NAKED_FUNCTION_ hook
		 */
		_H4API_ BOOL NakedHook5(UINT32 address, H4NakedFunction function);
		/**
		 * @brief same as NakedHook5, but replaces bytes after the first 5 by NOP instructions
		 *
		 * @param address where to place hook
		 * @param function _H4API_NAKED_FUNCTION_ hook
		 * @param total_bytes how many bytes should be overwritten, minimum 5
		 */
		_H4API_ BOOL NakedHook(UINT32 address, H4NakedFunction function, UINT32 total_bytes);
		/**
		 * @brief write data at specific location
		 *
		 * @tparam T byte, word or dword, float, double...
		 * @param address where to write data
		 * @param value data to write
		 * @return Whether the data was successfully written
		 */
		template<typename T>
		BOOL WriteValue(ADDRESS address, const T value);

		/**
		 * @brief write data at specific locations
		 *
		 * @tparam T byte, word or dword, float, double...
		 * @tparam size how many locations will be written to
		 * @param address where to write data
		 * @param value data to write
		 * @return Whether the data was successfully written
		 */
		template<typename T, size_t size>
		BOOL WriteValues(const UINT address, const T(&value)[size]);

		/**
		 * @brief writes pointer of data type (its address)
		 *
		 * @tparam T any data type
		 * @param address address to write to
		 * @param data a global or constexpr array, double or other value to be written as a pointer
		 * @return Whether the data was successfully written
		 */
		template<typename T>
		BOOL AddressOfPatch(const UINT address, const T& data);
		/**
		 * @brief writes pointer of data type (its address) to multiple locations
		 *
		 * @tparam Address primitive numerical type (int, unsigned int...)
		 * @tparam Type any data type
		 * @tparam size number of items in \p address array
		 * @param address addresses to write to
		 * @param data a global or constexpr array, double or other value to be written as a pointer
		 * @return H3Internal::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4>::type
		 */
		template<typename Address, typename Type, size_t size>
		typename std::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4, BOOL>::type
			AddressOfPatch(const Address(&address)[size], const Type& data);
		/**
		 * @brief writes data type to an object reference without having to dereference to obtain their address
		 *
		 * @tparam T type of the object
		 * @param reference data member of the object
		 * @param data replacement value
		 */
		template<typename T>
		BOOL ObjectPatch(T& reference, T data);
		/**
		 * @brief writes an array of bytes to the specified location
		 *
		 * @tparam size how many bytes are to be written
		 * @param address starting location to write patch
		 * @param value an array of bytes representing a patch
		 */
		template<size_t size>
		BOOL HexPatch(const UINT address, const BYTE(&value)[size]);

		_H4API_ BOOL BytePatch(ADDRESS address, UINT8 value);
		_H4API_ BOOL CharPatch(ADDRESS address, INT8 value);
		_H4API_ BOOL WordPatch(ADDRESS address, UINT16 value);
		_H4API_ BOOL ShortPatch(ADDRESS address, INT16 value);
		_H4API_ BOOL DwordPatch(ADDRESS address, UINT32 value);
		_H4API_ BOOL IntPatch(ADDRESS address, INT32 value);
		_H4API_ BOOL FloatPatch(ADDRESS address, FLOAT value);
		_H4API_ BOOL DoublePatch(ADDRESS address, DOUBLE value);
	}
}

#endif /* #define _H4MEMORY_HPP_ */