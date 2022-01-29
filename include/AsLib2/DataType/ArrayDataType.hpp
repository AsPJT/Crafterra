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

#ifndef INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_ARRAY_DATA_TYPE_HPP
#define INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_ARRAY_DATA_TYPE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>

//##########################################################################################
// <array> のインクルード
#ifndef ASLIB2_NOT_USE_ARRAY
#ifndef ASLIB2_USE_ARRAY
#define ASLIB2_USE_ARRAY
#endif // ASLIB2_USE_ARRAY
#include <array>
#endif // ASLIB2_NOT_USE_ARRAY
//##########################################################################################
// ARRAY_T
#ifndef ASLIB2_ARRAY_T
#ifdef ASLIB2_USE_ARRAY
#define ASLIB2_ARRAY_T ::std::array
#else
// 今後、ここに array の独自実装を追加
template <typename Type_>
class TestArray{};
#define ASLIB2_ARRAY_T TestArray
#endif // ASLIB2_USE_ARRAY
#endif // ASLIB2_ARRAY_T
//##########################################################################################
// ARRAY
#ifndef ASLIB2_ARRAY
#define ASLIB2_ARRAY ASLIB2_ARRAY_T
#endif // ASLIB2_ARRAY
//##########################################################################################
// using 型定義
namespace As {
	inline namespace DataType {
		template <class Type_, ::As::IndexUint Number_>
		using Array = ASLIB2_ARRAY_T<Type_, Number_>;

		template <class Type_, ::As::IndexUint NumberX_, ::As::IndexUint NumberY_>
		using Matrix = ASLIB2_ARRAY_T<ASLIB2_ARRAY_T<Type_, NumberX_>, NumberY_>;
	}
}
//##########################################################################################

#endif //Included AsLib2