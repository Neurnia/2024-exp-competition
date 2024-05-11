#include "MainWindow.h"
#include <Qmenubar>
#include <QMainWindow>
#include <QStatusBar>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include "mclmcrrt.h"
#include "mclcppclass.h"

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent),
      centralLayout(new QHBoxLayout),
      paraGroupBox(new ParaGroupBox),
      rightLayout(new QVBoxLayout),
      modeSelectBox(new QComboBox),
      connectionButton(new QPushButton("连接示波器")),

      chart(new QChart),
      series(new QLineSeries),
      chartView(new QChartView(chart, this))
{
    // 初始化 MATLAB Runtime
    if (!mclInitializeApplication(nullptr, 0)) {
        QMessageBox::critical(this, "初始化失败", "无法初始化MATLAB Runtime。");
        exit(1); // 或其他错误处理
    }

    if (!UsbConnectInitialize()) {
        QMessageBox::critical(this, "初始化失败", "无法初始化 UsbConnect 库。");
        exit(1); // 或其他错误处理
    }

    // 将系列添加到图表中
    chart->addSeries(series);
    chart->setTitle("波形图");
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

    connect(connectionButton, &QPushButton::clicked, this, &MainWindow::toggleConnection);

    rightLayout->addWidget(connectionButton);
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
    statusBar()->showMessage("未连接到示波器");
}

MainWindow::~MainWindow() {
    UsbConnectTerminate();
    mclTerminateApplication();

    delete chartView;
}

void MainWindow::toggleConnection() {
    try {
        mwArray isConnected, deviceID;
        if (connectionButton->text() == "连接示波器") {
            connectVisa(2, isConnected, deviceID);
            std::vector<mwUString> s = deviceID.GetStringData();
            mwUString &deviceIDString = s[0];
            if (isConnected) {
                connectionButton->setText("断开示波器");
                statusBar()->showMessage("已连接到示波器：" + QString::fromUtf16(deviceIDString.c_str()));
            } else {
                throw std::runtime_error(QString::fromUtf16(deviceIDString.c_str()).toUtf8().constData());
            }
        } else {
            disconnectVisa(1, isConnected);
            if (!isConnected) {
                connectionButton->setText("连接示波器");
                statusBar()->showMessage("已断开示波器");
            } else {
                throw std::runtime_error("断开示波器失败。");
            }
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "连接错误", QString::fromStdString(e.what()));
        statusBar()->showMessage(QString::fromStdString(e.what()));
    }
}