#include "database.h"

QPair<QStringList, QStringList> DB_Requests::splitOnColumnsAndData(QStringList data, QString exp)
{
  QStringList columns, values;
  for(auto &element : data)
    {
      columns << element.section(exp, 0, 0);
      values  << element.section(exp, 1);
    }
  return {columns, values};
}

QString DB_Requests::conditionsBuild(QStringList conditions)
{
  if(conditions.isEmpty()) return NULL;

  if(conditions.first().startsWith("*"))
    {
      conditions.first().remove(0, 1);
      return " " + conditions.first();
    }

  QStringList possible_operators = {" > ", " = ", " < ", " >= ", " <= ", " != "};

  QStringList where;
  QString order;

  for(auto &condition : conditions)
    {
      for(auto &_operator : possible_operators)
        {
          if(condition.contains(_operator))
            {
              QString column = condition.section(_operator, 0, 0);
              QString value = _operator + "'" + condition.section(_operator, 1) + "'";
              where << (column + value);
              break;
            }
        }
      if(condition.contains("ORDER", Qt::CaseInsensitive))
        {
          order = condition;
        }
    }

  QStringList columns, values;
  {
    QPair<QStringList, QStringList> data_splited = splitOnColumnsAndData(conditions);
    columns = data_splited.first;
    values = data_splited.second;
  }
  QString out;
  if(!where.isEmpty()) out += " WHERE ";
  out += where.join(" AND ") + " " + order;
  return out;
}

QPair<QString, QStringList> DB_Requests::insert(QString table, QStringList data)
{
  QStringList columns, values;
  {
    QPair<QStringList, QStringList> data_splited = splitOnColumnsAndData(data);
    columns = data_splited.first;
    values = data_splited.second;
  }
  QString request = "INSERT INTO " + table + " (";
  for(auto &column : columns)
    {
      if(column == columns.last())
        {
          request += column + ") VALUES (";
          break;
        }
      request += column + ", ";
    }
  for(auto &column : columns)
    {
      if(column == columns.last())
        {
          request += "?)";
          break;
        }
      request += "?, ";
    }
  return {request, values};
}

QString DB_Requests::select(QString table, QStringList columns, QStringList conditions)
{
  QString request = "SELECT ";
  if(columns.isEmpty()) request += "*";
  for(auto &column : columns)
    {
      if(column == columns.last())
        {
          request += column;
          break;
        }
      request += column + ", ";
    }
  request += " FROM " + table + conditionsBuild(conditions);
  return request;
}

QPair<QString, QStringList> DB_Requests::update(QString table, QStringList data, QStringList conditions)
{
  QStringList columns, values;
  {
    QPair<QStringList, QStringList> data_splited = splitOnColumnsAndData(data);
    columns = data_splited.first;
    values = data_splited.second;
  }
  QString request = "UPDATE " + table + " SET ";
  for(auto &column : columns)
    {
      if(column == columns.last())
        {
          request += column + " = ? ";
          break;
        }
      request += column + " = ?, ";
    }
  request += conditionsBuild(conditions);
  return {request, values};
}

QString DB_Requests::remove(QString table, QStringList conditions)
{
  QString request = "DELETE FROM " + table + conditionsBuild(conditions);
  return request;
}

Database::Database(QObject *parent, qint64 thread_id, QString db_name) : QObject(parent)
{
  m_connection_name = QString::number(thread_id);
  m_database = QSqlDatabase::addDatabase("QSQLITE", m_connection_name);
  m_database.setDatabaseName(db_name);
  m_database.open();
  m_query = new QSqlQuery(m_database);
}

Database::~Database()
{
  m_database = QSqlDatabase();
  QSqlDatabase::removeDatabase(m_connection_name);
  delete m_query;
}

void Database::readData(QString request, QList<QStringList> &result, QStringList values)
{
  if(!request.isEmpty())
    {
      m_query->prepare(request);
      if(!values.isEmpty())
        {
          while(!values.isEmpty()) m_query->addBindValue(values.takeFirst());
        }
      if(m_query->exec())
        {
          int n_columns = m_query->record().count();
          QStringList row;
          while(m_query->next())
            {
              row.clear();
              for(int i = 0; i < n_columns; i++)
                {
                  row << m_query->value(i).toString();
                }
              result << row;
            }
        }
      else
        {
          qDebug() << "database read data error ->" << m_query->lastError().text();
        }
    }
  else
    {
      qDebug() << "database read data error -> request is empty";
    }
}

void Database::writeData(DBPair data)
{
  QString request = data.first;
  QStringList values = data.second;
  qDebug() << request << values;
  if(!request.isEmpty())
    {
      m_query->prepare(request);
      if(!values.isEmpty())
        {
          while(!values.isEmpty()) m_query->addBindValue(values.takeFirst());
        }
      if(m_query->exec())
        {
          qDebug() << "database write data success ->" << m_query->lastQuery();
        }
      else
        {
          qDebug() << "database write data error ->" << m_query->lastError().text();
        }
    }
  else
    {
      qDebug() << "database write data error -> request is empty";
    }
}

bool Database::checkData(QString request)
{
    if(m_query->exec(request))
    {
        if(m_query->next())
        {
            m_query->clear();
            return true;
        }
        else
        {
            m_query->clear();
            return false;
        }
    }
    else
    {
        qDebug() << "database check data error ->" << m_query->lastError().text();
        m_query->clear();
        return false;
    }
}
