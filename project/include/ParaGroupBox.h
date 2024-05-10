#ifndef PARAGROUPBOX_H
#define PARAGROUPBOX_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

class ParaGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit ParaGroupBox(QWidget *parent = nullptr);
    ~ParaGroupBox();

private:
    QVBoxLayout *layout;
    QComboBox *samplingRateBox;
    QSpinBox *prfSpinBox;
    QSlider *gainSlider;
    QDoubleSpinBox *bandwidthSpinBox;
    QDoubleSpinBox *timeWindowSpinBox;
    QComboBox *filterSettingsBox;
};




#endif