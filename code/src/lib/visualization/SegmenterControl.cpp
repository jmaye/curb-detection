#include "visualization/SegmenterControl.h"

#include "visualization/DEMControl.h"
#include "segmenter/ConnectivityBuilder.h"
#include "segmenter/GraphSegmenter.h"

#include "ui_SegmenterControl.h"

#include <map>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SegmenterControl::SegmenterControl(bool bShowSegmenter) :
  mpUi(new Ui_SegmenterControl()),
  mpDEM(0) {
  mpUi->setupUi(this);

  connect(&GLView::getInstance(), SIGNAL(render(GLView&)), this,
    SLOT(render(GLView&)));

  connect(&DEMControl::getInstance(), SIGNAL(demUpdated(DEM*)), this,
    SLOT(demUpdated(DEM*)));

  mu32K = mpUi->KSpinBox->value();

  setShowSegmenter(bShowSegmenter);
}

SegmenterControl::~SegmenterControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void SegmenterControl::setK(int i32K) {
  mpUi->KSpinBox->setValue(i32K);
}

void SegmenterControl::setShowSegmenter(bool bShowSegmenter) {
  mpUi->showSegmenterCheckBox->setChecked(bShowSegmenter);
  GLView::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void SegmenterControl::renderSegmenter() {
  glPushAttrib(GL_CURRENT_BIT);

  if (mLabelsMap.size() != 0) {

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    for (uint32_t i = 0; i < mpDEM->getCellsNbrX(); i++) {
      for (uint32_t j =  0; j < mpDEM->getCellsNbrY(); j++) {
        if ((*(const DEM*)mpDEM)(i, j).getInvalidFlag() == false) {
          Point2D cellCenter = (*(const DEM*)mpDEM)(i, j).getCellCenter();
          Point2D cellSize = (*(const DEM*)mpDEM)(i, j).getCellSize();
          double f64CellHeightMean = (*(const DEM*)mpDEM)(i, j).getHeightDist().
            getMean();

          std::map<uint32_t, Color>::const_iterator it =
            mColorMap.find(mLabelsMap[std::make_pair(i, j)]);
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

  glPopAttrib();
}

void SegmenterControl::render(GLView& view) {
  if (mpUi->showSegmenterCheckBox->isChecked())
    renderSegmenter();
}

void SegmenterControl::demUpdated(DEM* pDEM) {
  mpDEM = pDEM;
  ConnectivityBuilder::build(*pDEM, mEdgeSet);
  GraphSegmenter::segment(*pDEM, mEdgeSet, mLabelsMap, mSupportsMap, mu32K);
  mColorMap.clear();
  srand(time(NULL));
  for (uint32_t i = 0; i < mLabelsMap.size(); i++) {
    Color color;
    setColor(color);
    mColorMap[i] = color;
  }
  pDEM->setInitialLabels(mLabelsMap, mSupportsMap);
  mpUi->showSegmenterCheckBox->setEnabled(true);
  emit segmenterUpdated(mpDEM, &mLabelsMap, &mSupportsMap, &mEdgeSet);
  GLView::getInstance().update();
}

void SegmenterControl::KChanged(int i32Value) {
  mu32K = (uint32_t)i32Value;
  setK(i32Value);
  demUpdated(mpDEM);
}

void SegmenterControl::setColor(Color& color) const {
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

void SegmenterControl::showSegmenterToggled(bool bChecked) {
  setShowSegmenter(bChecked);
}
