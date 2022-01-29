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

#ifndef INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_VECTOR_DATA_TYPE_HPP
#define INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_VECTOR_DATA_TYPE_HPP

//##########################################################################################
// <vector> のインクルード
#ifndef ASLIB2_NOT_USE_VECTOR
#ifndef ASLIB2_USE_VECTOR
#define ASLIB2_USE_VECTOR
#endif // ASLIB2_USE_VECTOR
#include <vector>
#endif // ASLIB2_NOT_USE_VECTOR
//##########################################################################################
// VECTOR_T
#ifndef ASLIB2_VECTOR_T
#ifdef ASLIB2_USE_VECTOR
#define ASLIB2_VECTOR_T ::std::vector
#else
// 今後、ここに vector の独自実装を追加
template <typename Type_>
class TestVector{};
#define ASLIB2_VECTOR_T TestVector
#endif // ASLIB2_USE_VECTOR
#endif // ASLIB2_VECTOR_T
//##########################################################################################
// VECTOR
#ifndef ASLIB2_VECTOR
#define ASLIB2_VECTOR ASLIB2_VECTOR_T
#endif // ASLIB2_VECTOR
//##########################################################################################
//// using 型定義
//namespace Asc {
//	inline namespace DataType {
//		// メモリアロケータは未実装
//		template <typename Type_>
//		using Vector = ASLIB2_VECTOR_T<Type_>;
//	}
//}
//##########################################################################################

#endif //Included AsLib2