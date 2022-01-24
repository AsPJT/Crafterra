﻿/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_RANGE_RECT_BASE_WITH_VALUE_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_RANGE_RECT_BASE_WITH_VALUE_HPP

#include <DTL/Base/Struct.hpp>
#include <DTL/Macros/constexpr.hpp>
#include <DTL/Macros/nodiscard.hpp>
#include <DTL/Type/SizeT.hpp>
#include <DTL/Range/BasicRect.hpp>

/*#######################################################################################
	[概要] "dtl名前空間"とは"DungeonTemplateLibrary"の全ての機能が含まれる名前空間である。
	[Summary] The "dtl" is a namespace that contains all the functions of "DungeonTemplateLibrary".
#######################################################################################*/
namespace dtl {
	inline namespace range { //"dtl::range"名前空間に属する

		//四角形クラス
		template<typename Derived_, typename Matrix_Var_, Matrix_Var_ matrix_value_ = Matrix_Var_{} >
		class RectBaseWithValue : public ::dtl::range::BasicRect<Derived_> {
		private:

			///// エイリアス (Alias) /////

			using Index_Size = ::dtl::type::size;
			using RectBase_t = ::dtl::range::BasicRect<Derived_>;


		protected:


			///// メンバ変数 (Member Variable) /////

			Matrix_Var_ draw_value{ matrix_value_ };


		public:


			///// メンバ変数の値を取得 (Get Value) /////

/*#######################################################################################
	[概要] 描画値を取得する。
	[戻り値] 戻り値の型は 当クラスの参照値 である。
	[参考ページ] https://github.com/Kasugaccho/DungeonTemplateLibrary/wiki/dtl::XX::YY::getValue-(形状描画)/
	[Summary] Gets the drawing value.
	[Return value] The return type is a reference value of this class.
#######################################################################################*/
			template<typename Matrix_Int1_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				Derived_& getValue(Matrix_Int1_& value_) noexcept {
				value_ = static_cast<Matrix_Int1_>(this->draw_value);
				return static_cast<Derived_&>(*this);
			}

/*#######################################################################################
	[概要] 描画値を取得する。
	[戻り値] 戻り値の型は Matrix_Var_ である。
	[参考ページ] https://github.com/Kasugaccho/DungeonTemplateLibrary/wiki/dtl::XX::YY::getValue-(形状描画)/
	[Summary] Gets the drawing value.
	[Return value] The return type is Matrix_Var_.
#######################################################################################*/
			DTL_VERSIONING_CPP17_NODISCARD
			constexpr Matrix_Var_ getValue() const noexcept {
				return this->draw_value;
			}


			///// 消去 (Clear) /////


/*#######################################################################################
	[概要] 塗り値を初期値に戻す(描画値を消去する)。
	[戻り値] 戻り値の型は 当クラスの参照値 である。
	[Summary] Resets the drawing value to the initial value (deletes the drawing value).
	[Return value] The return type is a reference value of this class.
#######################################################################################*/
			DTL_VERSIONING_CPP14_CONSTEXPR
				Derived_& clearValue() noexcept {
				const Matrix_Var_ new_draw_value{};
				this->draw_value = new_draw_value;
				return static_cast<Derived_&>(*this);
			}

/*#######################################################################################
	[概要] 全ての値を初期値に戻す。
	[戻り値] 戻り値の型は 当クラスの参照値 である。
	[Summary] Reset all values to their initial values.
	[Return value] The return type is a reference value of this class.
#######################################################################################*/
			DTL_VERSIONING_CPP14_CONSTEXPR
				Derived_& clear() noexcept {
				this->clearRange();
				this->clearValue();
				return static_cast<Derived_&>(*this);
			}


			///// 代入 /////

/*#######################################################################################
	[概要] 描画値を設定する。
	[戻り値] 戻り値の型は 当クラスの参照値 である。
	[Summary] Set the drawing value.
	[Return value] The return type is a reference value of this class.
#######################################################################################*/
			DTL_VERSIONING_CPP14_CONSTEXPR
				Derived_& setValue(const Matrix_Var_& draw_value_) noexcept {
				this->draw_value = draw_value_;
				return static_cast<Derived_&>(*this);
			}


			///// コンストラクタ (Constructor) /////

			RectBaseWithValue() = default;
			constexpr explicit RectBaseWithValue(const ::dtl::base::MatrixRange& matrix_range_) noexcept
				:RectBase_t(matrix_range_)  {}
			constexpr RectBaseWithValue(const Index_Size start_x_, const Index_Size start_y_, const Index_Size width_, const Index_Size height_) noexcept
				:RectBase_t(start_x_, start_y_, width_, height_) {}

			constexpr explicit RectBaseWithValue(const Matrix_Var_ & draw_value_) noexcept
				:draw_value(draw_value_) {}
			constexpr RectBaseWithValue(const ::dtl::base::MatrixRange & matrix_range_, const Matrix_Var_ & draw_value_) noexcept
				:RectBase_t(matrix_range_),
				draw_value(draw_value_) {}
			constexpr RectBaseWithValue(const Index_Size start_x_, const Index_Size start_y_, const Index_Size width_, const Index_Size height_, const Matrix_Var_ & draw_value_) noexcept
				:RectBase_t(start_x_, start_y_, width_, height_),
				draw_value(draw_value_) {}
		};
	}
}

#endif //Included Dungeon Template Library
