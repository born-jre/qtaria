#include <iostream>
#include "ariahandler.h"

ariahandler::ariahandler() {
    aria2::libraryInit();
    config.downloadEventCallback = downloadEventCallback;
    session = aria2::sessionNew(aria2::KeyVals(), config);
    me = this;

}

void ariahandler::addNewDownload( QString url) {

    std::vector<std::string> urls = {url.toStdString()};
    std::string dirlocation; //= {location.toStdString()};
    aria2::KeyVals options;
    options.push_back(std::pair<std::string, std::string> ("dir", dirlocation=""));
    options.push_back(std::pair<std::string, std::string> ("continue","false"));
    aria2::A2Gid gid;
    int rv = aria2::addUri(session, &gid, urls, options);
    uint fid = gid;
    if(rv < 0) {
        fid = 0;
        std::cout<<"Failed";
        return;
    }
    if(!running) {
        this->run();
    }
}

void ariahandler::run() {
    auto start = std::chrono::steady_clock::now();
    int flag = 0;
    for (;;) {
        int rv = aria2::run(session, aria2::RUN_ONCE);
        if (rv != 1) {
            break;
        }
        // the application can call aria2 API to add URI or query progress
        // here
        auto now = std::chrono::steady_clock::now();
        auto count =
                std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
                        .count();
        // Print progress information once per 500ms
        if (count >= 500) {
            flag++; //TEMP
            start = now;
            aria2::GlobalStat gstat = aria2::getGlobalStat(session);
            
          //OO  emit globalDownloadStat(gstat.numWaiting,gstat.numActive,gstat.downloadSpeed,gstat.uploadSpeed);

            std::vector<aria2::A2Gid> gids = aria2::getActiveDownload(session);
            for (const auto& gid : gids) {
                aria2::DownloadHandle* dh = aria2::getDownloadHandle(session, gid);
                
                if(flag>10) {
				//try to resume
				std::cout<<"pausing"<<std::endl;
				aria2::pauseDownload(session,gid,true);
				
				}
                
                if (dh) {
                    uint id = gid;
                    uint i = (dh->getTotalLength() > 0 ? (100 * dh->getCompletedLength() /dh->getTotalLength()): 0);
                    std::cout<<"emiting"<< flag <<std::endl;
                    emit signal_update_item_stats(i);
                   //OO emit downloadStatPerItem(gid,dh->getCompletedLength()/1024,dh->getTotalLength()/1024,dh->getDownloadSpeed()/1024,dh->getUploadSpeed() / 1024);
                    }
            }
        }
    }
    //int rv = aria2::sessionFinal(session);
//aria2::libraryDeinit();
}





















static int downloadEventCallback(aria2::Session* session, aria2::DownloadEvent event, aria2::A2Gid gid, void* userData) {
    uint id = gid; //A2Gid is not Qtmetobject so
    switch (event) {
        case aria2::EVENT_ON_DOWNLOAD_COMPLETE: {
            std::cerr << "COMPLETE";
            break;
        }
        case aria2::EVENT_ON_DOWNLOAD_ERROR: {
            std::cerr << "ERROR";
            break;
        }
        default:
            return 0;
    }
}

