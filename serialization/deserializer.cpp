#include "deserializer.h"

Deserializer::Deserializer(QIODevice *device)
{
  m_device = device;
  if(!m_device->isOpen())
    m_device->open(QIODevice::ReadWrite);
  m_buffer.open(QIODevice::ReadWrite);
  m_stream.setDevice(&m_buffer);
  m_stream.setVersion(QDataStream::Qt_6_3);

  // -----------------------
  read(sizeof(qint64));
  m_buffer.seek(0);
  qint64 data_size;
  m_stream >> data_size;
  // ----------------------- reading data size first

  // -----------------------
  read(data_size);
  m_buffer.seek(sizeof(qint64));
  // ----------------------- reading rest of data and place buffer pos after data
  // so now we can get data written by the Serializer by using 'stream'
}

void Deserializer::read(int size)
{
  // -----------------------
  while(m_buffer.size() < size)
    {
      if(!m_device->bytesAvailable())
        {
          m_device->waitForReadyRead(3000);
        }
      m_buffer.write(m_device->read(size - m_buffer.size()));

    }
  // ----------------------- reading data from device and writing it to buffer
  // until buffer size less than size that we define in Serializer
}
