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
typedef uint32_t Color;
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
	Color color;
	size_t rectWidthPix;
	size_t rectMarginPix;
	size_t boardMarginPix;
  size_t realWidthPix;
  size_t realHeightPix;
  size_t rectID = 0;

	void writeHeader();
	void writeFooter();
public:
	SVGStencil(const char* filename, Color color, size_t width, size_t height, size_t rectWidth, size_t rectMargin, size_t boardMargin) ;
	virtual ~SVGStencil();

	void writePixel(size_t x, size_t y);
};
}

/* namespace kallaballa */
#endif /* PIXELSTENCIL_HPP_ */
