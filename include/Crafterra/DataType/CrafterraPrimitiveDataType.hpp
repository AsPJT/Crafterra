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

#include <Crafterra/DataType/PrimitiveDataType.hpp>

//##########################################################################################
// BIOME_T
#ifndef CRAFTERRA_BIOME_T
#define CRAFTERRA_BIOME_T ::Crafterra::DataType::Uint16
#endif // CRAFTERRA_BIOME_T

// BLOCK_T
#ifndef CRAFTERRA_BLOCK_T
#define CRAFTERRA_BLOCK_T ::Crafterra::DataType::Uint16
#endif // CRAFTERRA_BLOCK_T

// ELEVATION_T
#ifndef CRAFTERRA_ELEVATION_T
#define CRAFTERRA_ELEVATION_T ::Crafterra::DataType::Uint16
#endif // CRAFTERRA_ELEVATION_T

// ACTOR_DIRECTION_T
#ifndef CRAFTERRA_ACTOR_DIRECTION_T
#define CRAFTERRA_ACTOR_DIRECTION_T ::Crafterra::DataType::Uint8
#endif // CRAFTERRA_ACTOR_DIRECTION_T

// OPERATION_ACTOR_STATE_IN_FIELD_MAP_T
#ifndef CRAFTERRA_OPERATION_ACTOR_STATE_IN_FIELD_MAP_T
#define CRAFTERRA_OPERATION_ACTOR_STATE_IN_FIELD_MAP_T ::Crafterra::DataType::Uint8
#endif // CRAFTERRA_OPERATION_ACTOR_STATE_IN_FIELD_MAP_T

// MAP_CHIP_TYPE_HOMOGENEOUS_CONNECTION_T
#ifndef MAP_CHIP_TYPE_HOMOGENEOUS_CONNECTION_T
#define MAP_CHIP_TYPE_HOMOGENEOUS_CONNECTION_T ::Crafterra::DataType::Uint8
#endif // MAP_CHIP_TYPE_HOMOGENEOUS_CONNECTION_T

// AUTO_TILE_TYPE_HOMOGENEOUS_CONNECTION_T
#ifndef AUTO_TILE_TYPE_HOMOGENEOUS_CONNECTION_T
#define AUTO_TILE_TYPE_HOMOGENEOUS_CONNECTION_T ::Crafterra::DataType::Uint8
#endif // AUTO_TILE_TYPE_HOMOGENEOUS_CONNECTION_T
//##########################################################################################
// using 型定義
namespace Crafterra {
	inline namespace DataType {
		using BiomeType = CRAFTERRA_BIOME_T;
		using BlockType = CRAFTERRA_BLOCK_T;
		// 標高値
		using ElevationUint = CRAFTERRA_ELEVATION_T;
		using ActorDirectionUint = CRAFTERRA_ACTOR_DIRECTION_T;
		using OperationActorStateInFieldMapUint = CRAFTERRA_OPERATION_ACTOR_STATE_IN_FIELD_MAP_T;
		using MapChipTypeHomogeneousConnectionUint = MAP_CHIP_TYPE_HOMOGENEOUS_CONNECTION_T;
		using AutoTileTypeHomogeneousConnectionUint = AUTO_TILE_TYPE_HOMOGENEOUS_CONNECTION_T;
	}
}
//##########################################################################################

#endif //Included Crafterra Library