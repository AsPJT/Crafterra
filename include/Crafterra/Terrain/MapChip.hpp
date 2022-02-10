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
#include <Crafterra/Enum/TerrainObject.hpp>

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

	// 148,185,32
	// 110,163,0
	// 170,212,43
	// 127,145,72
	// 201,196,119
	// 151,130,73
	// 234,226,135
	// 176,186,163

	enum class AutoTileType : ::As::Uint8 {
		empty     // 無し
		, normal
		, wolf
		, cliff
		, cliff_top
		, size
	};

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
		TerrainObject terrain_object{};
		ElevationUint elevation{}; // カメラの位置にずらした、ブロックの高さに合わせた標高値
		TerrainBiome draw_biome{ TerrainBiome::empty }; // 描画用バイオーム
		AutoTile auto_tile{}; // 描画用オートタイル
		AutoTileType auto_tile_type{ AutoTileType::normal }; // オートタイルの種類
		AutoTile biome_auto_tile{}; // 描画用オートタイル
		bool is_biome_cliff_top = false;

	public:

		::As::IndexUint getX() const { return this->field_map_x; }
		::As::IndexUint getY() const { return this->field_map_y; }
		::As::IndexUint getZ() const { return this->field_map_z; }
		void setX(const ::As::IndexUint x_) { this->field_map_x = x_; }
		void setY(const ::As::IndexUint y_) { this->field_map_x = y_; }
		void setZ(const ::As::IndexUint z_) { this->field_map_x = z_; }

		TerrainBiome getDrawBiome() const { return this->draw_biome; }
		void setDrawBiome(const TerrainBiome& draw_biome_) { this->draw_biome = draw_biome_; }
		TerrainObject getTerrainObject() const { return this->terrain_object; }
		void setTerrainObject(const TerrainObject& block_) { this->terrain_object = block_; }
		ElevationUint getElevation() const { return this->elevation; }
		void setElevation(const ElevationUint& elevation_) { this->elevation = elevation_; }
		CliffConnection getCliffTop() const { return this->cliff_top; }
		void setCliffTop(const CliffConnection& cliff_top_) { this->cliff_top = cliff_top_; }
		CliffConnection getCliff() const { return this->cliff; }
		void setCliff(const CliffConnection& cliff_) { this->cliff = cliff_; }
		// バイオームの崖上であるかどうか？
		bool getIsBiomeCliffTop() const { return this->is_biome_cliff_top; }
		void setIsBiomeCliffTop(const bool is_biome_cliff_) { this->is_biome_cliff_top = is_biome_cliff_; }
		// 崖であるかどうか？
		bool getIsCliff() const { return this->is_cliff; }
		void setIsCliff(const bool is_cliff_) { this->is_cliff = is_cliff_; }
		// 崖上であるかどうか？
		bool getIsCliffTop() const { return this->is_cliff_top; }
		void setIsCliffTop(const bool is_cliff_top_) { this->is_cliff_top = is_cliff_top_; }
		// オートタイル
		AutoTile getAutoTile() const { return this->auto_tile; }
		void setAutoTile(const AutoTile& auto_tile_) { this->auto_tile = auto_tile_; }
		AutoTileType getAutoTileType() const { return this->auto_tile_type; }
		void setAutoTileType(const AutoTileType& auto_tile_type_) { this->auto_tile_type = auto_tile_type_; }
		AutoTile getBiomeAutoTile() const { return this->biome_auto_tile; }
		void setBiomeAutoTile(const AutoTile& biome_auto_tile_) { this->biome_auto_tile = biome_auto_tile_; }
	};

	constexpr ::As::IndexUint draw_map_layer_max = 4;

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
		void setTerrainObject(const TerrainObject& block_) { this->tile[this->tile_num].setTerrainObject(block_); }
		void setElevation(const ElevationUint& elevation_) { this->tile[this->tile_num].setElevation(elevation_); }
		void setCliffTop(const CliffConnection& cliff_top_) { this->tile[this->tile_num].setCliffTop(cliff_top_); }
		void setCliff(const CliffConnection& cliff_) { this->tile[this->tile_num].setCliff(cliff_); }
		void setIsCliff(const bool is_cliff_) { this->tile[this->tile_num].setIsCliff(is_cliff_); }
		void setIsCliffTop(const bool is_cliff_top_) { this->tile[this->tile_num].setIsCliffTop(is_cliff_top_); }
		void setAutoTile(const AutoTile& auto_tile_) { this->tile[this->tile_num].setAutoTile(auto_tile_); }
		void setBiomeAutoTile(const AutoTile& biome_auto_tile_) { this->tile[this->tile_num].setBiomeAutoTile(biome_auto_tile_); }
	};

	bool isBiomeCliff(const AutoTile& at, const DrawMapChipUnit& draw_map) {

		if (draw_map.getTerrainObject() != TerrainObject::cliff_top) {
			return false;
		}

		// 描画するバイオーム
		const bool is_draw_biome = (draw_map.getDrawBiome() != TerrainBiome::empty
			&& draw_map.getDrawBiome() != TerrainBiome::sea
			&& draw_map.getDrawBiome() != TerrainBiome::lake
			&& draw_map.getDrawBiome() != TerrainBiome::normal
			&& draw_map.getDrawBiome() != TerrainBiome::hill
			);
		if (!is_draw_biome) return false;

		if (draw_map.getDrawBiome() != TerrainBiome::forest
			&& draw_map.getDrawBiome() != TerrainBiome::tundra) {
			return false;
		}

		if (at.auto_tile_upper_left == AutoTileConnection::nothing_upper_left
			&& at.auto_tile_upper_right == AutoTileConnection::nothing_upper_right
			&& at.auto_tile_lower_left == AutoTileConnection::nothing_lower_left
			&& at.auto_tile_lower_right == AutoTileConnection::nothing_lower_right
			&& draw_map.getCliffTop() == CliffConnection::nothing) {
			return true;
		}
		else if ((at.auto_tile_upper_left == AutoTileConnection::all_upper_left
			//|| at.auto_tile_upper_left == AutoTileConnection::cross_upper_left
			) && (at.auto_tile_upper_right == AutoTileConnection::all_upper_right
				//|| at.auto_tile_upper_right == AutoTileConnection::cross_upper_right
				) && (at.auto_tile_lower_left == AutoTileConnection::all_lower_left
					//|| at.auto_tile_lower_left == AutoTileConnection::cross_lower_left
					) && (at.auto_tile_lower_right == AutoTileConnection::all_lower_right
						//|| at.auto_tile_lower_right == AutoTileConnection::cross_lower_right
						) && draw_map.getCliffTop() == CliffConnection::all) {
			return true;
		}
		else if (
			at.auto_tile_upper_left == AutoTileConnection::up_and_down_upper_left
			&& at.auto_tile_upper_right == AutoTileConnection::up_and_down_upper_right
			&& draw_map.getCliffTop() == CliffConnection::up) {
			return true;
		}
		else if (
			at.auto_tile_lower_left == AutoTileConnection::up_and_down_lower_left
			&& at.auto_tile_lower_right == AutoTileConnection::up_and_down_lower_right
			&& draw_map.getCliffTop() == CliffConnection::down) {
			return true;
		}
		else if (
			at.auto_tile_upper_left == AutoTileConnection::left_and_right_upper_left
			&& at.auto_tile_lower_left == AutoTileConnection::left_and_right_lower_left
			&& draw_map.getCliffTop() == CliffConnection::left) {
			return true;
		}
		else if (
			at.auto_tile_upper_right == AutoTileConnection::left_and_right_upper_right
			&& at.auto_tile_lower_right == AutoTileConnection::left_and_right_lower_right
			&& draw_map.getCliffTop() == CliffConnection::right) {
			return true;
		}
		else if (
			at.auto_tile_upper_right == AutoTileConnection::left_and_right_upper_right
			&& at.auto_tile_lower_right == AutoTileConnection::all_lower_right
			&& at.auto_tile_lower_left == AutoTileConnection::up_and_down_lower_left
			&& (draw_map.getCliffTop() == CliffConnection::right_down_0
				|| draw_map.getCliffTop() == CliffConnection::right_down_1)) {
			return true;
		}
		else if (
			at.auto_tile_upper_left == AutoTileConnection::left_and_right_upper_left
			&& at.auto_tile_lower_right == AutoTileConnection::up_and_down_lower_right
			&& at.auto_tile_lower_left == AutoTileConnection::all_lower_left
			&& (draw_map.getCliffTop() == CliffConnection::left_down_0
				|| draw_map.getCliffTop() == CliffConnection::left_down_1)) {
			return true;
		}
		else if (
			at.auto_tile_lower_right == AutoTileConnection::left_and_right_lower_right
			&& at.auto_tile_upper_right == AutoTileConnection::all_upper_right
			&& at.auto_tile_upper_left == AutoTileConnection::up_and_down_upper_left
			&& (draw_map.getCliffTop() == CliffConnection::up_right_0
				|| draw_map.getCliffTop() == CliffConnection::up_right_1)) {
			return true;
		}
		else if (
			at.auto_tile_lower_left == AutoTileConnection::left_and_right_lower_left
			&& at.auto_tile_upper_right == AutoTileConnection::up_and_down_upper_right
			&& at.auto_tile_upper_left == AutoTileConnection::all_upper_left
			&& (draw_map.getCliffTop() == CliffConnection::up_left_0
				|| draw_map.getCliffTop() == CliffConnection::up_left_1)) {
			return true;
		}
		else if (at.auto_tile_upper_left == AutoTileConnection::all_upper_left
			&& at.auto_tile_upper_right == AutoTileConnection::all_upper_right
			&& at.auto_tile_lower_left == AutoTileConnection::left_and_right_lower_left
			&& at.auto_tile_lower_right == AutoTileConnection::left_and_right_lower_right
			&& (draw_map.getCliffTop() == CliffConnection::up_left_right_0
				|| draw_map.getCliffTop() == CliffConnection::up_left_right_1
				|| draw_map.getCliffTop() == CliffConnection::up_left_right_2
				|| draw_map.getCliffTop() == CliffConnection::up_left_right_3
				)) {
			return true;
		}
		else if (at.auto_tile_lower_left == AutoTileConnection::all_lower_left
			&& at.auto_tile_lower_right == AutoTileConnection::all_lower_right
			&& at.auto_tile_upper_left == AutoTileConnection::left_and_right_upper_left
			&& at.auto_tile_upper_right == AutoTileConnection::left_and_right_upper_right
			&& (draw_map.getCliffTop() == CliffConnection::left_right_down_0
				|| draw_map.getCliffTop() == CliffConnection::left_right_down_1
				|| draw_map.getCliffTop() == CliffConnection::left_right_down_2
				|| draw_map.getCliffTop() == CliffConnection::left_right_down_3
				)) {
			return true;
		}
		return false;
	}

}

#endif //Included Crafterra Library