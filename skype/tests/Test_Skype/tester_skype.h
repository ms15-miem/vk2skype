#ifndef TESTER_SKYPE_H
#define TESTER_SKYPE_H

#include <QTest>
#include "../../src/skype.h"

class Tester_Skype : public QObject
{
    Q_OBJECT
private:
    Skype *skype;

public:
    explicit Tester_Skype(QObject *parent = 0);
    
signals:
    
public slots:

private slots:
    void getChatFriendlyName();
};

#endif // TESTER_SKYPE_H
