#ifndef TRACING_H
#define TRACING_H

#include <QString>
#include <QDebug>
#include <QTextStream>


namespace TraceVariable
{
    static bool gsTraceEnabled = false;
    static bool gsInfoFlag = false;
}


enum TraceType : int32_t
{
    TRACEERROR = 0,
    WARNING,
    INFO
};

inline void TraceOutMessage(QString message)
{
    qDebug()<< message << Qt::endl;
}

inline void Trace(const TraceType type, QString message)
{
    if(!TraceVariable::gsTraceEnabled)
    {
        return;
    }

    switch(type)
    {
        case TraceType::TRACEERROR:
            TraceOutMessage(message.prepend("ERROR : "));
            break;
        case TraceType::WARNING:
            TraceOutMessage(message.prepend("WARNING : "));
            break;
        case TraceType::INFO:
            return TraceVariable::gsInfoFlag ? TraceOutMessage(message.prepend("INFO : ")) : void() ;
        default:
            break;
    }
}

#endif // TRACING_H
