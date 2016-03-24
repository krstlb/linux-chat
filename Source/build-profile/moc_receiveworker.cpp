/****************************************************************************
** Meta object code from reading C++ file 'receiveworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client/receiveworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'receiveworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ReceiveWorker_t {
    QByteArrayData data[12];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReceiveWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReceiveWorker_t qt_meta_stringdata_ReceiveWorker = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ReceiveWorker"
QT_MOC_LITERAL(1, 14, 11), // "receiveData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "finished"
QT_MOC_LITERAL(4, 36, 22), // "updateChatWindowSignal"
QT_MOC_LITERAL(5, 59, 7), // "msgText"
QT_MOC_LITERAL(6, 67, 12), // "usernameText"
QT_MOC_LITERAL(7, 80, 20), // "updateUserListSignal"
QT_MOC_LITERAL(8, 101, 8), // "username"
QT_MOC_LITERAL(9, 110, 19), // "clearUserListSignal"
QT_MOC_LITERAL(10, 130, 6), // "doWork"
QT_MOC_LITERAL(11, 137, 8) // "stopWork"

    },
    "ReceiveWorker\0receiveData\0\0finished\0"
    "updateChatWindowSignal\0msgText\0"
    "usernameText\0updateUserListSignal\0"
    "username\0clearUserListSignal\0doWork\0"
    "stopWork"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReceiveWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    2,   51,    2, 0x06 /* Public */,
       7,    1,   56,    2, 0x06 /* Public */,
       9,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   60,    2, 0x0a /* Public */,
      11,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ReceiveWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ReceiveWorker *_t = static_cast<ReceiveWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveData(); break;
        case 1: _t->finished(); break;
        case 2: _t->updateChatWindowSignal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->updateUserListSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->clearUserListSignal(); break;
        case 5: _t->doWork(); break;
        case 6: _t->stopWork(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ReceiveWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::receiveData)) {
                *result = 0;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::finished)) {
                *result = 1;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::updateChatWindowSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::updateUserListSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (ReceiveWorker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ReceiveWorker::clearUserListSignal)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject ReceiveWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReceiveWorker.data,
      qt_meta_data_ReceiveWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ReceiveWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReceiveWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ReceiveWorker.stringdata0))
        return static_cast<void*>(const_cast< ReceiveWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int ReceiveWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ReceiveWorker::receiveData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ReceiveWorker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ReceiveWorker::updateChatWindowSignal(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ReceiveWorker::updateUserListSignal(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ReceiveWorker::clearUserListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
