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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_FONT_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_FONT_HPP

// #include <Windows.h>

namespace AsLib2 {

	class Font {
	private:

#ifdef __WINDOWS__
		LPCSTR font_path{};
		bool is_font = false;
#endif // __WINDOWS__
		int m_font = -1;

	public:

		Font() {
#ifdef __WINDOWS__
			font_path = "./../../../resource/Font/Misaki Gothic.ttf"; // 読み込むフォントファイルのパス
			is_font = (AddFontResourceEx(font_path, FR_PRIVATE, nullptr) != 0);
#endif // __WINDOWS__
#if defined(__DXLIB)
			if (is_font) m_font = ::DxLib::CreateFontToHandle(nullptr, 10, -1, -1, DX_CHARSET_SHFTJIS);
#endif // __DXLIB
		}

		~Font() {
#ifdef __WINDOWS__
			// フォントのアンロード
			if (is_font) {
				(RemoveFontResourceEx(font_path, FR_PRIVATE, nullptr));
			}
#endif // __WINDOWS__
		}

		int getFont() const { return this->m_font; }

	};
}

#endif //Included Crafterra Library