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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_TILE_CONNECTION_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_TILE_CONNECTION_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>
#include <AsLib2/DataType/ArrayDataType.hpp>
#include <AsLib2/DataType/StringDataType.hpp>

#include <Crafterra/Enum/CrafterraEnum.hpp>

namespace Crafterra {

	// 同じ性質のブロックとの接続タイプ ( 崖 )
	TerrainTileConnectionCliff getHomogeneousConnectionCliff(
		const bool left_
		, const bool right_
		, const bool down_
	) {
		if (down_) {
			if (left_) {
				if (right_) return TerrainTileConnectionCliff::left_right_down_cliff;
				else        return TerrainTileConnectionCliff::left_down_cliff;
			}
			else {
				if (right_) return TerrainTileConnectionCliff::right_down_cliff;
				else        return TerrainTileConnectionCliff::down_cliff;
			}
		}
		else {
			if (left_) {
				if (right_) return TerrainTileConnectionCliff::left_right_up_cliff;
				else        return TerrainTileConnectionCliff::left_up_cliff;
			}
			else {
				if (right_) return TerrainTileConnectionCliff::right_up_cliff;
				else        return TerrainTileConnectionCliff::up_cliff;
			}
		}
	}

	::As::Uint32 getAutoTileIndex(const TerrainTileConnectionWoditorAutoTile ahc_, const ::As::Uint32 animation_number_, const ::As::Uint32 animation_max_number_) {
		const ::As::Uint32 an2 = animation_number_ * 2; // アニメーション数の 2 倍
		const ::As::Uint32 amn2 = animation_max_number_ * 2; // 最大アニメーション数の 2 倍
		const ::As::Uint32 ahc = ::As::Uint32(ahc_);
		const ::As::Uint32 ahcp2 = ::As::Uint32(ahc_) / 2;
		const ::As::Uint32 right = ((ahc % 2 == 0) ? 0 : 1);
		return amn2 * ahcp2 + an2 + right;
	}

	// 今後、別の hpp を作成して管理
	struct AutoTileIndex {
		::As::Uint32 auto_tile_upper_left{};
		::As::Uint32 auto_tile_upper_right{};
		::As::Uint32 auto_tile_lower_left{};
		::As::Uint32 auto_tile_lower_right{};

		AutoTileIndex(const AutoTile& auto_tile_, const ::As::Uint32 animation_number_, const ::As::Uint32 animation_max_number_) :
			auto_tile_upper_left(getAutoTileIndex(auto_tile_.auto_tile_upper_left, animation_number_, animation_max_number_))
			, auto_tile_upper_right(getAutoTileIndex(auto_tile_.auto_tile_upper_right, animation_number_, animation_max_number_))
			, auto_tile_lower_left(getAutoTileIndex(auto_tile_.auto_tile_lower_left, animation_number_, animation_max_number_))
			, auto_tile_lower_right(getAutoTileIndex(auto_tile_.auto_tile_lower_right, animation_number_, animation_max_number_))
		{}
	};

	// 同じ性質のブロックとの接続タイプ ( 通常 )
	AutoTile getHomogeneousConnectionAutoTile(
		const bool up_
		, const bool left_
		, const bool right_
		, const bool down_
		, const bool upper_left_
		, const bool upper_right_
		, const bool lower_left_
		, const bool lower_right_
	) {
		AutoTile at{};
		// 左上
		if (up_) {
			if (left_) {
				if (upper_left_) at.auto_tile_upper_left = TerrainTileConnectionWoditorAutoTile::all_upper_left;
				else              at.auto_tile_upper_left = TerrainTileConnectionWoditorAutoTile::cross_upper_left;
			}
			else                  at.auto_tile_upper_left = TerrainTileConnectionWoditorAutoTile::up_and_down_upper_left;
		}
		else {
			if (left_)             at.auto_tile_upper_left = TerrainTileConnectionWoditorAutoTile::left_and_right_upper_left;
			else                  at.auto_tile_upper_left = TerrainTileConnectionWoditorAutoTile::nothing_upper_left;
		}
		// 右上
		if (up_) {
			if (right_) {
				if (upper_right_) at.auto_tile_upper_right = TerrainTileConnectionWoditorAutoTile::all_upper_right;
				else              at.auto_tile_upper_right = TerrainTileConnectionWoditorAutoTile::cross_upper_right;
			}
			else                  at.auto_tile_upper_right = TerrainTileConnectionWoditorAutoTile::up_and_down_upper_right;
		}
		else {
			if (right_)             at.auto_tile_upper_right = TerrainTileConnectionWoditorAutoTile::left_and_right_upper_right;
			else                  at.auto_tile_upper_right = TerrainTileConnectionWoditorAutoTile::nothing_upper_right;
		}
		// 左下
		if (down_) {
			if (left_) {
				if (lower_left_) at.auto_tile_lower_left = TerrainTileConnectionWoditorAutoTile::all_lower_left;
				else              at.auto_tile_lower_left = TerrainTileConnectionWoditorAutoTile::cross_lower_left;
			}
			else                  at.auto_tile_lower_left = TerrainTileConnectionWoditorAutoTile::up_and_down_lower_left;
		}
		else {
			if (left_)             at.auto_tile_lower_left = TerrainTileConnectionWoditorAutoTile::left_and_right_lower_left;
			else                  at.auto_tile_lower_left = TerrainTileConnectionWoditorAutoTile::nothing_lower_left;
		}
		// 右上
		if (down_) {
			if (right_) {
				if (lower_right_) at.auto_tile_lower_right = TerrainTileConnectionWoditorAutoTile::all_lower_right;
				else              at.auto_tile_lower_right = TerrainTileConnectionWoditorAutoTile::cross_lower_right;
			}
			else                  at.auto_tile_lower_right = TerrainTileConnectionWoditorAutoTile::up_and_down_lower_right;
		}
		else {
			if (right_)             at.auto_tile_lower_right = TerrainTileConnectionWoditorAutoTile::left_and_right_lower_right;
			else                  at.auto_tile_lower_right = TerrainTileConnectionWoditorAutoTile::nothing_lower_right;
		}

		return at;
	}

	// 同じ性質のブロックとの接続タイプ ( 通常 )
	TerrainTileConnectionCliff getHomogeneousConnection(
		const bool up_
		, const bool left_
		, const bool right_
		, const bool down_
		, const bool upper_left_
		, const bool upper_right_
		, const bool lower_left_
		, const bool lower_right_
	) {
		TerrainTileConnectionCliff mcthc = TerrainTileConnectionCliff::all;

		if (up_) {
			if (left_) {
				if (right_) {
					if (down_) return   TerrainTileConnectionCliff::all;
					else        mcthc = TerrainTileConnectionCliff::up_left_right_0;
				}
				else {
					if (down_) mcthc = TerrainTileConnectionCliff::up_left_down_0;
					else        mcthc = TerrainTileConnectionCliff::up_left_0;
				}
			}
			else {
				if (right_) {
					if (down_) mcthc = TerrainTileConnectionCliff::up_right_down_0;
					else        mcthc = TerrainTileConnectionCliff::up_right_0;
				}
				else {
					if (down_) return   TerrainTileConnectionCliff::up_down;
					else        return   TerrainTileConnectionCliff::up;
				}
			}
		}
		else {
			if (left_) {
				if (right_) {
					if (down_) mcthc = TerrainTileConnectionCliff::left_right_down_0;
					else        return   TerrainTileConnectionCliff::left_right;
				}
				else {
					if (down_) mcthc = TerrainTileConnectionCliff::left_down_0;
					else        return   TerrainTileConnectionCliff::left;
				}
			}
			else {
				if (right_) {
					if (down_) mcthc = TerrainTileConnectionCliff::right_down_0;
					else        return   TerrainTileConnectionCliff::right;
				}
				else {
					if (down_) return   TerrainTileConnectionCliff::down;
					else        return   TerrainTileConnectionCliff::nothing;
				}
			}
		}
		return mcthc;
	}


	template<typename Type_>
	TerrainTileConnectionCliff getHomogeneousConnectionValueElevation3(
		const Type_ center_
		, const Type_ up_
		, const Type_ left_
		, const Type_ right_
		, const Type_ down_
		, const Type_ upper_left_
		, const Type_ upper_right_
		, const Type_ lower_left_
		, const Type_ lower_right_
	) {
		return getHomogeneousConnection(
			center_ == up_
			, center_ <= left_
			, center_ <= right_
			, center_ <= down_
			, center_ == upper_left_
			, center_ == upper_right_
			, center_ == lower_left_
			, center_ == lower_right_
		);
	}

	template<typename Type_>
	TerrainTileConnectionCliff getHomogeneousConnectionCliffValueElevation3(
		const Type_ center_
		, const Type_ left_
		, const Type_ right_
		, const Type_ down_
	) {
		return getHomogeneousConnectionCliff(
			center_ == left_
			, center_ == right_
			, center_ == down_
		);
	}

	template<typename Type_>
	TerrainTileConnectionCliff getHomogeneousConnectionValue(
		const Type_ center_
		, const Type_ up_
		, const Type_ left_
		, const Type_ right_
		, const Type_ down_
		, const Type_ upper_left_
		, const Type_ upper_right_
		, const Type_ lower_left_
		, const Type_ lower_right_
	) {
		return getHomogeneousConnection(
			center_ == up_
			, center_ == left_
			, center_ == right_
			, center_ == down_
			, center_ == upper_left_
			, center_ == upper_right_
			, center_ == lower_left_
			, center_ == lower_right_
		);
	}

	template<typename Matrix_, typename Type_>
	TerrainTileConnectionCliff getHomogeneousConnectionArray(
		const Matrix_& matrix_
		, const Type_ x_
		, const Type_ y_
	) {
		return getHomogeneousConnectionValue(
			matrix_[y_ - 1][x_]
			, matrix_[y_][x_ - 1]
			, matrix_[y_][x_ + 1]
			, matrix_[y_ + 1][x_]
			, matrix_[y_ - 1][x_ - 1]
			, matrix_[y_ - 1][x_ + 1]
			, matrix_[y_ + 1][x_ - 1]
			, matrix_[y_ + 1][x_ + 1]
		);
	}

}

#endif //Included Crafterra Library