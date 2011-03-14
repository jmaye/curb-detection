#ifndef STINGRAYIMGMSG_H
#define STINGRAYIMGMSG_H

#include <moosMessages/genericMessage.h>
#include <libfirecam/frame.h>

#include <string>

class StingrayImgMsg : public GenericMessage {
  AIS_OBJECT
  AIS_PROPERTY(std::string id READ id)

  StingrayImgMsg(const StingrayImgMsg& other);
  StingrayImgMsg& operator = (const StingrayImgMsg& other);

public:
  StingrayImgMsg();
  ~StingrayImgMsg();

  bool writeBinary(std::ostream& os) const;
  bool readBinary(std::istream& is);

  FireCAMFrame mFrame;
  std::string id;

protected:

};

DEFINE_DEFAULT_BINARY_MOOS_MSG_TRAITS(StingrayImgMsg, "STINGRAY_IMAGE")

#endif // STINGRAYIMGMSG_H
