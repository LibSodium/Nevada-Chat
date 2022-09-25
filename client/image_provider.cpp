#include "image_provider.h"

void ImageProvider::setImage(QImage &image)
{
    m_image.swap(image);
    m_image_width = m_image.width();
    m_image_height = m_image.height();
    emit imageChanged();
    update();
}

void ImageProvider::setRadius(int &radius)
{
  if(m_radius == radius) return;
  m_radius = radius;
  emit radiusChanged();
  update();
}

void ImageProvider::setSource(QString &path)
{
  m_source = path;
  QImage img(path);
  m_image.swap(img);
  m_image_width = m_image.width();
  m_image_height = m_image.height();
  emit sourceChanged();
  update();
}

void ImageProvider::download(QString savePath)
{
    if(!m_image.isNull())
    {
        QString name = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss-zzz") + ".jpg";
        m_image.save(savePath + name, "jpg", 100);
    }
}

void ImageProvider::paint(QPainter *painter)
{
    if(m_image.isNull()) return;
    QRectF bounding_rect = boundingRect();
    float coof_w = 1;
    float coof_h = 1;
    if(m_image.width() > m_image.height())
    {
        coof_w = float(m_image.width()) / float(m_image.height());
    }
    else
    {
        coof_h = float(m_image.height()) / float(m_image.width());
    }
    QImage scaled =  m_image.scaled(bounding_rect.width() * coof_w, bounding_rect.height() * coof_h, Qt::KeepAspectRatio);
    QTransform transform(1, 0, 0, 1, scaled.width() / 2 + width() / 2, scaled.height() / 2 + height() / 2);
    QBrush brush(scaled);
    brush.setTransform(transform);
    painter->setBrush(brush);
    painter->drawRoundedRect(bounding_rect, m_radius, m_radius);
    setAntialiasing(true);
}
