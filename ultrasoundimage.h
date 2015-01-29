#ifndef ULTRASOUNDIMAGE_H
#define ULTRASOUNDIMAGE_H

#include <QObject>
#include <QColor>

#include "organ.h"

class UltraSoundImage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ getImagePath CONSTANT)
    Q_PROPERTY(QString mappedImagePath READ getMappedImagePath CONSTANT)
public:
    explicit UltraSoundImage(int imageId, QObject *parent = nullptr);

signals:

public slots:
    QString getImagePath() const;
    QString getMappedImagePath() const;
    bool hasOrganTypeAtPosition(int x, int y, Organ::Type organ) const;


private:
    int m_imageId;
    bool hasColorInArea(int x, int y, QRgb color, int radius=10) const;
};

#endif // ULTRASOUNDIMAGE_H
