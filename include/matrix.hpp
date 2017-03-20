/*
 * matrix.hpp
 *
 *  Created on: Mar 20, 2017
 *      Author: alessandro
 *
 *      This class wraps matrices so that they be easily wrapped in shared pointers mantaining RAII design principles.
 */

#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <array>

template <typename T>
class Matrix {
public:

	//constructor for lvalue of vector shape
	Matrix(const std::vector<int>& shapes_) {
        copy(shapes_.begin(), shapes_.end(), shapes.begin());
		setUp_from_shapes();
	};

	//constructor for rvalue of vector shape
	Matrix(std::vector<int>&& shapes_) : shapes(shapes_) {
		setUp_from_shapes();
	};

	//copy constructor
	Matrix(const Matrix<T>& other) {
		copy(other.shapes.begin(), other.shapes.end(), shapes.begin());
		copy(other.accumulated_indeces.begin(), other.accumulated_indeces.end(), accumulated_indeces.begin());
		tot_size = other.tot_size;
		data = new T[tot_size];
		for(int i=0; i<tot_size; i++) {
            data[i] = other.data[i];
		}
	};

	//move constructor
	Matrix(Matrix<T>&& other): shapes(std::move(other.shapes)),
			                   accumulated_indeces(std::move(other.accumulated_indeces)),
							   tot_size(other.tot_size),
							   data(other.data) {
		other.data = nullptr;
	}

	void setUp_from_shapes() {
		if(shapes.size()>0) {
			tot_size = 1;
			for(auto iter = shapes.rbegin(); iter != shapes.rend(); iter++) {
				tot_size *= *iter;
			}
			data = new T[tot_size];

			int size = shapes.size();
			accumulated_indeces[ size - 1] = 1;
			for(int iter = size - 2; iter >= 0; iter-- ) {
				accumulated_indeces[iter] = accumulated_indeces[iter+1] * shapes[iter+1];
			}
		} else {
			throw std::invalid_argument( "Shapes specified is empty when build a new blob." );
		}
	};

	~Matrix() {
		if (data){
		    delete[] data;
		}
	};

	T* get_data() {
        return data;
	};

	template <typename D, typename SIZE>
	int get_array_index(D indeces)
	{
		if(accumulated_indeces.size()!=SIZE) {
			throw std::invalid_argument( "Shapes and indices are not consistent." );
		}
		int index = 0;
		for(int i = 0; i != SIZE; i++) {
            index = index + indeces[i] * accumulated_indeces[i];
		}
		return index;
	}

	template <typename D>
	inline T get_data_1d_idx(const D& idx) {
		if(idx>=tot_size) {
			throw std::out_of_range( "The index requested for the matrix is outside array size." );
		}
		return data[idx];
	}

	template <typename D, typename SIZE>
	inline T get_data(const D& indeces) {
		int idx = get_array_index<D, SIZE>(indeces);
        return get_data_1d_idx(idx);
	}

	template <typename D>
	inline void set_data_1d_idx(const T& value, const D& idx) {
		if(idx>=tot_size) {
			throw std::out_of_range( "The index requested for the matrix is outside array size." );
		}
		data[idx] = value;
	}

	template <typename D, typename SIZE>
	inline void set_data(const T& value, const D& indeces) {
        int idx = get_array_index<D, SIZE>(indeces);
        set_data_1d_idx(value, idx);
	}

	std::vector<int> get_shapes() {
        return shapes;
	}

private:
	std::vector<int> shapes;
	int tot_size;
	std::vector<int> accumulated_indeces;
	T* data;
};


#endif /* INCLUDE_MATRIX_HPP_ */
