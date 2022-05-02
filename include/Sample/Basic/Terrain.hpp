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
		, ::As::UniquePtrMatrix4D<TerrainObject>& terrain_object_matrix // フィールドマップ
		, ::As::UniquePtrMatrix<TerrainInformation>& terrain_information_matrix // フィールドマップ
		, ::As::UniquePtrMatrix<DrawMapChip>& draw_map_matrix // 描画用フィールドマップ
		, TerrainPerlinNoise& terrain_noise // 地形生成
	) {
		// 右側に生成
		if (cs.camera_size.getCenterX() > float(cs.field_map_size.getCenterX() + (cs.field_map_size.getWidthHalf() * 2 / 3))) {
			cs.camera_size.moveX(-float(cs.field_map_size.getWidthHalf()));
			chunk.moveRight();
			terrain.moveLeft(terrain_object_matrix, terrain_information_matrix, terrain_information_matrix.getWidth() / 2);
			terrain.generation(terrain_object_matrix, terrain_information_matrix, terrain_noise, chunk.getX() + 1, chunk.getZ(), 
				::As::IndexAreaXZ(terrain_information_matrix.getWidth() / 2, 0, terrain_information_matrix.getWidth() / 2, terrain_information_matrix.getDepth()));
			terrain.setDrawMapFromTerrain(terrain_object_matrix, terrain_information_matrix, draw_map_matrix, 0, 0, draw_map_matrix.getWidth(), draw_map_matrix.getDepth());
			terrain.setDrawAutoTileConnection(draw_map_matrix);
			terrain.setDrawRange(draw_map_matrix);
		}
		// 左側に生成
		else if (cs.camera_size.getCenterX() < float(cs.field_map_size.getCenterX() - (cs.field_map_size.getWidthHalf() * 2 / 3))) {
			cs.camera_size.moveX(+float(cs.field_map_size.getWidthHalf()));
			chunk.moveLeft();
			terrain.moveRight(terrain_object_matrix, terrain_information_matrix, terrain_information_matrix.getWidth() / 2);
			terrain.generation(terrain_object_matrix, terrain_information_matrix, terrain_noise, chunk.getX(), chunk.getZ(), 
				::As::IndexAreaXZ(0, 0, terrain_information_matrix.getWidth() / 2, terrain_information_matrix.getDepth()));
			//terrain.moveRightDraw(draw_map_matrix, draw_map_matrix.getWidth() / 2);
			terrain.setDrawMapFromTerrain(terrain_object_matrix, terrain_information_matrix, draw_map_matrix, 0, 0, draw_map_matrix.getWidth(), draw_map_matrix.getDepth());
			terrain.setDrawAutoTileConnection(draw_map_matrix);
			terrain.setDrawRange(draw_map_matrix);
		}
		// 上側に生成
		if (cs.camera_size.getCenterY() > float(cs.field_map_size.getCenterY() + (cs.field_map_size.getHeightHalf() * 2 / 3))) {
			cs.camera_size.moveY(-float(cs.field_map_size.getHeightHalf()));
			chunk.moveUp();
			terrain.moveUp(terrain_object_matrix, terrain_information_matrix, terrain_information_matrix.getDepth() / 2);
			terrain.generation(terrain_object_matrix, terrain_information_matrix, terrain_noise, chunk.getX(), chunk.getZ() + 1, 
				::As::IndexAreaXZ(0, terrain_information_matrix.getDepth() / 2, terrain_information_matrix.getWidth(), terrain_information_matrix.getDepth() / 2));
			terrain.setDrawMapFromTerrain(terrain_object_matrix, terrain_information_matrix, draw_map_matrix, 0, 0, draw_map_matrix.getWidth(), draw_map_matrix.getDepth());
			terrain.setDrawAutoTileConnection(draw_map_matrix);
			terrain.setDrawRange(draw_map_matrix);
		}
		// 下側に生成
		else if (cs.camera_size.getCenterY() < float(cs.field_map_size.getCenterY() - (cs.field_map_size.getHeightHalf() * 2 / 3))) {
			cs.camera_size.moveY(+float(cs.field_map_size.getHeightHalf()));
			chunk.moveDown();
			terrain.moveDown(terrain_object_matrix, terrain_information_matrix, terrain_information_matrix.getDepth() / 2);
			terrain.generation(terrain_object_matrix, terrain_information_matrix, terrain_noise, chunk.getX(), chunk.getZ(), 
				::As::IndexAreaXZ(0, 0, terrain_information_matrix.getWidth(), terrain_information_matrix.getDepth() / 2));
			terrain.setDrawMapFromTerrain(terrain_object_matrix, terrain_information_matrix, draw_map_matrix, 0, 0, draw_map_matrix.getWidth(), draw_map_matrix.getDepth());
			terrain.setDrawAutoTileConnection(draw_map_matrix);
			terrain.setDrawRange(draw_map_matrix);
		}
	}

}

#endif //Included Sample