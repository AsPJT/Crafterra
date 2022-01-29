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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_CHARACTER_CHIP_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_CHARACTER_CHIP_HPP

#include <vector>

namespace As {

	// キャラチップの状態
	struct CharacterChipStatus {
		int move_num = 4;
		int animation_num = 3;
		int size_x = 32;
		int size_y = 32;
	};

	class CharacterChipImage {
	private:

		// 0 1 2
		// 3 4 5
		// 6 7 8
		// 9 a b
		::std::vector<int> character_chip{};
		::std::vector<int> character_start_index_chip{};
		int start_index = 0;
		//int player_index = 0;

		void add(const int move_num_, const int animation_num_, const ::std::string& file_name_) {
			const int all_num = move_num_ * animation_num_;
			this->character_chip.resize(this->character_chip.size() + all_num);
#if defined(__DXLIB)
			::DxLib::LoadDivGraph(file_name_.c_str(),
				all_num, animation_num_, move_num_, 32, 32, &(this->character_chip[start_index]));
#endif // __DXLIB
			// そのキャラの開始インデックスを格納
			this->character_start_index_chip.emplace_back(start_index);
			start_index += all_num;
		}

	public:

		CharacterChipImage() {
			this->add(4, 3, "./../../../resource/Picture/Chip/Character/pipo-airship01.png");
			this->add(4, 3, "./../../../resource/Picture/Chip/Character/pipo-charachip026c.png");
		}

		~CharacterChipImage() {

		}

		int getCharacterChip(const ::As::IndexUint character_id_, const ::As::IndexUint index_) const {
			return this->character_chip[::As::IndexUint(this->character_start_index_chip[character_id_]) + index_];
		}

	};
}

#endif //Included Crafterra Library