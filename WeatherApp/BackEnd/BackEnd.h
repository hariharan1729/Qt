#ifndef BackEnd_HEADER
#define BackEnd_HEADER

#include <QObject>
#include <QNetworkAccessManager>

//class QNetworkAccessManager;
class QNetworkReply;
class QXmlStreamReader;
class IRequestMessage;
class IResponse;
class IMessage;


class BackEnd : public QObject
{
    Q_OBJECT

public:
    BackEnd(std::shared_ptr<IResponse> pResponse,QObject *parent = nullptr);
    void request(std::shared_ptr<IMessage> pRequestMessage);
private slots:
    void handleNetworkData(QNetworkReply *networkReply);

private:
    void digest(const QString &data);
    void readTemp(QXmlStreamReader &xml);
    void readDateTime(QXmlStreamReader &xml);
private:
     QNetworkAccessManager m_manager;
     std::shared_ptr<IRequestMessage> m_pRequestMessage = nullptr;
     std::shared_ptr<IResponse> m_pResponseMessage = nullptr;

//signals:
//    void newDataRecieved(std::shared_ptr<IResponse> pResponseMessage);

};
#endif
