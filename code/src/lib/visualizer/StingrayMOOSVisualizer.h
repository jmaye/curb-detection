#ifndef STINGRAYMOOSVISUALIZER_H
#define STINGRAYMOOSVISUALIZER_H

#include <MOOSLIB/MOOSApp.h>
#include <libfirecam/firecam.h>
#include <libfirecam/utils.h>

#include <highgui.h>

#include <string>

#include <stdint.h>

class StingrayMOOSVisualizer : public CMOOSApp {
  StingrayMOOSVisualizer(const StingrayMOOSVisualizer& other);
  StingrayMOOSVisualizer& operator = (const StingrayMOOSVisualizer& other);

public:
  StingrayMOOSVisualizer();
  ~StingrayMOOSVisualizer();

protected:
  bool OnNewMail(MOOSMSG_LIST& NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();

  std::string msVehicleName;
  IplImage* mpDispImage;
  IplImage* mpLeftImage;
  IplImage* mpRightImage;
  double mf64LastLeftImage;
  double mf64LastRightImage;
};

#endif // STINGRAYMOOSVISUALIZER_H
