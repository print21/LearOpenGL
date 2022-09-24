
#pragma once

#include <QWidget>

class SliderControlView;

class ModelControlWidget : public QWidget
{
    Q_OBJECT;
public:
    explicit ModelControlWidget(QWidget * parent = nullptr);
    ~ModelControlWidget();

protected:
    void initView();

protected:
    SliderControlView * _sliderPosX;
    SliderControlView * _sliderPosY;
    SliderControlView * _sliderPosZ;

    SliderControlView * _sliderRotP;// pitch
    SliderControlView * _sliderRotY;// yaw
    SliderControlView * _sliderRotR;// roll
};



