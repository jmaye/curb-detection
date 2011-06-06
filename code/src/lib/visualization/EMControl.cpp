#include "visualization/EMControl.h"

#include "visualization/SegmenterControl.h"
#include "statistics/EM.h"
#include "statistics/LinearRegressor.h"

#include "ui_EMControl.h"

#include <map>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

EMControl::EMControl(bool bShowEM) :
  mpUi(new Ui_EMControl()),
  mpDEM(0),
  mpLabelsMap(0),
  mpSupportsMap(0),
  mu32EMIterations(15),
  mf64EMTolerance(1e-6),
  mu32BPIterations(10000),
  mf64BPTolerance(1e-9) {
  mpUi->setupUi(this);

  connect(&GLView::getInstance(), SIGNAL(render(GLView&)), this,
    SLOT(render(GLView&)));

  connect(&SegmenterControl::getInstance(), SIGNAL(segmenterUpdated(DEM*,
    const std::map<std::pair<uint32_t, uint32_t>, uint32_t>*,
    const std::map<uint32_t, uint32_t>*,
    const std::multiset<Edge, EdgeCompare>*)), this,
    SLOT(segmenterUpdated(DEM*,
    const std::map<std::pair<uint32_t, uint32_t>, uint32_t>*,
    const std::map<uint32_t, uint32_t>*,
    const std::multiset<Edge, EdgeCompare>*)));

  setShowEM(bShowEM);
  setEMIterations(mu32EMIterations);
  setEMTolerance(mf64EMTolerance);
  setBPIterations(mu32BPIterations);
  setBPTolerance(mf64BPTolerance);
}

EMControl::~EMControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void EMControl::setShowEM(bool bShowEM) {
  mpUi->showEMCheckBox->setChecked(bShowEM);
  GLView::getInstance().update();
}

void EMControl::setEMIterations(uint32_t u32Iterations) {
  mpUi->EMIterationsSpinBox->setValue(u32Iterations);
}

void EMControl::setEMTolerance(double f64Tol) {
  mpUi->EMToleranceSpinBox->setValue(f64Tol);
}

void EMControl::setBPIterations(uint32_t u32Iterations) {
  mpUi->BPIterationsSpinBox->setValue(u32Iterations);
}

void EMControl::setBPTolerance(double f64Tol) {
  mpUi->BPToleranceSpinBox->setValue(f64Tol);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void EMControl::renderEM() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  for (uint32_t i = 0; i < mpDEM->getCellsNbrX(); i++) {
    for (uint32_t j =  0; j < mpDEM->getCellsNbrY(); j++) {
      if ((*(const DEM*)mpDEM)(i, j).getInvalidFlag() == false) {
        Point2D cellCenter = (*(const DEM*)mpDEM)(i, j).getCellCenter();
        Point2D cellSize = (*(const DEM*)mpDEM)(i, j).getCellSize();
        double f64CellHeightMean = (*(const DEM*)mpDEM)(i, j).getHeightDist().
          getMean();
        uint32_t u32LabelIdx = (*(const DEM*)mpDEM)(i, j).getMAPLabelsDist();
        std::map<uint32_t, Color>::const_iterator it =
          mColorMap.find(u32LabelIdx);
        Color color = (*it).second;

        glBegin(GL_POLYGON);
        glColor3f(color.mRedColorByte, color.mGreenColorByte,
          color.mBlueColorByte);
        glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
          cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);
        glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
          cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);
        glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
          cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);
        glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
          cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);
        glEnd();
      }
    }
  }
}

void EMControl::render(GLView& view) {
  if (mpUi->showEMCheckBox->isChecked())
    renderEM();
}

void EMControl::setColor(Color& color) const {
  double f64H = ((double)rand() / (double)RAND_MAX) * 360.0;
  double f64S = 1.0;
  double f64V = 1.0;
  f64H /= 60.0;
  int i32I = floor(f64H);
  double f64F =  f64H - i32I;
  double f64P = f64V * (1 - f64S);
  double f64Q = f64V * (1 - f64S * f64F);
  double f64T = f64V * (1 - f64S * (1 - f64F));

  switch (i32I) {
    case 0:
      color.mRedColorByte = f64V ;
      color.mGreenColorByte = f64T;
      color.mBlueColorByte = f64P;
      break;
    case 1:
      color.mRedColorByte = f64Q;
      color.mGreenColorByte = f64V;
      color.mBlueColorByte = f64P;
      break;
    case 2:
      color.mRedColorByte = f64P;
      color.mGreenColorByte = f64V;
      color.mBlueColorByte = f64T;
      break;
    case 3:
      color.mRedColorByte = f64P;
      color.mGreenColorByte = f64Q;
      color.mBlueColorByte = f64V;
      break;
    case 4:
      color.mRedColorByte = f64T;
      color.mGreenColorByte = f64P;
      color.mBlueColorByte = f64V;
      break;
    default:
      color.mRedColorByte = f64V;
      color.mGreenColorByte = f64P;
      color.mBlueColorByte = f64Q;
      break;
  }
}

void EMControl::showEMToggled(bool bChecked) {
  setShowEM(bChecked);
}

void EMControl::EMIterationsChanged(int i32Iterations) {
  mu32EMIterations = i32Iterations;
  setEMIterations(i32Iterations);
}

void EMControl::EMToleranceChanged(double f64Tol) {
  mf64EMTolerance = f64Tol;
  setEMTolerance(f64Tol);
}

void EMControl::BPIterationsChanged(int i32Iterations) {
  mu32BPIterations = i32Iterations;
  setBPIterations(i32Iterations);
}

void EMControl::BPToleranceChanged(double f64Tol) {
  mf64BPTolerance = f64Tol;
  setBPTolerance(f64Tol);
}

void EMControl::runEMPushed() {
  std::vector<std::vector<double> > coeffsMatrix;
  std::vector<double> variancesVector;
  std::vector<double> weightsVector;
  LinearRegressor::estimate(*mpDEM, coeffsMatrix, variancesVector,
    weightsVector);
  EM::run(*mpDEM, *mpEdgeSet, coeffsMatrix, variancesVector, weightsVector,
    mu32EMIterations, mf64EMTolerance, mu32BPIterations, mf64BPTolerance);
  mColorMap.clear();
  srand(time(NULL));
  for (uint32_t i = 0; i < mpDEM->getLabelsNbr(); i++) {
    Color color;
    setColor(color);
    mColorMap[i] = color;
  }
  mpUi->showEMCheckBox->setEnabled(true);
  GLView::getInstance().update();
}

void EMControl::segmenterUpdated(DEM* pDEM,
  const std::map<std::pair<uint32_t, uint32_t>, uint32_t>* pLabelsMap,
  const std::map<uint32_t, uint32_t>* pSupportsMap,
  const std::multiset<Edge, EdgeCompare>* pEdgeSet) {
  mpDEM = pDEM;
  mpLabelsMap = pLabelsMap;
  mpSupportsMap = pSupportsMap;
  mpEdgeSet = pEdgeSet;
  mpUi->showEMCheckBox->setChecked(false);
  mpUi->showEMCheckBox->setEnabled(false);
  mpUi->runEMPushButton->setEnabled(true);
}
