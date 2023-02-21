#ifndef Renderer_HEADER
#define Renderer_HEADER


#include <QObject>
#include <QtGlobal>

class BackEnd;
class IResponse;
class IMessage;

class Renderer : public QObject
{
    Q_OBJECT

public:
    Renderer(QObject *parent = nullptr);
    ~Renderer();
    void setReqMsg(const QString& msg);


private:
    std::shared_ptr<BackEnd> m_pBackEnd = nullptr;
    std::shared_ptr<IResponse> m_pResponse = nullptr;

public slots:
    void OnnewDataRecieved(std::shared_ptr<IMessage> pReplyMessage);

 signals:
    void newMessagePosted(std::shared_ptr<IMessage> pReplyMessage);


};
#endif
