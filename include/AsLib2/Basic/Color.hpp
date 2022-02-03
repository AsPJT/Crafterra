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

#ifndef INCLUDED_ASLIB2_ASLIB2_BASIC_COLOR_HPP
#define INCLUDED_ASLIB2_ASLIB2_BASIC_COLOR_HPP

namespace As {

	class Color {
	private:

		using ColorType_ = int;
#ifdef ASLIB2_USE_DXLIB
		using ColorTypeGet_ = unsigned int;
#elif defined(SIV3D_INCLUDED)
		using ColorTypeGet_ = ::s3d::Color;
#else
		using ColorTypeGet_ = unsigned int;
#endif // ASLIB2_USE_DXLIB

		ColorType_ r{}, g{}, b{}, a{};
	public:
		// コンストラクタ
		Color() = default;
		Color(const ColorType_ rgb_) :r(rgb_), g(rgb_), b(rgb_) {}
		Color(const ColorType_ rgb_, const ColorType_ a_) :r(rgb_), g(rgb_), b(rgb_), a(a_) {}
		Color(const ColorType_ r_, const ColorType_ g_, const ColorType_ b_) :r(r_), g(g_), b(b_) {}
		Color(const ColorType_ r_, const ColorType_ g_, const ColorType_ b_, const ColorType_ a_) :r(r_), g(g_), b(b_), a(a_) {}

		ColorType_ getRed() const { return this->r; }
		ColorType_ getAlpha() const { return this->a; }
		bool isAlpha() const { return this->a != 0; }

		ColorTypeGet_ getColor() {
#ifdef ASLIB2_USE_DXLIB
			return ::DxLib::GetColor(this->r, this->g, this->b);
#elif defined(SIV3D_INCLUDED)
			return ::s3d::Color(::As::Uint8(this->r), ::As::Uint8(this->g), ::As::Uint8(this->b), ::As::Uint8(255 - this->a));
#else
			return 0;
#endif // ASLIB2_USE_DXLIB
		}

	};

}

#endif //Included AsLib2