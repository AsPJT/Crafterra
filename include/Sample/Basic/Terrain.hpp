/*##########################################################################################

	Crafterra Sample Source Code 🌏

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

#ifndef INCLUDED_SAMPLE_SAMPLE_BASIC_TERRAIN_HPP
#define INCLUDED_SAMPLE_SAMPLE_BASIC_TERRAIN_HPP

// Crafterra 
#include <Crafterra/Crafterra.hpp>

// 各描画ライブラリをまとめたもの
#include <AsLib2/ThirdParty/Framework/Framework.hpp>

namespace Crafterra {

	// 無限生成処理
	void updateTerrain(
		CoordinateSystem& cs // 座標系管理クラス
		, TerrainChunk& chunk // 地形チャンク管理
		, const Terrain& terrain // 地形整理クラス
		, ::As::Matrix<MapChip, init_field_map_width, init_field_map_height>& field_map_matrix // フィールドマップ
		, ::As::Matrix<DrawMapChip, init_field_map_width, init_field_map_height>& draw_map_matrix // 描画用フィールドマップ
		, TerrainNoise& terrain_noise // 地形生成
	) {
		// 右側に生成
		if (cs.camera_size.getCenterX() > float(cs.field_map_size.getCenterX() + (cs.field_map_size.getWidthHalf() * 2 / 3))) {
			cs.camera_size.moveX(-float(cs.field_map_size.getWidthHalf()));
			chunk.moveRight();
			terrain.moveLeft(field_map_matrix, init_field_map_width / 2);
			terrain.generation(field_map_matrix, terrain_noise, chunk.getX() + 1, chunk.getY(), init_field_map_width / 2, 0, init_field_map_width, init_field_map_height);
			terrain.setTerrain(field_map_matrix, draw_map_matrix);
		}
		// 左側に生成
		else if (cs.camera_size.getCenterX() < float(cs.field_map_size.getCenterX() - (cs.field_map_size.getWidthHalf() * 2 / 3))) {
			cs.camera_size.moveX(+float(cs.field_map_size.getWidthHalf()));
			chunk.moveLeft();
			terrain.moveRight(field_map_matrix, init_field_map_width / 2);
			terrain.generation(field_map_matrix, terrain_noise, chunk.getX(), chunk.getY(), 0, 0, init_field_map_width / 2, init_field_map_height);
			terrain.setTerrain(field_map_matrix, draw_map_matrix);
		}
		// 上側に生成
		if (cs.camera_size.getCenterY() > float(cs.field_map_size.getCenterY() + (cs.field_map_size.getHeightHalf() * 2 / 3))) {
			cs.camera_size.moveY(-float(cs.field_map_size.getHeightHalf()));
			chunk.moveUp();
			terrain.moveUp(field_map_matrix, init_field_map_height / 2);
			terrain.generation(field_map_matrix, terrain_noise, chunk.getX(), chunk.getY() + 1, 0, init_field_map_height / 2, init_field_map_width, init_field_map_height);
			terrain.setTerrain(field_map_matrix, draw_map_matrix);
		}
		// 下側に生成
		else if (cs.camera_size.getCenterY() < float(cs.field_map_size.getCenterY() - (cs.field_map_size.getHeightHalf() * 2 / 3))) {
			cs.camera_size.moveY(+float(cs.field_map_size.getHeightHalf()));
			chunk.moveDown();
			terrain.moveDown(field_map_matrix, init_field_map_height / 2);
			terrain.generation(field_map_matrix, terrain_noise, chunk.getX(), chunk.getY(), 0, 0, init_field_map_width, init_field_map_height / 2);
			terrain.setTerrain(field_map_matrix, draw_map_matrix);
		}
	}

}

#endif //Included Sample