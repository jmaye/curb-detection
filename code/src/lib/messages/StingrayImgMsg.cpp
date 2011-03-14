#include "StingrayImgMsg.h"

#include "aisStingrayImgMsg.h"

using namespace std;

StingrayImgMsg::StingrayImgMsg() {
}

StingrayImgMsg::StingrayImgMsg(const StingrayImgMsg& other) {
}

StingrayImgMsg& StingrayImgMsg::operator = (const StingrayImgMsg& other) {
  return *this;
}

StingrayImgMsg::~StingrayImgMsg() {
}

bool StingrayImgMsg::writeBinary(std::ostream& os) const {
  mFrame.save(os);
  return true;
}

bool StingrayImgMsg::readBinary(std::istream& is) {
  mFrame.load(is);
  return true;
}
