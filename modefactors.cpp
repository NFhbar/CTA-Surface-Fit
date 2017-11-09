#include "modefactors.h"

ModeFactors::ModeFactors(QObject *parent) :
    QObject(parent)
{
}

ModeFactors::~ModeFactors()
{

}

void ModeFactors::process()
{
    //Constants
    arma::mat dz; dz = Residuals;
    double Delta = (2.*arma::datum::pi)/16.;
    int L = SphericalData.n_rows;
    int I = AKM.n_rows;
    double rmaxMinusrmin = R(1) - R(0);
    int ModeNumber = (AK0+1)*(A0M+1);

    arma::mat AFactors; AFactors.set_size(ModeNumber,4); AFactors.zeros();
    //Find AFactors
    {
    int AFactorsIndex = 0;
    for(int k = 0; k <= AK0; k++)
    {
        for(int m = 0; m <= A0M; m++)
        {
            for(int j = 0; j <= I - 1; j++)
                {
                    if(AKM(j,0) == k && AKM(j,1) == m)
                        {
                            AFactors(AFactorsIndex,0) = k;
                            AFactors(AFactorsIndex,1) = m;
                            AFactors(AFactorsIndex,2) = AKM(j,2);
                            AFactors(AFactorsIndex,3) = AKM(j,3);
                            AFactorsIndex = AFactorsIndex + 1;
                        }
                }
        }
    }
    }

    A.set_size(L,ModeNumber); A.zeros();
    //Calculate Modes
    {
        int modecount = 0;
        for(int k = 0; k <= AK0; k++)
            {
            for(int m = 0; m <= A0M; m++)
                {
                    for(int i = 0; i <= L-1; i++)
                        {
                            //k->k+0.5
                            //m->m+0.5
                            double arg = 2.*arma::datum::pi*(k)*(SphericalData(i,0) -R(0))/(rmaxMinusrmin) + 2.*arma::datum::pi*(m)*SphericalData(i,2)/Delta;
                            A(i,modecount) = ( 2./sqrt(SphericalData(i,0)))*(AFactors(modecount,2)*cos(arg) - AFactors(modecount,3)*(sin(arg)));
                        }
                    modecount = modecount + 1;
                }

            }
     }

    AA.set_size(ModeNumber,ModeNumber); AA.zeros();
    //Fill Matrix
    {
        for(int k = 0; k < ModeNumber; k++)
        {
            for(int m = 0; m < ModeNumber ; m++)
            {
                for(int h = 0; h <= L-1; h++)
                {
                        AA(m,k) = AA(m,k) + A(h,k)*A(h,m);
                }
            }
        }
    }

    arma::vec dzA; dzA.set_size(ModeNumber); dzA.zeros();
    //Calculate Column Vector
    {
        for(int k = 0; k < ModeNumber ; k++)
        {
            for(int h = 0; h <= L-1; h++)
            {
                dzA(k) = dzA(k) + dz(h,2)*A(h,k);
            }
        }
    }

     abg.set_size(ModeNumber); abg.zeros();
     //Find Weight Factors
     abg = inv(AA)*dzA;

      //Calculate New Residuals
      int rows = dz.n_rows;
      arma::vec AlphaDz; AlphaDz.set_size(rows); AlphaDz.zeros();
      {
      for(int g = 0; g <= rows - 1; g++)
      {
          for(int i = 0; i < ModeNumber; i++)
          {
                double Modes =  abg(i)*A(g,i);
                dz(g,2) = dz(g,2) - Modes;
                AlphaDz(g) = AlphaDz(g) + Modes;
          }
      }
      }

      //Plots
      int width = 1280;
      int height = 600;
      Amplitudes.set_size(ModeNumber,4);
      //Individual
      if(PlotType == "Individual")
      {
          for(int i = 0; i<=(ModeNumber) - 1; i++)
          {
          //New dz
          dz.insert_cols(2,abg(i)*A.col(i));
          Amplitudes(i,0) = AFactors(i,0);
          Amplitudes(i,1) = AFactors(i,1);
          Amplitudes(i,2) = min(dz.col(2));
          Amplitudes(i,3) = max(dz.col(2));

          //Number of Points in Data
          int nop = dz.n_rows;

          //Containers
          mglData x(nop);
          mglData y(nop);
          mglData z(nop);

          //Place Data in Cotainers
          for(int j = 0; j <= nop -1; j++)
              {
              x.a[j] = dz(j,0);
              y.a[j] = dz(j,1);
              z.a[j] = dz(j,2);
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
          QString DynamicTitle;
          int kt = AFactors(i,0);
          int mt = AFactors(i,1);
          QString kts = QString::number(kt);
          QString mts = QString::number(mt);
          DynamicTitle = QString("A" + kts + mts);

          QByteArray byteArray = DynamicTitle.toUtf8();
          const char* DynamicTitleChar = byteArray.constData();
          Plot3D.Title(DynamicTitleChar);

          //Window to show Plot
          {
              QMainWindow *Wnd = new QMainWindow();
              Wnd->resize(width,height);
              Wnd->setWindowTitle(DynamicTitle);
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
          QString DynamicSave = QString("/home/nicolas/Desktop/factor%1.png").arg(i+1);
          QByteArray byteArray3 = DynamicSave.toUtf8();
          const char* DynamicSaveChar = byteArray3.constData();
          Plot3D.WritePNG(DynamicSaveChar,"",false);
        }
      }

      //Suppressed Factors Combined
      if (PlotType == "Combined")
      {
          dz.insert_cols(2,AlphaDz);
          for(int i =0; i<ModeNumber; i++)
          {
              Amplitudes(i,0) = AFactors(i,0);
              Amplitudes(i,1) = AFactors(i,1);
          }
           Amplitudes(0,2) = min(dz.col(2));
           Amplitudes(0,3) = max(dz.col(2));

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


}


//=============================================================================================//
//=============================SLOTS==========================================================//
void ModeFactors::ListenResiduals(arma::mat r)
{
    Residuals = r;
}

void ModeFactors::ListenSphericalData(arma::mat sd)
{
    SphericalData = sd;
}

void ModeFactors::ListenAKM(arma::mat akm)
{
    AKM = akm;
}

void ModeFactors::ListenRadius(arma::vec r)
{
    R = r;
}

void ModeFactors::ListenK(int k)
{
    AK0 = k;
}

void ModeFactors::ListenM(int m)
{
    A0M = m;
}

void ModeFactors::ListenPlotType(QString pt)
{
    PlotType = pt;
}
