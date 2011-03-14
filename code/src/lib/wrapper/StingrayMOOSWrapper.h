#ifndef STINGRAYMOOSWRAPPER_H
#define STINGRAYMOOSWRAPPER_H

#include <MOOSLIB/MOOSApp.h>
#include <libfirecam/firecam.h>
#include <libfirecam/utils.h>

#include <string>

#include <stdint.h>

class StingrayMOOSWrapper : public CMOOSApp {
  StingrayMOOSWrapper(const StingrayMOOSWrapper& other);
  StingrayMOOSWrapper& operator = (const StingrayMOOSWrapper& other);

public:
  StingrayMOOSWrapper();
  ~StingrayMOOSWrapper();

protected:
  bool OnNewMail(MOOSMSG_LIST& NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();

  std::string msVehicleName;
  FireCAMCamera mCamera;
  FireCAMConfiguration mConfiguration;
  std::string msGUID;
  uint64_t mu64GUID;
  uint32_t mu32Width;
  uint32_t mu32Height;
  std::string msColor;
  bool mbScalable;
  double mf64Framerate;
  std::string msCaptureMode;
  uint32_t mu32CaptureBuffer;
  uint32_t mu32CaptureSpeed;
  std::string msFilterTile;
  std::string msFilterMethod;
  bool mbFilterEnabled;
};

#endif // STINGRAYMOOSWRAPPER_H
