#include "StingrayMOOSWrapper.h"

#include <iostream>

using namespace std;

int main(int argc ,char** argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " -l|r <mission.moos>" << endl;
    return -1;
  }

  const char* sMOOSNameLeft = "EUROPAStingrayLeft";
  const char* sMOOSNameRight = "EUROPAStingrayRight";
  const char* sMissionFile = argv[2];

  StingrayMOOSWrapper stingrayMOOS;

  char c = getopt(argc, argv, "lr");
  if (c == 'l')
    stingrayMOOS.Run(sMOOSNameLeft, sMissionFile);
  else if (c == 'r')
    stingrayMOOS.Run(sMOOSNameRight, sMissionFile);
  else {
    cerr << "Usage: " << argv[0] << " l|r <mission.moos>" << endl;
    return -1;
  }

  return 0;
}
