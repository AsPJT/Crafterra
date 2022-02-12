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

//----------
// 各種設定

// <cstddef> をインクルードしない
// #define ASLIB2_NOT_USE_CSTDDEF

// <cstdint> をインクルードしない
// #define ASLIB2_NOT_USE_CSTDINT

//----------
// <cstddef> のインクルード
#ifndef ASLIB2_NOT_USE_CSTDDEF
#ifndef ASLIB2_USE_CSTDDEF
#define ASLIB2_USE_CSTDDEF
#endif // !ASLIB2_USE_CSTDDEF
#include <cstddef> // size_t
#endif // !ASLIB2_NOT_USE_CSTDDEF
//----------
// <cstdint> のインクルード
#ifndef ASLIB2_NOT_USE_CSTDINT
#ifndef ASLIB2_USE_CSTDINT
#define ASLIB2_USE_CSTDINT
#endif // !ASLIB2_USE_CSTDINT
#include <cstdint>
#endif // !ASLIB2_NOT_USE_CSTDINT
//----------
// SIZE_T
#ifndef ASLIB2_SIZE_T
#ifdef ASLIB2_USE_CSTDDEF
#define ASLIB2_SIZE_T ::std::size_t
#else
#define ASLIB2_SIZE_T unsigned long long
#endif // ASLIB2_USE_CSTDDEF
#endif // !ASLIB2_SIZE_T




//----------
// INT64_T
#ifndef ASLIB2_INT64_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef INT64_MAX
#define ASLIB2_INT64_T ::std::int64_t
#else
#define ASLIB2_INT64_T ::std::int_least64_t
#endif // INT64_MAX
#else
#define ASLIB2_INT64_T long long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT64_T
//----------
// UINT64_T
#ifndef ASLIB2_UINT64_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef UINT64_MAX
#define ASLIB2_UINT64_T ::std::uint64_t
#else
#define ASLIB2_UINT64_T ::std::uint_least64_t
#endif // UINT64_MAX
#else
#define ASLIB2_UINT64_T unsigned long long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT64_T
//----------
// INT32_T
#ifndef ASLIB2_INT32_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef INT32_MAX
#define ASLIB2_INT32_T ::std::int32_t
#else
#define ASLIB2_INT32_T ::std::int_least32_t
#endif // INT32_MAX
#else
#define ASLIB2_INT32_T long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT32_T
//----------
// UINT32_T
#ifndef ASLIB2_UINT32_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef UINT32_MAX
#define ASLIB2_UINT32_T ::std::uint32_t
#else
#define ASLIB2_UINT32_T ::std::uint_least32_t
#endif // UINT32_MAX
#else
#define ASLIB2_UINT32_T unsigned long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT32_T
//----------
// INT16_T
#ifndef ASLIB2_INT16_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef INT16_MAX
#define ASLIB2_INT16_T ::std::int16_t
#else
#define ASLIB2_INT16_T ::std::int_least16_t
#endif // INT16_MAX
#else
#define ASLIB2_INT16_T short
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT16_T
//----------
// UINT16_T
#ifndef ASLIB2_UINT16_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef UINT16_MAX
#define ASLIB2_UINT16_T ::std::uint16_t
#else
#define ASLIB2_UINT16_T ::std::uint_least16_t
#endif // UINT16_MAX
#else
#define ASLIB2_UINT16_T unsigned short
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT16_T
//----------
// INT8_T
#ifndef ASLIB2_INT8_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef INT8_MAX
#define ASLIB2_INT8_T ::std::int8_t
#else
#define ASLIB2_INT8_T ::std::int_least8_t
#endif // INT8_MAX
#else
#define ASLIB2_INT8_T char
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT8_T
//----------
// UINT8_T
#ifndef ASLIB2_UINT8_T
#ifdef ASLIB2_USE_CSTDINT
#ifdef UINT8_MAX
#define ASLIB2_UINT8_T ::std::uint8_t
#else
#define ASLIB2_UINT8_T ::std::uint_least8_t
#endif // UINT8_MAX
#else
#define ASLIB2_UINT8_T unsigned char
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT8_T




//----------
// INT_LEAST64_T
#ifndef ASLIB2_INT_LEAST64_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_LEAST64_T ::std::int_least64_t
#else
#define ASLIB2_INT_LEAST64_T long long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_LEAST64_T
//----------
// UINT_LEAST64_T
#ifndef ASLIB2_UINT_LEAST64_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_LEAST64_T ::std::uint_least64_t
#else
#define ASLIB2_UINT_LEAST64_T unsigned long long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_LEAST64_T
//----------
// INT_LEAST32_T
#ifndef ASLIB2_INT_LEAST32_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_LEAST32_T ::std::int_least32_t
#else
#define ASLIB2_INT_LEAST32_T long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_LEAST32_T
//----------
// UINT_LEAST32_T
#ifndef ASLIB2_UINT_LEAST32_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_LEAST32_T ::std::uint_least32_t
#else
#define ASLIB2_UINT_LEAST32_T unsigned long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_LEAST32_T
//----------
// INT_LEAST16_T
#ifndef ASLIB2_INT_LEAST16_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_LEAST16_T ::std::int_least16_t
#else
#define ASLIB2_INT_LEAST16_T short
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_LEAST16_T
//----------
// UINT_LEAST16_T
#ifndef ASLIB2_UINT_LEAST16_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_LEAST16_T ::std::uint_least16_t
#else
#define ASLIB2_UINT_LEAST16_T unsigned short
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_LEAST16_T
//----------
// INT_LEAST8_T
#ifndef ASLIB2_INT_LEAST8_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_LEAST8_T ::std::int_least8_t
#else
#define ASLIB2_INT_LEAST8_T char
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_LEAST8_T
//----------
// UINT_LEAST8_T
#ifndef ASLIB2_UINT_LEAST8_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_LEAST8_T ::std::uint_least8_t
#else
#define ASLIB2_UINT_LEAST8_T unsigned char
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_LEAST8_T




//----------
// INT_FAST64_T
#ifndef ASLIB2_INT_FAST64_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_FAST64_T ::std::int_fast64_t
#else
#define ASLIB2_INT_FAST64_T long long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_FAST64_T
//----------
// UINT_FAST64_T
#ifndef ASLIB2_UINT_FAST64_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_FAST64_T ::std::uint_fast64_t
#else
#define ASLIB2_UINT_FAST64_T unsigned long long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_FAST64_T
//----------
// INT_FAST32_T
#ifndef ASLIB2_INT_FAST32_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_FAST32_T ::std::int_fast32_t
#else
#define ASLIB2_INT_FAST32_T long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_FAST32_T
//----------
// UINT_FAST32_T
#ifndef ASLIB2_UINT_FAST32_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_FAST32_T ::std::uint_fast32_t
#else
#define ASLIB2_UINT_FAST32_T unsigned long
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_FAST32_T
//----------
// INT_FAST16_T
#ifndef ASLIB2_INT_FAST16_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_FAST16_T ::std::int_fast16_t
#else
#define ASLIB2_INT_FAST16_T int
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_FAST16_T
//----------
// UINT_FAST16_T
#ifndef ASLIB2_UINT_FAST16_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_FAST16_T ::std::uint_fast16_t
#else
#define ASLIB2_UINT_FAST16_T unsigned int
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_FAST16_T
//----------
// INT_FAST8_T
#ifndef ASLIB2_INT_FAST8_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_INT_FAST8_T ::std::int_fast8_t
#else
#define ASLIB2_INT_FAST8_T char
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_INT_FAST8_T
//----------
// UINT_FAST8_T
#ifndef ASLIB2_UINT_FAST8_T
#ifdef ASLIB2_USE_CSTDINT
#define ASLIB2_UINT_FAST8_T ::std::uint_fast8_t
#else
#define ASLIB2_UINT_FAST8_T unsigned char
#endif // ASLIB2_USE_CSTDINT
#endif // !ASLIB2_UINT_FAST8_T




//----------
// CHAR_T
#ifndef ASLIB2_CHAR_T
#define ASLIB2_CHAR_T char
#endif // !ASLIB2_CHAR_T
//----------
// CHAR32_T
#ifndef ASLIB2_CHAR32_T
#define ASLIB2_CHAR32_T char32_t
#endif // !ASLIB2_CHAR32_T
//----------
// CHAR16_T
#ifndef ASLIB2_CHAR16_T
#define ASLIB2_CHAR16_T char16_t
#endif // !ASLIB2_CHAR16_T
//----------
// CHAR8_T ( C++20 以降の処理は今後実装 )
#ifndef ASLIB2_CHAR8_T
#define ASLIB2_CHAR8_T char
#endif // !ASLIB2_CHAR8_T
//----------
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
		// int_least, uint_least
		using IntLeast64 = ASLIB2_INT_LEAST64_T;
		using UintLeast64 = ASLIB2_UINT_LEAST64_T;
		using IntLeast32 = ASLIB2_INT_LEAST32_T;
		using UintLeast32 = ASLIB2_UINT_LEAST32_T;
		using IntLeast16 = ASLIB2_INT_LEAST16_T;
		using UintLeast16 = ASLIB2_UINT_LEAST16_T;
		using IntLeast8 = ASLIB2_INT_LEAST8_T;
		using UintLeast8 = ASLIB2_UINT_LEAST8_T;
		// int_fast, uint_fast
		using IntFast64 = ASLIB2_INT_FAST64_T;
		using UintFast64 = ASLIB2_UINT_FAST64_T;
		using IntFast32 = ASLIB2_INT_FAST32_T;
		using UintFast32 = ASLIB2_UINT_FAST32_T;
		using IntFast16 = ASLIB2_INT_FAST16_T;
		using UintFast16 = ASLIB2_UINT_FAST16_T;
		using IntFast8 = ASLIB2_INT_FAST8_T;
		using UintFast8 = ASLIB2_UINT_FAST8_T;
		// char
		using Char   = ASLIB2_CHAR_T;
		using Char32 = ASLIB2_CHAR32_T;
		using Char16 = ASLIB2_CHAR16_T;
		using Char8  = ASLIB2_CHAR8_T;
		// float
		using Float32 = float;
		using Float64 = double;
		using FloatMax = long double;
	}
}
//----------

#endif //Included AsLib2