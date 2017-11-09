#ifndef LABEL_INFO_H
#define LABEL_INFO_H

#include <QLabel>
#include <QMouseEvent>


class Label_Info : public QLabel
{
    Q_OBJECT
public:
    explicit Label_Info(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *ev);
    
signals:
    void Mouse_Pressed();
    
public slots:
    
};

#endif // LABEL_INFO_H
