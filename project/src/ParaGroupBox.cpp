#include "ParaGroupBox.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>

ParaGroupBox::ParaGroupBox(QWidget *parent)
    : QGroupBox(tr("参数设置"), parent),
      layout(new QVBoxLayout),
      samplingRateBox(new QComboBox),
      prfSpinBox(new QSpinBox),
      gainSlider(new QSlider(Qt::Horizontal)),
      bandwidthSpinBox(new QDoubleSpinBox),
      timeWindowSpinBox(new QDoubleSpinBox),
      filterSettingsBox(new QComboBox)
{
    // 采样率
    QHBoxLayout *samplingLayout = new QHBoxLayout();
    QLabel *samplingLabel = new QLabel("采样率");
    samplingRateBox->addItem("1000 Hz");
    samplingRateBox->addItem("2000 Hz");
    samplingRateBox->addItem("4000 Hz");
    samplingLayout->addWidget(samplingLabel);
    samplingLayout->addWidget(samplingRateBox);

    // 脉冲重复频率
    QHBoxLayout *prfLayout = new QHBoxLayout();
    QLabel *prfLabel = new QLabel("脉冲重复频率");
    prfSpinBox->setRange(100, 5000);
    prfSpinBox->setSingleStep(100);
    prfLayout->addWidget(prfLabel);
    prfLayout->addWidget(prfSpinBox);

    // 增益
    QHBoxLayout *gainLayout = new QHBoxLayout();
    QLabel *gainLabel = new QLabel("增益");
    gainSlider->setRange(0, 60);
    gainLayout->addWidget(gainLabel);
    gainLayout->addWidget(gainSlider);

    // 带宽
    QHBoxLayout *bandwidthLayout = new QHBoxLayout();
    QLabel *bandwidthLabel = new QLabel("带宽");
    bandwidthSpinBox->setRange(10, 10000);  // 需要后续调整
    bandwidthSpinBox->setSingleStep(1);
    bandwidthLayout->addWidget(bandwidthLabel);
    bandwidthLayout->addWidget(bandwidthSpinBox);

    // 时间窗
    QHBoxLayout *timeWindowLayout = new QHBoxLayout();
    QLabel *timeWindowLabel = new QLabel("时间窗");
    timeWindowSpinBox->setRange(1, 1000);  // 微秒到毫秒
    timeWindowSpinBox->setSingleStep(1);
    timeWindowLayout->addWidget(timeWindowLabel);
    timeWindowLayout->addWidget(timeWindowSpinBox);

    // 滤波设置
    QHBoxLayout *filterLayout = new QHBoxLayout();
    QLabel *filterLabel = new QLabel("滤波设置");
    filterSettingsBox->addItem("高通");
    filterSettingsBox->addItem("低通");
    filterSettingsBox->addItem("带通");
    filterSettingsBox->addItem("带阻");
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterSettingsBox);

    // 将所有布局添加到主布局
    layout->addLayout(samplingLayout);
    layout->addLayout(prfLayout);
    layout->addLayout(gainLayout);
    layout->addLayout(bandwidthLayout);
    layout->addLayout(timeWindowLayout);
    layout->addLayout(filterLayout);

    this->setLayout(layout);
}

ParaGroupBox::~ParaGroupBox()
{
    // 析构函数
}
