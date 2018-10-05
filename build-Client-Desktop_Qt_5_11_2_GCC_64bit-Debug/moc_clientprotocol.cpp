/****************************************************************************
** Meta object code from reading C++ file 'clientprotocol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QtInterface/clientprotocol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientprotocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_client__protocol__ClientSender_t {
    QByteArrayData data[10];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_client__protocol__ClientSender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_client__protocol__ClientSender_t qt_meta_stringdata_client__protocol__ClientSender = {
    {
QT_MOC_LITERAL(0, 0, 30), // "client::protocol::ClientSender"
QT_MOC_LITERAL(1, 31, 12), // "disconnected"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 16), // "onPacketReceived"
QT_MOC_LITERAL(4, 62, 24), // "babel::protocol::Packet&"
QT_MOC_LITERAL(5, 87, 18), // "onFriendListChange"
QT_MOC_LITERAL(6, 106, 19), // "std::vector<Friend>"
QT_MOC_LITERAL(7, 126, 7), // "friends"
QT_MOC_LITERAL(8, 134, 13), // "onCallRequest"
QT_MOC_LITERAL(9, 148, 8) // "username"

    },
    "client::protocol::ClientSender\0"
    "disconnected\0\0onPacketReceived\0"
    "babel::protocol::Packet&\0onFriendListChange\0"
    "std::vector<Friend>\0friends\0onCallRequest\0"
    "username"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_client__protocol__ClientSender[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    1,   38,    2, 0x06 /* Public */,
       8,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void client::protocol::ClientSender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientSender *_t = static_cast<ClientSender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->disconnected(); break;
        case 1: _t->onPacketReceived((*reinterpret_cast< babel::protocol::Packet(*)>(_a[1]))); break;
        case 2: _t->onFriendListChange((*reinterpret_cast< std::vector<Friend>(*)>(_a[1]))); break;
        case 3: _t->onCallRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientSender::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSender::disconnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientSender::*)(babel::protocol::Packet & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSender::onPacketReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientSender::*)(std::vector<Friend> const & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSender::onFriendListChange)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientSender::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSender::onCallRequest)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject client::protocol::ClientSender::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_client__protocol__ClientSender.data,
      qt_meta_data_client__protocol__ClientSender,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *client::protocol::ClientSender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *client::protocol::ClientSender::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_client__protocol__ClientSender.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "babel::protocol::Sender"))
        return static_cast< babel::protocol::Sender*>(this);
    return QObject::qt_metacast(_clname);
}

int client::protocol::ClientSender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void client::protocol::ClientSender::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void client::protocol::ClientSender::onPacketReceived(babel::protocol::Packet & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void client::protocol::ClientSender::onFriendListChange(std::vector<Friend> const & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void client::protocol::ClientSender::onCallRequest(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
