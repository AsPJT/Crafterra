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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_HOMOGENEOUS_CONNECTION_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MAP_HOMOGENEOUS_CONNECTION_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>
#include <AsLib2/DataType/ArrayDataType.hpp>
#include <AsLib2/DataType/StringDataType.hpp>

#include <Crafterra/Enum/CrafterraEnum.hpp>

namespace Crafterra {

	// 同じ性質のブロックとの接続タイプ ( 崖 )
	CliffConnection getHomogeneousConnectionCliff(
		const bool left_
		, const bool right_
		, const bool down_
	) {
		if (down_) {
			if (left_) {
				if (right_) return CliffConnection::left_right_down_cliff;
				else        return CliffConnection::left_down_cliff;
			}
			else {
				if (right_) return CliffConnection::right_down_cliff;
				else        return CliffConnection::down_cliff;
			}
		}
		else {
			if (left_) {
				if (right_) return CliffConnection::left_right_up_cliff;
				else        return CliffConnection::left_up_cliff;
			}
			else {
				if (right_) return CliffConnection::right_up_cliff;
				else        return CliffConnection::up_cliff;
			}
		}
	}

	::As::DataType::Uint32 getAutoTileIndex(const AutoTileConnection ahc_, const ::As::DataType::Uint32 animation_number_, const ::As::DataType::Uint32 animation_max_number_) {
		const ::As::DataType::Uint32 an2 = animation_number_ * 2; // アニメーション数の 2 倍
		const ::As::DataType::Uint32 amn2 = animation_max_number_ * 2; // 最大アニメーション数の 2 倍
		const ::As::DataType::Uint32 ahc = ::As::DataType::Uint32(ahc_);
		const ::As::DataType::Uint32 ahcp2 = ::As::DataType::Uint32(ahc_) / 2;
		const ::As::DataType::Uint32 right = ((ahc % 2 == 0) ? 0 : 1);
		return amn2 * ahcp2 + an2 + right;
	}

	// 今後、別の hpp を作成して管理
	struct AutoTileIndex {
		::As::DataType::Uint32 auto_tile_upper_left{};
		::As::DataType::Uint32 auto_tile_upper_right{};
		::As::DataType::Uint32 auto_tile_lower_left{};
		::As::DataType::Uint32 auto_tile_lower_right{};

		AutoTileIndex(const AutoTile& auto_tile_, const ::As::DataType::Uint32 animation_number_, const ::As::DataType::Uint32 animation_max_number_) :
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
				if (upper_left_) at.auto_tile_upper_left = AutoTileConnection::all_upper_left;
				else              at.auto_tile_upper_left = AutoTileConnection::cross_upper_left;
			}
			else                  at.auto_tile_upper_left = AutoTileConnection::up_and_down_upper_left;
		}
		else {
			if (left_)             at.auto_tile_upper_left = AutoTileConnection::left_and_right_upper_left;
			else                  at.auto_tile_upper_left = AutoTileConnection::nothing_upper_left;
		}
		// 右上
		if (up_) {
			if (right_) {
				if (upper_right_) at.auto_tile_upper_right = AutoTileConnection::all_upper_right;
				else              at.auto_tile_upper_right = AutoTileConnection::cross_upper_right;
			}
			else                  at.auto_tile_upper_right = AutoTileConnection::up_and_down_upper_right;
		}
		else {
			if (right_)             at.auto_tile_upper_right = AutoTileConnection::left_and_right_upper_right;
			else                  at.auto_tile_upper_right = AutoTileConnection::nothing_upper_right;
		}
		// 左下
		if (down_) {
			if (left_) {
				if (lower_left_) at.auto_tile_lower_left = AutoTileConnection::all_lower_left;
				else              at.auto_tile_lower_left = AutoTileConnection::cross_lower_left;
			}
			else                  at.auto_tile_lower_left = AutoTileConnection::up_and_down_lower_left;
		}
		else {
			if (left_)             at.auto_tile_lower_left = AutoTileConnection::left_and_right_lower_left;
			else                  at.auto_tile_lower_left = AutoTileConnection::nothing_lower_left;
		}
		// 右上
		if (down_) {
			if (right_) {
				if (lower_right_) at.auto_tile_lower_right = AutoTileConnection::all_lower_right;
				else              at.auto_tile_lower_right = AutoTileConnection::cross_lower_right;
			}
			else                  at.auto_tile_lower_right = AutoTileConnection::up_and_down_lower_right;
		}
		else {
			if (right_)             at.auto_tile_lower_right = AutoTileConnection::left_and_right_lower_right;
			else                  at.auto_tile_lower_right = AutoTileConnection::nothing_lower_right;
		}

		return at;
	}

	// 同じ性質のブロックとの接続タイプ ( 通常 )
	CliffConnection getHomogeneousConnection(
		const bool up_
		, const bool left_
		, const bool right_
		, const bool down_
		, const bool upper_left_
		, const bool upper_right_
		, const bool lower_left_
		, const bool lower_right_
	) {
		CliffConnection mcthc = CliffConnection::all;

		if (up_) {
			if (left_) {
				if (right_) {
					if (down_) return   CliffConnection::all;
					else        mcthc = CliffConnection::up_left_right_0;
				}
				else {
					if (down_) mcthc = CliffConnection::up_left_down_0;
					else        mcthc = CliffConnection::up_left_0;
				}
			}
			else {
				if (right_) {
					if (down_) mcthc = CliffConnection::up_right_down_0;
					else        mcthc = CliffConnection::up_right_0;
				}
				else {
					if (down_) return   CliffConnection::up_down;
					else        return   CliffConnection::up;
				}
			}
		}
		else {
			if (left_) {
				if (right_) {
					if (down_) mcthc = CliffConnection::left_right_down_0;
					else        return   CliffConnection::left_right;
				}
				else {
					if (down_) mcthc = CliffConnection::left_down_0;
					else        return   CliffConnection::left;
				}
			}
			else {
				if (right_) {
					if (down_) mcthc = CliffConnection::right_down_0;
					else        return   CliffConnection::right;
				}
				else {
					if (down_) return   CliffConnection::down;
					else        return   CliffConnection::nothing;
				}
			}
		}
		return mcthc;
	}


	template<typename Type_>
	CliffConnection getHomogeneousConnectionValueElevation3(
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
	CliffConnection getHomogeneousConnectionCliffValueElevation3(
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
	CliffConnection getHomogeneousConnectionValue(
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
	CliffConnection getHomogeneousConnectionArray(
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