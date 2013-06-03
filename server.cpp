#include "server.h"

#include <QDebug>

Server::Server(QObject *parent) :
    QObject(parent)
{
    vk = new Vk("3353341", "vk", this);
    vk->setKeepAuth(true);

    connect(vk, SIGNAL(setReady(bool)), SLOT(slotWork(bool)));
    vk->connect();

    Skype *skype = new Skype("vk2skype", 8, this);
    if (!skype->connect()) {
        qDebug() << "skype::connect() error";
        exit(1);
    }

    bool ok = false;

    QString chatFriendlyName = "MIEM";

    QStringList chatIds = skype->getBookmarkedChatIds(chatFriendlyName, ok);

    if (!ok) {
        qDebug() << "skype::getBookmarkedChatIds() error";
        exit(1);
    }

    if (chatIds.size() < 1) {
        qDebug() << chatFriendlyName + " has not been found in bookmarked chats";
        exit(1);
    }

    skype->setChatId(chatIds.at(0));

    connect(vk, SIGNAL(unreadedMessage(Message*)), skype, SLOT(sendChatMessage(Message*)));
}

void Server::slotWork(bool ready)
{
    if (qobject_cast<Vk*>(sender()) && ready) {
        vk->slotStartCheckCycle();
    }
}
