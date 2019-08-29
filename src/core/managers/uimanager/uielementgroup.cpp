#include "uielementgroup.h"

uielementgroup::uielementgroup(QWidget * parent ):

    QObject(parent)
{
        holder = new QHBoxLayout(parent);
        info = new QLabel(parent);
        play_pause_btn = new QPushButton(parent);
        stop_btn = new QPushButton(parent);
        groupw = new QWidget(parent);
        //groupw->setGeometry(0,0,10,40);

        //play_pause_btn->setText(QString("pause"));
        //stop_btn->setText(QString("stop"));

        holder->setSpacing(0);
        //temp_objh->holder->setMargin(0);
        holder->addWidget(info);
        holder->addSpacerItem(new QSpacerItem(10,10,QSizePolicy::Expanding));
        holder->addWidget(play_pause_btn);
        holder->addWidget(stop_btn);
        groupw->setLayout(holder);

        play_pause_btn->hide();
        stop_btn->hide();

        if(p == nullptr) { p = parent; }

            /* to make different stripes pattern in download items list  */
        if(!uielementgroup::count){
            default_style = QString("background-color:rgb(171, 194, 233);");
            groupw->setStyleSheet(default_style);
            uielementgroup::count++;
            return;
        }
        if(uielementgroup::count%2){
            default_style = QString("background-color: rgb(214, 206, 255);");
            groupw->setStyleSheet(default_style);
        } else {
            default_style = QString("background-color:rgb(171, 194, 233);");
            groupw->setStyleSheet(default_style);
        }

    uielementgroup::count++;
}

int uielementgroup::count = 0;
QWidget *uielementgroup::p = nullptr;
