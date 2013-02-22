#include <QDebug>
#include "skype.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Skype skype("test", 8);
    if (skype.connect()) {
        bool ok = false;
        QStringList list = skype.getBookmarkedChatIds("code4food", ok);
        if (ok) {
            foreach(QString line, list) {
                qDebug() << line;
            }
        }

        skype.invoke("CALL echo123");

        skype.sendChatMessage(skype.getBookmarkedChatIds(QString("code4food"), ok).at(0),
                              QString::fromUtf8("парамс"));
    }
}
