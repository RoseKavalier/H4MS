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

#ifndef _H4BASE_HPP_
#define _H4BASE_HPP_

#include "../H4_Core.hpp"
#include "../../H4Types.hpp"

// * Prevents some warnings
#define _CRT_SECURE_NO_WARNINGS

// * Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// * use std::min and std::max instead
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

// * use STL functions instead of C-style
#include <algorithm>

// * Input / output functions
#include <cstdio>

// * disable sprintf warning
#pragma warning(disable:4996)

#if (__cplusplus > 199711L || (_MSC_VER && _MSC_VER >= 1900))
// * true if your IDE version is C++11 compatible
// * this checks for C++11 standard or Visual Studio 2015+
#define _CPLUSPLUS11_
#endif

#if (_MSC_VER && _MSC_VER <= 1500)
#pragma warning (disable:4482)
#endif

#ifndef _CPLUSPLUS11_
#ifndef nullptr
// * nullptr was added with C++11
#define nullptr NULL
#endif
#ifndef constexpr
// * constexpr was added with C++11
#define constexpr const
#endif
#ifndef _H4ENUM_
// * enum class was added with C++11
#define _H4ENUM_ enum
#endif
#ifndef noexcept
// * noexcept keyword added with C++11
#define noexcept throw()
#endif
#else
#ifndef _H4ENUM_
// * enum class
#define _H4ENUM_ enum class
#endif
#endif

#ifdef _MSC_VER
#ifndef _H4API_FORCEINLINE_
/**
 * @brief used to force function to be inline
 */
#define _H4API_FORCEINLINE_ __forceinline
#endif
#elif defined(__GNUC__)
#ifndef _H4API_FORCEINLINE_
 /**
 * @brief used to force function to be inline
 */
#define _H4API_FORCEINLINE_ inline __attribute__((__always_inline__))
#endif
#elif defined(__CLANG__)
#if __has_attribute(__always_inline__)
#ifndef _H4API_FORCEINLINE_
/**
 * @brief used to force function to be inline
 */
#define _H4API_FORCEINLINE_ inline __attribute__((__always_inline__))
#endif
#else
#ifndef _H4API_FORCEINLINE_
/**
 * @brief used to force function to be inline
 */
#define _H4API_FORCEINLINE_ inline
#endif
#endif
#else
#ifndef _H4API_FORCEINLINE_
/**
 * @brief used to force function to be inline
 */
#define _H4API_FORCEINLINE_ inline
#endif
#endif

// * indicates this content will be deprecated
// * and replaced by equivalent expressions
#define _H4API_DEPRECATED_

// * for uniformity's sake
#ifdef VOID
#undef VOID
// * void type
typedef void VOID;
#else
// * void type
typedef void VOID;
#endif

#ifndef ArraySize
// * returns number of elements in an array
#define ArraySize(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifndef Abs
// * returns absolute value of number
#define Abs(num) (((num) >= 0) ? (num) : (-(num)))
#endif

// * model function definitions
// * used to interact with game functions
#pragma region Model Functions
#pragma region THISCALL_DECLARATIONS
#ifndef THISCALL_0
#define THISCALL_0(return_type, address) ((return_type(__thiscall *)(VOID))(address))()
#endif
#ifndef THISCALL_1
#define THISCALL_1(return_type, address, a1) ((return_type(__thiscall *)(UINT))(address))((UINT)(a1))
#endif
#ifndef THISCALL_2
#define THISCALL_2(return_type, address, a1, a2) ((return_type(__thiscall *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef THISCALL_3
#define THISCALL_3(return_type, address, a1, a2, a3) ((return_type(__thiscall *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef THISCALL_4
#define THISCALL_4(return_type, address, a1, a2, a3, a4) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef THISCALL_5
#define THISCALL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef THISCALL_6
#define THISCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef THISCALL_7
#define THISCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef THISCALL_8
#define THISCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef THISCALL_9
#define THISCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef THISCALL_10
#define THISCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef THISCALL_11
#define THISCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef THISCALL_12
#define THISCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef THISCALL_13
#define THISCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef THISCALL_14
#define THISCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef THISCALL_15
#define THISCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef THISCALL_16
#define THISCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef THISCALL_17
#define THISCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif
#pragma endregion

#pragma region STDCALL_DECLARATIONS
#ifndef STDCALL_0
#define STDCALL_0(return_type, address) ((return_type(__stdcall *)(VOID))(address))()
#endif
#ifndef STDCALL_1
#define STDCALL_1(return_type, address, a1) ((return_type(__stdcall *)(UINT))(address))((UINT)(a1))
#endif
#ifndef STDCALL_2
#define STDCALL_2(return_type, address, a1, a2) ((return_type(__stdcall *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef STDCALL_3
#define STDCALL_3(return_type, address, a1, a2, a3) ((return_type(__stdcall *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef STDCALL_4
#define STDCALL_4(return_type, address, a1, a2, a3, a4) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef STDCALL_5
#define STDCALL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef STDCALL_6
#define STDCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef STDCALL_7
#define STDCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef STDCALL_8
#define STDCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef STDCALL_9
#define STDCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef STDCALL_10
#define STDCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef STDCALL_11
#define STDCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef STDCALL_12
#define STDCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef STDCALL_13
#define STDCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef STDCALL_14
#define STDCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef STDCALL_15
#define STDCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef STDCALL_16
#define STDCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef STDCALL_17
#define STDCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif
#pragma endregion

#pragma region FASTCALL_DECLARATIONS
#ifndef FASTCALL_0
#define FASTCALL_0(return_type, address) ((return_type(__fastcall *)(VOID))(address))()
#endif
#ifndef FASTCALL_1
#define FASTCALL_1(return_type, address, a1) ((return_type(__fastcall *)(UINT))(address))((UINT)(a1))
#endif
#ifndef FASTCALL_2
#define FASTCALL_2(return_type, address, a1, a2) ((return_type(__fastcall *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef FASTCALL_3
#define FASTCALL_3(return_type, address, a1, a2, a3) ((return_type(__fastcall *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef FASTCALL_4
#define FASTCALL_4(return_type, address, a1, a2, a3, a4) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef FASTCALL_5
#define FASTCALL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef FASTCALL_6
#define FASTCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef FASTCALL_7
#define FASTCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef FASTCALL_8
#define FASTCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef FASTCALL_9
#define FASTCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef FASTCALL_10
#define FASTCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef FASTCALL_11
#define FASTCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef FASTCALL_12
#define FASTCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef FASTCALL_13
#define FASTCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef FASTCALL_14
#define FASTCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef FASTCALL_15
#define FASTCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef FASTCALL_16
#define FASTCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef FASTCALL_17
#define FASTCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif
#pragma endregion

#pragma region CDECL_DECLARATIONS
#ifndef CDECL_0
#define CDECL_0(return_type, address) ((return_type(__cdecl *)(VOID))(address))()
#endif
#ifndef CDECL_1
#define CDECL_1(return_type, address, a1) ((return_type(__cdecl *)(UINT))(address))((UINT)(a1))
#endif
#ifndef CDECL_2
#define CDECL_2(return_type, address, a1, a2) ((return_type(__cdecl *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef CDECL_3
#define CDECL_3(return_type, address, a1, a2, a3) ((return_type(__cdecl *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef CDECL_4
#define CDECL_4(return_type, address, a1, a2, a3, a4) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef CDECL_5
#define CDECL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef CDECL_6
#define CDECL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef CDECL_7
#define CDECL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef CDECL_8
#define CDECL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef CDECL_9
#define CDECL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef CDECL_10
#define CDECL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef CDECL_11
#define CDECL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef CDECL_12
#define CDECL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef CDECL_13
#define CDECL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef CDECL_14
#define CDECL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef CDECL_15
#define CDECL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef CDECL_16
#define CDECL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef CDECL_17
#define CDECL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif
#pragma endregion

#pragma region VA_DECLARATIONS

// * you absolutely need c++11 to use STDCALL_VA, THISCALL_VA and FASTCALL_VA
// * in prior versions, variadic templates don't exist
// * va_list arguments would absolutely require __cdecl to clean the stack
#ifdef _CPLUSPLUS11_

namespace h4vargs
{
	template<typename return_type, typename ...Args>
	return_type Stdcall_Variadic(UINT address, Args... args)
	{
		return (reinterpret_cast<return_type(__stdcall*)(Args...)>(address))(args...);
	}

	template<typename return_type, typename ...Args>
	return_type Thiscall_Variadic(UINT address, Args... args)
	{
		return (reinterpret_cast<return_type(__thiscall*)(Args...)>(address))(args...);
	}

	template<typename return_type, typename ...Args>
	return_type Fastcall_Variadic(UINT address, Args... args)
	{
		return (reinterpret_cast<return_type(__fastcall*)(Args...)>(address))(args...);
	}
}

#ifndef STDCALL_VA
#define STDCALL_VA(return_type, address, ...) h4vargs::Stdcall_Variadic<return_type>(address, __VA_ARGS__)
#endif

#ifndef THISCALL_VA
#define THISCALL_VA(return_type, address, ...) h4vargs::Thiscall_Variadic<return_type>(address, __VA_ARGS__)
#endif

#ifndef FASTCALL_VA
#define FASTCALL_VA(return_type, address, ...) h4vargs::Fastcall_Variadic<return_type>(address, __VA_ARGS__)
#endif

#endif /* _CPLUSPLUS11_ */

#ifndef CDECL_VA
#define CDECL_VA(return_type, address, a1, ...) ((return_type(__cdecl *)(UINT, ...))(address))((UINT)(a1), __VA_ARGS__)
#endif

#ifndef CDECL_VA2
#define CDECL_VA2(return_type, address, a1, a2, ...) ((return_type(__cdecl *)(UINT, UINT, ...))(address))((UINT)(a1), (UINT)(a2), __VA_ARGS__)
#endif
#pragma endregion

#pragma endregion

namespace h4
{
	/**
	 * @brief Get a reference of specific type at the specified address
	 *
	 * @tparam T Type of data to cast to.
	 * @param address The location of the sought data.
	 * @return A reference of the value at the specified location.
	*/
	template<typename T>
	_H4API_FORCEINLINE_ T& ValueAt(ADDRESS address) { return *reinterpret_cast<T*>(address); }

	/**
	 * @brief Get a reference of const char* at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the string at the specified location.
	 */
	_H4API_FORCEINLINE_ LPCSTR& StrAt(ADDRESS address) { return ValueAt<LPCSTR>(address); }
	/**
	 * @brief Get a reference of pointer for any data.
	 *
	 * @tparam T Type of data of the data.
	 * @param address The location of the sought data.
	 * @return A reference of the pointer at the specified location.
	 */
	template<typename T>
	_H4API_FORCEINLINE_ UINT32& PtrAt(T data) { return ValueAt<UINT32>(ADDRESS(data)); }
	/**
	 * @brief Get a reference of unsigned integer at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the unsigned integer at the specified location.
	 */
	_H4API_FORCEINLINE_ UINT32& DwordAt(ADDRESS address) { return ValueAt<UINT32>(address); }
	/**
	 * @brief Get a reference of signed integer at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the signed integer at the specified location.
	 */
	_H4API_FORCEINLINE_ INT32&  IntAt(ADDRESS address) { return ValueAt<INT32>(address); }
	/**
	 * @brief Get a reference of unsigned short at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the unsigned short at the specified location.
	 */
	_H4API_FORCEINLINE_ UINT16& WordAt(ADDRESS address) { return ValueAt<UINT16>(address); }
	/**
	 * @brief Get a reference of signed short at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the signed short at the specified location.
	 */
	_H4API_FORCEINLINE_ INT16&  ShortAt(ADDRESS address) { return ValueAt<INT16>(address); }
	/**
	 * @brief Get a reference of unsigned char at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the unsigned char at the specified location.
	 */
	_H4API_FORCEINLINE_ UINT8&  ByteAt(ADDRESS address) { return ValueAt<UINT8>(address); }
	/**
	 * @brief Get a reference of signed char at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the signed char at the specified location.
	 */
	_H4API_FORCEINLINE_ INT8&   CharAt(ADDRESS address) { return ValueAt<INT8>(address); }
	/**
	 * @brief Get a reference of float at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the float at the specified location.
	 */
	_H4API_FORCEINLINE_ FLOAT&  FloatAt(ADDRESS address) { return ValueAt<FLOAT>(address); }
	/**
	 * @brief Get a reference of double at the specified address.
	 *
	 * @param address The location of the sought data.
	 * @return A reference of the double at the specified location.
	 */
	_H4API_FORCEINLINE_ DOUBLE& DoubleAt(ADDRESS address) { return ValueAt<DOUBLE>(address); }

	/**
	 * @brief Get the value of the function called (or jump destination) at the specified address.
	 *
	 * @param address The location of the call/JMP instruction.
	 * @return The address of the destination.
	 */
	_H4API_FORCEINLINE_ h4func  FuncAt(ADDRESS address) { return ValueAt<h4func>(address + 1) + address + 5; }

	/**
	 * @brief Get the address of a specific object.
	 *
	 * @tparam T Type of the current object.
	 * @param value The object itself.
	 * @return The address of the provided object.
	 */
	template<typename T>
	_H4API_FORCEINLINE_ ADDRESS AddressOf(const T& value) { return reinterpret_cast<ADDRESS>(&value); }

	/**
	 * @brief Used to get the hexadecimal value of a type T instead of getting a casted value.
	 * Useful to convert a FLOAT to DWORD, e.g. 0.25f is returned as 0x3E800000h instead of 0h.
	 *
	 * @tparam T Type of data to convert
	 * @param value Value of the data to convert.
	 * @return Converted data as unsigned integer.
	 */
	template<typename T>
	_H4API_FORCEINLINE_ UINT32 ValueAsDword(T value) { return DwordAt(AddressOf(value)); }

	// * heapalloc using H3 assets
	PVOID F_malloc(UINT size);
	// * heapfree using H3 assets
	VOID F_delete(PVOID obj);

	class H4Version
	{
	public:
		enum class GameVersion
		{
			UNKNOWN          = -1,
			GAME             = 0,			
			EDITOR           = 1,
			UNPATCHED_GAME   = 2,
			UNPATCHED_EDITOR = 3,
		};
	public:
		/**
		 * @brief the constructor is required to detect the exe type
		 */
		_H4API_ H4Version();
		/**
		 * @brief returns the detected exe version
		 *
		 * @return GameVersion a value matching the current exe
		 */
		_H4API_ GameVersion version() const;
		/**
		 * @brief returns the detected exe version
		 *
		 * @return true if the current exe is game
		 */
		_H4API_ BOOL8 game() const;
		/**
		 * @brief returns the detected exe version
		 *
		 * @return true if the current exe is editor
		 */
		_H4API_ BOOL8 editor() const;
	private:
		GameVersion m_version;
	};

	namespace H4Error
	{
		// * external messagebox showing message
		_H4API_ VOID ShowError(LPCSTR message, LPCSTR title = "H4Error!");
		// * external messagebox showing message and offering OK / Cancel choice
		_H4API_ BOOL ShowErrorChoice(LPCSTR message, LPCSTR title = "H4Error!");
		// * external messagebox showing message
		// * wide char format
		_H4API_ VOID _ShowError(LPCWSTR message, LPCWSTR title = L"H4Error!");
		// * external messagebox showing message and offering OK / Cancel choice
		// * wide char format
		_H4API_ BOOL _ShowErrorChoice(LPCWSTR message, LPCWSTR title = L"H4Error!");
	}

	// * dword used as bitfield
	// * can be used as an array of bitfields
	struct H4Bitfield
	{
	protected:
		UINT m_bf;
	public:
		// * returns whether bit at position is set or not
		// * position can exceed the scope of bitfield, meaning greater than 32 bits
		_H4API_ BOOL GetState(INT32 position) const;
		// * sets bit at position to on or off
		// * position can exceed the scope of bitfield, meaning greater than 32 bits
		_H4API_ VOID SetState(INT32 position, BOOL state);
		// * Sets bitfield to specified value
		_H4API_ VOID Set(UINT32 value);
		// * Gets bitfield value as 32bits
		_H4API_ UINT Get() const;
	};
} // namespace h4

#endif /* #define _H4BASE_HPP_ */