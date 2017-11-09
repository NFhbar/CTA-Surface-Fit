#ifndef SUPPRESSRESIDUALS_H
#define SUPPRESSRESIDUALS_H

#include <QObject>
#include <QtCore>
#include <QMainWindow>
#include <QScrollArea>
#include <armadillo>
#include <QListWidget>
#include <mgl2/mgl.h>
#include <mgl2/data.h>
#include <mgl2/qmathgl.h>
#include <mgl2/qt.h>
#include <mgl2/wnd.h>
#include <mgl2/canvas_wnd.h>
#include <cmath>
#include <boost/lexical_cast.hpp>

class SuppressResiduals : public QObject
{
    Q_OBJECT

private:
    arma::mat dz;
    arma::mat Residuals;
    arma::mat Amplitudes;
    QStringList SelectedModes;
    arma::vec Weights;
    arma::mat Factors;
    arma::vec NWeights;
    arma::mat NFactors;
    arma::vec R;
    arma::mat SphericalData;
    int K;
    int M;
    int SpanOfM;
    QString Title;
    QString PlotType;
    arma::mat pkm;

public:
    explicit SuppressResiduals(QObject *parent = 0);
    ~SuppressResiduals();

    arma::mat Get_New_Residuals () {return(dz);}
    arma::mat Get_Amplitudes () {return(Amplitudes);}
    arma::mat Get_PKM () {return(pkm);}
    arma::vec Get_Selected_Weights() {return(NWeights);}
    arma::mat Get_Selected_Factors() {return(NFactors);}

    QStringList Get_Selected_Modes () {return(SelectedModes);}

    void process();


signals:

public slots:
    void ListenResiduals(arma::mat re);
    void ListenSelectedModes(QStringList m);
    void ListenWeights(arma::vec w);
    void ListenFactors(arma::mat f);
    void ListenRadius(arma::vec r);
    void ListenSphericalData(arma::mat s);
    void ListenK(int k);
    void ListenM(int m);
    void ListenSpanOfM(int sm);
    void ListenPlotTitle(QString pt);
    void ListenPlotType(QString p);

};

#endif // SUPPRESSRESIDUALS_H
