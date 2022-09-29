#pragma once

#include <QDir>
#include <QThread>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>

typedef QPair<QString, QStringList> DBPair;
typedef QList<QStringList> DBData;

struct DB_Requests
{
  static QPair<QStringList, QStringList> splitOnColumnsAndData(QStringList data, QString exp = " = ");
  static QString conditionsBuild(QStringList conditions);

  static DBPair  insert(QString table, QStringList data);
  static DBPair  update(QString table, QStringList data, QStringList conditions = {});
  static QString select(QString table, QStringList columns, QStringList conditions = {});
  static QString remove(QString table, QStringList conditions);
};

class Database : public QObject
{
  Q_OBJECT
public:
 ~Database();
  Database(QObject *parent, qint64 thread_id, QString db_name);
  void readData(QString request, QList<QStringList> &result, QStringList values = {});
  void writeData(DBPair data);
  bool checkData(QString request);
  
  void changeDatabase(QString db_name) {m_database.setDatabaseName(db_name);}
  
private:
  QSqlDatabase m_database;
  QSqlQuery *m_query;
  QString m_connection_name;
};
