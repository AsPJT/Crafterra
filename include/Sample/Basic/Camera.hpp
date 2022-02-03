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

#include <sstream>

namespace Crafterra {

	// 描画関数
	void updateCamera(
		CoordinateSystem& cs // 座標系管理クラス
		, const ::As::UniquePtrMatrix<DrawMapChip>& draw_map_matrix // フィールドマップ
		, ::Crafterra::Resource& resource_
		, const int cd_anime_sea
		, const ::Crafterra::Enum::ActorMode mode
		, const bool is_debug_log
	) {
		// 描画関数
		cs.updateCamera(
			[&](const float csx_, const float csy_, const float cw_, const float ch_, const ::As::IndexUint x_, const ::As::IndexUint y_) {
				bool is_floor = false;
				const ::As::Rect map_chip_rect(int(csx_ + 0.5f), int(csy_ + 0.5f), int(csx_ + cw_ + 0.5f) - int(csx_ + 0.5f), int(csy_ + ch_ + 0.5f) - int(csy_ + 0.5f));
				
				::As::MapChipImage& tile = resource_.getMapChip();

				::std::stringstream ss;
				
				for (::As::IndexUint layer = 0; layer < draw_map_layer_max; ++layer) {

					const DrawMapChipUnit& draw_map = draw_map_matrix[y_][x_].cgetTile(layer);



					if (layer != 0) ss << '\n';
					ss << 'L' << layer << '|';
					ss << 'X' << x_ << '|';
					ss << 'Y' << draw_map.getElevation3() << '|';
					ss << 'Z' << y_ << '|';
					ss << 'B' << ::As::IndexUint(draw_map.getDrawBlock()) << '|';

					bool is_map_chip_type_homogeneous_connection_all = false;
					bool is_auto_tile_desert_alpha = false;

					// 描画するバイオーム
					bool is_draw_biome = (draw_map.getDrawBiome() != MapChipTypeBiome::empty
						&& draw_map.getDrawBiome() != MapChipTypeBiome::sea
						&& draw_map.getDrawBiome() != MapChipTypeBiome::lake
						&& draw_map.getDrawBiome() != MapChipTypeBiome::normal
						&& draw_map.getDrawBiome() != MapChipTypeBiome::hill
						);

					if (is_draw_biome) {
						AutoTileIndex auto_tile_index(draw_map.getBiomeAutoTile(), 0, 2);
						if (tile.getIsDesertAlpha(auto_tile_index)) is_auto_tile_desert_alpha = true;
					}
					else is_auto_tile_desert_alpha = true;

					// 崖を先に描画
					if (draw_map.getDrawBlock() == Block::cliff) {
						if (!is_floor && tile.getMapChipCliffTopAlpha(As::IndexUint(draw_map.getCliff())) == 0) {
							::As::Image(tile.getMapChip("Base", 0)).draw(map_chip_rect);
							is_floor = true;
						}
						::As::Image(tile.getMapChip("Cliff", As::IndexUint(draw_map.getCliff()))).draw(map_chip_rect);
					}
					// 崖上を描画
					else if (draw_map.getIsCliffTop()) {
						if (is_auto_tile_desert_alpha) {
							is_map_chip_type_homogeneous_connection_all = true;
							if (!is_floor && tile.getMapChipCliffTopAlpha(As::IndexUint(draw_map.getCliffTop())) == 0) {
								::As::Image(tile.getMapChip("Base", 0)).draw(map_chip_rect);
								is_floor = true;
							}

							::As::Image(tile.getMapChip("Cliff", As::IndexUint(draw_map.getCliffTop()))).draw(map_chip_rect);
						}
					}

					// ------------------------------------------------------------------------------------------------------------------------------------
					if (draw_map.getIsCliff()) continue;
					//if (draw_map.getDrawBlock() == Block::cliff) return;
					if (is_draw_biome) {
						const ::std::string& biome_string = MapChipTypeBiomeString[As::IndexUint(draw_map.getDrawBiome())];
						AutoTileIndex auto_tile_index(draw_map.getBiomeAutoTile(), 0, 2);
						::As::ImageQuadrant(
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_upper_left),
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_upper_right),
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_lower_left),
							tile.getMapChip(biome_string, auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
					}

					switch (draw_map.getDrawBlock()) {
					case Block::water_ground:
					{
						AutoTileIndex sea_auto_tile_index(draw_map.getBiomeAutoTile(), cd_anime_sea, 8);

						if (!is_floor && tile.getIsSeaAlpha(sea_auto_tile_index)) {
							::As::Image(tile.getMapChip("Base", 0)).draw(map_chip_rect);
							is_floor = true;
						}
						::As::ImageQuadrant(
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_upper_left),
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_upper_right),
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_lower_left),
							tile.getMapChip("Sea", sea_auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
					}
						break;
					case Block::grass_1:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 0)).draw(map_chip_rect);
						break;
					case Block::grass_2:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 1)).draw(map_chip_rect);
						break;
					case Block::grass_3:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 2)).draw(map_chip_rect);
						break;
					case Block::grass_4:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 3)).draw(map_chip_rect);
						break;
					case Block::flower_1:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 4)).draw(map_chip_rect);
						break;
					case Block::flower_2:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 5)).draw(map_chip_rect);
						break;
					case Block::flower_3:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 6)).draw(map_chip_rect);
						break;
					case Block::flower_4:
						::As::Image(tile.getMapChip("Base", 8 * 6 + 7)).draw(map_chip_rect);
						break;
					case Block::house_wall_1_up:
						//::As::Image(tile.getMapChip("Base", 8 * 46 + 7)).draw(map_chip_rect);
						::As::Image(tile.getMapChip("Base", 8 * 115 + 3)).draw(map_chip_rect);
						break;
					case Block::house_wall_1_down:
						//::As::Image(tile.getMapChip("Base", 8 * 47 + 7)).draw(map_chip_rect);
						::As::Image(tile.getMapChip("Base", 8 * 116 + 3)).draw(map_chip_rect);
						break;
					case Block::yellow_green_broadleaf_tree_up:
						::As::Image(tile.getMapChip("Base", 8 * 9 + 0)).draw(map_chip_rect);
						break;
					case Block::yellow_green_broadleaf_tree_down:
						::As::Image(tile.getMapChip("Base", 8 * 10 + 0)).draw(map_chip_rect);
						break;
					case Block::green_broadleaf_tree_up:
						::As::Image(tile.getMapChip("Base", 8 * 9 + 1)).draw(map_chip_rect);
						break;
					case Block::green_broadleaf_tree_down:
						::As::Image(tile.getMapChip("Base", 8 * 10 + 1)).draw(map_chip_rect);
						break;
					case Block::yellow_broadleaf_tree_up:
						::As::Image(tile.getMapChip("Base", 8 * 9 + 2)).draw(map_chip_rect);
						break;
					case Block::yellow_broadleaf_tree_down:
						::As::Image(tile.getMapChip("Base", 8 * 10 + 2)).draw(map_chip_rect);
						break;
					case Block::red_broadleaf_tree_up:
						::As::Image(tile.getMapChip("Base", 8 * 9 + 3)).draw(map_chip_rect);
						break;
					case Block::red_broadleaf_tree_down:
						::As::Image(tile.getMapChip("Base", 8 * 10 + 3)).draw(map_chip_rect);
						break;
					case Block::deciduous_tree_up:
						::As::Image(tile.getMapChip("Base", 8 * 9 + 4)).draw(map_chip_rect);
						break;
					case Block::deciduous_tree_down:
						::As::Image(tile.getMapChip("Base", 8 * 10 + 4)).draw(map_chip_rect);
						break;
					case Block::yellow_green_coniferous_tree_up:
						::As::Image(tile.getMapChip("Base", 8 * 9 + 5)).draw(map_chip_rect);
						break;
					case Block::yellow_green_coniferous_tree_down:
						::As::Image(tile.getMapChip("Base", 8 * 10 + 5)).draw(map_chip_rect);
						break;
					case Block::green_coniferous_tree_up:
						::As::Image(tile.getMapChip("Base", 8 * 9 + 6)).draw(map_chip_rect);
						break;
					case Block::green_coniferous_tree_down:
						::As::Image(tile.getMapChip("Base", 8 * 10 + 6)).draw(map_chip_rect);
						break;
					case Block::cultivated_land:
						::As::Image(tile.getMapChip("Base", 8 * 21 + 3)).draw(map_chip_rect);
						break;
					case Block::planted_carrot:
						::As::Image(tile.getMapChip("Base", 8 * 19 + 6)).draw(map_chip_rect);
						break;
					case Block::water_ground_2:
					{
						AutoTileIndex auto_tile_index(draw_map.getAutoTile(), cd_anime_sea, 8);
						::As::ImageQuadrant(
							tile.getMapChip("Lake", auto_tile_index.auto_tile_upper_left),
							tile.getMapChip("Lake", auto_tile_index.auto_tile_upper_right),
							tile.getMapChip("Lake", auto_tile_index.auto_tile_lower_left),
							tile.getMapChip("Lake", auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
					}
						break;
					}
					
				}

				// 人間の場合はデバッグ表示
				if (is_debug_log && mode == ::Crafterra::Enum::ActorMode::humanoid) {
					::As::DrawRect(map_chip_rect, ::As::Color(255, 255, 255)).drawLine();
					resource_.getFont().draw(map_chip_rect.start_x, map_chip_rect.start_y, ss.str());
				}

			}
		);
	}

}

#endif //Included Sample