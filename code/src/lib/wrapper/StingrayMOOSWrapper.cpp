#include "StingrayMOOSWrapper.h"

#include "StingrayImgMsg.h"

#include <sstream>

using namespace std;

StingrayMOOSWrapper::StingrayMOOSWrapper() {
}

StingrayMOOSWrapper::StingrayMOOSWrapper(const StingrayMOOSWrapper& other) {
}

StingrayMOOSWrapper& StingrayMOOSWrapper::operator =
  (const StingrayMOOSWrapper& other) {
  return *this;
}

StingrayMOOSWrapper::~StingrayMOOSWrapper() {
  mCamera.disconnect();
}

bool StingrayMOOSWrapper::OnNewMail(MOOSMSG_LIST& NewMail) {
  return true;
}

bool StingrayMOOSWrapper::Iterate() {
  StingrayImgMsg imgMsg;
  mCamera.capture(imgMsg.mFrame);
  imgMsg.id = msVehicleName;
  size_t binarySize;
  m_Comms.Notify(MsgTraits<StingrayImgMsg>::name(), imgMsg.toBinary(binarySize),
    binarySize, imgMsg.toString(), MOOSTime());
  return true;
}

bool StingrayMOOSWrapper::OnConnectToServer() {
  return true;
}

bool StingrayMOOSWrapper::OnStartUp() {
  if (!m_MissionReader.GetConfigurationParam("VehicleName", msVehicleName))
    return MOOSFail("Configuration Failure - no \"VehicleName\" specified in mission file");
  if (!m_MissionReader.GetConfigurationParam("GUID", msGUID))
    return MOOSFail("Configuration Failure - no \"GUID\" specified in mission file");
  if (!m_MissionReader.GetValue("Width", mu32Width))
    return MOOSFail("Configuration Failure - no \"Width\" specified in mission file");
  if (!m_MissionReader.GetValue("Height", mu32Height))
    return MOOSFail("Configuration Failure - no \"Height\" specified in mission file");
  if (!m_MissionReader.GetConfigurationParam("Color", msColor))
    return MOOSFail("Configuration Failure - no \"Color\" specified in mission file");
  if (!m_MissionReader.GetValue("Scalable", mbScalable))
    return MOOSFail("Configuration Failure - no \"Scalable\" specified in mission file");
  if (!m_MissionReader.GetValue("Framerate", mf64Framerate))
    return MOOSFail("Configuration Failure - no \"Framerate\" specified in mission file");
  if (!m_MissionReader.GetConfigurationParam("CaptureMode", msCaptureMode))
    return MOOSFail("Configuration Failure - no \"CaptureMode\" specified in mission file");
  if (!m_MissionReader.GetValue("CaptureBuffer", mu32CaptureBuffer))
    return MOOSFail("Configuration Failure - no \"CaptureBuffer\" specified in mission file");
  if (!m_MissionReader.GetValue("CaptureSpeed", mu32CaptureSpeed))
    return MOOSFail("Configuration Failure - no \"CaptureSpeed\" specified in mission file");
  if (!m_MissionReader.GetConfigurationParam("FilterTile", msFilterTile))
    return MOOSFail("Configuration Failure - no \"FilterTile\" specified in mission file");
  if (!m_MissionReader.GetConfigurationParam("FilterMethod", msFilterMethod))
    return MOOSFail("Configuration Failure - no \"FilterMethod\" specified in mission file");
  if (!m_MissionReader.GetValue("FilterEnabled", mbFilterEnabled))
    return MOOSFail("Configuration Failure - no \"FilterEnabled\" specified in mission file");

  stringstream guidStream(msGUID);
  guidStream >> hex >> mu64GUID;

  mCamera = FireCAM::getInstance().getCamera(mu64GUID);
  mConfiguration = mCamera.getConfiguration();
  FireCAMColor::Coding colorMode = FireCAMUtils::convert(msColor,
    FireCAMColor::codingStrings);
  FireCAMVideoMode videoMode(mu32Width, mu32Height, colorMode, mbScalable);
  mConfiguration.setVideoMode(videoMode);
  mConfiguration.setFramerate(mf64Framerate);
  FireCAMCapture::Mode captureMode = FireCAMUtils::convert(msCaptureMode,
    FireCAMCapture::modeStrings);
  FireCAMCapture capture(mu32CaptureBuffer, captureMode, mu32CaptureSpeed);
  mConfiguration.setCapture(capture);
  FireCAMColorFilter::Tile filterTile = FireCAMUtils::convert(msFilterTile,
    FireCAMColorFilter::tileStrings);
  FireCAMColorFilter::Method filterMethod =
    FireCAMUtils::convert(msFilterMethod, FireCAMColorFilter::methodStrings);
  FireCAMColorFilter colorFilter(mbFilterEnabled, filterTile, filterMethod);
  mConfiguration.setColorFilter(colorFilter);
  for (std::set<FireCAMFeature>::const_iterator it =
    mCamera.getFeatures().begin(); it != mCamera.getFeatures().end(); ++it) {
    FireCAMFeature feature = *it;
    string sFeatureName = feature.getName();
    string sFeatureEnabledVar = sFeatureName + "Enabled";
    bool bFeatureEnabled;
    if (!m_MissionReader.GetValue(sFeatureEnabledVar, bFeatureEnabled))
      return MOOSFail("Configuration Failure - no \"%s\" specified in mission file", sFeatureEnabledVar.c_str());
    feature.setEnabled(bFeatureEnabled);
    string sFeatureModeVar = sFeatureName + "Mode";
    string sFeatureMode;
    if (!m_MissionReader.GetConfigurationParam(sFeatureModeVar, sFeatureMode))
      return MOOSFail("Configuration Failure - no \"%s\" specified in mission file", sFeatureModeVar.c_str());
    feature.setMode(FireCAMUtils::convert(sFeatureMode,
      FireCAMFeature::modeStrings));
    string sFeatureValuesVar = sFeatureName + "Values";
    string sFeatureValues;
    if (!m_MissionReader.GetConfigurationParam(sFeatureValuesVar,
      sFeatureValues))
      return MOOSFail("Configuration Failure - no \"%s\" specified in mission file", sFeatureValuesVar.c_str());
    vector<size_t> valuesVector;
    FireCAMUtils::convert("1", valuesVector);
    feature.setValues(valuesVector);
    mConfiguration.setFeature(feature);
  }
  mCamera.setConfiguration(mConfiguration);
  mCamera.connect();
  cout << "Camera connected!" << endl;
  return true;
}
