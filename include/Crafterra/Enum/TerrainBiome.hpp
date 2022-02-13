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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_TERRAIN_BIOME_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_TERRAIN_BIOME_HPP

/*#######################################################################################
	日本語リファレンス (Reference-ja)
	https://github.com/AsPJT/Crafterra/wiki/仕様：地形バイオーム
#######################################################################################*/

#include <AsLib2/DataType/PrimitiveDataType.hpp>

#ifndef CRAFTERRA_BIOME_T
#define CRAFTERRA_BIOME_T ::As::Uint8
#endif // CRAFTERRA_BIOME_T

namespace Crafterra {
	inline namespace DataType { using BiomeUint = CRAFTERRA_BIOME_T; }
	inline namespace Enum {

		// バイオームの種類
		enum class TerrainBiome : ::Crafterra::BiomeUint {
			empty     // 無し
			, sea        // 海
			, lake       // 湖
			, tundra    // ツンドラ
			, mountain // 山
			, desert    // 砂漠
			, forest    // 森林
			, rock      // 岩山
			, hill       // 丘
			, savannah // サバンナ
			, grass     // 草原
			, wall     // 草原
			, way     // 草原
			, room     // 草原
			, normal   // 通常の地面
			, size   // バイオームの数
		};

	}
}

#endif //Included Crafterra Library