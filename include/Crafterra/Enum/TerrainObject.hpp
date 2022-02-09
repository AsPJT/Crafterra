﻿/*##########################################################################################

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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_TERRAIN_OBJECT_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_ENUM_TERRAIN_OBJECT_HPP

#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

namespace Crafterra {

	// 未完成
	enum class TerrainObject : TerrainObjectType {
		empty				// 無し
		, cliff				// 崖
		, cliff_top			// 崖上
		, sea				// 海
		, flower_1			// 花
		, flower_2			// 花
		, flower_3			// 花
		, flower_4			// 花
		, grass_1			// 草
		, grass_2			// 草
		, grass_3			// 草
		, grass_4			// 草
		, water_ground_2	// 水
		, running_water	// 流水
		, waterfall			// 滝
		, normal_ground	// 地面 ( 後に削除される予定 , 地面タイルの描画を呼ぶために使用中 )
		, house_wall_1_up						// 家の壁
		, house_wall_1_down					// 家の壁
		, yellow_green_broadleaf_tree_up		// 黄緑色の広葉樹 上
		, yellow_green_broadleaf_tree_down	// 黄緑色の広葉樹 下
		, green_broadleaf_tree_up				// 緑色の広葉樹 上
		, green_broadleaf_tree_down			// 緑色の広葉樹 下
		, yellow_broadleaf_tree_up			// 黄色の広葉樹 上
		, yellow_broadleaf_tree_down			// 黄色の広葉樹 下
		, red_broadleaf_tree_up				// 赤色の広葉樹 上
		, red_broadleaf_tree_down			// 赤色の広葉樹 下
		, deciduous_tree_up					// 落葉樹 上
		, deciduous_tree_down					// 落葉樹 下
		, yellow_green_coniferous_tree_up	// 黄緑色の針葉樹 上
		, yellow_green_coniferous_tree_down	// 黄緑色の針葉樹 下
		, green_coniferous_tree_up			// 緑色の針葉樹 上
		, green_coniferous_tree_down			// 緑色の針葉樹 下
		, b					// 家の壁
		, cultivated_land	// 畑
		, planted_carrot	// ニンジン
		, size				// ブロックの数
	};

}

#endif //Included Crafterra Library