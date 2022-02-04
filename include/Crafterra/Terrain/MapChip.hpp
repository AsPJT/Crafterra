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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_MAP_CHIP_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_MAP_CHIP_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>
#include <AsLib2/DataType/ArrayDataType.hpp>
#include <AsLib2/DataType/StringDataType.hpp>

#include <Crafterra/Enum/CrafterraEnum.hpp>

namespace Crafterra {

	// バイオームの種類
	enum class MapChipTypeBiome : BiomeType {
		empty     // 無し
		, sea        // 海
		, lake       // 湖
		, tundra    // ツンドラ
		, mountain // 山
		, desert    // 砂漠
		, forest    // 森林
		, rock      // 岩山
		, hill       // 丘
		, savannah // サバンナ
		, grass     // 草原
		, wall     // 草原
		, way     // 草原
		, room     // 草原
		, normal   // 通常の地面
		, size   // バイオームの数
	};


	::As::Array<::As::String, As::IndexUint(MapChipTypeBiome::size)>
		MapChipTypeBiomeString{ {
				"Empty","Sea","Lake","Tundra","Mountain","Desert","Forest","Rock","Hill","Savannah","Grass","Wall","Way","Room","Normal"
	} };

	//#if (__cplusplus < 202002L)
	//	::Crafterra::DataType::Array<::As::String, MapChipTypeBiome::size>
	//		MapChipTypeBiomeString{ {
	//				u8"無し",u8"海",u8"湖",u8"山",u8"砂漠",u8"森林",u8"岩山",u8"丘",u8"サバンナ",u8"草原",u8"壁",u8"道",u8"部屋",u8"通常"
	//	} };
	//#else
		//::Crafterra::DataType::Array<::As::String, As::IndexUint(MapChipTypeBiome::size)>
		//	MapChipTypeBiomeString{ {
		//			"無し","海","湖","山","砂漠","森林","岩山","丘","サバンナ","草原","壁","道","部屋","通常"
		//} };
	//#endif

		// 未完成
	enum class Block : BlockType {
		empty     // 無し
		, normal_ground        // 地面
		, water_ground       // 水
		, water_ground_2       // 水
		, running_water // 流水
		, waterfall    // 滝
		, cliff    // 崖
		, cliff_top      // 崖上
		, flower_1      // 花
		, flower_2      // 花
		, flower_3      // 花
		, flower_4      // 花
		, grass_1      // 草
		, grass_2      // 草
		, grass_3      // 草
		, grass_4      // 草
		, house_wall_1_up      // 家の壁
		, house_wall_1_down      // 家の壁
		, yellow_green_broadleaf_tree_up      // 黄緑色の広葉樹 上
		, yellow_green_broadleaf_tree_down   // 黄緑色の広葉樹 下
		, green_broadleaf_tree_up      // 緑色の広葉樹 上
		, green_broadleaf_tree_down   // 緑色の広葉樹 下
		, yellow_broadleaf_tree_up      // 黄色の広葉樹 上
		, yellow_broadleaf_tree_down   // 黄色の広葉樹 下
		, red_broadleaf_tree_up      // 赤色の広葉樹 上
		, red_broadleaf_tree_down   // 赤色の広葉樹 下
		, deciduous_tree_up      // 落葉樹 上
		, deciduous_tree_down   // 落葉樹 下
		, yellow_green_coniferous_tree_up      // 黄緑色の針葉樹 上
		, yellow_green_coniferous_tree_down   // 黄緑色の針葉樹 下
		, green_coniferous_tree_up      // 緑色の針葉樹 上
		, green_coniferous_tree_down   // 緑色の針葉樹 下
		, b      // 家の壁
		, cultivated_land      // 畑
		, planted_carrot      // ニンジン
		, size   // ブロックの数
	};

	// 148,185,32
	// 110,163,0
	// 170,212,43
	// 127,145,72
	// 201,196,119
	// 151,130,73
	// 234,226,135
	// 176,186,163

	// 描画用マップチップ
	class DrawMapChipUnit {
	private:
		// ---------- 描画座標系 ----------

		::As::IndexUint field_map_x{};
		::As::IndexUint field_map_y{};
		::As::IndexUint field_map_z{};

		CliffConnection cliff_top{ CliffConnection::size }; // 崖上タイルの種類
		CliffConnection cliff{ CliffConnection::size }; // 崖タイルの種類
		bool is_cliff = false;
		bool is_cliff_top = false;
		Block draw_block{}; // 後に配列になる予定
		ElevationUint elevation{}; // カメラの位置にずらした、ブロックの高さに合わせた標高値
		MapChipTypeBiome draw_biome{ MapChipTypeBiome::empty }; // 描画用バイオーム
		AutoTile auto_tile{}; // 描画用オートタイル
		AutoTile biome_auto_tile{}; // 描画用オートタイル

	public:

		::As::IndexUint getX() const { return this->field_map_x; }
		::As::IndexUint getY() const { return this->field_map_y; }
		::As::IndexUint getZ() const { return this->field_map_z; }
		void setX(const ::As::IndexUint x_) { this->field_map_x = x_; }
		void setY(const ::As::IndexUint y_) { this->field_map_x = y_; }
		void setZ(const ::As::IndexUint z_) { this->field_map_x = z_; }

		MapChipTypeBiome getDrawBiome() const {
			return this->draw_biome;
		}
		void setDrawBiome(const MapChipTypeBiome& draw_biome_) {
			this->draw_biome = draw_biome_;
		}
		Block getDrawBlock() const {
			return this->draw_block;
		}
		void setDrawBlock(const Block& block_) {
			this->draw_block = block_;
		}
		// 暫定
		ElevationUint getElevation3() const {
			return this->elevation;
		}
		void setElevation3(const ElevationUint& elevation_) {
			this->elevation = elevation_;
		}
		// 暫定
		CliffConnection getCliffTop() const {
			return this->cliff_top;
		}
		void setCliffTop(const CliffConnection& cliff_top_) {
			this->cliff_top = cliff_top_;
		}
		CliffConnection getCliff() const {
			return this->cliff;
		}
		void setCliff(const CliffConnection& cliff_) {
			this->cliff = cliff_;
		}
		// 崖であるかどうか？
		bool getIsCliff() const {
			return this->is_cliff;
		}
		void setIsCliff(const bool is_cliff_) {
			this->is_cliff = is_cliff_;
		}
		// 崖上であるかどうか？
		bool getIsCliffTop() const {
			return this->is_cliff_top;
		}
		void setIsCliffTop(const bool is_cliff_top_) {
			this->is_cliff_top = is_cliff_top_;
		}
		// オートタイル
		AutoTile getAutoTile() const {
			return this->auto_tile;
		}
		void setAutoTile(const AutoTile& auto_tile_) {
			this->auto_tile = auto_tile_;
		}
		AutoTile getBiomeAutoTile() const {
			return this->biome_auto_tile;
		}
		void setBiomeAutoTile(const AutoTile& biome_auto_tile_) {
			this->biome_auto_tile = biome_auto_tile_;
		}
	};

	constexpr ::As::IndexUint draw_map_layer_max = 3;

	// 描画用マップチップ
	class DrawMapChip {
	private:
		// ---------- 描画座標系 ----------

		DrawMapChipUnit tile[draw_map_layer_max]{};
		::As::IndexUint tile_num = draw_map_layer_max;

	public:

		void setX(const ::As::IndexUint x_) { this->tile[this->tile_num].setX(x_); }
		void setY(const ::As::IndexUint y_) { this->tile[this->tile_num].setY(y_); }
		void setZ(const ::As::IndexUint z_) { this->tile[this->tile_num].setZ(z_); }

		void clearTile() {
			for (::As::IndexUint i = 0; i < draw_map_layer_max; ++i) {
				tile[i] = DrawMapChipUnit{};
			}
		}

		void setNextTile() {
			if (tile_num >= draw_map_layer_max) {
				tile_num = 0;
				return;
			}
			if (tile_num < draw_map_layer_max - 1) {
				++tile_num;
				return;
			}
			for (::As::IndexUint i = 0; i < draw_map_layer_max - 1; ++i) {
				tile[i] = tile[i + 1];
			}
			tile[draw_map_layer_max - 1] = DrawMapChipUnit{};
		}

		::As::IndexUint getTileNum() const {
			return this->tile_num;
		}
		void setTileNum(const ::As::IndexUint tile_num_) {
			this->tile_num = tile_num_;
		}
		DrawMapChipUnit& getTile() {
			return this->tile[this->tile_num];
		}
		DrawMapChipUnit& getMaxTile() {
			return this->tile[draw_map_layer_max - 1];
		}
		DrawMapChipUnit& getTile(const ::As::IndexUint tile_num_) {
			return this->tile[tile_num_];
		}
		const DrawMapChipUnit& cgetTile() const {
			return this->tile[this->tile_num];
		}
		const DrawMapChipUnit& cgetTile(const ::As::IndexUint tile_num_) const {
			return this->tile[tile_num_];
		}

		void setDrawBiome(const MapChipTypeBiome& draw_biome_) {
			this->tile[this->tile_num].setDrawBiome(draw_biome_);
		}
		void setDrawBlock(const Block& block_) {
			this->tile[this->tile_num].setDrawBlock(block_);
		}
		void setElevation3(const ElevationUint& elevation_) {
			this->tile[this->tile_num].setElevation3(elevation_);
		}
		void setCliffTop(const CliffConnection& cliff_top_) {
			this->tile[this->tile_num].setCliffTop(cliff_top_);
		}
		void setCliff(const CliffConnection& cliff_) {
			this->tile[this->tile_num].setCliff(cliff_);
		}
		void setIsCliff(const bool is_cliff_) {
			this->tile[this->tile_num].setIsCliff(is_cliff_);
		}
		void setIsCliffTop(const bool is_cliff_top_) {
			this->tile[this->tile_num].setIsCliffTop(is_cliff_top_);
		}
		// オートタイル
		void setAutoTile(const AutoTile& auto_tile_) {
			this->tile[this->tile_num].setAutoTile(auto_tile_);
		}
		void setBiomeAutoTile(const AutoTile& biome_auto_tile_) {
			this->tile[this->tile_num].setBiomeAutoTile(biome_auto_tile_);
		}
	};

	constexpr ::As::IndexUint block_layer_max = 3;

	// ブロックのレイヤー
	class BlockLayer {
	private:
		Block block[block_layer_max]{};
	public:
		Block getBlock(const ::As::IndexUint index_) const {
			return this->block[index_];
		}
		void setBlock(const Block block_, const ::As::IndexUint index_) {
			this->block[index_] = block_;
		}
	};

	// マップチップ情報を管理
	class MapChip {
	private:
		// ---------- 元の座標系 ----------

		using FlowerFloat = double;

		BlockLayer block[128]{}; // ブロック
		MapChipTypeBiome biome{ MapChipTypeBiome::empty }; // バイオーム
		ElevationUint block_elevation{}; // ブロックの高さに合わせた標高値

		ElevationUint elevation{}; // 元の標高値
		ElevationUint temperature{}; // 気温
		ElevationUint amount_of_rainfall{}; // 降水量
		FlowerFloat flower{}; // 花
		ElevationUint lake{}; // 花
		::As::Uint32 seed{}; // 乱数シード

	public:

		MapChipTypeBiome getBiome() const {
			return this->biome;
		}
		void setBiome(const MapChipTypeBiome& biome_) {
			this->biome = biome_;
		}
		const BlockLayer& cgetBlockLayer(const As::IndexUint index_) const {
			return this->block[index_];
		}
		BlockLayer& getBlockLayer(const As::IndexUint index_) {
			return this->block[index_];
		}
		void setBlockLayer(const BlockLayer& block_, const As::IndexUint index_) {
			this->block[index_] = block_;
		}
		Block getBlock(const As::IndexUint index_, const As::IndexUint layer_index_) const {
			return this->block[index_].getBlock(layer_index_);
		}
		void setBlock(const Block& block_, const As::IndexUint index_, const As::IndexUint layer_index_) {
			this->block[index_].setBlock(block_, layer_index_);
		}
		ElevationUint getElevation() const {
			return this->elevation;
		}
		void setElevation(const ElevationUint& elevation_) {
			this->elevation = elevation_;
		}
		FlowerFloat getFlower() const {
			return this->flower;
		}
		void setFlower(const FlowerFloat& flower_) {
			this->flower = flower_;
		}
		ElevationUint getLake() const {
			return this->lake;
		}
		void setLake(const ElevationUint& lake_) {
			this->lake = lake_;
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
		::As::Uint32 getSeed() const {
			return this->seed;
		}
		void setSeed(const ::As::Uint32 seed_) {
			this->seed = seed_;
		}

	};

}

#endif //Included Crafterra Library