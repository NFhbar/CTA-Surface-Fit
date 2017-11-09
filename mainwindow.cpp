#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //Window Title
    QWidget::setWindowTitle("Data Analysis V2");

//==========================================Simulate Data Page====================================================================//
//===============================================================================================================================//

    //Disable
    ui->frame_2->setEnabled(false);
    ui->frame_3->setEnabled(false);
    ui->frame_4->setEnabled(false);
    ui->frame_5->setEnabled(false);
    ui->frame_6->setEnabled(false);
    ui->frame_7->setEnabled(false);
    ui->frame_11->setDisabled(true);
    ui->frame_12->setDisabled(true);
    ui->lineEdit->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_19->setEnabled(false);
   // ui->tab_9->setEnabled(false);
    //ui->scrollArea_9->setDisabled(true);  //obsolete eror mode page
    ui->scrollArea_7->setDisabled(true);    //error mode page


    //Validators
    QValidator *DoubleInput = new QDoubleValidator();
    QValidator *IntInput = new QIntValidator();
    QValidator *IntInput2 = new QIntValidator(0,2147483647);
    ui->lineEdit->setValidator(DoubleInput);            //sigma
    ui->lineEdit_7->setValidator(DoubleInput);          //startx
    ui->lineEdit_2->setValidator(DoubleInput);          //endx
    ui->lineEdit_3->setValidator(DoubleInput);          //stepx
    ui->lineEdit_4->setValidator(DoubleInput);          //starty
    ui->lineEdit_5->setValidator(DoubleInput);          //endy
    ui->lineEdit_6->setValidator(DoubleInput);          //setpy
    ui->lineEdit_8->setValidator(DoubleInput);          //beta
    ui->lineEdit_9->setValidator(DoubleInput);          //alpha
    ui->lineEdit_10->setValidator(DoubleInput);          //tx
    ui->lineEdit_11->setValidator(DoubleInput);          //ty
    ui->lineEdit_12->setValidator(DoubleInput);          //tz
    ui->lineEdit_13->setValidator(DoubleInput);          //FL
    ui->lineEdit_13->setText("558.6300");
    ui->lineEdit_17->setValidator(DoubleInput);          //Multiply Data
    ui->lineEdit_18->setValidator(IntInput);             //Delete Point
    ui->lineEdit_22->setValidator(DoubleInput);          //beta
    ui->lineEdit_23->setValidator(DoubleInput);          //alpha
    ui->lineEdit_24->setValidator(DoubleInput);          //tx
    ui->lineEdit_25->setValidator(DoubleInput);          //ty
    ui->lineEdit_25->setValidator(DoubleInput);          //tz
    ui->lineEdit_27->setValidator(DoubleInput);          //fl
    ui->lineEdit_27->setText("558.6300");
    ui->lineEdit_28->setValidator(IntInput);             //iterations
    ui->lineEdit_29->setValidator(DoubleInput);          //start x
    ui->lineEdit_30->setValidator(DoubleInput);          //end x
    ui->lineEdit_31->setValidator(DoubleInput);          //step x
    ui->lineEdit_32->setValidator(DoubleInput);          //start y
    ui->lineEdit_33->setValidator(DoubleInput);          //end y
    ui->lineEdit_34->setValidator(DoubleInput);          //step y
    ui->lineEdit_35->setValidator(DoubleInput);          //scale residuals
    ui->lineEdit_36->setValidator(IntInput);            //delete residual point
    ui->lineEdit_41->setValidator(DoubleInput);          //radius
    ui->lineEdit_42->setValidator(DoubleInput);          //radius
    ui->lineEdit_37->setValidator(DoubleInput);          //radius2
    ui->lineEdit_38->setValidator(DoubleInput);          //radius2
    ui->lineEdit_41->setText("219.3503");               //radius
    ui->lineEdit_42->setText("340.0000");                   //radius
    ui->lineEdit_37->setText("219.3503");               //radius2
    ui->lineEdit_38->setText("340.0000");                   //radius2
    ui->lineEdit_52->setValidator(IntInput2);            //validator for m
    ui->lineEdit_53->setValidator(IntInput2);            //validator for k

    connect(this, SIGNAL(checkBoxStatusChanged(CheckBoxStatusList)), this, SLOT(testMonitorCheckStatus(CheckBoxStatusList)));

    //label info
    connect(ui->label_2, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedSurface()));
    connect(ui->label_4, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedError()));
    connect(ui->label_20, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedUnits()));
    connect(ui->label_6, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedGrid()));
    connect(ui->label_13, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedTransformation()));
    connect(ui->label_26, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedOpenData()));
    connect(ui->label_33, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedDataType()));
    connect(ui->label_34, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedSurfaceType()));
    connect(ui->label_35, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedAnalysisType()));
    connect(ui->label_36, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedInitialGuess()));
    connect(ui->label, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedChiSMap()));
    connect(ui->label_50, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedResiduals()));
    connect(ui->label_60, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedRadii()));
    connect(ui->label_66, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedMagnitude()));
    connect(ui->label_78, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_PressedAmplitude()));
}

MainWindow::~MainWindow()
{
    delete ui;
}




//==========================================Simulate Data Page====================================================================//
//===============================================================================================================================//
//Parabola
void MainWindow::on_radioButton_clicked()
{
    Surface = "Parabola";
    ui->frame_2->setEnabled(true);
    ui->plainTextEdit_15->appendPlainText("Surface Type:  " + Surface);
}

//Mirror
void MainWindow::on_radioButton_2_clicked()
{
    Surface = "Mirror";
    ui->frame_2->setEnabled(true);
    ui->plainTextEdit_15->appendPlainText("Surface Type:  " + Surface);
}

//False Point Yes
void MainWindow::on_radioButton_3_clicked()
{
    False = "Yes";
    ui->frame_3->setEnabled(true);
//    ui->plainTextEdit_15->appendPlainText("False Point:  " + False);
//    ui->textEdit->append("False Point Option: " + False);
    //False Point not supported
    QString Info = "Information";
    QString Message = "False Point Option Currently not Supported";
    QMessageBox::information(0,Info, Message, QMessageBox::Ok);

}

//False Point No
void MainWindow::on_radioButton_4_clicked()
{
    False = "No";
    ui->frame_3->setEnabled(true);
//    ui->plainTextEdit_15->appendPlainText("False Point:  " + False);
//    ui->textEdit->append("False Point Option: " + False);
    QString Info = "Information";
    QString Message = "False Point Option Currently not Supported";
    QMessageBox::information(0,Info, Message, QMessageBox::Ok);
}

//Error Yes
void MainWindow::on_radioButton_5_clicked()
{
    Error = "Yes";
    ui->frame_6->setEnabled(true);
    ui->frame_4->setEnabled(true);
    ui->frame_5->setEnabled(true);
    ui->lineEdit->setEnabled(true);

}

//Error No
void MainWindow::on_radioButton_6_clicked()
{
    Error = "No";
    ui->frame_6->setEnabled(true);
    ui->frame_4->setEnabled(true);
    ui->frame_5->setEnabled(true);
    ui->lineEdit->setEnabled(false);
    ui->plainTextEdit_15->appendPlainText("Error in z-axis:  " + Error);

}

//Sigma Value
void MainWindow::on_lineEdit_editingFinished()
{
    Sigma = ui->lineEdit->text().toDouble();

    QString sigma2 = QString::number(Sigma);
    ui->plainTextEdit_15->appendPlainText("Error in z-axis: " + sigma2);

}

//Units
void MainWindow::on_lineEdit_14_editingFinished()
{
    Units = ui->lineEdit_14->text();
    ui->plainTextEdit_15->appendPlainText("Units: " + Units);

}

//Start x
void MainWindow::on_lineEdit_7_editingFinished()
{
    Startx = ui->lineEdit_7->text();
    ui->plainTextEdit_15->appendPlainText("Start x: " + Startx);

}

//End x
void MainWindow::on_lineEdit_2_editingFinished()
{
    Endx = ui->lineEdit_2->text();
    ui->plainTextEdit_15->appendPlainText("End x: " + Endx);

}

//Step x
void MainWindow::on_lineEdit_3_editingFinished()
{
    Stepx = ui->lineEdit_3->text();
    ui->plainTextEdit_15->appendPlainText("Step x: " + Stepx);

}

//Start y
void MainWindow::on_lineEdit_4_editingFinished()
{
    Starty = ui->lineEdit_4->text();
    ui->plainTextEdit_15->appendPlainText("Start y: " + Starty);

}

//End y
void MainWindow::on_lineEdit_5_editingFinished()
{
     Endy = ui->lineEdit_5->text();
     ui->plainTextEdit_15->appendPlainText("End y: " + Endy);
}

//Step y
void MainWindow::on_lineEdit_6_editingFinished()
{
    Stepy = ui->lineEdit_6->text();
    ui->plainTextEdit_15->appendPlainText("Step y: " + Stepy);
}

//Beta
void MainWindow::on_lineEdit_8_editingFinished()
{
    beta = ui->lineEdit_8->text();
    ui->plainTextEdit_15->appendPlainText("beta: " + beta);
}

//Alpha
void MainWindow::on_lineEdit_9_editingFinished()
{
    alpha = ui->lineEdit_9->text();
    ui->plainTextEdit_15->appendPlainText("alpha: " + alpha);
}

//tx
void MainWindow::on_lineEdit_10_editingFinished()
{
    tx = ui->lineEdit_10->text();
    ui->plainTextEdit_15->appendPlainText("tx: " + tx);
}

//ty
void MainWindow::on_lineEdit_11_editingFinished()
{
    ty = ui->lineEdit_11->text();
    ui->plainTextEdit_15->appendPlainText("ty: " + ty);
}

//tz
void MainWindow::on_lineEdit_12_editingFinished()
{
    tz = ui->lineEdit_12->text();
    ui->plainTextEdit_15->appendPlainText("tz: " + tz);

    ui->pushButton_3->setEnabled(true);
}

//Focal Length
void MainWindow::on_lineEdit_13_editingFinished()
{
    QString FocalLength = ui->lineEdit_13->text();
    ui->plainTextEdit_15->appendPlainText("Focal Length: " + FocalLength);

}

//Generate Data
void MainWindow::on_pushButton_3_clicked()
{
    ui->frame_7->setEnabled(true);

    arma::vec ParametersOfGid;
    ParametersOfGid.set_size(7);
    ParametersOfGid[0] = ui->lineEdit_7->text().toDouble();
    ParametersOfGid[1] = ui->lineEdit_2->text().toDouble();
    ParametersOfGid[2] = ui->lineEdit_3->text().toDouble();
    ParametersOfGid[3] = ui->lineEdit_4->text().toDouble();
    ParametersOfGid[4] = ui->lineEdit_5->text().toDouble();
    ParametersOfGid[5] = ui->lineEdit_6->text().toDouble();
    ParametersOfGid[6] = ui->lineEdit->text().toDouble();

    arma::vec ParametersofTransformation;
    ParametersofTransformation.set_size(6);
    ParametersofTransformation[0] = ui->lineEdit_8->text().toDouble();
    ParametersofTransformation[1] = ui->lineEdit_9->text().toDouble();
    ParametersofTransformation[2] = ui->lineEdit_10->text().toDouble();
    ParametersofTransformation[3] = ui->lineEdit_11->text().toDouble();
    ParametersofTransformation[4] = ui->lineEdit_12->text().toDouble();
    ParametersofTransformation[5] = ui->lineEdit_13->text().toDouble();

    GenrateData Generate;
    connect(this, SIGNAL(SayGrid(arma::vec)), &Generate, SLOT(ListenGrid(arma::vec)));
    connect(this, SIGNAL(SayPara(arma::vec)), &Generate, SLOT(ListenParameters(arma::vec)));
    connect(this, SIGNAL(SaySurf(QString)), &Generate, SLOT(ListenSurface(QString)));
    emit SayGrid(ParametersOfGid);
    emit SayPara(ParametersofTransformation);
    emit SaySurf(Surface);

    Generate.Execute();

    TransData = Generate.Get_Data();
    NonTransData = Generate.Get_ModelData();

    int nop = TransData.n_rows;
    QString np = QString::number(nop);

    //Fill Text with data info
    ui->textEdit->clear();
    ui->textEdit->append("Surface Type: " + Surface);
    ui->textEdit->append("Units: " + Units);

    if(Error == "No")
    {
        ui->textEdit->append("Error in z-axis " + Error);
    }
    else
    {
        ui->textEdit->append("Error in z-axis " + Error);
        QString sigma2 = QString::number(Sigma);
        ui->textEdit->append("Error in z-axis = " + sigma2);
    }

    QString sx = ui->lineEdit_7->text();
    ui->textEdit->append("Start x = " + sx);
    QString ex = ui->lineEdit_2->text();
    ui->textEdit->append("End x = " + ex);
    QString ssx = ui->lineEdit_3->text();
    ui->textEdit->append("Step x = " + ssx);
    QString sy = ui->lineEdit_4->text();
    ui->textEdit->append("Start y = " + sy);
    QString ey = ui->lineEdit_5->text();
    ui->textEdit->append("End y = " + ey);
    QString ssy = ui->lineEdit_6->text();
    ui->textEdit->append("Step y = " + ssy);
    QString b = ui->lineEdit_8->text();
    ui->textEdit->append("beta = " + b);
    QString a = ui->lineEdit_9->text();
    ui->textEdit->append("alpha = " + a);
    QString tx = ui->lineEdit_10->text();
    ui->textEdit->append("tx = " + tx);
    QString ty = ui->lineEdit_11->text();
    ui->textEdit->append("ty = " + ty);
    QString tz = ui->lineEdit_12->text();
    ui->textEdit->append("tz = " + tz);
    QString f = ui->lineEdit_13->text();
    ui->textEdit->append("Focal Length = " + f);
    ui->textEdit->append("Number of Points = " + np);
    ui->textEdit->append("");

    //Transformed Data
    ui->textEdit->append("Transformed Data");
    for(int i = 0; i<nop; i++)
    {
        double x = TransData(i,0);
        double y = TransData(i,1);
        double z = TransData(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->textEdit->append(sx + "   " + sy + "   " + sz);
    }
    ui->textEdit->append("");

    //Non Transformed Data
    ui->textEdit->append("Non Transformed Data");
    for(int i = 0; i<nop; i++)
    {
        double x = NonTransData(i,0);
        double y = NonTransData(i,1);
        double z = NonTransData(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->textEdit->append(sx + "   " + sy + "   " + sz);
    }
    ui->textEdit->append("");

    ui->plainTextEdit_15->appendPlainText("Data Generated");

    Data = TransData;
    d = TransData;
    RoNotData = TransData;
    ResidualsData = TransData;
}

//Save
void MainWindow::on_pushButton_2_clicked()
{
    //Save File
    SaveData = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (SaveData.isEmpty())
          return;

    QFile SaveCalculations(SaveData);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->textEdit->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

    //Message Everything Ok
    QString Info = "Information";
    QString Message = "Data Saved";
    QMessageBox::information(0,Info, Message, QMessageBox::Ok);

     ui->plainTextEdit_15->appendPlainText("Data Saved:" + SaveData);
}

//Transformed Plot3D
void MainWindow::on_radioButton_7_clicked()
{
    ui->pushButton_4->setEnabled(true);
    TransPlot = "3D";
}

//Transformed PlotContour
void MainWindow::on_radioButton_8_clicked()
{
    ui->pushButton_4->setEnabled(true);
    TransPlot = "Contour";
}

//Transformed PlotDots
void MainWindow::on_radioButton_9_clicked()
{
    ui->pushButton_4->setEnabled(true);
    TransPlot = "Dots";
}

//NonTransformed Plot3D
void MainWindow::on_radioButton_10_clicked()
{
    ui->pushButton_5->setEnabled(true);
    NonTransPlot = "3D";
}

//NonTransformed PlotContour
void MainWindow::on_radioButton_11_clicked()
{
    ui->pushButton_5->setEnabled(true);
    NonTransPlot = "Contour";
}

//NonTransformed PlotDots
void MainWindow::on_radioButton_12_clicked()
{
    ui->pushButton_5->setEnabled(true);
    NonTransPlot = "Dots";
}

//Transformed Plot
void MainWindow::on_pushButton_4_clicked()
{
    QString Title = ui->lineEdit_15->text();
    plot TPlot(TransData, Units, TransPlot, Title);

    ui->plainTextEdit_15->appendPlainText("Transformed Data Plotted");

}

//NonTransformed Plot
void MainWindow::on_pushButton_5_clicked()
{
    QString Title = ui->lineEdit_16->text();
    plot NTPlot(NonTransData, Units, NonTransPlot, Title);

    ui->plainTextEdit_15->appendPlainText("Non-Transformed Data Plotted");
}


//==========================================Log==================================================================================//
//===============================================================================================================================//
//Save
void MainWindow::on_pushButton_clicked()
{
    //Save File
    QString DataFileSave = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (DataFileSave.isEmpty())
          return;

    QFile SaveCalculations(DataFileSave);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->plainTextEdit_15->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

        ui->plainTextEdit_15->appendPlainText("Log Saved  " + DataFileSave);

    //Message Everything Ok
    QString Info = "Information";
    QString Message = "Log Saved";
    QMessageBox::information(0,Info, Message, QMessageBox::Ok);
}

//==========================================Load Data Page======================================================================================//
//==============================================================================================================================================//

//Load Data
void MainWindow::on_pushButton_6_clicked()
{

    DataOpen = QFileDialog::getOpenFileName(this, tr("Open Data File"), "/home/", tr("Text Files (*.txt)"));
    if(DataOpen.isEmpty())
    {
        QString Info = "Warning";
        QString Message = "No File Selected";
        QMessageBox::warning(0,Info, Message, QMessageBox::Ok);
    }

    else
    {
       arma::mat E;                                         //matrix to check for succesful opening of data
       std::string s = DataOpen.toUtf8().constData();       //qstring to std::string for arma::load(std::string filename)

       bool status = E.load(s);                             //boolean for status of opened file

        if(status == true)
          {

            LoadData.load(s);                               //load data
            arma::vec maxvalues = (max(LoadData).t());      //get ranges
            arma::vec minvalues = (min(LoadData).t());

            //TextBrower
            QString n = QString::number(LoadData.n_rows);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit->appendPlainText("");

            ui->plainTextEdit_2->clear();
            for(int i = 0; i < LoadData.n_rows; i++)
            {
                double x = LoadData(i,0);
                double y = LoadData(i,1);
                double z = LoadData(i,2);

                QString sx = QString::number(x,'e',6);
                QString sy = QString::number(y,'e',6);
                QString sz = QString::number(z,'e',6);

                ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
            }

            //Log
            ui->plainTextEdit_15->appendPlainText("Data Loaded: " + DataOpen);

            //Validator
            QValidator *IntegerInput = new QIntValidator(1,LoadData.n_rows,this);
            ui->lineEdit_18->setValidator(IntegerInput);
            ui->lineEdit_21->setValidator(IntegerInput);

            Data = LoadData;
            d = LoadData;
            RoNotData = LoadData;
            ResidualsData = LoadData;

            //Enable
            ui->frame_11->setEnabled(true);
            ui->frame_12->setEnabled(true);

          }

        else
          {
            QString Info = "Warning";
            QString Message = "Data Loading Failed. File must have 3 columns (x y z)";
            QMessageBox::warning(0,Info, Message, QMessageBox::Ok);
          }
    }

}

//Multiply Data
void MainWindow::on_pushButton_7_clicked()
{
    double factor = ui->lineEdit_17->text().toDouble();
    Data =factor*Data;
    RoNotData = Data;
    ResidualsData = Data;
    d = Data;
    int NumberofPoints = Data.n_rows;

    //Range
    {
        arma::vec maxvalues; maxvalues.set_size(3);
        arma::vec minvalues; minvalues.set_size(3);
        maxvalues = (max(Data).t());
        minvalues = (min(Data).t());

        //TextBrower
        QString n = QString::number(NumberofPoints);
        QString maxx = QString::number(maxvalues(0));
        QString maxy = QString::number(maxvalues(1));
        QString maxz = QString::number(maxvalues(2));
        QString minx = QString::number(minvalues(0));
        QString miny = QString::number(minvalues(1));
        QString minz = QString::number(minvalues(2));

        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("Number of Points = " + n);
        ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
        ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
        ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
        ui->plainTextEdit->appendPlainText("");
    }

    //Points
    ui->plainTextEdit_2->clear();
    for(int i = 0; i<NumberofPoints; i++)
    {
        double x = Data(i,0);
        double y = Data(i,1);
        double z = Data(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
    }

    QString f = QString::number(factor);
    ui->plainTextEdit_15->appendPlainText("Data Scaled by = " + f);

}

//Delete Point
void MainWindow::on_pushButton_9_clicked()
{
    int deleterow = ui->lineEdit_18->text().toInt();
    Data.shed_row(deleterow-1);
    ResidualsData = Data;
    RoNotData = Data;
    d = Data;
    int nop = Data.n_rows;
    //Validator
    QValidator *IntegerInput = new QIntValidator(1,nop,this);
    ui->lineEdit_18->setValidator(IntegerInput);
    ui->lineEdit_21->setValidator(IntegerInput);

    //Range
    {
        arma::vec maxvalues; maxvalues.set_size(3);
        arma::vec minvalues; minvalues.set_size(3);
        maxvalues = (max(Data).t());
        minvalues = (min(Data).t());

        //TextBrower
        QString n = QString::number(nop);
        QString maxx = QString::number(maxvalues(0));
        QString maxy = QString::number(maxvalues(1));
        QString maxz = QString::number(maxvalues(2));
        QString minx = QString::number(minvalues(0));
        QString miny = QString::number(minvalues(1));
        QString minz = QString::number(minvalues(2));

        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("Number of Points = " + n);
        ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
        ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
        ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
        ui->plainTextEdit->appendPlainText("");
    }

    //Points
    ui->plainTextEdit_2->clear();
    for(int i = 0; i<nop; i++)
    {
        double x = Data(i,0);
        double y = Data(i,1);
        double z = Data(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
    }

    QString f = QString::number(deleterow);
    ui->plainTextEdit_15->appendPlainText("Point Removed = " + f);

}

//Rotate
void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        Data.col(1) = (-1)*Data.col(1);
        Data.col(2) = (-1)*Data.col(2);
        int nop = Data.n_rows;
        ResidualsData = Data;
        RoNotData = Data;
        d = Data;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(Data).t());
            minvalues = (min(Data).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit->appendPlainText("");
        }

        //Points
        ui->plainTextEdit_2->clear();
        for(int i = 0; i<nop; i++)
        {
            double x = Data(i,0);
            double y = Data(i,1);
            double z = Data(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Data Rotated");

    }

    if(!ui->checkBox->isChecked())
    {
        Data.col(1) = (-1)*Data.col(1);
        Data.col(2) = (-1)*Data.col(2);
        int nop = Data.n_rows;
        ResidualsData = Data;
        RoNotData = Data;
        d = Data;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(Data).t());
            minvalues = (min(Data).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit->appendPlainText("");
        }

        //Points
        ui->plainTextEdit_2->clear();
        for(int i = 0; i<nop; i++)
        {
            double x = Data(i,0);
            double y = Data(i,1);
            double z = Data(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Data Rotated Back");

    }
}

//Reflect
void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
    {
        Data.col(2) = (-1)*Data.col(2);
        int nop = Data.n_rows;
        ResidualsData = Data;
        RoNotData = Data;
        d = Data;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(Data).t());
            minvalues = (min(Data).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit->appendPlainText("");
        }

        //Points
        ui->plainTextEdit_2->clear();
        for(int i = 0; i<nop; i++)
        {
            double x = Data(i,0);
            double y = Data(i,1);
            double z = Data(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Data Reflected");

    }

    if(!ui->checkBox_2->isChecked())
    {
        Data.col(2) = (-1)*Data.col(2);
        int nop = Data.n_rows;
        ResidualsData = Data;
        RoNotData = Data;
        d = Data;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(Data).t());
            minvalues = (min(Data).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit->appendPlainText("");
        }

        //Points
        ui->plainTextEdit_2->clear();
        for(int i = 0; i<nop; i++)
        {
            double x = Data(i,0);
            double y = Data(i,1);
            double z = Data(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Data Reflected Back");

    }

}

//Undo
void MainWindow::on_pushButton_8_clicked()
{
    Data = LoadData;
    int nop = Data.n_rows;
    ResidualsData = Data;
    RoNotData = Data;
    d = Data;

    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);

    //Range
    {
        arma::vec maxvalues; maxvalues.set_size(3);
        arma::vec minvalues; minvalues.set_size(3);
        maxvalues = (max(Data).t());
        minvalues = (min(Data).t());

        //TextBrower
        QString n = QString::number(nop);
        QString maxx = QString::number(maxvalues(0));
        QString maxy = QString::number(maxvalues(1));
        QString maxz = QString::number(maxvalues(2));
        QString minx = QString::number(minvalues(0));
        QString miny = QString::number(minvalues(1));
        QString minz = QString::number(minvalues(2));

        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("Number of Points = " + n);
        ui->plainTextEdit->appendPlainText("Range x =  " + minx + "  " +maxx);
        ui->plainTextEdit->appendPlainText("Range y =  " + miny + "  " +maxy);
        ui->plainTextEdit->appendPlainText("Range z =  " + minz + "  " +maxz);
        ui->plainTextEdit->appendPlainText("");
    }

    //Points
    ui->plainTextEdit_2->clear();
    for(int i = 0; i<nop; i++)
    {
        double x = Data(i,0);
        double y = Data(i,1);
        double z = Data(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->plainTextEdit_2->appendPlainText(sx + "   " + sy + "   " + sz);
    }

    ui->plainTextEdit_15->appendPlainText("Data Restored");
}

//Save Data
void MainWindow::on_pushButton_11_clicked()
{
    //Save File
    QString DataFileSave = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (DataFileSave.isEmpty())
          return;

    QFile SaveCalculations(DataFileSave);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->plainTextEdit_2->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

        ui->plainTextEdit_15->appendPlainText("Data Saved: " + DataFileSave);
}

//3D Plot
void MainWindow::on_radioButton_13_clicked()
{
    LoadPlot = "3D";
}

//Contour
void MainWindow::on_radioButton_14_clicked()
{
    LoadPlot = "Contour";
}

//Dots
void MainWindow::on_radioButton_15_clicked()
{
    LoadPlot = "Dots";
}

//Plot
void MainWindow::on_pushButton_10_clicked()
{
    QString Title = ui->lineEdit_19->text();
    QString Units = ui->lineEdit_20->text();
    plot Plot(Data, Units, LoadPlot, Title);

    ui->plainTextEdit_15->appendPlainText("Data Plotted " + LoadPlot);
}

//==========================================Recover Parameters Page======================================================================================//
//=======================================================================================================================================================//

//Simulated
void MainWindow::on_radioButton_16_clicked()
{
    DataType = "Simulated";
    ui->plainTextEdit_15->appendPlainText("Data Type: " + DataType);
}

//Measured
void MainWindow::on_radioButton_17_clicked()
{
    DataType = "Measured";   
    ui->plainTextEdit_15->appendPlainText("Data Type: " + DataType);
}

//Parabola
void MainWindow::on_radioButton_18_clicked()
{
    SurfaceType = "Parabola";
    ui->plainTextEdit_15->appendPlainText("Surface Type: " + SurfaceType);
}

//Mirror
void MainWindow::on_radioButton_19_clicked()
{
    SurfaceType = "Mirror";
    ui->plainTextEdit_15->appendPlainText("Surface Type: " + SurfaceType);
}

//Standard
void MainWindow::on_radioButton_20_clicked()
{
    AnalysisType = "Standard";
    ui->lineEdit_21->setEnabled(false);

    ui->plainTextEdit_15->appendPlainText("Analysis Type: " + AnalysisType);

    ui->pushButton_16->setEnabled(true);
    ui->pushButton_17->setEnabled(true);

    Data = d;
    int num = Data.n_rows;

    ui->plainTextEdit_4->clear();
    for (int i = 0; i<=num -1 ;i++)
        {
            double x = Data(i,0);
            double y = Data(i,1);
            double z = Data(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_4->appendPlainText(sx + "   " + sy + "   " + sz);
        }

}

//SetPoint
void MainWindow::on_radioButton_21_clicked()
{
    AnalysisType = "Set Point";
    ui->lineEdit_21->setEnabled(true);

    ui->pushButton_16->setEnabled(false);
    ui->pushButton_17->setEnabled(false);

    ui->plainTextEdit_15->appendPlainText("Analysis Type: " + AnalysisType);
}

//SetPoint Value
void MainWindow::on_lineEdit_21_editingFinished()
{
    SetPoint = ui->lineEdit_21->text().toInt();

    Data = d;
    arma::mat Data2;
    Data2 = Data;
    int num = Data.n_rows;
    ui->plainTextEdit_4->clear();
    for (int i = 0; i<=num -1 ;i++)
        {
            Data.row(i) = Data2.row(i) - Data2.row(SetPoint-1);

            double x = Data(i,0);
            double y = Data(i,1);
            double z = Data(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_4->appendPlainText(sx + "   " + sy + "   " + sz);
        }

    QString f = QString::number(SetPoint);
    ui->plainTextEdit_15->appendPlainText("Set Point = " + f);

}

//Calculate
void MainWindow::on_pushButton_12_clicked()
{
    //Get Values
    int IterationsIndex = ui->lineEdit_28->text().toInt();
    double FocalLength = ui->lineEdit_27->text().toDouble();
    arma::vec parameters; parameters.set_size(5);
    parameters(0) = ui->lineEdit_22->text().toDouble();
    parameters(1) = ui->lineEdit_23->text().toDouble();
    parameters(2) = ui->lineEdit_24->text().toDouble();
    parameters(3) = ui->lineEdit_25->text().toDouble();
    parameters(4) = ui->lineEdit_26->text().toDouble();

    arma::vec initialguess; initialguess = parameters;
    //Repeating Values
    double InvFocalLength  = 1./FocalLength;
    double InvFocalLength2 = 1./(FocalLength*FocalLength);
    int NumberPoints= Data.n_rows;

    calculate CS;
    connect(this, SIGNAL(SayFocalLength(double)), &CS, SLOT(ListenFocalLength(double)));
    connect(this, SIGNAL(SayParameters(arma::vec)), &CS, SLOT(ListenParameters(arma::vec)));
    connect(this, SIGNAL(SayData(arma::mat)), &CS, SLOT(ListenData(arma::mat)));
    connect(this, SIGNAL(SaySurfaceType(QString)), &CS, SLOT(ListenSurfaceType(QString)));

    emit SayFocalLength(FocalLength);
    emit SayParameters(parameters);
    emit SayData(Data);
    emit SaySurfaceType(SurfaceType);

    //ChiSquare Table
    ui->tableWidget_3->setRowCount(IterationsIndex);
    ui->tableWidget_3->setColumnCount(6);
    QStringList TableHeaderChiS; TableHeaderChiS<<"Chi Square [cm^2]" <<"Delta beta [radians]" <<"Delta alpha [radians]"
                                                <<"Delta tx [cm]" <<"Delta ty [cm]" <<"Delta tz [cm]";
    ui->tableWidget_3->setHorizontalHeaderLabels(TableHeaderChiS);
    ui->tableWidget_3->setShowGrid(false);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int l = 0;
    ui->plainTextEdit_5->clear();
    ui->plainTextEdit_5->appendPlainText("Data Type: " + DataType);
    ui->plainTextEdit_5->appendPlainText("Surface Type: " + SurfaceType);
    ui->plainTextEdit_5->appendPlainText("Analysis Type = " + AnalysisType);


    if(AnalysisType == "Standard")
    {

        //EigenValue Table
        ui->tableWidget->setRowCount(IterationsIndex);
        ui->tableWidget->setColumnCount(5);
        QStringList TableHeader; TableHeader<<"EigenValue 1"<<"EigenValue 2"<<"EigenValue 3" <<"EigenValue 4" <<"EigenValue 5";
        ui->tableWidget->setHorizontalHeaderLabels(TableHeader);
        ui->tableWidget->setShowGrid(false);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Eigenvalues.set_size(IterationsIndex,5);

        //EigenVectors Table
        ui->tableWidget_2->setRowCount(6*IterationsIndex);
        ui->tableWidget_2->setColumnCount(5);
        QStringList TableHeaderEV; TableHeaderEV<<"Eigenvectors(1)" <<"Eigenvectors(2)" <<"Eigenvectors(3)" <<"Eigenvectors(4)" <<"Eigenvectors(5)";
        ui->tableWidget_2->setHorizontalHeaderLabels(TableHeaderEV);
        ui->tableWidget_2->setShowGrid(false);
        ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(int j = 0; j<IterationsIndex; j++)
        {
            CS.process();

            double ChiS = CS.Get_ChiS();
            arma::vec V = CS.Get_V();
            arma::mat M = CS.Get_M();

            ChiS = InvFocalLength2*ChiS;
            V.rows(0,1) = InvFocalLength2*V.rows(0,1);
            V.rows(2,4) = InvFocalLength*V.rows(2,4);
            M.submat(arma::span(0,1),arma::span(0,1)) = InvFocalLength2*M.submat(arma::span(0,1),arma::span(0,1));
            M.submat(arma::span(0,1),arma::span(2,4)) = InvFocalLength*M.submat(arma::span(0,1),arma::span(2,4));
            M.submat(arma::span(2,4),arma::span(0,1)) = InvFocalLength*M.submat(arma::span(2,4),arma::span(0,1));		//M [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1]

            arma::vec eigenvalues; arma::mat eigenvectors;

            if (!eig_sym(eigenvalues, eigenvectors, M))
            {
                QString Info = "Warning";
                QString Message = "The matrix cannot be inverted, select a different intial guess.";
                QMessageBox::warning(0,Info, Message, QMessageBox::Ok);
                break;
            }

            arma::eig_sym(eigenvalues, eigenvectors, M);

            arma::vec delta_parameters; delta_parameters.set_size(5);
            delta_parameters = -(inv(M))*V;
            delta_parameters.rows(2,4) = FocalLength*delta_parameters.rows(2,4);

            parameters = parameters + delta_parameters;

            //ChiS Table
            QTableWidgetItem *cs = new QTableWidgetItem();
            cs->setData(Qt::DisplayRole,ChiS);
            QTableWidgetItem *db = new QTableWidgetItem();
            db->setData(Qt::DisplayRole,delta_parameters[0]);
            QTableWidgetItem *da = new QTableWidgetItem();
            da->setData(Qt::DisplayRole,delta_parameters[1]);
            QTableWidgetItem *dx = new QTableWidgetItem();
            dx->setData(Qt::DisplayRole,delta_parameters[2]);
            QTableWidgetItem *dy = new QTableWidgetItem();
            dy->setData(Qt::DisplayRole,delta_parameters[3]);
            QTableWidgetItem *dz = new QTableWidgetItem();
            dz->setData(Qt::DisplayRole,delta_parameters[4]);

            ui->tableWidget_3->setItem(j,0,cs);
            ui->tableWidget_3->setItem(j,1,db);
            ui->tableWidget_3->setItem(j,2,da);
            ui->tableWidget_3->setItem(j,3,dx);
            ui->tableWidget_3->setItem(j,4,dy);
            ui->tableWidget_3->setItem(j,5,dz);

            //Eigenvalues Table
            for(int i = 0; i < 5; i++)
            {
                QTableWidgetItem *eigen = new QTableWidgetItem();
                eigen->setData(Qt::DisplayRole,eigenvalues(i));
                ui->tableWidget->setItem(j,i,eigen);
                Eigenvalues(j,i) = eigenvalues(i);
            }


            //Eigenvectors Table
            QTableWidgetItem *iterationcount = new QTableWidgetItem();
            iterationcount->setData(Qt::DisplayRole,j+1);
            ui->tableWidget_2->setItem(l,0,iterationcount);

            for(int col = 0; col < 5; col++)
            {
                for(int row = 0; row < 5; row++)
                {
                    QTableWidgetItem *value = new QTableWidgetItem();
                    value->setData(Qt::DisplayRole,eigenvectors(row,col));
                    ui->tableWidget_2->setItem(l+1,row,value);
                }
                l = l + 1;
            }
            l = l + 1;


            emit SayParameters(parameters);             //listen calculate
        }

        if(DataType == "Simulated")
        {

            QString NOP = QString::number(NumberPoints);
            ui->plainTextEdit_5->appendPlainText("Number of Data Points = " + NOP);
            QString INT = QString::number(IterationsIndex);
            ui->plainTextEdit_5->appendPlainText("Number of Iterations =  " + INT);
            QString FLS = QString::number(FocalLength);
            ui->plainTextEdit_5->appendPlainText("Focal Length =  " + FLS);

            ui->plainTextEdit_5->appendPlainText("");

            QString BETA = ui->lineEdit_8->text();
            QString AL = ui->lineEdit_9->text();
            QString TX = ui->lineEdit_10->text();
            QString TY = ui->lineEdit_11->text();
            QString TZ = ui->lineEdit_12->text();
            ui->plainTextEdit_5->appendPlainText("Original Values of Transformation");
            ui->plainTextEdit_5->appendPlainText("beta  = " + BETA + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + AL + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + TX + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + TY + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + TZ + "[cm]");

            ui->plainTextEdit_5->appendPlainText("");


            QString igb = QString::number(initialguess[0]);
            QString iga = QString::number(initialguess[1]);
            QString igx = QString::number(initialguess[2]);
            QString igy = QString::number(initialguess[3]);
            QString igz = QString::number(initialguess[4]);
            ui->plainTextEdit_5->appendPlainText("Initial Guess");
            ui->plainTextEdit_5->appendPlainText("beta  = " + igb + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + iga + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + igx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + igy + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + igz + "[cm]");

            ui->plainTextEdit_5->appendPlainText("");

            QString p1 = QString::number(parameters[0]);
            QString p2 = QString::number(parameters[1]);
            QString p3 = QString::number(parameters[2]);
            QString p4 = QString::number(parameters[3]);
            QString p5 = QString::number(parameters[4]);
            ui->plainTextEdit_5->appendPlainText("Calculated Values");
            ui->plainTextEdit_5->appendPlainText("beta  = " + p1 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + p2 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + p3 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + p4 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + p5 + "[cm]");

            double difbeta = parameters(0) - ui->lineEdit_8->text().toDouble(); QString difb = QString::number(difbeta);
            double difal = parameters(1) - ui->lineEdit_9->text().toDouble();     QString difa = QString::number(difal);
            double diftx = parameters(2) - ui->lineEdit_10->text().toDouble();     QString difx = QString::number(diftx);
            double difty = parameters(3) - ui->lineEdit_11->text().toDouble();     QString dify = QString::number(difty);
            double diftz = parameters(4) - ui->lineEdit_12->text().toDouble();     QString difz = QString::number(diftz);

            ui->plainTextEdit_5->appendPlainText("");
            ui->plainTextEdit_5->appendPlainText("Difference Between Calcualted and Actual Values");
            ui->plainTextEdit_5->appendPlainText("beta  = " + difb + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + difa + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + difx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + dify + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + difz + "[cm]");

             ui->plainTextEdit_5->appendPlainText("");
        }

        if(DataType == "Measured")
        {
            ui->plainTextEdit_5->appendPlainText("Analysis Type: Standard");
            QString NOP = QString::number(NumberPoints);
            ui->plainTextEdit_5->appendPlainText("Number of Data Points = " + NOP);
            QString INT = QString::number(IterationsIndex);
            ui->plainTextEdit_5->appendPlainText("Number of Iterations =  " + INT);
            QString FLS = QString::number(FocalLength);
            ui->plainTextEdit_5->appendPlainText("Focal Length =  " + FLS);

            ui->plainTextEdit_5->appendPlainText("");

            QString igb = QString::number(initialguess[0]);
            QString iga = QString::number(initialguess[1]);
            QString igx = QString::number(initialguess[2]);
            QString igy = QString::number(initialguess[3]);
            QString igz = QString::number(initialguess[4]);
            ui->plainTextEdit_5->appendPlainText("Initial Guess");
            ui->plainTextEdit_5->appendPlainText("beta  = " + igb + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + iga + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + igx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + igy + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + igz + "[cm]");
            ui->plainTextEdit_5->appendPlainText("");

            QString p1 = QString::number(parameters[0]);
            QString p2 = QString::number(parameters[1]);
            QString p3 = QString::number(parameters[2]);
            QString p4 = QString::number(parameters[3]);
            QString p5 = QString::number(parameters[4]);
            ui->plainTextEdit_5->appendPlainText("Calculated Values");
            ui->plainTextEdit_5->appendPlainText("beta  = " + p1 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + p2 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + p3 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + p4 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + p5 + "[cm]");

             ui->plainTextEdit_5->appendPlainText("");
        }


    }

    if(AnalysisType == "Set Point")
    {

        //EigenValue Table
        ui->tableWidget->setRowCount(IterationsIndex);
        ui->tableWidget->setColumnCount(3);
        QStringList TableHeader; TableHeader<<"EigenValue 1"<<"EigenValue 2"<<"EigenValue 3";
        ui->tableWidget->setHorizontalHeaderLabels(TableHeader);
        ui->tableWidget->setShowGrid(false);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //EigenVectors Table
        ui->tableWidget_2->setRowCount(4*IterationsIndex);
        ui->tableWidget_2->setColumnCount(3);
        QStringList TableHeaderEV; TableHeaderEV<<"Eigenvectors(1)" <<"Eigenvectors(2)" <<"Eigenvectors(3)";
        ui->tableWidget_2->setHorizontalHeaderLabels(TableHeaderEV);
        ui->tableWidget_2->setShowGrid(false);
        ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Eigenvalues.set_size(IterationsIndex,3);

        arma::vec V3; V3.set_size(3);
        arma::mat M3; M3.set_size(3,3);

        for(int j = 0; j<IterationsIndex; j++)
        {
            CS.process();

            double ChiS = CS.Get_ChiS();
            arma::vec V = CS.Get_V();
            arma::mat M = CS.Get_M();

            ChiS = InvFocalLength2*ChiS;
            V.rows(0,1) = InvFocalLength2*V.rows(0,1);
            V.rows(2,4) = InvFocalLength*V.rows(2,4);
            M.submat(arma::span(0,1),arma::span(0,1)) = InvFocalLength2*M.submat(arma::span(0,1),arma::span(0,1));
            M.submat(arma::span(0,1),arma::span(2,4)) = InvFocalLength*M.submat(arma::span(0,1),arma::span(2,4));
            M.submat(arma::span(2,4),arma::span(0,1)) = InvFocalLength*M.submat(arma::span(2,4),arma::span(0,1));		//M [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1]

            V3.rows(0,1) = V.rows(0,1);
            V3(2) = V(4);

            M3.submat(arma::span(0,1),arma::span(0,1)) = M.submat(arma::span(0,1),arma::span(0,1));
            M3(0,2) = M(0,4);
            M3(1,2) = M(1,4);
            M3(2,0) = M(4,0);
            M3(2,1) = M(4,1);
            M3(2,2) = M(4,4);

            arma::vec eigenvalues; arma::mat eigenvectors;

            if (!eig_sym(eigenvalues, eigenvectors, M))
            {
                QString Info = "Warning";
                QString Message = "The matrix cannot be inverted, select a different intial guess.";
                QMessageBox::warning(0,Info, Message, QMessageBox::Ok);
                break;
            }

            arma::eig_sym(eigenvalues, eigenvectors, M3);

            arma::vec delta_parameters; delta_parameters.set_size(3);
            delta_parameters = -(inv(M3))*V3;
            delta_parameters(2) = (FocalLength)*delta_parameters(2);			//[1,1,cm]
            delta_parameters.insert_rows(2,2);

            parameters = parameters + delta_parameters;

            //ChiS Table
            QTableWidgetItem *cs = new QTableWidgetItem();
            cs->setData(Qt::DisplayRole,ChiS);
            QTableWidgetItem *db = new QTableWidgetItem();
            db->setData(Qt::DisplayRole,delta_parameters[0]);
            QTableWidgetItem *da = new QTableWidgetItem();
            da->setData(Qt::DisplayRole,delta_parameters[1]);
            QTableWidgetItem *dx = new QTableWidgetItem();
            dx->setData(Qt::DisplayRole,delta_parameters[2]);
            QTableWidgetItem *dy = new QTableWidgetItem();
            dy->setData(Qt::DisplayRole,delta_parameters[3]);
            QTableWidgetItem *dz = new QTableWidgetItem();
            dz->setData(Qt::DisplayRole,delta_parameters[4]);

            ui->tableWidget_3->setItem(j,0,cs);
            ui->tableWidget_3->setItem(j,1,db);
            ui->tableWidget_3->setItem(j,2,da);
            ui->tableWidget_3->setItem(j,3,dx);
            ui->tableWidget_3->setItem(j,4,dy);
            ui->tableWidget_3->setItem(j,5,dz);

            //Eigenvalues Table
            for(int i = 0; i < 3; i++)
            {
                QTableWidgetItem *eigen = new QTableWidgetItem();
                eigen->setData(Qt::DisplayRole,eigenvalues(i));
                ui->tableWidget->setItem(j,i,eigen);
                Eigenvalues(j,i) = eigenvalues(i);
            }

            //Eigenvectors Table
            QTableWidgetItem *iterationcount = new QTableWidgetItem();
            iterationcount->setData(Qt::DisplayRole,j+1);
            ui->tableWidget_2->setItem(l,0,iterationcount);

            for(int col = 0; col < 3; col++)
            {
                for(int row = 0; row < 3; row++)
                {
                    QTableWidgetItem *value = new QTableWidgetItem();
                    value->setData(Qt::DisplayRole,eigenvectors(row,col));
                    ui->tableWidget_2->setItem(l+1,row,value);
                }
                l = l + 1;
            }
            l = l + 1;

            emit SayParameters(parameters);             //listen calculate
        }

        arma::vec trans; trans.set_size(3);
        arma::vec ronot;
        arma::vec rnot;

        arma::mat Ry;
        Ry << cos(parameters[0])  << 0 << sin(parameters[0]) << arma::endr
           << 0 		          << 1 << 0 		         << arma::endr
           << -sin(parameters[0]) << 0 << cos(parameters[0]) << arma::endr;

        arma::mat Rx;
        Rx << 1 << 0 		          << 0 		             << arma::endr
           << 0 << cos(parameters[1]) << -sin(parameters[1]) << arma::endr
           << 0 << sin(parameters[1]) <<  cos(parameters[1]) << arma::endr;

        int PointSelection = ui->lineEdit_21->text().toInt();
        ronot = RoNotData.row(PointSelection - 1).t();
        rnot = parameters.rows(2,4);

        trans = -Ry*Rx*ronot +rnot;

        parameters.rows(2,4) = trans;

        if(DataType == "Simulated")
        {

            QString NOP = QString::number(NumberPoints);
            ui->plainTextEdit_5->appendPlainText("Number of Data Points = " + NOP);
            QString INT = QString::number(IterationsIndex);
            ui->plainTextEdit_5->appendPlainText("Number of Iterations =  " + INT);
            QString FLS = QString::number(FocalLength);
            ui->plainTextEdit_5->appendPlainText("Focal Length =  " + FLS);

            ui->plainTextEdit_5->appendPlainText("");

            QString BETA = ui->lineEdit_8->text();
            QString AL = ui->lineEdit_9->text();
            QString TX = ui->lineEdit_10->text();
            QString TY = ui->lineEdit_11->text();
            QString TZ = ui->lineEdit_12->text();
            ui->plainTextEdit_5->appendPlainText("Original Values of Transformation");
            ui->plainTextEdit_5->appendPlainText("beta  = " + BETA + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + AL + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + TX + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + TY + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + TZ + "[cm]");

            ui->plainTextEdit_5->appendPlainText("");


            QString igb = QString::number(initialguess[0]);
            QString iga = QString::number(initialguess[1]);
            QString igx = QString::number(initialguess[2]);
            QString igy = QString::number(initialguess[3]);
            QString igz = QString::number(initialguess[4]);
            ui->plainTextEdit_5->appendPlainText("Initial Guess");
            ui->plainTextEdit_5->appendPlainText("beta  = " + igb + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + iga + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = 0  [cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = 0  [cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = 0  [cm]");

            ui->plainTextEdit_5->appendPlainText("");
            QString pointselection = QString::number(SetPoint = ui->lineEdit_21->text().toInt());
            ui->plainTextEdit_5->appendPlainText("Point Selection = " + pointselection);
            ui->plainTextEdit_5->appendPlainText("");
            ui->plainTextEdit_5->appendPlainText("rnotx = " + igx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("rnoty = " + igy + "[cm]");
            ui->plainTextEdit_5->appendPlainText("rnotz = " + igz + "[cm]");
            ui->plainTextEdit_5->appendPlainText("");
            QString pnotx = QString::number(ronot[0]);
            QString pnoty = QString::number(ronot[1]);
            QString pnotz = QString::number(ronot[2]);
            ui->plainTextEdit_5->appendPlainText("pnotx = " + pnotx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("pnoty = " + pnoty + "[cm]");
            ui->plainTextEdit_5->appendPlainText("pnotz = " + pnotz + "[cm]");

            QString p1 = QString::number(parameters[0]);
            QString p2 = QString::number(parameters[1]);
            QString p3 = QString::number(parameters[2]);
            QString p4 = QString::number(parameters[3]);
            QString p5 = QString::number(parameters[4]);
            ui->plainTextEdit_5->appendPlainText("");
            ui->plainTextEdit_5->appendPlainText("Calculated Values");
            ui->plainTextEdit_5->appendPlainText("beta  = " + p1 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + p2 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + p3 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + p4 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + p5 + "[cm]");

            double difbeta = parameters(0) - ui->lineEdit_8->text().toDouble(); QString difb = QString::number(difbeta);
            double difal = parameters(1) - ui->lineEdit_9->text().toDouble();     QString difa = QString::number(difal);
            double diftx = parameters(2) - ui->lineEdit_10->text().toDouble();     QString difx = QString::number(diftx);
            double difty = parameters(3) - ui->lineEdit_11->text().toDouble();     QString dify = QString::number(difty);
            double diftz = parameters(4) - ui->lineEdit_12->text().toDouble();     QString difz = QString::number(diftz);

            ui->plainTextEdit_5->appendPlainText("");
            ui->plainTextEdit_5->appendPlainText("Difference Between Calcualted and Actual Values");
            ui->plainTextEdit_5->appendPlainText("beta  = " + difb + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + difa + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + difx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + dify + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + difz + "[cm]");

             ui->plainTextEdit_5->appendPlainText("");
        }

        if(DataType == "Measured")
        {
            ui->plainTextEdit_5->appendPlainText("Analysis Type: Set Point");
            QString NOP = QString::number(NumberPoints);
            ui->plainTextEdit_5->appendPlainText("Number of Data Points = " + NOP);
            QString INT = QString::number(IterationsIndex);
            ui->plainTextEdit_5->appendPlainText("Number of Iterations =  " + INT);
            QString FLS = QString::number(FocalLength);
            ui->plainTextEdit_5->appendPlainText("Focal Length =  " + FLS);

            ui->plainTextEdit_5->appendPlainText("");
            QString igb = QString::number(initialguess[0]);
            QString iga = QString::number(initialguess[1]);
            QString igx = QString::number(initialguess[2]);
            QString igy = QString::number(initialguess[3]);
            QString igz = QString::number(initialguess[4]);
            ui->plainTextEdit_5->appendPlainText("Initial Guess");
            ui->plainTextEdit_5->appendPlainText("beta  = " + igb + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + iga + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = 0 [cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = 0 [cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = 0 [cm]");

            ui->plainTextEdit_5->appendPlainText("");
            QString pointselection = QString::number(SetPoint = ui->lineEdit_21->text().toInt());
            ui->plainTextEdit_5->appendPlainText("Point Selection = " + pointselection);
            ui->plainTextEdit_5->appendPlainText("");
            ui->plainTextEdit_5->appendPlainText("rnotx = " + igx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("rnoty = " + igy + "[cm]");
            ui->plainTextEdit_5->appendPlainText("rnotz = " + igz + "[cm]");
            ui->plainTextEdit_5->appendPlainText("");
            QString pnotx = QString::number(ronot[0]);
            QString pnoty = QString::number(ronot[1]);
            QString pnotz = QString::number(ronot[2]);
            ui->plainTextEdit_5->appendPlainText("pnotx = " + pnotx + "[cm]");
            ui->plainTextEdit_5->appendPlainText("pnoty = " + pnoty + "[cm]");
            ui->plainTextEdit_5->appendPlainText("pnotz = " + pnotz + "[cm]");

            QString p1 = QString::number(parameters[0]);
            QString p2 = QString::number(parameters[1]);
            QString p3 = QString::number(parameters[2]);
            QString p4 = QString::number(parameters[3]);
            QString p5 = QString::number(parameters[4]);
            ui->plainTextEdit_5->appendPlainText("");
            ui->plainTextEdit_5->appendPlainText("Calculated Values");
            ui->plainTextEdit_5->appendPlainText("beta  = " + p1 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("alpha = " + p2 + "[radians]");
            ui->plainTextEdit_5->appendPlainText("tx    = " + p3 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("ty    = " + p4 + "[cm]");
            ui->plainTextEdit_5->appendPlainText("tz    = " + p5 + "[cm]");

             ui->plainTextEdit_5->appendPlainText("");
        }


    }


    ui->plainTextEdit_15->appendPlainText("Parameters Calculated");
    ui->pushButton_19->setEnabled(true);
    Fparameters = parameters;
}

//Plot Eigen1
void MainWindow::on_pushButton_13_clicked()
{
    arma::vec Eigenvalue1;
    Eigenvalue1 = Eigenvalues.col(0);
    plot PlotEigen1(Eigenvalue1);
}

//Plot Eigen2
void MainWindow::on_pushButton_14_clicked()
{
    arma::vec Eigenvalue2;
    Eigenvalue2 = Eigenvalues.col(1);
    plot PlotEigen2(Eigenvalue2);
}

//Plot Eigen3
void MainWindow::on_pushButton_15_clicked()
{
    arma::vec Eigenvalue3;
    Eigenvalue3 = Eigenvalues.col(2);
    plot PlotEigen3(Eigenvalue3);
}

//Plot Eigen4
void MainWindow::on_pushButton_16_clicked()
{
    arma::vec Eigenvalue4;
    Eigenvalue4 = Eigenvalues.col(3);
    plot PlotEigen4(Eigenvalue4);
}

//Plot Eigen5
void MainWindow::on_pushButton_17_clicked()
{
    arma::vec Eigenvalue5;
    Eigenvalue5 = Eigenvalues.col(4);
    plot PlotEigen5(Eigenvalue5);
}


//==========================================ChiSquare Map Page======================================================================================//
//=======================================================================================================================================================//

//Map ChiSquare
void MainWindow::on_pushButton_18_clicked()
{
    //Plot Parameters
    arma::vec PlotParameters; PlotParameters.set_size(6);
    PlotParameters(0) = ui->lineEdit_29->text().toDouble();
    PlotParameters(1) = ui->lineEdit_30->text().toDouble();
    PlotParameters(2) = ui->lineEdit_31->text().toDouble();
    PlotParameters(3) = ui->lineEdit_32->text().toDouble();
    PlotParameters(4) = ui->lineEdit_33->text().toDouble();
    PlotParameters(5) = ui->lineEdit_34->text().toDouble();

    //Get Values
    int IterationsIndex = ui->lineEdit_28->text().toInt();
    double FocalLength = ui->lineEdit_27->text().toDouble();
    arma::vec parameters; parameters.set_size(5);
    parameters(0) = ui->lineEdit_22->text().toDouble();
    parameters(1) = ui->lineEdit_23->text().toDouble();
    parameters(2) = ui->lineEdit_24->text().toDouble();
    parameters(3) = ui->lineEdit_25->text().toDouble();
    parameters(4) = ui->lineEdit_26->text().toDouble();

    arma::vec initialguess; initialguess = parameters;
    //Repeating Values
    double InvFocalLength  = 1./FocalLength;
    double InvFocalLength2 = 1./(FocalLength*FocalLength);
    int NumberPoints= Data.n_rows;

    calculate CS;
    connect(this, SIGNAL(SayFocalLength(double)), &CS, SLOT(ListenFocalLength(double)));
    connect(this, SIGNAL(SayParameters(arma::vec)), &CS, SLOT(ListenParameters(arma::vec)));
    connect(this, SIGNAL(SayData(arma::mat)), &CS, SLOT(ListenData(arma::mat)));
    connect(this, SIGNAL(SaySurfaceType(QString)), &CS, SLOT(ListenSurfaceType(QString)));

    emit SayFocalLength(FocalLength);
    emit SayParameters(parameters);
    emit SayData(Data);
    emit SaySurfaceType(SurfaceType);


    if(AnalysisType == "Standard")
    {
        //Dimensions of grid to scan
        double startingtx       = parameters[2] - PlotParameters[0];
        double finishingtx      = parameters[2] + PlotParameters[1];
        double startingty       = parameters[3] - PlotParameters[3];
        double finishingty      = parameters[3] + PlotParameters[4];

        int numberpointsx       = (finishingtx -startingtx)/PlotParameters[2];
        int numberpointsy       = (finishingty -startingty)/PlotParameters[5];
        int totalnumberofpoints = (numberpointsx+1)*(numberpointsy+1);

        //Containers for Data
        mglData tx(totalnumberofpoints);
        mglData ty(totalnumberofpoints);
        mglData XS(totalnumberofpoints);
        arma::mat ParametersChiS; ParametersChiS.set_size(totalnumberofpoints,2);
        arma::vec X; X.set_size(totalnumberofpoints);
        arma::vec chisquares; chisquares.set_size(totalnumberofpoints);
        int w = 0;

        //Table for Values
        //EigenValue Table
        ui->tableWidget_4->setRowCount(totalnumberofpoints);
        ui->tableWidget_4->setColumnCount(3);
        QStringList TableHeader; TableHeader<<"X Value"<<"Y Value"<<"Chi Square";
        ui->tableWidget_4->setHorizontalHeaderLabels(TableHeader);
        ui->tableWidget_4->setShowGrid(false);
        ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(int i = 0; i<= numberpointsx; i++)
        {
            for(int k = 0; k<=numberpointsy; k++)
            {

                parameters[2] = startingtx + (i*PlotParameters[2]);
                parameters[3] = startingty + (k*PlotParameters[5]);

                tx.a[w] = parameters[2];
                ty.a[w] = parameters[3];

                double ChiS;

                for(int j = 0; j<IterationsIndex; j++)
                {
                    CS.process();

                    double ChiS = CS.Get_ChiS();
                    arma::vec V = CS.Get_V();
                    arma::mat M = CS.Get_M();

                    ChiS = InvFocalLength2*ChiS;
                    V.rows(0,1) = InvFocalLength2*V.rows(0,1);
                    V.rows(2,4) = InvFocalLength*V.rows(2,4);
                    M.submat(arma::span(0,1),arma::span(0,1)) = InvFocalLength2*M.submat(arma::span(0,1),arma::span(0,1));
                    M.submat(arma::span(0,1),arma::span(2,4)) = InvFocalLength*M.submat(arma::span(0,1),arma::span(2,4));
                    M.submat(arma::span(2,4),arma::span(0,1)) = InvFocalLength*M.submat(arma::span(2,4),arma::span(0,1));		//M [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1]

                    arma::vec eigenvalues; arma::mat eigenvectors;
                    arma::eig_sym(eigenvalues, eigenvectors, M);

                    arma::vec delta_parameters; delta_parameters.set_size(5);
                    delta_parameters = -(inv(M))*V;
                    delta_parameters.rows(2,4) = FocalLength*delta_parameters.rows(2,4);

                    parameters = parameters + delta_parameters;

                    emit SayParameters(parameters);             //listen calculate


                }

                //Fill Table
                QTableWidgetItem *x = new QTableWidgetItem();
                x->setData(Qt::DisplayRole,parameters(2));
                ui->tableWidget_4->setItem(w,0,x);

                QTableWidgetItem *y = new QTableWidgetItem();
                y->setData(Qt::DisplayRole,parameters(3));
                ui->tableWidget_4->setItem(w,1,y);

                QTableWidgetItem *cs = new QTableWidgetItem();
                cs->setData(Qt::DisplayRole,ChiS);
                ui->tableWidget_4->setItem(w,2,cs);

                ParametersChiS(w,0) = parameters(2);
                ParametersChiS(w,1) = parameters(3);
                chisquares(w) = ChiS;
                double RMS = sqrt(ChiS/InvFocalLength2/NumberPoints)*1E+4; 					// RMS of Delta Z in micrometers for each point
                XS.a[w] = RMS;														//Z axis in plot
                X(w) = RMS;															//range of colorbar in plot
                w = w + 1;
            }

        }

        plot ChiSMap(numberpointsx, numberpointsy, startingtx, finishingtx, startingty, finishingty, XS, tx, ty, ParametersChiS, initialguess, chisquares);

        //Actual and Calculated
        arma::uword indexofminChiS;
        double minvalueChiS = chisquares.min(indexofminChiS);

        QString x = QString::number(ParametersChiS(indexofminChiS,0));
        QString y = QString::number(ParametersChiS(indexofminChiS,1));
        QString cs = QString::number(minvalueChiS);
        ui->plainTextEdit_3->appendPlainText("Calculated CS");
        ui->plainTextEdit_3->appendPlainText("x = " + x );
        ui->plainTextEdit_3->appendPlainText("y = " + y );
        ui->plainTextEdit_3->appendPlainText("CS = " + cs);

        QString xi = QString::number(initialguess[2]);
        QString yi = QString::number(initialguess[3]);
        QString csi = QString::number(minvalueChiS);
        ui->plainTextEdit_3->appendPlainText("Ideal CS");
        ui->plainTextEdit_3->appendPlainText("x = " + xi );
        ui->plainTextEdit_3->appendPlainText("y = " + yi );

    }

    if(AnalysisType == "Set Point")
    {

        //Dimensions of grid to scan
        double startingtx       = parameters[2] - PlotParameters[0];
        double finishingtx      = parameters[2] + PlotParameters[1];
        double startingty       = parameters[3] - PlotParameters[3];
        double finishingty      = parameters[3] + PlotParameters[4];

        int numberpointsx       = (finishingtx -startingtx)/PlotParameters[2];
        int numberpointsy       = (finishingty -startingty)/PlotParameters[5];
        int totalnumberofpoints = (numberpointsx+1)*(numberpointsy+1);

        //Containers for Data
        mglData tx(totalnumberofpoints);
        mglData ty(totalnumberofpoints);
        mglData XS(totalnumberofpoints);
        arma::mat ParametersChiS; ParametersChiS.set_size(totalnumberofpoints,2);
        arma::vec X; X.set_size(totalnumberofpoints);
        arma::vec chisquares; chisquares.set_size(totalnumberofpoints);
        int w = 0;

        //Table for Values
        //EigenValue Table
        ui->tableWidget_4->setRowCount(totalnumberofpoints);
        ui->tableWidget_4->setColumnCount(3);
        QStringList TableHeader; TableHeader<<"X Value"<<"Y Value"<<"Chi Square";
        ui->tableWidget_4->setHorizontalHeaderLabels(TableHeader);
        ui->tableWidget_4->setShowGrid(false);
        ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);

        for(int i = 0; i<= numberpointsx; i++)
        {
            for(int k = 0; k<=numberpointsy; k++)
            {

                parameters[2] = startingtx + (i*PlotParameters[2]);
                parameters[3] = startingty + (k*PlotParameters[5]);

                tx.a[w] = parameters[2];
                ty.a[w] = parameters[3];

                double ChiS;

                arma::vec V3; V3.set_size(3);
                arma::mat M3; M3.set_size(3,3);

                for(int j = 0; j<IterationsIndex; j++)
                {
                    CS.process();

                    ChiS = CS.Get_ChiS();
                    arma::vec V = CS.Get_V();
                    arma::mat M = CS.Get_M();

                    ChiS = InvFocalLength2*ChiS;
                    V.rows(0,1) = InvFocalLength2*V.rows(0,1);
                    V.rows(2,4) = InvFocalLength*V.rows(2,4);
                    M.submat(arma::span(0,1),arma::span(0,1)) = InvFocalLength2*M.submat(arma::span(0,1),arma::span(0,1));
                    M.submat(arma::span(0,1),arma::span(2,4)) = InvFocalLength*M.submat(arma::span(0,1),arma::span(2,4));
                    M.submat(arma::span(2,4),arma::span(0,1)) = InvFocalLength*M.submat(arma::span(2,4),arma::span(0,1));		//M [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1] [1,1,1,1,1]

                    V3.rows(0,1) = V.rows(0,1);
                    V3(2) = V(4);

                    M3.submat(arma::span(0,1),arma::span(0,1)) = M.submat(arma::span(0,1),arma::span(0,1));
                    M3(0,2) = M(0,4);
                    M3(1,2) = M(1,4);
                    M3(2,0) = M(4,0);
                    M3(2,1) = M(4,1);
                    M3(2,2) = M(4,4);

                    arma::vec delta_parameters;
                    delta_parameters = -(inv(M3))*V3;
                    delta_parameters(2) = (FocalLength)*delta_parameters(2);			//[1,1,cm]
                    delta_parameters.insert_rows(2,2);

                    parameters = parameters + delta_parameters;

                    //Emit
                    emit SayParameters(parameters);     //listen calculate

                }

                //Fill Table
                QTableWidgetItem *x = new QTableWidgetItem();
                x->setData(Qt::DisplayRole,parameters(2));
                ui->tableWidget_4->setItem(w,0,x);

                QTableWidgetItem *y = new QTableWidgetItem();
                y->setData(Qt::DisplayRole,parameters(3));
                ui->tableWidget_4->setItem(w,1,y);

                QTableWidgetItem *cs = new QTableWidgetItem();
                cs->setData(Qt::DisplayRole,ChiS);
                ui->tableWidget_4->setItem(w,2,cs);

                ParametersChiS(w,0) = parameters(2);
                ParametersChiS(w,1) = parameters(3);
                chisquares(w) = ChiS;
                double RMS = sqrt(ChiS/InvFocalLength2/NumberPoints)*1E+4; 					// RMS of Delta Z in micrometers for each point
                XS.a[w] = RMS;														//Z axis in plot
                X(w) = RMS;															//range of colorbar in plot
                w = w + 1;
            }

        }

        plot ChiSMap(numberpointsx, numberpointsy, startingtx, finishingtx, startingty, finishingty, XS, tx, ty, ParametersChiS, initialguess, chisquares);

        //Actual and Calculated
        arma::uword indexofminChiS;
        double minvalueChiS = chisquares.min(indexofminChiS);

        QString x = QString::number(ParametersChiS(indexofminChiS,0));
        QString y = QString::number(ParametersChiS(indexofminChiS,1));
        QString cs = QString::number(minvalueChiS);
        ui->plainTextEdit_3->appendPlainText("Calculated CS");
        ui->plainTextEdit_3->appendPlainText("x = " + x );
        ui->plainTextEdit_3->appendPlainText("y = " + y );
        ui->plainTextEdit_3->appendPlainText("CS = " + cs);

        QString xi = QString::number(initialguess[2]);
        QString yi = QString::number(initialguess[3]);
        QString csi = QString::number(minvalueChiS);
        ui->plainTextEdit_3->appendPlainText("Ideal CS");
        ui->plainTextEdit_3->appendPlainText("x = " + xi );
        ui->plainTextEdit_3->appendPlainText("y = " + yi );

    }


    ui->plainTextEdit_15->appendPlainText("Chi Square Plotted");
}


//==========================================Residuals Page======================================================================================//
//=======================================================================================================================================================//

//calculate residuals
void MainWindow::on_pushButton_19_clicked()
{
    CalculateResiduals CR;
    connect(this, SIGNAL(SayData(arma::mat)), &CR, SLOT(ListenData(arma::mat)));
    connect(this, SIGNAL(SayFocalLength(double)), &CR, SLOT(ListenFocalLength(double)));
    connect(this, SIGNAL(SayFinalParameters(arma::vec)), &CR, SLOT(ListenFinalParameters(arma::vec)));

    emit SayData(ResidualsData);
    double FocalLength = ui->lineEdit_27->text().toDouble();
    emit SayFocalLength(FocalLength);
    emit SayFinalParameters(Fparameters);

    CR.execute();
    LoadedResiduals = CR.Get_Residuals();

    //Get Range
    arma::vec maxrange; maxrange.set_size(3);
    arma::vec minrange; minrange.set_size(3);
    maxrange = (max(LoadedResiduals).t());
    minrange = (min(LoadedResiduals).t());

    //Values
    int np = LoadedResiduals.n_rows;
    QString NP = QString::number(np);
    QString maxx = QString::number(maxrange(0));
    QString maxy = QString::number(maxrange(1));
    QString maxz = QString::number(maxrange(2));
    QString minx = QString::number(minrange(0));
    QString miny = QString::number(minrange(1));
    QString minz = QString::number(minrange(2));

    ui->plainTextEdit_6->clear();
    ui->plainTextEdit_6->appendPlainText("Number of Points = " + NP);
    ui->plainTextEdit_6->appendPlainText("Range x = " + maxx + "   " + minx );
    ui->plainTextEdit_6->appendPlainText("Range y = " + maxy + "   " + miny );
    ui->plainTextEdit_6->appendPlainText("Range z = " + maxz + "   " + minz );
    ui->plainTextEdit_6->appendPlainText(" ");

    for(int i = 0; i<np; i++)
    {
        double x = LoadedResiduals(i,0);
        double y = LoadedResiduals(i,1);
        double z = LoadedResiduals(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
    }

    //Validator
    QValidator *IntegerInput = new QIntValidator(1,np,this);
    ui->lineEdit_36->setValidator(IntegerInput);

    //ui->tab_9->setEnabled(true);  Page for error obsolete error mode page
    ui->scrollArea_7->setEnabled(true);     //error mode page

    CleanResiduals = LoadedResiduals;

    ui->plainTextEdit_15->appendPlainText("Residuals Calculated");
}

//LoadResiduals
void MainWindow::on_pushButton_20_clicked()
{
    //String to open window to get fileName
    QString ResidualsFile = QFileDialog::getOpenFileName(this, tr("Open Residuals File"), "/home/", tr("Text Files (*.txt)"));
    if(ResidualsFile.isEmpty())
    {
        QString Info = "Warning";
        QString Message = "No File Selected";
        QMessageBox::warning(0,Info, Message, QMessageBox::Ok);
    }

    else
    {
        LoadResiduals GetResiduals(ResidualsFile);
        LoadedResiduals = GetResiduals.Get_Data();
        arma::vec maxrange = GetResiduals.Get_Max_Range();
        arma::vec minrange = GetResiduals.Get_Min_Range();

        //Values
        int np = LoadedResiduals.n_rows;
        QString NP = QString::number(np);
        QString maxx = QString::number(maxrange(0));
        QString maxy = QString::number(maxrange(1));
        QString maxz = QString::number(maxrange(2));
        QString minx = QString::number(minrange(0));
        QString miny = QString::number(minrange(1));
        QString minz = QString::number(minrange(2));
        ui->plainTextEdit_6->clear();
        ui->plainTextEdit_6->appendPlainText("Number of Points = " + NP);
        ui->plainTextEdit_6->appendPlainText("Range x = " + maxx + "   " + minx );
        ui->plainTextEdit_6->appendPlainText("Range y = " + maxy + "   " + miny );
        ui->plainTextEdit_6->appendPlainText("Range z = " + maxz + "   " + minz );
        ui->plainTextEdit_6->appendPlainText(" ");

        for(int i = 0; i<np; i++)
        {
            double x = LoadedResiduals(i,0);
            double y = LoadedResiduals(i,1);
            double z = LoadedResiduals(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
        }


        //Validator
        QValidator *IntegerInput = new QIntValidator(1,np,this);
        ui->lineEdit_36->setValidator(IntegerInput);

        //ui->tab_9->setEnabled(true); Page for error obsolete error mode page
        ui->scrollArea_7->setEnabled(true);     //error mode page

        CleanResiduals = LoadedResiduals;

        ui->plainTextEdit_15->appendPlainText("Residuals Loaded: " + ResidualsFile);

    }

}

//Multiply Residuals
void MainWindow::on_pushButton_21_clicked()
{
    double factor = ui->lineEdit_35->text().toDouble();
    LoadedResiduals =factor*LoadedResiduals;
    int np = LoadedResiduals.n_rows;

    //Range

        arma::vec maxvalues; maxvalues.set_size(3);
        arma::vec minvalues; minvalues.set_size(3);
        maxvalues = (max(LoadedResiduals).t());
        minvalues = (min(LoadedResiduals).t());

        //Values
        QString NP = QString::number(np);
        QString maxx = QString::number(maxvalues(0));
        QString maxy = QString::number(maxvalues(1));
        QString maxz = QString::number(maxvalues(2));
        QString minx = QString::number(minvalues(0));
        QString miny = QString::number(minvalues(1));
        QString minz = QString::number(minvalues(2));
        ui->plainTextEdit_6->clear();
        ui->plainTextEdit_6->appendPlainText("Number of Points = " + NP);
        ui->plainTextEdit_6->appendPlainText("Range x = " + maxx + "   " + minx );
        ui->plainTextEdit_6->appendPlainText("Range y = " + maxy + "   " + miny );
        ui->plainTextEdit_6->appendPlainText("Range z = " + maxz + "   " + minz );
        ui->plainTextEdit_6->appendPlainText(" ");

        for(int i = 0; i<np; i++)
        {
            double x = LoadedResiduals(i,0);
            double y = LoadedResiduals(i,1);
            double z = LoadedResiduals(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
        }

        QString factoritem = QString::number(factor);
        ui->plainTextEdit_15->appendPlainText("Residuals Scaled by = " + factoritem);

}

//Delete Point
void MainWindow::on_pushButton_22_clicked()
{
    int deleterow = ui->lineEdit_36->text().toInt();
    LoadedResiduals.shed_row(deleterow-1);

    //Values
    int np = LoadedResiduals.n_rows;
    arma::vec maxrange; maxrange.set_size(3);
    arma::vec minrange; minrange.set_size(3);
    maxrange = (max(LoadedResiduals).t());
    minrange = (min(LoadedResiduals).t());
    QString NP = QString::number(np);
    QString maxx = QString::number(maxrange(0));
    QString maxy = QString::number(maxrange(1));
    QString maxz = QString::number(maxrange(2));
    QString minx = QString::number(minrange(0));
    QString miny = QString::number(minrange(1));
    QString minz = QString::number(minrange(2));
    ui->plainTextEdit_6->clear();
    ui->plainTextEdit_6->appendPlainText("Number of Points = " + NP);
    ui->plainTextEdit_6->appendPlainText("Range x = " + maxx + "   " + minx );
    ui->plainTextEdit_6->appendPlainText("Range y = " + maxy + "   " + miny );
    ui->plainTextEdit_6->appendPlainText("Range z = " + maxz + "   " + minz );
    ui->plainTextEdit_6->appendPlainText(" ");

    for(int i = 0; i<np; i++)
    {
        double x = LoadedResiduals(i,0);
        double y = LoadedResiduals(i,1);
        double z = LoadedResiduals(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
    }

    //Validator
    QValidator *IntegerInput = new QIntValidator(1,np,this);
    ui->lineEdit_36->setValidator(IntegerInput);

    QString f = QString::number(deleterow);
    ui->plainTextEdit_15->appendPlainText("Residuals Point Removed = " + f);

}

//Rotate
void MainWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked())
    {
        LoadedResiduals.col(1) = (-1)*LoadedResiduals.col(1);
        LoadedResiduals.col(2) = (-1)*LoadedResiduals.col(2);
        int nop = LoadedResiduals.n_rows;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(LoadedResiduals).t());
            minvalues = (min(LoadedResiduals).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit_6->clear();
            ui->plainTextEdit_6->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit_6->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit_6->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit_6->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit_6->appendPlainText("");
        }

        //Points
        for(int i = 0; i<nop; i++)
        {
            double x = LoadedResiduals(i,0);
            double y = LoadedResiduals(i,1);
            double z = LoadedResiduals(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Residuals Rotated");

    }

    if(!ui->checkBox_3->isChecked())
    {
        LoadedResiduals.col(1) = (-1)*LoadedResiduals.col(1);
        LoadedResiduals.col(2) = (-1)*LoadedResiduals.col(2);
        int nop = LoadedResiduals.n_rows;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(LoadedResiduals).t());
            minvalues = (min(LoadedResiduals).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit_6->clear();
            ui->plainTextEdit_6->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit_6->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit_6->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit_6->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit_6->appendPlainText("");
        }

        //Points
        for(int i = 0; i<nop; i++)
        {
            double x = LoadedResiduals(i,0);
            double y = LoadedResiduals(i,1);
            double z = LoadedResiduals(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Residuals Rotated Back");
}

}

//Reflect
void MainWindow::on_checkBox_4_clicked()
{
    if(ui->checkBox_3->isChecked())
    {
        LoadedResiduals.col(2) = (-1)*LoadedResiduals.col(2);
        int nop = LoadedResiduals.n_rows;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(LoadedResiduals).t());
            minvalues = (min(LoadedResiduals).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit_6->clear();
            ui->plainTextEdit_6->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit_6->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit_6->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit_6->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit_6->appendPlainText("");
        }

        //Points
        for(int i = 0; i<nop; i++)
        {
            double x = LoadedResiduals(i,0);
            double y = LoadedResiduals(i,1);
            double z = LoadedResiduals(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Residuals Reflected");

    }

    if(!ui->checkBox_3->isChecked())
    {
        LoadedResiduals.col(2) = (-1)*LoadedResiduals.col(2);
        int nop = LoadedResiduals.n_rows;

        //Range
        {
            arma::vec maxvalues; maxvalues.set_size(3);
            arma::vec minvalues; minvalues.set_size(3);
            maxvalues = (max(LoadedResiduals).t());
            minvalues = (min(LoadedResiduals).t());

            //TextBrower
            QString n = QString::number(nop);
            QString maxx = QString::number(maxvalues(0));
            QString maxy = QString::number(maxvalues(1));
            QString maxz = QString::number(maxvalues(2));
            QString minx = QString::number(minvalues(0));
            QString miny = QString::number(minvalues(1));
            QString minz = QString::number(minvalues(2));

            ui->plainTextEdit_6->clear();
            ui->plainTextEdit_6->appendPlainText("Number of Points = " + n);
            ui->plainTextEdit_6->appendPlainText("Range x =  " + minx + "  " +maxx);
            ui->plainTextEdit_6->appendPlainText("Range y =  " + miny + "  " +maxy);
            ui->plainTextEdit_6->appendPlainText("Range z =  " + minz + "  " +maxz);
            ui->plainTextEdit_6->appendPlainText("");
        }

        //Points
        for(int i = 0; i<nop; i++)
        {
            double x = LoadedResiduals(i,0);
            double y = LoadedResiduals(i,1);
            double z = LoadedResiduals(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
        }

         ui->plainTextEdit_15->appendPlainText("Residuals Reflected Back");
}

}

//Undo
void MainWindow::on_pushButton_23_clicked()
{
    LoadedResiduals = CleanResiduals;
    int nop = LoadedResiduals.n_rows;

    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);

    //Range
    {
        arma::vec maxvalues; maxvalues.set_size(3);
        arma::vec minvalues; minvalues.set_size(3);
        maxvalues = (max(LoadedResiduals).t());
        minvalues = (min(LoadedResiduals).t());

        //TextBrower
        QString n = QString::number(nop);
        QString maxx = QString::number(maxvalues(0));
        QString maxy = QString::number(maxvalues(1));
        QString maxz = QString::number(maxvalues(2));
        QString minx = QString::number(minvalues(0));
        QString miny = QString::number(minvalues(1));
        QString minz = QString::number(minvalues(2));

        ui->plainTextEdit_6->clear();
        ui->plainTextEdit_6->appendPlainText("Number of Points = " + n);
        ui->plainTextEdit_6->appendPlainText("Range x =  " + minx + "  " +maxx);
        ui->plainTextEdit_6->appendPlainText("Range y =  " + miny + "  " +maxy);
        ui->plainTextEdit_6->appendPlainText("Range z =  " + minz + "  " +maxz);
        ui->plainTextEdit_6->appendPlainText("");
    }

    //Points
    for(int i = 0; i<nop; i++)
    {
        double x = LoadedResiduals(i,0);
        double y = LoadedResiduals(i,1);
        double z = LoadedResiduals(i,2);

        QString sx = QString::number(x,'e',6);
        QString sy = QString::number(y,'e',6);
        QString sz = QString::number(z,'e',6);

        ui->plainTextEdit_6->appendPlainText(sx + "   " + sy + "   " + sz);
    }

    //Validator
    QValidator *IntegerInput = new QIntValidator(1,nop,this);
    ui->lineEdit_36->setValidator(IntegerInput);

    ui->plainTextEdit_15->appendPlainText("Residuals Restored");
}

//Save Residuals
void MainWindow::on_pushButton_24_clicked()
{
    //Save File
    QString DataFileSave = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (DataFileSave.isEmpty())
          return;

    QFile SaveCalculations(DataFileSave);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->plainTextEdit_6->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

        ui->plainTextEdit_15->appendPlainText("Residuals Saved: " + DataFileSave);
}


//3D
void MainWindow::on_radioButton_22_clicked()
{
    ResidualsPlot = "3D";
}

//Contour
void MainWindow::on_radioButton_23_clicked()
{
    ResidualsPlot = "Contour";
}

//Dots
void MainWindow::on_radioButton_24_clicked()
{
    ResidualsPlot = "Dots";
}

//Plot Residuals
void MainWindow::on_pushButton_29_clicked()
{
    QString Title = ui->lineEdit_39->text();
    QString Units = ui->lineEdit_40->text();
    plot Plot(LoadedResiduals, Units, ResidualsPlot, Title);

    ui->plainTextEdit_15->appendPlainText("Residuals Plotted " + ResidualsPlot);
}

//=========================================NOT IN USE======================================================================================================//
//==========================================Parameters and Modes Page======================================================================================//
//=======================================================================================================================================================//

//K over M
void MainWindow::on_radioButton_25_clicked()
{
    PlotType = "ErrorModes";
}

//Magnitude
void MainWindow::on_radioButton_26_clicked()
{
    PlotType = "Magnitude";
}

//Plot
void MainWindow::on_pushButton_30_clicked()
{
    //Get Parameters to Pass to ModeAnalysis
    int K = ui->lineEdit_46->text().toInt();
    int M = ui->lineEdit_45->text().toInt();
    int SpanOfM = ui->lineEdit_47->text().toInt();
    R.set_size(2);
    R[0] = ui->lineEdit_41->text().toDouble();
    R[1] = ui->lineEdit_42->text().toDouble();
    QString PlotTitle = ui->lineEdit_48->text();

    //Range for K & M modes
    ui->spinBox->setRange(0,K);
    ui->horizontalSlider->setRange(0,K);
    ui->spinBox_2->setRange(0,M);
    ui->horizontalSlider_2->setRange(0,M);

    //Emit
    ModeAnalysis Modes;
    connect(this, SIGNAL(SayK(int)), &Modes, SLOT(ListenK(int)));
    connect(this, SIGNAL(SayM(int)), &Modes, SLOT(ListenM(int)));
    connect(this, SIGNAL(SaySpanM(int)), &Modes, SLOT(ListenSpanM(int)));
    connect(this, SIGNAL(SayRadius(arma::vec)), &Modes, SLOT(ListenRadius(arma::vec)));
    connect(this, SIGNAL(SayTitle(QString)), &Modes, SLOT(ListenTitle(QString)));
    connect(this, SIGNAL(SayResiduals(arma::mat)), &Modes, SLOT(ListenResiduals(arma::mat)));
    connect(this, SIGNAL(SayPlotType(QString)), &Modes, SLOT(ListenErrorModesPlot(QString)));

    emit SayK(K);
    emit SayM(M);
    emit SaySpanM(SpanOfM);
    emit SayRadius(R);
    emit SayTitle(PlotTitle);
    emit SayResiduals(LoadedResiduals);
    emit SayPlotType(PlotType);

    //Pass to Mode Analysis
    Modes.process();
    Akm = Modes.Get_Akm();
    arma::mat Pkm = Modes.Get_Pkm();
    SphericalData = Modes.Get_SphericalData();
    arma::mat Amplitudes = Modes.Get_Amplitudes();


    //Text
    ui->plainTextEdit_7->clear();
    QString ks = QString::number(K);
    QString ms = QString::number(M);
    ui->plainTextEdit_7->appendPlainText("Radial Modes = " + ks);
    ui->plainTextEdit_7->appendPlainText("Angular Modes = " + ms);
    QString sm = QString::number(SpanOfM);
    ui->plainTextEdit_7->appendPlainText("Display Angular Modes = " + sm);
    QString rmin = QString::number(R[0]);
    QString rmax = QString::number(R[1]);
    ui->plainTextEdit_7->appendPlainText("Rmin = " + rmin);
    ui->plainTextEdit_7->appendPlainText("Rmax = " + rmax);

    //Amplitudes Table
    ui->tableWidget_5->setRowCount(SpanOfM+1);
    ui->tableWidget_5->setColumnCount(3);
    QStringList TableHeader; TableHeader<<"M Mode"<<"Min Value"<<"Max Value";
    ui->tableWidget_5->setHorizontalHeaderLabels(TableHeader);
    ui->tableWidget_5->verticalHeader()->setVisible(false);
    ui->tableWidget_5->setShowGrid(false);
    ui->tableWidget_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int np = Amplitudes.n_rows;
    for(int i = 0; i<np; i++)
    {
        QTableWidgetItem *M = new QTableWidgetItem();
        M->setData(Qt::DisplayRole,Amplitudes(i,0));
        ui->tableWidget_5->setItem(i,0,M);

        QTableWidgetItem *min = new QTableWidgetItem();
        min->setData(Qt::DisplayRole,Amplitudes(i,1));
        ui->tableWidget_5->setItem(i,1,min);

        QTableWidgetItem *max = new QTableWidgetItem();
        max->setData(Qt::DisplayRole,Amplitudes(i,2));
        ui->tableWidget_5->setItem(i,2,max);
    }

    //Total Amplitudes
    int nop = Pkm.n_rows;
    int index = 0;
    ui->tableWidget_6->setRowCount((SpanOfM+1)*(2*K+1));
    ui->tableWidget_6->setColumnCount(3);
    QStringList TableHeader2; TableHeader2<<"M Mode"<<"K Mode"<<"Amplitude";
    ui->tableWidget_6->setHorizontalHeaderLabels(TableHeader2);
    ui->tableWidget_6->verticalHeader()->setVisible(false);
    ui->tableWidget_6->setShowGrid(false);
    ui->tableWidget_6->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int j = 0; j<=SpanOfM; j++)
    {
        for(int i = 0;i<nop; i++)
            {
                if(Pkm(i,1) == j )
                        {
                            QTableWidgetItem *m = new QTableWidgetItem();
                            m->setData(Qt::DisplayRole,Pkm(i,1));
                            ui->tableWidget_6->setItem(index,0,m);

                            QTableWidgetItem *k = new QTableWidgetItem();
                            k->setData(Qt::DisplayRole,Pkm(i,0));
                            ui->tableWidget_6->setItem(index,1,k);

                            QTableWidgetItem *kvalue = new QTableWidgetItem();
                            kvalue->setData(Qt::DisplayRole,Pkm(i,2));
                            ui->tableWidget_6->setItem(index,2,kvalue);
                            index = index + 1;
                        }
            }
    }

    ui->plainTextEdit_15->appendPlainText("Error Modes Plotted " + PlotType);

}

//K mode
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    QString AKtext = QString("K Mode %1").arg(arg1);
    ui->label_72->setText(AKtext);
    Ak = ui->spinBox->value();
}

//M Mode
void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    QString AMtext = QString("M Mode %1").arg(arg1);
    ui->label_73->setText(AMtext);
    Am = ui->spinBox_2->value();
}

//Individual
void MainWindow::on_radioButton_27_clicked()
{
    PlotTypeFactors = "Individual";
}

//Combined
void MainWindow::on_radioButton_28_clicked()
{
     PlotTypeFactors = "Combined";
}


//Modes
void MainWindow::on_pushButton_31_clicked()
{
    m_checkBoxList.clear();
    ModeFactors Factors;
    connect(this, SIGNAL(SayResiduals(arma::mat)), &Factors, SLOT(ListenResiduals(arma::mat)));
    connect(this, SIGNAL(SayAKM(arma::mat)), &Factors, SLOT(ListenAKM(arma::mat)));
    connect(this, SIGNAL(SaySphericalData(arma::mat)), &Factors, SLOT(ListenSphericalData(arma::mat)));
    connect(this, SIGNAL(SayK(int)), &Factors, SLOT(ListenK(int)));
    connect(this, SIGNAL(SayM(int)), &Factors, SLOT(ListenM(int)));
    connect(this, SIGNAL(SayRadius(arma::vec)), &Factors, SLOT(ListenRadius(arma::vec)));
    connect(this, SIGNAL(SayPlotType(QString)), &Factors, SLOT(ListenPlotType(QString)));

    emit SayResiduals(LoadedResiduals);
    emit SayAKM(Akm);
    emit SaySphericalData(SphericalData);
    emit SayK(Ak);
    emit SayM(Am);
    emit SayRadius(R);
    emit SayPlotType(PlotTypeFactors);

    Factors.process();
    arma::mat AA = Factors.Get_Matrix();
    Weights = Factors.Get_Weights();
    arma::mat Amplitudes = Factors.Get_Amplitudes();
    A = Factors.Get_A();

    //Add Buttons
    int NumberModes = Amplitudes.n_rows;

    QWidget *wid = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    for(int i=0; i<NumberModes; i++)
    {
        int k = Amplitudes(i,0);
        int m = Amplitudes(i,1);
        QString ks = QString::number(k);
        QString ms = QString::number(m);
        QString position = QString::number(i);
        QString mode = "A"+ks+ms;
        Selected1.append(mode);
        //emit SayModeToDisplay(mode);

        QCheckBox *checkBox = new QCheckBox(mode);
        connect(checkBox, SIGNAL(toggled(bool)), this, SLOT(monitorCheckStatus()));
        m_checkBoxList.append(checkBox);

        layout->addWidget(checkBox);
        updateGeometry();
    }

    wid->setLayout(layout);
    ui->scrollArea->setWidget(wid);

    //MatrixTable
    int MatrixSize = (Ak+1)*(Am+1);
    ui->tableWidget_7->setRowCount(MatrixSize);
    ui->tableWidget_7->setColumnCount(MatrixSize);
    for(int k = 0; k<MatrixSize; k++)
    {
        for(int m = 0; m<MatrixSize; m++)
        {
            QTableWidgetItem *value = new QTableWidgetItem();
            value->setData(Qt::DisplayRole,AA(k,m));
            ui->tableWidget_7->setItem(k,m,value);
        }
    }

    //Weight Table
    int weights = Weights.n_rows;
    ui->tableWidget_8->setRowCount(weights);
    ui->tableWidget_8->setColumnCount(1);
    for(int i=0; i<weights; i++)
    {
        QTableWidgetItem *value = new QTableWidgetItem();
        value->setData(Qt::DisplayRole,Weights(i));
        ui->tableWidget_8->setItem(i,0,value);
    }

    //Amplitudes Table
    if(PlotTypeFactors == "Individual")
    {
        int NumberModes = Amplitudes.n_rows;
        ui->tableWidget_9->setRowCount(NumberModes);
        ui->tableWidget_9->setColumnCount(3);
        QStringList TableHeader; TableHeader<<"Mode"<<"Min Value"<<"Max Value";
        ui->tableWidget_9->setHorizontalHeaderLabels(TableHeader);
        for(int i=0; i<NumberModes; i++)
        {
            int k = Amplitudes(i,0);
            int m = Amplitudes(i,1);
            QString ks = QString::number(k);
            QString ms = QString::number(m);
            QString Mode = "A"+ks+ms;
            QTableWidgetItem *mode = new QTableWidgetItem();
            mode->setData(Qt::DisplayRole,Mode);
            ui->tableWidget_9->setItem(i,0,mode);

            QTableWidgetItem *min = new QTableWidgetItem();
            min->setData(Qt::DisplayRole,Amplitudes(i,2));
            ui->tableWidget_9->setItem(i,1,min);

            QTableWidgetItem *max = new QTableWidgetItem();
            max->setData(Qt::DisplayRole,Amplitudes(i,3));
            ui->tableWidget_9->setItem(i,2,max);
        }
    }

    if(PlotTypeFactors == "Combined")
    {
        int NumberModes = Amplitudes.n_rows;
        ui->tableWidget_9->setRowCount(1);
        ui->tableWidget_9->setColumnCount(3);
        QStringList TableHeader; TableHeader<<"Mode"<<"Min Value"<<"Max Value";
        ui->tableWidget_9->setHorizontalHeaderLabels(TableHeader);
        QString Mode;
        for(int i=0; i<NumberModes; i++)
        {
            int k = Amplitudes(i,0);
            int m = Amplitudes(i,1);
            QString ks = QString::number(k);
            QString ms = QString::number(m);
            QString mode = "A"+ks+ms;
            Mode.append(mode);
        }
        QTableWidgetItem *mode = new QTableWidgetItem();
        mode->setData(Qt::DisplayRole,Mode);
        ui->tableWidget_9->setItem(0,0,mode);

        QTableWidgetItem *min = new QTableWidgetItem();
        min->setData(Qt::DisplayRole,Amplitudes(0,2));
        ui->tableWidget_9->setItem(0,1,min);

        QTableWidgetItem *max = new QTableWidgetItem();
        max->setData(Qt::DisplayRole,Amplitudes(0,3));
        ui->tableWidget_9->setItem(0,2,max);
    }

}


//Suppress Error Modes
void MainWindow::on_radioButton_29_clicked()
{
    PlotTypeS = "ErrorModes";
}

//Factors
void MainWindow::on_radioButton_30_clicked()
{
    PlotTypeS = "Factors";
}

//Magnitude
void MainWindow::on_radioButton_31_clicked()
{
    PlotTypeS = "Magnitude";
}

//Residuals
void MainWindow::on_radioButton_32_clicked()
{
    PlotTypeS = "Residuals";
}

//Suppress
void MainWindow::on_pushButton_32_clicked()
{
    QString PlotTitle = ui->lineEdit_49->text();
    int K = ui->lineEdit_46->text().toInt();
    int M = ui->lineEdit_45->text().toInt();
    int SpanOfM = ui->lineEdit_47->text().toInt();

    SuppressResiduals Suppress;
    connect(this, SIGNAL(SayResiduals(arma::mat)), &Suppress, SLOT(ListenResiduals(arma::mat)));
    connect(this, SIGNAL(SayWeights(arma::vec)), &Suppress, SLOT(ListenWeights(arma::vec)));
    connect(this, SIGNAL(SayFactors(arma::mat)), &Suppress, SLOT(ListenFactors(arma::mat)));
    connect(this, SIGNAL(SayRadius(arma::vec)), &Suppress, SLOT(ListenRadius(arma::vec)));
    connect(this, SIGNAL(SaySphericalData(arma::mat)), &Suppress, SLOT(ListenSphericalData(arma::mat)));
    connect(this, SIGNAL(SayK(int)), &Suppress, SLOT(ListenK(int)));
    connect(this, SIGNAL(SayM(int)), &Suppress, SLOT(ListenM(int)));
    connect(this, SIGNAL(SaySuppressPlot(QString)), &Suppress, SLOT(ListenPlotType(QString)));
    connect(this, SIGNAL(SaySpanM(int)), &Suppress, SLOT(ListenSpanOfM(int)));
    connect(this, SIGNAL(SaySuppressTitle(QString)), &Suppress, SLOT(ListenPlotTitle(QString)));
    connect(this, SIGNAL(Selected(QStringList)), &Suppress, SLOT(ListenSelectedModes(QStringList)));

    emit SayResiduals(LoadedResiduals);
    emit SayWeights(Weights);
    emit SayFactors(A);
    emit SayRadius(R);
    emit SaySphericalData(SphericalData);
    emit SayK(K);
    emit SayM(M);
    emit SaySuppressPlot(PlotTypeS);
    emit SaySpanM(SpanOfM);
    emit SaySuppressTitle(PlotTitle);
    emit Selected(List);


    Suppress.process();
    arma::mat Amplitudes = Suppress.Get_Amplitudes();
    arma::mat pkm = Suppress.Get_PKM();
    NewResiduals = Suppress.Get_New_Residuals();

    //Text
    ui->plainTextEdit_8->clear();
    QString k = QString::number(K);
    QString m = QString::number(M);
    ui->plainTextEdit_8->appendPlainText("Radial Modes = " + k);
    ui->plainTextEdit_8->appendPlainText("Radial Modes = " + m);



    int n = List.size();
    QStringList Selected2;
    Selected2.clear();
    for(int i=0; i<n;i++)
    {
        QString submode = List.at(i);
        if(submode.mid(1,1) == "c")
        {
            QString submode2 = submode.mid(0,1);
            Selected2.append(submode2);
        }
    }


    QString SM = QString::number(SpanOfM);
    ui->plainTextEdit_8->appendPlainText("Display Angular Modes = " + SM);

    ui->tableWidget_10->setRowCount(SpanOfM+1);
    ui->tableWidget_10->setColumnCount(3);
    QStringList TableHeader; TableHeader<<"M Mode"<<"Min Value"<<"Max Value";
    ui->tableWidget_10->setHorizontalHeaderLabels(TableHeader);
    ui->tableWidget_10->verticalHeader()->setVisible(false);
    ui->tableWidget_10->setShowGrid(false);
    ui->tableWidget_10->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int np = Amplitudes.n_rows;
     for(int i = 0; i<np; i++)
     {
         QTableWidgetItem *M = new QTableWidgetItem();
         M->setData(Qt::DisplayRole,Amplitudes(i,0));
         ui->tableWidget_10->setItem(i,0,M);

         QTableWidgetItem *min = new QTableWidgetItem();
         min->setData(Qt::DisplayRole,Amplitudes(i,1));
         ui->tableWidget_10->setItem(i,1,min);

         QTableWidgetItem *max = new QTableWidgetItem();
         max->setData(Qt::DisplayRole,Amplitudes(i,2));
         ui->tableWidget_10->setItem(i,2,max);
     }

     int nop = pkm.n_rows;
     int index = 0;
     ui->tableWidget_11->setRowCount((SpanOfM+1)*(2*K+1));
     ui->tableWidget_11->setColumnCount(3);
     QStringList TableHeader2; TableHeader2<<"M Mode"<<"K Mode"<<"Amplitude";
     ui->tableWidget_11->setHorizontalHeaderLabels(TableHeader2);
     ui->tableWidget_11->verticalHeader()->setVisible(false);
     ui->tableWidget_11->setShowGrid(false);
     ui->tableWidget_11->setEditTriggers(QAbstractItemView::NoEditTriggers);

     for(int j = 0; j<=SpanOfM; j++)
     {
         for(int i = 0;i<nop; i++)
             {
                 if(pkm(i,1) == j )
                         {
                             QTableWidgetItem *m = new QTableWidgetItem();
                             m->setData(Qt::DisplayRole,pkm(i,1));
                             ui->tableWidget_11->setItem(index,0,m);

                             QTableWidgetItem *k = new QTableWidgetItem();
                             k->setData(Qt::DisplayRole,pkm(i,0));
                             ui->tableWidget_11->setItem(index,1,k);

                             QTableWidgetItem *kvalue = new QTableWidgetItem();
                             kvalue->setData(Qt::DisplayRole,pkm(i,2));
                             ui->tableWidget_11->setItem(index,2,kvalue);
                             index = index + 1;
                         }
             }
     }
     int number = Selected2.size();
     if(Selected2.isEmpty())
     {
         ui->plainTextEdit_8->appendPlainText("Suppressed Modes = None");
     }
     else
     {
         for(int i=0; i<number; i++)
         {
             QString mode = Selected2.at(i);
             int modeint = mode.toInt();
             QString modedisplay = Selected1.at(modeint);
             ui->plainTextEdit_8->appendPlainText("Suppressed Modes = " + modedisplay);
         }
     }

     ui->plainTextEdit_8->appendPlainText("");

     ui->plainTextEdit_15->appendPlainText("Suppressed Plotted" + PlotTypeS);

     //Remove Points Page
     //Get Range
     arma::vec maxrange; maxrange.set_size(3);
     arma::vec minrange; minrange.set_size(3);
     maxrange = (max(NewResiduals).t());
     minrange = (min(NewResiduals).t());

     //Values
     int p = NewResiduals.n_rows;
     QString NP = QString::number(p);
     QString maxx = QString::number(maxrange(0));
     QString maxy = QString::number(maxrange(1));
     QString maxz = QString::number(maxrange(2));
     QString minx = QString::number(minrange(0));
     QString miny = QString::number(minrange(1));
     QString minz = QString::number(minrange(2));

     ui->plainTextEdit_9->clear();
     ui->plainTextEdit_9->appendPlainText("Number of Points = " + NP);
     ui->plainTextEdit_9->appendPlainText("Range x = " + maxx + "   " + minx );
     ui->plainTextEdit_9->appendPlainText("Range y = " + maxy + "   " + miny );
     ui->plainTextEdit_9->appendPlainText("Range z = " + maxz + "   " + minz );
     ui->plainTextEdit_9->appendPlainText(" ");

     //validate cuts with new residuals range
     double minva = minrange(2);
     double maxva = maxrange(2);

     ui->doubleSpinBox->setDecimals(6);
     ui->doubleSpinBox_2->setDecimals(6);
     ui->doubleSpinBox->setSingleStep(0.00001);
     ui->doubleSpinBox_2->setSingleStep(0.00001);
     ui->doubleSpinBox->setRange(minva,0);
     ui->doubleSpinBox_2->setRange(0,maxva);




}


//=======================================================SLOTS==========================================================================//
//======================================================================================================================================//
void MainWindow::monitorCheckStatus()
{
        CheckBoxStatusList checkBoxStatus;
        for (int i = 0; i < m_checkBoxList.count(); ++i)
            checkBoxStatus.append(m_checkBoxList.at(i)->isChecked());
        emit checkBoxStatusChanged(checkBoxStatus);
 }

void MainWindow::testMonitorCheckStatus(const CheckBoxStatusList &checkBoxStatus)
{
    List.clear();
        for (int i = 0; i < checkBoxStatus.count(); ++i)
        {

                QString s = QString::number(i);
                QString say = s + (checkBoxStatus.at(i) ? "c" : "u"); //changed from checked to c and from unchecked to u
                List.append(say);

        }
        //emit Selected(List);
    }


//=======================================================Remove Points Page===============================================================//
//======================================================================================================================================//

//Pre Cut 3D
void MainWindow::on_radioButton_33_clicked()
{
    RPlotType = "3D";
}

//Pre Cut Dots;
void MainWindow::on_radioButton_34_clicked()
{
    RPlotType = "Dots";
}

//Pre Cut Contour
void MainWindow::on_radioButton_35_clicked()
{
    RPlotType = "Contour";
}

//Plot PreCut Residuals
void MainWindow::on_pushButton_27_clicked()
{
    QString Units = ui->lineEdit_44->text();
    QString Title = ui->lineEdit_43->text();

    plot Plot(NewResiduals, Units, RPlotType, Title);

    ui->plainTextEdit_15->appendPlainText("PreCut Residuals Plotted " + RPlotType);
}

//Cut Residuals
void MainWindow::on_pushButton_25_clicked()
{

    if( (!Data.is_empty()) && (!NewResiduals.is_empty()) )
    {
        arma::vec Cut;
        Cut.set_size(2);

        Cut[0] = ui->doubleSpinBox->value();
        Cut[1] = ui->doubleSpinBox_2->value();

        CutResiduals Cuts;
        connect(this, SIGNAL(SayCutResiduals(arma::mat)), &Cuts, SLOT(ListenResiduals(arma::mat)));
        connect(this, SIGNAL(SayCuts(arma::vec)), &Cuts, SLOT(ListenCut(arma::vec)));
        connect(this, SIGNAL(SayData(arma::mat)), &Cuts, SLOT(ListenData(arma::mat)));
        emit SayCutResiduals(NewResiduals);
        emit SayCuts(Cut);
        emit SayData(Data);

        Cuts.process();
        ResidualsCut = Cuts.Get_CutResiduals();
        CutPoints = Cuts.Get_CutPoints();
        arma::mat CutData = Cuts.Get_CutData();

        //Fill Text Cut Points
        int n = CutPoints.n_rows;
        QString nop = QString::number(n);

        ui->plainTextEdit_11->clear();
        ui->plainTextEdit_11->appendPlainText("Number of Points Cut = " + nop);
        ui->plainTextEdit_11->appendPlainText("Points Cut: ");
        for(int i = 0; i<n; i++)
        {
            double x = CutPoints(i,0);
            double y = CutPoints(i,1);
            double z = CutPoints(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_11->appendPlainText(sx + "   " + sy + "   " + sz);
        }


        //Fill Text Residuals Post Cut
        int np = ResidualsCut.n_rows;
        ui->plainTextEdit_12->clear();
        for(int i = 0; i<np; i++)
        {
            double x = ResidualsCut(i,0);
            double y = ResidualsCut(i,1);
            double z = ResidualsCut(i,2);

            QString sx = QString::number(x,'e',6);
            QString sy = QString::number(y,'e',6);
            QString sz = QString::number(z,'e',6);

            ui->plainTextEdit_12->appendPlainText(sx + "   " + sy + "   " + sz);
        }

        //Fill Post Cut Range
        //Get Range
        arma::vec maxrange; maxrange.set_size(3);
        arma::vec minrange; minrange.set_size(3);
        maxrange = (max(ResidualsCut).t());
        minrange = (min(ResidualsCut).t());

        //Values
        QString NP = QString::number(np);
        QString maxx = QString::number(maxrange(0));
        QString maxy = QString::number(maxrange(1));
        QString maxz = QString::number(maxrange(2));
        QString minx = QString::number(minrange(0));
        QString miny = QString::number(minrange(1));
        QString minz = QString::number(minrange(2));

        ui->plainTextEdit_10->clear();
        ui->plainTextEdit_10->appendPlainText("Number of Points = " + NP);
        ui->plainTextEdit_10->appendPlainText("Range x = " + maxx + "   " + minx );
        ui->plainTextEdit_10->appendPlainText("Range y = " + maxy + "   " + miny );
        ui->plainTextEdit_10->appendPlainText("Range z = " + maxz + "   " + minz );
        ui->plainTextEdit_10->appendPlainText(" ");

        //Fill Text  Cut Data
        int npd = CutData.n_rows;
        ui->plainTextEdit_13->clear();
        ui->plainTextEdit_14->clear();
        for(int i = 0; i<npd; i++)
        {
            if(CutData(i,3) == 0)
            {
                double x = CutData(i,0);
                double y = CutData(i,1);
                double z = CutData(i,2);

                QString sx = QString::number(x,'e',6);
                QString sy = QString::number(y,'e',6);
                QString sz = QString::number(z,'e',6);

                ui->plainTextEdit_13->appendPlainText(sx + "   " + sy + "   " + sz + "   ");
            }
            else
            {
                double x = CutData(i,0);
                double y = CutData(i,1);
                double z = CutData(i,2);

                QString sx = QString::number(x,'e',6);
                QString sy = QString::number(y,'e',6);
                QString sz = QString::number(z,'e',6);

                ui->plainTextEdit_14->appendPlainText(sx + "   " + sy + "   " + sz + "   ");
            }

        }

        double low  = Cut(0);
        double high = Cut(1);
        QString lower = QString::number(low);
        QString higher = QString::number(high);
        ui->plainTextEdit_15->appendPlainText("Residuals and Data Cut = " + lower + "   " + higher);

    }

    else
    {
        QString Info = "Warning";
        QString Message = "You have to load both data and residuals to perform a point cut.";
        QMessageBox::warning(0,Info, Message, QMessageBox::Ok);
    }
}

//Save Post Cut Residuals
void MainWindow::on_pushButton_26_clicked()
{
    //Save File
    QString DataFileSave = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (DataFileSave.isEmpty())
          return;

    QFile SaveCalculations(DataFileSave);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->plainTextEdit_12->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

        ui->plainTextEdit_15->appendPlainText("Post Cut Residuals Saved  " + DataFileSave);
}

//Save Cut Info
void MainWindow::on_pushButton_33_clicked()
{
    //Save File
    QString DataFileSave = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (DataFileSave.isEmpty())
          return;

    QFile SaveCalculations(DataFileSave);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->plainTextEdit_11->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

        ui->plainTextEdit_15->appendPlainText(" Cut Info  " + DataFileSave);
}

//Save Cut Data
void MainWindow::on_pushButton_35_clicked()
{
    //Save File
    QString DataFileSave = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (DataFileSave.isEmpty())
          return;

    QFile SaveCalculations(DataFileSave);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->plainTextEdit_14->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

        ui->plainTextEdit_15->appendPlainText("Cut Data Saved  " + DataFileSave);
}

//Save Post Cut Data
void MainWindow::on_pushButton_34_clicked()
{
    //Save File
    QString DataFileSave = QFileDialog::getSaveFileName(this, tr("Save Data"), "/home" , tr("Text File (*.txt);;All Files (*)"));

    if (DataFileSave.isEmpty())
          return;

    QFile SaveCalculations(DataFileSave);
        if (!SaveCalculations.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&SaveCalculations);
        out << ui->plainTextEdit_13->document()->toPlainText();
        SaveCalculations.flush();
        SaveCalculations.close();

        ui->plainTextEdit_15->appendPlainText("Post Cut Data Saved  " + DataFileSave);
}

//Post Cut 3D
void MainWindow::on_radioButton_36_clicked()
{
    RCPlotType = "3D";
}

//Post Cut Dots
void MainWindow::on_radioButton_37_clicked()
{
    RCPlotType = "Dots";
}

//Post Cut Contour
void MainWindow::on_radioButton_38_clicked()
{
    RCPlotType = "Contour";
}

//Post Cut Plot
void MainWindow::on_pushButton_28_clicked()
{
    QString Units = ui->lineEdit_51->text();
    QString Title = ui->lineEdit_50->text();

    plot Plot(ResidualsCut, Units, RCPlotType, Title);

    ui->plainTextEdit_15->appendPlainText("PostCut Residuals Plotted " + RCPlotType);
}

//===================================================================================================//
//Labels Info
//===================================================================================================//
//Generate Data - Surface Type
void MainWindow::Mouse_PressedSurface()
{

    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

    //Set file.txt to Text
    QFile HelpFile(":/Surface/resources/surface.txt");

    //If File Not Open Then Stop
     if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream ReadHelp(&HelpFile);
    QString HelpText;

    while(!ReadHelp.atEnd())
    {
        HelpText = ReadHelp.readAll();
    }

    emit SayText(HelpText);
    HelpWindow.exec();
}

//Generate Data - Error
void MainWindow::Mouse_PressedError()
{

    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/error.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Generate Data - Units
void MainWindow::Mouse_PressedUnits()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/units.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Generate Data -Grid
void MainWindow::Mouse_PressedGrid()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/grid.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Generate Data - Transformation
void MainWindow::Mouse_PressedTransformation()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/transformation.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Open Data - Open Data
void MainWindow::Mouse_PressedOpenData()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/opendata.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Recover Parameters - Data Type
void MainWindow::Mouse_PressedDataType()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/datatype.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Recover Parameters - Surface Type
void MainWindow::Mouse_PressedSurfaceType()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/surfacetype.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Recover Parameters - Analysis Type
void MainWindow::Mouse_PressedAnalysisType()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/analysistype.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();

}

//Recover Parameters - Initial Guess
void MainWindow::Mouse_PressedInitialGuess()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/initialguess.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Chi Square Map
void MainWindow::Mouse_PressedChiSMap()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/chismap.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Residuals - Open/Calculate Residuals
void MainWindow::Mouse_PressedResiduals()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/residuals.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Error Modes - Radii
void MainWindow::Mouse_PressedRadii()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/radii.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Error Modes - Magnitude Plots
void MainWindow::Mouse_PressedMagnitude()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/magnitude.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}

//Error Modes - Amplitudes
void MainWindow::Mouse_PressedAmplitude()
{
    InfoDialog HelpWindow;
    connect(this, SIGNAL(SayText(QString)), &HelpWindow, SLOT(ListenText(QString)));

     //Set file.txt to Text
     QFile HelpFile(":/Surface/resources/amplitude.txt");

     //If File Not Open Then Stop
      if (!HelpFile.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream ReadHelp(&HelpFile);
     QString HelpText;

     while(!ReadHelp.atEnd())
     {
         HelpText = ReadHelp.readAll();
     }

     emit SayText(HelpText);
     HelpWindow.exec();
}


//==========================================Modes Page - Incomplete======================================================================================//
//=======================================================================================================================================================//
//Calculate Constants
void MainWindow::on_pushButton_36_clicked()
{
    //Get Parameters to Pass to ModeAnalysis
    arma::vec R; R.set_size(2);
    R[0] = ui->lineEdit_37->text().toDouble(); //min value
    R[1] = ui->lineEdit_38->text().toDouble(); //max value
    int K = ui->lineEdit_53->text().toInt();
    int M = ui->lineEdit_52->text().toInt();

    //Emit Values
    modeanalysis2 Constants;
    connect(this, SIGNAL(SayK(int)), &Constants, SLOT(ListenK(int)));
    connect(this, SIGNAL(SayM(int)), &Constants, SLOT(ListenM(int)));
    connect(this, SIGNAL(SayRadius(arma::vec)), &Constants, SLOT(ListenRadius(arma::vec)));
    connect(this, SIGNAL(SayResiduals(arma::mat)), &Constants, SLOT(ListenResiduals(arma::mat)));

    emit SayK(K);
    emit SayM(M);
    emit SayRadius(R);
    emit SayResiduals(LoadedResiduals);

    //Process and get Constants
    Constants.process();
    arma::mat CC = Constants.Get_CC();
    arma::mat CS = Constants.Get_CS();
    arma::mat SC = Constants.Get_SC();
    arma::mat SS = Constants.Get_SS();
    FactorMap.clear();
    FactorMap = Constants.Get_Map();

    //Display Values in Table
    //Constants Table
    int size = (K+1)*(M+1);
    ui->tableWidget_12->setRowCount(size);
    ui->tableWidget_12->setColumnCount(6);
    QStringList TableHeader; TableHeader<< "k" << "m" <<"CCkm"<<"CSkm"<<"SCkm"<<"SSkm";
    ui->tableWidget_12->setHorizontalHeaderLabels(TableHeader);
    ui->tableWidget_12->verticalHeader()->setVisible(false);
    ui->tableWidget_12->setShowGrid(false);
    ui->tableWidget_12->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int np = CC.n_rows;
    //Fill Table with Constants Data
    for(int i = 0; i<np; i++)
            {

                    QTableWidgetItem *k = new QTableWidgetItem();
                    k->setData(Qt::DisplayRole,CC(i,0));
                    ui->tableWidget_12->setItem(i,0,k);

                    QTableWidgetItem *m = new QTableWidgetItem();
                    m->setData(Qt::DisplayRole,CC(i,1));
                    ui->tableWidget_12->setItem(i,1,m);

                    QTableWidgetItem *cc = new QTableWidgetItem();
                    cc->setData(Qt::DisplayRole,CC(i,2));
                    ui->tableWidget_12->setItem(i,2,cc);

                    QTableWidgetItem *cs = new QTableWidgetItem();
                    cs->setData(Qt::DisplayRole,CS(i,2));
                    ui->tableWidget_12->setItem(i,3,cs);

                    QTableWidgetItem *sc = new QTableWidgetItem();
                    sc->setData(Qt::DisplayRole,SC(i,2));
                    ui->tableWidget_12->setItem(i,4,sc);

                    QTableWidgetItem *ss = new QTableWidgetItem();
                    ss->setData(Qt::DisplayRole,SS(i,2));
                    ui->tableWidget_12->setItem(i,5,ss);
        }

    //Fill Table with Amplitudes
    //Amplitudes Table
    ui->tableWidget_13->setRowCount(4*size);
    ui->tableWidget_13->setColumnCount(4);
    QStringList TableHeader2; TableHeader2<< "ModeKM" << "min" <<"max"<<"(max - min)";
    ui->tableWidget_13->setHorizontalHeaderLabels(TableHeader2);
    ui->tableWidget_13->verticalHeader()->setVisible(false);
    ui->tableWidget_13->setShowGrid(false);
    ui->tableWidget_13->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QMap<QString, arma::mat>::iterator i;
    int rowindex = 0;
    for (i = FactorMap.begin(); i != FactorMap.end(); ++i)
    {

        QTableWidgetItem *mode = new QTableWidgetItem();
        mode->setData(Qt::DisplayRole,i.key());
        ui->tableWidget_13->setItem(rowindex,0,mode);

        arma::mat Factor = i.value();
        arma::colvec Factorz = Factor.col(2);
        double minval = min(Factorz);
        double maxval = max(Factorz);

        QTableWidgetItem *minv = new QTableWidgetItem();
        minv->setData(Qt::DisplayRole,minval);
        ui->tableWidget_13->setItem(rowindex,1,minv);

        QTableWidgetItem *maxv = new QTableWidgetItem();
        maxv->setData(Qt::DisplayRole,maxval);
        ui->tableWidget_13->setItem(rowindex,2,maxv);

        double difval = maxval - minval;
        QTableWidgetItem *dif = new QTableWidgetItem();
        dif->setData(Qt::DisplayRole,difval);
        ui->tableWidget_13->setItem(rowindex,3,dif);

        rowindex++;
        Factor.zeros();
        Factorz.zeros();

    }
    //Sort Items
    ui->tableWidget_13->sortByColumn(3);

        //Fill ScrollArea with Modes
        QWidget *wid = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout();
         m_checkBoxList.clear();
        for(int i=0; i<np; i++)
        {
            int k = CC(i,0);
            int m = CC(i,1);
            QString ks = QString::number(k);
            QString ms = QString::number(m);
            QString cc = "CC"+ks+ms;
            QString cs = "CS"+ks+ms;
            QString sc = "SC"+ks+ms;
            QString ss = "SS"+ks+ms;
            Selected2.append(cc);
            Selected2.append(cs);
            Selected2.append(sc);
            Selected2.append(ss);

            QCheckBox *checkBox1 = new QCheckBox(cc);
            QCheckBox *checkBox2 = new QCheckBox(cs);
            QCheckBox *checkBox3 = new QCheckBox(sc);
            QCheckBox *checkBox4 = new QCheckBox(ss);
            connect(checkBox1, SIGNAL(toggled(bool)), this, SLOT(monitorCheckStatus()));
            connect(checkBox2, SIGNAL(toggled(bool)), this, SLOT(monitorCheckStatus()));
            connect(checkBox3, SIGNAL(toggled(bool)), this, SLOT(monitorCheckStatus()));
            connect(checkBox4, SIGNAL(toggled(bool)), this, SLOT(monitorCheckStatus()));
            m_checkBoxList.append(checkBox1);
            m_checkBoxList.append(checkBox2);
            m_checkBoxList.append(checkBox3);
            m_checkBoxList.append(checkBox4);

            layout->addWidget(checkBox1);
            layout->addWidget(checkBox2);
            layout->addWidget(checkBox3);
            layout->addWidget(checkBox4);
            updateGeometry();
        }

        wid->setLayout(layout);
        ui->scrollArea_10->setWidget(wid);


}

//Plot Selected
void MainWindow::on_pushButton_37_clicked()
{
    //Find Selected Modes
    int n = List.size();
    QStringList SelectedModes;
    SelectedModes.clear();
    for(int i=0; i<n;i++)
    {
        QString submode = List.at(i);
        bool check = submode.contains("c");
        if(check)
        {
           SelectedModes.append(Selected2.at(i));
        }
    }

    //Pick Modes to Plot
    int sizelist = SelectedModes.size();
    for(int i = 0; i<sizelist; i++)
    {
        QString Mode = SelectedModes.at(i);     //pick the first selected mode
        QString factor = Mode.mid(0,2);         //Pick the constant
        double k = Mode.mid(2,1).toDouble();    //pick the k value
        double m = Mode.mid(3,1).toDouble();    //pick the m value
        arma::mat Matrix = FactorMap[Mode];     //Pick the matrix from the map
        plot PlotFactors(Matrix,k,m,factor);    //plot

    }

}

//Calculate Weights
void MainWindow::on_pushButton_38_clicked()
{
    //Find Selected Modes
    int n = List.size();
    QStringList SelectedModes;
    SelectedModes.clear();
    for(int i=0; i<n;i++)
    {
        QString submode = List.at(i);
        bool check = submode.contains("c");
        if(check)
        {
           SelectedModes.append(Selected2.at(i));
        }
    }

    //Emit Values
    modeanalysis2 ConstantsWeights;
    connect(this, SIGNAL(SayResiduals(arma::mat)), &ConstantsWeights, SLOT(ListenResiduals(arma::mat)));
    connect(this,SIGNAL(Selected(QStringList)), &ConstantsWeights, SLOT(ListenSelectedModes(QStringList)));
    connect(this, SIGNAL(SayFactorMap(QMap<QString,arma::mat>)), &ConstantsWeights, SLOT(ListenFactorMap(QMap<QString,arma::mat>)));

    emit Selected(SelectedModes);
    emit SayResiduals(LoadedResiduals);
    emit SayFactorMap(FactorMap);

    ConstantsWeights.process2();
    WeightsReceived.zeros();
    WeightsReceived = ConstantsWeights.Get_Weights();

    //Fill Table with weights
    //Amplitudes Table
    int size = SelectedModes.size();
    ui->tableWidget_14->setRowCount(size);
    ui->tableWidget_14->setColumnCount(2);
    QStringList TableHeader2; TableHeader2<< "ModeKM" << "Weight";
    ui->tableWidget_14->setHorizontalHeaderLabels(TableHeader2);
    ui->tableWidget_14->verticalHeader()->setVisible(false);
    ui->tableWidget_14->setShowGrid(false);
    ui->tableWidget_14->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i = 0; i<size; i++)
    {
        QTableWidgetItem *mode = new QTableWidgetItem();
        mode->setData(Qt::DisplayRole,SelectedModes.at(i));
        ui->tableWidget_14->setItem(i,0,mode);

        QTableWidgetItem *weight = new QTableWidgetItem();
        weight->setData(Qt::DisplayRole,WeightsReceived(i));
        ui->tableWidget_14->setItem(i,1,weight);

    }

}

//Plot Weight Constants Individually
void MainWindow::on_pushButton_39_clicked()
{
    //Find Selected Modes
    int n = List.size();
    QStringList SelectedModes;
    SelectedModes.clear();
    for(int i=0; i<n;i++)
    {
        QString submode = List.at(i);
        bool check = submode.contains("c");
        if(check)
        {
           SelectedModes.append(Selected2.at(i));
        }
    }

    //Pick Modes to Plot
    int sizelist = SelectedModes.size();
    int rows = LoadedResiduals.n_rows;
    arma::mat ModesMatrix; ModesMatrix.set_size(rows,3);

    for(int i = 0; i<sizelist; i++)
    {
        QString Mode = SelectedModes.at(i);             //pick the first selected mode
        QString factor = Mode.mid(0,2);                 //Pick the constant
        double k = Mode.mid(2,1).toDouble();            //pick the k value
        double m = Mode.mid(3,1).toDouble();            //pick the m value
        arma::mat Matrix = FactorMap[Mode];             //Pick the matrix from the map
        Matrix.col(2) = WeightsReceived(i)*Matrix.col(2); //Multiply mode by weight
        plot PlotFactors(Matrix,k,m,factor);       //plot
    }

}

//Plot Weight Constants Combined
void MainWindow::on_pushButton_40_clicked()
{
    //Find Selected Modes
    int n = List.size();
    QStringList SelectedModes;
    SelectedModes.clear();
    for(int i=0; i<n;i++)
    {
        QString submode = List.at(i);
        bool check = submode.contains("c");
        if(check)
        {
           SelectedModes.append(Selected2.at(i));
        }
    }

    //Pick Modes to Plot
    int sizelist = SelectedModes.size();
    int rows = LoadedResiduals.n_rows;
    QString TotalModes;
    arma::mat ModesMatrix; ModesMatrix.set_size(rows,3); ModesMatrix.zeros();
    arma::vec Column; Column.set_size(rows); Column.zeros();

    for(int i = 0; i<sizelist; i++)
    {
        QString Mode = SelectedModes.at(i);             //pick the first selected mode
        TotalModes.append(Mode);                        //append modes to string for plot title
        arma::mat Matrix = FactorMap[Mode];             //Pick the matrix from the map
        Column = Column + WeightsReceived(i)*Matrix.col(2);
        Matrix.zeros();
    }

    ModesMatrix = LoadedResiduals;              //Set x,y,z
    ModesMatrix.insert_cols(2,Column);          //replace z with combined modes
    plot Combined(ModesMatrix,TotalModes);      //Plot

}

//Plot Residuals - Modes
void MainWindow::on_pushButton_41_clicked()
{
    //Find Selected Modes
    int n = List.size();
    QStringList SelectedModes;
    SelectedModes.clear();
    for(int i=0; i<n;i++)
    {
        QString submode = List.at(i);
        bool check = submode.contains("c");
        if(check)
        {
           SelectedModes.append(Selected2.at(i));
        }
    }

    //Pick Modes to Plot
    int sizelist = SelectedModes.size();
    int rows = LoadedResiduals.n_rows;
    QString TotalModes;
    arma::mat ResidualsMinusModes; ResidualsMinusModes.set_size(rows,3); ResidualsMinusModes.zeros();
    arma::vec Column; Column.set_size(rows); Column.zeros();

    for(int i = 0; i<sizelist; i++)
    {
        QString Mode = SelectedModes.at(i);             //pick the first selected mode
        TotalModes.append(Mode);                        //append modes to string for plot title
        arma::mat Matrix = FactorMap[Mode];             //Pick the matrix from the map
        Column = Column + WeightsReceived(i)*Matrix.col(2);
        Matrix.zeros();
    }

    ResidualsMinusModes = LoadedResiduals;              //Set x,y,z
    ResidualsMinusModes.col(2) = ResidualsMinusModes.col(2) - Column;
    QString title = "Residuals - Modes";
    QString Units = "cm";
    QString type = "3D";
    plot Combined(ResidualsMinusModes, Units, type, title);      //Plot

    //Remove Points Page
    ui->scrollArea_9->setEnabled(true);
    NewResiduals = ResidualsMinusModes;
    //Get Range
    arma::vec maxrange; maxrange.set_size(3);
    arma::vec minrange; minrange.set_size(3);
    maxrange = (max(NewResiduals).t());
    minrange = (min(NewResiduals).t());

    //Values
    int p = NewResiduals.n_rows;
    QString NP = QString::number(p);
    QString maxx = QString::number(maxrange(0));
    QString maxy = QString::number(maxrange(1));
    QString maxz = QString::number(maxrange(2));
    QString minx = QString::number(minrange(0));
    QString miny = QString::number(minrange(1));
    QString minz = QString::number(minrange(2));

    ui->plainTextEdit_9->clear();
    ui->plainTextEdit_9->appendPlainText("Number of Points = " + NP);
    ui->plainTextEdit_9->appendPlainText("Range x = " + maxx + "   " + minx );
    ui->plainTextEdit_9->appendPlainText("Range y = " + maxy + "   " + miny );
    ui->plainTextEdit_9->appendPlainText("Range z = " + maxz + "   " + minz );
    ui->plainTextEdit_9->appendPlainText(" ");

    //validate cuts with new residuals range
    double minva = minrange(2);
    double maxva = maxrange(2);

    ui->doubleSpinBox->setDecimals(6);
    ui->doubleSpinBox_2->setDecimals(6);
    ui->doubleSpinBox->setSingleStep(0.00001);
    ui->doubleSpinBox_2->setSingleStep(0.00001);
    ui->doubleSpinBox->setRange(minva,0);
    ui->doubleSpinBox_2->setRange(0,maxva);


}
