#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(false);
    a.setApplicationName("vk2skype");

    Server server;

    return a.exec();
}
