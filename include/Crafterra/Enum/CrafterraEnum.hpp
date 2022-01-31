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

		// フィールドマップにおける操作アクタの状態
		enum class ActorMode : ::Crafterra::DataType::ActorModeUint {
			  empty
			, humanoid     // 陸路の歩行
			, ratite_bird // 飛べない鳥 ( 地上の高速移動 )
			, ship        // 船
			, airship     // 飛空艇
			, size
		};


		// 同じ性質のブロックとの接続タイプ ( 通常 + 崖 )
		enum class CliffConnection : CliffConnectionUint {
			nothing
			, all
			, up_down
			, left_right
			, up
			, left
			, right
			, down
			, up_left_0
			, up_right_0
			, left_down_0
			, right_down_0
			, up_left_1
			, up_right_1
			, left_down_1
			, right_down_1
			, up_left_right_0
			, up_left_down_0
			, up_right_down_0
			, left_right_down_0
			, up_left_right_1
			, up_left_down_1
			, up_right_down_1
			, left_right_down_1
			, up_left_right_2
			, up_left_down_2
			, up_right_down_2
			, left_right_down_2
			, up_left_right_3
			, up_left_down_3
			, up_right_down_3
			, left_right_down_3
			, right_down_cliff
			, left_right_down_cliff
			, left_down_cliff
			, down_cliff
			, right_up_cliff
			, left_right_up_cliff
			, left_up_cliff
			, up_cliff
			, size
		};


		// ( オートタイル ) 同じ性質のブロックとの接続タイプ ( 通常 + 崖 )
		enum class AutoTileConnection : AutoTileConnectionUint {
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
			AutoTileConnection auto_tile_upper_left{ AutoTileConnection::nothing_upper_left };
			AutoTileConnection auto_tile_upper_right{ AutoTileConnection::nothing_upper_right };
			AutoTileConnection auto_tile_lower_left{ AutoTileConnection::nothing_lower_left };
			AutoTileConnection auto_tile_lower_right{ AutoTileConnection::nothing_lower_right };
		};

	}
}

#endif //Included Crafterra Library