/*
 * tensor.hpp
 *
 *  Created on: Mar 5, 2017
 *      Author: alessandro
 */

#ifndef BLOB_HPP_
#define BLOB_HPP_

#include <vector>
#include <memory>
#include <array>

template<typename T>
class Blob {

public:
	Blob(const std::vector<int>& shapes_);

private:
	std::shared_ptr<std::array<T> > data;
	std::shared_ptr<std::array<T> > diff;
	std::vector<int> shapes;
};



#endif /* BLOB_HPP_ */
