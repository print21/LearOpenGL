
#include "SliderControlView.h"

#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

SliderControlView::SliderControlView(QWidget * parent /* = nullptr */)
{
    initView();
}

SliderControlView::~SliderControlView()
{

}

void SliderControlView::initView()
{
    QHBoxLayout * layout = new QHBoxLayout();
    _valueSlider = new QSlider(this);
    _titleLabel = new QLabel(this);
    _valueLabel = new QLabel(this);

    _valueSlider->setOrientation(Qt::Orientation::Horizontal);
    _valueSlider->setRange(-10, 10);
    _valueSlider->setValue(0);
    _valueLabel->setText(QString::number(0));

    layout->addWidget(_titleLabel);
    layout->addWidget(_valueSlider, 1);
    layout->addWidget(_valueLabel);

    this->setLayout(layout);
    layout->setMargin(0);

    connect(_valueSlider, &QSlider::valueChanged, this, &SliderControlView::slotSliderValueChanged);
}

void SliderControlView::slotSliderValueChanged(int v)
{
    _valueLabel->setText(QString::number(v));
    Q_EMIT signalValueChanged(v);
}

void SliderControlView::setSliderRange(int minV, int maxV)
{
    _valueSlider->setRange(minV, maxV);
}

void SliderControlView::setSingleStep(int inc)
{
    _valueSlider->setSingleStep(inc);
}

void SliderControlView::setSliderValue(int v)
{
    _valueSlider->setValue(v);
}

int SliderControlView::sliderValue()
{
    return _valueSlider->value();
}

void SliderControlView::setTitle(const QString & title)
{
    _titleLabel->setText(title);
}

