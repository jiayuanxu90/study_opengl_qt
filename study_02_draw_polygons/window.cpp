#include "window.h"
#include <QMessageBox>

#include "glwidget.h"


Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    switch (QMessageBox::information(0,
        "Start Fullscreen?",
        "Would you like to run in fullscreen mode?",
        QMessageBox::Yes,
        QMessageBox::No | QMessageBox::Default)) {
    case QMessageBox::Yes:
        fs = true;
        break;
    case QMessageBox::No:
        fs = false;
        break;
    default:
        break;
    }

    glwidget = new GLWidget(0);
    setCentralWidget(glwidget);
    if (fs) {
        showFullScreen();
    }
}

Window::~Window()
{

}

void Window::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_F2:
        fs = !fs;
        if (fs)
            showFullScreen();
        else {
            this->showNormal();
        }
        glwidget->update();
        break;
    case Qt::Key_Escape:
        close();
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}


















