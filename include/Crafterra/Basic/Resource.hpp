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

#include <AsLib2C/DataType/PrimitiveDataType.hpp>

namespace AsLib2 {
	class Font;
	class Music;
	class MapChipImage;
	class CharacterChipImage;
}

namespace Crafterra {

	class Resource {

		// 各種素材のポインタ
	private:
		::AsLib2::Font* font = nullptr;
		::AsLib2::Music* music = nullptr;
		::AsLib2::MapChipImage* map_chip = nullptr;
		::AsLib2::CharacterChipImage* character_chip = nullptr;

	public:
		void setFont(::AsLib2::Font& font_) { this->font = &font_; }
		::AsLib2::Font& getFont() { return *(this->font); }
		void setMusic(::AsLib2::Music& music_) { this->music = &music_; }
		::AsLib2::Music& getMusic() { return *(this->music); }
		void setMapChip(::AsLib2::MapChipImage& map_chip_) { this->map_chip = &map_chip_; }
		::AsLib2::MapChipImage& getMapChip() { return *(this->map_chip); }
		void setCharacterChip(::AsLib2::CharacterChipImage& character_chip_) { this->character_chip = &character_chip_; }
		::AsLib2::CharacterChipImage& getCharacterChip() { return *(this->character_chip); }

	private:
		Asc::DataType::IndexUint window_width = 0;
		Asc::DataType::IndexUint window_height = 0;

	public:
		void setWindowWidth(const ::Asc::DataType::IndexUint window_width_) { this->window_width = window_width_; }
		void setWindowHeight(const ::Asc::DataType::IndexUint window_height_) { this->window_height = window_height_; }
		::Asc::DataType::IndexUint getWindowWidth() const { return this->window_width; }
		::Asc::DataType::IndexUint getWindowHeight() const { return this->window_height; }
	};

}

#endif //Included Crafterra Library