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


#ifndef PIXELSTENCIL_HPP_
#define PIXELSTENCIL_HPP_

#define cimg_display 0
#include "CImg.h"
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "NamedColor.hpp"

namespace kallaballa
{
using namespace cimg_library;
using std::string;
using std::map;
using std::vector;
using std::ostream;

typedef unsigned char sample_t;
typedef std::pair<int32_t,int32_t> Pixel;
typedef std::vector<Pixel> PixelList;
typedef std::map<Color, std::vector<Pixel> > PixelMap;

float PIXEL_TO_MM = 3.5434;

class PixelPlanes {
	CImg<sample_t> img;
	size_t width;
	size_t height;
	PixelMap planes;
public:
	typedef PixelMap::iterator iterator;

	PixelPlanes(char* filename);
	virtual ~PixelPlanes();

	iterator begin() {
		return planes.begin();
	}

	iterator end() {
		return planes.end();
	}

	size_t getWidth() {
		return width;
	}

	size_t getHeight() {
		return height;
	}
};

class SVGStencil {
	std::ofstream ofs;
	NamedColor color;
	size_t pixelWidthPix;
	size_t pixelMarginPix;
	size_t boardMarginPix;
  size_t realWidthPix;
  size_t realHeightPix;
  size_t pixelID = 0;

	void writeHeader();
	void writeFooter();
public:
	SVGStencil(const char* filename, NamedColor color, size_t widthPix, size_t heightPix, size_t pixelWidthMM, size_t pixelMarginMM, size_t boardMarginMM) ;
	virtual ~SVGStencil();

	void writePixel(size_t x, size_t y);
};
}

/* namespace kallaballa */
#endif /* PIXELSTENCIL_HPP_ */
