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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ITEM_INVENTORY_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ITEM_INVENTORY_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <Crafterra/Enum/TerrainObject.hpp> // 地形オブジェクト

namespace Crafterra {

	using ItemCountUint = ::As::Uint8;

	// 道具 ( 道具は地形オブジェクトと同一の物として管理される )
	struct Item {
		TerrainObject terrain_obj = TerrainObject::empty;
		ItemCountUint count = 0;
	};

	// 持ち物
	class Inventory {
	private:
		

	public:


	};

}

#endif //Included Crafterra Library