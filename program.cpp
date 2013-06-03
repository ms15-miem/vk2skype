#include <QCoreApplication>
#include <QNetworkProxy>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.setApplicationName("vk2skype");

    Server server;

    return a.exec();
}
