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

namespace Crafterra {

	// Crafterra を再生
	void playCrafterra(::Crafterra::Resource& resource_) {

		int cd_anime = 0; // アニメーション
		int cd_anime_sea = 0; // アニメーション

		int time_count = 0;
		const int time_count_max = 5;

		resource_.getMusic().playLoop(); // 曲を再生

		::std::random_device seed_gen;
		::std::mt19937 engine(seed_gen()); // 乱数生成器
		const ::As::Uint32 temperature_seed = engine();
		const ::As::Uint32 amount_of_rainfall_seed = engine();
		const ::As::Uint32 elevation_seed = engine();

		CoordinateSystem cs(resource_.getWindowWidth(), resource_.getWindowHeight());

		using FieldMapMatrix = ::As::Matrix<MapChip, init_field_map_width, init_field_map_height>; // 世界
		using FieldMapMatrixPtr = ::std::unique_ptr<FieldMapMatrix>; // 世界

		FieldMapMatrixPtr field_map_matrix_ptr(CRAFTERRA_NEW FieldMapMatrix); // フィールドマップのポインタ
		if (!field_map_matrix_ptr) return; // メモリ確保できなかった時は return

		FieldMapMatrix& field_map_matrix = (*field_map_matrix_ptr); // フィールドマップ

		Chunk chunk(0, 0, 100000000, 100000000); // チャンクの範囲を指定

		// 地形
		Terrain terrain(temperature_seed, amount_of_rainfall_seed, elevation_seed);
		terrain.initialGeneration(field_map_matrix, chunk.getX(), chunk.getY());
		terrain.setTerrain(field_map_matrix);

		// プレイヤーの位置
		Actor player{};
		player.setX(cs.camera_size.getCenterX());
		player.setY(float(field_map_matrix[As::IndexUint(cs.camera_size.getCenterY() + 0.5f)][As::IndexUint(cs.camera_size.getCenterX() + 0.5f)].getElevation3()));
		player.setZ(cs.camera_size.getCenterY() - player.getY());

		::As::InputKey key;

		OperationActorStateInFieldMap operation_actor_state_in_field = OperationActorStateInFieldMap::airship;
		cs.setMapChipSize(10.f);
		//OperationActorStateInFieldMap operation_actor_state_in_field = ::Crafterra::Enum::operation_actor_state_in_field_map_walking;
		//cs.setMapChipSize(64.f);

		ElapsedTime elapsed_time;

		::As::DrawRect log_background(::As::Rect(0, 0, 250, 220), ::As::Color(40));

		bool is_debug_log = true;

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
			float key_displacement = 0.f;
			// フィールドマップにおける操作アクタの状態
			switch (operation_actor_state_in_field) {

				//----------------------------------------------------------------------------------------------------
				// 🚶 人間 ( 陸を歩行する者 ) 🚶 
			case ::Crafterra::Enum::OperationActorStateInFieldMap::walking:
				key_displacement = 0.2f;
				break;

				//----------------------------------------------------------------------------------------------------
				// 🛸 飛空艇 ( 空を飛んでいる者 ) 🛸 
			case ::Crafterra::Enum::OperationActorStateInFieldMap::airship:
				key_displacement = 2.f;
				break;
			}
			//#ifndef __APPLE__
							// キー関連
			{
				key.setKey();
				if (key.isPressed(::As::Key::key_a) || key.isPressed(::As::Key::key_left)) {
					cs.camera_size.moveX(-key_displacement);
					player.setDirection(::Crafterra::Enum::ActorDirection::left);
				}
				if (key.isPressed(::As::Key::key_d) || key.isPressed(::As::Key::key_right)) {
					cs.camera_size.moveX(key_displacement);
					player.setDirection(::Crafterra::Enum::ActorDirection::right);
				}
				if (key.isPressed(::As::Key::key_w) || key.isPressed(::As::Key::key_up)) {
					cs.camera_size.moveY(-key_displacement);
					player.setDirection(::Crafterra::Enum::ActorDirection::up);
				}
				if (key.isPressed(::As::Key::key_s) || key.isPressed(::As::Key::key_down)) {
					cs.camera_size.moveY(key_displacement);
					player.setDirection(::Crafterra::Enum::ActorDirection::down);
				}
				if (key.isDown(::As::Key::key_g)) {
					terrain.initialGeneration(field_map_matrix, chunk.getX(), chunk.getY());
					terrain.setTerrain(field_map_matrix);
				}
				if (key.isPressed(::As::Key::key_j)) {
					cs.expandMapChipSize(0.995f); // 画面縮小
				}
				if (key.isPressed(::As::Key::key_k)) {
					cs.expandMapChipSize(1.005f); // 画面拡大
				}
				if (key.isDown(::As::Key::key_1)) {
					cs.setMapChipSize(10.f);
					operation_actor_state_in_field = ::Crafterra::Enum::OperationActorStateInFieldMap::airship;
				}
				if (key.isDown(::As::Key::key_2)) {
					cs.setMapChipSize(64.f);
					operation_actor_state_in_field = ::Crafterra::Enum::OperationActorStateInFieldMap::walking;
				}
				if (key.isDown(::As::Key::key_p)) {
					is_debug_log = (!is_debug_log);
#ifdef __DXLIB
					::DxLib::clsDx();
#endif // __DXLIB
				}
			}
			//#endif // !__APPLE__
							// 無限生成処理
			{
				// 右側に生成
				if (cs.camera_size.getCenterX() > float(cs.field_map_size.getCenterX() + (cs.field_map_size.getWidthHalf() * 2 / 3))) {
					cs.camera_size.moveX(-float(cs.field_map_size.getWidthHalf()));
					chunk.moveRight();
					terrain.moveLeft(field_map_matrix, init_field_map_width / 2);
					terrain.generation(field_map_matrix, chunk.getX() + 1, chunk.getY(), init_field_map_width / 2, 0, init_field_map_width, init_field_map_height);
					terrain.setTerrain(field_map_matrix);
				}
				// 左側に生成
				else if (cs.camera_size.getCenterX() < float(cs.field_map_size.getCenterX() - (cs.field_map_size.getWidthHalf() * 2 / 3))) {
					cs.camera_size.moveX(+float(cs.field_map_size.getWidthHalf()));
					chunk.moveLeft();
					terrain.moveRight(field_map_matrix, init_field_map_width / 2);
					terrain.generation(field_map_matrix, chunk.getX(), chunk.getY(), 0, 0, init_field_map_width / 2, init_field_map_height);
					terrain.setTerrain(field_map_matrix);
				}
				// 上側に生成
				if (cs.camera_size.getCenterY() > float(cs.field_map_size.getCenterY() + (cs.field_map_size.getHeightHalf() * 2 / 3))) {
					cs.camera_size.moveY(-float(cs.field_map_size.getHeightHalf()));
					chunk.moveUp();
					terrain.moveUp(field_map_matrix, init_field_map_height / 2);
					terrain.generation(field_map_matrix, chunk.getX(), chunk.getY() + 1, 0, init_field_map_height / 2, init_field_map_width, init_field_map_height);
					terrain.setTerrain(field_map_matrix);
				}
				// 下側に生成
				else if (cs.camera_size.getCenterY() < float(cs.field_map_size.getCenterY() - (cs.field_map_size.getHeightHalf() * 2 / 3))) {
					cs.camera_size.moveY(+float(cs.field_map_size.getHeightHalf()));
					chunk.moveDown();
					terrain.moveDown(field_map_matrix, init_field_map_height / 2);
					terrain.generation(field_map_matrix, chunk.getX(), chunk.getY(), 0, 0, init_field_map_width, init_field_map_height / 2);
					terrain.setTerrain(field_map_matrix);
				}
			}

			{
				// 描画関数
				cs.updateCamera(
					[&field_map_matrix, &resource_, &cd_anime_sea](const float csx_, const float csy_, const float cw_, const float ch_, const ::As::IndexUint x_, const ::As::IndexUint y_) {

						const MapChip& field_map = field_map_matrix[y_][x_];

						const int start_x = int(csx_ + 0.5f);
						const int start_y = int(csy_ + 0.5f);
						const int center_x = int(csx_ + cw_ / 2.f + 0.5f);
						const int center_y = int(csy_ + ch_ / 2.f + 0.5f);
						const int end_x = int(csx_ + cw_ + 0.5f);
						const int end_y = int(csy_ + ch_ + 0.5f);

						const ::As::Rect map_chip_rect(int(csx_ + 0.5f), int(csy_ + 0.5f), int(csx_ + cw_ + 0.5f) - int(csx_ + 0.5f), int(csy_ + ch_ + 0.5f) - int(csy_ + 0.5f));

						bool is_map_chip_type_homogeneous_connection_all = false;
						bool is_auto_tile_desert_alpha = false;

						// 描画するバイオーム
						bool is_draw_biome = (field_map.getDrawBiome() != MapChipTypeBiome::empty
							&& field_map.getDrawBiome() != MapChipTypeBiome::sea
							&& field_map.getDrawBiome() != MapChipTypeBiome::lake
							&& field_map.getDrawBiome() != MapChipTypeBiome::normal
							&& field_map.getDrawBiome() != MapChipTypeBiome::hill
							);

						if (is_draw_biome) {
							AutoTileIndex auto_tile_index(field_map.getAutoTile(), 0, 2);
							if (resource_.getMapChip().getIsDesertAlpha(auto_tile_index)) is_auto_tile_desert_alpha = true;
						}
						else is_auto_tile_desert_alpha = true;

						// 崖を先に描画
						if (field_map.getDrawBlock() == Block::cliff) {
							if (resource_.getMapChip().getMapChipCliffTopAlpha(As::IndexUint(field_map.getCliff())) == 0) {
								::As::Image(resource_.getMapChip().getMapChip("Base", 0)).draw(map_chip_rect);
							}
							::As::Image(resource_.getMapChip().getMapChip("Cliff", As::IndexUint(field_map.getCliff()))).draw(map_chip_rect);
						}
						// 海を描画
						else if (field_map.getDrawBlock() == Block::water_ground) {
							AutoTileIndex auto_tile_index(field_map.getAutoTile(), cd_anime_sea, 8);

							if (resource_.getMapChip().getIsSeaAlpha(auto_tile_index)) {
								::As::Image(resource_.getMapChip().getMapChip("Base", 0)).draw(map_chip_rect);
							}
							::As::ImageQuadrant(
								resource_.getMapChip().getMapChip("Sea", auto_tile_index.auto_tile_upper_left),
								resource_.getMapChip().getMapChip("Sea", auto_tile_index.auto_tile_upper_right),
								resource_.getMapChip().getMapChip("Sea", auto_tile_index.auto_tile_lower_left),
								resource_.getMapChip().getMapChip("Sea", auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
						}
						// 崖上を描画
						else if (field_map.getCliffTop() != CliffConnection::size) {
							if (is_auto_tile_desert_alpha) {
								is_map_chip_type_homogeneous_connection_all = true;
								if (resource_.getMapChip().getMapChipCliffTopAlpha(As::IndexUint(field_map.getCliffTop())) == 0) {
									::As::Image(resource_.getMapChip().getMapChip("Base", 0)).draw(map_chip_rect);
								}

								::As::Image(resource_.getMapChip().getMapChip("Cliff", As::IndexUint(field_map.getCliffTop()))).draw(map_chip_rect);
							}
						}

						// ------------------------------------------------------------------------------------------------------------------------------------
						if (field_map.getIsCliff()) return;
						if (is_draw_biome) {
							const ::std::string& biome_string = MapChipTypeBiomeString[As::IndexUint(field_map.getDrawBiome())];
							AutoTileIndex auto_tile_index(field_map.getAutoTile(), 0, 2);
							::As::ImageQuadrant(
								resource_.getMapChip().getMapChip(biome_string, auto_tile_index.auto_tile_upper_left),
								resource_.getMapChip().getMapChip(biome_string, auto_tile_index.auto_tile_upper_right),
								resource_.getMapChip().getMapChip(biome_string, auto_tile_index.auto_tile_lower_left),
								resource_.getMapChip().getMapChip(biome_string, auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
						}

						switch (field_map.getDrawBlock()) {
						case Block::grass_1:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 0)).draw(map_chip_rect);
							break;
						case Block::grass_2:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 1)).draw(map_chip_rect);
							break;
						case Block::grass_3:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 2)).draw(map_chip_rect);
							break;
						case Block::grass_4:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 3)).draw(map_chip_rect);
							break;
						case Block::flower_1:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 4)).draw(map_chip_rect);
							break;
						case Block::flower_2:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 5)).draw(map_chip_rect);
							break;
						case Block::flower_3:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 6)).draw(map_chip_rect);
							break;
						case Block::flower_4:
							::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 6 + 7)).draw(map_chip_rect);
							break;
						}

					}
				);
			}
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
			switch (operation_actor_state_in_field) {

				//----------------------------------------------------------------------------------------------------
				// 🚶 人間 ( 陸を歩行する者 ) 🚶 
			case ::Crafterra::Enum::OperationActorStateInFieldMap::walking:
				::As::Image(resource_.getCharacterChip().getMapChip("Human", dir)).draw(::As::Rect(
					::As::RectDataType(cs.window_size.getWidth() / 2 - cs.map_chip_size.getWidth() / 2),
					::As::RectDataType(cs.window_size.getHeight() / 2 - cs.map_chip_size.getHeight() / 2),
					::As::RectDataType(cs.map_chip_size.getWidth()),
					::As::RectDataType(cs.map_chip_size.getHeight())
				));
				break;

				//----------------------------------------------------------------------------------------------------
				// 🚢 船 ( 海上に浮かんでいる者 ) 🚢 
			case ::Crafterra::Enum::OperationActorStateInFieldMap::ship:
				break;

				//----------------------------------------------------------------------------------------------------
				// 🛸 飛空艇 ( 空を飛んでいる者 ) 🛸 
			case ::Crafterra::Enum::OperationActorStateInFieldMap::airship:
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
		}

	}

}

#endif //Included Sample