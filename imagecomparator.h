#ifndef IMAGECOMPARATOR_H
#define IMAGECOMPARATOR_H

#include <QPixmap>

class ImageComparator
{
public:
    ImageComparator();

    float compare( const QPixmap& lhs, const QPixmap& rhs );

    QString const & getHash();

private:
    QString hashSum = "SOME_HASH";
};

#endif // IMAGECOMPARATOR_H
