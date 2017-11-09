#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <armadillo>


class calculate : public QObject
{
    Q_OBJECT

private:
arma::vec V;
arma::mat M;
double ChiS;
double FocalLength;
arma::vec parameters;
arma::mat data;
QString SurfaceType;

public:
    explicit calculate(QObject *parent = 0);

    arma::vec Get_V (void) {return(V) ;}
    arma::mat Get_M (void) {return(M) ;}
    double Get_ChiS (void) {return(ChiS) ;}

    ~calculate();

signals:

public slots:
    void ListenFocalLength(double FL);
    void ListenParameters(arma::vec p);
    void ListenData(arma::mat GetData);
    void ListenSurfaceType(QString surfacetype);
    void process();

};

#endif // CALCULATE_H
