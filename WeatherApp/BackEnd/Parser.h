#ifndef Parser_HEADER
#define Parser_HEADER

#include "IParser.h"
#include <QObject>
//#include "Message.h"

class QXmlStreamReader;
class IRequestMessage;
class Message;
class IMessage;


class Parser : public QObject ,public IParser
{
    Q_OBJECT

public:
    Parser() = default;
    ~Parser() = default;

    void parse(const QString &data, std::shared_ptr<IMessage> pIMessage);

private:
    void readTemp(QXmlStreamReader &xml, Message *message);
    void readDateTime(QXmlStreamReader &xml, Message* pMessage);


};
#endif
