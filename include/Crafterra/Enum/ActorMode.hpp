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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_ACTOR_MODE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_ACTOR_MODE_HPP

/*#######################################################################################
	日本語リファレンス (Reference-ja)
	https://github.com/AsPJT/Crafterra/wiki/仕様：アクタの形態
#######################################################################################*/

#include <AsLib2/DataType/PrimitiveDataType.hpp>

#ifndef CRAFTERRA_ACTOR_MODE_T
#define CRAFTERRA_ACTOR_MODE_T ::As::Uint8
#endif // CRAFTERRA_ACTOR_MODE_T

namespace Crafterra {
	inline namespace DataType { using ActorModeUint = CRAFTERRA_ACTOR_MODE_T; }
	inline namespace Enum {

		// アクタの形態
		enum class ActorMode : ::Crafterra::DataType::ActorModeUint {
			  empty
			, humanoid     // 陸路の歩行
			, ratite_bird // 飛べない鳥 ( 地上の高速移動 )
			, ship        // 船
			, airship     // 飛空艇
			, size
		};

	}
}

#endif //Included Crafterra Library