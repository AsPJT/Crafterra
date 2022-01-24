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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_ELAPSED_TIME_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_ELAPSED_TIME_HPP

#include <chrono>
#include <Crafterra/DataType/CrafterraPrimitiveDataType.hpp>

namespace Crafterra {

	class ElapsedTime {

		::std::chrono::system_clock::time_point  now_time{}, old_time{};

	public:
		ElapsedTime() : now_time(::std::chrono::system_clock::now()) {}

		void update() {
			old_time = now_time;
			now_time = ::std::chrono::system_clock::now();
		}

		Int64 getMicroseconds() {
			return ::std::chrono::duration_cast<::std::chrono::microseconds>(now_time - old_time).count();
		}

	};

}

#endif //Included Crafterra Library