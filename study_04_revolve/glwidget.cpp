#include "glwidget.h"
#include <QtOpenGL>
#include <QtWidgets>
#include <gl/GLU.h>

#include <iostream>
using namespace std;

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    rTri = 0.0f;
    rQuad = 0.0f;
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glClearDepth(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-1.5, 0.0, -6.0);
    glRotatef(rTri, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();

    glLoadIdentity();

    glTranslatef(1.5, 0.0, -6.0);
    glRotatef(rQuad, 1.0, 1.0, 0.0);
    glColor3f(0.5, 0.5, 1.0);

    glBegin(GL_QUADS);
    glVertex3f(-1.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glEnd();

    rTri += 0.5f;
    rQuad -= 0.2f;
}

void GLWidget::resizeGL(int w, int h)
{
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}











