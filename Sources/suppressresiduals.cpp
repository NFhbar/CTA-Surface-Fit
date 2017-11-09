#include "suppressresiduals.h"

SuppressResiduals::SuppressResiduals(QObject *parent) :
    QObject(parent)
{
}

SuppressResiduals::~SuppressResiduals()
{

}

void SuppressResiduals::process()
{
    //Constants
    dz = Residuals;
    double Delta = (2.*arma::datum::pi)/16.;
    int L = SphericalData.n_rows;
    //int I = AKM.n_rows;
    double rmaxMinusrmin = R(1) - R(0);

    //Get Modes
    int modes = SelectedModes.size();
    arma::vec Modes; Modes.set_size(modes);
    if(SelectedModes.isEmpty())
    {
        NWeights = Weights;
        NFactors = Factors;
    }

    else
    {
        NWeights.set_size(modes);
        NFactors.set_size(L,modes);
        for(int i = 0; i<modes; i++)
        {
            QString mode = SelectedModes[i];
            int modeint = mode.toInt();
            NWeights(i) = Weights(modeint);
            NFactors.col(i) = Factors.col(modeint);
        }
    }

      //Calculate New Residuals
      int rows = dz.n_rows;
      int NumberModes = Modes.n_rows;
      arma::vec AlphaDz; AlphaDz.set_size(rows); AlphaDz.zeros();
      {
      for(int g = 0; g <= rows - 1; g++)
      {
          for(int i = 0; i < NumberModes; i++)
          {
                dz(g,2) = dz(g,2) - NWeights(i)*NFactors(g,i);
                AlphaDz(g) = AlphaDz(g) + NWeights(i)*NFactors(g,i);
          }
      }
      }

      //Constants and Spherical Coordinates
      double AFactor = R(1) + R(0);
      int J = dz.n_rows;
      int font_size = 2;

      //Loop Over Modes
      int index = 0;
      pkm.set_size((2*K+1)*(2*M+1),3); pkm.zeros();
      arma::mat akm; akm.set_size((2*K+1)*(2*M+1),4); akm.zeros();

      //Find Akm and Pkm
      for (int k = -K; k<=K; k++)
          {
              for (int m = -M; m<=M; m++)
              {
                  double Rkm = 0.;
                  double Ikm = 0.;
                  for (int j = 0; j<=J-1; j++)
                  {
                      double arg = k*(SphericalData(j,0) - R(0))/rmaxMinusrmin + m*SphericalData(j,2)/Delta;
                      double Coskm = cos(2*arma::datum::pi*arg);
                      double Sinkm = sin(2*arma::datum::pi*arg);
                      Rkm = Rkm +(1./J)*(dz(j,2)/sqrt(SphericalData(j,0)))*Coskm;
                      Ikm = Ikm -(1./J)*(dz(j,2)/sqrt(SphericalData(j,0)))*Sinkm;

                  }
                  akm(index,2) = Rkm;
                  akm(index,3) = Ikm;
                  pkm(index,2) = 2.*(Rkm*Rkm+Ikm*Ikm);

                  if((k==0) && (m ==0))
                  {
                      pkm(index,2) = pkm(index,2)/2.;
                  }

                  akm(index,0) = k;
                  akm(index,1) = m;
                  pkm(index,0) = k;
                  pkm(index,1) = m;
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
      int size_A_plot = akm.n_rows;

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
          arma::uvec indexk = find(pkm.col(1) == i);				//vec to find indices of given m for matrix
          int indexkrows = indexk.n_rows;						//number of modes matrix

          //-------------------------------------------------------------------------------------------
          //loop to place the values of given modes Matrix
          for (int j = 0; j<=indexkrows -1; j++)
          {
              Matrix_k_Pk.a[j] = pkm(indexk(j),0);			//place k values in container
              Matrix_P_Pk.a[j] = pkm(indexk(j),2);			//place P values in container
              PKrange(j)		 = pkm(indexk(j),2);
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
              maxvalues = (max(pkm).t());
              minvalues = (min(pkm).t());

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
              Matrix_k_Akm.a[h] = akm(h,0);
              Matrix_m_Akm.a[h] = akm(h,1);
              Matrix_A_Akm.a[h] = sqrt(akm(h,2)*akm(h,2) + akm(h,3)*akm(h,3));
              Matrix_range_Akm(h) = sqrt(akm(h,2)*akm(h,2) + akm(h,3)*akm(h,3));

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

      if(PlotType == "Factors")
      {
          dz.insert_cols(2,AlphaDz);
//          for(int i =0; i<ModeNumber; i++)
//          {
//              Amplitudes(i,0) = AFactors(i,0);
//              Amplitudes(i,1) = AFactors(i,1);
//          }
           //Amplitudes(0,2) = min(dz.col(2));
           //Amplitudes(0,3) = max(dz.col(2));

       //Number of Points in Data
       int nop = dz.n_rows;

       //Containers
       mglData x(nop);
       mglData y(nop);
       mglData z(nop);

       //Place Data in Cotainers
       for(int i = 0; i <= nop -1; i++)
           {
           x.a[i] = dz(i,0);
           y.a[i] = dz(i,1);
           z.a[i] = dz(i,2);
           }

       //Plot
       //Range
       arma::vec maxvalues; maxvalues.set_size(3);
       arma::vec minvalues; minvalues.set_size(3);
       maxvalues = (max(dz).t());
       minvalues = (min(dz).t());

       //Graph
       mglGraph Plot3D;
       Plot3D.SetSize(width,height);
       Plot3D.SetFontSize(2);

       Plot3D.SetRange('x',minvalues[0],maxvalues[0]);
       Plot3D.SetRange('y',minvalues[1],maxvalues[1]);
       Plot3D.SetRange('z',minvalues[2],maxvalues[2]);
       Plot3D.SetRange('c',minvalues[2],maxvalues[2]);

       Plot3D.Light(true);  Plot3D.Rotate(50,10);
       Plot3D.Axis();       Plot3D.Box();

       Plot3D.Label('x',"\\i{cm}",1);
       Plot3D.Label('y',"\\i{cm}",1);
       Plot3D.Label('z',"\\i{cm}",1);

       Plot3D.Crust(x,y,z);
       Plot3D.Colorbar();
       Plot3D.Puts(mglPoint(360,68),"\\i{cm}");

       //Dynamic Title
       QString Title = "Combined Modes";
       QByteArray byteArray = Title.toUtf8();
       const char* TitleChar = byteArray.constData();
       Plot3D.Title(TitleChar);

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

              QMGL->setGraph(&Plot3D);
              qApp->processEvents();
              QMGL->update();

              //window
              QMGL->setRotate(true);
              scroll->setWidget(QMGL);

              Wnd->setCentralWidget(scroll);
              QMGL->refresh();
              Wnd->show();
          }
       QString DynamicSave = QString("/home/nicolas/Desktop/SubResiduals.png");
       QByteArray byteArray3 = DynamicSave.toUtf8();
       const char* DynamicSaveChar = byteArray3.constData();
       Plot3D.WritePNG(DynamicSaveChar,"",false);
     }

      if(PlotType == "Residuals")
      {
            int nop = dz.n_rows;

       //Containers
       mglData x(nop);
       mglData y(nop);
       mglData z(nop);

       //Place Data in Cotainers
       for(int i = 0; i <= nop -1; i++)
           {
           x.a[i] = dz(i,0);
           y.a[i] = dz(i,1);
           z.a[i] = dz(i,2);
           }

       //Plot
       //Range
       arma::vec maxvalues; maxvalues.set_size(3);
       arma::vec minvalues; minvalues.set_size(3);
       maxvalues = (max(dz).t());
       minvalues = (min(dz).t());

       //Graph
       mglGraph Plot3D;
       Plot3D.SetSize(width,height);
       Plot3D.SetFontSize(2);

       Plot3D.SetRange('x',minvalues[0],maxvalues[0]);
       Plot3D.SetRange('y',minvalues[1],maxvalues[1]);
       Plot3D.SetRange('z',minvalues[2],maxvalues[2]);
       Plot3D.SetRange('c',minvalues[2],maxvalues[2]);

       Plot3D.Light(true);  Plot3D.Rotate(50,10);
       Plot3D.Axis();       Plot3D.Box();

       Plot3D.Label('x',"\\i{cm}",1);
       Plot3D.Label('y',"\\i{cm}",1);
       Plot3D.Label('z',"\\i{cm}",1);

       Plot3D.Crust(x,y,z);
       Plot3D.Colorbar();
       Plot3D.Puts(mglPoint(360,68),"\\i{cm}");

       //Dynamic Title
       QString Title = "Substracted Residuals";
       QByteArray byteArray = Title.toUtf8();
       const char* TitleChar = byteArray.constData();
       Plot3D.Title(TitleChar);

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

              QMGL->setGraph(&Plot3D);
              qApp->processEvents();
              QMGL->update();

              //window
              QMGL->setRotate(true);
              scroll->setWidget(QMGL);

              Wnd->setCentralWidget(scroll);
              QMGL->refresh();
              Wnd->show();
          }
       QString DynamicSave = QString("/home/nicolas/Desktop/SubResiduals.png");
       QByteArray byteArray3 = DynamicSave.toUtf8();
       const char* DynamicSaveChar = byteArray3.constData();
       Plot3D.WritePNG(DynamicSaveChar,"",false);
      }
}


//=============================================================================================================//
//LISTEN SLOTS
//=============================================================================================================//
void SuppressResiduals::ListenResiduals(arma::mat re)
{
    Residuals = re;
}

void SuppressResiduals::ListenSelectedModes(QStringList s)
{
    int n = s.size();
    SelectedModes.clear();
    for(int i=0; i<n;i++)
    {
        QString submode = s.at(i);
        if(submode.mid(1,1) == "c")
        {
            QString submode2 = submode.mid(0,1);
            SelectedModes.append(submode2);
        }
    }
}

void SuppressResiduals::ListenFactors(arma::mat f)
{
    Factors = f;
}

void SuppressResiduals::ListenWeights(arma::vec w)
{
    Weights = w;
}

void SuppressResiduals::ListenRadius(arma::vec r)
{
    R = r;
}

void SuppressResiduals::ListenSphericalData(arma::mat s)
{
    SphericalData = s;
}

void SuppressResiduals::ListenK(int k)
{
    K = k;
}

void SuppressResiduals::ListenM(int m)
{
    M = m;
}

void SuppressResiduals::ListenSpanOfM(int sm)
{
    SpanOfM = sm;
}

void SuppressResiduals::ListenPlotTitle(QString pt)
{
    Title = pt;
}

void SuppressResiduals::ListenPlotType(QString p)
{
    PlotType = p;
}
