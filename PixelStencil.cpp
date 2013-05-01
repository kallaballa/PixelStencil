/*
 * PixelStencil
 * Copyright (C) 2013 Amir Hassan <amir@viel-zu.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
