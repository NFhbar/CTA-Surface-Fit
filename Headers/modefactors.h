#ifndef MODEFACTORS_H
#define MODEFACTORS_H

#include <QObject>
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

class ModeFactors : public QObject
{
    Q_OBJECT

private:
    arma::mat Residuals;
    arma::mat SphericalData;
    arma::mat AKM;
    int AK0;
    int A0M;
    arma::vec R;
    QString PlotType;
    arma::mat AA;
    arma::vec abg;
    arma::mat Amplitudes;
    arma::mat A;

public:
    explicit ModeFactors(QObject *parent = 0);
    void process();
    ~ModeFactors();

    arma::mat Get_Matrix() {return (AA);}
    arma::vec Get_Weights() {return (abg);}
    arma::mat Get_Amplitudes() {return (Amplitudes);}
    arma::mat Get_A() {return (A);}

signals:

public slots:
    void ListenResiduals(arma::mat r);
    void ListenSphericalData(arma::mat sd);
    void ListenAKM(arma::mat akm);
    void ListenK(int k);
    void ListenM(int m);
    void ListenRadius(arma::vec r);
    void ListenPlotType(QString pt);

};

#endif // MODEFACTORS_H
