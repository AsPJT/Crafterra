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

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <AsLib2/ThirdParty/Framework/DataType.hpp>

#include <Crafterra/Map/HomogeneousConnection.hpp> // AutoTileIndex

#include <Crafterra/Basic/InitRead.hpp> // ReadText

#include <vector>
#include <string>


#include <string>
#include <cstdint>

namespace As {

	// UTF-32(char32_t) から UTF-8(char*)へ
	const char* utf8(const char32_t src) {

		static char u8char[5];
		u8char[0] = 0;
		u8char[1] = 0;
		u8char[2] = 0;
		u8char[3] = 0;
		u8char[4] = 0;

		if (src < 0 || src > 0x10ffff) return u8char;

		if (src < 0x80) u8char[0] = char(src);
		else if (src < 0x800) {
			u8char[0] = 0xc0 | char(src >> 6);
			u8char[1] = 0x80 | (char(src) & 0x3f);
		}
		else if (src < 0x10000) {
			u8char[0] = 0xe0 | char(src >> 12);
			u8char[1] = 0x80 | (char(src >> 6) & 0x3f);
			u8char[2] = 0x80 | (char(src) & 0x3f);
		}
		else {
			u8char[0] = 0xf0 | char(src >> 18);
			u8char[1] = 0x80 | (char(src >> 12) & 0x3f);
			u8char[2] = 0x80 | (char(src >> 6) & 0x3f);
			u8char[3] = 0x80 | (char(src) & 0x3f);
		}

		return u8char;
	}

	// UTF-32(char32_t*) から UTF-8(char*)へ
	const char* utf8(const char32_t* src)
	{
		static std::string u8str;
		u8str = "";

		for (size_t j = 0;; ++j) {

			if (src[j] == 0) break;
			u8str += utf8(src[j]);
		}
		return u8str.c_str();
	}

	// UTF-32(u32string) から UTF-8(char*)へ
	const char* utf8(const std::u32string& src)
	{
		static std::string u8str;
		u8str = "";

		const size_t src_len = src.length();
		for (size_t j = 0; j < src_len; ++j) {

			if (src[j] == 0) break;
			u8str += utf8(src[j]);
		}
		return u8str.c_str();
	}

	// UTF-32(u32string) から UTF-32(char32_t*)へ
	const char32_t* utf32(const std::u32string& src) { return src.c_str(); }

	// UTF-32(char32_t*) から UTF-32(char32_t*)へ
	const char32_t* utf32(const char32_t* src) { return src; }

	// UTF-32(char32_t) から UTF-32(char32_t*)へ
	const char32_t* utf32(const char32_t src) {
		static char32_t u32char[2];
		u32char[0] = src;
		u32char[1] = 0;
		return u32char;
	}

	int32_t utf8Byte(char src) {
		if (0 <= uint8_t(src) && uint8_t(src) < 0x80) return 1;
		if (0xc2 <= uint8_t(src) && uint8_t(src) < 0xe0) return 2;
		if (0xe0 <= uint8_t(src) && uint8_t(src) < 0xf0) return 3;
		if (0xf0 <= uint8_t(src) && uint8_t(src) < 0xf8) return 4;
		return 0;
	}

	bool utf8_0x80To0xc0(char src) { return 0x80 <= uint8_t(src) && uint8_t(src) < 0xc0; }

	const char32_t char_utf32(const char src[5], int32_t& number_of_byte) {
		char32_t u32char{};

		number_of_byte = utf8Byte(src[0]);
		if (number_of_byte == 0) return u32char;

		switch (number_of_byte) {

		case 1:u32char = char32_t(uint8_t(src[0])); break;

		case 2:
			if (!utf8_0x80To0xc0(src[1])) return u32char;
			if ((uint8_t(src[0]) & 0x1e) == 0) return u32char;

			u32char = char32_t(src[0] & 0x1f) << 6;
			u32char |= char32_t(src[1] & 0x3f);
			break;

		case 3:
			if (!utf8_0x80To0xc0(src[1]) || !utf8_0x80To0xc0(src[2])) return u32char;
			if ((uint8_t(src[0]) & 0x0f) == 0 && (uint8_t(src[1]) & 0x20) == 0) return u32char;

			u32char = char32_t(src[0] & 0x0f) << 12;
			u32char |= char32_t(src[1] & 0x3f) << 6;
			u32char |= char32_t(src[2] & 0x3f);
			break;

		case 4:
			if (!utf8_0x80To0xc0(src[1]) || !utf8_0x80To0xc0(src[2]) || !utf8_0x80To0xc0(src[3])) return u32char;
			if ((uint8_t(src[0]) & 0x07) == 0 && (uint8_t(src[1]) & 0x30) == 0) return u32char;

			u32char = char32_t(src[0] & 0x07) << 18;
			u32char |= char32_t(src[1] & 0x3f) << 12;
			u32char |= char32_t(src[2] & 0x3f) << 6;
			u32char |= char32_t(src[3] & 0x3f);
			break;

		default:return u32char; break;

		}

		return u32char;
	}

	// UTF-8(char) から UTF-32(char32_t*)へ
	const char32_t* utf32(const char src) {
		static char32_t u32char[2];
		char u8char[5]{};
		int32_t number_of_byte;
		u8char[0] = src;

		u32char[0] = char_utf32(u8char, number_of_byte);
		u32char[1] = 0;
		return u32char;
	}

	const char32_t char_utf32(const std::string& src, char u8char[5], const size_t j, int32_t& number_of_byte) {
		u8char[0] = 0;
		u8char[1] = 0;
		u8char[2] = 0;
		u8char[3] = 0;

		if (src[j] == 0) return char_utf32(u8char, number_of_byte);
		u8char[0] = src[j];
		if (src[j + 1] == 0) return char_utf32(u8char, number_of_byte);
		u8char[1] = src[j + 1];
		if (src[j + 2] == 0) return char_utf32(u8char, number_of_byte);
		u8char[2] = src[j + 2];
		if (src[j + 3] == 0) return char_utf32(u8char, number_of_byte);
		u8char[3] = src[j + 3];

		return char_utf32(u8char, number_of_byte);
	}

	// UTF-8(string) から UTF-32(char32_t*)へ
	const char32_t* utf32(const std::string& src) {
		static std::u32string u32str;
		u32str = U"";

		char u8char[5]{};
		int32_t number_of_byte;

		const size_t src_len = src.length();
		for (size_t j = 0; j < src_len;) {
			if (src[j] == 0) break;
			u32str += char_utf32(src, u8char, j, number_of_byte);
			if (number_of_byte) j += number_of_byte;
			else ++j;
		}
		return u32str.c_str();
	}

	const char32_t char_utf32(const char* src, char u8char[5], const size_t j, int32_t& number_of_byte) {
		u8char[0] = 0;
		u8char[1] = 0;
		u8char[2] = 0;
		u8char[3] = 0;

		if (src[j] == 0) return char_utf32(u8char, number_of_byte);
		u8char[0] = src[j];
		if (src[j + 1] == 0) return char_utf32(u8char, number_of_byte);
		u8char[1] = src[j + 1];
		if (src[j + 2] == 0) return char_utf32(u8char, number_of_byte);
		u8char[2] = src[j + 2];
		if (src[j + 3] == 0) return char_utf32(u8char, number_of_byte);
		u8char[3] = src[j + 3];

		return char_utf32(u8char, number_of_byte);
	}

	// UTF-8(char*) から UTF-32(char32_t*)へ
	const char32_t* utf32(const char* src)
	{
		static std::u32string u32str;
		u32str = U"";

		char u8char[5]{};
		int32_t number_of_byte;

		for (size_t j = 0;;) {
			if (src[j] == 0) break;
			u32str += char_utf32(src, u8char, j, number_of_byte);
			if (number_of_byte) j += number_of_byte;
			else ++j;
		}
		return u32str.c_str();
	}

}

namespace As {

	class MapChipFormat {
	private:
		::As::Uint16 width = 32;   // 1 マップチップの横のピクセル数
		::As::Uint16 height = 32;   // 1 マップチップの縦のピクセル数
		::As::Uint16 x = 1; // 横のマップチップ数
		::As::Uint16 y = 1;   // 縦のマップチップ数
		::As::DataType::IndexUint start_index = 0;   // そのマップチップの最初の添え字番号
		::std::string str{}; // 識別
	public:
		// コンストラクタ
		MapChipFormat() = default;
		MapChipFormat(::As::Uint16 width_, ::As::Uint16 height_, ::As::Uint16 x_, ::As::Uint16 y_, ::As::DataType::IndexUint start_index_, const ::std::string& str_)
			:width(width_), height(height_), x(x_), y(y_), start_index(start_index_), str(str_) {}

		::As::Uint16 getX() const {
			return this->x;
		}
		::As::Uint16 getY() const {
			return this->y;
		}
		::As::Uint16 getNum() const {
			return (this->x * this->y);
		}
		::As::Uint16 getWidth() const {
			return this->width;
		}
		::As::Uint16 getHeight() const {
			return this->height;
		}
		::As::DataType::IndexUint getStartIndex() const {
			return this->start_index;
		}
		const ::std::string& getString() const {
			return this->str;
		}
		void setX(const ::As::Uint16 x_) {
			this->x = x_;
		}
		void setY(const ::As::Uint16 y_) {
			this->y = y_;
		}
		void setWidth(const ::As::Uint16 width_) {
			this->width = width_;
		}
		void setHeight(const ::As::Uint16 height_) {
			this->height = height_;
		}
		void setStartIndex(const ::As::DataType::IndexUint start_index_) {
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

		::As::DataType::Uint8 sea_alpha[16 * 10] = {
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
		::As::DataType::Uint8 desert_alpha[4 * 10] = {
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

		::As::DataType::Uint8 cliff_top_alpha[4 * 10] = {
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
			::As::Uint16 width_, ::As::Uint16 height_, ::As::Uint16 x_, ::As::Uint16 y_,
			::As::DataType::IndexUint& start_index_, const ::std::string& str_, 
//#if defined(__DXLIB)
			const ::std::string& link_
//#elif defined(SIV3D_INCLUDED)
//			const ::s3d::FilePathView& link_
//#endif
		) {

			map_chip_format.emplace_back(MapChipFormat(width_, height_, x_, y_, start_index_, str_));
			map_chip.resize(start_index_ + map_chip_format.back().getNum());
#if defined(__DXLIB)
			::DxLib::LoadDivGraph(link_.c_str(), int(x_ * y_),
				int(x_), int(y_),
				int(width_), int(height_), &(map_chip[start_index_]));
#elif defined(SIV3D_INCLUDED)
			texture_map_chip.emplace_back(::s3d::Texture(::As::utf32(link_)));
			for (::As::DataType::IndexUint y = 0, count = 0; y < y_; ++y)
				for (::As::DataType::IndexUint x = 0; x < x_; ++x, ++count) {
					map_chip[start_index_ + count] = (texture_map_chip.back()(double(width_ * x), double(height_ * y), double(width_), double(height_)));
				}
#endif
			start_index_ += map_chip_format.back().getNum();
		}


		MapChipImage(const ::std::string& path_, const ::Crafterra::ReadText& read_text) {

//#if defined(__DXLIB)

			::As::DataType::IndexUint index = 0;

			const auto& mat = read_text.getMatrix();
			if (mat.size() <= 1) return; // 画像データなし

			for (::As::DataType::IndexUint y = 1; y < mat.size(); ++y) {
				::As::Uint16 width{};
				::As::Uint16 height{};
				::As::Uint16 getx{};
				::As::Uint16 gety{};
				::As::DataType::IndexUint start_index{};
				::std::string tile{};
				::std::string label{};
				::std::string path{};
				for (::As::DataType::IndexUint x = 0; x < mat[y].size(); ++x) {
					if ((mat.front()[x]) == ::std::string("width")) width = ::As::Uint16(::Crafterra::getNum(mat[y][x]));
					else if ((mat.front()[x]) == ::std::string("height")) height = ::As::Uint16(::Crafterra::getNum(mat[y][x]));
					else if ((mat.front()[x]) == ::std::string("x")) getx = ::As::Uint16(::Crafterra::getNum(mat[y][x]));
					else if ((mat.front()[x]) == ::std::string("y")) gety = ::As::Uint16(::Crafterra::getNum(mat[y][x]));
					else if ((mat.front()[x]) == ::std::string("tile")) tile = mat[y][x];
					else if ((mat.front()[x]) == ::std::string("label")) label = mat[y][x];
					else if ((mat.front()[x]) == ::std::string("path")) path = mat[y][x];
				}
				loadMapChip(width, height, getx, gety, index, label, path_ + path);
			}

//#elif defined(SIV3D_INCLUDED)

			//::As::DataType::IndexUint index = 0;
			//loadMapChip(32, 32, 8, 133, index, "Base", U"./../../../../resource/Picture/Chip/Map/Base(pipoya).png");
			//loadMapChip(32, 32, 4, 10, index, "Cliff", U"./../../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png");
			//loadMapChip(16, 16, 16, 10, index, "Sea", U"./../../../../resource/Picture/Chip/AutoTile/Water1(pipoya).png");
			//loadMapChip(16, 16, 4, 10, index, "Desert", U"./../../../../resource/Picture/Chip/AutoTile/Dirt3(pipoya).png");
			//loadMapChip(16, 16, 4, 10, index, "Rock", U"./../../../../resource/Picture/Chip/AutoTile/Dirt2(pipoya).png");
			//loadMapChip(16, 16, 4, 10, index, "Savannah", U"./../../../../resource/Picture/Chip/AutoTile/Dirt1(pipoya).png");
			//loadMapChip(16, 16, 4, 10, index, "Mountain", U"./../../../../resource/Picture/Chip/AutoTile/Grass2(pipoya).png");
			//loadMapChip(16, 16, 4, 10, index, "Forest", U"./../../../../resource/Picture/Chip/AutoTile/Grass4(pipoya).png");
			//loadMapChip(16, 16, 4, 10, index, "Grass", U"./../../../../resource/Picture/Chip/AutoTile/LongGrass(pipoya).png");

//#endif // __DXLIB
		}

		~MapChipImage() {

		}
		Image_ getMapChip(const ::std::string& str_, const::As::DataType::IndexUint index_) const {
			for (const auto& mcf : map_chip_format) {
				if (mcf.getString() != str_) continue;
				return this->map_chip[mcf.getStartIndex() + index_];
			}
			return this->map_chip[0];
		}
		::As::DataType::Uint8 getSeaAlpha(const ::As::DataType::IndexUint index_) const { return this->sea_alpha[index_]; }
		bool getIsSeaAlpha(const ::As::DataType::IndexUint index_) const { return (this->sea_alpha[index_] == 0); }
		bool getIsAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_, const ::As::DataType::Uint8* const alpha_array_) const {
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
		::As::DataType::Uint8 getMapChipCliffTopAlpha(const ::As::DataType::IndexUint index_) const { return this->cliff_top_alpha[index_]; }

	};
}

#endif //Included Crafterra Library