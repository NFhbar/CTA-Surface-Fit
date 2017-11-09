#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QListWidget>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QList>
#include <armadillo>
#include <mgl2/data.h>
#include <mgl2/mgl.h>
#include <mgl2/qmathgl.h>
#include <mgl2/qt.h>
#include <mgl2/wnd.h>
#include <mgl2/canvas_wnd.h>
#include <QDebug>
#include <sstream>

#include "genratedata.h"
#include "plot.h"
#include "calculate.h"
#include "calculateresiduals.h"
#include "loadresiduals.h"
#include "modeanalysis.h"
#include "modefactors.h"
#include "suppressresiduals.h"
#include "cutresiduals.h"
#include "label_info.h"
#include "infodialog.h"
#include "modeanalysis2.h"

typedef QList<bool> CheckBoxStatusList;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:
    //GenerateData
    void SayGrid(arma::vec);
    void SayPara(arma::vec);
    void SaySurf(QString);

    //Calculate
    void SayFocalLength(double);
    void SayParameters(arma::vec);
    void SayData(arma::mat);
    void SaySurfaceType(QString);

    //Calculate residuals
    void SayFinalParameters(arma::vec);

    //Error Modes
    void SayK(int);
    void SayM(int);
    void SaySpanM(int);
    void SayRadius(arma::vec);
    void SayTitle(QString);
    void SayResiduals(arma::mat);
    void SayPlotType(QString);

    //Mode Factors
    void SaySphericalData(arma::mat);
    void SayAKM(arma::mat);
    void Selected(QStringList s);
    void SayFactorMap(QMap<QString, arma::mat>);


     //Suppress
     void SayWeights(arma::vec);
     void SayFactors(arma::mat);
     void SaySuppressPlot(QString);
     void SaySuppressTitle(QString);
     //void Selected(QStringList);
     void checkBoxStatusChanged(const CheckBoxStatusList &checkBoxStatus);

     //Cut Residuals
     void SayCutResiduals(arma::mat);
     void SayCuts(arma::vec);

     //HelpInfo
     void SayText(QString);
    
private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_14_editingFinished();

    void on_lineEdit_7_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_lineEdit_8_editingFinished();

    void on_lineEdit_9_editingFinished();

    void on_lineEdit_10_editingFinished();

    void on_lineEdit_11_editingFinished();

    void on_lineEdit_12_editingFinished();

    void on_lineEdit_13_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_10_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_12_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_radioButton_13_clicked();

    void on_radioButton_14_clicked();

    void on_radioButton_15_clicked();

    void on_pushButton_10_clicked();

    void on_radioButton_16_clicked();

    void on_radioButton_17_clicked();

    void on_radioButton_18_clicked();

    void on_radioButton_19_clicked();

    void on_radioButton_20_clicked();

    void on_radioButton_21_clicked();

    void on_lineEdit_21_editingFinished();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_29_clicked();

    void on_radioButton_22_clicked();

    void on_radioButton_23_clicked();

    void on_radioButton_24_clicked();

    void on_radioButton_25_clicked();

    void on_radioButton_26_clicked();

    void on_pushButton_30_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_radioButton_27_clicked();

    void on_radioButton_28_clicked();

    void on_pushButton_31_clicked();

    void on_radioButton_29_clicked();

    void on_radioButton_30_clicked();

    void on_radioButton_31_clicked();

    void on_radioButton_32_clicked();

    void on_pushButton_32_clicked();

    void on_radioButton_33_clicked();

    void on_radioButton_34_clicked();

    void on_radioButton_35_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_33_clicked();

    void on_radioButton_36_clicked();

    void on_radioButton_37_clicked();

    void on_radioButton_38_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_34_clicked();

    //Help Dialogs
    void Mouse_PressedSurface();
    void Mouse_PressedError();
    void Mouse_PressedUnits();
    void Mouse_PressedGrid();
    void Mouse_PressedTransformation();
    void Mouse_PressedOpenData();
    void Mouse_PressedDataType();
    void Mouse_PressedSurfaceType();
    void Mouse_PressedAnalysisType();
    void Mouse_PressedInitialGuess();
    void Mouse_PressedChiSMap();
    void Mouse_PressedResiduals();
    void Mouse_PressedRadii();
    void Mouse_PressedMagnitude();
    void Mouse_PressedAmplitude();

    void on_pushButton_36_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_41_clicked();

public slots:
    void monitorCheckStatus();
    void testMonitorCheckStatus(const CheckBoxStatusList &checkBoxStatus);

private:
    Ui::MainWindow *ui;

    //Data
    arma::mat Data;
    arma::mat d;

    //Simulate Data Page
    QString Surface;
    QString False;
    QString Error;
    double Sigma;
    QString Units;
    QString Startx;
    QString Endx;
    QString Stepx;
    QString Starty;
    QString Endy;
    QString Stepy;
    QString beta;
    QString alpha;
    QString tx;
    QString ty;
    QString tz;
    //QString FocalLength;
    QString SaveData;
    arma::mat TransData;
    arma::mat NonTransData;
    QString TransPlot;
    QString NonTransPlot;

    //Log
    QString SaveLog;

    //Load Data
    QString DataOpen;
    arma::mat LoadData;
    QString LoadPlot;

    //Recover
    QString DataType;
    QString SurfaceType;
    QString AnalysisType;
    int SetPoint;
    arma::mat RoNotData;
    arma::mat Eigenvalues;

    //Residuals
    arma::vec Fparameters;
    arma::mat ResidualsData;
    arma::mat LoadedResiduals;
    arma::mat CleanResiduals;
    QString ResidualsPlot;
    arma::vec R;

    //Error Modes
    QString PlotType;
    arma::mat Akm;
    arma::mat SphericalData;
    int Ak;
    int Am;
    QString PlotTypeFactors;
    arma::mat A;

    //Suppress
    QString PlotTypeS;
    QStringList List;
    arma::vec Weights;
    QStringList Selected1;
    QStringList Selected2;
    QList<QCheckBox *> m_checkBoxList;
    arma::mat NewResiduals;

    //Cut Residuals
    QString RPlotType;
    arma::mat ResidualsCut;
    arma::mat CutPoints;
    QString RCPlotType;

    //Error Modes - Incomplete
    QMap<QString, arma::mat> FactorMap;
    arma::vec WeightsReceived;


};

#endif // MAINWINDOW_H
