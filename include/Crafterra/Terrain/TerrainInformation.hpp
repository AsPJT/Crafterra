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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_TERRAIN_INFOMATION_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_TERRAIN_INFOMATION_HPP

#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>
#include <Crafterra/Enum/CrafterraEnum.hpp>
#include <Crafterra/Enum/TerrainBiome.hpp>

namespace Crafterra {

	// 地形情報
	class TerrainInformation {
	private:
		using FlowerFloat = double;

		TerrainBiome biome{ TerrainBiome::empty }; // バイオーム
		ElevationUint block_elevation{}; // ブロックの高さに合わせた標高値

		ElevationUint elevation{}; // 元の標高値
		ElevationUint temperature{}; // 気温
		ElevationUint amount_of_rainfall{}; // 降水量
		FlowerFloat flower{}; // 花
		ElevationUint lake{}; // 花

	public:

		TerrainBiome getBiome() const { return this->biome; }
		void setBiome(const TerrainBiome& biome_) { this->biome = biome_; }
		ElevationUint getElevation() const { return this->elevation; }
		void setElevation(const ElevationUint& elevation_) { this->elevation = elevation_; }
		FlowerFloat getFlower() const { return this->flower; }
		void setFlower(const FlowerFloat& flower_) { this->flower = flower_; }
		ElevationUint getLake() const { return this->lake; }
		void setLake(const ElevationUint& lake_) { this->lake = lake_; }
		ElevationUint getTemperature() const { return this->temperature; }
		void setTemperature(const ElevationUint& temperature_) { this->temperature = temperature_; }
		ElevationUint getAmountOfRainfall() const { return this->amount_of_rainfall; }
		void setAmountOfRainfall(const ElevationUint& amount_of_rainfall_) { this->amount_of_rainfall = amount_of_rainfall_; }
		ElevationUint getBlockElevation() const { return this->block_elevation; }
		void setBlockElevation(const ElevationUint& elevation_) { this->block_elevation = elevation_; }

	};

}

#endif //Included Crafterra Library