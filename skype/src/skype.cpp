#include "skype.h"

Skype::Skype(QString _appName, uint _protocol, QObject *parent):
    QObject(parent), appName(_appName), protocol(_protocol)
{
}

bool Skype::connect()
{
    bool ok = false;

    QString skypeServiceName("com.Skype.API");
    iface = new QDBusInterface(skypeServiceName, "/com/Skype", "com.Skype.API",
                               QDBusConnection::sessionBus(), this);

    if (QDBusConnection::sessionBus().isConnected()) {
        if (iface->isValid()) {
            // tell Skype that an application called appName wants to communicate with it
            reply = iface->call("Invoke", "NAME " + appName);

            if (reply.isValid() && reply.value() == "OK") {
                // specify the protocol
                reply = iface->call("Invoke", QString("PROTOCOL ") + QString::number(protocol));
                if (reply.isValid() && reply.value() == QString("PROTOCOL ") + QString::number(protocol)) {
                    ok = true;
                }
            }
        }
    }
    return ok;
}

void Skype::setChatId(QString _chatId)
{
    chatId = _chatId;
}

QStringList Skype::getBookmarkedChatIds(QString chatFriendlyName, bool &ok)
{
    QStringList ans;

    QStringList ids = searchBookmarkedChats(ok);
    if (ok) {
        foreach(QString id, ids) {
            QString name = getChatFriendlyName(id, ok);
            if (!ok) return ans;
            if (name == chatFriendlyName) {
                ans << id;
            }
        }
    }

    return ans;
}

QStringList Skype::searchBookmarkedChats(bool &ok)
{
    QStringList ans;

    QDBusReply<QString> reply = invoke("SEARCH BOOKMARKEDCHATS");
    if (reply.isValid() && reply.value().startsWith("CHATS")) {
        ok = true;
        // CHATS #bitman/$jessy;eb06e65612353279, #bitman/$jdenton;9244e98f82d7d391
        qDebug() << reply.value();
        QString chats = reply.value().mid(6);
        ans = chats.split(", ");
    }
    else {
        ok = false;
    }

    return ans;
}

QString Skype::getChatFriendlyName(QString id, bool &ok)
{
    QString ans;
    QDBusReply<QString> reply = invoke("GET CHAT " + id + " FRIENDLYNAME");
    if (reply.isValid() && static_cast<QString>(reply.value()).startsWith("CHAT")) {
        ok = true;
        ans = static_cast<QString>(reply.value()).mid(
                    QString("CHAT " + id + " FRIENDLYNAME ").size());
    }
    else {
        ok = false;
    }
    return ans;
}

bool Skype::sendChatMessage(QString _chatId, Message *message)
{
    QString msg = message->getText();
    message->deleteLater();

    reply = iface->call("Invoke", "CHATMESSAGE " + _chatId + " " + msg);
    if (reply.isValid() && reply.value() == "CHATMESSAGE " + _chatId + " STATUS SENDING") {
        return true;
    }
    else {
        return false;
    }
}

bool Skype::sendChatMessage(Message *message)
{
    if (chatId.isNull()) {
        qDebug() << "chatId is not initialized";
        exit(1);
    }
    return this->sendChatMessage(chatId, message);
}



QDBusReply<QString> Skype::invoke(QString command)
{
    //                    reply = iface.call("Invoke", "CALL echo123");
    reply = iface->call("Invoke", command);
    return reply;
}
