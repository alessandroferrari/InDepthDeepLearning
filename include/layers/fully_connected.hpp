/*
 * fully_connected.hpp
 *
 *  Created on: Mar 20, 2017
 *      Author: deepcolony
 */

#ifndef INCLUDE_LAYERS_FULLY_CONNECTED_HPP_
#define INCLUDE_LAYERS_FULLY_CONNECTED_HPP_

#include <string>
#include <sstream>
#include <memory>
#include "layer.hpp"

template <typename T>
class FullyConnected : Layer {
public:

	FullyConnected(const LayerParams& params, int batch_size_)
                                          : batch_size(batch_size_)
    {
        name = params.name();
        top_name = params.top();
        bottom_name = params.bottom();
        if( params.has_fully_connected_params() ) {
		    out = params.fully_connected_params().output();
        } else {
            throw std::invalid_argument("LayerParam for fully connected layer does not have FullyConnectedParams!");
        }
        std::vector<int> shapes_ = {out,batch_size};
        std::shared_ptr<Blob<T> > tmp_top(Blob<T>(shapes_, top_name) );
        top = std::move(tmp_top);
	}

	void LayerSetup(const Blob<T>& bottom_blob) {
		//set the bottom blob (the layer is responsible for instantiate only the top blob)
        std::shared_ptr<Blob<T> > tmp_bottom(bottom_blob);
        bottom = std::move(tmp_bottom);
        std::vector<int> bottom_shapes = bottom.get()->get_shapes();
        if(bottom_shapes.size()!=2) {
            std::stringstream ss;
            ss << "Bottom input blob of layer " << name << " has not 2 dimensions.";
            throw std::invalid_argument( ss.str() );
        }
        std::vector<int> top_shapes = top.get()->get_shapes();
        if(top_shapes.size()!=2) {
			std::stringstream ss;
			ss << "Top input blob of layer " << name << " has not 2 dimensions.";
			throw std::invalid_argument( ss.str() );
		}

        //weights and biases blob initialization
        int bottom_dim, bottom_batch_size, top_dim, top_batch_size;
        bottom_dim = bottom_shapes[0];
        bottom_batch_size = bottom_shapes[1];
        top_dim = top_shapes[0];
        top_batch_size = top_shapes[1];
        if (top_batch_size!=bottom_batch_size) {
        	std::stringstream ss;
        	ss << "For fully_connected layer " << name << " the batch size of the bottom blob is different from that of the top blob.";
        	throw std::logic_error(ss.str());
        }
        std::vector<int> weights_size = {bottom_dim, top_dim};
        std::shared_ptr<Blob<T> > weights_tmp(Blob<T>(weights_size) );
        weights = std::move(weights_tmp);
        std::vector<int> biases_size = {top_dim};
        std::shared_ptr<Blob<T> > biases_tmp(Blob<T>(biases_size) );
        biases = std::move(biases_tmp);
	}


private:
	int out;
    std::string name, top_name, bottom_name;
    std::shared_ptr<Blob<T> > top, bottom, weights, biases;
    int batch_size;
};



#endif /* INCLUDE_LAYERS_FULLY_CONNECTED_HPP_ */
