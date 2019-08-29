#pragma once

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QFile>
#include "../downloaderinterface.h"

class downloadjob: public QObject {
Q_OBJECT
public:
    downloadjob(DownloaderInterface *_parent, qint32 _id, QUrl _url, const QString &_filename);
    qint32 id;
    DownloaderInterface *parent;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QNetworkRequest request;
    QFile file;
    qint64 finishedoffset;
    QUrl url;
    
    /*state of job downloading and not downloading for now */
    enum D_STATES{ D_STOPPED, D_RUNNING };
    D_STATES MY_STATE;

    bool start( ){
        qDebug() <<"start";
        MY_STATE = D_RUNNING;
        QNetworkRequest request(url);


        reply = manager.get(request);

        //make file for write
        if(!file.open(QIODevice::WriteOnly)) {

            qDebug() <<"could not open file";
            //call deletedl
            //return false;
        }

        //connects
        connect(reply, SIGNAL(readyRead()), SLOT(chunksave()));
        QObject::connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
        QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinished_fullsave(QNetworkReply*)));
        return true;
    }

    bool pause(){
        qDebug() <<"pause";
        if(!MY_STATE) /*if not running*/{
            return false;
        }
        reply->abort();
        file.flush();
        //file.close()
        MY_STATE = D_STOPPED;
        reply->deleteLater();
    }

    bool resume(){
        qDebug() <<"resume";
        if(MY_STATE) /*if running*/{
            qDebug() <<"already running";
            return true;
        }

        qDebug() <<"start";
        MY_STATE = D_RUNNING;
        QNetworkRequest request(url);
        reply = manager.get(request);
        //make file for write
        if( !file.isOpen() ) {
            //call deletedl
            return false;
        }
        
        if(!file.open(QIODevice::WriteOnly) ) {
			qDebug() <<"could not open file";
			//call deletedl
			return false;
			}
        
        
        QByteArray rangeHeaderValue = "bytes=" + QByteArray::number(file.size()) + "-";
        request.setRawHeader("Range",rangeHeaderValue);
        return true;

    }

    bool deletedl(  bool delete_file ) {
        qDebug() <<"delete";

        reply->abort();
        reply->deleteLater();
        MY_STATE = D_STOPPED;

        if(delete_file) {
            file.remove();

        }
        return true;

    }

public slots:
    void downloadProgress(qint64 recieved, qint64 total) {
            //qDebug() << recieved << total;
        qint64 i = (recieved * 100) / total;
        qDebug() << "download percentage"<< i;
            if(i > 0) {
                emit parent->signal_update_item_stats(id, QString("downloading %0").arg(i));
                qDebug() <<"emiting signal for download progress";
                //emit signal_update_item_stats( i);
            }
        }


    void chunksave() {

        QByteArray buffer = reply->readAll();
        file.seek( finishedoffset );
        file.write( buffer );
        finishedoffset += buffer.size();
    }


    void downloadFinished_fullsave(QNetworkReply* data) {

        if (!file.isOpen()){
            qDebug() << "could not read file to save download";
            return;
        }

        const QByteArray buffer = data->readAll();
        file.seek(finishedoffset);
        file.write(buffer);
        file.close();
        qDebug() <<"Done writing whole file..";
        //emit
    }

};


