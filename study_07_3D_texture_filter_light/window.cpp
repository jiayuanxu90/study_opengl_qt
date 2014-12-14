#include "window.h"
#include <QMessageBox>
#include <QTimer>

#include "glwidget.h"


Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    QTimer * timer = new QTimer(this);
    timer->setInterval(10);
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

    QObject::connect(timer, SIGNAL(timeout()), glwidget, SLOT(updateGL()));
    timer->start();
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
        glwidget->keyPressEvent(e);
        break;
    }
}


















