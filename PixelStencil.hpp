/*
 * PixelStencil.hpp
 *
 *  Created on: Apr 30, 2013
 *      Author: elchaschab
 */

#ifndef PIXELSTENCIL_HPP_
#define PIXELSTENCIL_HPP_

#include "CImg.h"
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/format.hpp>

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
typedef std::map<long, std::vector<Pixel> > PixelMap;

float PIXEL_TO_MM = 3.52112676056;

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
	size_t rectWidthMM = 20;
	size_t rectMarginMM = 20;
	size_t boardMarginMM = 20;
	size_t rectID = 0;

	void writeHeader(size_t widthMM, size_t heightMM) {
		this->ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"<< std::endl;
		this->ofs << "<svg " << std::endl;
		this->ofs << "xmlns:dc=\"http://purl.org/dc/elements/1.1/\"" << std::endl;
		this->ofs << "xmlns:cc=\"http://creativecommons.org/ns#\"" << std::endl;
		this->ofs << "xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"" << std::endl;
		this->ofs << "xmlns:svg=\"http://www.w3.org/2000/svg\"" << std::endl;
		this->ofs << "xmlns=\"http://www.w3.org/2000/svg\"" << std::endl;
		this->ofs << "version=\"1.1\"" << std::endl;
		this->ofs << "width=\"" << widthMM << "\"" << std::endl;
		this->ofs << "height=\"" << heightMM << "\"" << std::endl;
		this->ofs << "id=\"svg2\">" << std::endl;
		this->ofs << "<g id=\"layer1\">" << std::endl;
	}

	void writeFooter() {
		this->ofs << "</g></svg>" << std::endl;
	}
public:
	SVGStencil(const char* filename, size_t width, size_t height, size_t rectWidth, size_t rectMargin, size_t boardMargin) :
		ofs(filename),
		rectWidthMM(rectWidth * PIXEL_TO_MM),
		rectMarginMM(rectMargin * PIXEL_TO_MM),
		boardMarginMM(boardMargin * PIXEL_TO_MM) {
		writeHeader(
				width * rectWidthMM + width * rectMarginMM + boardMargin * PIXEL_TO_MM * 2,
				height * rectWidthMM + height * rectMarginMM + boardMargin * PIXEL_TO_MM * 2);
	}

	virtual ~SVGStencil() {
		writeFooter();
		this->ofs.close();
	}

	void writePixel(size_t x, size_t y) {
		this->ofs << "<rect" << std::endl;
		this->ofs << "width=\"" << rectWidthMM << "\"" << std::endl;
		this->ofs << "height=\"" << rectWidthMM << "\"" << std::endl;
		this->ofs << "x=\"" << boardMarginMM + rectWidthMM * x + rectMarginMM * x << "\"" << std::endl;
		this->ofs << "y=\"" << boardMarginMM + rectWidthMM * y + rectMarginMM * y << "\"" << std::endl;
		this->ofs << "id=\"" << rectID++ << "\"" << std::endl;
		this->ofs << "style=\"fill:none;stroke:#000000;stroke-width:0.09;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;
	}
};
}

/* namespace kallaballa */
#endif /* PIXELSTENCIL_HPP_ */
