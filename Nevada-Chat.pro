QT += quick

SOURCES += \
        client/client.cpp \
        client/requests.cpp \
        client/responses.cpp \
        database.cpp \
        main.cpp \
        server/requests.cpp \
        server/responses.cpp \
        server/server.cpp

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    client/client.h \
    client/requests.h \
    client/responses.h \
    database.h \
    server/requests.h \
    server/responses.h \
    server/server.h
