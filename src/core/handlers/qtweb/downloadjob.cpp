#include "downloadjob.h"


downloadjob::downloadjob(DownloaderInterface *_parent, qint32 _id, QUrl _url, const QString &_filename):
        QObject(nullptr),
        parent(_parent),
        id(_id),
        manager(this),
        request(),
        MY_STATE(D_STOPPED),
        finishedoffset(0),
        reply(nullptr),
        file(_filename),
        url(_url) {};