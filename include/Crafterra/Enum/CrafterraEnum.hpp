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

namespace Crafterra {
	inline namespace Enum {

		// アクタの向き
		enum class ActorDirection : ::Crafterra::DataType::ActorDirectionUint {
			empty
			, down
			, left
			, right
			, up
			, lower_left
			, lower_right
			, upper_left
			, upper_right
			, size
		};
		// フィールドマップにおける操作アクタの状態
		enum OperationActorStateInFieldMap : ::Crafterra::DataType::OperationActorStateInFieldMapUint {
			operation_actor_state_in_field_map_empty
			, operation_actor_state_in_field_map_walking // 陸路の歩行
			, operation_actor_state_in_field_map_ratite_bird // 飛べない鳥 ( 地上の高速移動 )
			, operation_actor_state_in_field_map_ship // 船
			, operation_actor_state_in_field_map_airship // 飛空艇
			, operation_actor_state_in_field_map_size
		};


		// 同じ性質のブロックとの接続タイプ ( 通常 + 崖 )
		enum MapChipTypeHomogeneousConnection : MapChipTypeHomogeneousConnectionUint {
			map_chip_type_homogeneous_connection_nothing
			, map_chip_type_homogeneous_connection_all
			, map_chip_type_homogeneous_connection_up_down
			, map_chip_type_homogeneous_connection_left_right
			, map_chip_type_homogeneous_connection_up
			, map_chip_type_homogeneous_connection_left
			, map_chip_type_homogeneous_connection_right
			, map_chip_type_homogeneous_connection_down
			, map_chip_type_homogeneous_connection_up_left_0
			, map_chip_type_homogeneous_connection_up_right_0
			, map_chip_type_homogeneous_connection_left_down_0
			, map_chip_type_homogeneous_connection_right_down_0
			, map_chip_type_homogeneous_connection_up_left_1
			, map_chip_type_homogeneous_connection_up_right_1
			, map_chip_type_homogeneous_connection_left_down_1
			, map_chip_type_homogeneous_connection_right_down_1
			, map_chip_type_homogeneous_connection_up_left_right_0
			, map_chip_type_homogeneous_connection_up_left_down_0
			, map_chip_type_homogeneous_connection_up_right_down_0
			, map_chip_type_homogeneous_connection_left_right_down_0
			, map_chip_type_homogeneous_connection_up_left_right_1
			, map_chip_type_homogeneous_connection_up_left_down_1
			, map_chip_type_homogeneous_connection_up_right_down_1
			, map_chip_type_homogeneous_connection_left_right_down_1
			, map_chip_type_homogeneous_connection_up_left_right_2
			, map_chip_type_homogeneous_connection_up_left_down_2
			, map_chip_type_homogeneous_connection_up_right_down_2
			, map_chip_type_homogeneous_connection_left_right_down_2
			, map_chip_type_homogeneous_connection_up_left_right_3
			, map_chip_type_homogeneous_connection_up_left_down_3
			, map_chip_type_homogeneous_connection_up_right_down_3
			, map_chip_type_homogeneous_connection_left_right_down_3
			, map_chip_type_homogeneous_connection_right_down_cliff
			, map_chip_type_homogeneous_connection_left_right_down_cliff
			, map_chip_type_homogeneous_connection_left_down_cliff
			, map_chip_type_homogeneous_connection_down_cliff
			, map_chip_type_homogeneous_connection_right_up_cliff
			, map_chip_type_homogeneous_connection_left_right_up_cliff
			, map_chip_type_homogeneous_connection_left_up_cliff
			, map_chip_type_homogeneous_connection_up_cliff
			, map_chip_type_homogeneous_connection_size
		};


		// ( オートタイル ) 同じ性質のブロックとの接続タイプ ( 通常 + 崖 )
		enum AutoTileTypeHomogeneousConnection : AutoTileTypeHomogeneousConnectionUint {
			  auto_tile_type_homogeneous_connection_nothing_upper_left
			, auto_tile_type_homogeneous_connection_nothing_upper_right
			, auto_tile_type_homogeneous_connection_nothing_lower_left
			, auto_tile_type_homogeneous_connection_nothing_lower_right
			, auto_tile_type_homogeneous_connection_up_and_down_upper_left
			, auto_tile_type_homogeneous_connection_up_and_down_upper_right
			, auto_tile_type_homogeneous_connection_up_and_down_lower_left
			, auto_tile_type_homogeneous_connection_up_and_down_lower_right
			, auto_tile_type_homogeneous_connection_left_and_right_upper_left
			, auto_tile_type_homogeneous_connection_left_and_right_upper_right
			, auto_tile_type_homogeneous_connection_left_and_right_lower_left
			, auto_tile_type_homogeneous_connection_left_and_right_lower_right
			, auto_tile_type_homogeneous_connection_cross_upper_left
			, auto_tile_type_homogeneous_connection_cross_upper_right
			, auto_tile_type_homogeneous_connection_cross_lower_left
			, auto_tile_type_homogeneous_connection_cross_lower_right
			, auto_tile_type_homogeneous_connection_all_upper_left
			, auto_tile_type_homogeneous_connection_all_upper_right
			, auto_tile_type_homogeneous_connection_all_lower_left
			, auto_tile_type_homogeneous_connection_all_lower_right
			, auto_tile_type_homogeneous_connection_size
		};

		// 今後、別の hpp を作成して管理
		struct AutoTile {
			AutoTileTypeHomogeneousConnection auto_tile_upper_left{ auto_tile_type_homogeneous_connection_nothing_upper_left };
			AutoTileTypeHomogeneousConnection auto_tile_upper_right{ auto_tile_type_homogeneous_connection_nothing_upper_right };
			AutoTileTypeHomogeneousConnection auto_tile_lower_left{ auto_tile_type_homogeneous_connection_nothing_lower_left };
			AutoTileTypeHomogeneousConnection auto_tile_lower_right{ auto_tile_type_homogeneous_connection_nothing_lower_right };
		};

	}
}

#endif //Included Crafterra Library