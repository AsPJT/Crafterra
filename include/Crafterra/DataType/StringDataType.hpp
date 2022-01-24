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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_STRING_DATA_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_STRING_DATA_TYPE_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>

//##########################################################################################
// <string> のインクルード
#ifndef CRAFTERRA_NOT_USE_STRING
#ifndef CRAFTERRA_USE_STRING
#define CRAFTERRA_USE_STRING
#endif // CRAFTERRA_USE_STRING
#include <string>
#endif // CRAFTERRA_NOT_USE_STRING
//##########################################################################################
// STRING_T
#ifndef CRAFTERRA_STRING_T
#ifdef CRAFTERRA_USE_STRING
#define CRAFTERRA_STRING_T ::std::basic_string<::Crafterra::DataType::Char>
#else
// 今後、ここに string の独自実装を追加
class TestString{};
#define CRAFTERRA_STRING_T TestString
#endif // CRAFTERRA_USE_STRING
#endif // CRAFTERRA_STRING_T
//##########################################################################################
// STRING
#ifndef CRAFTERRA_STRING
#define CRAFTERRA_STRING CRAFTERRA_STRING_T
#endif // CRAFTERRA_STRING
//##########################################################################################
// using 型定義
namespace Crafterra {
	inline namespace DataType {
		using String = CRAFTERRA_STRING_T;
	}
}
//##########################################################################################

#endif //Included Crafterra Library