#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget * parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    GLfloat rTri;
    GLfloat rQuad;
};

#endif // GLWIDGET_H
