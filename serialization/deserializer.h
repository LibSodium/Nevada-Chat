#pragma once

#include <QBuffer>
#include <QIODevice>

/*
  The objects of this class can read data from device
  in the order in which they were written by Serializer
*/

class Deserializer
{
public:
  Deserializer(QIODevice *device);
  QDataStream &stream() {return m_stream;}
  QIODevice *device() {return m_device;}
  int bytesAvailable() {return m_buffer.bytesAvailable();} // returns how many bytes unread

private:
  QBuffer     m_buffer;
  QDataStream m_stream;
  QIODevice  *m_device;

private:
  void read(int size); // using for writing data from device to buffer
};
