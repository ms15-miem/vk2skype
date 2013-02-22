#include "tester_skype.h"

Tester_Skype::Tester_Skype(QObject *parent) :
    QObject(parent)
{
    skype = new Skype("test", 8, this);
    QVERIFY(skype->connect());
}

void Tester_Skype::getChatFriendlyName()
{
    bool ok = false;
    QCOMPARE(skype->getChatFriendlyName(
                 "#narcjkeee/$leonid.postovski;ef476a24824f8b7f", ok), QString("code4food"));
    QVERIFY(ok);
}

QTEST_MAIN(Tester_Skype)
