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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MAPCHIP_IMAGE_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MAPCHIP_IMAGE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <AsLib2/ThirdParty/Framework/DataType.hpp>

#include <Crafterra/Terrain/TileConnection.hpp> // AutoTileIndex

#include <Crafterra/Basic/InitRead.hpp> // ReadText

#include <AsLib2/Basic/Unicode.hpp>

#include <vector>
#include <string>

namespace As {

	class MapChipFormat {
	private:
		::As::Uint16 width = 32;   // 1 マップチップの横のピクセル数
		::As::Uint16 height = 32;   // 1 マップチップの縦のピクセル数
		::As::Uint16 x = 1; // 横のマップチップ数
		::As::Uint16 y = 1;   // 縦のマップチップ数
		::As::IndexUint start_index = 0;   // そのマップチップの最初の添え字番号
		::std::string str{}; // 識別
	public:
		// コンストラクタ
		MapChipFormat() = default;
		MapChipFormat(const ::As::Uint16 width_, const ::As::Uint16 height_, const ::As::Uint16 x_, const ::As::Uint16 y_, const ::As::IndexUint start_index_, const ::std::string& str_)
			:width(width_), height(height_), x(x_), y(y_), start_index(start_index_), str(str_) {}

		::As::Uint16 getX() const { return this->x; }
		::As::Uint16 getY() const { return this->y; }
		::As::Uint16 getNum() const { return (this->x * this->y); }
		::As::Uint16 getWidth() const { return this->width; }
		::As::Uint16 getHeight() const { return this->height; }
		::As::IndexUint getStartIndex() const { return this->start_index; }
		const ::std::string& getString() const { return this->str; }
		void setX(const ::As::Uint16 x_) { this->x = x_; }
		void setY(const ::As::Uint16 y_) { this->y = y_; }
		void setWidth(const ::As::Uint16 width_) { this->width = width_; }
		void setHeight(const ::As::Uint16 height_) { this->height = height_; }
		void setStartIndex(const ::As::IndexUint start_index_) { this->start_index = start_index_; }
		void setString(const ::std::string& str_) { this->str = str_; }
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

		::As::Uint8 sea_alpha[16 * 10] = {
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
		::As::Uint8 desert_alpha[4 * 10] = {
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

		::As::Uint8 cliff_top_alpha[4 * 10] = {
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

		// マップチップを取り込む
		void loadMapChip(
			::As::Uint16 width_, ::As::Uint16 height_, ::As::Uint16 x_, ::As::Uint16 y_,
			::As::IndexUint& start_index_, const ::std::string& str_, 
			const ::std::string& link_
		) {

			map_chip_format.emplace_back(MapChipFormat(width_, height_, x_, y_, start_index_, str_));
			map_chip.resize(start_index_ + map_chip_format.back().getNum());
#if defined(__DXLIB)
			::DxLib::LoadDivGraph(link_.c_str(), int(x_ * y_),
				int(x_), int(y_),
				int(width_), int(height_), &(map_chip[start_index_]));
#elif defined(SIV3D_INCLUDED)
			texture_map_chip.emplace_back(::s3d::Texture(::As::utf32(link_)));
			for (::As::IndexUint y = 0, count = 0; y < y_; ++y)
				for (::As::IndexUint x = 0; x < x_; ++x, ++count) {
					map_chip[start_index_ + count] = (texture_map_chip.back()(double(width_ * x), double(height_ * y), double(width_), double(height_)));
				}
#endif
			start_index_ += map_chip_format.back().getNum();
		}

		// コンストラクタ
		MapChipImage(const ::std::string& path_, const ::std::string& text_path_) {

			::As::IndexUint index = 0;

			::Crafterra::ReadText read_text(text_path_);
			const auto& mat = read_text.getMatrix();
			if (mat.size() <= 1) return; // 画像データなし

			for (::As::IndexUint y = 1; y < mat.size(); ++y) {
				::As::Uint16 width{};
				::As::Uint16 height{};
				::As::Uint16 getx{};
				::As::Uint16 gety{};
				::std::string tile{};
				::std::string label{};
				::std::string path{};
				for (::As::IndexUint x = 0; x < mat[y].size(); ++x) {
					     if ((mat.front()[x]) == ::std::string("width")) width  = ::As::Uint16(::Crafterra::getNum(mat[y][x])); // 1 マップチップの幅
					else if ((mat.front()[x]) == ::std::string("height")) height = ::As::Uint16(::Crafterra::getNum(mat[y][x])); // 1 マップチップの高さ
					else if ((mat.front()[x]) == ::std::string("x")) getx        = ::As::Uint16(::Crafterra::getNum(mat[y][x])); // 横のマップチップ数
					else if ((mat.front()[x]) == ::std::string("y")) gety        = ::As::Uint16(::Crafterra::getNum(mat[y][x])); // 縦のマップチップ数
					else if ((mat.front()[x]) == ::std::string("tile")) tile       = mat[y][x]; // マップチップのタイル形式の種類
					else if ((mat.front()[x]) == ::std::string("label")) label    = mat[y][x]; // マップチップのラベル名
					else if ((mat.front()[x]) == ::std::string("path")) path     = mat[y][x]; // マップチップの保管場所
				}
				this->loadMapChip(width, height, getx, gety, index, label, path_ + path); // マップチップを取り込む
			}
		}

		Image_ getMapChip(const ::std::string& str_, const::As::IndexUint index_) const {
			for (const auto& mcf : map_chip_format) {
				if (mcf.getString() != str_) continue;
				return this->map_chip[mcf.getStartIndex() + index_];
			}
			return this->map_chip[0]; // 今後変える
		}
		::As::Uint8 getSeaAlpha(const ::As::IndexUint index_) const { return this->sea_alpha[index_]; }
		bool getIsSeaAlpha(const ::As::IndexUint index_) const { return (this->sea_alpha[index_] == 0); }
		bool getIsAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_, const ::As::Uint8* const alpha_array_) const {
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
		::As::Uint8 getMapChipCliffTopAlpha(const ::As::IndexUint index_) const { return this->cliff_top_alpha[index_]; }

	};
}

#endif //Included Crafterra Library