#ifndef CALCULATERESIDUALS_H
#define CALCULATERESIDUALS_H

#include <QObject>
#include <armadillo>

class CalculateResiduals : public QObject
{
    Q_OBJECT
private:
    arma::mat data;
    arma::vec calculatedparameters;
    double FocalLength;
    arma::mat getdata;

public:
    explicit CalculateResiduals(QObject *parent = 0);
    arma::mat Get_Residuals() {return(data);}

    ~CalculateResiduals();

signals:

public slots:

    void ListenData(arma::mat d);
    void ListenFocalLength(double fl);
    void ListenFinalParameters(arma::vec fp);
    void execute();

};

#endif // CALCULATERESIDUALS_H
