#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QWidget>

class GLWidget;

class Window : public QMainWindow
{
    Q_OBJECT

private:
    bool fs = false;
    GLWidget * glwidget;

public:
    Window(QWidget *parent = 0);
    ~Window();

protected:
    void keyPressEvent(QKeyEvent * e);

};

#endif // WINDOW_H
