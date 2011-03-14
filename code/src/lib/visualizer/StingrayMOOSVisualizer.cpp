#include "StingrayMOOSVisualizer.h"

#include "StingrayImgMsg.h"

using namespace std;

StingrayMOOSVisualizer::StingrayMOOSVisualizer() : mpDispImage(0),
                                                   mpLeftImage(0),
                                                   mpRightImage(0) {
}

StingrayMOOSVisualizer::
  StingrayMOOSVisualizer(const StingrayMOOSVisualizer& other) {
}

StingrayMOOSVisualizer& StingrayMOOSVisualizer::operator =
  (const StingrayMOOSVisualizer& other) {
  return *this;
}

StingrayMOOSVisualizer::~StingrayMOOSVisualizer() {
  if (mpDispImage != 0)
    cvReleaseImage(&mpDispImage);
  cvDestroyWindow("Stingray Visualizer");
}

bool StingrayMOOSVisualizer::OnNewMail(MOOSMSG_LIST& NewMail) {
  CMOOSMsg Msg;
  if (m_Comms.PeekMail(NewMail, MsgTraits<StingrayImgMsg>::name(), Msg,
    true, true) == true) {
    if (!Msg.IsSkewed(MOOSTime())) {
      int binarySize = Msg.m_sVal.size();
      const unsigned char* binaryData = (const unsigned char*)Msg.m_sVal.data();
      StingrayImgMsg sMsg;
      sMsg.fromBinary(binaryData, binarySize);
      sMsg.fromString(Msg.GetString());
    }
  }
  return true;
}

bool StingrayMOOSVisualizer::Iterate() {
  cvShowImage("Stingray Visualizer", mpDispImage);
  cvWaitKey(5);
  return true;
}

bool StingrayMOOSVisualizer::OnConnectToServer() {
  m_Comms.Register(MsgTraits<StingrayImgMsg>::name(), 0);
  return true;
}

bool StingrayMOOSVisualizer::OnStartUp() {
  if (!m_MissionReader.GetConfigurationParam("VehicleName", msVehicleName))
    return MOOSFail("Configuration Failure - no \"VehicleName\" specified in mission file");

  cvNamedWindow("Stingray Visualizer");
  m_Comms.Register(MsgTraits<StingrayImgMsg>::name(), 0);
  return true;
}
