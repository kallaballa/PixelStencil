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


#ifndef NAMEDCOLORTABLE_HPP_
#define NAMEDCOLORTABLE_HPP_

#include "kdtree++/kdtree.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "NamedColor.hpp"

namespace kallaballa
{
using std::string;

double colorComponent(const NamedColor& color, const int& k);
std::vector<string> getNextLineAndSplitIntoTokens(std::istream& str);

class NamedColorTable: public KDTree::KDTree<3, NamedColor, std::pointer_to_binary_function<const NamedColor&, const int&, double>> {
public:
  NamedColorTable() :
      KDTree::KDTree(std::ptr_fun(colorComponent)) {
  }

  void readFromCSV(const string& filename);
};

}

/* namespace kallaballa */
#endif /* NAMEDCOLORTABLE_HPP_ */
