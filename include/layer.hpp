/*
 * layer.hpp
 *
 *  Created on: Mar 5, 2017
 *      Author: alessandro
 */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <vector>

#include "layer.hpp"

#include "blob.hpp"
#include "proto/net.pb.h"

template <typename T>
class Layer {

public:
	Layer(const LayerParams& params);

private:
	std::vector<Blob<T> > blobs;
};


#endif /* LAYER_HPP_ */
