#ifndef HANDLERS_H
#define HANDLERS_H
#include<QObject>
// every download backend like aria2, youtube-dl, libtorrent inherits this class
class DownloaderInterface: public QObject {
    Q_OBJECT
public:


public slots:


    virtual void addNewDownload( QString url, qint32 id) = 0;
    virtual void pauseItem( qint32 id ) = 0;
    virtual void resumeItem( qint32 id ) = 0;
    virtual void deleteItem( qint32 id, bool delete_file) = 0;

    
signals:
	void signal_update_item_stats( qint32 id, QString progress );
	void signal_update_global_stats( QString progress );
	void signal_download_added( qint32 id );
	void signal_error_occured( qint32 id );
	void signal_paused( qint32 id);
	void signal_resumed( qint32 id);
	void signal_deleted( qint32 id);
	void signal_downloadfinished( qint32 id);

};





#endif // HANDLERS_H
