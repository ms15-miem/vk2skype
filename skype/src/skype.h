#ifndef SKYPE_H
#define SKYPE_H

#include <QtDBus>
#include <QStringList>
#include "vk_mail/message.h"

class Skype : public QObject
{
    Q_OBJECT

private:
    QDBusReply<QString> reply;
    QDBusInterface *iface;
    QString appName;
    uint protocol;
    QString chatId;

public:
    /**
     * @brief Skype - отправитель сообщений в конференцию, вначале нужно вызвать connect()
     * @param protocol - версия протокола
     * @param appName - имя должно быть без пробелов
     */
    explicit Skype(QString _appName, uint _protocol = 8, QObject *parent = 0);

    /**
     * @brief connect - подключаемся к d-bus, авторизовываем приложение, устанавливаем версию протокола
     * @return - returns true if no error occurred; otherwise, returns false
     */
    bool connect();

    void setChatId(QString _chatId);

    /**
     * @brief getBookmarkedChatIds - возвращает id чатов с именем chatName, добавленных в закладки!
     * @param chatFriendlyName - name shown in chat window title
     * @param ok
     * @return - список ids
     */
    QStringList getBookmarkedChatIds(QString chatFriendlyName, bool &ok);

    /**
     * @brief searchBookmarkedChats
     * @return - returns a list of chat IDs of chats which are bookmarked.
     */
    QStringList searchBookmarkedChats(bool &ok);

    /**
     * @brief getChatFriendlyName - returns name shown in chat window title
     * @param id
     * @param ok
     * @return - returns name shown in chat window title
     */
    QString getChatFriendlyName(QString id, bool &ok);

signals:

public slots:
    /**
     * @brief sendChatMessage - отправляем сообщение в чат
     * @param chatId - идентификатор чата, например "#narcjkeee/$leonid.postovski;ef476a24824f8b7f"
     * @param msg - сообщение
     * @return - returns true if no error occurred; otherwise, returns false
     */
    bool sendChatMessage(QString _chatId, Message *message);

    bool sendChatMessage(Message *message);

    /**
     * @brief invoke - выполнть команду в skype
     * @param command - команда
     * @return - QDBusReply::value() returns the remote function's calls return value.
     * If the remote call returned with an error, the return value of this function is undefined
     * and may be undistinguishable from a valid return value.
     * QDBusReply::isValid() returns true if no error occurred; otherwise, returns false.
     */
    QDBusReply<QString> invoke(QString command);
};



//Skype skype("test", 8);
//if (skype.connect()) {
//    bool ok = false;
//    QStringList list = skype.getBookmarkedChatIds("code4food", ok);
//    if (ok) {
//        foreach(QString line, list) {
//            qDebug() << line;
//        }
//    }

//    skype.invoke("CALL echo23");

//    skype.sendChatMessage(skype.getBookmarkedChatIds(QString("code4food"), ok).at(0),
//                          QString::fromUtf8("парамс"));
//}


#endif // SKYPE_H
