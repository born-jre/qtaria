//
// Created by bing on 1/15/18.
//

#ifndef SRC_ARIAHANDLER_H
#define SRC_ARIAHANDLER_H

#include<aria2/aria2.h>
#include "../downloaderinterface.h"

static int downloadEventCallback(aria2::Session* session, aria2::DownloadEvent event, aria2::A2Gid gid, void* userData);

class ariahandler: public DownloaderInterface {


public slots:
    ariahandler();
    void addNewDownload( QString url);
    void pauseItem(int id) override {}
    void resumeItem(int id) override {}
    void deleteItem(int id) override {}
private:

    //aria stuff
    aria2::Session* session;
    aria2::SessionConfig config;
    aria2::KeyVals options;
    aria2::GlobalStat gstat;
    bool running = false;
    void run();
};

static ariahandler * me;

#endif //SRC_ARIAHANDLER_H
