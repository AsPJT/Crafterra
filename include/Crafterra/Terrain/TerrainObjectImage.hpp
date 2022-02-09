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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_TERRAIN_OBJECT_IMAGE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_TERRAIN_OBJECT_IMAGE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>

#include <Crafterra/Enum/TerrainObject.hpp>

#include <AsLib2/ThirdParty/Framework/MapChipImage.hpp>

#include <AsLib2/Basic/Rect.hpp>

namespace Crafterra {

	// 地形オブジェクトの画像を管理
	class TerrainObjectImage {
	public:
		::std::unique_ptr<::As::Image[]> terrain_image{};
	public:

		TerrainObjectImage(::As::MapChipImage& tile) 
			: terrain_image(new(::std::nothrow) ::As::Image[::As::IndexUint(TerrainObject::size)])
		{

			for (::As::IndexUint i = 0; i < ::As::IndexUint(TerrainObject::size); ++i) {

				switch (TerrainObject(i)) {
				case TerrainObject::cliff:
					// 今のところ実装無し
				break;
				case TerrainObject::cliff_top:
					// 今のところ実装無し
				break;
				case TerrainObject::sea:
				case TerrainObject::water_ground_2:
					// 今のところ実装無し
				break;
				case TerrainObject::normal_ground:
					terrain_image[i] = (tile.getMapChip("Base", 0));
					break;
				case TerrainObject::grass_1:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 0));
					break;
				case TerrainObject::grass_2:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 1));
					break;
				case TerrainObject::grass_3:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 2));
					break;
				case TerrainObject::grass_4:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 3));
					break;
				case TerrainObject::flower_1:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 4));
					break;
				case TerrainObject::flower_2:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 5));
					break;
				case TerrainObject::flower_3:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 6));
					break;
				case TerrainObject::flower_4:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 6 + 7));
					break;
				case TerrainObject::house_wall_1_up:
					//(tile.getMapChip("Base", 8 * 46 + 7));
					terrain_image[i] = (tile.getMapChip("Base", 8 * 115 + 3));
					break;
				case TerrainObject::house_wall_1_down:
					//(tile.getMapChip("Base", 8 * 47 + 7));
					terrain_image[i] = (tile.getMapChip("Base", 8 * 116 + 3));
					break;
				case TerrainObject::yellow_green_broadleaf_tree_up:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 9 + 0));
					break;
				case TerrainObject::yellow_green_broadleaf_tree_down:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 10 + 0));
					break;
				case TerrainObject::green_broadleaf_tree_up:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 9 + 1));
					break;
				case TerrainObject::green_broadleaf_tree_down:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 10 + 1));
					break;
				case TerrainObject::yellow_broadleaf_tree_up:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 9 + 2));
					break;
				case TerrainObject::yellow_broadleaf_tree_down:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 10 + 2));
					break;
				case TerrainObject::red_broadleaf_tree_up:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 9 + 3));
					break;
				case TerrainObject::red_broadleaf_tree_down:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 10 + 3));
					break;
				case TerrainObject::deciduous_tree_up:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 9 + 4));
					break;
				case TerrainObject::deciduous_tree_down:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 10 + 4));
					break;
				case TerrainObject::yellow_green_coniferous_tree_up:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 9 + 5));
					break;
				case TerrainObject::yellow_green_coniferous_tree_down:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 10 + 5));
					break;
				case TerrainObject::green_coniferous_tree_up:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 9 + 6));
					break;
				case TerrainObject::green_coniferous_tree_down:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 10 + 6));
					break;
				case TerrainObject::cultivated_land:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 21 + 3));
					break;
				case TerrainObject::planted_carrot:
					terrain_image[i] = (tile.getMapChip("Base", 8 * 19 + 6));
					break;
				}
			}
		}

	};

}

#endif //Included Crafterra Library