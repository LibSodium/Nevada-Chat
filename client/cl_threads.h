#pragma once

#include <QThread>

class ConnectionTracker : public QThread
{
    Q_OBJECT
public:
    ConnectionTracker();
    
};
