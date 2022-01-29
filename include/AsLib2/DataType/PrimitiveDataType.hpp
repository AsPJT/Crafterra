/*##########################################################################################

	AsLib2 🌏

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

#ifndef INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_PRIMITIVE_DATA_TYPE_HPP
#define INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_PRIMITIVE_DATA_TYPE_HPP

//##########################################################################################
// 各種設定

// <cstddef> をインクルードしない
// #define ASLIB2_NOT_USE_CSTDDEF

// <cstdint> をインクルードしない
// #define ASLIB2_NOT_USE_CSTDINT

//##########################################################################################
// <cstddef> のインクルード
#ifndef ASLIB2_NOT_USE_CSTDDEF
#ifndef ASLIB2_USE_CSTDDEF
#define ASLIB2_USE_CSTDDEF
#endif // ASLIB2_USE_CSTDDEF
#include <cstddef> // size_t
#endif // ASLIB2_NOT_USE_CSTDDEF
//##########################################################################################
// <cstdint> のインクルード
#ifndef ASLIB2_NOT_USE_CSTDINT
#ifndef ASLIB2_USE_CSTDINT
#define ASLIB2_USE_CSTDINT
#endif // ASLIB2_USE_CSTDINT
#include <cstdint>
#endif // ASLIB2_NOT_USE_CSTDINT
//##########################################################################################
// SIZE_T
#ifndef ASLIB2_SIZE_T
#ifdef ASLIB2_USE_CSTDDEF
#define ASLIB2_SIZE_T ::std::size_t
#else
#define ASLIB2_SIZE_T unsigned long long
#endif // ASLIB2_USE_CSTDDEF
#endif // ASLIB2_SIZE_T
//##########################################################################################
// INT64_T
#ifndef ASLIB2_INT64_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT64_T ::std::int_fast64_t
#else
#define ASLIB2_INT64_T long long
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_INT64_T
//##########################################################################################
// UINT64_T
#ifndef ASLIB2_UINT64_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT64_T ::std::uint_fast64_t
#else
#define ASLIB2_UINT64_T unsigned long long
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_UINT64_T
//##########################################################################################
// INT32_T
#ifndef ASLIB2_INT32_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT32_T ::std::int_fast32_t
#else
#define ASLIB2_INT32_T long
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_INT32_T
//##########################################################################################
// UINT32_T
#ifndef ASLIB2_UINT32_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT32_T ::std::uint_fast32_t
#else
#define ASLIB2_UINT32_T unsigned long
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_UINT32_T
//##########################################################################################
// INT16_T
#ifndef ASLIB2_INT16_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT16_T ::std::int_fast16_t
#else
#define ASLIB2_INT16_T short
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_INT16_T
//##########################################################################################
// UINT16_T
#ifndef ASLIB2_UINT16_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT16_T ::std::uint_fast16_t
#else
#define ASLIB2_UINT16_T unsigned short
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_UINT16_T
//##########################################################################################
// INT8_T
#ifndef ASLIB2_INT8_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT8_T ::std::int_fast8_t
#else
#define ASLIB2_INT8_T char
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_INT8_T
//##########################################################################################
// UINT8_T
#ifndef ASLIB2_UINT8_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT8_T ::std::uint_fast8_t
#else
#define ASLIB2_UINT8_T unsigned char
#endif // ASLIB2_USE_CSTDINT
#endif // ASLIB2_UINT8_T
//##########################################################################################
// CHAR_T
#ifndef ASLIB2_CHAR_T
#define ASLIB2_CHAR_T char
#endif // ASLIB2_CHAR_T
//##########################################################################################
// CHAR32_T
#ifndef ASLIB2_CHAR32_T
#define ASLIB2_CHAR32_T char32_t
#endif // ASLIB2_CHAR32_T
//##########################################################################################
// CHAR16_T
#ifndef ASLIB2_CHAR16_T
#define ASLIB2_CHAR16_T char16_t
#endif // ASLIB2_CHAR16_T
//##########################################################################################
// CHAR8_T ( C++20 以降の処理は今後実装 )
#ifndef ASLIB2_CHAR8_T
#define ASLIB2_CHAR8_T char
#endif // ASLIB2_CHAR8_T
//##########################################################################################
// using 型定義
namespace As {
	inline namespace DataType {
		// size_t
		using IndexUint = ASLIB2_SIZE_T;
		using SizeUint  = ASLIB2_SIZE_T;
		// int, uint
		using Int64  = ASLIB2_INT64_T;
		using Uint64 = ASLIB2_UINT64_T;
		using Int32  = ASLIB2_INT32_T;
		using Uint32 = ASLIB2_UINT32_T;
		using Int16  = ASLIB2_INT16_T;
		using Uint16 = ASLIB2_UINT16_T;
		using Int8   = ASLIB2_INT8_T;
		using Uint8  = ASLIB2_UINT8_T;
		// char
		using Char   = ASLIB2_CHAR_T;
		using Char32 = ASLIB2_CHAR32_T;
		using Char16 = ASLIB2_CHAR16_T;
		using Char8  = ASLIB2_CHAR8_T;
	}
}
//##########################################################################################

#endif //Included AsLib2