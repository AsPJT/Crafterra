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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ACTOR_ACTOR_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ACTOR_ACTOR_HPP

#include <Crafterra/Enum/ActorDirection.hpp>

namespace Crafterra {

	// アクタ ( プレイヤー、動物、人間、動くもの全般 )
	class Actor {
		// アクタの向き
		::Crafterra::Enum::ActorDirection direction{ ::Crafterra::Enum::ActorDirection::down };

		using Pos_ = float;

		// 座標 ( フィールドマップ座標系 )
		Pos_ x{}, y{}, z{};

		// 見た目の大きさ
		Pos_ apparent_width{ 0.9f }, apparent_height{ 0.9f }, apparent_depth{ 0.9f };

		// あたり判定の大きさ
		Pos_ hit_width{ 0.9f }, hit_height{ 0.9f }, hit_depth{ 0.9f };

		// 歩行速度
		float walking_speed = 0.2f;

		// アクタの様式
		ActorMode actor_mode = ActorMode::humanoid;

	public:
		::Crafterra::Enum::ActorDirection getDirection() const { return this->direction; }
		void setDirection(const ::Crafterra::Enum::ActorDirection& direction_) { this->direction = direction_; }

		// 座標 ( フィールドマップ座標系 )  ----------

		Pos_ getX() const { return this->x; }
		Pos_ getY() const { return this->y; }
		Pos_ getZ() const { return this->z; }
		void setX(const Pos_ x_) { this->x = x_; }
		void setY(const Pos_ y_) { this->y = y_; }
		void setZ(const Pos_ z_) { this->z = z_; }

		// 見た目の大きさ ----------

		Pos_ getApparentWidth() const { return this->apparent_width; }
		Pos_ getApparentHeight() const { return this->apparent_height; }
		Pos_ getApparentDepth() const { return this->apparent_depth; }
		void setApparentWidth(const Pos_ width_) { this->apparent_width = width_; }
		void setApparentHeight(const Pos_ height_) { this->apparent_height = height_; }
		void setApparentDepth(const Pos_ depth_) { this->apparent_depth = depth_; }

		// あたり判定の大きさ ----------

		Pos_ getHitWidth() const { return this->hit_width; }
		Pos_ getHitHeight() const { return this->hit_height; }
		Pos_ getHitDepth() const { return this->hit_depth; }
		void setHitWidth(const Pos_ width_) { this->hit_width = width_; }
		void setHitHeight(const Pos_ height_) { this->hit_height = height_; }
		void setHitDepth(const Pos_ depth_) { this->hit_depth = depth_; }

		// 速度 ----------
		float getWalkingSpeed() const { return this->walking_speed; }
		void setWalkingSpeed(const float walking_speed_) { this->walking_speed = walking_speed_; }

		// 様式 ----------
		ActorMode getMode() const { return this->actor_mode; }
		void setMode(const ActorMode actor_mode_) { this->actor_mode = actor_mode_; }

	};

}

#endif //Included Crafterra Library