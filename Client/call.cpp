#include "call.h"

call::call()
{
    QThread* thread = new QThread;
    MyObject* myObject = new MyObject();
    myObject->moveToThread(thread);
    connect(myObject, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), myObject, SLOT(process()));
    connect(myObject, SIGNAL(finished()), thread, SLOT(quit()));
    connect(myObject, SIGNAL(finished()), myObject, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MyObject::process()
{
    _udpWrapper = new UdpWrapper();
    SoundWrapper &soundWrapper = Singletons::getSoundWrapper();
    while (true) {
        soundWrapper.getPa().record();
        CompData data = soundWrapper.getPa().getData();
        std::string str(data.data.begin(), data.data.end());
        str += ' ' + data.length;
        _udpWrapper->sendData(QString::fromStdString(str));
    }
}

MyObject::MyObject()
{
}

MyObject::~MyObject()
{
}
