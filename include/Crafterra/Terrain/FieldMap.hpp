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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_FIELD_MAP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_FIELD_MAP_HPP


#include <Crafterra/Terrain/TerrainInformation.hpp>

#include <AsLib2/DataType/ArrayDataType.hpp>
#include <Crafterra/Terrain/MapChip.hpp>

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

#include <memory>
#include <Crafterra/Macro/New.hpp> // CRAFTERRA_NEW

#include <Crafterra/Terrain/TileConnection.hpp>

// パーリンノイズ
#include <Crafterra/TerrainGeneration/PerlinNoise2D.hpp>
// パーリンノイズをフィールドマップ上に生成
#include <Crafterra/TerrainGeneration/TerrainPerlinNoise.hpp>

namespace Crafterra {

	unsigned int getDxColor(const int r_, const int g_, const int b_) {
		return (r_ * 256 + g_) * 256 + b_;
	}

	class XorShift32 {
	private:
		::As::Uint32 seed;
	public:
		::As::Uint32 getRand() {
			seed ^= seed << 13;
			seed ^= seed >> 17;
			seed ^= seed << 5;
			return seed;
		}
		double getRand2() {
			return double(getRand() - 1) / 4294967295.0;
		}
		bool getProbability(const double probability_) {
			return (probability_ > getRand2());
		}
		As::Int32 getProbabilityDivision(const double probability_, const As::Int32 division_) {
			if (probability_ <= getRand2() || division_ <= 0) return -1;
			return As::Int32(getRand2() / probability_ * double(division_));
		}
		void setSeed(const ::As::Uint32 seed_) {
			seed = seed_;
		}
		XorShift32(const ::As::Uint32 seed_) : seed(seed_) {}
	};

	class Terrain {

		// 暫定的なマップデータ
		using MapMat = ::As::UniquePtrMatrix<::Crafterra::TerrainInformation>;
		using ObjectMapMat = ::As::UniquePtrMatrix4D<TerrainObject>;
		using DrawMapMat = ::As::UniquePtrMatrix<DrawMapChip>;
		using shape_t = ElevationUint;

	public:

		void setTile(DrawMapMat& draw_map_matrix) const {
			// 崖のオートタイルを計算
			for (::As::IndexUint col{ 1 }; col < draw_map_matrix.getWidth() - 1; ++col)
				for (::As::IndexUint row{}; row < draw_map_matrix.getDepth() - 1; ++row)
					for (::As::IndexUint layer = 0; layer < draw_map_layer_max; ++layer) {
						DrawMapChipUnit& draw_map_tile = draw_map_matrix[row][col].getTile(layer);
						if (draw_map_tile.getTerrainObject() != TerrainObject::cliff) continue; // 崖じゃなかったら返す
						bool is_left = true;
						bool is_right = true;
						bool is_down = true;
						for (::As::IndexUint layer2 = 0; layer2 < draw_map_layer_max; ++layer2) {
							const DrawMapChipUnit& left_tile = draw_map_matrix[row][col - 1].cgetTile(layer2);
							const DrawMapChipUnit& right_tile = draw_map_matrix[row][col + 1].cgetTile(layer2);
							const DrawMapChipUnit& down_tile = draw_map_matrix[row + 1][col].cgetTile(layer2);

							if (is_left)
								is_left = (left_tile.getIsCliff() ||
									((!left_tile.getIsCliff()) && draw_map_tile.getElevation() < left_tile.getElevation()));
							if (is_right)
								is_right = (right_tile.getIsCliff() ||
									((!right_tile.getIsCliff()) && draw_map_tile.getElevation() < right_tile.getElevation()));
							if (is_down)
								is_down = (down_tile.getIsCliff());
						}
						draw_map_tile.setCliff(
							getHomogeneousConnectionCliff(
								is_left
								, is_right
								, is_down
							)
						);
					}

			for (::As::IndexUint col{ 1 }; col < draw_map_matrix.getWidth() - 1; ++col)
				for (::As::IndexUint row{ 1 }; row < draw_map_matrix.getDepth() - 1; ++row) {
					for (::As::IndexUint layer = 0; layer < draw_map_layer_max; ++layer) {
						DrawMapChipUnit& draw_map_tile = draw_map_matrix[row][col].getTile(layer);
						if (draw_map_tile.getIsCliff()) continue;

						bool is_cliff_top_up = false;
						bool is_cliff_top_left = false;
						bool is_cliff_top_right = false;
						bool is_cliff_top_down = false;
						bool is_cliff_top_upper_left = false;
						bool is_cliff_top_upper_right = false;
						bool is_cliff_top_lower_left = false;
						bool is_cliff_top_lower_right = false;

						bool is_biome_auto_tile_up = false;
						bool is_biome_auto_tile_left = false;
						bool is_biome_auto_tile_right = false;
						bool is_biome_auto_tile_down = false;
						bool is_biome_auto_tile_upper_left = false;
						bool is_biome_auto_tile_upper_right = false;
						bool is_biome_auto_tile_lower_left = false;
						bool is_biome_auto_tile_lower_right = false;

						bool is_auto_tile_up = false;
						bool is_auto_tile_left = false;
						bool is_auto_tile_right = false;
						bool is_auto_tile_down = false;
						bool is_auto_tile_upper_left = false;
						bool is_auto_tile_upper_right = false;
						bool is_auto_tile_lower_left = false;
						bool is_auto_tile_lower_right = false;

						const ElevationUint center_elevation = draw_map_matrix[row][col].getTile(layer).getElevation();
						for (::As::IndexUint layer2 = 0; layer2 < draw_map_layer_max; ++layer2) {

							const ElevationUint up_elevation = draw_map_matrix[row - 1][col].getTile(layer2).getElevation();
							const ElevationUint left_elevation = draw_map_matrix[row][col - 1].getTile(layer2).getElevation();
							const ElevationUint right_elevation = draw_map_matrix[row][col + 1].getTile(layer2).getElevation();
							const ElevationUint down_elevation = draw_map_matrix[row + 1][col].getTile(layer2).getElevation();
							const ElevationUint upper_left_elevation = draw_map_matrix[row - 1][col - 1].getTile(layer2).getElevation();
							const ElevationUint upper_right_elevation = draw_map_matrix[row - 1][col + 1].getTile(layer2).getElevation();
							const ElevationUint lower_left_elevation = draw_map_matrix[row + 1][col - 1].getTile(layer2).getElevation();
							const ElevationUint lower_right_elevation = draw_map_matrix[row + 1][col + 1].getTile(layer2).getElevation();

							if (!is_cliff_top_up) is_cliff_top_up = (center_elevation == up_elevation);
							if (!is_cliff_top_left) is_cliff_top_left = (center_elevation == left_elevation);
							if (!is_cliff_top_right) is_cliff_top_right = (center_elevation == right_elevation);
							if (!is_cliff_top_down) is_cliff_top_down = (center_elevation == down_elevation);
							if (!is_cliff_top_upper_left) is_cliff_top_upper_left = (center_elevation == upper_left_elevation);
							if (!is_cliff_top_upper_right) is_cliff_top_upper_right = (center_elevation == upper_right_elevation);
							if (!is_cliff_top_lower_left) is_cliff_top_lower_left = (center_elevation == lower_left_elevation);
							if (!is_cliff_top_lower_right) is_cliff_top_lower_right = (center_elevation == lower_right_elevation);


							if (!is_biome_auto_tile_up) is_biome_auto_tile_up = draw_map_matrix[row - 1][col].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row - 1][col].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row - 1][col].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_left) is_biome_auto_tile_left = draw_map_matrix[row][col - 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row][col - 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row][col - 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_right) is_biome_auto_tile_right = draw_map_matrix[row][col + 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row][col + 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row][col + 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_down) is_biome_auto_tile_down = draw_map_matrix[row + 1][col].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row + 1][col].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row + 1][col].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_upper_left) is_biome_auto_tile_upper_left = draw_map_matrix[row - 1][col - 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row - 1][col - 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row - 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_upper_right) is_biome_auto_tile_upper_right = draw_map_matrix[row - 1][col + 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row - 1][col + 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row - 1][col + 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_lower_left) is_biome_auto_tile_lower_left = draw_map_matrix[row + 1][col - 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row + 1][col - 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row + 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_lower_right) is_biome_auto_tile_lower_right = draw_map_matrix[row + 1][col + 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row + 1][col + 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row + 1][col + 1].getTile(layer2).getIsCliff());

							if (!is_auto_tile_up) is_auto_tile_up = draw_map_matrix[row - 1][col].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row - 1][col].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row - 1][col].getTile(layer2).getIsCliff());
							if (!is_auto_tile_left) is_auto_tile_left = draw_map_matrix[row][col - 1].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row][col - 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row][col - 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_right) is_auto_tile_right = draw_map_matrix[row][col + 1].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row][col + 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row][col + 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_down) is_auto_tile_down = draw_map_matrix[row + 1][col].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row + 1][col].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row + 1][col].getTile(layer2).getIsCliff());
							if (!is_auto_tile_upper_left) is_auto_tile_upper_left = draw_map_matrix[row - 1][col - 1].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row - 1][col - 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row - 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_upper_right) is_auto_tile_upper_right = draw_map_matrix[row - 1][col + 1].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row - 1][col + 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row - 1][col + 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_lower_left) is_auto_tile_lower_left = draw_map_matrix[row + 1][col - 1].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row + 1][col - 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row + 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_lower_right) is_auto_tile_lower_right = draw_map_matrix[row + 1][col + 1].getTile(layer2).getTerrainObject() == draw_map_tile.getTerrainObject() && draw_map_matrix[row + 1][col + 1].getTile(layer2).getElevation() == draw_map_tile.getElevation() && (!draw_map_matrix[row + 1][col + 1].getTile(layer2).getIsCliff());
						}

						// 崖上のオートタイルを計算 ( 一部バグがあり、未完成 )
						draw_map_matrix[row][col].getTile(layer).setCliffTop(
							getHomogeneousConnection(
								is_cliff_top_up
								, is_cliff_top_left
								, is_cliff_top_right
								, is_cliff_top_down
								, is_cliff_top_upper_left
								, is_cliff_top_upper_right
								, is_cliff_top_lower_left
								, is_cliff_top_lower_right
							)
						);
						// ウディタ規格オートタイルの計算
						// 同質接続の条件：同じバイオーム＆同じ標高＆崖ではない
						draw_map_tile.setBiomeAutoTile(
							getHomogeneousConnectionAutoTile(
								is_biome_auto_tile_up
								, is_biome_auto_tile_left
								, is_biome_auto_tile_right
								, is_biome_auto_tile_down
								, is_biome_auto_tile_upper_left
								, is_biome_auto_tile_upper_right
								, is_biome_auto_tile_lower_left
								, is_biome_auto_tile_lower_right
							)
						);
						// ウディタ規格オートタイルの計算
						// 同質接続の条件：同じバイオーム＆同じ標高＆崖ではない
						draw_map_tile.setAutoTile(
							getHomogeneousConnectionAutoTile(
								is_auto_tile_up
								, is_auto_tile_left
								, is_auto_tile_right
								, is_auto_tile_down
								, is_auto_tile_upper_left
								, is_auto_tile_upper_right
								, is_auto_tile_lower_left
								, is_auto_tile_lower_right
							)
						);
					}
				}
		}

		void setTerrain(ObjectMapMat& terrain_object_matrix, MapMat& terrain_information_matrix, DrawMapMat& draw_map_matrix) const {

			for (::As::IndexUint row{}, mat_index{}; row < draw_map_matrix.getDepth(); ++row)
				for (::As::IndexUint col{}; col < draw_map_matrix.getWidth(); ++col, ++mat_index) {
					TerrainInformation& field_map = terrain_information_matrix[row][col];
					DrawMapChip& draw_map = draw_map_matrix[row][col];
					draw_map.setTileNum(0);
					draw_map.clearTile();
					for (::As::IndexUint layer{}; layer < draw_map_layer_max; ++layer) {
						draw_map.getTile(layer).setElevation(0); // 初期化
					}

					for (::As::IndexUint row3{ row }, block_index{}; block_index < terrain_object_matrix.getHeight(); --row3, ++block_index) {
						for (::As::IndexUint block_layer_index = 0; block_layer_index < terrain_object_matrix.getLayer(); ++block_layer_index) {
							const TerrainObject block = terrain_object_matrix.getValueZXYL(mat_index, block_index, block_layer_index);
							if (block != TerrainObject::empty) {
								DrawMapChip& draw_map_2 = draw_map_matrix[row3][col];
								draw_map_2.setNextTile();
								draw_map_2.setIsCliff(block == TerrainObject::cliff); // どこが崖になっているか調べる
								draw_map_2.setIsCliffTop(block_index == ::As::IndexUint(field_map.getBlockElevation())); // どこが崖上になっているか調べる
								draw_map_2.setTerrainObject(block); // ブロックを格納
								draw_map_2.setX(col);
								draw_map_2.setY(block_index);
								draw_map_2.setZ(row);

								if (ElevationUint(block_index) <= field_map.getBlockElevation()) {
									if (draw_map_2.getTile().getElevation() < ElevationUint(block_index)) draw_map_2.setElevation(ElevationUint(block_index));
								}
							}
						}
						if (row3 == 0) break;
					}

					const As::Int32 row2 = As::Int32(row) - As::Int32(field_map.getBlockElevation());
					if (row2 >= 0) {
						for (::As::IndexUint layer = 0; layer < draw_map_layer_max; ++layer) {
							draw_map_matrix[row2][col].getTile(layer).setDrawBiome(field_map.getBiome());
						}
					}

				}
			this->setTile(draw_map_matrix);
		}

		// フィールドマップの下半分の地形が上半分へ移動する
		void moveUp(ObjectMapMat& terrain_object_matrix, MapMat& terrain_information_matrix, const ::As::IndexUint field_height_half_) const {
			for (::As::IndexUint row{}; row < field_height_half_; ++row)
				for (::As::IndexUint col{}; col < terrain_information_matrix.getWidth(); ++col) {

					const ::As::IndexUint before_bo_index_2d = terrain_object_matrix.getIndexMulZX(row + field_height_half_, col);
					const ::As::IndexUint after_bo_index_2d = terrain_object_matrix.getIndexMulZX(row, col);
					for (As::IndexUint i = 0; i < terrain_object_matrix.getHeight(); ++i)
						for (As::IndexUint layer = 0; layer < terrain_object_matrix.getLayer(); ++layer) {
							const TerrainObject& obj = terrain_object_matrix.getValueMulZXYL(before_bo_index_2d, i, layer);
							terrain_object_matrix.setValueMulZXYL(obj, after_bo_index_2d, i, layer);
						}

					TerrainInformation& field_map_after = terrain_information_matrix[row][col];
					const TerrainInformation& field_map_before = terrain_information_matrix[row + field_height_half_][col];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの上半分の地形が下半分へ移動する
		void moveDown(ObjectMapMat& terrain_object_matrix, MapMat& terrain_information_matrix, const ::As::IndexUint field_height_half_) const {
			for (::As::IndexUint row{}; row < field_height_half_; ++row)
				for (::As::IndexUint col{}; col < terrain_information_matrix.getWidth(); ++col) {

					const ::As::IndexUint before_bo_index_2d = terrain_object_matrix.getIndexMulZX(row, col);
					const ::As::IndexUint after_bo_index_2d = terrain_object_matrix.getIndexMulZX(row + field_height_half_, col);
					for (As::IndexUint i = 0; i < terrain_object_matrix.getHeight(); ++i)
						for (As::IndexUint layer = 0; layer < terrain_object_matrix.getLayer(); ++layer) {
							const TerrainObject& obj = terrain_object_matrix.getValueMulZXYL(before_bo_index_2d, i, layer);
							terrain_object_matrix.setValueMulZXYL(obj, after_bo_index_2d, i, layer);
						}

					TerrainInformation& field_map_after = terrain_information_matrix[row + field_height_half_][col];
					const TerrainInformation& field_map_before = terrain_information_matrix[row][col];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの右半分の地形が左半分へ移動する
		void moveLeft(ObjectMapMat& terrain_object_matrix, MapMat& terrain_information_matrix, const ::As::IndexUint field_width_half_) const {
			for (::As::IndexUint row{}; row < terrain_information_matrix.getDepth(); ++row)
				for (::As::IndexUint col{}; col < field_width_half_; ++col) {

					const ::As::IndexUint before_bo_index_2d = terrain_object_matrix.getIndexMulZX(row, col + field_width_half_);
					const ::As::IndexUint after_bo_index_2d = terrain_object_matrix.getIndexMulZX(row, col);
					for (As::IndexUint i = 0; i < terrain_object_matrix.getHeight(); ++i)
						for (As::IndexUint layer = 0; layer < terrain_object_matrix.getLayer(); ++layer) {
							const TerrainObject& obj = terrain_object_matrix.getValueMulZXYL(before_bo_index_2d, i, layer);
							terrain_object_matrix.setValueMulZXYL(obj, after_bo_index_2d, i, layer);
						}

					TerrainInformation& field_map_after = terrain_information_matrix[row][col];
					const TerrainInformation& field_map_before = terrain_information_matrix[row][col + field_width_half_];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの左半分の地形が右半分へ移動する
		void moveRight(ObjectMapMat& terrain_object_matrix, MapMat& terrain_information_matrix, const ::As::IndexUint field_width_half_) const {
			for (::As::IndexUint row{}; row < terrain_information_matrix.getDepth(); ++row)
				for (::As::IndexUint col{}; col < field_width_half_; ++col) {

					const ::As::IndexUint before_bo_index_2d = terrain_object_matrix.getIndexMulZX(row, col);
					const ::As::IndexUint after_bo_index_2d = terrain_object_matrix.getIndexMulZX(row, col + field_width_half_);
					for (As::IndexUint i = 0; i < terrain_object_matrix.getHeight(); ++i)
						for (As::IndexUint layer = 0; layer < terrain_object_matrix.getLayer(); ++layer) {
							const TerrainObject& obj = terrain_object_matrix.getValueMulZXYL(before_bo_index_2d, i, layer);
							terrain_object_matrix.setValueMulZXYL(obj, after_bo_index_2d, i, layer);
						}

					TerrainInformation& field_map_after = terrain_information_matrix[row][col + field_width_half_];
					const TerrainInformation& field_map_before = terrain_information_matrix[row][col];
					field_map_after = field_map_before;
				}
		}

		// 木の生成
		void generationTree(ObjectMapMat& terrain_object_matrix, const ::As::IndexUint bo_index_2d, TerrainInformation& field_map) const {

			const ElevationUint temperature = field_map.getTemperature();
			const ElevationUint elevation = field_map.getElevation();
			const ElevationUint block_elevation = elevation / 2;
			const ElevationUint amount_of_rainfall = field_map.getAmountOfRainfall();

			const ::As::Uint32 flower_num = 9;
			const double flower_probability = 0.02;
			const double default_max = (flower_probability * flower_num);
			double coniferous_tree_generation_probability = 0.0; // 針葉樹の生成確率
			double green_broadleaf_tree_generation_probability = 0.0; // 緑色の広葉樹の生成確率
			double yellow_green_broadleaf_tree_generation_probability = 0.0; // 黄緑色の広葉樹の生成確率

			if (amount_of_rainfall >= 100 && temperature >= 20) {
				if (temperature < 44) {
					coniferous_tree_generation_probability = ((temperature - 20.0) / (44 - 20)) * 0.3; // 針葉樹の生成確率
				}
				else if (temperature < 64) {
					coniferous_tree_generation_probability = (1.0 - ((temperature - 44.0) / (64 - 44))) * 0.3; // 針葉樹の生成確率
				}

				if (temperature >= 44) {
					if (temperature < 72) {
						green_broadleaf_tree_generation_probability = ((temperature - 44.0) / (72 - 44)) * 0.1; // 緑色の広葉樹の生成確率
					}
					else {
						green_broadleaf_tree_generation_probability = 0.1 + ((temperature - 72.0) / (240 - 72)) * 0.6; // 緑色の広葉樹の生成確率
					}
				}
			}
			// 生成される確率
			const double probability_of_generation
				= (default_max
					+ coniferous_tree_generation_probability
					+ green_broadleaf_tree_generation_probability
					+ yellow_green_broadleaf_tree_generation_probability);

			// 生成されない確率
			const double probability_of_no_generation = (1.0 - probability_of_generation);

			double probability = field_map.getFlower();

			//if (probability == 0.0) {
			//	field_map.setBlock(TerrainObject::red_broadleaf_tree_down, block_elevation); // テスト
			//	return;
			//}
			//if (probability == 1.0) {
			//	field_map.setBlock(TerrainObject::red_broadleaf_tree_up, block_elevation); // テスト
			//	return;
			//}

			if (probability < probability_of_no_generation) return;
			probability -= probability_of_no_generation;

			::As::IndexUint block_layer_index = 0;
			for (As::IndexUint layer = 0; layer < terrain_object_matrix.getLayer(); ++layer) {
				if (TerrainObject::empty == terrain_object_matrix.getValueMulZXYL(bo_index_2d, block_elevation, layer)) {
					block_layer_index = layer;
					break;
				}
			}

			// 草花の生成テスト
			if (probability < flower_probability) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::grass_1, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < (flower_probability * 2)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::grass_2, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < (flower_probability * 3)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::grass_3, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < (flower_probability * 4)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::grass_4, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < (flower_probability * 5)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::flower_1, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < (flower_probability * 6)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::flower_2, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < (flower_probability * 7)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::flower_3, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < (flower_probability * 8)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::flower_4, bo_index_2d, block_elevation, block_layer_index);
				return;
			}
			else if (probability < default_max) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::cultivated_land, bo_index_2d, block_elevation, block_layer_index);
				terrain_object_matrix.setValueMulZXYL(TerrainObject::planted_carrot, bo_index_2d, block_elevation, block_layer_index + 1);
				return;
			}
			else if (probability <
				(default_max + coniferous_tree_generation_probability)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::green_coniferous_tree_down, bo_index_2d, block_elevation, block_layer_index);
				terrain_object_matrix.setValueMulZXYL(TerrainObject::green_coniferous_tree_up, bo_index_2d, block_elevation + 1, block_layer_index);
				return;
			}
			else if (probability <
				(default_max + coniferous_tree_generation_probability + green_broadleaf_tree_generation_probability)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::green_broadleaf_tree_down, bo_index_2d, block_elevation, block_layer_index);
				terrain_object_matrix.setValueMulZXYL(TerrainObject::green_broadleaf_tree_up, bo_index_2d, block_elevation + 1, block_layer_index);
				return;
			}
			else if (probability <
				(default_max + coniferous_tree_generation_probability + green_broadleaf_tree_generation_probability + yellow_green_broadleaf_tree_generation_probability)) {
				terrain_object_matrix.setValueMulZXYL(TerrainObject::yellow_green_broadleaf_tree_down, bo_index_2d, block_elevation, block_layer_index);
				terrain_object_matrix.setValueMulZXYL(TerrainObject::yellow_green_broadleaf_tree_up, bo_index_2d, block_elevation + 1, block_layer_index);
				return;
			}
		}

		// フィールドマップを生成
		void generation(ObjectMapMat& terrain_object_matrix, MapMat& terrain_information_matrix, TerrainPerlinNoise& terrain_noise_, const ::As::IndexUint chunk_index_x_, const ::As::IndexUint chunk_index_y_, const ::As::IndexUint start_x_, const ::As::IndexUint start_y_, const ::As::IndexUint end_x_, const ::As::IndexUint end_y_) const {

			const ElevationUint sea_elevation = 110;

			terrain_noise_.generation(terrain_information_matrix, chunk_index_x_, chunk_index_y_, start_x_, start_y_, end_x_, end_y_);

			XorShift32 xs32(terrain_noise_.getElevationSeed());

			//バイオームの分類分け
			for (::As::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::As::IndexUint col{ start_x_ }; col < end_x_; ++col) {
					const ::As::IndexUint bo_index_2d = terrain_object_matrix.getIndexMulZX(row, col);
					TerrainInformation& field_map = terrain_information_matrix[row][col];

					const ElevationUint elevation = field_map.getElevation();
					const ElevationUint block_elevation = elevation / 2;
					const ElevationUint amount_of_rainfall = field_map.getAmountOfRainfall();
					const ElevationUint temperature = ((field_map.getTemperature() < block_elevation) ? 0 : (field_map.getTemperature() - block_elevation));
					field_map.setTemperature(temperature);

					// 標高がある定数値よりも少ない場合は海になる
					if (elevation < sea_elevation) field_map.setBiome(TerrainBiome::sea);
					// 気温が低い場合はツンドラになる
					else if (temperature < 24) field_map.setBiome(TerrainBiome::tundra);
					// 降水量が少ない場合は砂漠になる
					else if (amount_of_rainfall < 24) field_map.setBiome(TerrainBiome::desert);

					else if (amount_of_rainfall < 72) {
						if (temperature < 128) field_map.setBiome(TerrainBiome::rock); // ステップ？
						else field_map.setBiome(TerrainBiome::savannah);
					}
					else if (temperature < 69) field_map.setBiome(TerrainBiome::forest); // grass
					else if (temperature < 96) field_map.setBiome(TerrainBiome::normal);
					else if (temperature < 120) field_map.setBiome(TerrainBiome::forest);
					else if (amount_of_rainfall < 125) field_map.setBiome(TerrainBiome::mountain);
					else if (temperature < 132) field_map.setBiome(TerrainBiome::mountain);
					else field_map.setBiome(TerrainBiome::mountain);

					const ::As::IndexUint block_layer_index = 0;

					// ブロックを初期化
					for (As::IndexUint i = 0; i < terrain_object_matrix.getHeight(); ++i) {
						for (As::IndexUint layer = 0; layer < terrain_object_matrix.getLayer(); ++layer) {
							terrain_object_matrix.setValueMulZXYL(TerrainObject::empty, bo_index_2d, i, layer);
						}
					}

					for (As::IndexUint i = 0; i < block_elevation; ++i) {
						terrain_object_matrix.setValueMulZXYL(TerrainObject::cliff, bo_index_2d, i, block_layer_index);
					}
					for (As::IndexUint i = block_elevation + 1; i < terrain_object_matrix.getHeight(); ++i) {
						terrain_object_matrix.setValueMulZXYL(TerrainObject::empty, bo_index_2d, i, block_layer_index); // からの場合 ( 崖上を除く )
					}
					terrain_object_matrix.setValueMulZXYL(TerrainObject::cliff_top, bo_index_2d, block_elevation, block_layer_index); // からだけど崖上の場合

					// 海
					if (field_map.getBiome() == TerrainBiome::sea) {
						field_map.setElevation(sea_elevation);
						field_map.setBlockElevation(sea_elevation / 2);

						for (As::IndexUint i = elevation / 2; i <= sea_elevation / 2; ++i) {
							terrain_object_matrix.setValueMulZXYL(TerrainObject::cliff_top, bo_index_2d, i, block_layer_index);
							terrain_object_matrix.setValueMulZXYL(TerrainObject::water_ground, bo_index_2d, i, block_layer_index + 1);
						}
					}
					// 陸
					else {
						field_map.setBlockElevation(block_elevation);

						this->generationTree(terrain_object_matrix, bo_index_2d, field_map); // 木の生成
					}
				}
		}
		void initialGeneration(ObjectMapMat& terrain_object_matrix, MapMat& field_map_matrix_, TerrainPerlinNoise& terrain_noise_, const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_) const {
			generation(terrain_object_matrix, field_map_matrix_, terrain_noise_, chunk_index_x_, chunk_index_y_, 0, 0, field_map_matrix_.getWidth(), field_map_matrix_.getDepth());
		}

	};

}

#endif //Included Crafterra Library