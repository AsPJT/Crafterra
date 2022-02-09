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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_RESOURCE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_RESOURCE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>

namespace As {
	class Font;
	class Music;
	class MapChipImage;
	class CharacterChipImage;
}

namespace Crafterra {

	class Resource {

		// 各種素材のポインタ
	private:
		::As::Font*					font			 = nullptr; // フォント
		::As::Music*				music			 = nullptr; // 音楽
		::As::MapChipImage*		map_chip		 = nullptr; // マップチップ
		::As::MapChipImage*		character_chip	 = nullptr; // キャラチップ

	public:
		void setFont(::As::Font& font_) { this->font = &font_; }
		::As::Font& getFont() { return *(this->font); }
		void setMusic(::As::Music& music_) { this->music = &music_; }
		::As::Music& getMusic() { return *(this->music); }
		void setMapChip(::As::MapChipImage& map_chip_) { this->map_chip = &map_chip_; }
		::As::MapChipImage& getMapChip() { return *(this->map_chip); }
		void setCharacterChip(::As::MapChipImage& character_chip_) { this->character_chip = &character_chip_; }
		::As::MapChipImage& getCharacterChip() { return *(this->character_chip); }

	private:
		As::IndexUint window_width = 0;
		As::IndexUint window_height = 0;

	public:
		void setWindowWidth(const ::As::IndexUint window_width_) { this->window_width = window_width_; }
		void setWindowHeight(const ::As::IndexUint window_height_) { this->window_height = window_height_; }
		::As::IndexUint getWindowWidth() const { return this->window_width; }
		::As::IndexUint getWindowHeight() const { return this->window_height; }
	};

}

#endif //Included Crafterra Library