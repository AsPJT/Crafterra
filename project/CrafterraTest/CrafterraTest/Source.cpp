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

#include <DxLib.h>

// Crafterra 
#include <Crafterra/Crafterra.hpp>

#include <memory>

#include <chrono>

namespace Crafterra {

	// アクタ ( プレイヤー、動物、人間、動くもの全般 )
	class Actor {
		// アクタの向き
		::Crafterra::Enum::ActorDirection direction{ ::Crafterra::Enum::ActorDirection::down };

		using Pos_ = float;

		// 座標 ( フィールドマップ座標系 )
		Pos_ x{}, y{}, z{};

		// 大きさ
		Pos_ width{ 0.9f }, height{ 0.9f }, depth{ 0.9f };

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

		// 大きさ ----------

		Pos_ getWidth() const { return this->width; }
		Pos_ getHeight() const { return this->height; }
		Pos_ getDepth() const { return this->depth; }
		void setWidth(const Pos_ width_) { this->width = width_; }
		void setHeight(const Pos_ height_) { this->height = height_; }
		void setDepth(const Pos_ depth_) { this->depth = depth_; }
	};

	namespace System {
		void crafterraMain(::Crafterra::Resource& resource_) {

			int cd_anime = 0; // アニメーション
			int cd_anime_sea = 0; // アニメーション

			int time_count = 0;
			const int time_count_max = 5;

			resource_.getMusic().playLoop();

			::std::random_device seed_gen;
			::std::mt19937 engine(seed_gen());
			const Uint32 temperature_seed = engine();
			const Uint32 amount_of_rainfall_seed = engine();
			const Uint32 elevation_seed = engine();

			CoordinateSystem cs(resource_.getWindowWidth(), resource_.getWindowHeight());

			using FieldMapMatrix = ::Crafterra::DataType::Matrix<MapChip, init_field_map_width, init_field_map_height>; // 世界
			using FieldMapMatrixPtr = ::std::unique_ptr<FieldMapMatrix>; // 世界

			FieldMapMatrixPtr field_map_matrix_ptr(CRAFTERRA_NEW FieldMapMatrix); // フィールドマップのポインタ
			if (!field_map_matrix_ptr) return; // メモリ確保できなかった時は return

			FieldMapMatrix& field_map_matrix = (*field_map_matrix_ptr); // フィールドマップ



			const Uint32 chunk_min_x = 0;
			const Uint32 chunk_min_y = 0;
			const Uint32 chunk_max_x = 100000000;
			const Uint32 chunk_max_y = 100000000;
			const Uint32 init_chunk_x = (chunk_max_x - chunk_min_x) / 2;
			const Uint32 init_chunk_y = (chunk_max_y - chunk_min_y) / 2;


			Uint32 chunk_x = init_chunk_x;
			Uint32 chunk_y = init_chunk_y;

			// 地形
			Terrain terrain(temperature_seed, amount_of_rainfall_seed, elevation_seed);
			terrain.initialGeneration(field_map_matrix, chunk_x, chunk_y);

			// プレイヤーの位置
			Actor player{};
			player.setX(cs.camera_size.getCenterX());
			player.setY(float(field_map_matrix[IndexUint(cs.camera_size.getCenterY() + 0.5f)][IndexUint(cs.camera_size.getCenterX() + 0.5f)].getElevation3()));
			player.setZ(cs.camera_size.getCenterY() - player.getY());

			::AsLib2::InputKey key;

			OperationActorStateInFieldMap operation_actor_state_in_field = OperationActorStateInFieldMap::airship;
			cs.setMapChipSize(10.f);
			//OperationActorStateInFieldMap operation_actor_state_in_field = ::Crafterra::Enum::operation_actor_state_in_field_map_walking;
			//cs.setMapChipSize(64.f);

			ElapsedTime elapsed_time;

			::AsLib2::DrawRect log_background(::AsLib2::Rect(0, 0, 200, 180), ::AsLib2::Color(40));


			while (::Crafterra::System::Update()) {
				elapsed_time.update();
				const Int64 elapsed = elapsed_time.getMicroseconds();
#ifdef __DXLIB
				//::DxLib::clsDx();
				//::DxLib::printfDx("%d micro sec/f\n", int(elapsed));
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
#ifndef __APPLE__
				// キー関連
				{
					key.setKey();
					{
						if (key.isPressed(::AsLib2::Key::key_a) || key.isPressed(::AsLib2::Key::key_left)) {
							//// プレイヤーのあたり判定テスト
							//if (operation_actor_state_in_field == ::Crafterra::Enum::OperationActorStateInFieldMap::walking) {
							//	const auto left_map = field_map_matrix[IndexUint(player.getZ() + 0.5f)][IndexUint(player.getX() + 0.5f - key_displacement - player.getWidth() / 2)];
							//	if (left_map.getBlock(IndexUint(player.getY())) != Block::cliff) {
							//		player.setX(player.getX() - key_displacement);
							//		player.setY(float(left_map.getBlockElevation()));
							//		cs.camera_size.moveX(-key_displacement);
							//	}
							//}
							//else 
								cs.camera_size.moveX(-key_displacement);
							player.setDirection(::Crafterra::Enum::ActorDirection::left);
						}
						if (key.isPressed(::AsLib2::Key::key_d) || key.isPressed(::AsLib2::Key::key_right)) {
							cs.camera_size.moveX(key_displacement);
							player.setDirection(::Crafterra::Enum::ActorDirection::right);
						}
						if (key.isPressed(::AsLib2::Key::key_w) || key.isPressed(::AsLib2::Key::key_up)) {
							cs.camera_size.moveY(-key_displacement);
							player.setDirection(::Crafterra::Enum::ActorDirection::up);
						}
						if (key.isPressed(::AsLib2::Key::key_s) || key.isPressed(::AsLib2::Key::key_down)) {
							cs.camera_size.moveY(key_displacement);
							player.setDirection(::Crafterra::Enum::ActorDirection::down);
						}
						if (key.isDown(::AsLib2::Key::key_g)) {
							terrain.initialGeneration(field_map_matrix);
						}
						if (key.isPressed(::AsLib2::Key::key_j)) {
							cs.expandMapChipSize(0.995f); // 画面縮小
						}
						if (key.isPressed(::AsLib2::Key::key_k)) {
							cs.expandMapChipSize(1.005f); // 画面拡大
						}
						if (key.isDown(::AsLib2::Key::key_1)) {
							cs.setMapChipSize(10.f);
							operation_actor_state_in_field = ::Crafterra::Enum::OperationActorStateInFieldMap::airship;
						}
						if (key.isDown(::AsLib2::Key::key_2)) {
							cs.setMapChipSize(64.f);
							operation_actor_state_in_field = ::Crafterra::Enum::OperationActorStateInFieldMap::walking;
						}
					}
				}
#endif // !__APPLE__
				// 無限生成処理
				{
					// 右側に生成
					if (cs.camera_size.getCenterX() > float(cs.field_map_size.getCenterX() + (cs.field_map_size.getWidthHalf() * 2 / 3))) {
						cs.camera_size.moveX(-float(cs.field_map_size.getWidthHalf()));
						if (chunk_x >= chunk_max_x - 1) chunk_x = chunk_min_x;
						else ++chunk_x;
						terrain.moveLeftTerrain(field_map_matrix, init_field_map_width / 2);
						terrain.generation(field_map_matrix, chunk_x + 1, chunk_y, init_field_map_width / 2, 0, init_field_map_width, init_field_map_height);
					}
					// 左側に生成
					else if (cs.camera_size.getCenterX() < float(cs.field_map_size.getCenterX() - (cs.field_map_size.getWidthHalf() * 2 / 3))) {
						cs.camera_size.moveX(+float(cs.field_map_size.getWidthHalf()));
						if (chunk_x <= chunk_min_x) chunk_x = chunk_max_x - 1;
						else --chunk_x;
						terrain.moveRightTerrain(field_map_matrix, init_field_map_width / 2);
						terrain.generation(field_map_matrix, chunk_x, chunk_y, 0, 0, init_field_map_width / 2, init_field_map_height);
					}
					// 上側に生成
					if (cs.camera_size.getCenterY() > float(cs.field_map_size.getCenterY() + (cs.field_map_size.getHeightHalf() * 2 / 3))) {
						cs.camera_size.moveY(-float(cs.field_map_size.getHeightHalf()));
						if (chunk_y >= chunk_max_y - 1) chunk_y = chunk_min_y;
						else ++chunk_y;
						terrain.moveUpTerrain(field_map_matrix, init_field_map_height / 2);
						terrain.generation(field_map_matrix, chunk_x, chunk_y + 1, 0, init_field_map_height / 2, init_field_map_width, init_field_map_height);
					}
					// 下側に生成
					else if (cs.camera_size.getCenterY() < float(cs.field_map_size.getCenterY() - (cs.field_map_size.getHeightHalf() * 2 / 3))) {
						cs.camera_size.moveY(+float(cs.field_map_size.getHeightHalf()));
						if (chunk_y <= chunk_min_y) chunk_y = chunk_max_y - 1;
						else --chunk_y;
						terrain.moveDownTerrain(field_map_matrix, init_field_map_height / 2);
						terrain.generation(field_map_matrix, chunk_x, chunk_y, 0, 0, init_field_map_width, init_field_map_height / 2);
					}
				}

				{
					// 描画関数
					cs.updateCamera(
						[&field_map_matrix, &resource_, &cd_anime_sea](const float csx_, const float csy_, const float cw_, const float ch_, const ::Crafterra::DataType::IndexUint x_, const ::Crafterra::DataType::IndexUint y_) {

							const MapChip& field_map = field_map_matrix[y_][x_];

							const int start_x = int(csx_ + 0.5f);
							const int start_y = int(csy_ + 0.5f);
							const int center_x = int(csx_ + cw_ / 2.f + 0.5f);
							const int center_y = int(csy_ + ch_ / 2.f + 0.5f);
							const int end_x = int(csx_ + cw_ + 0.5f);
							const int end_y = int(csy_ + ch_ + 0.5f);

							const ::AsLib2::Rect map_chip_rect(int(csx_ + 0.5f), int(csy_ + 0.5f), int(csx_ + cw_ + 0.5f) - int(csx_ + 0.5f), int(csy_ + ch_ + 0.5f) - int(csy_ + 0.5f));

							bool is_map_chip_type_homogeneous_connection_all = false;
							bool is_auto_tile_desert_alpha = false;

							if (field_map.getDrawBiome() == MapChipTypeBiome::desert) {
								AutoTileIndex auto_tile_index(field_map.getAutoTile(), 0, 2);
								if (resource_.getMapChip().getIsSeaAlpha(auto_tile_index)) is_auto_tile_desert_alpha = true;
							}
							else {
								is_auto_tile_desert_alpha = true;
							}

							// 崖を先に描画
							//if (field_map.getIsCliff()) {
							if (field_map.getDrawBlock() == Block::cliff) {
								if (resource_.getMapChip().getMapChipCliffTopAlpha(IndexUint(field_map.getCliff())) == 0) {
									::AsLib2::Image(resource_.getMapChip().getMapChip(0)).draw(map_chip_rect);
								}
								::AsLib2::Image(resource_.getMapChip().getMapChipCliffTop(IndexUint(field_map.getCliff()))).draw(map_chip_rect);
							}
							// 海を描画
							//else if (field_map.getDrawBiome() == MapChipTypeBiome::sea) {
								//else if (field_map.getDrawBlock() == Block::water_ground) {
							else if (field_map.getDrawBlock() == Block::water_ground) {
								AutoTileIndex auto_tile_index(field_map.getAutoTile(), cd_anime_sea, 8);

								if (resource_.getMapChip().getIsSeaAlpha(auto_tile_index)) {
									::AsLib2::Image(resource_.getMapChip().getMapChip(0)).draw(map_chip_rect);
								}
								::AsLib2::ImageQuadrant(
									resource_.getMapChip().getSea(auto_tile_index.auto_tile_upper_left),
									resource_.getMapChip().getSea(auto_tile_index.auto_tile_upper_right),
									resource_.getMapChip().getSea(auto_tile_index.auto_tile_lower_left),
									resource_.getMapChip().getSea(auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
							}
							// 崖上を描画
							else if (field_map.getCliffTop() != CliffConnection::size) {
								if (is_auto_tile_desert_alpha) {
									is_map_chip_type_homogeneous_connection_all = true;
									if (resource_.getMapChip().getMapChipCliffTopAlpha(IndexUint(field_map.getCliffTop())) == 0) {
										::AsLib2::Image(resource_.getMapChip().getMapChip(0)).draw(map_chip_rect);
									}

									::AsLib2::Image(resource_.getMapChip().getMapChipCliffTop(IndexUint(field_map.getCliffTop()))).draw(map_chip_rect);
								}
							}

							// ------------------------------------------------------------------------------------------------------------------------------------
							if (field_map.getIsCliff()) return;
							if (field_map.getDrawBiome() == MapChipTypeBiome::desert) {

								AutoTileIndex auto_tile_index(field_map.getAutoTile(), 0, 2);

								::AsLib2::ImageQuadrant(
									resource_.getMapChip().getDesert(auto_tile_index.auto_tile_upper_left),
									resource_.getMapChip().getDesert(auto_tile_index.auto_tile_upper_right),
									resource_.getMapChip().getDesert(auto_tile_index.auto_tile_lower_left),
									resource_.getMapChip().getDesert(auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
							}
							::AsLib2::Image(resource_.getMapChip().getMapChip(field_map.getDrawChip())).draw(map_chip_rect);
							//else
							//	::DxLib::DrawBox(start_x, start_y, end_x, end_y, field_map.getColor(), TRUE);

							switch (field_map.getDrawBlock()) {
							case Block::grass_1:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 0)).draw(map_chip_rect);
								break;
							case Block::grass_2:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 1)).draw(map_chip_rect);
								break;
							case Block::grass_3:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 2)).draw(map_chip_rect);
								break;
							case Block::grass_4:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 3)).draw(map_chip_rect);
								break;
							case Block::flower_1:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 4)).draw(map_chip_rect);
								break;
							case Block::flower_2:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 5)).draw(map_chip_rect);
								break;
							case Block::flower_3:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 6)).draw(map_chip_rect);
								break;
							case Block::flower_4:
								::AsLib2::Image(resource_.getMapChip().getMapChip(8 * 6 + 7)).draw(map_chip_rect);
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
				// カメラの中心を描画
				//::DxLib::DrawCircle(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2, cs.map_chip_size.getWidthHalf(), 0x00111111, TRUE);

				//----------------------------------------------------------------------------------------------------
				// フィールドマップにおける操作アクタの状態
				switch (operation_actor_state_in_field) {

					//----------------------------------------------------------------------------------------------------
					// 🚶 人間 ( 陸を歩行する者 ) 🚶 
				case ::Crafterra::Enum::OperationActorStateInFieldMap::walking:
#ifdef __DXLIB
					::DxLib::DrawRotaGraph(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2,
						cs.map_chip_size.getWidthHalf() / 16, 0.0,
						resource_.getCharacterChip().getCharacterChip(1, dir), TRUE, FALSE);
#endif // __DXLIB
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

					// 飛空艇を描画
					::DxLib::DrawRotaGraph(cs.window_size.getWidth() / 2, cs.window_size.getHeight() / 2,
						cs.map_chip_size.getWidthHalf() * 2 / 3, 0.0,
						resource_.getCharacterChip().getCharacterChip(0, dir), TRUE, FALSE);
#endif // __DXLIB
					break;

				default:
					break;
				}
				//----------------------------------------------------------------------------------------------------

				// 座標を文字として出力
				//DrawFormatStringToHandle(10, 50, GetColor(255, 255, 255), resource_.getFont().getFont(),
				//DrawBox(0, 0, 200, 180, AsLib2::Color(40).getColor(), TRUE);
				//log_background.draw();
#ifdef __DXLIB
				//::DxLib::printfDx(
				//	//#if (__cplusplus >= 202002L)
				//	//					u8"カメラ中央X: %.2f\nカメラ中央Y: %.2f\nカメラ開始X: %.2f\nカメラ終了Y: %.2f\n1:飛空艇視点\n2:人間視点\nJ:カメラを遠ざける\nK:カメラを近づける\nバイオーム: %s\n%d"
				//	//#else
				//	u8"カメラ中央X: %.2f\nカメラ中央Y: %.2f\nカメラ開始X: %.2f\nカメラ終了Y: %.2f\n1:飛空艇視点\n2:人間視点\nJ:カメラを遠ざける\nK:カメラを近づける\nバイオーム: \n%d\nX:%f Y:%f Z:%f"
				//	//#endif
				//	, cs.camera_size.getCenterX(), cs.camera_size.getCenterY()
				//	, cs.camera_size.getStartX(), cs.camera_size.getStartY()
				//	//, MapChipTypeBiomeString[IndexUint(field_map_matrix[IndexUint(cs.camera_size.getCenterY())][IndexUint(cs.camera_size.getCenterX())].getDrawBiome())].c_str()
				//	//, int(getAutoTileIndex(field_map_matrix[100][100].getAutoTile().auto_tile_lower_left, 0, 1))
				//	, resource_.getMapChip().getDesert(getAutoTileIndex(field_map_matrix[100][100].getAutoTile().auto_tile_lower_left, 0, 0))
				//	,player.getX(),player.getY(),player.getZ()
				//	//, field_map_matrix[100][100].getCliffTop()
				//);
#endif // __DXLIB
			}

		}

	}
}
