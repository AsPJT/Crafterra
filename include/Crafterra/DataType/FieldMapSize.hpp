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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_FIELD_MAP_SIZE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_FIELD_MAP_SIZE_HPP

#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

namespace Crafterra {
	inline namespace DataType {

		// フィールドマップの大きさ
		constexpr ::As::IndexUint default_field_map_width = 512; // 幅
		constexpr ::As::IndexUint default_field_map_depth = 512; // 奥行
		constexpr ::As::IndexUint default_field_map_height = 128; // 高さ
		constexpr ::As::IndexUint default_field_map_layer = 3; // 層

		// フィールドマップ座標系
		struct FieldMapSize {
			::As::IndexUint width = default_field_map_width; // 幅
			::As::IndexUint depth = default_field_map_depth; // 奥行
			::As::IndexUint height = default_field_map_height; // 高さ
			::As::IndexUint layer = default_field_map_layer; // 層
		};
		constexpr FieldMapSize default_field_map = FieldMapSize{};

	}
}
//##########################################################################################

#endif //Included Crafterra Library