#include "telemetry.h"


namespace telemetry{

  std::vector<std::vector<int> > TeleReader::readfile(int numberColumns=4)
  {
  	std::ifstream datafile(fname);
  	std::string line = "";
  	std::vector<std::vector<int> > dataOut;
  	auto lineCount = 0;

  	while(std::getline(datafile, line))
  	{
  		if (lineCount != 0)
  		{
  			std::vector<int> lineVector;
  			std::string s = "";
  			auto colCount = 0;
  			for (auto& c : line)
  			{
  				if (c==',')
  				{
  					lineVector.push_back(std::stoi(s));
  					s = "";
  					++colCount;
  				}
  				else
  				{
  					s += c;
  				}
  				if (colCount >= numberColumns){
  					//Only read the first n columns.
  					break;
  				}
  			}
  			dataOut.push_back(lineVector);
  		}
  		++lineCount;
  	}
  	return dataOut;
  }

  std::vector<std::vector<double> > teleStatistics(std::string filename, int window_size, int stride)
  {
  	//Read in data from file, stored as vec of vecs
  	TeleReader tr (filename);
  	auto d = tr.readfile();

  	std::deque<int> windowTime = {}; //Timestamps
  	std::deque<double> windowAccel = {}; //Total Acceleration data
  	int timePos = 0;
  	double accel = 0;
  	std::vector<std::vector<double> > statsTable; //min, max, mean

  	for (auto v : d)
  	{
  		if (v[0] > timePos + window_size)
  		{
  			std::vector<double> windowStats;

  			windowStats.push_back(*std::min_element(windowAccel.begin(), windowAccel.end()));
  			windowStats.push_back(*std::max_element(windowAccel.begin(), windowAccel.end()));
  			windowStats.push_back(std::accumulate(windowAccel.begin(), windowAccel.end(), (double) 0)/windowAccel.size());
  			statsTable.push_back(windowStats);

  			timePos += stride;
  			while (windowTime.front() < timePos)
  			{
  				windowTime.pop_front();
  				windowAccel.pop_front();
  			}
  		}
  		//Find total acceleration
  		for (int i=1; i<4; ++i)
  		{
  			accel += v[i]*v[i];
  		}
  		accel = sqrt(accel);

  		//Add to deque
  		windowTime.push_back(v[0]);
  		windowAccel.push_back(accel);

  	}
  	return statsTable;
  }
}
