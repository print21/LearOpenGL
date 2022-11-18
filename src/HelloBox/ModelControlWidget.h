
#pragma once

#include <QWidget>

class SliderControlView;

class ModelControlWidget : public QWidget
{
    Q_OBJECT;
public:
    explicit ModelControlWidget(QWidget * parent = nullptr);
    ~ModelControlWidget();

Q_SIGNALS:
    void signalModelValueChanged(int posx, int posy, int posz, int rotp, int roty, int rotr);

protected:
    void initView();

protected Q_SLOTS:
    void slotValuePosXChanged(int v);
    void slotValuePosYChanged(int v);
    void slotValuePosZChanged(int v);
    void slotValueRotPChanged(int v);
    void slotValueRotYChanged(int v);
    void slotValueRotRChanged(int v);

protected:
    SliderControlView * _sliderPosX;
    SliderControlView * _sliderPosY;
    SliderControlView * _sliderPosZ;

    SliderControlView * _sliderRotP;// pitch
    SliderControlView * _sliderRotY;// yaw
    SliderControlView * _sliderRotR;// roll
};



