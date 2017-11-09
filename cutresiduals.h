#ifndef CUTRESIDUALS_H
#define CUTRESIDUALS_H

#include <QObject>
#include <armadillo>
#include <QDebug>

class CutResiduals : public QObject
{
    Q_OBJECT

private:
    arma::mat Residuals;
    arma::vec Cut;
    arma::mat CutPoints;
    arma::mat ResidualCut;
    arma::mat CutData;
    arma::mat D;

public:
    explicit CutResiduals(QObject *parent = 0);
    ~CutResiduals();

    arma::mat Get_CutResiduals () {return(ResidualCut);}
    arma::mat Get_CutPoints () {return(CutPoints);}
    arma::mat Get_CutData () {return(CutData);}

    void process();
    
signals:
    
public slots:
    void ListenResiduals(arma::mat);
    void ListenCut(arma::vec);
    void ListenData(arma::mat);
    
};

#endif // CUTRESIDUALS_H
