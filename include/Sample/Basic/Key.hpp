/*##########################################################################################

	Crafterra Sample Source Code 🌏

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

#ifndef INCLUDED_SAMPLE_SAMPLE_BASIC_KEY_HPP
#define INCLUDED_SAMPLE_SAMPLE_BASIC_KEY_HPP

// Crafterra 
#include <Crafterra/Crafterra.hpp>

// 各描画ライブラリをまとめたもの
#include <AsLib2/ThirdParty/Framework/Framework.hpp>

namespace Crafterra {

	void updateKey(
		::As::InputKey& key, // キーボードクラス
		CoordinateSystem& cs, // 座標系管理クラス
		Actor& player, // アクタクラス
		const Terrain& terrain, // 地形整理クラス
		bool& is_debug_log, // デバッグログの表示をするかしないか
		::As::UniquePtrMatrix4D<TerrainObject>& terrain_object_matrix, // フィールドマップ
		::As::UniquePtrMatrix<TerrainInformation>& terrain_information_matrix, // フィールドマップ
		::As::UniquePtrMatrix<DrawMapChip>& draw_map_matrix, // 描画用フィールドマップ
		TerrainPerlinNoise& terrain_noise, // 地形生成
		TerrainChunk& chunk, // 地形チャンク管理
        ::Crafterra::Resource& resource_
	) {

        // 移動
		key.setKey();
        
		if (key.isPressed(::As::Key::key_a) || key.isPressed(::As::Key::key_left)) {
            player.setDirection(::Crafterra::Enum::ActorDirection::left);
            player.moveLeft(cs, terrain_object_matrix);
		}
		if (key.isPressed(::As::Key::key_d) || key.isPressed(::As::Key::key_right)) {
            player.setDirection(::Crafterra::Enum::ActorDirection::right);
            player.moveRight(cs, terrain_object_matrix);
		}
		if (key.isPressed(::As::Key::key_w) || key.isPressed(::As::Key::key_up)) {
            player.setDirection(::Crafterra::Enum::ActorDirection::up);
            player.moveUp(cs, terrain_object_matrix);
		}
		if (key.isPressed(::As::Key::key_s) || key.isPressed(::As::Key::key_down)) {
            player.setDirection(::Crafterra::Enum::ActorDirection::down);
            player.moveDown(cs, terrain_object_matrix);
		}
        // ジャンプ
//        if (key.isPressed(::As::Key::key_s) || key.isPressed(::As::Key::key_down)) {
//            float move_speed = player.getWalkingSpeed();
//            if (player.movePlayer(terrain_object_matrix, 0.0f, move_speed)) {
//                cs.camera_size.moveY(move_speed);
//            }
//            player.setDirection(::Crafterra::Enum::ActorDirection::down);
//        }
		if (key.isDown(::As::Key::key_g)) {
			terrain.initialGeneration(terrain_object_matrix, terrain_information_matrix, terrain_noise, chunk);
			terrain.setDrawMapFromTerrain(terrain_object_matrix, terrain_information_matrix, draw_map_matrix);
			terrain.setDrawAutoTileConnection(draw_map_matrix);
			terrain.setDrawRange(draw_map_matrix);
		}
		if (key.isPressed(::As::Key::key_j)) {
			cs.expandMapChipSize(0.995f); // 画面縮小
		}
		if (key.isPressed(::As::Key::key_k)) {
			cs.expandMapChipSize(1.005f); // 画面拡大
		}
		if (key.isDown(::As::Key::key_1)) {
			cs.setMapChipSize(10.f);
			player.setMode(::Crafterra::Enum::ActorMode::airship);
			player.setWalkingSpeed(2.f);
		}
		if (key.isDown(::As::Key::key_2)) {
			cs.setMapChipSize(64.f);
			player.setMode(::Crafterra::Enum::ActorMode::humanoid);
            // 高さ情報をセット(暫定実装)
            player.setY(float(draw_map_matrix[::As::IndexUint(cs.camera_size.getCenterY() + 0.5f)][::As::IndexUint(cs.camera_size.getCenterX() + 0.5f)].getTile(draw_map_layer_max - 1).getElevation()));
			player.setWalkingSpeed(0.2f);
		}
        // 音量調整
        if (key.isDown(::As::Key::key_8)) {
            // ボリュームダウン
            resource_.getMusic().volumeDown();
        }
        if (key.isDown(::As::Key::key_9)) {
            // ボリュームアップ
            resource_.getMusic().volumeUp();
        }
        if (key.isDown(::As::Key::key_0)) {
            // ボリュームアップ
            resource_.getMusic().mute();
        }
		if (key.isDown(::As::Key::key_p)) {
			is_debug_log = (!is_debug_log);
#ifdef __DXLIB
			::DxLib::clsDx();
#endif // __DXLIB
		}
	}
}

#endif //Included Sample
