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

#ifndef INCLUDED_SAMPLE_SAMPLE_SAMPLE_1_HPP
#define INCLUDED_SAMPLE_SAMPLE_SAMPLE_1_HPP

// Crafterra 
#include <Crafterra/Crafterra.hpp>

// 各描画ライブラリをまとめたもの
#include <AsLib2/ThirdParty/Framework/Framework.hpp>

#include <memory>
#include <chrono>

#include <Sample/Basic/Key.hpp>
#include <Sample/Basic/Terrain.hpp>
#include <Sample/Basic/Camera.hpp>

namespace Crafterra {

	// Crafterra を再生
	void playCrafterra(::Crafterra::Resource& resource_) {

		// カウンタ ----------
		int cd_anime = 0; // アニメーション
		int cd_anime_sea = 0; // アニメーション

		int time_count = 0;
		const int time_count_max = 5;

		// 曲を再生 ----------
		resource_.getMusic().playLoop();

		// SEED 生成 ----------
		::std::random_device seed_gen;
		::std::mt19937 engine(seed_gen()); // 乱数生成器
		const ::As::Uint32 temperature_seed = engine();
		const ::As::Uint32 amount_of_rainfall_seed = engine();
		const ::As::Uint32 elevation_seed = engine();
		const ::As::Uint32 flower_seed = engine();
		const ::As::Uint32 lake_seed = engine();

		// 座標系 ----------
		CoordinateSystem cs(resource_.getWindowWidth(), resource_.getWindowHeight());

		// フィールドマップ ----------
		using FieldMapMatrix = ::As::Matrix<MapChip, init_field_map_width, init_field_map_height>; // 世界
		using FieldMapMatrixPtr = ::std::unique_ptr<FieldMapMatrix>; // 世界

		FieldMapMatrixPtr field_map_matrix_ptr(CRAFTERRA_NEW FieldMapMatrix); // フィールドマップのポインタ
		if (!field_map_matrix_ptr) return; // メモリ確保できなかった時は return

		FieldMapMatrix& field_map_matrix = (*field_map_matrix_ptr); // フィールドマップ

		// 地形生成 ----------
		TerrainChunk chunk(0, 0, 100000000, 100000000); // チャンクの範囲を指定
		TerrainNoise terrain_noise(temperature_seed, amount_of_rainfall_seed, elevation_seed, flower_seed, lake_seed);
		Terrain terrain;
		terrain.initialGeneration(field_map_matrix, terrain_noise, chunk.getX(), chunk.getY());
		terrain.setTerrain(field_map_matrix);

		// プレイヤーの位置 ----------
		Actor player{};
		player.setX(cs.camera_size.getCenterX());
		player.setY(float(field_map_matrix[As::IndexUint(cs.camera_size.getCenterY() + 0.5f)][As::IndexUint(cs.camera_size.getCenterX() + 0.5f)].getElevation3()));
		player.setZ(cs.camera_size.getCenterY() - player.getY());
		player.setWalkingSpeed(2.f);
		player.setMode(ActorMode::airship);

		// キー入力
		::As::InputKey key;

		// 操作アクタの初期設定
		cs.setMapChipSize(10.f);

		// 経過時間 ----------
		ElapsedTime elapsed_time;

		// ログ関連 ----------
		::As::DrawRect log_background(::As::Rect(0, 0, 250, 220), ::As::Color(40));
		bool is_debug_log = true;

		// メインループ ----------
		while (::Crafterra::System::update()) {
			elapsed_time.update();
			const ::As::Int64 elapsed = elapsed_time.getMicroseconds();
#ifdef __DXLIB
			if (is_debug_log) {
				::DxLib::clsDx();
				::DxLib::printfDx("%d micro sec/f\n", int(elapsed));
			}
#endif // __DXLIB

			++time_count;
			if (time_count >= time_count_max) {
				time_count = 0;

				++cd_anime;
				if (cd_anime == 4) {
					cd_anime = 0;
				}
				++cd_anime_sea;
				if (cd_anime_sea == 8) {
					cd_anime_sea = 0;
				}
			}

			// キー関連
			::Crafterra::updateKey(key, cs, player, terrain, is_debug_log, field_map_matrix, terrain_noise, chunk);

			// 無限生成処理
			::Crafterra::updateTerrain(cs, chunk, terrain, field_map_matrix, terrain_noise);

			// 描画関数
			::Crafterra::updateCamera(cs, field_map_matrix, resource_, cd_anime_sea);
			
			// 飛空艇のアニメーションを計算
			int dir = 0;
			const int cd_anime2 = ((cd_anime == 3) ? 1 : cd_anime);
			switch (player.getDirection()) {
			case ::Crafterra::Enum::ActorDirection::down:dir = 0 + cd_anime2; break;
			case ::Crafterra::Enum::ActorDirection::left: dir = 3 + cd_anime2; break;
			case ::Crafterra::Enum::ActorDirection::right:dir = 6 + cd_anime2; break;
			case ::Crafterra::Enum::ActorDirection::up:   dir = 9 + cd_anime2; break;
			}

			//----------------------------------------------------------------------------------------------------
			// フィールドマップにおける操作アクタの状態
			switch (player.getMode()) {

				//----------------------------------------------------------------------------------------------------
				// 🚶 人間 ( 陸を歩行する者 ) 🚶 
			case ::Crafterra::Enum::ActorMode::humanoid:
				::As::Image(resource_.getCharacterChip().getMapChip("Human", dir)).draw(::As::Rect(
					::As::RectDataType(cs.window_size.getWidth() / 2 - cs.map_chip_size.getWidth() / 2),
					::As::RectDataType(cs.window_size.getHeight() / 2 - cs.map_chip_size.getHeight() / 2),
					::As::RectDataType(cs.map_chip_size.getWidth()),
					::As::RectDataType(cs.map_chip_size.getHeight())
				));
				break;

				//----------------------------------------------------------------------------------------------------
				// 🚢 船 ( 海上に浮かんでいる者 ) 🚢 
			case ::Crafterra::Enum::ActorMode::ship:
				break;

				//----------------------------------------------------------------------------------------------------
				// 🛸 飛空艇 ( 空を飛んでいる者 ) 🛸 
			case ::Crafterra::Enum::ActorMode::airship:
				// 飛空艇の影を描画
#ifdef __DXLIB
				::DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				::DxLib::DrawOval(int(cs.window_size.getWidth() / 2), int(cs.window_size.getHeight() / 2 + cs.map_chip_size.getHeight() * 16),
					int(cs.map_chip_size.getWidthHalf() * 6), int(cs.map_chip_size.getHeightHalf() * 3), 0x00111111, TRUE);
				::DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif // __DXLIB

				// 飛空艇を描画
				::As::Image(resource_.getCharacterChip().getMapChip("Airship", dir)).draw(::As::Rect(
					::As::RectDataType(cs.window_size.getWidth() / 2 - cs.map_chip_size.getWidth() * 8 / 2),
					::As::RectDataType(cs.window_size.getHeight() / 2 - cs.map_chip_size.getHeight() * 8 / 2),
					::As::RectDataType(cs.map_chip_size.getWidth() * 8),
					::As::RectDataType(cs.map_chip_size.getHeight() * 8)
				));
				break;

			default:
				break;
			}
			//----------------------------------------------------------------------------------------------------

#ifdef __DXLIB
			if (is_debug_log) {
				log_background.draw();
				::DxLib::printfDx(
					//#if (__cplusplus >= 202002L)
					//					u8"カメラ中央X: %.2f\nカメラ中央Y: %.2f\nカメラ開始X: %.2f\nカメラ終了Y: %.2f\n1:飛空艇視点\n2:人間視点\nJ:カメラを遠ざける\nK:カメラを近づける\nバイオーム: %s\n%d"
					//#else
					//u8"カメラ中央X: %.2f\nカメラ中央Y: %.2f\nカメラ開始X: %.2f\nカメラ終了Y: %.2f\n1:飛空艇視点\n2:人間視点\nJ:カメラを遠ざける\nK:カメラを近づける\nバイオーム: \n%d\nX:%f Y:%f Z:%f"
					"Camera CenterX: %.2f\nCamera CenterY: %.2f\nCamera StartX: %.2f\nCamera StartY: %.2f\n1:Airship View\n2:Human View\nJ:camera\nK:camera\nbiome:%s \n%d\nX:%.2f Y:%.2f Z:%.2f"
					//#endif
					, cs.camera_size.getCenterX(), cs.camera_size.getCenterY()
					, cs.camera_size.getStartX(), cs.camera_size.getStartY()
					, MapChipTypeBiomeString[As::IndexUint(field_map_matrix[As::IndexUint(cs.camera_size.getCenterY())][As::IndexUint(cs.camera_size.getCenterX())].getDrawBiome())].c_str()
					//, int(getAutoTileIndex(field_map_matrix[100][100].getAutoTile().auto_tile_lower_left, 0, 1))
					, resource_.getMapChip().getMapChip("Desert", getAutoTileIndex(field_map_matrix[100][100].getAutoTile().auto_tile_lower_left, 0, 0))
					, player.getX(), player.getY(), player.getZ()
					//, field_map_matrix[100][100].getCliffTop()
				);
			}
#endif // __DXLIB

		} // メインループ

	}

}

#endif //Included Sample