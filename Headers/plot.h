#ifndef PLOT_H
#define PLOT_H

#include <QObject>
#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QSpinBox>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenu>
#include <QClipboard>
#include <QTextEdit>
#include <QPainter>
#include <QCursor>
#include <QImage>
#include <QToolBar>
#include <QMenuBar>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <armadillo>
#include <mgl2/mgl.h>
#include <mgl2/data.h>
#include <mgl2/qmathgl.h>
#include <mgl2/qt.h>

class plot : public QObject
{
    Q_OBJECT
public:
    explicit plot(QObject *parent = 0);

    plot(int, int, double, double, double, double, mglData, mglData, mglData, arma::mat, arma::vec, arma::vec);
    plot(arma::mat, QString, QString, QString);
    plot(arma::vec);
    plot(arma::mat, int, int, QString);
    plot(arma::mat, QString);

    ~plot();
    
signals:
    
public slots:

private:

    
};

#endif // PLOT_H
