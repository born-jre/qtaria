#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);

    myDownloader = new qtwebhandler();
    myDownloader->moveToThread(&worker);
    worker.start();
    
    //connects 
    connect(myDownloader,&DownloaderInterface::signal_update_item_stats,this,&MainWindow::slot_update_item_stats);
   // connect(myDownloader,&DownloaderInterface::signal_update_global_stats,this,&MainWindow::slot_update_item_stats);
    connect(myDownloader,&DownloaderInterface::signal_download_added,this,&MainWindow::slot_download_added);
    connect(myDownloader,&DownloaderInterface::signal_error_occured,this,&MainWindow::slot_error_occured);
    connect(myDownloader,&DownloaderInterface::signal_paused,this,&MainWindow::slot_paused);
    connect(myDownloader,&DownloaderInterface::signal_resumed,this,&MainWindow::slot_resumed);
    connect(myDownloader,&DownloaderInterface::signal_deleted,this,&MainWindow::slot_deleted);
    connect(myDownloader,&DownloaderInterface::signal_downloadfinished,this,&MainWindow::slot_downloadfinished);

  ui->verticalLayout_4->addWidget(&qw);
}

MainWindow::~MainWindow()
{

    delete ui;
}

/*since addnewdialog (dialog to input new url)  cannot call downloadmanager so it
 * passes new url and stuff to mainwindow and it passes into downloadmanager*/
void MainWindow::emitAddNewDownload(QString url,QString location)
{
    //  http://speed.hetzner.de/100MB.bin
    //  QString url = "  http://ipv4.download.thinkbroadband.com/5MB.zip  ";

    myDownloader->addNewDownload(url, new_ui_element()->id);

}


listwidget * MainWindow::new_ui_element() {
  auto lw = new listwidget(&qw);
  map_of_widgets.insert(lw->id, lw);
  return lw;
}

void MainWindow::delete_ui_element(qint32 id) {

}

void MainWindow::on_actionAddNew_triggered()
{
    newDialog = new addNewDialog(this);
    newDialog->show();

}

void MainWindow::slot_update_item_stats( qint32 id, QString progress) {

}

void MainWindow::slot_update_global_stats(QString progress) {

}

void MainWindow::slot_download_added(qint32 id) {

}

void MainWindow::slot_paused(qint32 id) {

}

void MainWindow::slot_error_occured(qint32 id) {

}

void MainWindow::slot_resumed(qint32 id) {

}

void MainWindow::slot_deleted(qint32 id) {

}

void MainWindow::slot_downloadfinished(qint32 id) {

}

