#include "glwidget.h"
#include <QtOpenGL>
#include <QtWidgets>
#include <gl/GLU.h>
#include <QImage>

#include <iostream>
using namespace std;



GLfloat lightAmbient[4] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPosition[4] = {0.0f, 0.0f, 2.0f, 1.0f};

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    xRot = 0.0f;
    yRot = 0.0f;
    zRot = 0.0f;

    zoom = -5.0f;
    xSpeed = 0.0f;
    ySpeed = 0.0f;

    filter = 0;

    light = false;

}

GLWidget::~GLWidget()
{

}


void GLWidget::loadGLTextures()
{
    QImage tex, buf;
    if (!buf.load(":/qt.png")) {
        qWarning("Could not read image file, using single-color instead.");
        QImage dummy(128, 128, QImage::Format::Format_RGB32);
        dummy.fill(QColor(Qt::green));
        buf = dummy;
    }
    tex = QGLWidget::convertToGLFormat(buf);
    glGenTextures(3, &texture[0]);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tex.width(), tex.height(),
                GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());


}

void GLWidget::initializeGL()
{
    loadGLTextures();
    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

    glEnable(GL_LIGHT1);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, zoom);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);

    glBindTexture(GL_TEXTURE_2D, texture[filter]);

    glBegin(GL_QUADS);
    // front
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);

    // back
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, -1.0);

    // top
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);

    // bottom
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);

    // right
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);


    // left
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);



    glEnd();

    xRot += xSpeed;
    yRot += ySpeed;
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

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_L:
        light =! light;
        if (!light)
            glDisable(GL_LIGHTING);
        else
            glEnable(GL_LIGHTING);
        updateGL();
        break;
    case Qt::Key_F:
        filter += 1;
        if (filter > 2)
            filter = 0;
        updateGL();
        break;
    case Qt::Key_Down:
        zoom += 0.2f;
        updateGL();
        break;
    case Qt::Key_Up:
        zoom -= 0.2f;
        updateGL();
        break;
    case Qt::Key_W:
        xSpeed += 0.01f;
        updateGL();
        break;
    case Qt::Key_S:
        xSpeed -= 0.01f;
        updateGL();
        break;
    case Qt::Key_D:
        ySpeed += 0.01f;
        updateGL();
        break;
    case Qt::Key_A:
        ySpeed -= 0.01f;
        updateGL();
        break;
    }
}
