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

#ifndef INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_INDEX_AREA_HPP
#define INCLUDED_ASLIB2_ASLIB2C_DATA_TYPE_INDEX_AREA_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp> // int

namespace As {
	inline namespace DataType {
		
		struct IndexAreaXZ {
			::As::IndexUint start_x{};
			::As::IndexUint start_z{};
			::As::IndexUint width{};
			::As::IndexUint depth{};

			IndexAreaXZ() = default;
			IndexAreaXZ(const ::As::IndexUint start_x_, const ::As::IndexUint start_z_, const ::As::IndexUint width_, const ::As::IndexUint depth_)
				:start_x(start_x_), start_z(start_z_), width(width_), depth(depth_) {}
			IndexAreaXZ(const ::As::IndexUint start_x_, const ::As::IndexUint start_z_, const ::As::IndexUint size_)
				:start_x(start_x_), start_z(start_z_), width(size_), depth(size_) {}
		};

	}
}
//##########################################################################################

#endif //Included AsLib2