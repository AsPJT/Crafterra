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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_SIZE2D_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_SIZE2D_HPP

namespace Crafterra {

	template<typename SizeType_>
	class Size2D {
	private:

		SizeType_ start_x;
		SizeType_ start_y;
		SizeType_ center_x;
		SizeType_ center_y;
		SizeType_ end_x;
		SizeType_ end_y;

		SizeType_ width;
		SizeType_ height;
		SizeType_ width_half;
		SizeType_ height_half;

	public:
		// コンストラクタ ( 幅と高さを指定 )
		constexpr Size2D(const SizeType_ width_, const SizeType_ height_) :
			width(width_), height(height_)
			, width_half(width_ / 2), height_half(height_ / 2)
			, start_x(0), start_y(0)
			, center_x(width_ / 2), center_y(height_ / 2)
			, end_x(width_), end_y(height_) {}

		// コンストラクタ ( 開始座標 X と Y 、幅と高さを指定 )
		constexpr Size2D(const SizeType_ start_x_, const SizeType_ start_y_, const SizeType_ width_, const SizeType_ height_) :
			width(width_), height(height_)
			, width_half(width_ / 2), height_half(height_ / 2)
			, start_x(start_x_), start_y(start_y_)
			, center_x(start_x_ + width_ / 2), center_y(start_y_ + height_ / 2)
			, end_x(start_x_ + width_), end_y(start_y_ + height_) {}

		constexpr SizeType_ getStartX() const { return this->start_x; }
		constexpr SizeType_ getStartY() const { return this->start_y; }
		constexpr SizeType_ getCenterX() const { return this->center_x; }
		constexpr SizeType_ getCenterY() const { return this->center_y; }
		constexpr SizeType_ getEndX() const { return this->end_x; }
		constexpr SizeType_ getEndY() const { return this->end_y; }
		constexpr SizeType_ getWidth() const { return this->width; }
		constexpr SizeType_ getHeight() const { return this->height; }
		constexpr SizeType_ getWidthHalf() const { return this->width_half; }
		constexpr SizeType_ getHeightHalf() const { return this->height_half; }

		void moveX(const SizeType_ move_value_) {
			this->start_x += move_value_;
			this->center_x += move_value_;
			this->end_x += move_value_;
		}

		void moveY(const SizeType_ move_value_) {
			this->start_y += move_value_;
			this->center_y += move_value_;
			this->end_y += move_value_;
		}
		//void setStartX(const SizeType_ value_) { this->start_x = value_; }
		//void setStartY(const SizeType_ value_) { this->start_y = value_; }
		//void setCenterX(const SizeType_ value_) { this->center_x = value_; }
		//void setCenterY(const SizeType_ value_) { this->center_y = value_; }
		//void setEndX(const SizeType_ value_) { this->end_x = value_; }
		//void setEndY(const SizeType_ value_) { this->end_y = value_; }

		// 幅を拡大・縮小する
		void expandWidth(const SizeType_ expand_value_) {
			this->width *= expand_value_;
			this->width_half = this->width / 2;
			this->start_x = (this->center_x - this->width_half);
			this->end_x = (this->center_x + this->width_half);
		}
		// 高さを拡大・縮小する
		void expandHeight(const SizeType_ expand_value_) {
			this->height *= expand_value_;
			this->height_half = this->width / 2;
			this->start_y = (this->center_y - this->height_half);
			this->end_y = (this->center_y + this->height_half);
		}
		void expandSize(const SizeType_ expand_value_) {
			this->expandWidth(expand_value_);
			this->expandHeight(expand_value_);
		}
		void expandWidthHalf(const SizeType_ expand_value_) { this->expandWidth(expand_value_ * 2); }
		void expandHeightHalf(const SizeType_ expand_value_) { this->expandHeight(expand_value_ * 2); }

		void setWidth(const SizeType_ value_) {
			this->width = value_;
			this->width_half = value_ / 2;
			this->start_x = (this->center_x - this->width_half);
			this->end_x = (this->center_x + this->width_half);
		}
		void setHeight(const SizeType_ value_) {
			this->height = value_;
			this->height_half = value_ / 2;
			this->start_y = (this->center_y - this->height_half);
			this->end_y = (this->center_y + this->height_half);
		}
		void setSize(const SizeType_ value_) {
			this->setWidth(value_);
			this->setHeight(value_);
		}
		void setWidthHalf(const SizeType_ value_) { this->setWidth(value_ * 2); }
		void setHeightHalf(const SizeType_ value_) { this->setHeight(value_ * 2); }
	};

}

#endif //Included Crafterra Library