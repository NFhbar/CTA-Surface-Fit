#include "modeanalysis2.h"

modeanalysis2::modeanalysis2(QObject *parent) :
    QObject(parent)
{
}

modeanalysis2::~modeanalysis2()
{

}

//Process to find Constants
void modeanalysis2::process()
{
    //Constants and Spherical Coordinates
    arma::mat dz; dz = Residuals;
    double Delta = (2.*arma::datum::pi)/16.;
    CylindricalData.copy_size(dz); CylindricalData.zeros();
    int J = dz.n_rows;
    double Jd = dz.n_rows;
    double OneOverJ = 1/Jd;
    double rmaxMinusrmin = R(1) - R(0);
    double rmaxPlusRmin = R(1) + R(0);

    for(int i = 0; i<=J-1; i++)
        {
            CylindricalData(i,0) = sqrt( dz(i,0)*dz(i,0) + dz(i,1)*dz(i,1) );
            CylindricalData(i,2) = atan2( dz(i,1),dz(i,0) );
        }

    //Find Constants
    int size = (K+1)*(M+1);
    CC.set_size(size,3); CC.zeros();
    CS.set_size(size,3); CS.zeros();
    SC.set_size(size,3); SC.zeros();
    SS.set_size(size,3); SS.zeros();

    int index = 0;
    for (int k = 0; k<=K; k++)
        {
            for (int m = 0; m<=M; m++)
                {
                double CCkm = 0.;
                double CSkm = 0.;
                double SCkm = 0.;
                double SSkm = 0.;

                for (int j = 0; j<=J-1; j++)
                    {

                    double argk = 2*arma::datum::pi*(k+0.5)*(CylindricalData(j,0) - R(0))/rmaxMinusrmin;
                    double argm = 2*arma::datum::pi*(m+0.5)*CylindricalData(j,2)/Delta;
                    double Cosk = cos(argk);
                    double Sink = sin(argk);
                    double Cosm = cos(argm);
                    double Sinm = sin(argm);
                    CCkm = CCkm + (dz(j,2)/sqrt(CylindricalData(j,0)))*Cosk*Cosm;
                    CSkm = CSkm + (dz(j,2)/sqrt(CylindricalData(j,0)))*Cosk*Sinm;
                    SCkm = SCkm + (dz(j,2)/sqrt(CylindricalData(j,0)))*Sink*Cosm;
                    SSkm = SSkm + (dz(j,2)/sqrt(CylindricalData(j,0)))*Sink*Sinm;

                    }


                double CCkmf = 2*rmaxPlusRmin*OneOverJ*CCkm;
                double CSkmf = 2*rmaxPlusRmin*OneOverJ*CSkm;
                double SCkmf = 2*rmaxPlusRmin*OneOverJ*SCkm;
                double SSkmf = 2*rmaxPlusRmin*OneOverJ*SSkm;

                CC(index,0) = k;
                CC(index,1) = m;
                CC(index,2) = CCkmf;

                CS(index,0) = k;
                CS(index,1) = m;
                CS(index,2) = CSkmf;

                SC(index,0) = k;
                SC(index,1) = m;
                SC(index,2) = SCkmf;

                SS(index,0) = k;
                SS(index,1) = m;
                SS(index,2) = SSkmf;

                index = index + 1;

                }

    }


    //Calculate Factor Plots
     arma::mat CCMat; CCMat.set_size(J,3); CCMat.zeros();
     arma::mat CSMat; CSMat.set_size(J,3); CSMat.zeros();
     arma::mat SCMat; SCMat.set_size(J,3); SCMat.zeros();
     arma::mat SSMat; SSMat.set_size(J,3); SSMat.zeros();
     QString CCkey;
     QString CSkey;
     QString SCkey;
     QString SSkey;
     FactorMap.clear();

    for(int i =0; i<size; i++)
    {
        //test map
        QString Kkey = QString::number(CC(i,0));
        QString Mkey = QString::number(CC(i,1));
        CCkey = "CC" + Kkey + Mkey;
        CSkey = "CS" + Kkey + Mkey;
        SCkey = "SC" + Kkey + Mkey;
        SSkey = "SS" + Kkey + Mkey;

        for(int j = 0; j<J; j++)
        {
            double argk = 2*arma::datum::pi*(CC(i,0)+0.5)*(CylindricalData(j,0) - R(0))/rmaxMinusrmin;
            double argm = 2*arma::datum::pi*(CC(i,1)+0.5)*CylindricalData(j,2)/Delta;
            double Cosk = cos(argk);
            double Sink = sin(argk);
            double Cosm = cos(argm);
            double Sinm = sin(argm);

            CCMat(j,0) = dz(j,0);
            CCMat(j,1) = dz(j,1);
            CCMat(j,2) = (1/sqrt(CylindricalData(j,0)))*CC(i,2)*Cosk*Cosm;

            CSMat(j,0) = dz(j,0);
            CSMat(j,1) = dz(j,1);
            CSMat(j,2) = (1/sqrt(CylindricalData(j,0)))*CS(i,2)*Cosk*Sinm;

            SCMat(j,0) = dz(j,0);
            SCMat(j,1) = dz(j,1);
            SCMat(j,2) = (1/sqrt(CylindricalData(j,0)))*SC(i,2)*Sink*Cosm;

            SSMat(j,0) = dz(j,0);
            SSMat(j,1) = dz(j,1);
            SSMat(j,2) = (1/sqrt(CylindricalData(j,0)))*SS(i,2)*Sink*Sinm;

        }

        FactorMap[CCkey] = CCMat;
        FactorMap[CSkey] = CSMat;
        FactorMap[SCkey] = SCMat;
        FactorMap[SSkey] = SSMat;

    }
}

//Calculate Weights for Constants
void modeanalysis2::process2()
{
    //Constants and Spherical Coordinates
    arma::mat dz; dz = Residuals;
    CylindricalData.copy_size(dz); CylindricalData.zeros();
    int J = dz.n_rows;

    for(int i = 0; i<=J-1; i++)
        {
            CylindricalData(i,0) = sqrt( dz(i,0)*dz(i,0) + dz(i,1)*dz(i,1) );
            CylindricalData(i,2) = atan2( dz(i,1),dz(i,0) );
        }

    //Matrix and Vector for Weights
    int NumberOfModes = List.size();
    arma::mat ConstantMat; ConstantMat.set_size(NumberOfModes,NumberOfModes); ConstantMat.zeros();
    arma::vec DzConstant; DzConstant.set_size(NumberOfModes); DzConstant.zeros();
    Weights.set_size(NumberOfModes); Weights.zeros();
    arma::mat A; A.set_size(J,NumberOfModes); A.zeros();

    //DzConstants Vector Fill
        for(int i = 0; i< NumberOfModes; i++)
        {
            //pick the selected mode
            QString Mode = List.at(i);                  //mode selection
            arma::mat C = FactorMapWeights[Mode];       //matrix selection
            arma::vec Ccol = C.col(2);                  //column selction

            //Fill Vector
            for(int k = 0; k< J; k++)
                {
                    DzConstant(i) = DzConstant(i) +  dz(k,2)*Ccol(k);
                    A(k,i) = Ccol(k);
                }
            C.zeros();
            Ccol.zeros();

        }


        //Place Constants in Matrix
            for(int k = 0; k < NumberOfModes; k++)
            {
                for(int m = 0; m < NumberOfModes ; m++)
                {
                    for(int h = 0; h < J; h++)
                    {
                            ConstantMat(k,m) = ConstantMat(k,m) + A(h,k)*A(h,m);
                    }

                }
            }

        //Invert Matrix and find Weights
        arma::mat inve;inve.zeros();
        inve = inv(ConstantMat);
        Weights = inve*DzConstant;

}


//==========================================SLOTS===========================================================//
//range of k
void modeanalysis2::ListenK(int k)
{
    K = k;
}

//range of m
void modeanalysis2::ListenM(int m)
{
    M = m;
}

//Listen Radius
void modeanalysis2::ListenRadius(arma::vec ra)
{
    R = ra;

}

//Listen Residuals
void modeanalysis2::ListenResiduals(arma::mat re)
{
    Residuals = re;
}

//Listen Selected Modes
void modeanalysis2::ListenSelectedModes(QStringList l)
{
    List = l;
}

//Listen Factor Map for Weights
void modeanalysis2::ListenFactorMap(QMap<QString, arma::mat> map)
{
    FactorMapWeights = map;
}

