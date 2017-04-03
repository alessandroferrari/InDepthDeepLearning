/*
 * tensor.hpp
 *
 *  Created on: Mar 5, 2017
 *      Author: alessandro
 */

#ifndef BLOB_HPP_
#define BLOB_HPP_

#include <map>
#include <vector>
#include <memory>
#include <array>
#include <utility>
#include <string>
#include <algorithm>
#include "matrix.hpp"

template<typename T>
class Blob {

public:
	Blob(const std::vector<int>& shapes_, const std::string name_ = "") :
	                                                   name(name_) {
		std::shared_ptr<Matrix<T> > tmp(new Matrix<T>(shapes_));
        data = std::move(tmp);
        std::shared_ptr<Matrix<T> > tmp_diff(new Matrix<T>(shapes_));
        diff = std::move(tmp_diff);
	};

	Blob(std::vector<int>&& shapes_, const std::string name_ = "") :
	                               name(name_) {
		std::shared_ptr<Matrix<T> > tmp(new Matrix<T>(shapes_));
		data = std::move(tmp);
		std::shared_ptr<Matrix<T> > tmp_diff(new Matrix<T>(shapes_));
		diff = std::move(tmp_diff);
	}

	//copy constructor
	Blob(const Blob<T>& other) {
		//invoke Matrix copy constructor
        std::shared_ptr<Matrix<T> > tmp(new Matrix<T>(*other.data.get()) );
        data = std::move(tmp);
        std::shared_ptr<Matrix<T> > tmp_diff(new Matrix<T>(*other.diff.get()) );
        diff = std::move(tmp_diff);
        name = other.name;
	}

	//move constructor
	Blob(Blob<T>&& other) {
        data = std::move(other.data);
        diff = std::move(other.diff);
        name = std::move(other.name);
	}

	std::vector<int> get_shapes() {
		return data.get()->get_shapes();
	}

private:
	std::shared_ptr<Matrix<T> > data;
	std::shared_ptr<Matrix<T> > diff;
	std::string name;
};

template <typename T>
using blobs_vector = std::vector<std::shared_ptr<Blob<T> > >;

template <typename T>
using blobs_map = std::map<std::string, std::shared_ptr<Blob<T> > >;
#endif /* BLOB_HPP_ */
