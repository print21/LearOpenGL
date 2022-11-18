
#pragma once

#include <QWidget>

class SliderControlView;

class ViewControlWidget : public QWidget
{
    Q_OBJECT;
public:
    explicit ViewControlWidget(QWidget * parent = nullptr);
    ~ViewControlWidget();

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

