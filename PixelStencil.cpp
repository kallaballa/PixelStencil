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
#include <iomanip>
#include "math.h"
#include "CImg.h"
#include "NamedColorTable.hpp"

namespace kallaballa {

PixelPlanes::PixelPlanes(char* filename) : img(filename), width(img.width()), height(img.height()) {
	for (int h = 0; h < img.height(); h++) {
		for (int w = 0; w < img.width(); w++) {
			Color p = 0;
			p |= img(w, h, 0, 0) << 16;
			p |= img(w, h, 0, 1) << 8;
			p |= img(w, h, 0, 2);

			planes[p].push_back({w,h});
		}
	}
}

PixelPlanes::~PixelPlanes() {
}

SVGStencil::SVGStencil(const char* filename, NamedColor color, size_t widthPix, size_t heightPix, size_t pixelWidthMM, size_t pixelMarginMM, size_t boardMarginMM) :
	ofs(filename),
	color(color),
	pixelWidthPix(pixelWidthMM * PIXEL_TO_MM),
	pixelMarginPix(pixelMarginMM * PIXEL_TO_MM),
	boardMarginPix(boardMarginMM * PIXEL_TO_MM),
	realWidthPix(widthPix * pixelWidthPix + widthPix * pixelMarginPix + boardMarginPix * 2),
	realHeightPix(heightPix * pixelWidthPix + heightPix * pixelMarginPix + boardMarginPix * 2) {
  writeHeader();
}

SVGStencil::~SVGStencil() {
	writeFooter();
	this->ofs.close();
}

void SVGStencil::writeHeader() {
	this->ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"<< std::endl;
	this->ofs << "<svg " << std::endl;
	this->ofs << "xmlns:dc=\"http://purl.org/dc/elements/1.1/\"" << std::endl;
	this->ofs << "xmlns:cc=\"http://creativecommons.org/ns#\"" << std::endl;
	this->ofs << "xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"" << std::endl;
	this->ofs << "xmlns:svg=\"http://www.w3.org/2000/svg\"" << std::endl;
	this->ofs << "xmlns=\"http://www.w3.org/2000/svg\"" << std::endl;
	this->ofs << "version=\"1.1\"" << std::endl;
	this->ofs << "width=\"" << realWidthPix << "\"" << std::endl;
	this->ofs << "height=\"" << realHeightPix << "\"" << std::endl;
	this->ofs << "id=\"svg2\">" << std::endl;
	this->ofs << "<g id=\"layer1\">" << std::endl;

	this->ofs << "<rect" << std::endl;
	this->ofs << "width=\"" << realWidthPix << "\"" << std::endl;
	this->ofs << "height=\"" << realHeightPix << "\"" << std::endl;
	this->ofs << "x=\"0\"" << std::endl;
	this->ofs << "y=\"0\"" << std::endl;
	this->ofs << "id=\"-1\"" << std::endl;
	this->ofs << "style=\"fill:none;stroke:#ff0000;stroke-width:0.09;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;
	this->ofs << "<text x=\"" << boardMarginPix / 2 << "\" y=\"" << boardMarginPix << "\" fill=\"#" << std::setfill('0') << std::setw(6) << std::hex << color.rgb << std::dec << "\" style=\"font-size:" << boardMarginPix / 2 << "px\" stroke=\"black\">" << color.name << "</text>" << std::endl;
}

void SVGStencil::writeFooter() {
	this->ofs << "</g></svg>" << std::endl;
}

void SVGStencil::writePixel(size_t x, size_t y) {
	this->ofs << "<rect" << std::endl;
	this->ofs << "width=\"" << pixelWidthPix << "\"" << std::endl;
	this->ofs << "height=\"" << pixelWidthPix << "\"" << std::endl;
	this->ofs << "x=\"" << boardMarginPix + pixelWidthPix * x + pixelMarginPix * x << "\"" << std::endl;
	this->ofs << "y=\"" << boardMarginPix + pixelWidthPix * y + pixelMarginPix * y << "\"" << std::endl;
	this->ofs << "id=\"" << pixelID++ << "\"" << std::endl;
	this->ofs << "style=\"fill:none;stroke:#ff0000;stroke-width:0.09;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:none\" />" << std::endl;
}
} /* namespace kallaballa */

int main(int argc, char** argv) {
	using namespace kallaballa;

	if(argc != 5) {
		std::cerr << "Usage: PixelStencil <img file> <pixel width mm> <pixel margin mm> <board margin mm>" << std::endl;
		return 1;
	}

	NamedColorTable ral;
	ral.readFromCSV("colors.txt");
	PixelPlanes pp(argv[1]);
	size_t pixelWidthMM = atoi(argv[2]);
	size_t pixelMarginMM = atoi(argv[3]);
	size_t boardMarginMM = atoi(argv[4]);

	int i = 0;
	for(auto it = pp.begin(); it != pp.end(); ++it) {
		const Color& color = (*it).first;
    const PixelList& pl = (*it).second;

    NamedColor sample;
    sample.rgb = color;
    auto nearest = ral.find_nearest(sample);
		std::cerr << std::dec << int(nearest.second) << "\t#" << std::setfill('0') << std::setw(6) << std::hex << (*nearest.first).rgb << '\t' << color << '\t' << (*nearest.first).name << std::endl;

		SVGStencil stencil((string(argv[1]) + std::to_string(i) + ".svg").c_str(),
		    *nearest.first,
		    pp.getWidth(),
				pp.getHeight(),
				pixelWidthMM,
				pixelMarginMM,
				boardMarginMM);

		for(auto it_l = pl.begin(); it_l != pl.end(); ++it_l) {
			stencil.writePixel((*it_l).first, (*it_l).second);
		}
		i++;
	}
}
