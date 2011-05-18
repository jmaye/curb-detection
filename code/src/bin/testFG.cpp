#include <dai/bp.h>
#include <dai/factorgraph.h>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc ,char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << "<fgFile>" << endl;
    return -1;
  }

  dai::FactorGraph factorGraph;
  factorGraph.ReadFromFile(argv[1]);

  size_t maxiter = 10000;
  dai::Real tol = 1e-9;
  size_t verb = 0;
  dai::PropertySet opts;
  opts.set("maxiter", maxiter);
  opts.set("tol", tol);
  opts.set("verbose", verb);
  opts.set("updates", string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", string("MAXPROD"));
  dai::BP bp = dai::BP(factorGraph, opts);
  bp.init();
  bp.run();
  std::vector<size_t> MAPStateVector = bp.findMaximum();
  double f64LogScore = factorGraph.logScore(MAPStateVector);

  return 0;
}
