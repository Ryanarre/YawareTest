#include "imagecomparator.h"

#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QColor>
#include <QCryptographicHash>

ImageComparator::ImageComparator()
{}

QPixmap convertToGrayScale(const QPixmap& pixmap) {
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        return QPixmap();
    }

    image = image.convertToFormat(QImage::Format_Grayscale8);

    QPixmap grayScalePixmap(image.size());
    grayScalePixmap.fill(Qt::transparent);
    QPainter painter(&grayScalePixmap);
    painter.drawImage(0, 0, image);
    painter.end();

    return grayScalePixmap;
}

int calculateAverageIntensity(const QPixmap& pixmap) {
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        return -1;
    }

    int totalIntensity = 0;

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            totalIntensity += qGray(image.pixel(x, y));
        }
    }

    int totalPixels = image.width() * image.height();
    return totalIntensity / totalPixels;
}

QPixmap applyThreshold(const QPixmap& pixmap, int thresholdValue) {
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        return QPixmap();
    }

    QImage thresholdedImage = image;

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);
            int grayValue = qGray(pixel);

            if (grayValue < thresholdValue) {
                thresholdedImage.setPixel(x, y, qRgb(0, 0, 0));
            } else {
                thresholdedImage.setPixel(x, y, qRgb(255, 255, 255));
            }
        }
    }

    return QPixmap::fromImage(thresholdedImage);
}

QByteArray calculateHashSum(const QPixmap& pixmap) {
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        return QByteArray();
    }

    image = image.convertToFormat(QImage::Format_Grayscale8);

    QByteArray pixelData(reinterpret_cast<const char*>(image.bits()), image.byteCount());

    return QCryptographicHash::hash(pixelData, QCryptographicHash::Md5);
}

int calculateHammingDistance(const QByteArray& hashSum1, const QByteArray& hashSum2) {
    if (hashSum1.size() != hashSum2.size()) {
        return -1;
    }

    int distance = 0;
    const char* data1 = hashSum1.constData();
    const char* data2 = hashSum2.constData();
    int length = hashSum1.size();

    for (int i = 0; i < length; ++i) {
        char xorResult = data1[i] ^ data2[i];
        while (xorResult) {
            distance += xorResult & 1;
            xorResult >>= 1;
        }
    }

    return distance;
}

float ImageComparator::compare( const QPixmap& lhs, const QPixmap& rhs )
{
    const auto& lhsGray = convertToGrayScale(
        lhs.scaled(8,8,Qt::IgnoreAspectRatio)
    );

    const auto& rhsGray = convertToGrayScale(
        rhs.scaled(8,8,Qt::IgnoreAspectRatio)
    );

    auto lhsAvg = calculateAverageIntensity( lhsGray );
    auto rhsAvg = calculateAverageIntensity( rhsGray );

    const auto& lhsBin = applyThreshold( lhsGray, lhsAvg );
    const auto& rhsBin = applyThreshold( rhsGray, rhsAvg );

    const auto& lhsHash = calculateHashSum( lhsBin );
    const auto& rhsHash = calculateHashSum( rhsBin );

    hashSum = QString::fromUtf8( rhsHash );

    return calculateHammingDistance( lhsHash, rhsHash );
}

QString const & ImageComparator::getHash()
{
    return hashSum;
}
