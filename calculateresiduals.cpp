#include "calculateresiduals.h"

CalculateResiduals::CalculateResiduals(QObject *parent) :
    QObject(parent)
{
}

CalculateResiduals::~CalculateResiduals()
{

}

void CalculateResiduals::execute()
{
    data = getdata;
    arma::vec parameters; parameters.set_size(6);
    parameters(0) = calculatedparameters(0);
    parameters(1) = calculatedparameters(1);
    parameters(2) = calculatedparameters(2);
    parameters(3) = calculatedparameters(3);
    parameters(4) = calculatedparameters(4);
    parameters(5) = FocalLength;

    arma::mat Ry;
    Ry << cos(parameters[0])  << 0 << sin(parameters[0]) << arma::endr
       << 0 		          << 1 << 0 		         << arma::endr
       << -sin(parameters[0]) << 0 << cos(parameters[0]) << arma::endr;

    arma::mat Rx;
    Rx << 1 << 0 		          << 0 		             << arma::endr
       << 0 << cos(parameters[1]) << -sin(parameters[1]) << arma::endr
       << 0 << sin(parameters[1]) <<  cos(parameters[1]) << arma::endr;

    arma::vec translation;
    translation << parameters[2]<< arma::endr
                << parameters[3]<< arma::endr
                << parameters[4]<< arma::endr;

    int NumberofPoints = data.n_rows;
    for (int i = 0; i<=NumberofPoints - 1; i++)
        {
            //transform measured data with calculated parameters
            data.row(i) = (Ry*Rx*data.row(i).t() + translation).t();

            //calculate z' with f(tau)
            double tau; tau       = (1./(parameters[5]*parameters[5]))*(data(i,0)*data(i,0) + data(i,1)*data(i,1));
            double sqrttau        = sqrt(1. - tau);
            double oneplussqrttau = 1. + sqrttau;
            double ftau           = (1./486.)*tau/(oneplussqrttau)/(oneplussqrttau)/(oneplussqrttau)*(47. + 141.*sqrttau + (1. - tau)*(171. + 73.*sqrttau));
            double zprime         = parameters[5]*ftau;

            //replace z in tdata with new z'
            data(i,2) = data(i,2) - zprime;

        }
}

void CalculateResiduals::ListenFinalParameters(arma::vec fp)
{
    calculatedparameters = fp;
}

void CalculateResiduals::ListenData(arma::mat d)
{
    getdata = d;
}

void CalculateResiduals::ListenFocalLength(double fl)
{
    FocalLength = fl;
}
