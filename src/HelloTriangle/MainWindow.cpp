
#include "MainWindow.h"
#include "View3dGL.h"

MainWindow::MainWindow(QWidget * parent /* = nullptr */)
    :QMainWindow(parent), _view3d(nullptr)
{
    initView();

    this->resize(1024, 768);
}

MainWindow::~MainWindow()
{

}

void MainWindow::initView()
{
    _view3d = new View3dGL(this);
    this->setCentralWidget(_view3d);
}

