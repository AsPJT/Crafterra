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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_ARRAY_DATA_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_ARRAY_DATA_TYPE_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>

//##########################################################################################
// <array> のインクルード
#ifndef CRAFTERRA_NOT_USE_ARRAY
#ifndef CRAFTERRA_USE_ARRAY
#define CRAFTERRA_USE_ARRAY
#endif // CRAFTERRA_USE_ARRAY
#include <array>
#endif // CRAFTERRA_NOT_USE_ARRAY
//##########################################################################################
// ARRAY_T
#ifndef CRAFTERRA_ARRAY_T
#ifdef CRAFTERRA_USE_ARRAY
#define CRAFTERRA_ARRAY_T ::std::array
#else
// 今後、ここに array の独自実装を追加
template <typename Type_>
class TestArray{};
#define CRAFTERRA_ARRAY_T TestArray
#endif // CRAFTERRA_USE_ARRAY
#endif // CRAFTERRA_ARRAY_T
//##########################################################################################
// ARRAY
#ifndef CRAFTERRA_ARRAY
#define CRAFTERRA_ARRAY CRAFTERRA_ARRAY_T
#endif // CRAFTERRA_ARRAY
//##########################################################################################
// using 型定義
namespace Crafterra {
	inline namespace DataType {
		template <class Type_, ::Crafterra::DataType::IndexUint Number_>
		using Array = CRAFTERRA_ARRAY_T<Type_, Number_>;

		template <class Type_, ::Crafterra::DataType::IndexUint NumberX_, ::Crafterra::DataType::IndexUint NumberY_>
		using Matrix = CRAFTERRA_ARRAY_T<CRAFTERRA_ARRAY_T<Type_, NumberX_>, NumberY_>;
	}
}
//##########################################################################################

#endif //Included Crafterra Library