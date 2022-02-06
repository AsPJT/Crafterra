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

#ifndef INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_MATRIX_HPP
#define INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_MATRIX_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <memory>
#include <new>

namespace As {
	inline namespace DataType {

		template<typename Type_>
		class UniquePtrMatrix {
		private:
			::std::unique_ptr<Type_[]> matrix{};
			::As::IndexUint width{};
			::As::IndexUint depth{};
		public:
			UniquePtrMatrix(const ::As::IndexUint num_x_, const ::As::IndexUint num_z_) :
				matrix(new(::std::nothrow) Type_[num_x_ * num_z_]), width(num_x_), depth(num_z_) {}
			template<typename Struct_>
			UniquePtrMatrix(const Struct_& struct_) :
				matrix(new(::std::nothrow) Type_[struct_.depth * struct_.width])
				, depth(struct_.depth)
				, width(struct_.width)
			{}

			// 配列を取得
			Type_* const operator[](const ::As::IndexUint z_) const {
				return this->matrix.get() + z_ * this->width;
			}

			::As::IndexUint size() const { return this->width * this->depth; }
			::As::IndexUint getSize() const { return this->width * this->depth; }
			::As::IndexUint getWidth() const { return this->width; }
			::As::IndexUint getDepth() const { return this->depth; }

		};

		// 4 次元配列管理
		template<typename Type_>
		class UniquePtrMatrix4D {
		private:
			::std::unique_ptr<Type_[]> matrix{};
			::As::IndexUint depth{}; // 奥行
			::As::IndexUint width{}; // 幅
			::As::IndexUint height{}; // 高さ
			::As::IndexUint layer{}; // 層
		public:
			UniquePtrMatrix4D(const ::As::IndexUint num_x_, const ::As::IndexUint num_y_, const ::As::IndexUint num_z_, const ::As::IndexUint num_l_) :
				matrix(new(::std::nothrow) Type_[num_x_ * num_y_ * num_z_ * num_l_])
				, depth(num_z_)
				, width(num_x_)
				, height(num_y_)
				, layer(num_l_)
			{}
			template<typename Struct_>
			UniquePtrMatrix4D(const Struct_& struct_) :
				matrix(new(::std::nothrow) Type_[struct_.depth * struct_.width * struct_.height * struct_.layer])
				, depth(struct_.depth)
				, width(struct_.width)
				, height(struct_.height)
				, layer(struct_.layer)
			{}

			// 配列の添え字を取得
			::As::IndexUint getIndexZX(const ::As::IndexUint z_, const ::As::IndexUint x_) const {
				return z_ * width + x_;
			}
			// 配列の添え字を取得
			::As::IndexUint getIndexMulZX(const ::As::IndexUint z_, const ::As::IndexUint x_) const {
				return this->getIndexZX(z_, x_) * height;
			}
			// 配列の添え字を取得
			::As::IndexUint getIndexZXY(const ::As::IndexUint z_, const ::As::IndexUint x_, const ::As::IndexUint y_) const {
				return this->getIndexZX(z_, x_) * height + y_;
			}
			// 配列の添え字を取得
			::As::IndexUint getIndexMulZXY(const ::As::IndexUint z_, const ::As::IndexUint x_, const ::As::IndexUint y_) const {
				return this->getIndexZXY(z_, x_, y_) * layer;
			}

			// 配列の添え字を取得
			::As::IndexUint getIndexZXYL(const ::As::IndexUint z_, const ::As::IndexUint x_, const ::As::IndexUint y_, const ::As::IndexUint l_) const {
				return (this->getIndexZXY(z_, x_, y_) * layer + l_);
			}
			// 配列の添え字を取得
			::As::IndexUint getIndexZXYL(const ::As::IndexUint zx_, const ::As::IndexUint y_, const ::As::IndexUint l_) const {
				return ((zx_ * height + y_) * layer + l_);
			}
			// 配列の添え字を取得
			::As::IndexUint getIndexZXYL(const ::As::IndexUint zxy_, const ::As::IndexUint l_) const {
				return (zxy_ * layer + l_);
			}
			// 配列の添え字を取得
			::As::IndexUint getIndexZXYL(const ::As::IndexUint zxyl_) const {
				return (zxyl_);
			}

			// 配列の値を取得
			const Type_& getValueMulZXYL(const ::As::IndexUint zx_, const ::As::IndexUint y_, const ::As::IndexUint l_) const {
				return *(this->matrix.get() + ((zx_ + y_) * layer + l_));
			}
			// 配列の値を取得
			const Type_& getValueMulZXYL(const ::As::IndexUint zxy_, const ::As::IndexUint l_) const {
				return *(this->matrix.get() + (zxy_ + l_));
			}

			// 配列の値を取得
			const Type_& getValueZXYL(const ::As::IndexUint z_, const ::As::IndexUint x_, const ::As::IndexUint y_, const ::As::IndexUint l_) const {
				return *(this->matrix.get() + (this->getIndexZXY(z_, x_, y_) * layer + l_));
			}
			// 配列の値を取得
			const Type_& getValueZXYL(const ::As::IndexUint zx_, const ::As::IndexUint y_, const ::As::IndexUint l_) const {
				return *(this->matrix.get() + ((zx_ * height + y_) * layer + l_));
			}
			// 配列の値を取得
			const Type_& getValueZXYL(const ::As::IndexUint zxy_, const ::As::IndexUint l_) const {
				return *(this->matrix.get() + (zxy_ * layer + l_));
			}
			// 配列の値を取得
			const Type_& getValueZXYL(const ::As::IndexUint zxyl_) const {
				return *(this->matrix.get() + zxyl_);
			}


			// 配列の値を取得
			void setValueMulZXYL(const Type_& value_, const ::As::IndexUint zx_, const ::As::IndexUint y_, const ::As::IndexUint l_) {
				this->matrix[(zx_ + y_) * layer + l_] = value_;
			}
			// 配列の値を取得
			void setValueMulZXYL(const Type_& value_, const ::As::IndexUint zxy_, const ::As::IndexUint l_) {
				this->matrix[zxy_ + l_] = value_;
			}

			// 配列の値を取得
			void setValueZXYL(const Type_& value_, const ::As::IndexUint z_, const ::As::IndexUint x_, const ::As::IndexUint y_, const ::As::IndexUint l_) {
				this->matrix[((z_ * width + x_) * height + y_) * layer + l_] = value_;
			}
			// 配列の値を取得
			void setValueZXYL(const Type_& value_, const ::As::IndexUint zx_, const ::As::IndexUint y_, const ::As::IndexUint l_) {
				this->matrix[(zx_ * height + y_) * layer + l_] = value_;
			}
			// 配列の値を取得
			void setValueZXYL(const Type_& value_, const ::As::IndexUint zxy_, const ::As::IndexUint l_) {
				this->matrix[zxy_ * layer + l_] = value_;
			}
			// 配列の値を取得
			void setValueZXYL(const Type_& value_, const ::As::IndexUint zxyl_) {
				this->matrix[zxyl_] = value_;
			}

			::As::IndexUint size() const { return this->width * this->height * this->depth * this->layer; }
			::As::IndexUint getSize() const { return this->width * this->height * this->depth * this->layer; }
			::As::IndexUint getWidth() const { return this->width; }
			::As::IndexUint getHeight() const { return this->height; }
			::As::IndexUint getDepth() const { return this->depth; }
			::As::IndexUint getLayer() const { return this->layer; }

		};

	}
}
//##########################################################################################

#endif //Included AsLib2