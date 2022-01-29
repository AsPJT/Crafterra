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

#ifndef INCLUDED_ASLIB2_ASLIB2_BASIC_RECT_HPP
#define INCLUDED_ASLIB2_ASLIB2_BASIC_RECT_HPP

namespace As {

	struct Rect {
#ifdef __DXLIB
		using Rect_ = int;
#else
		using Rect_ = double;
#endif
		Rect_ start_x{};
		Rect_ start_y{};
		Rect_ width{};
		Rect_ height{};

		// コンストラクタ
		Rect() = default;
		Rect(const Rect_ start_x_, const Rect_ start_y_, const Rect_ width_, const Rect_ height_)
			: start_x(start_x_), start_y(start_y_), width(width_), height(height_) {}
		Rect(const Rect_ start_x_, const Rect_ start_y_, const Rect_ size_)
			: start_x(start_x_), start_y(start_y_), width(size_), height(size_) {}
	};

#ifdef __DXLIB
	class Image {
	private:
		int handle = -1;
	public:
		Image(const int handle_) :handle(handle_) {};

		void draw(const Rect& rect_) const {
#ifdef __DXLIB
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y, rect_.start_x + rect_.width, rect_.start_y + rect_.height, this->handle, TRUE);
#endif // __DXLIB
		}
	};
#else
	class Image {
	private:
		const ::s3d::TextureRegion& handle;
	public:
		Image(const ::s3d::TextureRegion& handle_) :handle(handle_) {};

		void draw(const Rect& rect_) const {
			handle.resized(rect_.width, rect_.height).draw(rect_.start_x, rect_.start_y);
			//handle.draw(rect_.start_x, rect_.start_y);
#ifdef __DXLIB
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y, rect_.start_x + rect_.width, rect_.start_y + rect_.height, this->handle, TRUE);
#endif // __DXLIB
		}
	};
#endif // __DXLIB


#ifdef __DXLIB
	class ImageQuadrant {
	private:
		int handle1 = -1;
		int handle2 = -1;
		int handle3 = -1;
		int handle4 = -1;

	public:
		ImageQuadrant(const int handle_) :handle1(handle_), handle2(handle_), handle3(handle_), handle4(handle_) {};
		ImageQuadrant(const int handle1_, const int handle2_, const int handle3_, const int handle4_) :handle1(handle1_), handle2(handle2_), handle3(handle3_), handle4(handle4_) {};

		void draw(const Rect& rect_) const {
#ifdef __DXLIB
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y, rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2, this->handle1, TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x + rect_.width / 2, rect_.start_y, rect_.start_x + rect_.width, rect_.start_y + rect_.height / 2, this->handle2, TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y + rect_.height / 2, rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height, this->handle3, TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2, rect_.start_x + rect_.width, rect_.start_y + rect_.height, this->handle4, TRUE);
#endif // __DXLIB
		}
	};
#else
	class ImageQuadrant {
	private:
		const ::s3d::TextureRegion& handle1{};
		const ::s3d::TextureRegion& handle2{};
		const ::s3d::TextureRegion& handle3{};
		const ::s3d::TextureRegion& handle4{};

	public:
		ImageQuadrant(const ::s3d::TextureRegion& handle_) :handle1(handle_), handle2(handle_), handle3(handle_), handle4(handle_) {};
		ImageQuadrant(const ::s3d::TextureRegion& handle1_, const ::s3d::TextureRegion& handle2_, const ::s3d::TextureRegion& handle3_, const ::s3d::TextureRegion& handle4_) :handle1(handle1_), handle2(handle2_), handle3(handle3_), handle4(handle4_) {};

		void draw(const Rect& rect_) const {
			handle1.resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x, rect_.start_y);
			handle2.resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x + rect_.width / 2, rect_.start_y);
			handle3.resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x, rect_.start_y + rect_.height / 2);
			handle4.resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2);
#ifdef __DXLIB
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y, rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2, this->handle1, TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x + rect_.width / 2, rect_.start_y, rect_.start_x + rect_.width, rect_.start_y + rect_.height / 2, this->handle2, TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y + rect_.height / 2, rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height, this->handle3, TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2, rect_.start_x + rect_.width, rect_.start_y + rect_.height, this->handle4, TRUE);
#endif // __DXLIB
		}
	};
#endif // __DXLIB

}

#endif //Included AsLib2