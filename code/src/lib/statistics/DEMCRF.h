#ifndef DEMCRF_H
#define DEMCRF_H

#include "DEM.h"
#include "Edge.h"

#include <graphtool/CRF.hh>

#include <iosfwd>
#include <set>
#include <map>
#include <vector>

#include <stdint.h>

class DEMCRF : public CRF {
  friend std::ostream& operator << (std::ostream& stream,
    const DEMCRF& obj);
  friend std::istream& operator >> (std::istream& stream,
    DEMCRF& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const DEMCRF& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    DEMCRF& obj);

  DEMCRF(const DEMCRF& other);
  DEMCRF& operator = (const DEMCRF& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  Vector FeatureFunction(uint32_t u32NodeId, int32_t i32Label) const;
  Vector FeatureFunction(uint32_t u32NodeId1, uint32_t u32NodeId2,
    int32_t i32Label1, int32_t i32Label2) const;

  std::map<uint32_t, uint32_t> mIdMap;
  std::vector<vector<double> > mCoeffsMatrix;
  std::vector<double> mVariancesVector;

public:
  DEMCRF(const DEM& dem, const std::multiset<Edge, EdgeCompare>& edgeSet,
    const vector<vector<double> >& coeffsMatrix,
    const vector<double>& variancesVector);
  ~DEMCRF();

  const std::map<uint32_t, uint32_t>& getIdMap() const;
  const std::vector<vector<double> >& getCoeffsMatrix() const;
  const std::vector<double>& getVariancesVector() const;
  void setIdMap(const std::map<uint32_t, uint32_t>& idMap);
  void setCoeffsMatrix(const std::vector<vector<double> >& coeffsMatrix);
  void setVariancesVector(const std::vector<double>& variancesVector);

protected:

};

#endif // DEMCRF_H
