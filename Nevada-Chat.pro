QT += quick qml sql network

HEADERS += \
    client/cl_responses.h \
    client/cl_threads.h \
    client/client.h \
    client/image_provider.h \
    database.h \
    serialization/deserializer.h \
    serialization/serializer.h \
    server/server.h \
    server/sv_requests.h \
    server/sv_responses.h \
    server/sv_threads.h \
    settings.h \
    values.h

SOURCES += \
        client/cl_requests.cpp \
        client/cl_responses.cpp \
        client/cl_threads.cpp \
        client/client.cpp \
        client/image_provider.cpp \
        database.cpp \
        main.cpp \
        serialization/deserializer.cpp \
        serialization/serializer.cpp \
        server/server.cpp \
        server/sv_requests.cpp \
        server/sv_responses.cpp \
        server/sv_threads.cpp \
        settings.cpp

RESOURCES += qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


