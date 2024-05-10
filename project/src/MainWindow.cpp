#include "MainWindow.h"
#include <Qmenubar>
#include <QMainWindow>
#include <QStatusBar>
#include <QPushButton>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent),
      centralLayout(new QHBoxLayout),
      paraGroupBox(new ParaGroupBox),
      rightLayout(new QVBoxLayout),
      modeSelectBox(new QComboBox),

      chart(new QChart),
      series(new QLineSeries),
      chartView(new QChartView(chart, this))
{
    // 将系列添加到图表中
    chart->addSeries(series);

    // 设置图表标题
    chart->setTitle("波形图");

    // 创建默认的坐标轴
    chart->createDefaultAxes();

    // 配置 X 和 Y 轴
    auto axesX = chart->axes(Qt::Horizontal);
    if (!axesX.isEmpty()) {
        auto axisX = qobject_cast<QValueAxis*>(axesX.first());
        if (axisX) axisX->setTitleText("时间");
    }

    auto axesY = chart->axes(Qt::Vertical);
    if (!axesY.isEmpty()) {
        auto axisY = qobject_cast<QValueAxis*>(axesY.first());
        if (axisY) axisY->setTitleText("幅度");
    }

    // 设置图表视图抗锯齿渲染
    chartView->setRenderHint(QPainter::Antialiasing);

    // 中心右侧布局
    modeSelectBox->addItem("原始信号");
    modeSelectBox->addItem("仅显示正信号");
    modeSelectBox->addItem("负半轴翻转叠加信号");
    modeSelectBox->addItem("包络");
    modeSelectBox->setCurrentIndex(0);

    rightLayout->addWidget(chartView);
    rightLayout->addWidget(modeSelectBox);

    // 总体布局
    centralLayout->addWidget(paraGroupBox, 1);  // 左侧
    centralLayout->addLayout(rightLayout, 3); // 右侧，比例为 3

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    // 创建菜单栏
    QMenu *fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    QAction *exitAction = fileMenu->addAction(tr("退出(&x)"), this, &QWidget::close);
    exitAction->setShortcut(QKeySequence::Quit);

    // 设置状态栏信息
    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    // 清理资源
    delete chartView;
}