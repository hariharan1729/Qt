
#include "Parser.h"
#include "Message.h"
#include <QXmlStreamReader>
#include <QRegularExpression>
#include <iostream>
#include <string>
#include <QtGlobal>
#include "Utils.h"
#include <QString>

const QRegularExpression regx("[\r\n]");
const QString space(" ");


void Parser::parse(const QString &data, std::shared_ptr<IMessage> pIMessage)
{
    QXmlStreamReader xml(data);
    int numberOfFeaturesRead = 0;
    //bool foundCurrentForecast = false;
    auto message = dynamic_cast<Message*>(pIMessage.get());

    while (!xml.atEnd()) {
        xml.readNext();
        auto tkttpe = xml.tokenType();
//        qDebug()<<"tokenType : "<<tkttpe;
//        qDebug()<<"name  : "<<xml.name();
        if (tkttpe == QXmlStreamReader::StartElement) {
            if (xml.name() == u"doubleOrNilReasonTupleList") {
               //qDebug()<<  "value of doubleOrNilReasonTupleList = " << xml.readElementText();
               readTemp(xml,message);
               numberOfFeaturesRead++;
            }
            else if (xml.name() == u"positions") {
//               qDebug()<<  "value of positions = " << xml.readElementText();
               readDateTime(xml,message);
               numberOfFeaturesRead++;
            }
            else if(2 == numberOfFeaturesRead)
            {
                return;
            }

        }
    }
}

void Parser::readTemp(QXmlStreamReader &xml,Message* pMessage)
{
    if(nullptr == pMessage)
    {
        Q_ASSERT(nullptr != pMessage);
        return;
    }
//    pMessage->setMessageType(Message::MessageType::TEMPERATURE);

    qDebug()<<  "Temperature = ";
    QString tempLists = xml.readElementText().replace(space, "");
    auto tempList = tempLists.split(regx,Qt::SkipEmptyParts);
    for(const auto &t : tempList)
    {
        qDebug() << t;
        pMessage->setTemperatureMessage(t);
    }

}

void Parser::readDateTime(QXmlStreamReader &xml, Message *pMessage) {
    if(nullptr == pMessage)
    {
        Q_ASSERT(nullptr != pMessage);
        return;
    }
//    pMessage->setMessageType(Message::MessageType::DATETIME);
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

}




