
#include "BackEnd.h"
#include <QXmlStreamReader>
#include <QNetworkReply>
#include <QtGlobal>
#include "Utils.h"
#include <iostream>
#include <string>
#include "IResponse.h"
#include "Message.h"
#include <QRegularExpression>

const QRegularExpression regx("[\r\n]");
const QString space(" ");


BackEnd::BackEnd(std::shared_ptr<IResponse> pResponse, QObject *parent)
{
    connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));


    m_pResponseMessage = pResponse;
}

void BackEnd::handleNetworkData(QNetworkReply *networkReply) {
    //QUrl url = networkReply->url();
    auto e = networkReply->error();
    if (!e)
        digest(QString::fromUtf8(networkReply->readAll()));
    else
        qDebug()<<"networkReply Error: "<< e;
    networkReply->deleteLater();
}

void BackEnd::digest(const QString &data) {

    QXmlStreamReader xml(data);

    //bool foundCurrentForecast = false;
    while (!xml.atEnd()) {
        xml.readNext();
        auto tkttpe = xml.tokenType();
//        qDebug()<<"tokenType : "<<tkttpe;
//        qDebug()<<"name  : "<<xml.name();
        if (tkttpe == QXmlStreamReader::StartElement) {
            if (xml.name() == u"doubleOrNilReasonTupleList") {
               //qDebug()<<  "value of doubleOrNilReasonTupleList = " << xml.readElementText();
               readTemp(xml);
            }
            else if (xml.name() == u"positions") {
//               qDebug()<<  "value of positions = " << xml.readElementText();
               readDateTime(xml);
            }
        }
    }

}

void BackEnd::readTemp(QXmlStreamReader &xml)
{
    if(nullptr == m_pResponseMessage)
    {
        Q_ASSERT(nullptr != m_pResponseMessage);
        return;
    }
   auto pMessage = std::make_shared<Message>();;
    if(nullptr == pMessage)
    {
        Q_ASSERT(nullptr != pMessage);
        return;
    }
    qDebug()<<  "Temperature = ";
    QString tempLists = xml.readElementText().replace(space, "");
    auto tempList = tempLists.split(regx,Qt::SkipEmptyParts);
    for(const auto &t : tempList)
    {
        qDebug() << t;
        pMessage->setTemperatureMessage(t);
    }
    m_pResponseMessage->OnReply(pMessage);
}

void BackEnd::readDateTime(QXmlStreamReader &xml) {
    if(nullptr == m_pResponseMessage)
    {
        Q_ASSERT(nullptr != m_pResponseMessage);
        return;
    }
    auto pMessage = std::make_shared<Message>();;
    if(nullptr == pMessage)
    {
        Q_ASSERT(nullptr != pMessage);
        return;
    }
    qDebug()<<  "DateTime = ";
    QString tempLists = xml.readElementText();
    auto tempList = tempLists.split(regx,Qt::SkipEmptyParts);
    for(auto &t : tempList)
    {
      auto s = t.simplified().split(space,Qt::SkipEmptyParts);
      if(!s.isEmpty())
      {
           qDebug() << s.last()/*.replace(space, "")*/;
           pMessage->setTimeMessage(s.last());
      }
    }
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


