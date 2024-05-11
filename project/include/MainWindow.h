#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ParaGroupBox.h"
#include <QMainWindow>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include "UsbConnect.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QHBoxLayout *centralLayout;
    ParaGroupBox *paraGroupBox;
    QVBoxLayout *rightLayout;
    QComboBox *modeSelectBox;
    QPushButton *connectionButton;

    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;

    void toggleConnection();
};

#endif // MAINWINDOW_H