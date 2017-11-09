#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();

private:
    Ui::InfoDialog *ui;

public slots:
    void ListenText(QString text);

};

#endif // INFODIALOG_H
