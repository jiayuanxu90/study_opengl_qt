#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

class GLWidget;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    bool fs = false;
    GLWidget * glwidget;

protected:
    void keyPressEvent(QKeyEvent * e);
};

#endif // WINDOW_H
