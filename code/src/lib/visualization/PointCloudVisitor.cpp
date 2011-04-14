#include "PointCloudVisitor.h"

#include "PointCloud.h"
#include "Point3D.h"

#include <iostream>
#include <fstream>

#include <stdint.h>

using namespace std;

PointCloudVisitor::PointCloudVisitor(double f64PointSize, GLbyte redColorByte,
  GLbyte greenColorByte, GLbyte blueColorByte)
  : mf64PointSize(f64PointSize),
    mRedColorByte(redColorByte),
    mGreenColorByte(greenColorByte),
    mBlueColorByte(blueColorByte) {
}

PointCloudVisitor::~PointCloudVisitor() {
}

void PointCloudVisitor::read(istream& stream) {
}

void PointCloudVisitor::write(ostream& stream) const {
}

void PointCloudVisitor::read(ifstream& stream) {
}

void PointCloudVisitor::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream, const PointCloudVisitor& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream, PointCloudVisitor& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream, const PointCloudVisitor& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream, PointCloudVisitor& obj) {
  obj.read(stream);
  return stream;
}

void PointCloudVisitor::visit(const PointCloud* pointCloud) {
  GLuint glListIdx = glGenLists(1);
  glNewList(glListIdx, GL_COMPILE);
  glPointSize(mf64PointSize);
  glBegin(GL_POINTS);
  glColor3f(mRedColorByte, mGreenColorByte, mBlueColorByte);
  for (uint32_t i = 0; i < pointCloud->getSize(); i++)
    (*pointCloud)[i].accept(*this);
  glEnd();
  glEndList();
  mGLListVector.push_back(glListIdx);
}

void PointCloudVisitor::visit(const Point3D* point3D) const {
  glVertex3f(point3D->mf64X, point3D->mf64Y, point3D->mf64Z);
}

void PointCloudVisitor::setPointSize(double f64PointSize) {
  mf64PointSize = f64PointSize;
}

double PointCloudVisitor::getPointSize() const {
  return mf64PointSize;
}

void PointCloudVisitor::setRedColorByte(GLbyte colorByte) {
  mRedColorByte = colorByte;
}

GLbyte PointCloudVisitor::getRedColorByte() const {
  return mRedColorByte;
}

void PointCloudVisitor::setGreenColorByte(GLbyte colorByte) {
  mGreenColorByte = colorByte;
}

GLbyte PointCloudVisitor::getGreenColorByte() const {
  return mGreenColorByte;
}

void PointCloudVisitor::setBlueColorByte(GLbyte colorByte) {
  mBlueColorByte = colorByte;
}

GLbyte PointCloudVisitor::getBlueColorByte() const {
  return mBlueColorByte;
}
