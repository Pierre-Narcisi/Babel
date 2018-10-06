#ifndef SOUNDWRAPPER_H
#define SOUNDWRAPPER_H

#include <QObject>
#include "PaWrapper/PaWrapper.hpp"

class SoundWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SoundWrapper(QObject *parent = nullptr);
    PaWrapper &getPa();
private:
    PaWrapper _paWrapper;
signals:

public slots:
};

#endif // SOUNDWRAPPER_H
