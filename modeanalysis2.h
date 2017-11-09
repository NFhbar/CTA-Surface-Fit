#ifndef MODEANALYSIS2_H
#define MODEANALYSIS2_H

#include <QObject>
#include <armadillo>
#include <QStringList>
#include <QDebug>
#include <QMap>

class modeanalysis2 : public QObject
{
    Q_OBJECT

private:
    int K;
    int M;
    arma::vec R;
    arma::mat Residuals;
    arma::mat CylindricalData;
    arma::mat CC;
    arma::mat CS;
    arma::mat SC;
    arma::mat SS;
    arma::vec Weights;
    QStringList List;
    QMap<QString, arma::mat>FactorMap;
    QMap<QString, arma::mat>FactorMapWeights;

public:
    explicit modeanalysis2(QObject *parent = 0);
    ~modeanalysis2();

    void process();         //calculate constants
    void process2();        //calculate constants weights

    arma::mat Get_CC () {return(CC) ;}
    arma::mat Get_CS () {return(CS) ;}
    arma::mat Get_SC () {return(SC) ;}
    arma::mat Get_SS () {return(SS) ;}
    arma::mat Get_Weights () {return(Weights); }
    QMap<QString, arma::mat> Get_Map () {return(FactorMap) ;}
    
signals:
    
public slots:
    void ListenK(int k);
    void ListenM(int m);
    void ListenRadius(arma::vec ra);
    void ListenResiduals(arma::mat re);
    void ListenSelectedModes(QStringList l);
    void ListenFactorMap(QMap<QString, arma::mat>map);


    
};

#endif // MODEANALYSIS2_H
