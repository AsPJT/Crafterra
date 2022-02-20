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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_ACTOR_DIRECTION_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_ACTOR_DIRECTION_HPP

/*#######################################################################################
	日本語リファレンス (Reference-ja)
	https://github.com/AsPJT/Crafterra/wiki/仕様：アクタの向き
#######################################################################################*/

#include <AsLib2/DataType/PrimitiveDataType.hpp>

#ifndef CRAFTERRA_ACTOR_DIRECTION_T
#define CRAFTERRA_ACTOR_DIRECTION_T ::As::Uint8
#endif // CRAFTERRA_ACTOR_DIRECTION_T

namespace Crafterra {
	inline namespace DataType { using ActorDirectionUint = CRAFTERRA_ACTOR_DIRECTION_T; }
	inline namespace Enum {

		// アクタの向き
		enum class ActorDirection : ::Crafterra::DataType::ActorDirectionUint {
			  empty		// 無し
			, down			// 下
			, left			// 左
			, right			// 右
			, up			// 上
			, lower_left	// 左下
			, lower_right	// 右下
			, upper_left	// 左上
			, upper_right	// 右上
			, size
		};

	}
	inline namespace Value {
		// アクタの向きの大きさ
		constexpr ::Crafterra::DataType::ActorDirectionUint actor_direction_size = static_cast<::Crafterra::DataType::ActorDirectionUint>(::Crafterra::Enum::ActorDirection::size);
	}
}

#endif //Included Crafterra Library