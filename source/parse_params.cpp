/*
 * parse_params.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: alessandro
 */

#include "proto/net.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <fcntl.h>
#include <string>
#include <iostream>

using namespace google::protobuf;
using google::protobuf::Message;

int main() {

	std::string textFileName = "/tmp/net.prototxt";

	NetParams parsed;
    int fd = open(textFileName.c_str(), O_RDONLY);
    io::FileInputStream fstream(fd);
    TextFormat::Parse(&fstream, &parsed);

    for(int i=0; i<parsed.layer_size(); i++) {
    	LayerParams layer_params = parsed.layer(i);
        std::cout << "name:" << layer_params.name() << " bottom: " << layer_params.bottom() <<
        		" top: " << layer_params.top() << " type: " << layer_params.type() << std::endl;
    }

    std::string out;
    TextFormat::PrintToString(parsed,&out);
    std::cout << out << std::endl;

}
