#include "label_info.h"

Label_Info::Label_Info(QWidget *parent) :
    QLabel(parent)
{
}

void Label_Info::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}
