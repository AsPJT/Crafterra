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
//#define CRAFTERRA_USE_SAVE_SCREEN
#ifndef INCLUDED_SAMPLE_SAMPLE_SAMPLE_1_HPP
#define INCLUDED_SAMPLE_SAMPLE_SAMPLE_1_HPP

// Crafterra 
#include <Crafterra/Crafterra.hpp>

// 各描画ライブラリをまとめたもの
#include <AsLib2/ThirdParty/Framework/Framework.hpp>

#include <Sample/Basic/Key.hpp>
#include <Sample/Basic/Terrain.hpp>
#include <Sample/Basic/Camera.hpp>

namespace Crafterra {

	// Crafterra を再生
	void playCrafterra(::Crafterra::Resource& resource_) {

		// カウンタ
		int cd_anime = 0; // アニメーション
		int cd_anime_sea = 0; // アニメーション

		int time_count = 0;
		const int time_count_max = 5;

		// 曲を再生
		resource_.getMusic().playLoop();

		// ここから地形に関するもの ------------------------------

		// SEED 生成
		::std::random_device	 seed_gen;					 // 乱数生成器に使用する SEED を作成
		::std::mt19937		 engine(seed_gen());		 // 乱数生成器
		TerrainPerlinNoiseSeed	 terrain_seed(seed_gen);	 // 地形生成に使用する SEED を作成

		using FieldTerrainObj		 = ::As::UniquePtrMatrix4D<TerrainObject>;
		using FieldTerrainInfo		 = ::As::UniquePtrMatrix<TerrainInformation>;
		using FieldDrawMap		 = ::As::UniquePtrMatrix<DrawMapChip>;

		const ::As::IndexAreaXZ	 terrain_chunk_area(0, 0, 100000000);		 // 地形チャンクの範囲

		FieldTerrainObj		 terrain_obj_matrix(default_field_map);			 // 地形オブジェクト ( 4 次元配列 )
		FieldTerrainInfo		 terrain_info_matrix(default_field_map);			 // 地形情報 ( 2 次元配列 )
		FieldDrawMap			 draw_map_matrix(default_field_map);			 // 描画マップ ( 2 次元配列 )
		TerrainChunk			 terrain_chunk(terrain_chunk_area);				 // 地形チャンク
		TerrainPerlinNoise		 terrain_noise(terrain_seed);						 // 地形のノイズ生成
		TerrainObjectImage	 terrain_obj_image(resource_.getMapChip());		 // 地形オブジェクトの画像 ( 後に tsv 読み込みにする  )
		Terrain					 terrain;

		terrain.initialGeneration(terrain_obj_matrix, terrain_info_matrix, terrain_noise, terrain_chunk);	 // 初回の地形生成
		terrain.setDrawMapFromTerrain(terrain_obj_matrix, terrain_info_matrix, draw_map_matrix);		 // 地形から描画マップを作成
		terrain.setDrawAutoTileConnection(draw_map_matrix);												 // 描画マップのオートタイルの接続を計算する
		terrain.setDrawRange(draw_map_matrix);																 // 描画マップの描画範囲を作成

		// 座標系
		CoordinateSystem cs(resource_.getWindowWidth(), resource_.getWindowHeight(), terrain_info_matrix.getWidth(), terrain_info_matrix.getDepth());

		// プレイヤ
		Actor player{};
		player.setX(cs.camera_size.getCenterX());
		player.setY(float(draw_map_matrix[::As::IndexUint(cs.camera_size.getCenterY() + 0.5f)][::As::IndexUint(cs.camera_size.getCenterX() + 0.5f)].getTile(draw_map_layer_max - 1).getElevation()));
		player.setZ(cs.camera_size.getCenterY());
		player.setWalkingSpeed(0.2f);
		player.setMode(ActorMode::humanoid);

		// キー入力
		::As::InputKey key;

		// 操作アクタの初期設定
		cs.setMapChipSize(32.f);

		// 経過時間 ----------
		ElapsedTime elapsed_time;

		// ログ関連 ----------
		::As::DrawRect log_background(::As::Rect(0, 0, 250, 400), ::As::Color(40));
		
#if defined(CRAFTERRA_USE_SAVE_SCREEN)
		bool is_debug_log = false;
#else
		bool is_debug_log = true;
#endif // CRAFTERRA_USE_SAVE_SCREEN

		// メインループ ----------
#if !defined(CRAFTERRA_USE_SAVE_SCREEN)
		while (::Crafterra::System::update())
#endif // CRAFTERRA_USE_SAVE_SCREEN
		{
			elapsed_time.update();
			const ::As::Int64 elapsed = elapsed_time.getMicroseconds();

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

#if defined(SIV3D_INCLUDED)
::s3d::ClearPrint();
#endif

			// キー関連
			::Crafterra::updateKey(key, cs, player, terrain, is_debug_log, terrain_obj_matrix, terrain_info_matrix, draw_map_matrix, terrain_noise, terrain_chunk, resource_);

			// 無限生成処理
			::Crafterra::updateTerrain(cs, terrain_chunk, terrain, terrain_obj_matrix, terrain_info_matrix, draw_map_matrix, terrain_noise);

			// 描画関数
			::Crafterra::updateCamera(cs, draw_map_matrix, terrain_obj_image, resource_, cd_anime_sea, player.getMode(), is_debug_log);
			
			// 飛空艇のアニメーションを計算
			int dir = 0;
			const int cd_anime2 = ((cd_anime == 3) ? 1 : cd_anime);
			switch (player.getDirection()) {
			case ::Crafterra::Enum::ActorDirection::down:dir = 0 + cd_anime2; break;
			case ::Crafterra::Enum::ActorDirection::left: dir = 3 + cd_anime2; break;
			case ::Crafterra::Enum::ActorDirection::right:dir = 6 + cd_anime2; break;
			case ::Crafterra::Enum::ActorDirection::up:   dir = 9 + cd_anime2; break;
			}

#if defined(CRAFTERRA_USE_SAVE_SCREEN)
// なし
#else

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

			if (is_debug_log) {
				log_background.draw();
#ifdef __DXLIB
				::DxLib::clsDx();
				::DxLib::printfDx("%d micro sec/f\n", int(elapsed));
				::DxLib::printfDx(
					//#if (__cplusplus >= 202002L)
					//					u8"カメラ中央X: %.2f\nカメラ中央Y: %.2f\nカメラ開始X: %.2f\nカメラ終了Y: %.2f\n1:飛空艇視点\n2:人間視点\nJ:カメラを遠ざける\nK:カメラを近づける\nバイオーム: %s\n%d"
					//#else
					//u8"カメラ中央X: %.2f\nカメラ中央Y: %.2f\nカメラ開始X: %.2f\nカメラ終了Y: %.2f\n1:飛空艇視点\n2:人間視点\nJ:カメラを遠ざける\nK:カメラを近づける\nバイオーム: \n%d\nX:%f Y:%f Z:%f"
					"Camera CenterX: %.2f\nCamera CenterY: %.2f\nCamera StartX: %.2f\nCamera StartY: %.2f\n1:Airship View\n2:Human View\nJ:camera\nK:camera\nbiome:%s \n%d\nX:%.2f Y:%.2f Z:%.2f"
					//#endif
					, cs.camera_size.getCenterX(), cs.camera_size.getCenterY()
					, cs.camera_size.getStartX(), cs.camera_size.getStartY()
					, MapChipTypeBiomeString[As::IndexUint(draw_map_matrix[As::IndexUint(cs.camera_size.getCenterY())][As::IndexUint(cs.camera_size.getCenterX())].getTile(draw_map_layer_max - 1).getDrawBiome())].c_str()
					//, int(getAutoTileIndex(terrain_info_matrix[100][100].getAutoTile().auto_tile_lower_left, 0, 1))
					, resource_.getMapChip().getMapChip("Desert", getAutoTileIndex(draw_map_matrix[100][100].getTile(draw_map_layer_max - 1).getAutoTile().auto_tile_lower_left, 0, 0))
					, player.getX(), player.getY(), player.getZ()
					//, terrain_info_matrix[100][100].getCliffTop()
				);

#elif defined(SIV3D_INCLUDED)
			::s3d::ClearPrint();
			::s3d::Print
				<< int(elapsed) << U" micro sec/f\n"
				<< U"Camera CenterX: " << cs.camera_size.getCenterX()
				<< U"\nCamera CenterY: " << cs.camera_size.getCenterY()
				<< U"\nCamera StartX: " << cs.camera_size.getStartX()
				<< U"\nCamera StartY: " << cs.camera_size.getStartY()
				<< U"\n1:Airship View\n2:Human View\nJ:camera\nK:camera\nP:Debug Log" //  \n%d\nX:%.2f Y:%.2f Z:%.2f
				<< U"\nbiome:" 
				<< ::As::utf32(MapChipTypeBiomeString[As::IndexUint(draw_map_matrix[As::IndexUint(cs.camera_size.getCenterY())][As::IndexUint(cs.camera_size.getCenterX())].getTile(draw_map_layer_max - 1).getDrawBiome())])
				//<< resource_.getMapChip().getMapChip("Desert", getAutoTileIndex(draw_map_matrix[100][100].getTile(draw_map_layer_max - 1).getAutoTile().auto_tile_lower_left, 0, 0))
				<< U"\nPlayer dx: " << player.getX()
				<< U"\nPlayer dy: " << player.getY()
				<< U"\nPlayer dz: " << player.getZ();
#endif // __DXLIB
						}

#endif // CRAFTERRA_USE_SAVE_SCREEN

		} // メインループ
	}

}

#endif //Included Sample
