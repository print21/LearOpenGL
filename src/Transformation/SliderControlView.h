

#pragma once

#include <QWidget>

class QSlider;
class QLabel;

class SliderControlView : public QWidget
{
    Q_OBJECT;
public:
    explicit SliderControlView(QWidget * parent = nullptr);
    ~SliderControlView();

    void setSliderRange(int minV, int maxV);
    void setSingleStep(int inc);

    void setSliderValue(int v);
    int sliderValue();

    void setTitle(const QString & title);

Q_SIGNALS:
    void signalValueChanged(int v);

protected:
    void initView();

protected Q_SLOTS:
    void slotSliderValueChanged(int v);

protected:
    QSlider * _valueSlider;
    QLabel * _valueLabel;
    QLabel * _titleLabel;
};


