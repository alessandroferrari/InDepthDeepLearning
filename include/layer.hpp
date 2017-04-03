/*
 * layer.hpp
 *
 *  Created on: Mar 5, 2017
 *      Author: alessandro
 */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <exception>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <sstring>

#include "layer.hpp"

#include "blob.hpp"
#include "proto/net.pb.h"

template <typename T>
class Layer {

public:
	Layer(const LayerParams& params, const blobs_map<T>& _blobs_map) {
        //setup layer name
		name.assign(params.name);

		//setup bottom blobs
		if(num_bottom_blobs() != params.bottom_size()) {
            std::stringstream ss;
            ss << "Number of bottom blobs specified by params is "<< params.bottom_size() <<
            		" but requested is " << num_bottom_blobs() << ".\n";
			throw std::bad_exception(ss.str());
		}
		for(int bottom_idx = 0; bottom_idx < params.bottom_size(); bottom_idx++ ) {
            std::string bottom_name = params.bottom(bottom_idx);
            auto bottom_iter = _blobs_map.find(bottom_name);
            if(bottom_iter==_blobs_map.end()) {
            	std::stringstream ss;
            	ss << "The requested blob " << bottom_name <<
            			" in bottom blobs not found in the blobs_map.\n";
            	throw std::bad_exception(ss.str());
            } else {
            	bottom_blobs.push_back(bottom_iter->second);
            }
		}

		//setup top blobs
		if(num_top_blobs() != params.top_size()) {
			std::stringstream ss;
			ss << "Number of bottom blobs specified by params is "<< params.bottom_size() <<
			    	" but requested is " << num_bottom_blobs() << ".\n";
			throw std::bad_exception(ss.str());
		}
		for(int top_idx = 0; top_idx < params.top_size(); top_idx++ ) {
            std::string top_name = params.top(top_idx);
            auto top_iter = _blobs_map.find(top_name);
            if(top_iter==_blobs_map.end()) {
            	std::stringstream ss;
            	ss << "The requested blob " << top_name <<
            	     	" in top blobs not found in the blobs_map.\n";
            	throw std::bad_exception(ss.str());
            } else {
                top_blobs.push_back(top_iter->second);
            }
		}
	};
	//copy constructor
	Layer(const Layer& layer);
	//move constructor
	Layer(Layer&& layer);

	virtual int num_top_blobs();
	virtual int num_bottom_blobs();

protected:
	blobs_vector<T> bottom_blobs;
	blobs_vector<T> top_blobs;
    std::string name;

};


#endif /* LAYER_HPP_ */
