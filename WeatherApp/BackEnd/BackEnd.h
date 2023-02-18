#ifndef BackEnd_HEADER
#define BackEnd_HEADER

#include <QObject>
#include <QNetworkAccessManager>

class QNetworkReply;
class QXmlStreamReader;
class IRequestMessage;
class IResponse;
class IMessage;
class Message;
class QString;


class BackEnd : public QObject
{
    Q_OBJECT

public:
    BackEnd(std::shared_ptr<IResponse> pResponse,QObject *parent = nullptr);
    void request(std::shared_ptr<IMessage> pRequestMessage);
private slots:
    void handleNetworkData(QNetworkReply *pNetworkReply);

private:
    void digest(const QString &data);

private:
     QNetworkAccessManager m_manager;
     std::shared_ptr<IRequestMessage> m_pRequestMessage = nullptr;
     std::shared_ptr<IResponse> m_pResponseMessage = nullptr;

};
#endif
