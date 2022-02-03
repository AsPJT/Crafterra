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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_GENERATION_PERLIN_NOISE_ON_FIELD_MAP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_GENERATION_PERLIN_NOISE_ON_FIELD_MAP_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp> // int
#include <algorithm>
#include <random>

namespace Crafterra {

	// パーリンノイズをフィールドマップ上に生成
	template<typename Matrix_, typename ElevationUint_>
	void generatePerlinNoiseOnFieldMap(
		const Matrix_& matrix_,
		const ::As::IndexUint chunk_index_x_, const ::As::IndexUint chunk_index_y_, const As::IndexUint one_chunk_width_, const As::IndexUint one_chunk_height_,
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



	class PerlinNoiseOnFieldMap {
		// 暫定的なマップデータ
		using MapMat = ::As::UniquePtrMatrix<MapChip>;
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
		PerlinNoiseOnFieldMap(const ::As::Uint32 temperature_seed_, const ::As::Uint32 amount_of_rainfall_seed_, const ::As::Uint32 elevation_seed_, const ::As::Uint32 flower_seed_, const ::As::Uint32 lake_seed_)
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

	public:

		::As::Uint32 getElevationSeed() const { return this->elevation_seed; }

		void generation(MapMat& field_map_matrix, PerlinNoiseOnFieldMap& terrain_noise_, const ::As::IndexUint chunk_index_x_, const ::As::IndexUint chunk_index_y_, const ::As::IndexUint start_x_, const ::As::IndexUint start_y_, const ::As::IndexUint end_x_, const ::As::IndexUint end_y_) {
			//温度
			generatePerlinNoiseOnFieldMap(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setTemperature(value_); },
				chunk_index_x_, chunk_index_y_, field_map_matrix.getWidth() / 2, field_map_matrix.getHeight() / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_temperature_seed, 400.1, 8,
				240, 0
			);

			//降水量
			generatePerlinNoiseOnFieldMap(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setAmountOfRainfall(value_); },
				chunk_index_x_, chunk_index_y_, field_map_matrix.getWidth() / 2, field_map_matrix.getHeight() / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_amount_of_rainfall_seed, 400.1, 8,
				240, 0
			);

			//標高
			generatePerlinNoiseOnFieldMap(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setElevation(value_); },
				chunk_index_x_, chunk_index_y_, field_map_matrix.getWidth() / 2, field_map_matrix.getHeight() / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_elevation_seed, 600.1, 10,
				240, 0
			);

			//花
			generatePerlinNoiseOnFieldMap(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const double value_) { field_map_matrix[y_][x_].setFlower(value_); },
				chunk_index_x_, chunk_index_y_, field_map_matrix.getWidth() / 2, field_map_matrix.getHeight() / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_flower_seed, 1.12345, 1,
				1.0, 0.0
			);

			//湖
			generatePerlinNoiseOnFieldMap(
				[&field_map_matrix](const As::IndexUint x_, const As::IndexUint y_, const ElevationUint value_) { field_map_matrix[y_][x_].setLake(value_); },
				chunk_index_x_, chunk_index_y_, field_map_matrix.getWidth() / 2, field_map_matrix.getHeight() / 2,
				start_x_, start_y_, end_x_, end_y_,
				perlin_lake_seed, 10.12345, 3,
				200, 50
			);
		}
	};

}

#endif //Included Crafterra Library