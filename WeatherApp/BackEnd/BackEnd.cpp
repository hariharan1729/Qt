
#include "BackEnd.h"
#include <QNetworkReply>
#include "IResponse.h"
#include "Message.h"
#include "Parser.h"
#include <QString>
#include <memory>
//#include ""


BackEnd::BackEnd(std::shared_ptr<IResponse> pResponse, QObject *parent)
    :QObject(parent)
{
    connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
    m_pResponseMessage = pResponse;
}

void BackEnd::handleNetworkData(QNetworkReply *pNetworkReply) {
    if(nullptr == pNetworkReply)
    {
        return;
    }
    auto e = pNetworkReply->error();
    if (!e)
        digest(QString::fromUtf8(pNetworkReply->readAll()));
    else
        qDebug()<<"networkReply Error: "<< e;
    pNetworkReply->deleteLater();
}

void BackEnd::digest(const QString &data) {
    if(nullptr == m_pResponseMessage)
    {
        Q_ASSERT(nullptr != m_pResponseMessage);
        return;
    }
    auto pMessage = std::make_shared<Message>();
    Parser p;
    p.parse(data,pMessage);
    m_pResponseMessage->OnReply(pMessage);
}



void BackEnd::request(std::shared_ptr<IMessage> pRequestMessage) {
    if(nullptr == pRequestMessage)
    {
        qDebug()<<"pRequestMessage is nullptr";
        return;
    }
    m_manager.get(QNetworkRequest(QUrl(pRequestMessage->getReqMsg())));
}


