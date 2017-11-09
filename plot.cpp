#include "plot.h"


#define MGL_MAX_LINES	(INT_MAX-1000)
#if !defined(WIN32) && !defined(__APPLE__)
#include <X11/Xlib.h>
#endif

#define TR	QObject::tr
QMenu *mglMakeMenu(QMainWindow *Wnd, QMathGL * QMGL, QSpinBox *&tet, QSpinBox *&phi)
{
    QAction *a;
    QMenu *o, *oo;
    QToolBar *bb;

    QMenu *popup = new QMenu(Wnd);
    // file menu
    {
        o = Wnd->menuBar()->addMenu(TR("&File"));
        oo = new QMenu(TR("&Export as 2D ..."),Wnd);
        oo->addAction(TR("PNG"), QMGL, SLOT(exportPNG()),Qt::ALT+Qt::Key_P);
        oo->addAction(TR("JPEG"), QMGL, SLOT(exportJPG()),Qt::ALT+Qt::Key_J);
        o->addMenu(oo);		popup->addMenu(oo);

        o->addSeparator();
        a = new QAction(QPixmap(), TR("Print &graphics"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(print()));
        a->setToolTip(TR("Open printer dialog and print graphics\t(CTRl+P)"));
        a->setShortcut(Qt::CTRL+Qt::Key_P);	o->addAction(a);
        o->addSeparator();
        o->addAction(TR("&Close"), Wnd, SLOT(close()), Qt::CTRL+Qt::Key_W);
    }
    // graphics menu
    {
        bb = new QToolBar(TR("Graphics"),Wnd);
        Wnd->addToolBar(Qt::TopToolBarArea, bb);
        o = Wnd->menuBar()->addMenu(TR("&Graphics"));
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/rotate.xpm"), TR("&Rotate by mouse"), Wnd);
        a->setCheckable(true);
        Wnd->connect(a, SIGNAL(toggled(bool)), QMGL, SLOT(setRotate(bool)));
        Wnd->connect(QMGL, SIGNAL(rotateChanged(bool)), a, SLOT(setOn(bool)));
        a->setToolTip(TR("Switch on/off mouse handling of the graphics\n(rotation, shifting, zooming and perspective)."));
        bb->addAction(a);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/zoom_in.xpm"), TR("&Zoom by mouse"), Wnd);
        a->setCheckable(true);
        Wnd->connect(a, SIGNAL(toggled(bool)), QMGL, SLOT(setZoom(bool)));
        Wnd->connect(QMGL, SIGNAL(zoomChanged(bool)), a, SLOT(setOn(bool)));
        a->setToolTip(TR("Switch on/off mouse zoom of selected region."));
        bb->addAction(a);
        o->addSeparator();
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/zoom_out.xpm"), TR("Res&tore"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(restore()));
        a->setToolTip(TR("Restore default graphics rotation, zoom and perspective (Alt+Space)."));
        a->setShortcut(Qt::ALT+Qt::Key_Space);
        o->addAction(a);	bb->addAction(a);	popup->addAction(a);
        bb->addSeparator();
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/ok.xpm"), TR("Re&draw"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(update()));
        a->setToolTip(TR("Execute script and redraw graphics (F5)."));
        a->setShortcut(Qt::Key_F5);
        o->addAction(a);	bb->addAction(a);	popup->addAction(a);
        a = new QAction(TR("&Adjust size"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(adjust()));
        a->setToolTip(TR("Change canvas size to fill whole region (F6)."));
        a->setShortcut(Qt::Key_F6);		o->addAction(a);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/copy.xpm"), TR("&Copy plot"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(copy()));
        a->setToolTip(TR("Copy graphics to clipboard (CTRl+Shift+G)."));
        a->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_G);
        o->addAction(a);		bb->addAction(a);	popup->addAction(a);

        bb->addSeparator();
        oo = new QMenu(TR("Primitives ..."),Wnd);

        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/line.xpm"), TR("Add line"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(addLine()));
        Wnd->connect(QMGL, SIGNAL(usePrimChanged(bool)), a, SLOT(setVisible(bool)));
        a->setToolTip(TR("Add line which properties can be changed later by mouse."));
        bb->addAction(a);	oo->addAction(a);

        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/mark_a.xpm"), TR("Add mark"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(addMark()));
        Wnd->connect(QMGL, SIGNAL(usePrimChanged(bool)), a, SLOT(setVisible(bool)));
        a->setToolTip(TR("Add marker which properties can be changed later by mouse."));
        bb->addAction(a);	oo->addAction(a);

        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/text.xpm"), TR("Add text"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(addText()));
        Wnd->connect(QMGL, SIGNAL(usePrimChanged(bool)), a, SLOT(setVisible(bool)));
        a->setToolTip(TR("Add text which properties can be changed later by mouse."));
        bb->addAction(a);	oo->addAction(a);
        o->addMenu(oo);

        bb->addSeparator();
        tet = new QSpinBox(Wnd);	tet->setWrapping(true);
        bb->addWidget(tet);	tet->setRange(-180, 180);	tet->setSingleStep(10);
        Wnd->connect(tet, SIGNAL(valueChanged(int)), QMGL, SLOT(setTet(int)));
        Wnd->connect(QMGL, SIGNAL(tetChanged(int)), tet, SLOT(setValue(int)));
        tet->setToolTip(TR("Set value of \\theta angle."));
        bb->addSeparator();
        phi = new QSpinBox(Wnd);	phi->setWrapping(true);
        bb->addWidget(phi);	phi->setRange(-180, 180);	phi->setSingleStep(10);
        Wnd->connect(phi, SIGNAL(valueChanged(int)), QMGL, SLOT(setPhi(int)));
        Wnd->connect(QMGL, SIGNAL(phiChanged(int)), phi, SLOT(setValue(int)));
        phi->setToolTip(TR("Set value of \\phi angle."));
//	bb->addSeparator();
    }
    // zooming menu
    {
        oo = o->addMenu(TR("Zoom/move"));
        bb = new QToolBar(TR("Zoom graphics"),Wnd);
        Wnd->addToolBar(Qt::LeftToolBarArea, bb);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/left_1.xpm"), TR("Move &left"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(shiftLeft()));
        a->setToolTip(TR("Move graphics left by 1/3 of its width."));
        bb->addAction(a);		oo->addAction(a);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/up_1.xpm"), TR("Move &up"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(shiftUp()));
        a->setToolTip(TR("Move graphics up by 1/3 of its height."));
        bb->addAction(a);		oo->addAction(a);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/zoom_1.xpm"), TR("Zoom &in"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(zoomIn()));
        a->setToolTip(TR("Zoom in graphics."));
        bb->addAction(a);		oo->addAction(a);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/norm_1.xpm"), TR("Zoom &out"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(zoomOut()));
        a->setToolTip(TR("Zoom out graphics."));
        bb->addAction(a);		oo->addAction(a);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/down_1.xpm"), TR("Move &down"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(shiftDown()));
        a->setToolTip(TR("Move graphics up down 1/3 of its height."));
        bb->addAction(a);		oo->addAction(a);
        a = new QAction(QPixmap(":/usr/include/mathgl-2.1.2/include/xpm/right_1.xpm"), TR("Move &right"), Wnd);
        Wnd->connect(a, SIGNAL(triggered()), QMGL, SLOT(shiftRight()));
        a->setToolTip(TR("Move graphics right by 1/3 of its width."));
        bb->addAction(a);		oo->addAction(a);
    }
    // animation menu
    {

    }

    Wnd->menuBar()->addSeparator();

    return popup;
}

plot::plot(QObject *parent) :
    QObject(parent)
{
}

//Draw Function for Combined Modes
arma::mat CombinedPlot;
QString Combinedtitle;
int CombinedPlots(mglGraph *Combined)
{
    //Number of Points in Data
    int nop = CombinedPlot.n_rows;
    int width = 1280;
    int height = 600;

    //Containers
    mglData x(nop);
    mglData y(nop);
    mglData z(nop);

    //Place Data in Cotainers
    for(int j = 0; j <= nop -1; j++)
        {
        x.a[j] = CombinedPlot(j,0);
        y.a[j] = CombinedPlot(j,1);
        z.a[j] = CombinedPlot(j,2);
        }

    //Plot
    //Range
    arma::vec maxvalues; maxvalues.set_size(3);
    arma::vec minvalues; minvalues.set_size(3);
    maxvalues = (max(CombinedPlot).t());
    minvalues = (min(CombinedPlot).t());

    //Graph
    Combined->SetSize(width,height);
    Combined->SetFontSize(2);

    Combined->SetRange('x',minvalues[0],maxvalues[0]);
    Combined->SetRange('y',minvalues[1],maxvalues[1]);
    Combined->SetRange('z',minvalues[2],maxvalues[2]);
    Combined->SetRange('c',minvalues[2],maxvalues[2]);

    Combined->Light(true);  Combined->Rotate(50,10);
    Combined->Axis();       Combined->Box();

    Combined->Label('x',"\\i{cm}",1);
    Combined->Label('y',"\\i{cm}",1);
    Combined->Label('z',"\\i{cm}",1);

    Combined->Crust(x,y,z);
    Combined->Colorbar();
    Combined->Puts(mglPoint(360,68),"\\i{cm}");

    //title
    QByteArray byteArray = Combinedtitle.toUtf8();
    const char* DynamicTitleChar = byteArray.constData();
    Combined->Title(DynamicTitleChar);

    Combined->WritePNG("/home/nicolas/Desktop/factor.png","",false);
    return 0;

}

//Draw Function for Modes
arma::mat Factors;
int K;
int M;
QString ModeF;
int PlotFactors(mglGraph *FactorPlot)
{
    //Number of Points in Data
    int nop = Factors.n_rows;
    int width = 1280;
    int height = 600;

    //Containers
    mglData x(nop);
    mglData y(nop);
    mglData z(nop);

    //Place Data in Cotainers
    for(int j = 0; j <= nop -1; j++)
        {
        x.a[j] = Factors(j,0);
        y.a[j] = Factors(j,1);
        z.a[j] = Factors(j,2);
        }

    //Plot
    //Range
    arma::vec maxvalues; maxvalues.set_size(3);
    arma::vec minvalues; minvalues.set_size(3);
    maxvalues = (max(Factors).t());
    minvalues = (min(Factors).t());

    //Graph
    FactorPlot->SetSize(width,height);
    FactorPlot->SetFontSize(2);

    FactorPlot->SetRange('x',minvalues[0],maxvalues[0]);
    FactorPlot->SetRange('y',minvalues[1],maxvalues[1]);
    FactorPlot->SetRange('z',minvalues[2],maxvalues[2]);
    FactorPlot->SetRange('c',minvalues[2],maxvalues[2]);

    FactorPlot->Light(true);  FactorPlot->Rotate(50,10);
    FactorPlot->Axis();       FactorPlot->Box();

    FactorPlot->Label('x',"\\i{cm}",1);
    FactorPlot->Label('y',"\\i{cm}",1);
    FactorPlot->Label('z',"\\i{cm}",1);

    FactorPlot->Crust(x,y,z);
    FactorPlot->Colorbar();
    FactorPlot->Puts(mglPoint(360,68),"\\i{cm}");

    //Dynamic Title
    QString DynamicTitle;
    QString kts = QString::number(K);
    QString mts = QString::number(M);
    DynamicTitle = QString(ModeF + kts + mts);

    QByteArray byteArray = DynamicTitle.toUtf8();
    const char* DynamicTitleChar = byteArray.constData();
    FactorPlot->Title(DynamicTitleChar);

    FactorPlot->WritePNG("/home/nicolas/Desktop/factor.png","",false);
    return 0;

}

//Draw Function for Generated Data
arma::mat d;
QString u;
QString t;
QString ti;
mglGraph *Save;
int Plot(mglGraph *Plot3D)
{

    int Height = 600;
    int Width = 1280;
    Plot3D->SetSize(Width,Height);
    Plot3D->SetFontSize(2);

    //Containers
    int nop = d.n_rows;
    mglData x(nop);
    mglData y(nop);
    mglData z(nop);

    //Place Data in Cotainers
    for(int i = 0; i <= nop -1; i++)
        {
            x.a[i] = d(i,0);
            y.a[i] = d(i,1);
            z.a[i] = d(i,2);
        }

    //Plot
    //Range
    arma::vec maxvalues; maxvalues.set_size(3);
    arma::vec minvalues; minvalues.set_size(3);
    maxvalues = (max(d).t());
    minvalues = (min(d).t());

    Plot3D->SetRange('x',minvalues[0],maxvalues[0]);
    Plot3D->SetRange('y',minvalues[1],maxvalues[1]);
    Plot3D->SetRange('z',minvalues[2],maxvalues[2]);
    Plot3D->SetRange('c',minvalues[2],maxvalues[2]);

    Plot3D->Light(true);

    if(t == "Contour" || t == "Dots")
        {

        }

    if(t == "3D")
    {
        Plot3D->Rotate(50,10);
    }

    Plot3D->Axis();       Plot3D->Box();

    QByteArray Titlearray = ti.toUtf8();
    const char* Titlechar = Titlearray.constData();
    QByteArray Unitsarray = u.toUtf8();
    const char* Unitchar = Unitsarray.constData();

    Plot3D->Label('x',Unitchar,1);
    Plot3D->Label('y',Unitchar,1);
    Plot3D->Label('z',Unitchar,1);

    if(t == "Dots")
    {
        Plot3D->Dots(x,y,z);
    }

    if(t == "Contour" || t == "3D")
    {
        Plot3D->Crust(x,y,z);
    }

    Plot3D->Colorbar();
    Plot3D->Title(Titlechar);
    Save = Plot3D;
    Plot3D->WritePNG("/home/nicolas/Desktop/residuals.png","",false);
    return 0;
 }

//Draw Function for Eigenvalues
arma::vec eigen;
int PlotEigen(mglGraph *gr)
{
    int Height = 600;
    int Width = 1280;
    gr->SetSize(Width,Height);
    gr->SetFontSize(2);

    //Data
    int nop = eigen.n_rows;
    mglData eigenValues(nop);
    mglData Iterations(nop);

    for(int i = 0; i<nop; i++)
    {
        eigenValues.a[i] = eigen(i);
        Iterations.a[i] = i+1;
    }

    ///-------------------------------------------------
    //Prepare Plot
    gr->SetSize(1280,600);
    gr->SetFontSize(2);

    //Plot
    //Range
    arma::vec maxvalues; maxvalues.set_size(1);
    arma::vec minvalues; minvalues.set_size(1);
    maxvalues = (max(eigen));
    minvalues = (min(eigen));

    gr->SetRange('x',1.,nop);
    gr->SetRange('y',minvalues[0],maxvalues[0]);
    //gr.SetFunc("","lg(abs(y))");
    gr->Axis();

    gr->Plot(Iterations,eigenValues);

    gr->Label('x', "Iterations");
    gr->Label('y', "Eigenvalues");

    gr->Title("Eigenvalues per Iterations");
    gr->WritePNG("/home/nicolas/Desktop/residuals.png","",false);
    return 0;
}


//Draw Function for ChiS
int numberpointsx;
int numberpointsy;
double startingtx;
double finishingtx;
double startingty;
double finishingty;
mglData XS;
mglData tx;
mglData ty;
arma::mat ParametersChiS;
arma::vec initialguess;
arma::vec chisquares;
int PlotCS(mglGraph *CSCont)
{
    //Plot
    tx.Rearrange((numberpointsx+1),(numberpointsy+1));
    ty.Rearrange((numberpointsx+1),(numberpointsy+1));
    XS.Rearrange((numberpointsx+1),(numberpointsy+1));

    CSCont->SetSize(1280,600);
    CSCont->SetFontSize(2);

    CSCont->SetRange('x',startingtx,finishingtx);
    CSCont->SetRange('y',startingty,finishingty);
    CSCont->SetRange('c',XS.Minimal(),XS.Maximal());

    CSCont->Axis();
    CSCont->Box();

    CSCont->Dens(tx,ty,XS);
    CSCont->Colorbar(">I");

    CSCont->Label('x', "r_{0x} \\i{cm}");
    CSCont->Label('y', "r_{0y} \\i{cm}");
    arma::uword indexofminChiS;
    double minvalueChiS = chisquares.min(indexofminChiS);
    CSCont->Puts(mglPoint(ParametersChiS(indexofminChiS,0),ParametersChiS(indexofminChiS,1)),"C");
    CSCont->Puts(mglPoint(initialguess[2],initialguess[3]),"I");
    CSCont->Title("Map of \\chi^2 over range of x & y");

    CSCont->WritePNG("/home/nicolas/Desktop/residuals.png","",false);
    return 0;
}

//Constructor for Generated Data & Residuals
plot::plot(arma::mat data, QString Units, QString Type, QString Title)
{
    d = data;
    u = Units;
    t = Type;
    ti = Title;

    //Window to show Plot
    QMainWindow *Wnd = new QMainWindow();
    Wnd->resize(1280,600);
    Wnd->setWindowTitle("Title");
    QScrollArea *scroll = new QScrollArea(Wnd);

    //Setup QMathGL
    QMathGL *QMGL = new QMathGL(Wnd);
    QSpinBox *tet;
    QSpinBox *phi;

    QMenu *popup = mglMakeMenu(Wnd,QMGL, tet, phi);

    QMGL->setPopup(popup);

    QMGL->setDraw(Plot);
    qApp->processEvents();
    QMGL->update();

    QMGL->setRotate(true);
    scroll->setWidget(QMGL);
    Wnd->setCentralWidget(scroll);
    QMGL->refresh();
    Wnd->show();
}

//Constructor for Eigen
plot::plot(arma::vec e)
{
    eigen = e;

    //Window to show Plot
    QMainWindow *Wnd = new QMainWindow();
    Wnd->resize(1280,600);
    Wnd->setWindowTitle("Title");
    QScrollArea *scroll = new QScrollArea(Wnd);

    //Setup QMathGL
    QMathGL *QMGL = new QMathGL(Wnd);
    QSpinBox *tet;
    QSpinBox *phi;

    QMenu *popup = mglMakeMenu(Wnd,QMGL, tet, phi);

    QMGL->setPopup(popup);

    QMGL->setDraw(PlotEigen);
    qApp->processEvents();
    QMGL->update();

    QMGL->setRotate(true);
    scroll->setWidget(QMGL);
    Wnd->setCentralWidget(scroll);
    QMGL->refresh();
    Wnd->show();
}



//Constructor for MapChiS
plot::plot(int nx, int ny, double sx, double fx, double sy, double fy, mglData xs,
           mglData TX, mglData TY, arma::mat PCS, arma::vec ig, arma::vec cs)
{
    //Set
    numberpointsx = nx;
    numberpointsy = ny;
    startingtx = sx;
    finishingtx =fx;
    startingty = sy;
    finishingty = fy;
    XS = xs;
    tx = TX;
    ty = TY;
    ParametersChiS = PCS;
    initialguess = ig;
    chisquares = cs;

    //Window to show Plot
    QMainWindow *Wnd = new QMainWindow();
    Wnd->resize(1280,600);
    Wnd->setWindowTitle("Title");
    QScrollArea *scroll = new QScrollArea(Wnd);

    //Setup QMathGL
    QMathGL *QMGL = new QMathGL(Wnd);
    QSpinBox *tet;
    QSpinBox *phi;

    QMenu *popup = mglMakeMenu(Wnd,QMGL, tet, phi);

    QMGL->setPopup(popup);

    QMGL->setDraw(PlotCS);
    qApp->processEvents();
    QMGL->update();

    QMGL->setRotate(true);
    scroll->setWidget(QMGL);
    Wnd->setCentralWidget(scroll);
    QMGL->refresh();
    Wnd->show();

}


//Constructor for Constant Modes
plot::plot(arma::mat fa, int k, int m, QString mo)
{
    Factors = fa;
    K = k;
    M = m;
    ModeF = mo;

    //Window to show Plot
    QMainWindow *Wnd = new QMainWindow();
    Wnd->resize(1280,600);
    Wnd->setWindowTitle("Title");
    QScrollArea *scroll = new QScrollArea(Wnd);

    //Setup QMathGL
    QMathGL *QMGL = new QMathGL(Wnd);
    QSpinBox *tet;
    QSpinBox *phi;

    QMenu *popup = mglMakeMenu(Wnd,QMGL, tet, phi);

    QMGL->setPopup(popup);

    QMGL->setDraw(PlotFactors);
    qApp->processEvents();
    QMGL->update();

    QMGL->setRotate(true);
    scroll->setWidget(QMGL);
    Wnd->setCentralWidget(scroll);
    QMGL->refresh();
    Wnd->show();
}

//Plot for Combined Modes
plot::plot(arma::mat c, QString ct)
{
    CombinedPlot = c;
    Combinedtitle = ct;

    //Window to show Plot
    QMainWindow *Wnd = new QMainWindow();
    Wnd->resize(1280,600);
    Wnd->setWindowTitle("Title");
    QScrollArea *scroll = new QScrollArea(Wnd);

    //Setup QMathGL
    QMathGL *QMGL = new QMathGL(Wnd);
    QSpinBox *tet;
    QSpinBox *phi;

    QMenu *popup = mglMakeMenu(Wnd,QMGL, tet, phi);

    QMGL->setPopup(popup);

    QMGL->setDraw(CombinedPlots);
    qApp->processEvents();
    QMGL->update();

    QMGL->setRotate(true);
    scroll->setWidget(QMGL);
    Wnd->setCentralWidget(scroll);
    QMGL->refresh();
    Wnd->show();
}


plot::~plot()
{

}




//void QMathGL::exportPNG(QString fname)
//{
//    fname = QFileDialog::getSaveFileName(this, tr("Save Residuals Plot"), "/home" , tr("Png File (*.png);;All Files (*)"));
//    QByteArray byteArray = fname.toUtf8();
//    const char* PlotResidualsChar = byteArray.constData();

//    ::Save->WritePNG(fname);

//}


