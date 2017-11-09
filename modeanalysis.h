#ifndef MODEANALYSIS_H
#define MODEANALYSIS_H

#include <QObject>
#include <QtCore>
#include <QMainWindow>
#include <QScrollArea>
#include <armadillo>
#include <mgl2/mgl.h>
#include <mgl2/data.h>
#include <mgl2/qmathgl.h>
#include <mgl2/qt.h>
#include <mgl2/wnd.h>
#include <mgl2/canvas_wnd.h>
#include <cmath>
#include <boost/lexical_cast.hpp>

class ModeAnalysis : public QObject
{
    Q_OBJECT

private:
    arma::mat Akm;
    arma::mat Pkm;
    arma::mat SphericalData;
    QString PlotType;
    int K;
    int M;
    int SpanOfM;
    arma::vec R;
    arma::mat Residuals;
    QString Title;
    arma::mat Amplitudes;


public:
    explicit ModeAnalysis(QObject *parent = 0);
    ~ModeAnalysis();

    void process();


    arma::mat Get_Akm () {return(Akm) ;}
    arma::mat Get_Pkm () {return(Pkm) ;}
    arma::mat Get_SphericalData () {return(SphericalData);}
    arma::mat Get_Amplitudes () {return(Amplitudes);}

signals:

public slots:
    void ListenErrorModesPlot(QString ep);
    void ListenK(int k);
    void ListenM(int m);
    void ListenSpanM(int sm);
    void ListenRadius(arma::vec ra);
    void ListenResiduals(arma::mat re);
    void ListenTitle(QString t);


};

#endif // MODEANALYSIS_H
