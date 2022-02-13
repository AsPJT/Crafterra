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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_CRAFTERRA_PRIMITIVE_DATA_TYPE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_DATA_TYPE_CRAFTERRA_PRIMITIVE_DATA_TYPE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>

//##########################################################################################
// BIOME_T
#ifndef CRAFTERRA_BIOME_T
#define CRAFTERRA_BIOME_T ::As::Uint8
#endif // CRAFTERRA_BIOME_T

// TERRAIN_OBJECT_T
#ifndef CRAFTERRA_TERRAIN_OBJECT_T
#define CRAFTERRA_TERRAIN_OBJECT_T ::As::Uint8
#endif // CRAFTERRA_TERRAIN_OBJECT_T

// ELEVATION_T
#ifndef CRAFTERRA_ELEVATION_T
#define CRAFTERRA_ELEVATION_T ::As::Uint8
#endif // CRAFTERRA_ELEVATION_T

// ACTOR_DIRECTION_T
#ifndef CRAFTERRA_ACTOR_DIRECTION_T
#define CRAFTERRA_ACTOR_DIRECTION_T ::As::Uint8
#endif // CRAFTERRA_ACTOR_DIRECTION_T

// ACTOR_MODE_T
#ifndef CRAFTERRA_ACTOR_MODE_T
#define CRAFTERRA_ACTOR_MODE_T ::As::Uint8
#endif // CRAFTERRA_ACTOR_MODE_T

// TERRAIN_TILE_CONNECTION_CLIFF_T
#ifndef TERRAIN_TILE_CONNECTION_CLIFF_T
#define TERRAIN_TILE_CONNECTION_CLIFF_T ::As::Uint8
#endif // TERRAIN_TILE_CONNECTION_CLIFF_T

// TERRAIN_TILE_CONNECTION_WODITOR_AUTO_TILE_T
#ifndef TERRAIN_TILE_CONNECTION_WODITOR_AUTO_TILE_T
#define TERRAIN_TILE_CONNECTION_WODITOR_AUTO_TILE_T ::As::Uint8
#endif // TERRAIN_TILE_CONNECTION_WODITOR_AUTO_TILE_T
//##########################################################################################
// using 型定義
namespace Crafterra {
	inline namespace DataType {
		using BiomeType = CRAFTERRA_BIOME_T;
		using TerrainObjectType = CRAFTERRA_TERRAIN_OBJECT_T;
		// 標高値
		using ElevationUint = CRAFTERRA_ELEVATION_T;
		using ActorDirectionUint = CRAFTERRA_ACTOR_DIRECTION_T;
		using ActorModeUint = CRAFTERRA_ACTOR_MODE_T;
		using TerrainTileConnectionCliffUint = TERRAIN_TILE_CONNECTION_CLIFF_T;
		using TerrainTileConnectionWoditorAutoTileUint = TERRAIN_TILE_CONNECTION_WODITOR_AUTO_TILE_T;
	}
}
//##########################################################################################

#endif //Included Crafterra Library