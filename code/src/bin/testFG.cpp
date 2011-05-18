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
  size_t verb = 10;
  dai::PropertySet opts;
  opts.set("maxiter", maxiter);
  opts.set("tol", tol);
  opts.set("verbose", verb);
  opts.set("updates", string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", string("MAXPROD"));
  dai::BP mp = dai::BP(factorGraph, opts);
  opts.set("inference", string("SUMPROD"));
  dai::BP sp = dai::BP(factorGraph, opts);
  mp.init();
  mp.run();
  sp.init();
  sp.run();
  std::vector<size_t> MAPStateVector = mp.findMaximum();
  double f64LogScore = factorGraph.logScore(MAPStateVector);
  cout << "Log-Score (MP):" << f64LogScore << endl;
  cout << "Partition sum (MP): " << mp.logZ() << endl;
  cout << "Partition sum (SP): " << sp.logZ() << endl;
  for( size_t i = 0; i < factorGraph.nrVars(); i++ ) {
    dai::Factor factorMP = mp.beliefV(i);
    dai::Factor factorSP = sp.beliefV(i);
    vector<double> distVectorMP = factorMP.p().p();
    vector<double> distVectorSP = factorSP.p().p();
    double f64LargestValue = -numeric_limits<double>::max();
    uint32_t u32LargestIdxMP = 0;
    uint32_t u32LargestIdxSP = 0;
    for (uint32_t j = 0; j < distVectorSP.size(); j++) {
      if (distVectorSP[j] > f64LargestValue) {
        f64LargestValue = distVectorSP[j];
        u32LargestIdxSP = j;
      }
    }
    f64LargestValue = -numeric_limits<double>::max();
    for (uint32_t j = 0; j < distVectorMP.size(); j++) {
      if (distVectorMP[j] > f64LargestValue) {
        f64LargestValue = distVectorMP[j];
        u32LargestIdxMP = j;
      }
    }
  }
  return 0;
}
