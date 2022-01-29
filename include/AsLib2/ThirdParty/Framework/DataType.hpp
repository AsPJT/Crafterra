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

#ifndef INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_DATA_TYPE_HPP
#define INCLUDED_ASLIB2_ASLIB2_THIRD_PARTY_FRAMEWORK_DATA_TYPE_HPP

#include <AsLib2C/DataType/PrimitiveDataType.hpp>

namespace AsLib2 {

	using DxGraphInt = int;

	class DxGraph {
	private:
		DxGraphInt graph = -1;
	public:
		void set (const DxGraphInt graph_) { this->graph = graph_; }
		DxGraphInt get () const { return this->graph; }
	};

	template<::Asc::DataType::IndexUint Index_>
	class DxGraphArray {
	private:
		DxGraphInt graph[Index_]{};
	public:
		void set(const ::Asc::DataType::IndexUint index_, const DxGraphInt graph_) { this->graph[index_] = graph_; }
		int get (const ::Asc::DataType::IndexUint index_) const { return this->graph[index_]; }
		DxGraphInt* getPtr () { return this->graph; }
	};


}

#endif //Included Crafterra Library