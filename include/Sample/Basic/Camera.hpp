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

#ifndef INCLUDED_SAMPLE_SAMPLE_BASIC_CAMERA_HPP
#define INCLUDED_SAMPLE_SAMPLE_BASIC_CAMERA_HPP

// Crafterra 
#include <Crafterra/Crafterra.hpp>

// 各描画ライブラリをまとめたもの
#include <AsLib2/ThirdParty/Framework/Framework.hpp>



#include <memory>
#include <new>
#include <sstream>

namespace Crafterra {

	// 描画関数
	void updateCamera(
		CoordinateSystem& cs // 座標系管理クラス
		, const ::As::UniquePtrMatrix<DrawMapChip>& draw_map_matrix // フィールドマップ
		, TerrainObjectImage& terrain_obj_image
		, ::Crafterra::Resource& resource_
		, const int cd_anime_sea
		, const ::Crafterra::Enum::ActorMode mode
		, const bool is_debug_log
	) {
		// 透明か
		::std::unique_ptr<bool[]> is_alpha(new(::std::nothrow) bool[draw_map_layer_max]);
		if (!is_alpha) return;
		// 描画するかしないか
		::std::unique_ptr<bool[]> is_draw(new(::std::nothrow) bool[draw_map_layer_max]);
		if (!is_draw) return;


		// 描画関数
		cs.updateCamera(
			[&](const float csx_, const float csy_, const float cw_, const float ch_, const ::As::IndexUint x_, const ::As::IndexUint y_) {
				bool is_floor = false;
				const ::As::Rect map_chip_rect(int(csx_ + 0.5f), int(csy_ + 0.5f), int(csx_ + cw_ + 0.5f) - int(csx_ + 0.5f), int(csy_ + ch_ + 0.5f) - int(csy_ + 0.5f));
				
				::As::MapChipImage& tile = resource_.getMapChip();

				::std::stringstream ss;
				
				::As::IndexUint start_layer = 0;
				::As::IndexUint end_layer = 0;
				// 透明度を計算
				for (::As::IndexUint layer = 0; layer < draw_map_layer_max; ++layer) {
					const DrawMapChipUnit& draw_map = draw_map_matrix[y_][x_].cgetTile(layer);

					if (draw_map.getTerrainObject() == TerrainObject::empty) {
						is_alpha[layer] = true; // 透明
						is_draw[layer] = false; // 描画しない
						if (layer == start_layer) ++start_layer; // からはスキップ
						continue;
					}
					// 描画する
					end_layer = layer + 1;
					is_alpha[layer] = false; // 不透明
					is_draw[layer] = true; // 描画する

					if (layer == 0) continue;
					const DrawMapChipUnit& draw_map_before = draw_map_matrix[y_][x_].cgetTile(layer - 1);

					// 崖の場合
					if (draw_map.getTerrainObject() == TerrainObject::cliff) {
						// マップチップが不透明だったら 1 つ前のタイルを描画しない
						if (!tile.getMapChipAlpha("Cliff", As::IndexUint(draw_map.getCliff()))) start_layer = layer;
						// 1 つ前のマップチップに同じものがあったら 1 つ前のタイルを描画しない
						if (draw_map_before.getCliff() == draw_map.getCliff()) is_draw[layer - 1] = false;
					}
					else if (draw_map.getTerrainObject() == TerrainObject::sea) {
						// マップチップが不透明だったら 1 つ前のタイルを描画しない
						const AutoTile& at = draw_map.getAutoTile();
						if (at.auto_tile_upper_left == TerrainTileConnectionWoditorAutoTile::all_upper_left
							&& at.auto_tile_upper_right == TerrainTileConnectionWoditorAutoTile::all_upper_right
							&& at.auto_tile_lower_left == TerrainTileConnectionWoditorAutoTile::all_lower_left
							&& at.auto_tile_lower_right == TerrainTileConnectionWoditorAutoTile::all_lower_right
							) {
							start_layer = layer;
						}
					}
				}
				if (end_layer == 0) return;
				const DrawMapChipUnit& draw_map_end = draw_map_matrix[y_][x_].cgetTile(end_layer - 1);
				const ::As::Int32 y_elevation = ::As::Int32(draw_map_end.getElevation());
				ss << 'Y' << y_elevation << '\n';
                ss << '(' << x_ << ',' << y_ << ')' << '\n';
                ss << ::As::IndexUint(draw_map_end.getTerrainObject()) << '\n';
				bool is_elevation = true;

				// 処理
				for (::As::IndexUint layer = start_layer; layer < end_layer; ++layer) {
					// 描画しないものは処理しない
					if (!is_draw[layer]) continue;
					const DrawMapChipUnit& draw_map = draw_map_matrix[y_][x_].cgetTile(layer);

					//if (layer < start_layer) continue;

					//if (layer != 0) ss << '\n';

					//ss << 'L' << layer << '|';
					//ss << 'X' << x_ << '|';
					//ss << 'Y' << draw_map.getElevation() << '|';
					//ss << 'Z' << y_ << '|';
					//ss << 'B' << ::As::IndexUint(draw_map.getTerrainObject()) << '|';

					// 描画するバイオーム
					bool is_draw_biome = (draw_map.getDrawBiome() != TerrainBiome::empty
						&& draw_map.getDrawBiome() != TerrainBiome::sea
						&& draw_map.getDrawBiome() != TerrainBiome::lake
						&& draw_map.getDrawBiome() != TerrainBiome::normal
						&& draw_map.getDrawBiome() != TerrainBiome::hill
						);

					// ------------------------------------------------------------------------------------------------------------------------------------

					const TerrainObject tobj = draw_map.getTerrainObject();
					const ::As::IndexUint tobji = ::As::IndexUint(tobj);
					const ::As::IndexUint ngi = ::As::IndexUint(TerrainObject::normal_ground);
					switch (tobj) {
					case TerrainObject::cliff:
					{
						if (!is_floor && !tile.getMapChipAlpha("Cliff", As::IndexUint(draw_map.getCliff()))) {
							(terrain_obj_image.terrain_image[ngi]).draw(map_chip_rect); // 通常地面
							is_floor = true;
						}
						::As::Image(tile.getMapChip("Cliff", As::IndexUint(draw_map.getCliff()))).draw(map_chip_rect);
					}
						break;
					case TerrainObject::cliff_top:
					{
						bool is_biome_auto_tile_alpha = true;
						if (is_draw_biome) {
							const AutoTile& at = draw_map.getBiomeAutoTile();
							is_biome_auto_tile_alpha = !(at.auto_tile_upper_left == TerrainTileConnectionWoditorAutoTile::all_upper_left
								&& at.auto_tile_upper_right == TerrainTileConnectionWoditorAutoTile::all_upper_right
								&& at.auto_tile_lower_left == TerrainTileConnectionWoditorAutoTile::all_lower_left
								&& at.auto_tile_lower_right == TerrainTileConnectionWoditorAutoTile::all_lower_right
								);

							if (is_biome_auto_tile_alpha) {
								if (!is_floor && !tile.getMapChipAlpha("Cliff", As::IndexUint(draw_map.getCliffTop()))) {
									(terrain_obj_image.terrain_image[ngi]).draw(map_chip_rect); // 通常地面
									is_floor = true;
								}
							}

							// 森バイオームの場合は森用の崖にする
							if (draw_map.getIsBiomeCliffTop()) {
								if (draw_map.getDrawBiome() == TerrainBiome::forest) {
									::As::Image(tile.getMapChip("Cliff2", As::IndexUint(draw_map.getCliffTop()))).draw(map_chip_rect);
									break;
								}
								else if (draw_map.getDrawBiome() == TerrainBiome::tundra) {
									::As::Image(tile.getMapChip("Cliff3", As::IndexUint(draw_map.getCliffTop()))).draw(map_chip_rect);
									break;
								}
							}
						}

						if (is_biome_auto_tile_alpha) {
							if (!is_floor && !tile.getMapChipAlpha("Cliff", As::IndexUint(draw_map.getCliffTop()))) {
								(terrain_obj_image.terrain_image[ngi]).draw(map_chip_rect); // 通常地面
								is_floor = true;
							}
							::As::Image(tile.getMapChip("Cliff", As::IndexUint(draw_map.getCliffTop()))).draw(map_chip_rect);
						}

						if (!is_draw_biome) break;
						const ::std::string& biome_string = MapChipTypeBiomeString[As::IndexUint(draw_map.getDrawBiome())];
						AutoTileIndex auto_tile_index(draw_map.getBiomeAutoTile(), 0, 2);
						::As::ImageQuadrant(
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_upper_left),
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_upper_right),
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_lower_left),
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
					}
						break;
					case TerrainObject::sea:
					{
						AutoTileIndex sea_auto_tile_index(draw_map.getBiomeAutoTile(), cd_anime_sea, 8);

						if (!is_floor
							//&& tile.getMapChip(sea_auto_tile_index)
							) {
							(terrain_obj_image.terrain_image[ngi]).draw(map_chip_rect); // 通常地面
							is_floor = true;
						}
						::As::ImageQuadrant(
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_upper_left),
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_upper_right),
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_lower_left),
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
					}
						break;
					case TerrainObject::water_ground_2:
					{
						AutoTileIndex auto_tile_index(draw_map.getAutoTile(), cd_anime_sea, 8);
						::As::ImageQuadrant(
							tile.getMapChip("Lake", auto_tile_index.auto_tile_upper_left),
							tile.getMapChip("Lake", auto_tile_index.auto_tile_upper_right),
							tile.getMapChip("Lake", auto_tile_index.auto_tile_lower_left),
							tile.getMapChip("Lake", auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
					}
						break;
					default:
						(terrain_obj_image.terrain_image[tobji]).draw(map_chip_rect); // 通常のマップチップを描画する
						break;
					}
					
				}

				// 人間の場合はデバッグ表示
				if (is_debug_log && mode == ::Crafterra::Enum::ActorMode::humanoid) {
					::As::DrawRect(map_chip_rect,
						((!is_elevation) ? ::As::Color(255, 255, 255) :
						((y_elevation % 3 == 0)?::As::Color(150, 0, 0):
							((y_elevation % 3 == 1) ? ::As::Color(0, 150, 0) :
								::As::Color(0, 0, 150))))
					).drawLine();
					resource_.getFont().draw(int(map_chip_rect.start_x), int(map_chip_rect.start_y), ss.str());
				}

			}
		);
	}

}

#endif //Included Sample