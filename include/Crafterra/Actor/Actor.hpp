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
#include <AsLib2/DataType/Matrix.hpp>

namespace Crafterra {

	// アクタ ( プレイヤー、動物、人間、動くもの全般 )
	class Actor {
		// アクタの向き
		::Crafterra::Enum::ActorDirection direction{ ::Crafterra::Enum::ActorDirection::down };

		using Pos_ = float;
        using ObjectMapMat = ::As::UniquePtrMatrix4D<TerrainObject>;

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
        
        // あたり判定処理 ----------
        bool playerCanMove(ObjectMapMat& terrain_object_matrix, Pos_ nextPosX_, Pos_ nextPosZ_) {
            // フィールドマップ座標系
            ::As::IndexUint fx = As::IndexUint(nextPosX_);
            ::As::IndexUint fy = As::IndexUint(this->y);
            ::As::IndexUint fz = As::IndexUint(nextPosZ_) + fy;
            // 崖上 or 海判定
            for (int l = 0; l <= 2; ++l) {
                TerrainObject obj = terrain_object_matrix.getValueZXYL(fz, fx, fy, l);
                if (obj == TerrainObject::cliff_top || obj == TerrainObject::sea) {
                    return true;
                }
                else if (obj == TerrainObject::empty) {
                    
                }
            }
            return false;
        }

		// 速度 ----------
		float getWalkingSpeed() const { return this->walking_speed; }
		void setWalkingSpeed(const float walking_speed_) { this->walking_speed = walking_speed_; }
        
        // 移動処理 ----------
        bool movePlayer(ObjectMapMat& terrain_object_matrix, float speed_x_, float speed_z_) {
            Pos_ next_pos_x = this->x + speed_x_;
            Pos_ next_pos_z = this->z + speed_z_;
            // プレイヤ移動
            if (this->actor_mode == ActorMode::humanoid) {
                // 当たり判定
                if (!playerCanMove(terrain_object_matrix, next_pos_x, next_pos_z)) {
                    return false;
                }
            }
            this->x = next_pos_x;
            this->z = next_pos_z;
            return true;
        }
        
        // ジャンプ処理 ----------
        void jump(ObjectMapMat& terrain_object_matrix) {
            
        

		// 様式 ----------
		ActorMode getMode() const { return this->actor_mode; }
		void setMode(const ActorMode actor_mode_) { this->actor_mode = actor_mode_; }

	};

}

#endif //Included Crafterra Library
