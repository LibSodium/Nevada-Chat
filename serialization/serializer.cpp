#include "serializer.h"

Serializer::Serializer(QIODevice *device)
{
  m_device = device;
  if(!m_device->isOpen())
    m_device->open(QIODevice::ReadWrite);
  m_buffer.open(QIODevice::ReadWrite);
  m_stream.setDevice(&m_buffer);
  m_stream.setVersion(QDataStream::Qt_6_3);
  m_stream << qint64(0); // write empty 64 bit for writing data size in desctructor
}

Serializer::~Serializer()
{
  // -----------------------
  m_buffer.seek(0);
  m_stream << qint64(m_buffer.size());
  // ----------------------- write data size to empty 64 bits that we define in contructor

  m_device->write(m_buffer.buffer());
}
