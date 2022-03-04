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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_ACTOR_MOVE_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_ACTOR_MOVE_TYPE_HPP

/*#######################################################################################
	日本語リファレンス (Reference-ja)
	https://github.com/AsPJT/Crafterra/wiki/仕様：アクタの移動タイプ
#######################################################################################*/

#include <AsLib2/DataType/PrimitiveDataType.hpp>

#ifndef CRAFTERRA_ACTOR_MOVE_TYPE_T
#define CRAFTERRA_ACTOR_MOVE_TYPE_T ::As::Uint8
#endif // CRAFTERRA_ACTOR_MOVE_TYPE_T

namespace Crafterra {
    inline namespace DataType { using ActorMoveTypeUint = CRAFTERRA_ACTOR_MOVE_TYPE_T; }
    inline namespace Enum {

        // アクタの移動タイプ
        enum class ActorMoveType : ::Crafterra::DataType::ActorMoveTypeUint {
            stay,               // 移動なし
            walk,               // 歩く(高さの移動なし)
            climb_up,           // 登る(高さ+1)
            climb_down,         // 下る(高さ-1)
            climb_down_cliff,   // 崖を下る(高さ-1)
            size,
        };

    }
    inline namespace Value {
        // アクタの移動タイプの大きさ
        constexpr ::Crafterra::DataType::ActorMoveTypeUint actor_move_type_size = static_cast<::Crafterra::DataType::ActorMoveTypeUint>(::Crafterra::Enum::ActorMoveType::size);
    }
}

#endif //Included Crafterra Library