/*
 * PixelStencil.cpp
 *
 *  Created on: Apr 30, 2013
 *      Author: elchaschab
 */

#include "PixelStencil.hpp"
#include <iostream>
#include "math.h"
#include "CImg.h"
#include "boost/lexical_cast.hpp"

namespace kallaballa {

PixelPlanes::PixelPlanes(char* filename) : img(filename), width(img.width()), height(img.height()) {
	for (int h = 0; h < img.height(); h++) {
		for (int w = 0; w < img.width(); w++) {

	    	long p = 0;
	    	p |= img(w, h, 0, 0) << 16;
	    	p |= img(w, h, 0, 1) << 8;
	    	p |= img(w, h, 0, 2);

			planes[p].push_back({w,h});
		}
	}

	int i = 0;

	for (auto it = planes.begin(); it != planes.end(); ++it) {
		std::cout << (*it).first << std::endl;
		i++;
	}
	std::cout << planes.size() << std::endl;
}

PixelPlanes::~PixelPlanes() {
}

} /* namespace kallaballa */

int main(int argc, char** argv) {
	using namespace cimg_library;
	using namespace kallaballa;

	if(argc != 5) {
		std::cerr << "Usage: PixelStencil <img file> <pixel width mm> <pixel margin mm> <board margin mm>" << std::endl;
		return 1;
	}

	PixelPlanes pp(argv[1]);
	size_t pixelWidth = boost::lexical_cast<size_t>(argv[2]);
	size_t pixelMargin = boost::lexical_cast<size_t>(argv[3]);
	size_t boardMargin = boost::lexical_cast<size_t>(argv[4]);

	int i = 0;
	for(auto it = pp.begin(); it != pp.end(); ++it) {
		PixelList& pl = (*it).second;
		SVGStencil stencil((boost::format("%d.svg") % i).str().c_str(),
				pp.getWidth(),
				pp.getHeight(),
				pixelWidth,
				pixelMargin,
				boardMargin);

		for(auto it_l = pl.begin(); it_l != pl.end(); ++it_l) {
			stencil.writePixel((*it_l).first, (*it_l).second);
		}
		i++;
	}
}
