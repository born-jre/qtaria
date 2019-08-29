#pragma once

#include <QtGui>
#include <QListWidgetItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class listwidget: public QListWidgetItem, public QObject
{
 public:
  explicit listwidget( QListWidget *_parent ):
      QListWidgetItem(),
      QObject(_parent),
      widget(),
      label("Empty Now"),
      pushbutton("Push me"),
      parent(_parent) {

    widgetlayout.addWidget(&label);
    widgetlayout.addWidget(&pushbutton);
    widgetlayout.addStretch();
    widgetlayout.setSizeConstraint(QLayout::SetFixedSize);
    widget.setLayout(&widgetlayout);
    this->setSizeHint(widget.sizeHint());

    parent->addItem(this);
    parent->setItemWidget(this,&this->widget);

    id == count + 1;



  }

 public slots:
  void resumed() {};
  void paused() {}
  void error_occured() {};
  qint32 id;

  /*slots for own buttons (pause resume delete/ button1,button2)*/
  void button_one_pressed() {};
  void button_two_pressed() {};
  void i_am_selected() {};

 signals:
  void pause(qint32 id);
  void resume(qint32 id);
  void deleteb(qint32 id);

 private:
  QWidget widget;
  QLabel label;
  QHBoxLayout widgetlayout;
  QPushButton pushbutton;
  QListWidget *parent;
  static qint32 count;
};
