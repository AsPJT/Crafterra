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

#include <AsLib2/DataType/ArrayDataType.hpp>
#include <Crafterra/Terrain/MapChip.hpp>

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

#include <memory>
#include <Crafterra/Macro/New.hpp> // CRAFTERRA_NEW

#include <Crafterra/Terrain/TileConnection.hpp>


// 地形生成用 ( 後に削除予定 )
//#include <DTL/Utility/PerlinNoise.hpp>

#include <Crafterra/Generation/PerlinNoise.hpp>

namespace Crafterra {

	unsigned int getDxColor(const int r_, const int g_, const int b_) {
		return (r_ * 256 + g_) * 256 + b_;
	}

	template<typename Matrix_, typename ElevationUint_>
	void perlinNoise(
		const Matrix_& matrix_,
		const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_, const As::IndexUint one_chunk_width_, const As::IndexUint one_chunk_height_,
		const As::IndexUint start_x_, const As::IndexUint start_y_, const As::IndexUint end_x_, const As::IndexUint end_y_,
		::Crafterra::PerlinNoise& perlin, const double frequency_, const As::IndexUint octaves_,
		const ElevationUint_ max_height_, const ElevationUint_ min_height_ = 0) {

		for (As::IndexUint row_index{ start_y_ }, row{}; row_index < end_y_; ++row_index, ++row)
			for (As::IndexUint col_index{ start_x_ }, col{}; col_index < end_x_; ++col_index, ++col)
				matrix_(col_index, row_index,
				min_height_ + static_cast<ElevationUint_>(
				(max_height_ - min_height_) *
					perlin.octaveNoise(octaves_,
					(::As::Uint64(chunk_index_x_) * ::As::Uint64(one_chunk_width_) + ::As::Uint64(col)) / frequency_,
						((::As::Uint64(chunk_index_y_) * ::As::Uint64(one_chunk_height_) + ::As::Uint64(row)) / frequency_)
					)
					));
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

	class TerrainNoise {
		// 暫定的なマップデータ
		using MapMat = ::As::Matrix<MapChip, init_field_map_width, init_field_map_height>;
		using shape_t = ElevationUint;

		::As::Uint32 temperature_seed;
		::As::Uint32 amount_of_rainfall_seed;
		::As::Uint32 elevation_seed;
		::As::Uint32 flower_seed;
		::As::Uint32 lake_seed;

		::Crafterra::PerlinNoise perlin_temperature_seed;
		::Crafterra::PerlinNoise perlin_amount_of_rainfall_seed;
		::Crafterra::PerlinNoise perlin_elevation_seed;
		::Crafterra::PerlinNoise perlin_flower_seed;
		::Crafterra::PerlinNoise perlin_lake_seed;

	public:
		// コンストラクタ
		TerrainNoise(const ::As::Uint32 temperature_seed_, const ::As::Uint32 amount_of_rainfall_seed_, const ::As::Uint32 elevation_seed_, const ::As::Uint32 flower_seed_, const ::As::Uint32 lake_seed_)
			:
			temperature_seed(temperature_seed_)
			, amount_of_rainfall_seed(amount_of_rainfall_seed_)
			, elevation_seed(elevation_seed_)
			, flower_seed(flower_seed_)
			, lake_seed(lake_seed_)
			, perlin_temperature_seed(
				[temperature_seed_](std::array<::As::Uint8, 512>::iterator begin_, std::array<::As::Uint8, 512>::iterator end_) {
					::std::shuffle(begin_, end_, ::std::default_random_engine(temperature_seed_)); })
			, perlin_amount_of_rainfall_seed(
				[amount_of_rainfall_seed_](std::array<::As::Uint8, 512>::iterator begin_, std::array<::As::Uint8, 512>::iterator end_) {
					::std::shuffle(begin_, end_, ::std::default_random_engine(amount_of_rainfall_seed_)); })
						, perlin_elevation_seed(
							[elevation_seed_](std::array<::As::Uint8, 512>::iterator begin_, std::array<::As::Uint8, 512>::iterator end_) {
								::std::shuffle(begin_, end_, ::std::default_random_engine(elevation_seed_)); })
						, perlin_flower_seed(
							[flower_seed_](std::array<::As::Uint8, 512>::iterator begin_, std::array<::As::Uint8, 512>::iterator end_) {
								::std::shuffle(begin_, end_, ::std::default_random_engine(flower_seed_)); })
									, perlin_lake_seed(
										[lake_seed_](std::array<::As::Uint8, 512>::iterator begin_, std::array<::As::Uint8, 512>::iterator end_) {
											::std::shuffle(begin_, end_, ::std::default_random_engine(lake_seed_)); })
		{}

		::As::Uint32 getElevationSeed() const { return this->elevation_seed; }

		void generation(MapMat& field_map_matrix, TerrainNoise& terrain_noise_, const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_, const ::As::Uint32 start_x_, const ::As::Uint32 start_y_, const ::As::Uint32 end_x_, const ::As::Uint32 end_y_) {
			//温度
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setTemperature(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_temperature_seed, 400.1, 8,
				240, 0
			);

			//降水量
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setAmountOfRainfall(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_amount_of_rainfall_seed, 400.1, 8,
				240, 0
			);

			//標高
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setElevation(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_elevation_seed, 600.1, 10,
				240, 0
			);

			//花
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const double value_) { field_map_matrix[y_][x_].setFlower(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_flower_seed, 1.12345, 1,
				1.0, 0.0
			);

			//湖
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setLake(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_lake_seed, 10.12345, 3,
				200, 50
			);
		}
	};

	class Terrain {

		// 暫定的なマップデータ
		using MapMat = ::As::Matrix<MapChip, init_field_map_width, init_field_map_height>;
		using DrawMapMat = ::As::Matrix<DrawMapChip, init_field_map_width, init_field_map_height>;
		using shape_t = ElevationUint;

	public:

		void setTile(DrawMapMat& draw_map_matrix) const {
			// 崖のオートタイルを計算
			for (::As::IndexUint col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::As::IndexUint row{}; row < init_field_map_height - 1; ++row)
					for (::As::IndexUint layer = 0; layer < draw_map_layer_max; ++layer) {
						DrawMapChipUnit& draw_map_tile = draw_map_matrix[row][col].getTile(layer);

						bool is_left = true;
						bool is_right = true;
						bool is_down = true;
						for (::As::IndexUint layer2 = 0; layer2 < draw_map_layer_max; ++layer2) {
							const DrawMapChipUnit& left_tile = draw_map_matrix[row][col - 1].cgetTile(layer2);
							const DrawMapChipUnit& right_tile = draw_map_matrix[row][col + 1].cgetTile(layer2);
							const DrawMapChipUnit& down_tile = draw_map_matrix[row + 1][col].cgetTile(layer2);

							if (is_left) 
								is_left = (left_tile.getIsCliff() ||
								((!left_tile.getIsCliff()) && draw_map_tile.getElevation3() < left_tile.getElevation3()));
							if (is_right) 
								is_right = (right_tile.getIsCliff() ||
								((!right_tile.getIsCliff()) && draw_map_tile.getElevation3() < right_tile.getElevation3()));
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

			for (::As::IndexUint col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::As::IndexUint row{ 1 }; row < init_field_map_height - 1; ++row) {
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

						const ElevationUint center_elevation = draw_map_matrix[row][col].getTile(layer).getElevation3();
						for (::As::IndexUint layer2 = 0; layer2 < draw_map_layer_max; ++layer2) {

							const ElevationUint up_elevation = draw_map_matrix[row - 1][col].getTile(layer2).getElevation3();
							const ElevationUint left_elevation = draw_map_matrix[row][col - 1].getTile(layer2).getElevation3();
							const ElevationUint right_elevation = draw_map_matrix[row][col + 1].getTile(layer2).getElevation3();
							const ElevationUint down_elevation = draw_map_matrix[row + 1][col].getTile(layer2).getElevation3();
							const ElevationUint upper_left_elevation = draw_map_matrix[row - 1][col - 1].getTile(layer2).getElevation3();
							const ElevationUint upper_right_elevation = draw_map_matrix[row - 1][col + 1].getTile(layer2).getElevation3();
							const ElevationUint lower_left_elevation = draw_map_matrix[row + 1][col - 1].getTile(layer2).getElevation3();
							const ElevationUint lower_right_elevation = draw_map_matrix[row + 1][col + 1].getTile(layer2).getElevation3();

							if (!is_cliff_top_up) is_cliff_top_up = (center_elevation == up_elevation);
							if (!is_cliff_top_left) is_cliff_top_left = (center_elevation == left_elevation);
							if (!is_cliff_top_right) is_cliff_top_right = (center_elevation == right_elevation);
							if (!is_cliff_top_down) is_cliff_top_down = (center_elevation == down_elevation);
							if (!is_cliff_top_upper_left) is_cliff_top_upper_left = (center_elevation == upper_left_elevation);
							if (!is_cliff_top_upper_right) is_cliff_top_upper_right = (center_elevation == upper_right_elevation);
							if (!is_cliff_top_lower_left) is_cliff_top_lower_left = (center_elevation == lower_left_elevation);
							if (!is_cliff_top_lower_right) is_cliff_top_lower_right = (center_elevation == lower_right_elevation);


							if (!is_biome_auto_tile_up) is_biome_auto_tile_up = draw_map_matrix[row - 1][col].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row - 1][col].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row - 1][col].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_left) is_biome_auto_tile_left = draw_map_matrix[row][col - 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row][col - 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row][col - 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_right) is_biome_auto_tile_right = draw_map_matrix[row][col + 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row][col + 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row][col + 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_down) is_biome_auto_tile_down = draw_map_matrix[row + 1][col].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row + 1][col].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row + 1][col].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_upper_left) is_biome_auto_tile_upper_left = draw_map_matrix[row - 1][col - 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row - 1][col - 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row - 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_upper_right) is_biome_auto_tile_upper_right = draw_map_matrix[row - 1][col + 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row - 1][col + 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row - 1][col + 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_lower_left) is_biome_auto_tile_lower_left = draw_map_matrix[row + 1][col - 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row + 1][col - 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row + 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_biome_auto_tile_lower_right) is_biome_auto_tile_lower_right = draw_map_matrix[row + 1][col + 1].getTile(layer2).getDrawBiome() == draw_map_tile.getDrawBiome() && draw_map_matrix[row + 1][col + 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row + 1][col + 1].getTile(layer2).getIsCliff());

							if (!is_auto_tile_up) is_auto_tile_up = draw_map_matrix[row - 1][col].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row - 1][col].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row - 1][col].getTile(layer2).getIsCliff());
							if (!is_auto_tile_left) is_auto_tile_left = draw_map_matrix[row][col - 1].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row][col - 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row][col - 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_right) is_auto_tile_right = draw_map_matrix[row][col + 1].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row][col + 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row][col + 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_down) is_auto_tile_down = draw_map_matrix[row + 1][col].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row + 1][col].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row + 1][col].getTile(layer2).getIsCliff());
							if (!is_auto_tile_upper_left) is_auto_tile_upper_left = draw_map_matrix[row - 1][col - 1].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row - 1][col - 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row - 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_upper_right) is_auto_tile_upper_right = draw_map_matrix[row - 1][col + 1].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row - 1][col + 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row - 1][col + 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_lower_left) is_auto_tile_lower_left = draw_map_matrix[row + 1][col - 1].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row + 1][col - 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row + 1][col - 1].getTile(layer2).getIsCliff());
							if (!is_auto_tile_lower_right) is_auto_tile_lower_right = draw_map_matrix[row + 1][col + 1].getTile(layer2).getDrawBlock() == draw_map_tile.getDrawBlock() && draw_map_matrix[row + 1][col + 1].getTile(layer2).getElevation3() == draw_map_tile.getElevation3() && (!draw_map_matrix[row + 1][col + 1].getTile(layer2).getIsCliff());
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
								, is_cliff_top_lower_left
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

		void setTerrain(const MapMat& field_map_matrix, DrawMapMat& draw_map_matrix) const {

			for (::As::IndexUint row{}; row < init_field_map_height; ++row)
				for (::As::IndexUint col{}; col < init_field_map_width; ++col) {
					const MapChip& field_map = field_map_matrix[row][col];
					DrawMapChip& draw_map = draw_map_matrix[row][col];
					draw_map.setTileNum(0);
					draw_map.clearTile();
					for (::As::IndexUint layer{}; layer < draw_map_layer_max; ++layer) {
						draw_map.getTile(layer).setElevation3(0); // 初期化
					}

					for (::As::IndexUint row3{ row }, block_index{}; block_index < 128; --row3, ++block_index) {
						if (field_map.getBlock(block_index) != Block::empty) {
							DrawMapChip& draw_map_2 = draw_map_matrix[row3][col];
							draw_map_2.setNextTile();
							draw_map_2.setIsCliff(field_map.getBlock(block_index) == Block::cliff); // どこが崖になっているか調べる
							draw_map_2.setIsCliffTop(block_index == ::As::IndexUint(field_map.getBlockElevation())); // どこが崖上になっているか調べる
							draw_map_2.setDrawBlock(field_map.getBlock(block_index)); // ブロックを格納
							draw_map_2.setX(col);
							draw_map_2.setY(block_index);
							draw_map_2.setZ(row);

							if (ElevationUint(block_index) <= field_map.getBlockElevation()) {
								if (draw_map_2.getTile().getElevation3() < ElevationUint(block_index)) draw_map_2.setElevation3(ElevationUint(block_index));
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
		void moveUp(MapMat& field_map_matrix, const ::As::Uint32 field_height_half_) const {
			for (::As::IndexUint row{}; row < field_height_half_; ++row)
				for (::As::IndexUint col{}; col < init_field_map_width; ++col) {
					MapChip& field_map_after = field_map_matrix[row][col];
					const MapChip& field_map_before = field_map_matrix[row + field_height_half_][col];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの上半分の地形が下半分へ移動する
		void moveDown(MapMat& field_map_matrix, const ::As::Uint32 field_height_half_) const {
			for (::As::IndexUint row{}; row < field_height_half_; ++row)
				for (::As::IndexUint col{}; col < init_field_map_width; ++col) {
					MapChip& field_map_after = field_map_matrix[row + field_height_half_][col];
					const MapChip& field_map_before = field_map_matrix[row][col];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの右半分の地形が左半分へ移動する
		void moveLeft(MapMat& field_map_matrix, const ::As::Uint32 field_width_half_) const {
			for (::As::IndexUint row{}; row < init_field_map_height; ++row)
				for (::As::IndexUint col{}; col < field_width_half_; ++col) {
					MapChip& field_map_after = field_map_matrix[row][col];
					const MapChip& field_map_before = field_map_matrix[row][col + field_width_half_];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの左半分の地形が右半分へ移動する
		void moveRight(MapMat& field_map_matrix, const ::As::Uint32 field_width_half_) const {
			for (::As::IndexUint row{}; row < init_field_map_height; ++row)
				for (::As::IndexUint col{}; col < field_width_half_; ++col) {
					MapChip& field_map_after = field_map_matrix[row][col + field_width_half_];
					const MapChip& field_map_before = field_map_matrix[row][col];
					field_map_after = field_map_before;
				}
		}

		// 木の生成
		void generationTree(MapChip& field_map) const {

			const ElevationUint temperature = field_map.getTemperature();
			const ElevationUint elevation = field_map.getElevation();
			const ElevationUint block_elevation = elevation / 2;
			const ElevationUint amount_of_rainfall = field_map.getAmountOfRainfall();

			const ::As::Uint32 flower_num = 8;
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
			//	field_map.setBlock(Block::red_broadleaf_tree_down, block_elevation); // テスト
			//	return;
			//}
			//if (probability == 1.0) {
			//	field_map.setBlock(Block::red_broadleaf_tree_up, block_elevation); // テスト
			//	return;
			//}

			if (probability < probability_of_no_generation) return;
			probability -= probability_of_no_generation;

			// 草花の生成テスト
			if (probability < flower_probability) {
				field_map.setBlock(Block::grass_1, block_elevation); // テスト
				return;
			}
			else if (probability < (flower_probability * 2)) {
				field_map.setBlock(Block::grass_2, block_elevation); // テスト
				return;
			}
			else if (probability < (flower_probability * 3)) {
				field_map.setBlock(Block::grass_3, block_elevation); // テスト
				return;
			}
			else if (probability < (flower_probability * 4)) {
				field_map.setBlock(Block::grass_4, block_elevation); // テスト
				return;
			}
			else if (probability < (flower_probability * 5)) {
				field_map.setBlock(Block::flower_1, block_elevation); // テスト
				return;
			}
			else if (probability < (flower_probability * 6)) {
				field_map.setBlock(Block::flower_2, block_elevation); // テスト
				return;
			}
			else if (probability < (flower_probability * 7)) {
				field_map.setBlock(Block::flower_3, block_elevation); // テスト
				return;
			}
			else if (probability < default_max) {
				field_map.setBlock(Block::flower_4, block_elevation); // テスト
				return;
			}
			else if (probability <
				(default_max + coniferous_tree_generation_probability)) {
				field_map.setBlock(Block::green_coniferous_tree_up, block_elevation + 1); // テスト
				field_map.setBlock(Block::green_coniferous_tree_down, block_elevation); // テスト
				return;
			}
			else if (probability <
				(default_max + coniferous_tree_generation_probability + green_broadleaf_tree_generation_probability)) {
				field_map.setBlock(Block::green_broadleaf_tree_up, block_elevation + 1); // テスト
				field_map.setBlock(Block::green_broadleaf_tree_down, block_elevation); // テスト
				return;
			}
			else if (probability <
				(default_max + coniferous_tree_generation_probability + green_broadleaf_tree_generation_probability + yellow_green_broadleaf_tree_generation_probability)) {
				field_map.setBlock(Block::yellow_green_broadleaf_tree_up, block_elevation + 1); // テスト
				field_map.setBlock(Block::yellow_green_broadleaf_tree_down, block_elevation); // テスト
				return;
			}
		}

		// フィールドマップを生成
		void generation(MapMat& field_map_matrix, TerrainNoise& terrain_noise_, const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_, const ::As::Uint32 start_x_, const ::As::Uint32 start_y_, const ::As::Uint32 end_x_, const ::As::Uint32 end_y_) const {

			const ElevationUint sea_elevation = 110;

			terrain_noise_.generation(field_map_matrix, terrain_noise_, chunk_index_x_, chunk_index_y_, start_x_, start_y_, end_x_, end_y_);

			XorShift32 xs32(terrain_noise_.getElevationSeed());

			//バイオームの分類分け
			for (::As::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::As::IndexUint col{ start_x_ }; col < end_x_; ++col) {
					MapChip& field_map = field_map_matrix[row][col];

					const ElevationUint elevation = field_map.getElevation();
					const ElevationUint block_elevation = elevation / 2;
					const ElevationUint amount_of_rainfall = field_map.getAmountOfRainfall();
					const ElevationUint temperature = ((field_map.getTemperature() < block_elevation) ? 0 : (field_map.getTemperature() - block_elevation));
					field_map.setTemperature(temperature);

					// 標高がある定数値よりも少ない場合は海になる
					if (elevation < sea_elevation) field_map.setBiome(MapChipTypeBiome::sea);
					// 気温が低い場合はツンドラになる
					else if (temperature < 24) field_map.setBiome(MapChipTypeBiome::tundra);
					// 降水量が少ない場合は砂漠になる
					else if (amount_of_rainfall < 24) field_map.setBiome(MapChipTypeBiome::desert);

					else if (amount_of_rainfall < 72) {
						if (temperature < 128) field_map.setBiome(MapChipTypeBiome::rock); // ステップ？
						else field_map.setBiome(MapChipTypeBiome::savannah);
					}
					else if (temperature < 69) field_map.setBiome(MapChipTypeBiome::grass);
					else if (temperature < 96) field_map.setBiome(MapChipTypeBiome::normal);
					else if (temperature < 120) field_map.setBiome(MapChipTypeBiome::forest);
					else if (amount_of_rainfall < 125) field_map.setBiome(MapChipTypeBiome::mountain);
					else if (temperature < 132) field_map.setBiome(MapChipTypeBiome::mountain);
					else field_map.setBiome(MapChipTypeBiome::mountain);

					for (As::IndexUint i = 0; i < block_elevation; ++i) {
						field_map.setBlock(Block::cliff, i);
					}
					for (As::IndexUint i = block_elevation + 1; i < 128; ++i) {
						field_map.setBlock(Block::empty, i); // からの場合 ( 崖上を除く )
					}
					field_map.setBlock(Block::cliff_top, block_elevation); // からだけど崖上の場合

					// 海
					if (field_map.getBiome() == MapChipTypeBiome::sea) {
						field_map.setElevation(sea_elevation);
						field_map.setBlockElevation(sea_elevation / 2);

						for (As::IndexUint i = elevation / 2; i <= sea_elevation / 2; ++i) {
							field_map.setBlock(Block::water_ground, i);
						}
					}
					// 陸
					else {
						field_map.setBlockElevation(block_elevation);

						this->generationTree(field_map); // 木の生成
					}
				}
		}
		void initialGeneration(MapMat& field_map_matrix_, TerrainNoise& terrain_noise_, const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_) const {
			generation(field_map_matrix_, terrain_noise_, chunk_index_x_, chunk_index_y_, 0, 0, init_field_map_width, init_field_map_height);
		}

	};

}

#endif //Included Crafterra Library