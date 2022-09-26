QT += quick qml sql network

HEADERS += \
    client/client.h \
    client/image_provider.h \
    client/responses.h \
    database.h \
    serialization/deserializer.h \
    serialization/serializer.h \
    server/requests.h \
    server/responses.h \
    server/server.h \
    settings.h \
    values.h

SOURCES += \
        client/client.cpp \
        client/image_provider.cpp \
        client/responses.cpp \
        database.cpp \
        main.cpp \
        serialization/deserializer.cpp \
        serialization/serializer.cpp \
        server/requests.cpp \
        server/responses.cpp \
        server/server.cpp \
        settings.cpp

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


