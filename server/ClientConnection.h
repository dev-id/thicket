#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QTcpSocket>
#include "messages.pb.h"
#include "Logging.h"

class ClientConnection : public QTcpSocket
{
    Q_OBJECT

public:

    ClientConnection( const Logging::Config& loggingConfig = Logging::Config(), QObject* parent = 0 );

    bool sendMsg( const thicket::ServerToClientMsg* const protoMsg );

    uint64_t getBytesSent() const { return mBytesSent; }
    uint64_t getBytesReceived() const { return mBytesReceived; }

signals:
    void msgReceived( const thicket::ClientToServerMsg* const protoMsg );

private slots:
    void handleReadyRead();

private:

    quint16 mIncomingMsgHeader;

    uint64_t mBytesSent;
    uint64_t mBytesReceived;

    std::shared_ptr<spdlog::logger> mLogger;
};

#endif