#ifndef TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
#define TELEGRAM_REMOTE_SERVER_CONNECTION_HPP

#include <QObject>

#include "Peer.hpp"

namespace Telegram {

namespace Server {

class AbstractServerApi;
class AbstractUser;
class LocalServerApi;

class AbstractServerConnection : public QObject
{
    Q_OBJECT
public:
    explicit AbstractServerConnection(QObject *parent = nullptr);

    virtual quint32 dcId() const = 0;

    virtual AbstractUser *getUser(const UserId userId) const = 0;
    virtual AbstractUser *getUser(const QString &identifier) const = 0;
    virtual AbstractServerApi *api() = 0;

    virtual QByteArray getForeingUserAuthorization(UserId userId) = 0;
};

class RemoteServerConnection : public AbstractServerConnection
{
    Q_OBJECT
public:
    explicit RemoteServerConnection(QObject *parent = nullptr);

    quint32 dcId() const override;

    void setRemoteServer(LocalServerApi *remoteServer);

    AbstractUser *getUser(const UserId userId) const override;
    AbstractUser *getUser(const QString &identifier) const override;
    AbstractServerApi *api();

    QByteArray getForeingUserAuthorization(UserId userId);

protected:
    LocalServerApi *m_server = nullptr;
};

} // Server namespace

} // Telegram namespace

#endif // TELEGRAM_REMOTE_SERVER_CONNECTION_HPP
