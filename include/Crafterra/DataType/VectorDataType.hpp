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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_VECTOR_DATA_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_VECTOR_DATA_TYPE_HPP

//##########################################################################################
// <vector> のインクルード
#ifndef CRAFTERRA_NOT_USE_VECTOR
#ifndef CRAFTERRA_USE_VECTOR
#define CRAFTERRA_USE_VECTOR
#endif // CRAFTERRA_USE_VECTOR
#include <vector>
#endif // CRAFTERRA_NOT_USE_VECTOR
//##########################################################################################
// VECTOR_T
#ifndef CRAFTERRA_VECTOR_T
#ifdef CRAFTERRA_USE_VECTOR
#define CRAFTERRA_VECTOR_T ::std::vector
#else
// 今後、ここに vector の独自実装を追加
template <typename Type_>
class TestVector{};
#define CRAFTERRA_VECTOR_T TestVector
#endif // CRAFTERRA_USE_VECTOR
#endif // CRAFTERRA_VECTOR_T
//##########################################################################################
// VECTOR
#ifndef CRAFTERRA_VECTOR
#define CRAFTERRA_VECTOR CRAFTERRA_VECTOR_T
#endif // CRAFTERRA_VECTOR
//##########################################################################################
//// using 型定義
//namespace Crafterra {
//	inline namespace DataType {
//		// メモリアロケータは未実装
//		template <typename Type_>
//		using Vector = CRAFTERRA_VECTOR_T<Type_>;
//	}
//}
//##########################################################################################

#endif //Included Crafterra Library