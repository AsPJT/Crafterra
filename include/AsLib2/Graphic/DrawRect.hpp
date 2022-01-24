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

#ifndef INCLUDED_ASLIB2_ASLIB2_GRAPHIC_DRAW_RECT_HPP
#define INCLUDED_ASLIB2_ASLIB2_GRAPHIC_DRAW_RECT_HPP

#include <AsLib2/Basic/Color.hpp>
#include <AsLib2/Basic/Rect.hpp>

namespace AsLib2 {

	class DrawRect {
	public:
		Rect rect{};
		Color color{};

		// コンストラクタ
		DrawRect() = default;
		DrawRect(const Rect& rect_, const Color& color_) :rect(rect_), color(color_) {}

		void draw() {
			if (rect.width == 0 || rect.height == 0) return;
#ifdef ASLIB2_USE_DXLIB
			if (color.isAlpha()) ::DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.getAlpha());
			::DxLib::DrawBox(rect.start_x, rect.start_y, rect.start_x + rect.width, rect.start_y + rect.height, color.getColor(), TRUE);
			if (color.isAlpha()) ::DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif // ASLIB2_USE_DXLIB
		}

	};

}

#endif //Included AsLib2