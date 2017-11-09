#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);

    //Set Title of Window
    QWidget::setWindowTitle("Documentation");
}

InfoDialog::~InfoDialog()
{
    delete ui;
}


void InfoDialog::ListenText(QString text)
{
    ui->textBrowser->setText(text);
}
