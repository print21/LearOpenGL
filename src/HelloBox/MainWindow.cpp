
#include "MainWindow.h"
#include "View3dGL.h"
#include "ModelControlWidget.h"
#include "ViewControlWidget.h"
#include "TransformationInfoWidget.h"

#include <QDockWidget>
#include <QHBoxLayout>

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

    _modelControl = new ModelControlWidget(this);
    _viewControl = new ViewControlWidget(this);
    _infoView = new TransformationInfoWidget(this);

    connect(_modelControl, &ModelControlWidget::signalModelValueChanged, _view3d, &View3dGL::slotModelValueChanged);
    //connect(_modelControl, &ModelControlWidget::signalModelValueChanged, _view3d, View3dGL::slotModelValueChanged);

    QDockWidget * controlDock = new QDockWidget(this);
    controlDock->setFeatures(QDockWidget::DockWidgetMovable);
    controlDock->setAllowedAreas(Qt::BottomDockWidgetArea);

    QHBoxLayout * dockLayout = new QHBoxLayout();
    dockLayout->addWidget(_modelControl);
    dockLayout->addWidget(_viewControl);
    dockLayout->addWidget(_infoView);

    QWidget * dockWidget = new QWidget(controlDock);
    dockWidget->setLayout(dockLayout);
    controlDock->setWidget(dockWidget);

    this->addDockWidget(Qt::BottomDockWidgetArea, controlDock);
}

