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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_INIT_READ_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_INIT_READ_HPP

#include <fstream>
#include <sstream>

#include <Crafterra/DataType/StringDataType.hpp>

namespace Crafterra {

	class InitRead {
	private:
		bool is_fullscreen = false;
		bool is_fullscreen_flag = false;
		bool is_window_width_flag = false;
		bool is_window_height_flag = false;
		int window_width = ::Crafterra::System::init_window_width;
		int window_height = ::Crafterra::System::init_window_height;

		int getNum(const ::Crafterra::DataType::String& str_) const {
			int num = 0;
			for (auto& s : str_) {
				switch (s) {
				case '0': num = num * 10; break;
				case '1': num = num * 10 + 1; break;
				case '2': num = num * 10 + 2; break;
				case '3': num = num * 10 + 3; break;
				case '4': num = num * 10 + 4; break;
				case '5': num = num * 10 + 5; break;
				case '6': num = num * 10 + 6; break;
				case '7': num = num * 10 + 7; break;
				case '8': num = num * 10 + 8; break;
				case '9': num = num * 10 + 9; break;
				default:return -1;
				}
			}
			return num;
		}

		void setBool(bool& flag_, const ::Crafterra::DataType::String& label_buf_, const ::Crafterra::DataType::String& label_) {
			if (flag_) {
				flag_ = false;
				is_fullscreen = (label_buf_ == ::Crafterra::DataType::String("ON") || label_buf_ == ::Crafterra::DataType::String("on"));
			}
			// フルスクリーンフラグ
			else flag_ = (label_buf_ == label_);
		}

		void setInt(bool& flag_, int& value_, const ::Crafterra::DataType::String& label_buf_, const ::Crafterra::DataType::String& label_) {
			if (flag_) {
				flag_ = false;
				value_ = getNum(label_buf_);
			}
			// フルスクリーンフラグ
			else flag_ = (label_buf_ == label_);
		}


	public:



		InitRead(const ::Crafterra::DataType::String& path_) {
			::Crafterra::DataType::String str_buf{}, str_conma_buf{}, input_csv_file_path = path_;
			std::ifstream ifs(input_csv_file_path);
			if (!ifs) return;

			while (getline(ifs, str_buf)) {
				std::istringstream ifss(str_buf);
				while (getline(ifss, str_conma_buf, ':')) {

					setBool(is_fullscreen_flag, str_conma_buf, "Fullscreen");
					setInt(is_window_width_flag, window_width, str_conma_buf, "Window Width");
					setInt(is_window_height_flag, window_height, str_conma_buf, "Window Height");



				}
			}

		}


		bool isFullscreen() const { return this->is_fullscreen; }
		int getWindowWidth() const { return this->window_width; }
		int getWindowHeight() const { return this->window_height; }

	};

}


#endif //Included Crafterra Library