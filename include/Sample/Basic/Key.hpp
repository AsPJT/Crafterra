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
		::As::UniquePtrMatrix<MapChip>& field_map_matrix, // フィールドマップ
		::As::UniquePtrMatrix<DrawMapChip>& draw_map_matrix, // 描画用フィールドマップ
		PerlinNoiseOnFieldMap& terrain_noise, // 地形生成
		TerrainChunk& chunk // 地形チャンク管理
	) {

		key.setKey();
		if (key.isPressed(::As::Key::key_a) || key.isPressed(::As::Key::key_left)) {
			cs.camera_size.moveX(-player.getWalkingSpeed());
			player.setDirection(::Crafterra::Enum::ActorDirection::left);
		}
		if (key.isPressed(::As::Key::key_d) || key.isPressed(::As::Key::key_right)) {
			cs.camera_size.moveX(player.getWalkingSpeed());
			player.setDirection(::Crafterra::Enum::ActorDirection::right);
		}
		if (key.isPressed(::As::Key::key_w) || key.isPressed(::As::Key::key_up)) {
			cs.camera_size.moveY(-player.getWalkingSpeed());
			player.setDirection(::Crafterra::Enum::ActorDirection::up);
		}
		if (key.isPressed(::As::Key::key_s) || key.isPressed(::As::Key::key_down)) {
			cs.camera_size.moveY(player.getWalkingSpeed());
			player.setDirection(::Crafterra::Enum::ActorDirection::down);
		}
		if (key.isDown(::As::Key::key_g)) {
			terrain.initialGeneration(field_map_matrix, terrain_noise, chunk.getX(), chunk.getY());
			terrain.setTerrain(field_map_matrix, draw_map_matrix);
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
			player.setWalkingSpeed(0.2f);
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