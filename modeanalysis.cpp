#include "modeanalysis.h"

ModeAnalysis::ModeAnalysis(QObject *parent) :
    QObject(parent)
{
}

ModeAnalysis::~ModeAnalysis()
{

}

void ModeAnalysis::process()
{
    //Constants and Spherical Coordinates
    arma::mat dz; dz = Residuals;
    double Delta = (2.*arma::datum::pi)/16.;
    //double AFactor = R(1) + R(0);
    SphericalData.copy_size(dz); SphericalData.zeros();
    int J = dz.n_rows;
    double rmaxMinusrmin = R(1) - R(0);
    double rmaxPlusRmin = R(1) + R(0);
    int font_size = 2;

    for(int i = 0; i<=J-1; i++)
        {
            SphericalData(i,0) = sqrt( dz(i,0)*dz(i,0) + dz(i,1)*dz(i,1) );
            SphericalData(i,2) = atan2( dz(i,1),dz(i,0) );
        }

    //Loop Over Modes
    int index = 0;
    Akm.set_size((2*K+1)*(2*M+1),4); Akm.zeros();
    Pkm.set_size((2*K+1)*(2*M+1),3); Pkm.zeros();

    for (int k = -K; k<=K; k++)
        {
            for (int m = -M; m<=M; m++)
            {
                double Rkm = 0.;
                double Ikm = 0.;
                for (int j = 0; j<=J-1; j++)
                {

                    double arg = (k)*(SphericalData(j,0) - R(0))/rmaxMinusrmin + (m)*SphericalData(j,2)/Delta;
                    double Coskm = cos(2*arma::datum::pi*arg);
                    double Sinkm = sin(2*arma::datum::pi*arg);
                    Rkm = Rkm +(1./J)*(dz(j,2)/sqrt(SphericalData(j,0)))*Coskm;
                    Ikm = Ikm -(1./J)*(dz(j,2)/sqrt(SphericalData(j,0)))*Sinkm;

                }
                //added rmaxPlusRmin 01/04/14
                Akm(index,2) = rmaxPlusRmin*Rkm;
                Akm(index,3) = rmaxPlusRmin*Ikm;
                Pkm(index,2) = 2.*rmaxPlusRmin*rmaxPlusRmin*(Rkm*Rkm+Ikm*Ikm);

                if((k==0) && (m ==0))
                {
                    Pkm(index,2) = Pkm(index,2)/2.;
                }

                Akm(index,0) = k;
                Akm(index,1) = m;
                Pkm(index,0) = k;
                Pkm(index,1) = m;
                index = index + 1;
            }
        }

    //Plots
    //Map containers for dynamic allocation of data for m modes plots
    std::map<std::string, mglData> mglDatak;							//map to hold k values of given m
    std::map<std::string, mglData> mglDataP;							//map to hold P values of given m
    std::map<std::string, arma::mat> PKRange;

    //Size of containers
    int size_M_modes = 2*K+1;
    int size_A_plot = Akm.n_rows;

    //Containers for data for modes of m plots
    mglData Matrix_k_Pk(size_M_modes);							//mgldata to hold k values of given m
    mglData Matrix_P_Pk(size_M_modes);							//mgldata to hold P values of given m
    arma::vec PKrange; PKrange.set_size(size_M_modes);

    //Containers for data for magnitude of A plots
    mglData Matrix_k_Akm(size_A_plot);
    mglData Matrix_m_Akm(size_A_plot);
    mglData Matrix_A_Akm(size_A_plot);

    //Loop to find the desired modes of M
    for (int i = 0; i <= SpanOfM; i++)
    {
        arma::uvec indexk = find(Pkm.col(1) == i);				//vec to find indices of given m for matrix
        int indexkrows = indexk.n_rows;						//number of modes matrix

        //-------------------------------------------------------------------------------------------
        //loop to place the values of given modes Matrix
        for (int j = 0; j<=indexkrows -1; j++)
        {
            Matrix_k_Pk.a[j] = Pkm(indexk(j),0);			//place k values in container
            Matrix_P_Pk.a[j] = Pkm(indexk(j),2);			//place P values in container
            PKrange(j)		 = Pkm(indexk(j),2);
        }

        //-------------------------------------------------------------------------------------------
        //Dynamically allocate map key for each mode for Matrix
        std::string mglData_name_k("Matrix_k_Pk" + boost::lexical_cast<std::string>(i));  		//allocate name for key of map dynamically to correspond to each Pkm
        std::string mglData_name_P("Matrix_P_Pk" + boost::lexical_cast<std::string>(i));			//allocate name for key of map dynamically to correspond to each Pkm
        std::string range_for_PKm("RangeP_PK" + boost::lexical_cast<std::string>(i));

        //-------------------------------------------------------------------------------------------
        //Place key and data in map for Matrix
        mglDatak.insert(make_pair(mglData_name_k, Matrix_k_Pk));						//insert key and mgldata in map for k
        mglDataP.insert(make_pair(mglData_name_P, Matrix_P_Pk));						//insert key and mgldata in map for P
        PKRange.insert(make_pair(range_for_PKm, PKrange));

    }

    //QString to string for ErrorModesTitle
    QByteArray byteArray = Title.toUtf8();
    const char* TitleChar = byteArray.constData();
    //Size of Plot and Window
    int width = 1280;
    int height = 600;

    if(PlotType == "ErrorModes")
    {
        //---------------------------------------------------------------------------
        //Set Up Plots for M modes
        mglGraph PKM;
        PKM.SetSize(4096,2160);
        PKM.SetFontSize(font_size);

        PKM.Title(TitleChar,"", 3);

        arma::vec maxvalues; maxvalues.set_size(3);
        arma::vec minvalues; minvalues.set_size(3);
        Amplitudes.set_size(SpanOfM+1,3);


        //Plot dynamically modes of M for Matrix
        for(int k = 0;k <= SpanOfM; k++ )
            {

            PKM.SubPlot(1,SpanOfM+1,k);
            maxvalues = (max(Pkm).t());
            minvalues = (min(Pkm).t());

            PKM.SetRange('x',minvalues[0],maxvalues[0]);
            PKM.SetRange('y',PKRange["RangeP_PK"+boost::lexical_cast<std::string>(k)].min(),PKRange["RangeP_PK"+boost::lexical_cast<std::string>(k)].max());
            PKM.Axis();
            PKM.Plot(mglDatak["Matrix_k_Pk" + boost::lexical_cast<std::string>(k)],mglDataP["Matrix_P_Pk" + boost::lexical_cast<std::string>(k)],"R");
            PKM.Label('x',"k");
            PKM.Label('y', "Pk");

            Amplitudes(k,0) = k;
            Amplitudes(k,1) = PKRange["RangeP_PK"+boost::lexical_cast<std::string>(k)].min();
            Amplitudes(k,2) = PKRange["RangeP_PK"+boost::lexical_cast<std::string>(k)].max();

            }


        //Window to show Plot
        {
            QMainWindow *Wnd = new QMainWindow();
            Wnd->resize(width,height);
            Wnd->setWindowTitle(Title);
            QScrollArea *scroll = new QScrollArea(Wnd);

            //Setup QMathGL
            QMathGL *QMGL = new QMathGL(Wnd);
            QSpinBox *tet;
            QSpinBox *phi;
            QMenu *popup;

            popup = mglMakeMenu(Wnd,QMGL, tet, phi);
            QMGL->setPopup(popup);

            QMGL->setGraph(&PKM);
            qApp->processEvents();
            QMGL->update();

            //window
            QMGL->setRotate(true);
            scroll->setWidget(QMGL);

            Wnd->setCentralWidget(scroll);
            QMGL->refresh();
            Wnd->show();
        }
        PKM.WritePNG("/home/nicolas/Desktop/residuals.png","",false);

    }

    if(PlotType == "Magnitude")
    {
        //Set Up Plots for magnitude of A
        arma::vec Matrix_range_Akm; Matrix_range_Akm.set_size(size_A_plot);

        for(int h = 0; h<=size_A_plot - 1; h++)
        {
            Matrix_k_Akm.a[h] = Akm(h,0);
            Matrix_m_Akm.a[h] = Akm(h,1);
            Matrix_A_Akm.a[h] = sqrt(Akm(h,2)*Akm(h,2) + Akm(h,3)*Akm(h,3));
            Matrix_range_Akm(h) = sqrt(Akm(h,2)*Akm(h,2) + Akm(h,3)*Akm(h,3));

        }

        //AKM
        mglGraph Matrix_AKM;
        Matrix_AKM.SetSize(width,height);
        Matrix_AKM.SetFontSize(font_size);

        Matrix_AKM.Title(TitleChar,"", 3);

        Matrix_AKM.SetRange('x',-K,K);
        Matrix_AKM.SetRange('y',0,M);
        Matrix_AKM.SetRange('z',Matrix_range_Akm.min(),Matrix_range_Akm.max());
        Matrix_AKM.SetRange('c',Matrix_range_Akm.min(),Matrix_range_Akm.max());

        Matrix_AKM.Light(true);  Matrix_AKM.Rotate(50,10);
        Matrix_AKM.Axis();       Matrix_AKM.Box();

        Matrix_AKM.Label('x',"K",1);
        Matrix_AKM.Label('y',"M",1);
        Matrix_AKM.Label('z',"|A|",1);

        Matrix_AKM.Crust(Matrix_k_Akm,Matrix_m_Akm,Matrix_A_Akm);
        Matrix_AKM.Colorbar();

        //Window to show Plot
        {
            QMainWindow *Wnd = new QMainWindow();
            Wnd->resize(width,height);
            Wnd->setWindowTitle(Title);
            QScrollArea *scroll = new QScrollArea(Wnd);

            //Setup QMathGL
            QMathGL *QMGL = new QMathGL(Wnd);
            QSpinBox *tet;
            QSpinBox *phi;
            QMenu *popup;

            popup = mglMakeMenu(Wnd,QMGL, tet, phi);
            QMGL->setPopup(popup);

            QMGL->setGraph(&Matrix_AKM);
            qApp->processEvents();
            QMGL->update();

            //window
            QMGL->setRotate(true);
            scroll->setWidget(QMGL);

            Wnd->setCentralWidget(scroll);
            QMGL->refresh();
            Wnd->show();
        }
         Matrix_AKM.WritePNG("/home/nicolas/Desktop/residuals.png","",false);
    }

}


//=========================================================================================================//
//=======================================SLOTS=============================================================//

void ModeAnalysis::ListenErrorModesPlot(QString ep)
{
    PlotType = ep;
}

void ModeAnalysis::ListenK(int k)
{
    K = k;
}

void ModeAnalysis::ListenM(int m)
{
    M = m;
}

void ModeAnalysis::ListenRadius(arma::vec ra)
{
    R = ra;
}

void ModeAnalysis::ListenResiduals(arma::mat re)
{
    Residuals = re;
}

void ModeAnalysis::ListenSpanM(int sm)
{
    SpanOfM = sm;
}

void ModeAnalysis::ListenTitle(QString t)
{
    Title = t;
}


//=========================================================================================================//
//=========================================================================================================//
