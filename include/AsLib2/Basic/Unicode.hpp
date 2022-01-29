/*##########################################################################################

	AsLib2 🌏

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

#ifndef INCLUDED_ASLIB2_ASLIB2_BASIC_UNICODE_HPP
#define INCLUDED_ASLIB2_ASLIB2_BASIC_UNICODE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>

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

		for (::As::IndexUint j = 0;; ++j) {

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

		const ::As::IndexUint src_len = src.length();
		for (::As::IndexUint j = 0; j < src_len; ++j) {

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

	::As::Int32 utf8Byte(char src) {
		if (0 <= ::As::Uint8(src) && ::As::Uint8(src) < 0x80) return 1;
		if (0xc2 <= ::As::Uint8(src) && ::As::Uint8(src) < 0xe0) return 2;
		if (0xe0 <= ::As::Uint8(src) && ::As::Uint8(src) < 0xf0) return 3;
		if (0xf0 <= ::As::Uint8(src) && ::As::Uint8(src) < 0xf8) return 4;
		return 0;
	}

	bool utf8_0x80To0xc0(char src) { return 0x80 <= ::As::Uint8(src) && ::As::Uint8(src) < 0xc0; }

	const char32_t char_utf32(const char src[5], ::As::Int32& number_of_byte) {
		char32_t u32char{};

		number_of_byte = utf8Byte(src[0]);
		if (number_of_byte == 0) return u32char;

		switch (number_of_byte) {

		case 1:u32char = char32_t(::As::Uint8(src[0])); break;

		case 2:
			if (!utf8_0x80To0xc0(src[1])) return u32char;
			if ((::As::Uint8(src[0]) & 0x1e) == 0) return u32char;

			u32char = char32_t(src[0] & 0x1f) << 6;
			u32char |= char32_t(src[1] & 0x3f);
			break;

		case 3:
			if (!utf8_0x80To0xc0(src[1]) || !utf8_0x80To0xc0(src[2])) return u32char;
			if ((::As::Uint8(src[0]) & 0x0f) == 0 && (::As::Uint8(src[1]) & 0x20) == 0) return u32char;

			u32char = char32_t(src[0] & 0x0f) << 12;
			u32char |= char32_t(src[1] & 0x3f) << 6;
			u32char |= char32_t(src[2] & 0x3f);
			break;

		case 4:
			if (!utf8_0x80To0xc0(src[1]) || !utf8_0x80To0xc0(src[2]) || !utf8_0x80To0xc0(src[3])) return u32char;
			if ((::As::Uint8(src[0]) & 0x07) == 0 && (::As::Uint8(src[1]) & 0x30) == 0) return u32char;

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
		::As::Int32 number_of_byte;
		u8char[0] = src;

		u32char[0] = char_utf32(u8char, number_of_byte);
		u32char[1] = 0;
		return u32char;
	}

	const char32_t char_utf32(const std::string& src, char u8char[5], const ::As::IndexUint j, ::As::Int32& number_of_byte) {
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
		::As::Int32 number_of_byte;

		const ::As::IndexUint src_len = src.length();
		for (::As::IndexUint j = 0; j < src_len;) {
			if (src[j] == 0) break;
			u32str += char_utf32(src, u8char, j, number_of_byte);
			if (number_of_byte) j += number_of_byte;
			else ++j;
		}
		return u32str.c_str();
	}

	const char32_t char_utf32(const char* src, char u8char[5], const ::As::IndexUint j, ::As::Int32& number_of_byte) {
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
	const char32_t* utf32(const char* src) {
		static std::u32string u32str;
		u32str = U"";

		char u8char[5]{};
		::As::Int32 number_of_byte;

		for (::As::IndexUint j = 0;;) {
			if (src[j] == 0) break;
			u32str += char_utf32(src, u8char, j, number_of_byte);
			if (number_of_byte) j += number_of_byte;
			else ++j;
		}
		return u32str.c_str();
	}

}

#endif //Included AsLib2