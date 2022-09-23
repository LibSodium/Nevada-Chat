#include "client/client.h"
#include "server/server.h"

int main(int argc, char **argv)
{
   QGuiApplication app(argc, argv);
   QQmlApplicationEngine engine;
   QUrl entry;

#ifdef Q_OS_ANDROID
   entry = "qrc:/client/android/main.qml";
#endif

#ifdef Q_OS_WIN
   entry = "qrc:/client/windows/main.qml";
#endif

   engine.load(entry);
   return app.exec();
}
