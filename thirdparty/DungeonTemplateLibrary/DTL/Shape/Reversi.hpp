/*#######################################################################################
	Copyright (c) 2017-2019 Kasugaccho
	Copyright (c) 2018-2019 As Project
	https://github.com/Kasugaccho/DungeonTemplateLibrary
	wanotaitei@gmail.com

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#######################################################################################*/
#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_DOBUTSU_REVERSI_HPP
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_DTL_SHAPE_DOBUTSU_REVERSI_HPP

/*#######################################################################################
	日本語リファレンス (Reference-JP)
	https://github.com/Kasugaccho/DungeonTemplateLibrary/wiki/dtl::shape::Reversi-(形状クラス)/
#######################################################################################*/

#include <DTL/Base/Struct.hpp>
#include <DTL/Macros/constexpr.hpp>
#include <DTL/Macros/nodiscard.hpp>
#include <DTL/Type/Forward.hpp>
#include <DTL/Type/SizeT.hpp>
#include <DTL/Range/RectBaseWithBlackWhite.hpp>
#include <DTL/Utility/DrawJagged.hpp>

/*#######################################################################################
	[概要] "dtl名前空間"とは"DungeonTemplateLibrary"の全ての機能が含まれる名前空間である。
	[Summary] The "dtl" is a namespace that contains all the functions of "DungeonTemplateLibrary".
#######################################################################################*/
namespace dtl {
	inline namespace shape { //"dtl::shape"名前空間に属する

/*#######################################################################################
	[概要] Reversiとは "Matrixの描画範囲に どうぶつしょうぎ の駒を初期位置に設置する" 機能を持つクラスである。
	[Summary] Reversi is a class that generates Dobutsu Shogi, a Japanese game, in the drawing range of Matrix.
#######################################################################################*/
		template<typename Matrix_Var_>
		class Reversi : public ::dtl::range::RectBaseWithBlackWhite<Reversi<Matrix_Var_>, Matrix_Var_>,
			public ::dtl::utility::DrawJagged<Reversi<Matrix_Var_>, Matrix_Var_> {
		private:


			///// エイリアス (Alias) /////

			using Index_Size = ::dtl::type::size;
			using ShapeBase_t = ::dtl::range::RectBaseWithBlackWhite<Reversi, Matrix_Var_>;
			using DrawBase_t = ::dtl::utility::DrawJagged<Reversi, Matrix_Var_>;

			friend DrawBase_t;


			///// 基本処理 /////

			//STL
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				typename DTL_TYPE_ENABLE_IF<Matrix_::is_jagged::value, bool>::DTL_TYPE_EITYPE
				drawNormal(Matrix_&& matrix_, Args_&& ... args_) const noexcept {
				const Index_Size end_y_{ this->calcEndY(matrix_.getY()) };
				if (end_y_ <= this->start_y + 1) return true;
				const Index_Size set_y{ (end_y_ - this->start_y) / 2 };
				const Index_Size end_x_{ this->calcEndX(matrix_.getX(this->start_y + set_y - 1)) };
				if (end_x_ <= this->start_x + 1) return true;
				const Index_Size end_x2_{ this->calcEndX(matrix_.getX(this->start_y + set_y)) };
				if (end_x2_ <= this->start_x + 1) return true;

				const Index_Size set_x1{ (end_x_ - this->start_x) / 2 };
				const Index_Size set_x2{ (end_x2_ - this->start_x) / 2 };

				matrix_.set(this->start_x + set_x1 - 1, this->start_y + set_y - 1, this->white_value, args_...);
				matrix_.set(this->start_x + set_x1, this->start_y + set_y - 1, this->black_value, args_...);
				matrix_.set(this->start_x + set_x2 - 1, this->start_y + set_y, this->black_value, args_...);
				matrix_.set(this->start_x + set_x2, this->start_y + set_y, this->white_value, args_...);
				return true;
			}

			//Normal
			template<typename Matrix_, typename ...Args_>
			DTL_VERSIONING_CPP14_CONSTEXPR
				typename DTL_TYPE_ENABLE_IF<!Matrix_::is_jagged::value, bool>::DTL_TYPE_EITYPE
				drawNormal(Matrix_&& matrix_, Args_&& ... args_) const noexcept {
				const Index_Size end_x_{ this->calcEndX(matrix_.getX()) };
				const Index_Size end_y_{ this->calcEndY(matrix_.getY()) };
				if (end_x_ <= this->start_x + 1 || end_y_ <= this->start_y + 1) return true;

				const Index_Size set_y{ (end_y_ - this->start_y) / 2 };
				const Index_Size set_x{ (end_x_ - this->start_x) / 2 };

				matrix_.set(this->start_x + set_x - 1, this->start_y + set_y - 1, this->white_value, args_...);
				matrix_.set(this->start_x + set_x, this->start_y + set_y - 1, this->black_value, args_...);
				matrix_.set(this->start_x + set_x - 1, this->start_y + set_y, this->black_value, args_...);
				matrix_.set(this->start_x + set_x, this->start_y + set_y, this->white_value, args_...);
				return true;
			}

		public:


			///// コンストラクタ (Constructor) /////

			using ShapeBase_t::ShapeBase_t;
		};
	}
}

#endif //Included Dungeon Template Library
