#include "calculate.h"

calculate::calculate(QObject *parent) :
    QObject(parent)
{
}

//=========================================Constructor=======================================================//
//===========================================================================================================//
void calculate::process()
{
    int number_of_points = data.n_rows;

    //----------------------------------------------------------
    //Rotation matrices and translation vector
    //Rotation in Y (beta)
    arma::mat Ry, Ry1, Ry2;
    {
    double s = sin(parameters[0]);
    double c = cos(parameters[0]);

    Ry << c 	 << 0.0000 << s      << arma::endr					//Matrix for rotation in y axis
       << 0.0000 << 1.0000 << 0.0000 << arma::endr
       <<-s      << 0.0000 << c      << arma::endr;

    Ry1<<-s      << 0.0000 << c      << arma::endr					//1st derivative  of Matrix for rotation in y axis
       << 0.0000 << 0.0000 << 0.0000 << arma::endr
       <<-c      << 0.0000 <<-s      << arma::endr;

    Ry2<<-c      << 0.0000 <<-s      << arma::endr					//2nd derivative of Matrix for rotation in y axis
       << 0.0000 << 0.0000 << 0.0000 << arma::endr
       << s      << 0.0000 <<-c      << arma::endr;
    }

    //Rotation in X (alpha)
    arma::mat Rx, Rx1, Rx2;
    {
    double s_a = sin(parameters[1]);
    double c_a = cos(parameters[1]);

    Rx << 1.0000 << 0.0000 << 0.0000 << arma::endr				//Matrix for rotation in x axis
       << 0.0000 << c_a    << -s_a   << arma::endr
       << 0.0000 << s_a    <<  c_a   << arma::endr;

    Rx1 << 0.0000 << 0.0000 << 0.0000 << arma::endr	    		//1st derivative Matrix for rotation in x axis
        << 0.0000 <<-s_a    <<-c_a    << arma::endr
        << 0.0000 << c_a    <<-s_a    << arma::endr;

    Rx2 << 0.0000 << 0.0000 << 0.0000 << arma::endr		    	//2nd derivative Matrix for rotation in x axis
        << 0.0000 << -c_a   << s_a    << arma::endr
        << 0.0000 << -s_a   <<-c_a    << arma::endr;
    }

    //---------------------------------------------------
    //Translation vector
    arma::vec t;
    t << parameters[2] << arma::endr					//vector with translations in tx, ty, tz [cm]
      << parameters[3] << arma::endr
      << parameters[4] << arma::endr;

    //----------------------------------------------------------
    //repeating values of s1/FL^2
    double OneOverFLSquare = 1./(FocalLength*FocalLength);							//[1/cm^2]

    //--------------------------------------------------------
    //Return values of ChiSquare, vector V, and matrix M
    ChiS = 0.0000;																	//ChiSquare per iteration    [1]
    V.set_size(5); V.zeros();
    M.set_size(5,5); M.zeros();

    //----------------------------------------------------------
    //loop through data points
    for(int i = 0; i<=number_of_points - 1; i++)
        {

        //-------------------------------------------------------
        //Transforming data
        arma::vec S = Ry*Rx*(data.row(i)).t() + t;										// Units [cm]
        double tau_n = OneOverFLSquare*(S.row(0)*S.row(0) + S.row(1)*S.row(1));		// Units [1]

        //-----------------------------------------------------------------
        //Surface
        double f_tau_n, D_f_tau_n, D_f_tau_tau_n;

        if (SurfaceType == "Parabola")
        {
            f_tau_n       = (1./4.)*tau_n;
            D_f_tau_n     = (1./4.);
            D_f_tau_tau_n = 0.0000;
        }

        if (SurfaceType == "Mirror")
        {
            double sqrttau = sqrt(1. - tau_n);
            double oneplussqrttau = 1. + sqrttau;
            f_tau_n       = (1./486.)*tau_n/(oneplussqrttau)/(oneplussqrttau)/(oneplussqrttau)*(47. + 141.*sqrttau + (1. - tau_n)*(171. + 73.*sqrttau));
            D_f_tau_n     = (32.*(-1. + sqrttau) + tau_n*(-24. + sqrttau*(40. + 24.*tau_n)) + 73.*tau_n*tau_n)/(486.*tau_n*tau_n*tau_n);
            D_f_tau_tau_n = (2.*(-9.*(1. + sqrttau)) + (5. + sqrttau)*tau_n)/(81.*oneplussqrttau*oneplussqrttau*oneplussqrttau*oneplussqrttau*oneplussqrttau*sqrttau);
        }

        //-------------------------------------------------------
        //Repeating value
        double TworoMinusfTau = 2*(S.row(2) - FocalLength*f_tau_n);							// Units [cm]

        //Chi Square
        ChiS += (TworoMinusfTau*TworoMinusfTau/4.);
        // ChiS: [cm^2]

        //--------------------------------------------------------
        //First Derivatives of Chi Square

        arma::vec dSx, dSy, dSz, dtau, Vn;
        Vn.set_size(5); Vn.zeros();

        {
        arma::mat identity = arma::eye<arma::mat>(3,3);

        arma::mat dSdp;
        dSdp.set_size(3,5);
        dSdp.col(0) = Ry1*Rx*data.row(i).t();
        dSdp.col(1) = Ry*Rx1*data.row(i).t();
        dSdp.col(2) = identity.col(0);
        dSdp.col(3) = identity.col(1);
        dSdp.col(4) = identity.col(2);

        dSx = dSdp.row(0).t();				// Units [cm,cm,1,1,1]
        dSy = dSdp.row(1).t();				// Units [cm,cm,1,1,1]
        dSz = dSdp.row(2).t();				// Units [cm,cm,1,1,1]

        }

        dtau = 2*OneOverFLSquare*(S(0)*dSx + S(1)*dSy);		// Units [1,1,1/cm,1/cm,1/cm]

        Vn = TworoMinusfTau*(dSz - FocalLength*D_f_tau_n*dtau);

        V = V + Vn;

        // V: [cm^2,cm^2,cm,cm,cm]

        //-----------------------------------------------------------
        //Second Derivatives of Chi Square

        arma::mat d2Sx, d2Sy, d2Sz, d2tau, Mn;
        Mn.set_size(5,5); Mn.zeros();

        {
        arma::cube dSdp2;
        dSdp2.set_size(3,5,5); dSdp2.zeros();

        arma::mat b2;
        b2.set_size(3,5); b2.zeros();
        b2.col(0) = Ry2*Rx*data.row(i).t();
        b2.col(1) = Ry1*Rx1*data.row(i).t();

        arma::mat a2;
        a2.set_size(3,5); a2.zeros();
        a2.col(0) = b2.col(1);
        a2.col(1) = Ry*Rx2*data.row(i).t();

        arma::mat zero;
        zero.set_size(3,5); zero.zeros();

        dSdp2.slice(0) = b2;
        dSdp2.slice(1) = a2;
        dSdp2.slice(2) = zero;
        dSdp2.slice(3) = zero;
        dSdp2.slice(4) = zero;

        d2Sx = dSdp2(arma::span(0),arma::span(),arma::span());
        d2Sy = dSdp2(arma::span(1),arma::span(),arma::span());
        d2Sz = dSdp2(arma::span(2),arma::span(),arma::span());

        }

        d2tau = 2*OneOverFLSquare*(S(0)*d2Sx + S(1)*d2Sy + dSx*(dSx.t()) + dSy*(dSy.t()));

        Mn = 2*(dSz - FocalLength*D_f_tau_n*dtau)*(dSz - FocalLength*D_f_tau_n*dtau).t() + (1./2.)*TworoMinusfTau*(d2Sz - FocalLength*D_f_tau_n*d2tau - FocalLength*D_f_tau_tau_n*dtau*(dtau.t())); //prevents dividing by 0

        M = M + Mn;

        // M:
        // cm^2 cm^2 cm cm cm
        // cm^2 cm^2 cm cm cm
        // cm   cm   1   1  1
        // cm   cm   1   1  1
        // cm   cm   1   1  1
        }
}

//=========================================Destructor========================================================//
//===========================================================================================================//

calculate::~calculate()
{
//    delete V;
//    delete M;
//    delete ChiS;
//    delete FocalLength;
//    delete parameters;
//    delete data;
//    delete SurfaceType;
}

//=========================================SLOTS=============================================================//
//===========================================================================================================//
void calculate::ListenFocalLength(double FL)
{
    FocalLength = FL;
}

void calculate::ListenParameters(arma::vec p)
{
    parameters = p;
}

void calculate::ListenData(arma::mat GetData)
{
    data = GetData;
}

void calculate::ListenSurfaceType(QString surfacetype)
{
    SurfaceType = surfacetype;
}
//===========================================================================================================//
