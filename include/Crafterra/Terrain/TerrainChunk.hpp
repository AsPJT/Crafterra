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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_CHUNK_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_CHUNK_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>

namespace Crafterra {

	class TerrainChunk {
	private:
		::As::Uint32 chunk_min_x;
		::As::Uint32 chunk_min_y;
		::As::Uint32 chunk_max_x;
		::As::Uint32 chunk_max_y;
		::As::Uint32 init_chunk_x;
		::As::Uint32 init_chunk_y;

		::As::Uint32 chunk_x;
		::As::Uint32 chunk_y;

	public:
		// コンストラクタ
		TerrainChunk(const ::As::Uint32 chunk_min_x_, const ::As::Uint32 chunk_min_y_, const ::As::Uint32 chunk_max_x_, const ::As::Uint32 chunk_max_y_)
			:chunk_min_x(chunk_min_x_), chunk_min_y(chunk_min_y_), chunk_max_x(chunk_max_x_), chunk_max_y(chunk_max_y_),
			init_chunk_x((chunk_max_x_ - chunk_min_x_) / 2), init_chunk_y((chunk_max_y_ - chunk_min_y_) / 2),
			chunk_x(init_chunk_x), chunk_y(init_chunk_y) {}

		::As::Uint32 getX() const { return this->chunk_x; }
		::As::Uint32 getY() const { return this->chunk_y; }
		void setX(const ::As::Uint32 chunk_x_) { this->chunk_x = chunk_x_; }
		void setY(const ::As::Uint32 chunk_y_) { this->chunk_y = chunk_y_; }

		void moveLeft() {
			if (chunk_x <= chunk_min_x) chunk_x = chunk_max_x - 1;
			else --chunk_x;
		}
		void moveRight() {
			if (chunk_x >= chunk_max_x - 1) chunk_x = chunk_min_x;
			else ++chunk_x;
		}
		void moveUp() {
			if (chunk_y >= chunk_max_y - 1) chunk_y = chunk_min_y;
			else ++chunk_y;
		}
		void moveDown() {
			if (chunk_y <= chunk_min_y) chunk_y = chunk_max_y - 1;
			else --chunk_y;
		}
	};

}

#endif //Included Crafterra Library