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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_PERLIN_NOISE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_GENERATION_PERLIN_NOISE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp> // int
#include <algorithm>
#include <random>

namespace Crafterra {

	class PerlinNoise {
	private:

		using Double_ = double;

		///// エイリアス (Alias) /////

		using Pint = ::As::Uint8;


		///// メンバ変数 (Member Variable) /////

		::std::array<Pint, 512> p{ {} };


		///// メンバ関数 /////


		constexpr Double_ getFade(const Double_ t_) const noexcept {
			return t_ * t_* t_* (t_ * (t_ * 6 - 15) + 10);
			//return t_;
		}


		constexpr Double_ getLerp(const Double_ t_, const Double_ a_, const Double_ b_) const noexcept {
			return a_ + t_ * (b_ - a_);
		}


		constexpr Double_ makeGradUV(const Pint hash_, const Double_ u_, const Double_ v_) const noexcept {
			return (((hash_ & 1) == 0) ? u_ : -u_) + (((hash_ & 2) == 0) ? v_ : -v_);
		}


		constexpr Double_ makeGrad(const Pint hash_, const Double_ x_, const Double_ y_) const noexcept {
			return this->makeGradUV(hash_, (hash_ < 8) ? x_ : y_, (hash_ < 4) ? y_ : (hash_ == 12 || hash_ == 14) ? x_ : Double_(0.0));
		}

		constexpr Double_ getGrad(const Pint hash_, const Double_ x_, const Double_ y_) const noexcept {
			return this->makeGrad(hash_ & 15, x_, y_);
		}

		Double_ setNoise(Double_ x_, Double_ y_) const noexcept {

			const ::As::Uint64 floor_x = static_cast<::As::Uint64>(x_);
			const ::As::Uint64 floor_y = static_cast<::As::Uint64>(y_);

			const ::As::IndexUint x_int = static_cast<::As::IndexUint>(floor_x & 255);
			const ::As::IndexUint y_int = static_cast<::As::IndexUint>(floor_y & 255);
			x_ -= static_cast<Double_>(floor_x);
			y_ -= static_cast<Double_>(floor_y);
			const Double_ u{ this->getFade(x_) };
			const Double_ v{ this->getFade(y_) };
			const ::As::IndexUint a0{ static_cast<::As::IndexUint>(this->p[x_int] + y_int) };
			const ::As::IndexUint a1{ static_cast<::As::IndexUint>(this->p[a0]) };
			const ::As::IndexUint a2{ static_cast<::As::IndexUint>(this->p[a0 + 1]) };
			const ::As::IndexUint b0{ static_cast<::As::IndexUint>(this->p[x_int + 1] + y_int) };
			const ::As::IndexUint b1{ static_cast<::As::IndexUint>(this->p[b0]) };
			const ::As::IndexUint b2{ static_cast<::As::IndexUint>(this->p[b0 + 1]) };

			return this->getLerp(v,
				this->getLerp(u, this->getGrad(this->p[a1], x_, y_), this->getGrad(this->p[b1], x_ - 1, y_)),
				this->getLerp(u, this->getGrad(this->p[a2], x_, y_ - 1), this->getGrad(this->p[b2], x_ - 1, y_ - 1)));
		}

		Double_ setOctaveNoise(const ::As::IndexUint octaves_, Double_ x_, Double_ y_) const noexcept {
			Double_ noise_value{};
			Double_ amp{ 1.0 };
			for (::As::IndexUint i{}; i < octaves_; ++i) {
				noise_value += this->setNoise(x_, y_) * amp;
				x_ *= 2.0;
				y_ *= 2.0;
				amp *= 0.5;
			}
			return noise_value;
		}

	public:

		//オクターブ有りノイズを取得する
		Double_ octaveNoise(const ::As::IndexUint octaves_, const Double_ x_, const Double_ y_) const noexcept {
			const Double_ noise_value{ this->setOctaveNoise(octaves_, x_,y_) * Double_(0.5) + Double_(0.5) };
			return ((noise_value >= Double_(1.0)) ? Double_(1.0) : ((noise_value <= Double_(0.0)) ? Double_(0.0) : noise_value));
		}

		//SEED値を設定する
		template <typename Shuffle_>
		void setSeed(const Shuffle_& shuffle_) {
			for (::As::IndexUint i{}; i < 256; ++i)
				this->p[i] = static_cast<Pint>(i);
			shuffle_(this->p.begin(), this->p.begin() + 256);
			for (::As::IndexUint i{}; i < 256; ++i)
				this->p[256 + i] = this->p[i];
		}


		///// コンストラクタ (Constructor) /////

		PerlinNoise() = default;
		template <typename Shuffle_>
		explicit PerlinNoise(const Shuffle_& shuffle_) {
			this->setSeed(shuffle_);
		}

	};

}

#endif //Included Crafterra Library