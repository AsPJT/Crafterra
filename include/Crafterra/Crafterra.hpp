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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_CRAFTERRA_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_CRAFTERRA_HPP

//##########################################################################################
// Macro
// マクロ定義 ( 完成 & 更新あり )
#include <Crafterra/Macro/Library.hpp>
#include <Crafterra/Macro/Version.hpp>
#include <Crafterra/Macro/ThirdParty.hpp>
#include <Crafterra/Macro/New.hpp>
//##########################################################################################
// Data Type
// プリミティブ型定義 ( 完成 )
#include <AsLib2/DataType/PrimitiveDataType.hpp>
// テンプレート型 ( ほぼ完成 )
#include <AsLib2/DataType/StringDataType.hpp>
#include <AsLib2/DataType/ArrayDataType.hpp>
#include <AsLib2/DataType/VectorDataType.hpp>
//##########################################################################################


// Crafterra 固有のプリミティブ型定義 ( 骨組みは完成 )
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

#include <Crafterra/Enum/CrafterraEnum.hpp>
#include <Crafterra/Enum/ActorDirection.hpp>

#include <Crafterra/Basic/Size2D.hpp>
#include <Crafterra/Basic/ElapsedTime.hpp>

#include <Crafterra/Basic/Resource.hpp>

#include <AsLib2/DataType/PrimitiveDataType.hpp>

namespace Crafterra {
	namespace System {
		// 初期のウィンドウの幅
		constexpr ::As::IndexUint init_window_width = 1280;
		// 初期のウィンドウの高さ
		constexpr ::As::IndexUint init_window_height = 720;
	}
	// マップサイズ
	constexpr ::As::IndexUint init_field_map_width = 512;
	constexpr ::As::IndexUint init_field_map_height = 512;
}

// 初回読み込み
#include <Crafterra/Basic/InitRead.hpp>

namespace Crafterra {
	namespace Color {
		// 色クラス ( 暫定 )
		using Color3 = unsigned int;
	}
}

#include <Crafterra/Basic/CoordinateSystem.hpp>

#include <Crafterra/Terrain/MapChip.hpp>

#include <Crafterra/Actor/Actor.hpp>

#include <Crafterra/Terrain/TerrainChunk.hpp>

//##########################################################################################
#include <AsLib2/AsLib2.hpp>
//##########################################################################################

#include <Crafterra/Terrain/FieldMap.hpp>

#endif //Included Crafterra Library