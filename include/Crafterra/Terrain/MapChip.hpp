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

#include <Crafterra/Enum/TerrainBiome.hpp>

namespace Crafterra {

	::As::Array<::As::String, As::IndexUint(TerrainBiome::size)>
		MapChipTypeBiomeString{ {
				"Empty","Sea","Lake","Tundra","Mountain","Desert","Forest","Rock","Hill","Savannah","Grass","Wall","Way","Room","Normal"
	} };

	//#if (__cplusplus < 202002L)
	//	::Crafterra::DataType::Array<::As::String, TerrainBiome::size>
	//		MapChipTypeBiomeString{ {
	//				u8"無し",u8"海",u8"湖",u8"山",u8"砂漠",u8"森林",u8"岩山",u8"丘",u8"サバンナ",u8"草原",u8"壁",u8"道",u8"部屋",u8"通常"
	//	} };
	//#else
		//::Crafterra::DataType::Array<::As::String, As::IndexUint(TerrainBiome::size)>
		//	MapChipTypeBiomeString{ {
		//			"無し","海","湖","山","砂漠","森林","岩山","丘","サバンナ","草原","壁","道","部屋","通常"
		//} };
	//#endif

		// 未完成
	enum class TerrainObject : TerrainObjectType {
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
		TerrainObject draw_block{};
		ElevationUint elevation{}; // カメラの位置にずらした、ブロックの高さに合わせた標高値
		TerrainBiome draw_biome{ TerrainBiome::empty }; // 描画用バイオーム
		AutoTile auto_tile{}; // 描画用オートタイル
		AutoTile biome_auto_tile{}; // 描画用オートタイル

	public:

		::As::IndexUint getX() const { return this->field_map_x; }
		::As::IndexUint getY() const { return this->field_map_y; }
		::As::IndexUint getZ() const { return this->field_map_z; }
		void setX(const ::As::IndexUint x_) { this->field_map_x = x_; }
		void setY(const ::As::IndexUint y_) { this->field_map_x = y_; }
		void setZ(const ::As::IndexUint z_) { this->field_map_x = z_; }

		TerrainBiome getDrawBiome() const { return this->draw_biome; }
		void setDrawBiome(const TerrainBiome& draw_biome_) { this->draw_biome = draw_biome_; }
		TerrainObject getDrawBlock() const { return this->draw_block; }
		void setDrawBlock(const TerrainObject& block_) { this->draw_block = block_; }
		ElevationUint getElevation() const { return this->elevation; }
		void setElevation(const ElevationUint& elevation_) { this->elevation = elevation_; }
		CliffConnection getCliffTop() const { return this->cliff_top; }
		void setCliffTop(const CliffConnection& cliff_top_) { this->cliff_top = cliff_top_; }
		CliffConnection getCliff() const { return this->cliff; }
		void setCliff(const CliffConnection& cliff_) { this->cliff = cliff_; }
		// 崖であるかどうか？
		bool getIsCliff() const { return this->is_cliff; }
		void setIsCliff(const bool is_cliff_) { this->is_cliff = is_cliff_; }
		// 崖上であるかどうか？
		bool getIsCliffTop() const { return this->is_cliff_top; }
		void setIsCliffTop(const bool is_cliff_top_) { this->is_cliff_top = is_cliff_top_; }
		// オートタイル
		AutoTile getAutoTile() const { return this->auto_tile; }
		void setAutoTile(const AutoTile& auto_tile_) { this->auto_tile = auto_tile_; }
		AutoTile getBiomeAutoTile() const { return this->biome_auto_tile; }
		void setBiomeAutoTile(const AutoTile& biome_auto_tile_) { this->biome_auto_tile = biome_auto_tile_; }
	};

	constexpr ::As::IndexUint draw_map_layer_max = 3;

	// 描画用マップチップ
	class DrawMapChip {
	private:
		DrawMapChipUnit tile[draw_map_layer_max]{};
		::As::IndexUint tile_num = draw_map_layer_max;

	public:

		void setX(const ::As::IndexUint x_) { this->tile[this->tile_num].setX(x_); }
		void setY(const ::As::IndexUint y_) { this->tile[this->tile_num].setY(y_); }
		void setZ(const ::As::IndexUint z_) { this->tile[this->tile_num].setZ(z_); }

		void clearTile() {
			for (::As::IndexUint i = 0; i < draw_map_layer_max; ++i) this->tile[i] = DrawMapChipUnit{};
		}

		void setNextTile() {
			if (this->tile_num >= draw_map_layer_max) {
				this->tile_num = 0;
				return;
			}
			if (this->tile_num < draw_map_layer_max - 1) {
				++(this->tile_num);
				return;
			}
			for (::As::IndexUint i = 0; i < draw_map_layer_max - 1; ++i) this->tile[i] = this->tile[i + 1];
			this->tile[draw_map_layer_max - 1] = DrawMapChipUnit{};
		}

		::As::IndexUint getTileNum() const { return this->tile_num; }
		void setTileNum(const ::As::IndexUint tile_num_) { this->tile_num = tile_num_; }
		DrawMapChipUnit& getTile() { return this->tile[this->tile_num]; }
		DrawMapChipUnit& getMaxTile() { return this->tile[draw_map_layer_max - 1]; }
		DrawMapChipUnit& getTile(const ::As::IndexUint tile_num_) { return this->tile[tile_num_]; }
		const DrawMapChipUnit& cgetTile() const { return this->tile[this->tile_num]; }
		const DrawMapChipUnit& cgetTile(const ::As::IndexUint tile_num_) const { return this->tile[tile_num_]; }
		void setDrawBiome(const TerrainBiome& draw_biome_) { this->tile[this->tile_num].setDrawBiome(draw_biome_); }
		void setDrawBlock(const TerrainObject& block_) { this->tile[this->tile_num].setDrawBlock(block_); }
		void setElevation(const ElevationUint& elevation_) { this->tile[this->tile_num].setElevation(elevation_); }
		void setCliffTop(const CliffConnection& cliff_top_) { this->tile[this->tile_num].setCliffTop(cliff_top_); }
		void setCliff(const CliffConnection& cliff_) { this->tile[this->tile_num].setCliff(cliff_); }
		void setIsCliff(const bool is_cliff_) { this->tile[this->tile_num].setIsCliff(is_cliff_); }
		void setIsCliffTop(const bool is_cliff_top_) { this->tile[this->tile_num].setIsCliffTop(is_cliff_top_); }
		void setAutoTile(const AutoTile& auto_tile_) { this->tile[this->tile_num].setAutoTile(auto_tile_); }
		void setBiomeAutoTile(const AutoTile& biome_auto_tile_) { this->tile[this->tile_num].setBiomeAutoTile(biome_auto_tile_); }
	};

}

#endif //Included Crafterra Library