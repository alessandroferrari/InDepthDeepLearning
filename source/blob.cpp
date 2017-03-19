/*
 * blob.cpp
 *
 *  Created on: Mar 19, 2017
 *      Author: alessandro
 */

#include "blob.hpp"

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <numeric>

using std::accumulate;
using std::shared_ptr;
using std::array;

template <typename T>
Blob<T>::Blob(const std::vector<int>& shapes_) {
    shapes = shapes_;
    int tot = 0, mul = 1;
    for(auto iter = shapes_.rend(); iter < shapes_.rbegin(); iter++) {

    }
    shared_ptr<array<T, tot> > _data();
}


