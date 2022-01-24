/*##########################################################################################

	Crafterra Library 🌏

	[Planning and Production]
	2017-2022 Kasugaccho
	2018-2022 As Project

	[Contact Us]
	wanotaitei@gmail.com
	https://github.com/AsPJT/Crafterra

	[License]
	Distributed under the CC0 1.0.
	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_PRIMITIVE_DATA_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_PRIMITIVE_DATA_TYPE_HPP

//##########################################################################################
// 各種設定

// <cstddef> をインクルードしない
// #define CRAFTERRA_NOT_USE_CSTDDEF

// <cstdint> をインクルードしない
// #define CRAFTERRA_NOT_USE_CSTDINT

//##########################################################################################
// <cstddef> のインクルード
#ifndef CRAFTERRA_NOT_USE_CSTDDEF
#ifndef CRAFTERRA_USE_CSTDDEF
#define CRAFTERRA_USE_CSTDDEF
#endif // CRAFTERRA_USE_CSTDDEF
#include <cstddef> // size_t
#endif // CRAFTERRA_NOT_USE_CSTDDEF
//##########################################################################################
// <cstdint> のインクルード
#ifndef CRAFTERRA_NOT_USE_CSTDINT
#ifndef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_USE_CSTDINT
#include <cstdint>
#endif // CRAFTERRA_NOT_USE_CSTDINT
//##########################################################################################
// SIZE_T
#ifndef CRAFTERRA_SIZE_T
#ifdef CRAFTERRA_USE_CSTDDEF
#define CRAFTERRA_SIZE_T ::std::size_t
#else
#define CRAFTERRA_SIZE_T unsigned long long
#endif // CRAFTERRA_USE_CSTDDEF
#endif // CRAFTERRA_SIZE_T
//##########################################################################################
// INT64_T
#ifndef CRAFTERRA_INT64_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_INT64_T ::std::int_fast64_t
#else
#define CRAFTERRA_INT64_T long long
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_INT64_T
//##########################################################################################
// UINT64_T
#ifndef CRAFTERRA_UINT64_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_UINT64_T ::std::uint_fast64_t
#else
#define CRAFTERRA_UINT64_T unsigned long long
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_UINT64_T
//##########################################################################################
// INT32_T
#ifndef CRAFTERRA_INT32_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_INT32_T ::std::int_fast32_t
#else
#define CRAFTERRA_INT32_T long
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_INT32_T
//##########################################################################################
// UINT32_T
#ifndef CRAFTERRA_UINT32_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_UINT32_T ::std::uint_fast32_t
#else
#define CRAFTERRA_UINT32_T unsigned long
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_UINT32_T
//##########################################################################################
// INT16_T
#ifndef CRAFTERRA_INT16_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_INT16_T ::std::int_fast16_t
#else
#define CRAFTERRA_INT16_T short
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_INT16_T
//##########################################################################################
// UINT16_T
#ifndef CRAFTERRA_UINT16_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_UINT16_T ::std::uint_fast16_t
#else
#define CRAFTERRA_UINT16_T unsigned short
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_UINT16_T
//##########################################################################################
// INT8_T
#ifndef CRAFTERRA_INT8_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_INT8_T ::std::int_fast8_t
#else
#define CRAFTERRA_INT8_T char
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_INT8_T
//##########################################################################################
// UINT8_T
#ifndef CRAFTERRA_UINT8_T
#ifdef CRAFTERRA_USE_CSTDINT
#define CRAFTERRA_UINT8_T ::std::uint_fast8_t
#else
#define CRAFTERRA_UINT8_T unsigned char
#endif // CRAFTERRA_USE_CSTDINT
#endif // CRAFTERRA_UINT8_T
//##########################################################################################
// CHAR_T
#ifndef CRAFTERRA_CHAR_T
#define CRAFTERRA_CHAR_T char
#endif // CRAFTERRA_CHAR_T
//##########################################################################################
// CHAR32_T
#ifndef CRAFTERRA_CHAR32_T
#define CRAFTERRA_CHAR32_T char32_t
#endif // CRAFTERRA_CHAR32_T
//##########################################################################################
// CHAR16_T
#ifndef CRAFTERRA_CHAR16_T
#define CRAFTERRA_CHAR16_T char16_t
#endif // CRAFTERRA_CHAR16_T
//##########################################################################################
// CHAR8_T ( C++20 以降の処理は今後実装 )
#ifndef CRAFTERRA_CHAR8_T
#define CRAFTERRA_CHAR8_T char
#endif // CRAFTERRA_CHAR8_T
//##########################################################################################
// using 型定義
namespace Crafterra {
	inline namespace DataType {
		// size_t
		using IndexUint = CRAFTERRA_SIZE_T;
		using SizeUint  = CRAFTERRA_SIZE_T;
		// int, uint
		using Int64  = CRAFTERRA_INT64_T;
		using Uint64 = CRAFTERRA_UINT64_T;
		using Int32  = CRAFTERRA_INT32_T;
		using Uint32 = CRAFTERRA_UINT32_T;
		using Int16  = CRAFTERRA_INT16_T;
		using Uint16 = CRAFTERRA_UINT16_T;
		using Int8   = CRAFTERRA_INT8_T;
		using Uint8  = CRAFTERRA_UINT8_T;
		// char
		using Char   = CRAFTERRA_CHAR_T;
		using Char32 = CRAFTERRA_CHAR32_T;
		using Char16 = CRAFTERRA_CHAR16_T;
		using Char8  = CRAFTERRA_CHAR8_T;
	}
}
//##########################################################################################

#endif //Included Crafterra Library