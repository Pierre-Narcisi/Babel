#ifndef SOUNDWRAPPER_H
#define SOUNDWRAPPER_H

#include <QObject>

class SoundWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SoundWrapper(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SOUNDWRAPPER_H