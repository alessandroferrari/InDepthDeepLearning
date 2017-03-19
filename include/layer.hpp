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

class Layer {

public:
	Layer(LayerParams params);

private:
	std::vector<Blob> blobs;

};


#endif /* LAYER_HPP_ */
