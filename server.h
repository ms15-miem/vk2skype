#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "vk_mail/vk.h"
#include "skype/src/skype.h"

class Server : public QObject
{
    Q_OBJECT

private:
    Vk *vk;
    Skype *skype;

public:
    explicit Server(QObject *parent = 0);
    
signals:
    
public slots:

private slots:
    void slotWork(bool ready);
    
};

#endif // SERVER_H
