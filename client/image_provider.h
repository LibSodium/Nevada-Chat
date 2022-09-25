#pragma once

#include <QImage>
#include <QPainter>
#include <QDateTime>
#include <QQuickPaintedItem>

class ImageProvider : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int imageHeight READ imageHeight CONSTANT)
    Q_PROPERTY(int imageWidth  READ imageWidth  CONSTANT)

public:
    Q_INVOKABLE void download(QString savePath);
    Q_INVOKABLE bool isEmpty() {return m_image.isNull();}

    QImage image()    {return m_image;}
    int radius()      {return m_radius;}
    QString source()  {return m_source;}
    int imageHeight() {return m_image_height;}
    int imageWidth()  {return m_image_width;}

    void setRadius(int &radius);
    void setImage(QImage &image);
    void setSource(QString &path);

protected:
    void paint(QPainter *painter);

signals:
    void imageChanged();
    void radiusChanged();
    void sourceChanged();

private:
    QImage m_image;
    int m_radius = 0;
    int m_image_width;
    int m_image_height;
    QString m_source = "";
};

