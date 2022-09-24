

#include "ModelControlWidget.h"
#include "SliderControlView.h"

#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>

ModelControlWidget::ModelControlWidget(QWidget * parent /* = nullptr */)
    :QWidget(parent)
{
    initView();
}

ModelControlWidget::~ModelControlWidget()
{

}

void ModelControlWidget::initView()
{
    QGroupBox * group = new QGroupBox(this);
    group->setTitle(tr("Model"));

    QGridLayout * groupLayout = new QGridLayout();
    groupLayout->setMargin(1);
    {
        QLabel * label = new QLabel(this);
        label->setText("Position");

        _sliderPosX = new SliderControlView(this);
        _sliderPosY = new SliderControlView(this);
        _sliderPosZ = new SliderControlView(this);

        _sliderPosX->setTitle(tr("X    "));
        _sliderPosY->setTitle(tr("Y    "));
        _sliderPosZ->setTitle(tr("Z    "));

        QVBoxLayout * sliderLayout = new QVBoxLayout();
        sliderLayout->addWidget(_sliderPosX);
        sliderLayout->addWidget(_sliderPosY);
        sliderLayout->addWidget(_sliderPosZ);

        groupLayout->addWidget(label, 0, 0);
        groupLayout->addLayout(sliderLayout, 0, 1);
    }

    {
        QLabel * label = new QLabel(this);
        label->setText("Rotation");

        _sliderRotP = new SliderControlView(this);
        _sliderRotY = new SliderControlView(this);
        _sliderRotR = new SliderControlView(this);

        _sliderRotP->setTitle(tr("Pitch"));
        _sliderRotY->setTitle(tr("Yaw  "));
        _sliderRotR->setTitle(tr("Roll "));

        _sliderRotP->setSliderRange(-180, 180);
        _sliderRotY->setSliderRange(-180, 180);
        _sliderRotR->setSliderRange(-180, 180);

        QVBoxLayout * sliderLayout = new QVBoxLayout();
        sliderLayout->addWidget(_sliderRotP);
        sliderLayout->addWidget(_sliderRotY);
        sliderLayout->addWidget(_sliderRotR);

        groupLayout->addWidget(label, 1, 0);
        groupLayout->addLayout(sliderLayout, 1, 1);
    }

    group->setLayout(groupLayout);
    QVBoxLayout * layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(group);
    this->setLayout(layout);
}

