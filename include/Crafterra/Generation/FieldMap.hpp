﻿/*##########################################################################################

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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_FIELD_MAP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_FIELD_MAP_HPP

#include <AsLib2/DataType/ArrayDataType.hpp>
#include <Crafterra/Map/MapChip.hpp>

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

#include <memory>
#include <Crafterra/Macro/New.hpp> // CRAFTERRA_NEW

#include <Crafterra/Map/HomogeneousConnection.hpp>


// 地形生成用 ( 後に削除予定 )
#include <DTL/Utility/PerlinNoise.hpp>

namespace Crafterra {

	unsigned int getDxColor(const int r_, const int g_, const int b_) {
		return (r_ * 256 + g_) * 256 + b_;
	}

	template<typename Matrix_>
	void perlinNoise(
		const Matrix_& matrix_,
		const ::As::DataType::Uint32 chunk_index_x_, const ::As::DataType::Uint32 chunk_index_y_, const As::DataType::IndexUint one_chunk_width_, const As::DataType::IndexUint one_chunk_height_,
		const As::DataType::IndexUint start_x_, const As::DataType::IndexUint start_y_, const As::DataType::IndexUint end_x_, const As::DataType::IndexUint end_y_,
		::dtl::utility::PerlinNoise<double>& perlin, const double frequency_, const As::DataType::IndexUint octaves_,
		const ElevationUint max_height_, const ElevationUint min_height_ = 0) {

		for (As::DataType::IndexUint row_index{ start_y_ }, row{}; row_index < end_y_; ++row_index, ++row)
			for (As::DataType::IndexUint col_index{ start_x_ }, col{}; col_index < end_x_; ++col_index, ++col)
				matrix_(col_index, row_index,
				min_height_ + static_cast<ElevationUint>(
				(max_height_ - min_height_) *
					perlin.octaveNoise(octaves_,
					(::As::DataType::Uint64(chunk_index_x_) * ::As::DataType::Uint64(one_chunk_width_) + ::As::DataType::Uint64(col)) / frequency_,
						((::As::DataType::Uint64(chunk_index_y_) * ::As::DataType::Uint64(one_chunk_height_) + ::As::DataType::Uint64(row)) / frequency_)
					)
					));
	}

	class XorShift32 {
	private:
		::As::DataType::Uint32 seed;
	public:
		::As::DataType::Uint32 getRand() {
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
		As::DataType::Int32 getProbabilityDivision(const double probability_, const As::DataType::Int32 division_) {
			if (probability_ <= getRand2() || division_ <= 0) return -1;
			return (getRand2() / probability_ * double(division_));
		}
		void setSeed(const ::As::DataType::Uint32 seed_) {
			seed = seed_;
		}
		XorShift32(const ::As::DataType::Uint32 seed_) : seed(seed_) {}
	};


	class Terrain {

		// 暫定的なマップデータ
		using MapMat = ::As::DataType::Matrix<MapChip, init_field_map_width, init_field_map_height>;
		using shape_t = ElevationUint;

		::As::DataType::Uint32 temperature_seed;
		::As::DataType::Uint32 amount_of_rainfall_seed;
		::As::DataType::Uint32 elevation_seed;

		::dtl::utility::PerlinNoise<double> perlin_temperature_seed;
		::dtl::utility::PerlinNoise<double> perlin_amount_of_rainfall_seed;
		::dtl::utility::PerlinNoise<double> perlin_elevation_seed;

	public:

		Terrain(const ::As::DataType::Uint32 temperature_seed_, const ::As::DataType::Uint32 amount_of_rainfall_seed_, const ::As::DataType::Uint32 elevation_seed_)
			:
			  temperature_seed(temperature_seed_)
			, amount_of_rainfall_seed(amount_of_rainfall_seed_)
			, elevation_seed(elevation_seed_)
			, perlin_temperature_seed(temperature_seed_)
			, perlin_amount_of_rainfall_seed(amount_of_rainfall_seed_)
			, perlin_elevation_seed(elevation_seed_) {}

		void setTerrain(MapMat& field_map_matrix) const {


			//std::random_device seed_gen;
			//std::mt19937 engine(seed_gen());
			//std::bernoulli_distribution uid(0.01);

			for (::As::DataType::IndexUint row{}; row < init_field_map_height; ++row)
				for (::As::DataType::IndexUint col{}; col < init_field_map_width; ++col) {
					MapChip& field_map = field_map_matrix[row][col];
					field_map.setElevation3(0); // 初期化

					ElevationUint elevation3 = 0;
					for (::As::DataType::IndexUint row3{ row }, block_index{}; elevation3 <= field_map.getBlockElevation() && block_index < 128; --row3, ++elevation3, ++block_index) {
						if (field_map_matrix[row3][col].getElevation3() < elevation3) field_map_matrix[row3][col].setElevation3(elevation3);
						field_map_matrix[row3][col].setIsCliff(field_map_matrix[row][col].getBlock(block_index) == Block::cliff); // どこが崖になっているか調べる
						if (field_map_matrix[row][col].getBlock(block_index)!=Block::empty) {
							field_map_matrix[row3][col].setDrawBlock(field_map_matrix[row][col].getBlock(block_index)); // ブロックを格納
						}
						if (row3 == 0) break;
					}

					switch (field_map.getBiome()) {
					case MapChipTypeBiome::sea:
						field_map.setColor(getDxColor(33, 97, 124));
						break;
					case MapChipTypeBiome::lake:
						field_map.setColor(getDxColor(88, 124, 139));
						break;
					case MapChipTypeBiome::mountain:
						field_map.setColor(getDxColor(101, 100, 60));
						break;
					case MapChipTypeBiome::desert:
						field_map.setColor(getDxColor(217, 195, 143));
						break;
					case MapChipTypeBiome::forest:
						field_map.setColor(getDxColor(110, 149, 59));
						break;
					case MapChipTypeBiome::rock:
						field_map.setColor(getDxColor(120, 125, 108));
						break;
					case MapChipTypeBiome::hill:
						field_map.setColor(getDxColor(145, 177, 113));
						break;
					case MapChipTypeBiome::savannah:
						field_map.setColor(getDxColor(144, 140, 73));
						break;
					case MapChipTypeBiome::grass:
						field_map.setColor(getDxColor(90, 128, 63));
						break;
					case MapChipTypeBiome::wall:
						field_map.setColor(getDxColor(200, 200, 200));
						break;
					case MapChipTypeBiome::way:
						field_map.setColor(getDxColor(90, 128, 63));
						break;
					case MapChipTypeBiome::room:
						field_map.setColor(getDxColor(50, 160, 70));
						break;
					case MapChipTypeBiome::normal:
						field_map.setColor(getDxColor(170, 160, 70));
						break;
					}

					const As::DataType::Int32 row2 = As::DataType::Int32(row) - As::DataType::Int32(field_map_matrix[row][col].getBlockElevation());
					if (row2 >= 0) {
						//if (!field_map_matrix[row][col].getIsCliff())
							//field_map_matrix[row2][col].setDrawChip(field_map_matrix[row][col].getDrawChip());
							field_map_matrix[row2][col].setColor(field_map_matrix[row][col].getColor());
						field_map_matrix[row2][col].setDrawBiome(field_map_matrix[row][col].getBiome());
					}

				}
			// どこが崖になっているか調べる
			//for (::As::DataType::IndexUint col{}; col < init_field_map_width; ++col)
			//	for (::As::DataType::IndexUint row{ 1 }; row < init_field_map_height; ++row) {
			//			field_map_matrix[row][col].setIsCliff(field_map_matrix[row][col].getElevation3() < field_map_matrix[row - 1][col].getElevation3()); // 崖
			//	}
			// 崖のオートタイルを計算
			for (::As::DataType::IndexUint col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::As::DataType::IndexUint row{}; row < init_field_map_height - 1; ++row) {
					field_map_matrix[row][col].setCliff(
						getHomogeneousConnectionCliff(
							field_map_matrix[row][col - 1].getIsCliff() || ((!field_map_matrix[row][col - 1].getIsCliff()) && field_map_matrix[row][col].getElevation3() < field_map_matrix[row][col - 1].getElevation3())
							, field_map_matrix[row][col + 1].getIsCliff() || ((!field_map_matrix[row][col + 1].getIsCliff()) && field_map_matrix[row][col].getElevation3() < field_map_matrix[row][col + 1].getElevation3())
							, field_map_matrix[row + 1][col].getIsCliff()
						)
					);
				}

			for (::As::DataType::IndexUint col{ 1 }; col < init_field_map_width - 1; ++col)
				for (::As::DataType::IndexUint row{ 1 }; row < init_field_map_height - 1; ++row) {
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
					field_map_matrix[row][col].setAutoTile(
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
					// オブジェクトの自動配置の実験
					// 海でも崖でもない時
					//if (field_map_matrix[row][col].getBiome() != MapChipTypeBiome::sea && (!field_map_matrix[row][col].getIsCliff())) {
					//	if (uid(engine)) {
					//		if (field_map_matrix[row][col].getBiome() == MapChipTypeBiome::default) {
					//			field_map_matrix[row][col].setDrawChip(52); // 花を設置
					//		}
					//		else {
					//			field_map_matrix[row][col].setDrawChip(64); // 石を設置
					//		}
					//	}
					//}
				}
		}

		void perlinNoiseGeneration(MapMat& field_map_matrix, const ::As::DataType::Uint32 chunk_index_x_, const ::As::DataType::Uint32 chunk_index_y_, const ::As::DataType::Uint32 start_x_, const ::As::DataType::Uint32 start_y_, const ::As::DataType::Uint32 end_x_, const ::As::DataType::Uint32 end_y_) {
			//温度
			perlinNoise(
				[&field_map_matrix](const As::DataType::IndexUint x_, const As::DataType::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setTemperature(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_temperature_seed, 200.0, 5,
				240, 100
			);

			//降水量
			perlinNoise(
				[&field_map_matrix](const As::DataType::IndexUint x_, const As::DataType::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setAmountOfRainfall(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_amount_of_rainfall_seed, 200.0, 5,
				225, 0
			);

			//標高
			perlinNoise(
				[&field_map_matrix](const As::DataType::IndexUint x_, const As::DataType::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setElevation(value_); },
				chunk_index_x_, chunk_index_y_, init_field_map_width / 2, init_field_map_height / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_elevation_seed, 300.0, 8,
				195, 0
			);
		}

		// フィールドマップの下半分の地形が上半分へ移動する
		void moveUpTerrain(MapMat& field_map_matrix, const ::As::DataType::Uint32 field_height_half_) const {
			for (::As::DataType::IndexUint row{}; row < field_height_half_; ++row)
				for (::As::DataType::IndexUint col{}; col < init_field_map_width; ++col) {
					MapChip& field_map_after = field_map_matrix[row][col];
					const MapChip& field_map_before = field_map_matrix[row + field_height_half_][col];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの上半分の地形が下半分へ移動する
		void moveDownTerrain(MapMat& field_map_matrix, const ::As::DataType::Uint32 field_height_half_) const {
			for (::As::DataType::IndexUint row{}; row < field_height_half_; ++row)
				for (::As::DataType::IndexUint col{}; col < init_field_map_width; ++col) {
					MapChip& field_map_after = field_map_matrix[row + field_height_half_][col];
					const MapChip& field_map_before = field_map_matrix[row][col];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの右半分の地形が左半分へ移動する
		void moveLeftTerrain(MapMat& field_map_matrix, const ::As::DataType::Uint32 field_width_half_) const {
			for (::As::DataType::IndexUint row{}; row < init_field_map_height; ++row)
				for (::As::DataType::IndexUint col{}; col < field_width_half_; ++col) {
					MapChip& field_map_after = field_map_matrix[row][col];
					const MapChip& field_map_before = field_map_matrix[row][col + field_width_half_];
					field_map_after = field_map_before;
				}
		}
		// フィールドマップの左半分の地形が右半分へ移動する
		void moveRightTerrain(MapMat& field_map_matrix, const ::As::DataType::Uint32 field_width_half_) const {
			for (::As::DataType::IndexUint row{}; row < init_field_map_height; ++row)
				for (::As::DataType::IndexUint col{}; col < field_width_half_; ++col) {
					MapChip& field_map_after = field_map_matrix[row][col + field_width_half_];
					const MapChip& field_map_before = field_map_matrix[row][col];
					field_map_after = field_map_before;
				}
		}

		// フィールドマップを生成
		void generation(MapMat& field_map_matrix, const ::As::DataType::Uint32 chunk_index_x_, const ::As::DataType::Uint32 chunk_index_y_, const ::As::DataType::Uint32 start_x_, const ::As::DataType::Uint32 start_y_, const ::As::DataType::Uint32 end_x_, const ::As::DataType::Uint32 end_y_) {

			const ElevationUint sea_elevation = 110;

			perlinNoiseGeneration(field_map_matrix, chunk_index_x_, chunk_index_y_, start_x_, start_y_, end_x_, end_y_);

			XorShift32 xs32(elevation_seed);

			//バイオームの分類分け
			for (::As::DataType::IndexUint row{ start_y_ }; row < end_y_; ++row)
				for (::As::DataType::IndexUint col{ start_x_ }; col < end_x_; ++col) {
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

					for (As::DataType::IndexUint i = 0; i < elevation / 2; ++i) {
						field_map.setBlock(Block::cliff, i);
					}
					for (As::DataType::IndexUint i = elevation / 2 + 1; i < 128; ++i) {
						field_map.setBlock(Block::empty, i); // からの場合 ( 崖上を除く )
					}
					field_map.setBlock(Block::cliff_top, elevation / 2); // からだけど崖上の場合

					// 海
					if (field_map.getBiome() == MapChipTypeBiome::sea) {
						field_map.setElevation(sea_elevation);
						field_map.setBlockElevation(sea_elevation / 2);

						for (As::DataType::IndexUint i = elevation / 2; i <= sea_elevation / 2; ++i) {
							field_map.setBlock(Block::water_ground, i);
						}
					}
					else {
						field_map.setBlockElevation(elevation / 2);

						// 草花の生成テスト
						switch (xs32.getProbabilityDivision(0.1, 4)) {
						case 0:
							field_map.setBlock(Block::grass_1, elevation / 2); // テスト
							break;
						case 1:
							field_map.setBlock(Block::grass_2, elevation / 2); // テスト
							break;
						case 2:
							field_map.setBlock(Block::grass_3, elevation / 2); // テスト
							break;
						case 3:
							field_map.setBlock(Block::grass_4, elevation / 2); // テスト
							break;
						case 4:
							field_map.setBlock(Block::flower_1, elevation / 2); // テスト
							break;
						case 5:
							field_map.setBlock(Block::flower_2, elevation / 2); // テスト
							break;
						case 6:
							field_map.setBlock(Block::flower_3, elevation / 2); // テスト
							break;
						case 7:
							field_map.setBlock(Block::flower_4, elevation / 2); // テスト
							break;
						}
					}

					

				}
			setTerrain(field_map_matrix);
		}
		void initialGeneration(MapMat& field_map_matrix_) {
			generation(field_map_matrix_, 0, 0, 0, 0, init_field_map_width, init_field_map_height);
		}
		void initialGeneration(MapMat& field_map_matrix_, const ::As::DataType::Uint32 chunk_index_x_, const ::As::DataType::Uint32 chunk_index_y_) {
			generation(field_map_matrix_, chunk_index_x_, chunk_index_y_, 0, 0, init_field_map_width, init_field_map_height);
		}

	};

}

#endif //Included Crafterra Library