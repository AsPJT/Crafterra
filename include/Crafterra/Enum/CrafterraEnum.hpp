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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_CRAFTERRA_ENUM_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_CRAFTERRA_ENUM_HPP

#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

#include <Crafterra/Enum/ActorMode.hpp>
#include <Crafterra/Enum/TerrainTileConnectionCliff.hpp>

namespace Crafterra {
	inline namespace Enum {

		// ( オートタイル ) 同じ性質のブロックとの接続タイプ ( 通常 + 崖 )
		enum class TerrainTileConnectionWoditorAutoTile : TerrainTileConnectionWoditorAutoTileUint {
			  nothing_upper_left
			, nothing_upper_right
			, nothing_lower_left
			, nothing_lower_right
			, up_and_down_upper_left
			, up_and_down_upper_right
			, up_and_down_lower_left
			, up_and_down_lower_right
			, left_and_right_upper_left
			, left_and_right_upper_right
			, left_and_right_lower_left
			, left_and_right_lower_right
			, cross_upper_left
			, cross_upper_right
			, cross_lower_left
			, cross_lower_right
			, all_upper_left
			, all_upper_right
			, all_lower_left
			, all_lower_right
			, size
		};

		// 今後、別の hpp を作成して管理
		struct AutoTile {
			TerrainTileConnectionWoditorAutoTile auto_tile_upper_left{ TerrainTileConnectionWoditorAutoTile::nothing_upper_left };
			TerrainTileConnectionWoditorAutoTile auto_tile_upper_right{ TerrainTileConnectionWoditorAutoTile::nothing_upper_right };
			TerrainTileConnectionWoditorAutoTile auto_tile_lower_left{ TerrainTileConnectionWoditorAutoTile::nothing_lower_left };
			TerrainTileConnectionWoditorAutoTile auto_tile_lower_right{ TerrainTileConnectionWoditorAutoTile::nothing_lower_right };
		};

	}
}

#endif //Included Crafterra Library