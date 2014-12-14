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
    GLfloat xRot, yRot, zRot;
    GLuint texture[1];

    void loadGLTextures();
};

#endif // GLWIDGET_H
