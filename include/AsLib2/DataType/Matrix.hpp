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
			::As::IndexUint width;
			::As::IndexUint height;
		public:
			UniquePtrMatrix(const ::As::IndexUint num_x_, const ::As::IndexUint num_y_) :
				matrix(new(::std::nothrow) Type_[num_x_ * num_y_]), width(num_x_), height(num_y_) {}

			// 配列を取得
			Type_* const operator[](const ::As::IndexUint y_) const {
				return this->matrix.get() + y_ * this->width;
			}

			::As::IndexUint size() const { return this->width * this->height; }
			::As::IndexUint getSize() const { return this->width * this->height; }
			::As::IndexUint getWidth() const { return this->width; }
			::As::IndexUint getHeight() const { return this->height; }

		};

	}
}
//##########################################################################################

#endif //Included AsLib2