/****************************************************************************
** Meta object code from reading C++ file 'bus.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/bus.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bus.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Bus_t {
    QByteArrayData data[13];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bus_t qt_meta_stringdata_Bus = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Bus"
QT_MOC_LITERAL(1, 4, 22), // "UpdataCoordinatesByNet"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "GetReplyFinished"
QT_MOC_LITERAL(4, 45, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 60, 5), // "reply"
QT_MOC_LITERAL(6, 66, 4), // "Move"
QT_MOC_LITERAL(7, 71, 2), // "dx"
QT_MOC_LITERAL(8, 74, 2), // "dy"
QT_MOC_LITERAL(9, 77, 13), // "MoveNextPoint"
QT_MOC_LITERAL(10, 91, 14), // "QGeoCoordinate"
QT_MOC_LITERAL(11, 106, 11), // "coordinate1"
QT_MOC_LITERAL(12, 118, 11) // "coordinate2"

    },
    "Bus\0UpdataCoordinatesByNet\0\0"
    "GetReplyFinished\0QNetworkReply*\0reply\0"
    "Move\0dx\0dy\0MoveNextPoint\0QGeoCoordinate\0"
    "coordinate1\0coordinate2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bus[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       6,    2,   38,    2, 0x0a /* Public */,
       9,    2,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    7,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,   11,   12,

       0        // eod
};

void Bus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Bus *_t = static_cast<Bus *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdataCoordinatesByNet(); break;
        case 1: _t->GetReplyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->Move((*reinterpret_cast< const double(*)>(_a[1])),(*reinterpret_cast< const double(*)>(_a[2]))); break;
        case 3: _t->MoveNextPoint((*reinterpret_cast< const QGeoCoordinate(*)>(_a[1])),(*reinterpret_cast< const QGeoCoordinate(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGeoCoordinate >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Bus::staticMetaObject = {
    { &QDeclarativeGeoMapQuickItem::staticMetaObject, qt_meta_stringdata_Bus.data,
      qt_meta_data_Bus,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Bus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Bus.stringdata0))
        return static_cast<void*>(this);
    return QDeclarativeGeoMapQuickItem::qt_metacast(_clname);
}

int Bus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeGeoMapQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
