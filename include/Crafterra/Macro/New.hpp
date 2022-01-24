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

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MACRO_NEW_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_MACRO_NEW_HPP

//##########################################################################################
// <new> のインクルード
#ifndef CRAFTERRA_NOT_USE_NEW
#ifndef CRAFTERRA_USE_NEW
#define CRAFTERRA_USE_NEW
#endif // CRAFTERRA_USE_NEW
#include <new>
#endif // CRAFTERRA_NOT_USE_NEW
//##########################################################################################
// NEW
#ifndef CRAFTERRA_NEW
#ifdef CRAFTERRA_USE_NEW
#define CRAFTERRA_NEW new(::std::nothrow)
#else
#define CRAFTERRA_NEW new
#endif // CRAFTERRA_USE_NEW
#endif // CRAFTERRA_NEW
//##########################################################################################

#endif //Included Crafterra Library