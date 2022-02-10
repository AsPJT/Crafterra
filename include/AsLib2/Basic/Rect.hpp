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

#if defined(__DXLIB)
	using RectDataType = int;
#else
	using RectDataType = double;
#endif

	struct Rect {
		using Rect_ = RectDataType;
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


	class Image {
	private:

#if defined(__DXLIB)
		using Image_ = int;
		Image_ handle = -1;
#elif defined(SIV3D_INCLUDED)
		using Image_ = ::s3d::TextureRegion;
		Image_ handle{};
#endif

	public:
		Image() = default;

#if defined(__DXLIB)
		Image(const Image_ handle_) :handle(handle_) {};
#endif // __DXLIB

		void draw(const Rect& rect_) const {
#if defined(__DXLIB)
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y, rect_.start_x + rect_.width, rect_.start_y + rect_.height, this->handle, TRUE);
#elif defined(SIV3D_INCLUDED)
			handle.resized(rect_.width, rect_.height).draw(rect_.start_x, rect_.start_y);
#endif // __DXLIB
		}
#if defined(SIV3D_INCLUDED)
		Image(::s3d::Texture& handle_, const double start_x_, const double start_y_, const double width_, const double height_)
			:handle(handle_(start_x_, start_y_, width_, height_)) {};
		void set(::s3d::Texture& handle_, const double start_x_, const double start_y_, const double width_, const double height_) {
			this->handle = handle_(start_x_, start_y_, width_, height_);
		}
#endif // __DXLIB
		Image_& get() {
			return this->handle;
		}
	};


	class ImageQuadrant {
	private:
		::As::Image& handle1;
		::As::Image& handle2;
		::As::Image& handle3;
		::As::Image& handle4;

	public:
		ImageQuadrant(::As::Image& handle_) :handle1(handle_), handle2(handle_), handle3(handle_), handle4(handle_) {};
		ImageQuadrant(::As::Image& handle1_, ::As::Image& handle2_, ::As::Image& handle3_, ::As::Image& handle4_) :handle1(handle1_), handle2(handle2_), handle3(handle3_), handle4(handle4_) {};

		void draw(const Rect& rect_) const {
#ifdef __DXLIB
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y, rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2, this->handle1.get(), TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x + rect_.width / 2, rect_.start_y, rect_.start_x + rect_.width, rect_.start_y + rect_.height / 2, this->handle2.get(), TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x, rect_.start_y + rect_.height / 2, rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height, this->handle3.get(), TRUE);
			::DxLib::DrawExtendGraph(rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2, rect_.start_x + rect_.width, rect_.start_y + rect_.height, this->handle4.get(), TRUE);
#else
			handle1.get().resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x, rect_.start_y);
			handle2.get().resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x + rect_.width / 2, rect_.start_y);
			handle3.get().resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x, rect_.start_y + rect_.height / 2);
			handle4.get().resized(rect_.width / 2, rect_.height / 2).draw(rect_.start_x + rect_.width / 2, rect_.start_y + rect_.height / 2);
#endif // __DXLIB
		}
	};


}

#endif //Included AsLib2