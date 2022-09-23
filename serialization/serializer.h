#pragma once

#include <QBuffer>
#include <QIODevice>

/*
  The objects of this class can write data to device
  It supports such objects as
  - QString
  - QList, QMap and other containers
  - int, qint32, qint64 and other number types
  - QImage, QPixmap
  - QByteArray
  - and many others...
*/

class Serializer
{
public:
  ~Serializer();
  Serializer(QIODevice *device);
  QDataStream &stream() {return m_stream;}

private:
  QBuffer     m_buffer;
  QDataStream m_stream;
  QIODevice  *m_device;
};
