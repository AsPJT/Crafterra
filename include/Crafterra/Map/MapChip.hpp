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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_MAP_CHIP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_MAP_CHIP_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>
#include <Crafterra/DataType/ArrayDataType.hpp>
#include <Crafterra/DataType/StringDataType.hpp>

#include <Crafterra/Enum/CrafterraEnum.hpp>

namespace Crafterra {

	// バイオームの種類
	enum MapChipTypeBiome : BiomeType {
		map_chip_type_biome_empty     // 無し
		, map_chip_type_biome_sea        // 海
		, map_chip_type_biome_lake       // 湖
		, map_chip_type_biome_mountain // 山
		, map_chip_type_biome_desert    // 砂漠
		, map_chip_type_biome_forest    // 森林
		, map_chip_type_biome_rock      // 岩山
		, map_chip_type_biome_hill       // 丘
		, map_chip_type_biome_savannah // サバンナ
		, map_chip_type_biome_grass     // 草原
		, map_chip_type_biome_wall     // 草原
		, map_chip_type_biome_way     // 草原
		, map_chip_type_biome_room     // 草原
		, map_chip_type_biome_default   // 通常の地面
		, map_chip_type_biome_size   // バイオームの数
	};
//#if (__cplusplus < 202002L)
//	::Crafterra::DataType::Array<::Crafterra::DataType::String, map_chip_type_biome_size>
//		MapChipTypeBiomeString{ {
//				u8"無し",u8"海",u8"湖",u8"山",u8"砂漠",u8"森林",u8"岩山",u8"丘",u8"サバンナ",u8"草原",u8"壁",u8"道",u8"部屋",u8"通常"
//	} };
//#else
	::Crafterra::DataType::Array<::Crafterra::DataType::String, map_chip_type_biome_size>
		MapChipTypeBiomeString{ {
				"無し","海","湖","山","砂漠","森林","岩山","丘","サバンナ","草原","壁","道","部屋","通常"
	} };
//#endif

	// 148,185,32
	// 110,163,0
	// 170,212,43
	// 127,145,72
	// 201,196,119
	// 151,130,73
	// 234,226,135
	// 176,186,163

	// マップチップ情報を管理
	class MapChip {
	private:
		// ---------- 元の座標系 ----------

		::Crafterra::Color::Color3 rgb{}; // マップチップの色
		BiomeType biome{ map_chip_type_biome_empty }; // バイオーム
		BlockType block{}; // ブロック
		ElevationUint block_elevation{}; // ブロックの高さに合わせた標高値

		ElevationUint elevation{}; // 元の標高値
		ElevationUint temperature{}; // 気温
		ElevationUint amount_of_rainfall{}; // 降水量

		// ---------- 描画座標系 ----------

		MapChipTypeHomogeneousConnection cliff_top{ map_chip_type_homogeneous_connection_size }; // 崖上タイルの種類
		MapChipTypeHomogeneousConnection cliff{ map_chip_type_homogeneous_connection_size }; // 崖タイルの種類
		bool is_cliff = false;
		ElevationUint elevation3{}; // カメラの位置にずらした、ブロックの高さに合わせた標高値
		BiomeType draw_biome{ map_chip_type_biome_empty }; // 描画用バイオーム
		AutoTile auto_tile{}; // 描画用オートタイル
		int draw_chip = -1;

	public:

		void clearDrawValue() {
			cliff_top = map_chip_type_homogeneous_connection_size;
			cliff = map_chip_type_homogeneous_connection_size;
			is_cliff = false;

			// elevation = {}; // 元の標高値
			// block_elevation = {}; // ブロックの高さに合わせた標高値
			elevation3 = {}; // カメラの位置にずらした、ブロックの高さに合わせた標高値
			auto_tile = {};
			draw_chip = -1;
		}


		void setDrawChip(const int draw_chip_) {
			this->draw_chip = draw_chip_;
		}
		void setDrawChip() {
			if (block == 0) {
				if (biome == 0) {
					draw_chip = -1;
				}
				switch (biome)
				{
				case map_chip_type_biome_empty:
					draw_chip = -1;
					break;
				case map_chip_type_biome_default:
					draw_chip = 0;
					break;
				case map_chip_type_biome_forest:
					draw_chip = 1;
					break;
				case map_chip_type_biome_rock:
					draw_chip = 7;
					break;
				case map_chip_type_biome_mountain:
					draw_chip = 5;
					break;
				case map_chip_type_biome_desert:
					draw_chip = 6;
					break;
				}

			}
		}
		int getDrawChip() const {
			return this->draw_chip;
		}

		::Crafterra::Color::Color3 getColor() const {
			return this->rgb;
		}
		void setColor(const ::Crafterra::Color::Color3& rgb_) {
			this->rgb = rgb_;
		}
		BiomeType getBiome() const {
			return this->biome;
		}
		void setBiome(const BiomeType& biome_) {
			this->biome = biome_;
		}
		BiomeType getDrawBiome() const {
			return this->draw_biome;
		}
		void setDrawBiome(const BiomeType& draw_biome_) {
			this->draw_biome = draw_biome_;
		}
		BlockType getBlock() const {
			return this->block;
		}
		void setBlock(const BlockType& block_) {
			this->block = block_;
		}
		ElevationUint getElevation() const {
			return this->elevation;
		}
		void setElevation(const ElevationUint& elevation_) {
			this->elevation = elevation_;
		}
		ElevationUint getTemperature() const {
			return this->temperature;
		}
		void setTemperature(const ElevationUint& temperature_) {
			this->temperature = temperature_;
		}
		ElevationUint getAmountOfRainfall() const {
			return this->amount_of_rainfall;
		}
		void setAmountOfRainfall(const ElevationUint& amount_of_rainfall_) {
			this->amount_of_rainfall = amount_of_rainfall_;
		}
		ElevationUint getBlockElevation() const {
			return this->block_elevation;
		}
		void setBlockElevation(const ElevationUint& elevation_) {
			this->block_elevation = elevation_;
		}
		// 暫定
		ElevationUint getElevation3() const {
			return this->elevation3;
		}
		void setElevation3(const ElevationUint& elevation_) {
			this->elevation3 = elevation_;
		}


		// 暫定
		MapChipTypeHomogeneousConnection getCliffTop() const {
			return this->cliff_top;
		}
		void setCliffTop(const MapChipTypeHomogeneousConnection& cliff_top_) {
			this->cliff_top = cliff_top_;
		}
		MapChipTypeHomogeneousConnection getCliff() const {
			return this->cliff;
		}
		void setCliff(const MapChipTypeHomogeneousConnection& cliff_) {
			this->cliff = cliff_;
		}
		// 崖であるかどうか？
		bool getIsCliff() const {
			return this->is_cliff;
		}
		void setIsCliff(const bool is_cliff_) {
			this->is_cliff = is_cliff_;
		}
		// オートタイル
		AutoTile getAutoTile() const {
			return this->auto_tile;
		}
		void setAutoTile(const AutoTile& auto_tile_) {
			this->auto_tile = auto_tile_;
		}

	};

}

#endif //Included Crafterra Library