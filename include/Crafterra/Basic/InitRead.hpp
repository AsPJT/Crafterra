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

#include <vector>

#include <AsLib2C/DataType/StringDataType.hpp>

namespace Crafterra {

	Asc::DataType::Int32 getNum(const ::Asc::DataType::String& str_) {
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

	struct ReadBool {
		::Asc::DataType::String label;
		bool value{};
	};
	struct ReadInt {
		::Asc::DataType::String label;
		Asc::DataType::Int32 value{};
	};
	struct ReadString {
		::Asc::DataType::String label;
		::Asc::DataType::String value{};
	};

	struct ReadArray {
		::std::vector<ReadBool> bool_value;
		::std::vector<ReadInt> int_value;
		::std::vector<ReadString> string_value;
	};

	class ReadText {
	private:
		std::vector<std::vector<std::string>> string_matrix{}; // TSV ファイルの二次元配列

	public:
		// コンストラクタ
		ReadText(const ::Asc::DataType::String& path_, const char char_ = '\t') {
			::Asc::DataType::String str_buf{}, str_conma_buf{};
			std::ifstream ifs(path_);
			if (!ifs) return;

			// 二次元配列に文字列を格納
			while (::std::getline(ifs, str_buf)) {
				std::istringstream ifss(str_buf);
				this->string_matrix.emplace_back(std::vector<std::string>{});

				while (::std::getline(ifss, str_conma_buf, char_)) {
					this->string_matrix.back().emplace_back(str_conma_buf);
				}
			}

		}
		// 二次元配列を返す
		const std::vector<std::vector<std::string>>& getMatrix() const {
			return this->string_matrix;
		}

	};

	class InitRead {
	private:

		ReadArray read_array{};

		::Asc::DataType::String path{};

		Asc::DataType::Int32 getNum(const ::Asc::DataType::String& str_) const {
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


	public:



		InitRead(const ::Asc::DataType::String& path_) {
			::Asc::DataType::String str_buf{}, str_conma_buf{}, input_csv_file_path = path_;
			std::ifstream ifs(input_csv_file_path);
			if (!ifs) return;

			while (::std::getline(ifs, str_buf)) {
				std::istringstream ifss(str_buf);

				::Asc::DataType::String data_type{}, label{}, value{};
				if (!(::std::getline(ifss, data_type, '\t'))) continue;
				if (!(::std::getline(ifss, label, '\t'))) continue;
				if (!(::std::getline(ifss, value, '\t'))) continue;

				if (data_type == "bool") {
					read_array.bool_value.emplace_back(ReadBool{ label , (value == ::Asc::DataType::String("yes")) });
				}
				else if (data_type == "int") {
					read_array.int_value.emplace_back(ReadInt{ label , getNum(value) });
				}
				else if (data_type == "string") {
					read_array.string_value.emplace_back(ReadString{ label , value });
				}

			}

		}

		bool getBool(const ::Asc::DataType::String& label_) {
			for (const auto& bv : read_array.bool_value) {
				if (bv.label == label_) return bv.value;
			}
			return false;
		}
		Asc::DataType::Int32 getInt(const ::Asc::DataType::String& label_) {
			for (const auto& iv : read_array.int_value) {
				if (iv.label == label_) return iv.value;
			}
			return 0;
		}
		::Asc::DataType::String getString(const ::Asc::DataType::String& label_) {
			for (const auto& sv : read_array.string_value) {
				if (sv.label == label_) return sv.value;
			}
			return ::Asc::DataType::String{};
		}


	};

}


#endif //Included Crafterra Library