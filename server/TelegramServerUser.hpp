#ifndef TELEGRAMSERVERUSER_HPP
#define TELEGRAMSERVERUSER_HPP

#include <QObject>
#include <QVector>

namespace Telegram {

namespace Server {

class Session;
class User;

class RemoteUser
{
public:
    virtual quint32 id() const = 0;
    virtual QString phoneNumber() const = 0;
    virtual QString firstName() const = 0;
    virtual QString lastName() const = 0;
    virtual bool isOnline() const = 0;
    virtual quint32 dcId() const = 0;
};

class User : public QObject, public RemoteUser
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);

    quint32 id() const { return m_id; }
    QString phoneNumber() const { return m_phoneNumber; }
    void setPhoneNumber(const QString &phoneNumber);

    QString firstName() const { return m_firstName; }
    void setFirstName(const QString &firstName);

    QString lastName() const { return m_lastName; }
    void setLastName(const QString &lastName);

    bool isOnline() const;

    quint32 dcId() const { return m_dcId; }
    void setDcId(quint32 id);

    Session *getSession(quint64 authId) const;
    QVector<Session*> sessions() const { return m_sessions; }
    QVector<Session*> activeSessions() const;
    bool hasActiveSession() const;
    void addSession(Session *session);

    bool hasPassword() const { return !m_passwordSalt.isEmpty() && !m_passwordHash.isEmpty(); }
    QByteArray passwordSalt() const { return m_passwordSalt; }
    QByteArray passwordHash() const { return m_passwordHash; }

    void setPlainPassword(const QString &password);
    void setPassword(const QByteArray &salt, const QByteArray &hash);

    QString passwordHint() const { return QString(); }

signals:
    void sessionAdded(Session *newSession);
    void sessionDestroyed(Session *destroyedSession);

protected:
    quint32 m_id = 0;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_userName;
    QByteArray m_passwordSalt;
    QByteArray m_passwordHash;
    QVector<Session*> m_sessions;
    quint32 m_dcId = 0;
};

} // Server

} // Telegram

#endif // TELEGRAMSERVERUSER_HPP
