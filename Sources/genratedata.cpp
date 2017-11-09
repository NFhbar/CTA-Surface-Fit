#include "genratedata.h"

GenrateData::GenrateData(QObject *parent) :
    QObject(parent)
{
}


//Constructor
void GenrateData::Execute()
{
    //General Parameters
    //Vector for Data
    arma::vec r;
    r.set_size(3);
    r.zeros();

    //Tansformation
    arma::mat Ry;
    arma::mat Rx;
    arma::vec translation;

    Ry << cos(-ParametersofTransformation[0])  << 0 << sin(-ParametersofTransformation[0]) << arma::endr
       << 0 		           << 1 << 0 		           << arma::endr
       << -sin(-ParametersofTransformation[0]) << 0 << cos(-ParametersofTransformation[0]) << arma::endr;

    Rx << 1 << 0 		           << 0 		           << arma::endr
       << 0 << cos(-ParametersofTransformation[1]) << -sin(-ParametersofTransformation[1]) << arma::endr
       << 0 << sin(-ParametersofTransformation[1]) <<  cos(-ParametersofTransformation[1]) << arma::endr;

    translation << ParametersofTransformation[2]/ParametersofTransformation[5] << arma::endr
                << ParametersofTransformation[3]/ParametersofTransformation[5] << arma::endr
                << ParametersofTransformation[4]/ParametersofTransformation[5] << arma::endr;

    //Randon Number Generator
    gsl_rng *rng;
    rng = gsl_rng_alloc (gsl_rng_mt19937);
    gsl_rng_set(rng, time(NULL));
    double dz;

    //Total Number of Points
    int number_points_x = (int) abs ((ParametersOfGid[1] - ParametersOfGid[0])/ParametersOfGid[2]);
    int number_points_y = (int) abs ((ParametersOfGid[4] - ParametersOfGid[3])/ParametersOfGid[5]);

    //Matrices for Data
    Data.set_size((number_points_x+1)*(number_points_y+1),3); Data.zeros();
    ModelData.set_size((number_points_x+1)*(number_points_y+1),3); ModelData.zeros();

    //Making Grid Dimensionless
    double dsx = ParametersOfGid[0]/ParametersofTransformation[5];			//dimensionless starting x
    double ddx = ParametersOfGid[2]/ParametersofTransformation[5];			//dimensionless step in x
    double dsy = ParametersOfGid[3]/ParametersofTransformation[5];			//dimensionless starting y
    double ddy = ParametersOfGid[5]/ParametersofTransformation[5];			//dimensionless setp in y
    double ds = ParametersOfGid[6]/ParametersofTransformation[5];           //dimensionless sigma

    //Generate Data

    //Parabola
    if(Surface == "Parabola")
    {
        int w = 0;																	//int for counting rows in matrix
            for (int i = 0; i <= number_points_x; i++)
            {
                    for (int j = 0; j <= number_points_y; j++)
                    {
                        r[0] = dsx + (i * ddx);										//x values
                        r[1] = dsy + (j * ddy);										//y values

                        dz = (gsl_ran_gaussian (rng,ds));							//error

                        r[2] = (1./4.)*( r[0]*r[0] + r[1]*r[1] ) + dz;				//z values

                        w = w + 1;

                        Data.row(w-1) = (ParametersofTransformation[5]*Rx*Ry*(r - translation)).t();
                        ModelData.row(w-1) = ParametersofTransformation[5]*r.t();
                    }
            }

    }

    //FalsePoint
    if(Surface == "FalsePoint")
    {
        //CODE
    }

    //NoFalsePoint
    if(Surface == "Mirror")
    {
        double tau;
        double sqrttau;
        double oneplussqrttau;

        int w = 0;																								//int for counting rows in matrix
        for (int i = 0; i <= number_points_x; i++)
            {
                for (int j = 0; j <= number_points_y; j++)
                    {
                        r[0] = dsx + (i * ddx);																	//x values
                        r[1] = dsy + (j * ddy);																	//y values

                        dz = (gsl_ran_gaussian (rng,ds));														//error

                        tau = r[0]*r[0] + r[1]*r[1];
                        sqrttau= sqrt(1. - tau);
                        oneplussqrttau = 1. + sqrttau;

                        r[2] = (1./486.)*tau/(oneplussqrttau)/(oneplussqrttau)/(oneplussqrttau)*(47. + 141.*sqrttau + (1. - tau)*(171. + 73.*sqrttau)) + dz;	//z value + error dz

                        w = w + 1;																				//keeping track of the row

                        Data.row(w-1) = (ParametersofTransformation[5]*Rx*Ry*(r - translation)).t();					//placing TRANSFORMED unit-full data in matrix
                        ModelData.row(w-1) = ParametersofTransformation[5]*r.t();										//placing UNTRANSFORMED unit-full data in matrix
                    }
            }

    }

    //Sphere
    if(Surface == "Sphere")
    {
        //CODE
    }

}

//Destructor
GenrateData::~GenrateData()
{

}


//====================================================SLOTS===================================================================//
//===========================================================================================================================//

void GenrateData::ListenGrid(arma::vec Grid)
{
    ParametersOfGid = Grid;
}

void GenrateData::ListenParameters(arma::vec Para)
{
    ParametersofTransformation = Para;
}

void GenrateData::ListenSurface(QString S)
{
    Surface = S;
}
