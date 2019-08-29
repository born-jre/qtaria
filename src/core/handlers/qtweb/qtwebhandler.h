#ifndef QTARIA_QTWEBHANDLER_H
#define QTARIA_QTWEBHANDLER_H

#include <QMap>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QFile>
#include "../downloaderinterface.h"
#include "downloadjob.h"

class downloadjob;

class qtwebhandler: public DownloaderInterface {

Q_OBJECT

public:
    qtwebhandler(): joblist(){};
    QMap<qint32, downloadjob*> joblist;
public slots:

    void addNewDownload( QString url, qint32 id) override {
        QUrl _url = QUrl::fromEncoded(url.toLocal8Bit());
        downloadjob *ptr_dj = new downloadjob((DownloaderInterface*)this, id, _url, QString("downloadfile") );

        if(!ptr_dj->start()) {
            ptr_dj->deleteLater();
            qDebug()<<"could not add";
            return;
        }
        joblist.insert(id, ptr_dj);
        emit signal_download_added(id);
    }

    void pauseItem(qint32 id) override {
        if(!joblist[id]->pause()) {
			qDebug()<<"Error could not pause";
			return; //emit error
			}
        emit signal_paused(id);
    }

    void resumeItem(qint32 id) override {
        if(!joblist[id]->resume()) {
			qDebug()<<"Error could not resume";
			return; //emit error
			}        
        emit signal_resumed(id);
    }

    void deleteItem(qint32 id, bool delete_file) override {
        if(!joblist[id]->deletedl(delete_file)) {
			qDebug()<<"Error could delete";
			return; //emit error
			}
        joblist.remove(id);
        emit signal_deleted(id);
    }
};


#endif //QTARIA_QTWEBHANDLER_H
