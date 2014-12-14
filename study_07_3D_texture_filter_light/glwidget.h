#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QWidget>
#include <QKeyEvent>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget * parent = 0);
    ~GLWidget();

    void keyPressEvent(QKeyEvent * e);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


private:
    GLfloat xRot, yRot, zRot;
    GLfloat zoom;
    GLfloat xSpeed, ySpeed;
    GLuint texture[3];
    GLuint filter;

    bool light;



    void loadGLTextures();
};

#endif // GLWIDGET_H
