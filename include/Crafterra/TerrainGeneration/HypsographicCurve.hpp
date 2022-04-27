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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_GENERATION_HYPSOGRAPHIC_CURVE_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_TERRAIN_GENERATION_HYPSOGRAPHIC_CURVE_HPP

#include <AsLib2/DataType/PrimitiveDataType.hpp> // int
#include <cmath>

namespace Crafterra {

	namespace HypsographicCurve {

		constexpr double math_pi = 3.14159265358979323846; // 円周率

		double funcG(const double x_, const double mountainousness_) {
			return ::std::atan((2.0 * x_ - 1.0) * ::std::tan(mountainousness_ * math_pi * 0.5)) / (mountainousness_ * math_pi * 0.5) * 0.5 + 0.5;
		}

		double funcA(const double x_, const double mountainousness_) {
			return (funcG(x_, mountainousness_) - 0.5) * (mountainousness_ * 0.5 + 0.5) + 0.5;
		}

		double funcB(const double x_) {
			double a = (2.0 * x_ - 2.0);
			return a * a * (1.0 + a) * 0.25 + 1.0;
		}

		double funcC(const double x_) {
			return (::std::tan((2.0 * x_ - 1.0) * 0.25 * math_pi) * ::std::pow(::std::abs(2.0 * x_ - 1.0), 2.0 * x_) + 1.0) * 0.5;
		}

	}

	// 地形の標高分布を表す曲線
	double processNoiseUsingHypsographicCurve(const double noise_, const double min_height_, const double max_height_, const double mountainousness_, const double water_height) {

		const double water_prop = (water_height - min_height_) / (max_height_ - min_height_); // 海面率

		const double noise_adj = ((noise_ > water_prop) ?
				(noise_ - water_prop) / (1.0 - water_prop) * 0.5 + 0.5
				: (noise_ / water_prop) * 0.5);

		const double fa = HypsographicCurve::funcA(noise_adj, mountainousness_ * 0.5 + 0.5);
		double fr = HypsographicCurve::funcB(fa) * HypsographicCurve::funcC(fa);

		if (fr > water_prop)	fr = (2.0 * fr - 1.0) * (1.0 - water_prop) + water_prop;
		else					fr = (2.0 * fr) * water_prop;

		if (fr < 0.0)		fr = 0.0; // never
		else if (fr > 1.0)	fr = 1.0; // never

		return fr;

	}
}

#endif //Included Crafterra Library