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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MAPCHIP_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MAPCHIP_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>
#include <AsLib2/ThirdParty/Framework/DataType.hpp>

#include <Crafterra/Map/HomogeneousConnection.hpp> // AutoTileIndex

#include <vector>
#include <string>

namespace AsLib2 {

	class MapChipFormat {
	private:
		::Crafterra::Uint16 width = 32;   // 1 マップチップの横のピクセル数
		::Crafterra::Uint16 height = 32;   // 1 マップチップの縦のピクセル数
		::Crafterra::Uint16 x = 1; // 横のマップチップ数
		::Crafterra::Uint16 y = 1;   // 縦のマップチップ数
		::Crafterra::IndexUint start_index = 0;   // そのマップチップの最初の添え字番号
		::std::string str{}; // 識別
	public:
		// コンストラクタ
		MapChipFormat() = default;
		MapChipFormat(::Crafterra::Uint16 width_, ::Crafterra::Uint16 height_, ::Crafterra::Uint16 x_, ::Crafterra::Uint16 y_, ::Crafterra::IndexUint start_index_, const ::std::string& str_)
			:width(width_), height(height_), x(x_), y(y_), start_index(start_index_), str(str_) {}

		::Crafterra::Uint16 getX() const {
			return this->x;
		}
		::Crafterra::Uint16 getY() const {
			return this->y;
		}
		::Crafterra::Uint16 getNum() const {
			return (this->x * this->y);
		}
		::Crafterra::Uint16 getWidth() const {
			return this->width;
		}
		::Crafterra::Uint16 getHeight() const {
			return this->height;
		}
		::Crafterra::IndexUint getStartIndex() const {
			return this->start_index;
		}
		const ::std::string& getString() const {
			return this->str;
		}
		void setX(const ::Crafterra::Uint16 x_) {
			this->x = x_;
		}
		void setY(const ::Crafterra::Uint16 y_) {
			this->y = y_;
		}
		void setWidth(const ::Crafterra::Uint16 width_) {
			this->width = width_;
		}
		void setHeight(const ::Crafterra::Uint16 height_) {
			this->height = height_;
		}
		void setStartIndex(const ::Crafterra::IndexUint start_index_) {
			this->start_index = start_index_;
		}
		void setString(const ::std::string& str_) {
			this->str = str_;
		}
	};

	class MapChipImage {
	private:

#ifdef SIV3D_INCLUDED
		using Image_ = ::s3d::TextureRegion;
#else
		using Image_ = int;
#endif

#ifdef SIV3D_INCLUDED
		::std::vector <::s3d::Texture> texture_map_chip{};
#endif

		//Image_ base_map[8 * 133]{};
		//Image_ cliff_top[4 * 10]{};
		//Image_ sea[16 * 10]{};
		//Image_ desert[4 * 10]{};

		::std::vector<MapChipFormat> map_chip_format{};
		::std::vector<Image_> map_chip{};

		::Crafterra::DataType::Uint8 sea_alpha[16 * 10] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
			,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};
		::Crafterra::DataType::Uint8 desert_alpha[4 * 10] = {
			0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,1,1,1,1
			,1,1,1,1
		};

		::Crafterra::DataType::Uint8 cliff_top_alpha[4 * 10] = {
			0,1,1,0
			,1,0,0,0
			,1,1,0,0
			,1,1,0,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,1
			,0,0,0,0
		};

	public:

		void loadMapChip(
			::Crafterra::Uint16 width_, ::Crafterra::Uint16 height_, ::Crafterra::Uint16 x_, ::Crafterra::Uint16 y_,
			::Crafterra::IndexUint& start_index_, const ::std::string& str_, 
#if defined(__DXLIB)
			const ::std::string& link_
#elif defined(SIV3D_INCLUDED)
			const ::s3d::FilePathView& link_
#endif
		) {

			map_chip_format.emplace_back(MapChipFormat(width_, height_, x_, y_, start_index_, str_));
			map_chip.resize(start_index_ + map_chip_format.back().getNum());
#if defined(__DXLIB)
			::DxLib::LoadDivGraph(link_.c_str(), int(x_ * y_),
				int(x_), int(y_),
				int(width_), int(height_), &(map_chip[start_index_]));
#elif defined(SIV3D_INCLUDED)
			texture_map_chip.emplace_back(::s3d::Texture(link_));
			for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < y_; ++y)
				for (::Crafterra::DataType::IndexUint x = 0; x < x_; ++x, ++count) {
					map_chip[start_index_ + count] = (texture_map_chip.back()(double(width_ * x), double(height_ * y), double(width_), double(height_)));
				}
#endif
			start_index_ += map_chip_format.back().getNum();
		}


		MapChipImage() {

#if defined(__DXLIB)

			::Crafterra::IndexUint index = 0;
			loadMapChip(32, 32, 8, 133, index, "Base", "./../../../resource/Picture/Chip/Map/Base(pipoya).png");
			loadMapChip(32, 32, 4, 10, index, "Cliff", "./../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png");
			loadMapChip(16, 16, 16, 10, index, "Sea", "./../../../resource/Picture/Chip/AutoTile/Water1(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Desert", "./../../../resource/Picture/Chip/AutoTile/Dirt3(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Rock", "./../../../resource/Picture/Chip/AutoTile/Dirt2(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Savannah", "./../../../resource/Picture/Chip/AutoTile/Dirt1(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Mountain", "./../../../resource/Picture/Chip/AutoTile/Grass2(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Forest", "./../../../resource/Picture/Chip/AutoTile/Grass4(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Grass", "./../../../resource/Picture/Chip/AutoTile/LongGrass(pipoya).png");

#elif defined(SIV3D_INCLUDED)

			::Crafterra::IndexUint index = 0;
			loadMapChip(32, 32, 8, 133, index, "Base", U"./../../../../resource/Picture/Chip/Map/Base(pipoya).png");
			loadMapChip(32, 32, 4, 10, index, "Cliff", U"./../../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png");
			loadMapChip(16, 16, 16, 10, index, "Sea", U"./../../../../resource/Picture/Chip/AutoTile/Water1(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Desert", U"./../../../../resource/Picture/Chip/AutoTile/Dirt3(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Rock", U"./../../../../resource/Picture/Chip/AutoTile/Dirt2(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Savannah", U"./../../../../resource/Picture/Chip/AutoTile/Dirt1(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Mountain", U"./../../../../resource/Picture/Chip/AutoTile/Grass2(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Forest", U"./../../../../resource/Picture/Chip/AutoTile/Grass4(pipoya).png");
			loadMapChip(16, 16, 4, 10, index, "Grass", U"./../../../../resource/Picture/Chip/AutoTile/LongGrass(pipoya).png");

			//texture_basemap = ::s3d::Texture(U"./../../../../resource/Picture/Chip/Map/Base(pipo).png");
			//for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 249; ++y)
			//	for (::Crafterra::DataType::IndexUint x = 0; x < 8; ++x, ++count) {
			//		base_map[count] = texture_basemap(double(32 * x), double(32 * y), double(32), double(32));
			//	}
			//texture_cliff_top = ::s3d::Texture(U"./../../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png");
			//for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 10; ++y)
			//	for (::Crafterra::DataType::IndexUint x = 0; x < 4; ++x, ++count) {
			//		cliff_top[count] = texture_cliff_top(double(32 * x), double(32 * y), double(32), double(32));
			//	}
			//texture_sea = ::s3d::Texture(U"./../../../../resource/Picture/Chip/AutoTile/Water1(pipoya).png");
			//for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 10; ++y)
			//	for (::Crafterra::DataType::IndexUint x = 0; x < 16; ++x, ++count) {
			//		sea[count] = texture_sea(double(16 * x), double(16 * y), double(16), double(16));
			//	}
			//texture_desert = ::s3d::Texture(U"./../../../../resource/Picture/Chip/AutoTile/[A]Dirt3_pipo.png");
			//for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 10; ++y)
			//	for (::Crafterra::DataType::IndexUint x = 0; x < 4; ++x, ++count) {
			//		desert[count] = texture_desert(double(16 * x), double(16 * y), double(16), double(16));
			//	}
#endif // __DXLIB
		}

		~MapChipImage() {

		}
		Image_ getMapChip(const ::std::string& str_, const::Crafterra::DataType::IndexUint index_) const {
			for (const auto& mcf : map_chip_format) {
				if (mcf.getString() != str_) continue;
				return this->map_chip[mcf.getStartIndex() + index_];
			}
			return this->map_chip[0];
		}
		::Crafterra::DataType::Uint8 getSeaAlpha(const ::Crafterra::DataType::IndexUint index_) const { return this->sea_alpha[index_]; }
		bool getIsSeaAlpha(const ::Crafterra::DataType::IndexUint index_) const { return (this->sea_alpha[index_] == 0); }
		bool getIsAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_, const ::Crafterra::DataType::Uint8* const alpha_array_) const {
			return ((alpha_array_[auto_tile_index_.auto_tile_upper_left] == 0) ||
				(alpha_array_[auto_tile_index_.auto_tile_upper_right] == 0) ||
				(alpha_array_[auto_tile_index_.auto_tile_lower_left] == 0) ||
				(alpha_array_[auto_tile_index_.auto_tile_lower_right] == 0));
		}
		bool getIsSeaAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_) const {
			return getIsAlpha(auto_tile_index_, this->sea_alpha);
		}
		bool getIsDesertAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_) const {
			return getIsAlpha(auto_tile_index_, this->desert_alpha);
		}
		::Crafterra::DataType::Uint8 getMapChipCliffTopAlpha(const ::Crafterra::DataType::IndexUint index_) const { return this->cliff_top_alpha[index_]; }

	};
}

#endif //Included Crafterra Library