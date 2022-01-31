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

namespace Crafterra {

	// 描画関数
	void updateCamera(
		CoordinateSystem& cs // 座標系管理クラス
		, ::As::Matrix<MapChip, init_field_map_width, init_field_map_height>& field_map_matrix // フィールドマップ
		, ::Crafterra::Resource& resource_
		, int cd_anime_sea
	) {
		// 描画関数
		cs.updateCamera(
			[&field_map_matrix, &resource_, &cd_anime_sea](const float csx_, const float csy_, const float cw_, const float ch_, const ::As::IndexUint x_, const ::As::IndexUint y_) {

				const MapChip& field_map = field_map_matrix[y_][x_];

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
					AutoTileIndex auto_tile_index(field_map.getBiomeAutoTile(), 0, 2);
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
					AutoTileIndex auto_tile_index(field_map.getBiomeAutoTile(), cd_anime_sea, 8);

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
					AutoTileIndex auto_tile_index(field_map.getBiomeAutoTile(), 0, 2);
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
				case Block::house_wall_1_up:
					//::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 46 + 7)).draw(map_chip_rect);
					//::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 115 + 3)).draw(map_chip_rect);
					::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 9 + 0)).draw(map_chip_rect);
					break;
				case Block::house_wall_1_down:
					//::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 47 + 7)).draw(map_chip_rect);
					//::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 116 + 3)).draw(map_chip_rect);
					::As::Image(resource_.getMapChip().getMapChip("Base", 8 * 10 + 0)).draw(map_chip_rect);
					break;
				case Block::water_ground_2:
					AutoTileIndex auto_tile_index(field_map.getAutoTile(), cd_anime_sea, 8);
					::As::ImageQuadrant(
						resource_.getMapChip().getMapChip("Lake", auto_tile_index.auto_tile_upper_left),
						resource_.getMapChip().getMapChip("Lake", auto_tile_index.auto_tile_upper_right),
						resource_.getMapChip().getMapChip("Lake", auto_tile_index.auto_tile_lower_left),
						resource_.getMapChip().getMapChip("Lake", auto_tile_index.auto_tile_lower_right)).draw(map_chip_rect);
					break;
				}

			}
		);
	}

}

#endif //Included Sample