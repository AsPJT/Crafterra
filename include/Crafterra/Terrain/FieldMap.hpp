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

	template<typename Matrix_>
	void perlinNoise(
		const Matrix_& matrix_,
		const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_, const As::IndexUint one_chunk_width_, const As::IndexUint one_chunk_height_,
		const As::IndexUint start_x_, const As::IndexUint start_y_, const As::IndexUint end_x_, const As::IndexUint end_y_,
		::Crafterra::PerlinNoise& perlin, const double frequency_, const As::IndexUint octaves_,
		const ElevationUint max_height_, const ElevationUint min_height_ = 0) {

		for (As::IndexUint row_index{ start_y_ }, row{}; row_index < end_y_; ++row_index, ++row)
			for (As::IndexUint col_index{ start_x_ }, col{}; col_index < end_x_; ++col_index, ++col)
				matrix_(col_index, row_index,
				min_height_ + static_cast<ElevationUint>(
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
				240, 100
			);

			//降水量
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setAmountOfRainfall(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_amount_of_rainfall_seed, 400.1, 8,
				225, 0
			);

			//標高
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setElevation(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_elevation_seed, 600.1, 10,
				195, 0
			);

			//花
			perlinNoise(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setFlower(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_flower_seed, 1.12345, 1,
				200, 50
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
		using shape_t = ElevationUint;

	public:

		void setTerrain(MapMat& field_map_matrix) const {

			for (::As::IndexUint row{}; row < init_field_map_height; ++row)
				for (::As::IndexUint col{}; col < init_field_map_width; ++col) {
					MapChip& field_map = field_map_matrix[row][col];
					field_map.setElevation3(0); // 初期化

					ElevationUint elevation3 = 0;
					for (::As::IndexUint row3{ row }, block_index{}; block_index < 128; --row3, ++block_index) {
						if (field_map_matrix[row][col].getBlock(block_index) != Block::empty) {

							field_map_matrix[row3][col].setIsCliff(field_map_matrix[row][col].getBlock(block_index) == Block::cliff); // どこが崖になっているか調べる
							field_map_matrix[row3][col].setDrawBlock(field_map_matrix[row][col].getBlock(block_index)); // ブロックを格納
						}
						if (row3 == 0) break;
					}
					for (::As::IndexUint row3{ row }, block_index{}; elevation3 <= field_map.getBlockElevation(); --row3, ++elevation3, ++block_index) {
						if (field_map_matrix[row3][col].getElevation3() < elevation3) field_map_matrix[row3][col].setElevation3(elevation3);
						//field_map_matrix[row3][col].setIsCliff(field_map_matrix[row][col].getBlock(block_index) == Block::cliff); // どこが崖になっているか調べる
						//if (field_map_matrix[row][col].getBlock(block_index) != Block::empty) {
						//	field_map_matrix[row3][col].setDrawBlock(field_map_matrix[row][col].getBlock(block_index)); // ブロックを格納
						//}
						if (row3 == 0) break;
					}

					const As::Int32 row2 = As::Int32(row) - As::Int32(field_map_matrix[row][col].getBlockElevation());
					if (row2 >= 0) {
							field_map_matrix[row2][col].setColor(field_map_matrix[row][col].getColor());
						field_map_matrix[row2][col].setDrawBiome(field_map_matrix[row][col].getBiome());
					}

				}
			// 崖のオートタイルを計算
			for (::As::IndexUint col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::As::IndexUint row{}; row < init_field_map_height - 1; ++row) {
					field_map_matrix[row][col].setCliff(
						getHomogeneousConnectionCliff(
							field_map_matrix[row][col - 1].getIsCliff() || ((!field_map_matrix[row][col - 1].getIsCliff()) && field_map_matrix[row][col].getElevation3() < field_map_matrix[row][col - 1].getElevation3())
							, field_map_matrix[row][col + 1].getIsCliff() || ((!field_map_matrix[row][col + 1].getIsCliff()) && field_map_matrix[row][col].getElevation3() < field_map_matrix[row][col + 1].getElevation3())
							, field_map_matrix[row + 1][col].getIsCliff()
						)
					);
				}

			for (::As::IndexUint col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::As::IndexUint row{ 1 }; row < init_field_map_height - 1; ++row) {
					if (field_map_matrix[row][col].getIsCliff()) continue;
					// 崖上のオートタイルを計算 ( 一部バグがあり、未完成 )
					field_map_matrix[row][col].setCliffTop(
						getHomogeneousConnectionValueElevation3(
							field_map_matrix[row][col].getElevation3()
							, field_map_matrix[row - 1][col].getElevation3()
							, field_map_matrix[row][col - 1].getElevation3()
							, field_map_matrix[row][col + 1].getElevation3()
							, field_map_matrix[row + 1][col].getElevation3()
							, field_map_matrix[row - 1][col - 1].getElevation3()
							, field_map_matrix[row - 1][col + 1].getElevation3()
							, field_map_matrix[row + 1][col - 1].getElevation3()
							, field_map_matrix[row + 1][col + 1].getElevation3()
						));
					// ウディタ規格オートタイルの計算
					// 同質接続の条件：同じバイオーム＆同じ標高＆崖ではない
					field_map_matrix[row][col].setBiomeAutoTile(
						getHomogeneousConnectionAutoTile(
							field_map_matrix[row - 1][col].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row - 1][col].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col].getIsCliff())
							, field_map_matrix[row][col - 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row][col - 1].getIsCliff())
							, field_map_matrix[row][col + 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row][col + 1].getIsCliff())
							, field_map_matrix[row + 1][col].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row + 1][col].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col].getIsCliff())
							, field_map_matrix[row - 1][col - 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row - 1][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col - 1].getIsCliff())
							, field_map_matrix[row - 1][col + 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row - 1][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col + 1].getIsCliff())
							, field_map_matrix[row + 1][col - 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row + 1][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col - 1].getIsCliff())
							, field_map_matrix[row + 1][col + 1].getDrawBiome() == field_map_matrix[row][col].getDrawBiome() && field_map_matrix[row + 1][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col + 1].getIsCliff())
						)
					);
					// ウディタ規格オートタイルの計算
					// 同質接続の条件：同じバイオーム＆同じ標高＆崖ではない
					field_map_matrix[row][col].setAutoTile(
						getHomogeneousConnectionAutoTile(
							field_map_matrix[row - 1][col].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row - 1][col].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col].getIsCliff())
							, field_map_matrix[row][col - 1].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row][col - 1].getIsCliff())
							, field_map_matrix[row][col + 1].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row][col + 1].getIsCliff())
							, field_map_matrix[row + 1][col].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row + 1][col].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col].getIsCliff())
							, field_map_matrix[row - 1][col - 1].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row - 1][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col - 1].getIsCliff())
							, field_map_matrix[row - 1][col + 1].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row - 1][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row - 1][col + 1].getIsCliff())
							, field_map_matrix[row + 1][col - 1].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row + 1][col - 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col - 1].getIsCliff())
							, field_map_matrix[row + 1][col + 1].getDrawBlock() == field_map_matrix[row][col].getDrawBlock() && field_map_matrix[row + 1][col + 1].getElevation3() == field_map_matrix[row][col].getElevation3() && (!field_map_matrix[row + 1][col + 1].getIsCliff())
						)
					);
				}
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

		// フィールドマップを生成
		void generation(MapMat& field_map_matrix, TerrainNoise& terrain_noise_, const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_, const ::As::Uint32 start_x_, const ::As::Uint32 start_y_, const ::As::Uint32 end_x_, const ::As::Uint32 end_y_) const {

			const ElevationUint sea_elevation = 110;

			terrain_noise_.generation(field_map_matrix, terrain_noise_, chunk_index_x_, chunk_index_y_, start_x_, start_y_, end_x_, end_y_);

			XorShift32 xs32(terrain_noise_.getElevationSeed());

			//バイオームの分類分け
			for (::As::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::As::IndexUint col{ start_x_ }; col < end_x_; ++col) {
					MapChip& field_map = field_map_matrix[row][col];

					field_map.setTemperature(field_map.getTemperature() - field_map.getElevation() / 2);
					const ElevationUint temperature = field_map.getTemperature();
					const ElevationUint elevation = field_map.getElevation();
					const ElevationUint amount_of_rainfall = field_map.getAmountOfRainfall();

					if (elevation < sea_elevation) {
						field_map.setBiome(MapChipTypeBiome::sea);
					}
					else
						if (temperature < 45) field_map.setBiome(MapChipTypeBiome::rock);
						else if (amount_of_rainfall < 25) field_map.setBiome(MapChipTypeBiome::savannah);
						else if (amount_of_rainfall < 75) {
							if (temperature < 120) field_map.setBiome(MapChipTypeBiome::desert);
							else field_map.setBiome(MapChipTypeBiome::desert);
						}
						else if (temperature < 69) field_map.setBiome(MapChipTypeBiome::grass);
						else if (temperature < 96) field_map.setBiome(MapChipTypeBiome::normal);
						else if (temperature < 120) field_map.setBiome(MapChipTypeBiome::forest);
						else if (amount_of_rainfall < 125) field_map.setBiome(MapChipTypeBiome::mountain);
						else if (temperature < 132) field_map.setBiome(MapChipTypeBiome::mountain);
						else field_map.setBiome(MapChipTypeBiome::mountain);

					for (As::IndexUint i = 0; i < elevation / 2; ++i) {
						field_map.setBlock(Block::cliff, i);
					}
					for (As::IndexUint i = elevation / 2 + 1; i < 128; ++i) {
						field_map.setBlock(Block::empty, i); // からの場合 ( 崖上を除く )
					}
					field_map.setBlock(Block::cliff_top, elevation / 2); // からだけど崖上の場合

					// 海
					if (field_map.getBiome() == MapChipTypeBiome::sea) {
						field_map.setElevation(sea_elevation);
						field_map.setBlockElevation(sea_elevation / 2);

						for (As::IndexUint i = elevation / 2; i <= sea_elevation / 2; ++i) {
							field_map.setBlock(Block::water_ground, i);
						}
					}
					else {
						field_map.setBlockElevation(elevation / 2);

						//// 草花の生成テスト
						//switch (xs32.getProbabilityDivision(0.1, 4)) {
						//case 0:
						//	field_map.setBlock(Block::grass_1, elevation / 2); // テスト
						//	break;
						//case 1:
						//	field_map.setBlock(Block::grass_2, elevation / 2); // テスト
						//	break;
						//case 2:
						//	field_map.setBlock(Block::grass_3, elevation / 2); // テスト
						//	break;
						//case 3:
						//	field_map.setBlock(Block::grass_4, elevation / 2); // テスト
						//	break;
						//case 4:
						//	field_map.setBlock(Block::flower_1, elevation / 2); // テスト
						//	break;
						//case 5:
						//	field_map.setBlock(Block::flower_2, elevation / 2); // テスト
						//	break;
						//case 6:
						//	field_map.setBlock(Block::flower_3, elevation / 2); // テスト
						//	break;
						//case 7:
						//	field_map.setBlock(Block::flower_4, elevation / 2); // テスト
						//	break;
						//}



						if (amount_of_rainfall > 120 && elevation > sea_elevation) {
							if ((field_map.getLake()) > 150) {
								field_map.setBlock(Block::water_ground_2, elevation / 2); // テスト
							}
							else {
								// 草花の生成テスト
								switch (field_map.getFlower()) {
								case 150:
								case 160:
									field_map.setBlock(Block::grass_1, elevation / 2); // テスト
									break;
								case 151:
								case 161:
									field_map.setBlock(Block::grass_2, elevation / 2); // テスト
									break;
								case 152:
								case 162:
									field_map.setBlock(Block::grass_3, elevation / 2); // テスト
									break;
								case 153:
								case 163:
									field_map.setBlock(Block::grass_4, elevation / 2); // テスト
									break;
								case 154:
								case 164:
									field_map.setBlock(Block::flower_1, elevation / 2); // テスト
									break;
								case 155:
								case 165:
									field_map.setBlock(Block::flower_2, elevation / 2); // テスト
									break;
								case 156:
								case 166:
									field_map.setBlock(Block::flower_3, elevation / 2); // テスト
									break;
								case 157:
								case 167:
									field_map.setBlock(Block::flower_4, elevation / 2); // テスト
									break;
								case 158:
								case 168:
									field_map.setBlock(Block::house_wall_1_up, elevation / 2 + 1); // テスト
									field_map.setBlock(Block::house_wall_1_down, elevation / 2); // テスト
									break;
								}
							}
						}
						else {

							if (field_map.getBiome() == ::Crafterra::MapChipTypeBiome::forest) {
								// 草花の生成テスト
								switch (field_map.getFlower()) {
								case 100:
									field_map.setBlock(Block::grass_1, elevation / 2); // テスト
									break;
								case 101:
									field_map.setBlock(Block::grass_2, elevation / 2); // テスト
									break;
								case 102:
									field_map.setBlock(Block::grass_3, elevation / 2); // テスト
									break;
								case 103:
									field_map.setBlock(Block::grass_4, elevation / 2); // テスト
									break;
								case 104:
									field_map.setBlock(Block::flower_1, elevation / 2); // テスト
									break;
								case 105:
									field_map.setBlock(Block::flower_2, elevation / 2); // テスト
									break;
								case 106:
									field_map.setBlock(Block::flower_3, elevation / 2); // テスト
									break;
								case 107:
									field_map.setBlock(Block::flower_4, elevation / 2); // テスト
									break;
								}
								if (field_map.getFlower() > 130) {
									field_map.setBlock(Block::house_wall_1_up, elevation / 2 + 1); // テスト
									field_map.setBlock(Block::house_wall_1_down, elevation / 2); // テスト
								}
							}
							else {
								// 草花の生成テスト
								switch (field_map.getFlower()) {
								case 150:
									field_map.setBlock(Block::grass_1, elevation / 2); // テスト
									break;
								case 151:
									field_map.setBlock(Block::grass_2, elevation / 2); // テスト
									break;
								case 152:
									field_map.setBlock(Block::grass_3, elevation / 2); // テスト
									break;
								case 153:
									field_map.setBlock(Block::grass_4, elevation / 2); // テスト
									break;
								case 154:
									field_map.setBlock(Block::flower_1, elevation / 2); // テスト
									break;
								case 155:
									field_map.setBlock(Block::flower_2, elevation / 2); // テスト
									break;
								case 156:
									field_map.setBlock(Block::flower_3, elevation / 2); // テスト
									break;
								case 157:
									field_map.setBlock(Block::flower_4, elevation / 2); // テスト
									break;
								case 158:
									field_map.setBlock(Block::house_wall_1_up, elevation / 2 + 1); // テスト
									field_map.setBlock(Block::house_wall_1_down, elevation / 2); // テスト
									break;
								}
							}
						}
					}

					

				}
		}
		void initialGeneration(MapMat& field_map_matrix_, TerrainNoise& terrain_noise_, const ::As::Uint32 chunk_index_x_, const ::As::Uint32 chunk_index_y_) const {
			generation(field_map_matrix_, terrain_noise_, chunk_index_x_, chunk_index_y_, 0, 0, init_field_map_width, init_field_map_height);
		}

	};

}

#endif //Included Crafterra Library