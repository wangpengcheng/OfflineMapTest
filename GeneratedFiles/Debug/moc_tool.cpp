/****************************************************************************
** Meta object code from reading C++ file 'tool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/tool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tool_t {
    QByteArrayData data[16];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tool_t qt_meta_stringdata_Tool = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Tool"
QT_MOC_LITERAL(1, 5, 20), // "TransfromLatToDouble"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 1), // "x"
QT_MOC_LITERAL(4, 29, 1), // "y"
QT_MOC_LITERAL(5, 31, 20), // "TransfromLonToDouble"
QT_MOC_LITERAL(6, 52, 12), // "WPS84ToGCJ02"
QT_MOC_LITERAL(7, 65, 14), // "QGeoCoordinate"
QT_MOC_LITERAL(8, 80, 3), // "lat"
QT_MOC_LITERAL(9, 84, 3), // "lon"
QT_MOC_LITERAL(10, 88, 11), // "GetDistance"
QT_MOC_LITERAL(11, 100, 6), // "point1"
QT_MOC_LITERAL(12, 107, 6), // "point2"
QT_MOC_LITERAL(13, 114, 12), // "TestNoteTool"
QT_MOC_LITERAL(14, 127, 8), // "TestName"
QT_MOC_LITERAL(15, 136, 1) // "i"

    },
    "Tool\0TransfromLatToDouble\0\0x\0y\0"
    "TransfromLonToDouble\0WPS84ToGCJ02\0"
    "QGeoCoordinate\0lat\0lon\0GetDistance\0"
    "point1\0point2\0TestNoteTool\0TestName\0"
    "i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x02 /* Public */,
       5,    2,   44,    2, 0x02 /* Public */,
       6,    2,   49,    2, 0x02 /* Public */,
      10,    2,   54,    2, 0x02 /* Public */,
      13,    2,   59,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,
    0x80000000 | 7, QMetaType::Double, QMetaType::Double,    8,    9,
    QMetaType::Double, 0x80000000 | 7, 0x80000000 | 7,   11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   14,   15,

       0        // eod
};

void Tool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tool *_t = static_cast<Tool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { double _r = _t->TransfromLatToDouble((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 1: { double _r = _t->TransfromLonToDouble((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 2: { QGeoCoordinate _r = _t->WPS84ToGCJ02((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QGeoCoordinate*>(_a[0]) = std::move(_r); }  break;
        case 3: { double _r = _t->GetDistance((*reinterpret_cast< QGeoCoordinate(*)>(_a[1])),(*reinterpret_cast< QGeoCoordinate(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->TestNoteTool((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
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

QT_INIT_METAOBJECT const QMetaObject Tool::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tool.data,
      qt_meta_data_Tool,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Tool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tool::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tool.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Tool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
