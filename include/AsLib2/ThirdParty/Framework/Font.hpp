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
#if defined(SIV3D_INCLUDED)
#include <AsLib2/Basic/Unicode.hpp>
#endif // SIV3D_INCLUDED

namespace As {

	class Font {
	private:

#ifdef __WINDOWS__
		LPCSTR font_path{};
		bool is_font = false;
#endif // __WINDOWS__
		int m_font = -1;

#if defined(SIV3D_INCLUDED)
		::s3d::Font font;
#endif // __DXLIB

	public:

		Font() {
#ifdef __WINDOWS__
			font_path = "./../../../resource/Font/Misaki Gothic.ttf"; // 読み込むフォントファイルのパス
			is_font = (AddFontResourceEx(font_path, FR_PRIVATE, nullptr) != 0);
#endif // __WINDOWS__
#if defined(__DXLIB)
			if (is_font) m_font = ::DxLib::CreateFontToHandle(nullptr, 10, -1, -1, DX_CHARSET_SHFTJIS);
#elif defined(SIV3D_INCLUDED)
			font = ::s3d::Font(12);
#endif // __DXLIB
		}

		~Font() {
#if defined(__DXLIB)
#ifdef __WINDOWS__
			// フォントのアンロード
			if (is_font) {
				(RemoveFontResourceEx(font_path, FR_PRIVATE, nullptr));
			}
#endif // __WINDOWS__
#endif
		}

		int getFont() const { return this->m_font; }

		void draw(const int x_, const int y_, const ::std::string& str_) {
#if defined(__DXLIB)
			::DxLib::DrawStringToHandle(x_, y_, str_.c_str(), 0xffffffff, m_font);
#elif defined(SIV3D_INCLUDED)
			font(::As::utf32(str_)).draw(x_, y_);
#endif // __DXLIB
		}

	};
}

#endif //Included Crafterra Library