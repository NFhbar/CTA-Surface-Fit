#include "loadresiduals.h"

LoadResiduals::LoadResiduals(QObject *parent) :
    QObject(parent)
{
}

LoadResiduals::LoadResiduals(QString FileToOpen)
{
    //int For Number of Points in Parsed File
    int NumberofPoints = 0;

    //Set Name for emit signal
    //FileName = FileNameOpen;

    //Count Number of Points in File
    {
        //Open the Selected File
        QFile FileOpen(FileToOpen);
        QTextStream InFile( &FileOpen);
        QString Line;

        //If File Not Open Then Stop
        if (!FileOpen.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        //Count Number of Points in File
        while (!InFile.atEnd())
            {
                Line  = InFile.readLine();
                NumberofPoints = NumberofPoints + 1;
             }
        FileOpen.flush();
        FileOpen.close();
    }

    //Set Data Size
    residuals.set_size(NumberofPoints,3);

    //Get Data
    {
    QFile FileOpen2(FileToOpen);
    QTextStream InFile2( &FileOpen2);
    QString Line2;

    //If File Not Open Then Stop
    if (!FileOpen2.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //Indices for Keeping Track
    int index = 0;

    //Get Data in Matrix
    QStringList LineSplit;
    QRegExp format("(\\ )");

    while (!InFile2.atEnd())
        {
            Line2  = InFile2.readLine();
            index = index + 1;
            LineSplit = Line2.split(format,QString::SkipEmptyParts);
            residuals(index -1,0) = LineSplit.at(0).toDouble();
            residuals(index -1,1) = LineSplit.at(1).toDouble();
            residuals(index -1,2) = LineSplit.at(2).toDouble();
        }
    FileOpen2.flush();
    FileOpen2.close();
    }

    //Range
    maxvalues.set_size(3);
    minvalues.set_size(3);
    maxvalues = (max(residuals).t());
    minvalues = (min(residuals).t());
}
