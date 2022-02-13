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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_CLIFF_CONNECTION_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_CLIFF_CONNECTION_HPP

#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

namespace Crafterra {
	inline namespace Enum {

		// 同じ性質のブロックとの接続タイプ ( 通常 + 崖 )
		enum class TerrainTileConnectionCliff : TerrainTileConnectionCliffUint {
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

	}
}

#endif //Included Crafterra Library