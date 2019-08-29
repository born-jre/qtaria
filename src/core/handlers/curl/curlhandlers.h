#ifndef CURLHANDLERS_H
#define CURLHANDLERS_H

#include<curl/curl.h>
#include "../downloaderinterface.h"
#include <string>
#include <cstdio>
#include <QWidget>
class CurlHandlers : public DownloaderInterface
{
   // Q_OBJECT

public:
    //CurlHandlers(): Handler() { }
    //CurlHandlers(QWidget *p = nullptr): Handler(p) { }
    //    ~CurlHandlers();
public slots:
    void addNewDownload( QString url);
    void pauseItem(qint32 id) override {}
    void resumeItem(qint32 id) override {}
    void deleteItem(qint32 id) override {}
private:
    CURLcode res;
    FILE *outfile;

};

#endif // CURLHANDLERS_H
