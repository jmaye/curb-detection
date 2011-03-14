#include "Window.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

using namespace std;

Window::Window() {
}

Window::Window(int argc, char **argv, int i32Width, int i32Height) :
  mi32Width(i32Width),
  mi32Height(i32Height),
  mf64Scale(1.0),
  mbShowAxes(false),
  mi32MouseButton(-1),
  mi32MouseState(-1),
  mi32StartX(0),
  mi32StartY(0) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(i32Width, i32Height);
  glutInitWindowPosition(mci32InitX, mci32InitY);
  mi32ID = glutCreateWindow(argv[0]);
  glutSetWindowData(this);
  glutDisplayFunc(displayCallback);
  glutReshapeFunc(reshapeCallback);
  glutKeyboardFunc(keyboardCallback);
  glutMouseFunc(mouseCallback);
  glutMotionFunc(motionCallback);
}

Window::Window(const Window& other) {
}

Window& Window::operator = (const Window& other) {
  return *this;
}

Window::~Window() {
  glDeleteLists(mPointCloudListIndex, 1);
  glDeleteLists(mDEMListIndex, 1);
}

void Window::show() const {
  glutSetWindow(mi32ID);
  glutMainLoop();
}

void Window::redraw() const {
  glutSetWindow(mi32ID);
  glutPostRedisplay();
}

void Window::setTranslation(double f64X, double f64Y, double f64Z) {
  mTranslation.mf64X = f64X;
  mTranslation.mf64Y = f64Y;
  mTranslation.mf64Z = f64Z;
  glutPostRedisplay();
}

void Window::setRotation(double f64Yaw, double f64Pitch, double f64Roll) {
  mRotation.mf64X = f64Pitch;
  mRotation.mf64Y = f64Yaw;
  mRotation.mf64Z = f64Roll;
  glutPostRedisplay();
}

void Window::setScale(double f64Scale) {
  mf64Scale = f64Scale;
  glutPostRedisplay();
}

void Window::setVisibility(bool bShowAxes) {
  mbShowAxes = bShowAxes;
  glutPostRedisplay();
}

void Window::drawScene() const {
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glLoadIdentity();
  glTranslatef(mTranslation.mf64X, mTranslation.mf64Y, mTranslation.mf64Z);
  glRotatef(mRotation.mf64Y, 0, 1, 0);
  glRotatef(mRotation.mf64X, 1, 0, 0);
  glRotatef(mRotation.mf64Z, 0, 0, 1);
  glScalef(mf64Scale, mf64Scale, mf64Scale);
  drawBackground(1.0f, 1.0f, 1.0f);
  if (mbShowAxes)
    drawAxes(3.0);
  glCallList(mPointCloudListIndex);
  glCallList(mDEMListIndex);
  glutSwapBuffers();
  glFlush();
}

void Window::drawBackground(float f32Red, float f32Green, float f32Blue)
  const {
  glClearColor(f32Red, f32Green, f32Blue, 0.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::drawAxes(float f32Length) const {
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(f32Length, 0, 0);
  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, f32Length, 0);
  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, f32Length);
  glEnd();
}

void Window::displayCallback() {
  Window *window = (Window*)glutGetWindowData();
  window->drawScene();
}

void Window::reshapeCallback(int i32Width, int i32Height) {
  Window *window = (Window*)glutGetWindowData();
  if (i32Height == 0)
    i32Height = 1;
  window->mi32Width = i32Width;
  window->mi32Height = i32Height;
  glViewport(0, 0, window->mi32Width, window->mi32Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat)window->mi32Width /
    (GLfloat)window->mi32Height, 0.1f, 200.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Window::motionCallback(int i32X, int i32Y) {
  Window *window = (Window*)glutGetWindowData();
  if (window->mi32MouseState == GLUT_DOWN) {
    if (window->mi32MouseButton == GLUT_LEFT_BUTTON) {
      window->mRotation.mf64Y += (i32X - window->mi32StartX);
      window->mRotation.mf64X += (i32Y - window->mi32StartY);
      window->mi32StartX = i32X;
      window->mi32StartY = i32Y;
      window->redraw();
    }
    else if (window->mi32MouseButton == GLUT_RIGHT_BUTTON) {
      window->mTranslation.mf64X += (i32X - window->mi32StartX) /
        window->mf64Scale;
      window->mTranslation.mf64Y -= (i32Y - window->mi32StartY) /
        window->mf64Scale;
      window->mi32StartX = i32X;
      window->mi32StartY = i32Y;
      window->redraw();
    }
  }
}

void Window::mouseCallback(int i32Button, int i32State, int i32X,
  int i32Y) {
  Window *window = (Window*)glutGetWindowData();
  float f32DScale = 1.1;
  if (i32Button == mci32GlutWheelUp) {
    window->mf64Scale *= f32DScale;
  }
  else if (i32Button == mci32GlutWheelDown) {
    window->mf64Scale /= f32DScale;
  }
  else if (i32State == GLUT_DOWN) {
    window->mi32StartX = i32X;
    window->mi32StartY = i32Y;
  }
  window->mi32MouseButton = i32Button;
  window->mi32MouseState = i32State;
  window->redraw();
}

void Window::addPointCloud(const PointCloud& pointCloud) {
  mPointVector = pointCloud.getPointVector();
}

void Window::addDEM(const DEM& dem) {
  mCellVector = dem.getCellVector();
}

void Window::keyboardCallback(unsigned char u8Key, int i32X, int i32Y) {
  Window* window = (Window*)glutGetWindowData();
  if (u8Key == 'q') {
    glutDestroyWindow(window->mi32ID);
    exit(0);
  }
}

void Window::createGlLists() {
  mPointCloudListIndex = glGenLists(1);
  glNewList(mPointCloudListIndex, GL_COMPILE);
  glPointSize(2.0);
  glBegin(GL_POINTS);
  for (uint32_t i = 0; i < mPointVector.size(); i++) {
    //glColor3f(0, 0, mPointCloudVector[i].mu8Intensity);
    glVertex3f(mPointVector[i].mf64X, mPointVector[i].mf64Y,
      mPointVector[i].mf64Z);
  }
  glEnd();
  glEndList();
  mDEMListIndex = glGenLists(1);
  glNewList(mDEMListIndex, GL_COMPILE);
  glPointSize(4.0);
  glBegin(GL_POINTS);
  for (uint32_t i = 0; i < mCellVector.size(); i++) {
    glColor3f(255, 0, 0);
    glVertex3f(mCellVector[i].mf64CenterX, mCellVector[i].mf64CenterY, mCellVector[i].mf64HeightMean);
  }
  glEnd();
  glEndList();
}
