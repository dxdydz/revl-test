#ifndef __TELEMETRY_H_INCLUDED__
#define __TELEMETRY_H_INCLUDED__


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <deque>
#include <algorithm>
#include <math.h>


namespace telemetry
{

  //Class for reading in data from telemetry CSV
  class TeleReader
  {
  	std::string fname;
  public:
  	TeleReader(std::string filename) : fname(filename)
  	{ }
  	std::vector<std::vector<int> > readfile(int numberColumns);
  };

  //Function for calculating statistics; Probably should be put in own class?
  std::vector<std::vector<double> > teleStatistics(std::string filename, int window_size, int stride);

}
#endif
