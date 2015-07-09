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

#include <sstream>
#include <fstream>
#include "NamedColorTable.hpp"

namespace kallaballa {

double colorComponent(const NamedColor& color, const int& k) {
  if(k == 0)
    return color.rgb & 0x0000ff;
  else if(k == 1)
    return (color.rgb & 0x00ff00) >> 8;
  else
    return (color.rgb & 0xff0000) >> 16;
}

std::vector<string> getNextLineAndSplitIntoTokens(std::istream& str) {
  std::vector<string> result;
  string line;
  if(!std::getline(str, line))
    return {};

  std::stringstream lineStream(line);
  string cell;

  while (std::getline(lineStream, cell, ',')) {
    result.push_back(cell);
  }
  return result;
}

void NamedColorTable::readFromCSV(const string& filename) {
  std::ifstream ifs(filename);
  std::vector<string> row;
  NamedColor ralColor;
  while ((row = getNextLineAndSplitIntoTokens(ifs)).size() == 2) {
    ralColor.name = row[0];
    ralColor.rgb = strtol(row[1].substr(1).c_str(), NULL, 16);
    this->insert(ralColor);
  }
}
} /* namespace kallaballa */

