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
#include <Crafterra/Enum/ActorMoveType.hpp>
#include <AsLib2/DataType/Matrix.hpp>

namespace Crafterra {

	// アクタ ( プレイヤー、動物、人間、動くもの全般 )
	class Actor {
		// アクタの向き
		::Crafterra::Enum::ActorDirection direction{ ::Crafterra::Enum::ActorDirection::down };

		using Pos_ = float;
        using ObjectMapMat = ::As::UniquePtrMatrix4D<TerrainObject>;
        using MoveType = ::Crafterra::Enum::ActorMoveType;

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
        
        // 移動処理 ----------
        
        void moveRight(CoordinateSystem& cs_, ObjectMapMat& terrain_object_matrix_) {
            move(cs_, terrain_object_matrix_, this->walking_speed, 0.0f);
        }
        
        void moveLeft(CoordinateSystem& cs_, ObjectMapMat& terrain_object_matrix_) {
            move(cs_, terrain_object_matrix_, -this->walking_speed, 0.0f);
        }
        
        void moveUp(CoordinateSystem& cs_, ObjectMapMat& terrain_object_matrix_) {
            move(cs_, terrain_object_matrix_, 0.0f, -this->walking_speed);
        }
        
        void moveDown(CoordinateSystem& cs_, ObjectMapMat& terrain_object_matrix_) {
            move(cs_, terrain_object_matrix_, 0.0f, this->walking_speed);
        }
        
        void move(CoordinateSystem& cs_, ObjectMapMat& terrain_object_matrix, float speed_x_, float speed_z_) {
            Pos_ next_pos_x = this->x + speed_x_;
            Pos_ next_pos_z = this->z + speed_z_;
            // プレイヤ移動
            if (this->actor_mode == ActorMode::humanoid) {
                moveHumanoid(cs_, terrain_object_matrix, next_pos_x, next_pos_z);
                return;
            }
            this->x = next_pos_x;
            this->z = next_pos_z;
            drawActor(cs_);
        }

		// 様式 ----------
		ActorMode getMode() const { return this->actor_mode; }
		void setMode(const ActorMode actor_mode_) { this->actor_mode = actor_mode_; }
        
        // プレイヤの処理 =============
        
        // あたり判定処理 ----------
        ActorMoveType humanoidMoveType(ObjectMapMat& terrain_object_matrix_, Pos_ pos_x_, Pos_ pos_z_) {
            // フィールドマップ座標系
            ::As::IndexUint fx = As::IndexUint(pos_x_);
            ::As::IndexUint fy = As::IndexUint(this->y);
            ::As::IndexUint fz = As::IndexUint(pos_z_) + fy;
            
            // 崖上 or 海判定
            for (int l = 0; l <= 2; ++l) {
                // 歩き判定
                TerrainObject obj = terrain_object_matrix_.getValueZXYL(fz, fx, fy, l);
                if (obj == TerrainObject::cliff_top || obj == TerrainObject::sea) {
                    return MoveType::walk;
                }
                // 崖下り判定(cliffなし)
                TerrainObject objBellow = terrain_object_matrix_.getValueZXYL(fz - 1, fx, fy - 1, l);
                if (objBellow == TerrainObject::cliff_top) {
                    return MoveType::climb_down;
                }
                // 崖下り判定(cliffあり)
                if (obj == TerrainObject::empty && objBellow == TerrainObject::cliff) {
                    return MoveType::climb_down_cliff;
                }
            }
            return MoveType::stay;
        }
        
        // プレイヤの移動処理 ----------
        void moveHumanoid(CoordinateSystem& cs_, ObjectMapMat& terrain_object_matrix_, Pos_ pos_x, Pos_ pos_z) {
            // 移動タイプの取得
            ActorMoveType moveType = humanoidMoveType(terrain_object_matrix_, pos_x, pos_z);
            // 移動なし
            switch(moveType) {
                case ActorMoveType::stay:
                    return;
                case ActorMoveType::walk:
                    this->x = pos_x;
                    this->z = pos_z;
                    drawActor(cs_);
                    return;
                // 崖下り(cliffなし)
                case ActorMoveType::climb_down:
                    this->x = pos_x;
                    this->z = pos_z;
                    this->y--;
                    drawActor(cs_);
                    return;
                // 崖下り(cliffあり)
                case ActorMoveType::climb_down_cliff:
                    climbDownCliffHumanoid(cs_);
                    return;
                default:
                    return;
            }
        }
        
        // プレイヤー崖下り(cliffあり)
        void climbDownCliffHumanoid(CoordinateSystem& cs_) {
            float speed = this->walking_speed;
            float fall_speed = speed + 1.0f;
            // 高さ更新
            this->y--;
            switch(this->direction) {
                // X方向
                case ::Crafterra::Enum::ActorDirection::right:
                    cs_.camera_size.moveX(speed);
                    cs_.camera_size.moveY(fall_speed);
                    this->x += speed;
                    this->z += fall_speed;
                    return;
                case ::Crafterra::Enum::ActorDirection::left:
                    cs_.camera_size.moveX(-speed);
                    cs_.camera_size.moveY(fall_speed);
                    this->x -= speed;
                    this->z += fall_speed;
                    return;
                // Z方向
                case ::Crafterra::Enum::ActorDirection::down:
                    cs_.camera_size.moveY(fall_speed);
                    this->z += fall_speed;
                    return;
                default:
                    return;
            }
        }
        
        // プレイヤーの描画処理 ----------
        void drawActor(CoordinateSystem& cs_) {
            switch(this->direction) {
                case ::Crafterra::Enum::ActorDirection::right:
                    cs_.camera_size.moveX(this->walking_speed);
                    return;
                case ::Crafterra::Enum::ActorDirection::left:
                    cs_.camera_size.moveX(-this->walking_speed);
                    return;
                case ::Crafterra::Enum::ActorDirection::up:
                    cs_.camera_size.moveY(-this->walking_speed);
                    return;
                case ::Crafterra::Enum::ActorDirection::down:
                    cs_.camera_size.moveY(this->walking_speed);
                    return;
                default:
                    return;
            }
        }

	};

}

#endif //Included Crafterra Library
