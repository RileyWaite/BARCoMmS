/****************************************************************************
** Meta object code from reading C++ file 'fswitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modules/BARCoMmS_Bulletin/fswitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fswitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FSWItem_t {
    QByteArrayData data[5];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FSWItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FSWItem_t qt_meta_stringdata_FSWItem = {
    {
QT_MOC_LITERAL(0, 0, 7), // "FSWItem"
QT_MOC_LITERAL(1, 8, 10), // "flagYellow"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "flagOrange"
QT_MOC_LITERAL(4, 31, 7) // "flagRed"

    },
    "FSWItem\0flagYellow\0\0flagOrange\0flagRed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FSWItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FSWItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FSWItem *_t = static_cast<FSWItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->flagYellow(); break;
        case 1: _t->flagOrange(); break;
        case 2: _t->flagRed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FSWItem::staticMetaObject = {
    { &QTimer::staticMetaObject, qt_meta_stringdata_FSWItem.data,
      qt_meta_data_FSWItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FSWItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FSWItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FSWItem.stringdata0))
        return static_cast<void*>(const_cast< FSWItem*>(this));
    return QTimer::qt_metacast(_clname);
}

int FSWItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTimer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
