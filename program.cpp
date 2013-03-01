#include <QCoreApplication>
#include <QNetworkProxy>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    a.setQuitOnLastWindowClosed(false);
    a.setApplicationName("vk2skype");

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName("127.0.0.1");
    proxy.setPort(9999);
    QNetworkProxy::setApplicationProxy(proxy);

    Server server;

    return a.exec();
}
