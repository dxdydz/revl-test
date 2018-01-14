#include <iostream>
#include "telemetry.h"
#include <string>

/*Command line tool to read in telemtry CSV file and output telemetry statistics to std i/o*/

int main(int argc, char *argv[])
{
  //Check for invalid inputs or help command
  for (int i=0; i<argc; ++i)
  {
    std::string opt = argv[i];
    if (opt == "-h" || opt == "--help")
    {
      std::cout<<"Usage: "<<argv[0]<<" csvfile window_size stride\n";
      return 0;
    }
  }
  if (argc != 4)
  {
    std::cout<<"Insufficient arguments.";
    return 0;
  }

  std::string csvname = argv[1];
  int windowSize = std::stoi(argv[2]);
  int stride = std::stoi(argv[3]);

  auto d = telemetry::teleStatistics(csvname, windowSize, stride);
  for (auto v: d)
	{
		for (auto thing: v)
		{
			std::cout<<thing<<"\t";
		}
		std::cout<<"\n";
	}
}
