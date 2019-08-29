#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QMap>
#include <QWidget>
#include <QList>
#include <QListWidget>
#include <iostream>


#include "addnewdialog.h"
#include "core/handlers/qtweb/qtwebhandler.h"
#include "core/managers/uimanager/uielementgroup.h"
#include "core/handlers/downloaderinterface.h"
#include "core/managers/uimanager/uielementgroup.h"

#include "core/managers/uimanager/listwidget.h"

#define BUFFMAXUIELEMENTS 10

class addNewDialog;

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread worker;
    Ui::MainWindow *ui;
    addNewDialog *newDialog;
    DownloaderInterface *myDownloader;

    /*map to hold id and item in list of items in ui*/
    QMap<qint32, uielementgroup*> map_of_uielements;

    QMap<qint32, listwidget*> map_of_widgets;
    QListWidget qw;

  qint32 _id = 0; /*id for map*/

    /*list of buffer to hold some empty ui elements*/
    QList<uielementgroup*> list_of_uielements;

public:
    explicit MainWindow(QWidget *parent = 0);

    void emitAddNewDownload(QString url,QString location); //add new download btn

    /*ui elements managing stuff*/
    void init_ui_elements();
  listwidget * new_ui_element();
    void delete_ui_element(qint32 id);


    ~MainWindow() final;

private slots:
    void on_actionAddNew_triggered();
public slots:
    void slot_update_item_stats(qint32 id, QString progress);
    void slot_update_global_stats(QString progress);
    void slot_download_added(qint32 id);
    void slot_error_occured(qint32 id);
    void slot_paused(qint32 id);
    void slot_resumed(qint32 id);
    void slot_deleted(qint32 id);
    void slot_downloadfinished(qint32 id);

  /* slots for ui*/
  void pausepressed(qint32 id) {};
  void resumepresed(qint32 id) {};
  void deletepressed(qint32 id) {};
};

#endif // MAINWINDOW_H
