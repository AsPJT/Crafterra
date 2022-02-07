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
#include <AsLib2/DataType/IndexArea.hpp>

namespace Crafterra {

	// 地形チャンク
	class TerrainChunk {
	private:
		::As::Uint32 chunk_min_x;
		::As::Uint32 chunk_min_z;
		::As::Uint32 chunk_max_x;
		::As::Uint32 chunk_max_z;
		::As::Uint32 init_chunk_x;
		::As::Uint32 init_chunk_z;

		::As::Uint32 chunk_x;
		::As::Uint32 chunk_z;

	public:
		// コンストラクタ
		TerrainChunk(const ::As::IndexAreaXZ& area_)
			:chunk_min_x(area_.start_x), chunk_min_z(area_.start_z), chunk_max_x(area_.start_x + area_.width), chunk_max_z(area_.start_z + area_.depth),
			init_chunk_x(area_.start_x + area_.width / 2), init_chunk_z(area_.start_z + area_.depth / 2),
			chunk_x(init_chunk_x), chunk_z(init_chunk_z) {}

		::As::Uint32 getX() const { return this->chunk_x; }
		::As::Uint32 getZ() const { return this->chunk_z; }
		void setX(const ::As::Uint32 chunk_x_) { this->chunk_x = chunk_x_; }
		void setZ(const ::As::Uint32 chunk_z_) { this->chunk_z = chunk_z_; }

		void moveLeft() {
			if (this->chunk_x <= this->chunk_min_x) this->chunk_x = this->chunk_max_x - 1;
			else --this->chunk_x;
		}
		void moveRight() {
			if (this->chunk_x >= this->chunk_max_x - 1) this->chunk_x = this->chunk_min_x;
			else ++this->chunk_x;
		}
		void moveUp() {
			if (this->chunk_z >= this->chunk_max_z - 1) this->chunk_z = this->chunk_min_z;
			else ++this->chunk_z;
		}
		void moveDown() {
			if (this->chunk_z <= this->chunk_min_z) this->chunk_z = this->chunk_max_z - 1;
			else --this->chunk_z;
		}
	};

}

#endif //Included Crafterra Library