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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MAPCHIP_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_MAPCHIP_HPP

#include <Crafterra/DataType/PrimitiveDataType.hpp>
#include <AsLib2/ThirdParty/Framework/DataType.hpp>

#include <Crafterra/Map/HomogeneousConnection.hpp> // AutoTileIndex

namespace AsLib2 {

	class MapChipImage {
	private:

#ifdef SIV3D_INCLUDED
		::s3d::Texture texture_basemap{};
		::s3d::Texture texture_cliff_top{};
		::s3d::Texture texture_sea{};
		::s3d::Texture texture_desert{};
#endif

#ifdef SIV3D_INCLUDED
		TextureRegion base_map[8 * 249]{};
#else
		int base_map[8 * 249]{};
#endif
#ifdef SIV3D_INCLUDED
		TextureRegion cliff_top[4 * 10]{};
#else
		int cliff_top[4 * 10]{};
#endif
#ifdef SIV3D_INCLUDED
		TextureRegion sea[16 * 10]{};
#else
		int sea[16 * 10]{};
#endif
#ifdef SIV3D_INCLUDED
		TextureRegion desert[4 * 10]{};
#else
		int desert[4 * 10]{};
#endif
		
		::Crafterra::DataType::Uint8 sea_alpha[16 * 10] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
			,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};
		::Crafterra::DataType::Uint8 desert_alpha[4 * 10] = {
			0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,0,0,0,0
			,1,1,1,1
			,1,1,1,1
		};

		::Crafterra::DataType::Uint8 cliff_top_alpha[4 * 10] = {
			0,1,1,0
			,1,0,0,0
			,1,1,0,0
			,1,1,0,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,0
			,1,1,1,1
			,0,0,0,0
		};

	public:

		MapChipImage() {
#if defined(__DXLIB)
			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/Map/Base(pipo).png", 8 * 249,
				8, 249,
				32, 32, base_map);

			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png", 4 * 10,
				4, 10,
				32, 32, cliff_top);

			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/AutoTile/Water1(pipoya).png", 16 * 10,
				16, 10,
				16, 16, sea);
			::DxLib::LoadDivGraph("./../../../resource/Picture/Chip/AutoTile/[A]Dirt3_pipo.png", 4 * 10,
				4, 10,
				16, 16, desert);
#elif defined(SIV3D_INCLUDED)
			texture_basemap = ::s3d::Texture(U"./../../../../resource/Picture/Chip/Map/Base(pipo).png");
			for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 249; ++y)
				for (::Crafterra::DataType::IndexUint x = 0; x < 8; ++x, ++count) {
					base_map[count] = texture_basemap(double(32 * x), double(32 * y), double(32), double(32));
				}
			texture_cliff_top = ::s3d::Texture(U"./../../../../resource/Picture/Chip/AutoTile/Cliff(pipoya).png");
			for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 10; ++y)
				for (::Crafterra::DataType::IndexUint x = 0; x < 4; ++x, ++count) {
					cliff_top[count] = texture_cliff_top(double(32 * x), double(32 * y), double(32), double(32));
				}
			texture_sea = ::s3d::Texture(U"./../../../../resource/Picture/Chip/AutoTile/Water1(pipoya).png");
			for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 10; ++y)
				for (::Crafterra::DataType::IndexUint x = 0; x < 16; ++x, ++count) {
					sea[count] = texture_sea(double(16 * x), double(16 * y), double(16), double(16));
				}
			texture_desert = ::s3d::Texture(U"./../../../../resource/Picture/Chip/AutoTile/[A]Dirt3_pipo.png");
			for (::Crafterra::DataType::IndexUint y = 0, count = 0; y < 10; ++y)
				for (::Crafterra::DataType::IndexUint x = 0; x < 4; ++x, ++count) {
					desert[count] = texture_desert(double(16 * x), double(16 * y), double(16), double(16));
				}
#endif // __DXLIB
		}

		~MapChipImage() {

		}
#ifdef SIV3D_INCLUDED
		TextureRegion
#else
		DxGraphInt
#endif
			getMapChip(const ::Crafterra::DataType::IndexUint index_) const { return this->base_map[index_]; }
#ifdef SIV3D_INCLUDED
		TextureRegion
#else
		DxGraphInt
#endif
			getSea(const ::Crafterra::DataType::IndexUint index_) const { return this->sea[index_]; }
#ifdef SIV3D_INCLUDED
		TextureRegion
#else
		DxGraphInt
#endif
			getDesert(const ::Crafterra::DataType::IndexUint index_) const { return this->desert[index_]; }
		::Crafterra::DataType::Uint8 getSeaAlpha(const ::Crafterra::DataType::IndexUint index_) const { return this->sea_alpha[index_]; }
		bool getIsSeaAlpha(const ::Crafterra::DataType::IndexUint index_) const { return (this->sea_alpha[index_] == 0); }
		bool getIsAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_, const ::Crafterra::DataType::Uint8* const alpha_array_) const {
			return ((alpha_array_[auto_tile_index_.auto_tile_upper_left] == 0) ||
				(alpha_array_[auto_tile_index_.auto_tile_upper_right] == 0) ||
				(alpha_array_[auto_tile_index_.auto_tile_lower_left] == 0) ||
				(alpha_array_[auto_tile_index_.auto_tile_lower_right] == 0));
		}
		bool getIsSeaAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_) const {
			return getIsAlpha(auto_tile_index_, this->sea_alpha);
		}
		bool getIsDesertAlpha(const ::Crafterra::AutoTileIndex& auto_tile_index_) const {
			return getIsAlpha(auto_tile_index_, this->desert_alpha);
		}
#ifdef SIV3D_INCLUDED
		TextureRegion
#else
		DxGraphInt
#endif
			getMapChipCliffTop(const ::Crafterra::DataType::IndexUint index_) const { return this->cliff_top[index_]; }
		::Crafterra::DataType::Uint8 getMapChipCliffTopAlpha(const ::Crafterra::DataType::IndexUint index_) const { return this->cliff_top_alpha[index_]; }

	};
}

#endif //Included Crafterra Library