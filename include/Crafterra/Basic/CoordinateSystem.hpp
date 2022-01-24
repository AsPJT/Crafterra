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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_COORDINATE_SYSTEM_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_COORDINATE_SYSTEM_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>

namespace Crafterra {

	class CoordinateSystem {
	public:

		using cs_uint = IndexUint;
		using cs_int = Int32;
		using cs_f32 = float;

		using UintSize2D = ::Crafterra::Size2D<cs_uint>;
		using FloatSize2D = ::Crafterra::Size2D<cs_f32>;

		// ウィンドウの大きさ
		UintSize2D window_size;
		// フィールドマップの大きさ
		UintSize2D field_map_size;
	// private:
		// マップチップの大きさ
		FloatSize2D map_chip_size;
	public:
		// カメラの大きさ
		FloatSize2D camera_size;
		// マップグリッドの大きさ
		UintSize2D map_grid_size;
	public:
		void setMapChipWidth(const cs_f32 width_) {
			this->map_chip_size.setWidth(width_);
			this->camera_size.setWidth(cs_f32(this->window_size.getWidth()) / this->map_chip_size.getWidth());
		}
		void setMapChipHeight(const cs_f32 height_) {
			this->map_chip_size.setHeight(height_);
			this->camera_size.setHeight(cs_f32(this->window_size.getHeight()) / this->map_chip_size.getHeight());
		}
		void setMapChipSize(const cs_f32 size_) {
			this->setMapChipWidth(size_);
			this->setMapChipHeight(size_);
		}
		void setMapChipSize(const cs_f32 width_, const cs_f32 height_) {
			this->setMapChipWidth(width_);
			this->setMapChipHeight(height_);
		}

		void expandMapChipWidth(const cs_f32 width_) {
			this->map_chip_size.expandWidth(width_);
			this->camera_size.setWidth(cs_f32(this->window_size.getWidth()) / this->map_chip_size.getWidth());
		}
		void expandMapChipHeight(const cs_f32 height_) {
			this->map_chip_size.expandHeight(height_);
			this->camera_size.setHeight(cs_f32(this->window_size.getHeight()) / this->map_chip_size.getHeight());
		}
		void expandMapChipSize(const cs_f32 size_) {
			this->expandMapChipWidth(size_);
			this->expandMapChipHeight(size_);
		}
		void expandMapChipSize(const cs_f32 width_, const cs_f32 height_) {
			this->expandMapChipWidth(width_);
			this->expandMapChipHeight(height_);
		}

		CoordinateSystem(const cs_uint ww_, const cs_uint wh_) :
			window_size(ww_, wh_)
			, field_map_size(init_field_map_width, init_field_map_height)
			, map_chip_size(4.f, 4.f)
			, camera_size(
				field_map_size.getCenterX() - (cs_f32(window_size.getWidth()) / map_chip_size.getWidth()) / 2, // StartX
				field_map_size.getCenterY() - (cs_f32(window_size.getHeight()) / map_chip_size.getHeight()) / 2, // StartY
				(cs_f32(window_size.getWidth()) / map_chip_size.getWidth()), // Width
				(cs_f32(window_size.getHeight()) / map_chip_size.getHeight())) // Height
			, map_grid_size(1, 1)
		{
		}

		// 2D カメラ ( マップのピクセル数が一律の場合のみ使用可能 )
		template<typename Draw_>
		void updateCamera(Draw_ drawRect_) {
			const cs_uint sy = cs_uint((cs_int(this->camera_size.getStartY()) < cs_int(this->field_map_size.getStartY())) ?
				cs_uint(this->field_map_size.getStartY()) : cs_uint(this->camera_size.getStartY()));

			cs_f32 camera_y =
				((cs_int(this->camera_size.getStartY()) >= cs_int(this->field_map_size.getStartY())) ?
				((cs_f32(cs_int(this->camera_size.getStartY())) - this->camera_size.getStartY()) * cs_f32(this->map_chip_size.getHeight())) :
					(cs_f32(this->window_size.getHeightHalf()) - (this->camera_size.getCenterY() - cs_f32(this->field_map_size.getStartY())) * cs_f32(this->map_chip_size.getHeight())));

			for (cs_uint y = sy; y < this->field_map_size.getEndY(); ++y) {

				const cs_uint sx = cs_uint((cs_int(this->camera_size.getStartX()) < cs_int(this->field_map_size.getStartX())) ?
					cs_uint(this->field_map_size.getStartX()) : cs_uint(this->camera_size.getStartX()));

				cs_f32 camera_x =
					((cs_int(this->camera_size.getStartX()) >= cs_int(this->field_map_size.getStartX())) ?
					((cs_f32(cs_int(this->camera_size.getStartX())) - this->camera_size.getStartX()) * cs_f32(this->map_chip_size.getWidth())) :
						(cs_f32(this->window_size.getWidthHalf()) - (this->camera_size.getCenterX() - cs_f32(this->field_map_size.getStartX())) * cs_f32(this->map_chip_size.getWidth())));

				for (cs_uint x = sx; x < this->field_map_size.getEndX(); ++x) {

					drawRect_(
						camera_x, camera_y, // 描画開始位置
						this->map_chip_size.getWidth(), this->map_chip_size.getHeight(), // 描画幅・長さ
						x, y
					);

					camera_x += this->map_chip_size.getWidth();
					if (camera_x >= this->window_size.getEndX()) break;
				}
				camera_y += this->map_chip_size.getHeight();
				if (camera_y >= this->window_size.getEndY()) break;
			}
		}

	};

}

#endif //Included Crafterra Library