#include <iostream>

using namespace std;

int main(int argc ,char** argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " -l|r <mission.moos>" << endl;
    return -1;
  }

  return 0;
}
