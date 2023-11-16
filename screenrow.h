#ifndef SCREENROW_H
#define SCREENROW_H

struct ScreenRow
{
    ScreenRow() {}

    ScreenRow(
            const QString& _path
        ,   const QString& _hashSum
        ,   const float _percent
    )
        : path(_path)
        , hashSum(_hashSum)
        , percent(_percent)
    {}

    QString path;
    QString hashSum;

    float percent;
};

#endif // SCREENROW_H
