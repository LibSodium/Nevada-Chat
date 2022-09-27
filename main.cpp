#include "client/client.h"
#include "server/server.h"
#include "client/image_provider.h"

#include "server/sv_threads.h"

int main(int argc, char **argv)
{
   QGuiApplication app(argc, argv);
   QQmlApplicationEngine engine;
   QUrl entry;
   Client::Object = new Client();
   Server::Object = new Server();
   QScreen *screen = app.primaryScreen();
   QQmlContext *ctx = engine.rootContext();
   int screen_width = screen->geometry().width();
   int screen_height = screen->geometry().height();
   ctx->setContextProperty("screen_width", screen_width);
   ctx->setContextProperty("screen_height", screen_height);
   ctx->setContextProperty("cl", Client::Object);
   ctx->setContextProperty("sv", Server::Object);
   qmlRegisterType<ImageProvider>("Backend", 1, 0, "ImageProvider");

   // TEST ZONE DELETE AFTER TESTING
   Server::Object->start();
   
   // TEST ZONE DELETE AFTER TESTING

#ifdef Q_OS_ANDROID
   entry = "qrc:/client/android/main.qml";
#endif

#ifdef Q_OS_WIN
   entry = "qrc:/client/windows/main.qml";
#endif

   engine.load(entry);
   return app.exec();
}
