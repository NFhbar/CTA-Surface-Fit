#ifndef GENRATEDATA_H
#define GENRATEDATA_H

#include <QObject>
#include <armadillo>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

class GenrateData : public QObject
{
    Q_OBJECT
public:
    explicit GenrateData(QObject *parent = 0);
     ~GenrateData();

    void Execute();

    arma::mat Get_Data () { return(Data) ;}
    arma::mat Get_ModelData () { return(ModelData) ;}

signals:
    
public slots:
    void ListenGrid(arma::vec Grid);
    void ListenParameters(arma::vec Para);
    void ListenSurface(QString S);

private:
    arma::vec ParametersOfGid;
    arma::vec ParametersofTransformation;
    QString Surface;
    arma::mat Data;
    arma::mat ModelData;
    
};

#endif // GENRATEDATA_H
