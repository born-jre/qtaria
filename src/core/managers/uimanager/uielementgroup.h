#ifndef OBJECTHOLDER_H
#define OBJECTHOLDER_H
#include<QWidget>
#include<QLabel>
#include<QHBoxLayout>
#include<QPushButton>
#include<QString>
#include<iostream>
#include<QObject>


/*one all widget of one download item is grouped in this class
 * list of this class is managed by mainwindow in a Qmap and id
 * which helps to dispatch correct instance's method when user pauses,resume...in ui
 * as well as when downloadhandler sends download speed and stuff to ui correct item widget is selected
 * and update  Naming could have been more declerative, atleast its not class12
 * */

class uielementgroup : public QObject
{
    Q_OBJECT
public:
    explicit uielementgroup(QWidget * parent=nullptr);

    /*count  no of instances*/
    static int count;

    static QWidget *p; //parent needed later for accessing list


    /*ui elements*/
    QHBoxLayout *holder;
    QWidget *groupw;
    QLabel *info;
    QPushButton *stop_btn;
    QPushButton *play_pause_btn;
    QString default_style;


    /*hide buttons, remove labels, make ready for it to push to list*/
    void clear() {};

    void set_id(qint32 id) {};

    qint32 get_id() { return _id; }

  void set_update(const QString &p) { info->setText(p); }


    ~uielementgroup() final{
        uielementgroup::count--;
        //free all resource i guess
        delete holder;
        delete groupw;
        delete info;
        delete stop_btn;
        delete play_pause_btn;
    }
private:
    /* one instance id */
    qint32 _id;

public slots:
signals:

};
#endif // OBJECTHOLDER_H
