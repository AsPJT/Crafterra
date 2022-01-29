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

#ifndef INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_STRING_DATA_TYPE_HPP
#define INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_STRING_DATA_TYPE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>

//##########################################################################################
// <string> のインクルード
#ifndef ASLIB2_NOT_USE_STRING
#ifndef ASLIB2_USE_STRING
#define ASLIB2_USE_STRING
#endif // ASLIB2_USE_STRING
#include <string>
#endif // ASLIB2_NOT_USE_STRING
//##########################################################################################
// STRING_T
#ifndef ASLIB2_STRING_T
#ifdef ASLIB2_USE_STRING
#define ASLIB2_STRING_T ::std::basic_string<::As::Char>
#else
// 今後、ここに string の独自実装を追加
class TestString{};
#define ASLIB2_STRING_T TestString
#endif // ASLIB2_USE_STRING
#endif // ASLIB2_STRING_T
//##########################################################################################
// STRING
#ifndef ASLIB2_STRING
#define ASLIB2_STRING ASLIB2_STRING_T
#endif // ASLIB2_STRING
//##########################################################################################
// using 型定義
namespace As {
	inline namespace DataType {
		using String = ASLIB2_STRING_T;
	}
}
//##########################################################################################

#endif //Included AsLib2