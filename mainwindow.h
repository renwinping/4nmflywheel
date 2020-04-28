﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstring.h>
#include <QThread>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <qstylefactory.h>

#include "motor.h"
#include "motordriver.h"
#include "csqldatabase.h"
#include "qmotorreport.h"
#include "qdaqcard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool initDriver1();
    void initCombox();
    void updateMotor1Display();
    void initQCustomPlot1();
    void initSql();             //数据库初始化
    void initReport();          //报表初始化
    void initDaqCard();         //数据采集卡初始化
    QVector<QString> makeSqlVector(Motor &);
signals:
    void sendToSqlDB(QString,QString,QString,QVector<QString>);
    //请求从数据库中请求实验数据
    void getLastExpData(QString,QString);

    //非真空getdata信号
    void sendCurrentSpdForAutoTest(double);

    //真空一键测试--发送需要测试的模式
    void startAutoTestModeNoAir(QVector<QString>);
    //速度模式刷新信号
    void refreshAutoTestSpd();
    //滑行模式刷新信号
    void refreshAutoTestHX();
public slots:
    void logMsg(QString);


private slots:
    void on_pushButton_system_power_1_clicked();

    void on_pushButton_single_test_mode_1_clicked();

    void updateMotor();

    void on_doubleSpinBox_motor_test_spd_1_editingFinished();

    void on_comboBox_motor_test_mode_1_currentIndexChanged(int index);

    void refreshCustomPlotData1();

    void on_doubleSpinBox_moto_test_time_valueChanged(double arg1);

	void on_pushButton_auto_test_with_air_power_1_clicked();


    void on_pushButton_sql_query_clicked();

    void updataSqlTableView(const QVector<QVector<QString> > &);

    void on_pushButton_make_report_clicked();

    void setMotorDataFromDAQCard(const QVector<double> &res);

    void on_pushButton_ele_test_ly_mode_power_1_clicked();

    void on_tab1_horizontalSlider_valueChanged(int value);

    void on_pushButton_auto_test_noair_power_1_clicked();

    void on_doubleSpinBox_motor_test_acc_valueChanged(double arg1);
private:
    Ui::MainWindow *ui;

    Motor* p_motor1_;
//    Motor m_motor2_;
//    Motor m_motor3_;
//    Motor m_motor4_;
//    Motor m_motor5_;
//    Motor m_motor6_;

    MotorDriver* p_driver1_;
//    MotorDriver* p_driver2_;
//    MotorDriver* p_driver3_;
//    MotorDriver* p_driver4_;
//    MotorDriver* p_driver5_;
//    MotorDriver* p_driver6_;

    QThread* p_driver_thread1_;
    QThread* p_motor_thread1_;
    //...etc


    bool m_sys_status_1_;
    //获取数据定时器
    QTimer m_timer_get_data_;
    //发送控制指令定时器
    QTimer m_timer_update_;
    //界面刷新buffer
    QVector<double> keyContainer;
    QVector<double> tmpContainer;
    QVector<double> curContainer;
    QVector<double> spdContainer;
    QVector<double> setSpdContainer;

    //数据库部分
    SqlDataBase* p_sql_;
    QThread* p_sql_thread_;
    uint tab_num_ = 0;

    //报表部分
    QMotorReport* p_repoter_;
    QThread* p_repoter_thread_;

    //数据采集卡部分
    QDaqcard* p_daqcard_;
    QThread* p_daqcard_thread_;

};

#endif // MAINWINDOW_H
