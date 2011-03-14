#include "StingrayMOOSVisualizer.h"

#include <iostream>

using namespace std;

int main(int argc ,char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <mission.moos>" << endl;
    return -1;
  }

  const char* sMOOSName = "EUROPAStingray";
  const char* sMissionFile = argv[1];

  StingrayMOOSVisualizer stingrayMOOSVisualizer;

  stingrayMOOSVisualizer.Run(sMOOSName, sMissionFile);

  return 0;
}
