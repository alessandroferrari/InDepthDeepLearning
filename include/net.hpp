/*
 * net.hpp
 *
 *  Created on: Mar 7, 2017
 *      Author: alessandro
 */

#ifndef NET_HPP_
#define NET_HPP_

#include <vector>
#include <iostream>
#include <string>
#include "layer.hpp"

class Net {

public:
	Net();
	void setup(const std::istream& in);
	void setup(const std::string& fn_in);
    bool check_graph_correctness();
    void forward();
    void backward();

private:
	std::vector<Layer> layers;
};



#endif /* NET_HPP_ */
