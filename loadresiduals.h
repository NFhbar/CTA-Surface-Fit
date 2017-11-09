#ifndef LOADRESIDUALS_H
#define LOADRESIDUALS_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>
#include <QRegExp>
#include <armadillo>

class LoadResiduals : public QObject
{
    Q_OBJECT

private:
    arma::mat residuals;
    arma::vec maxvalues;
    arma::vec minvalues;

public:
    explicit LoadResiduals(QObject *parent = 0);
    LoadResiduals(QString);

    arma::mat Get_Data() {return(residuals);}
    arma::vec Get_Max_Range() {return(maxvalues);}
    arma::vec Get_Min_Range() {return(minvalues);}



signals:

public slots:

};

#endif // LOADRESIDUALS_H
