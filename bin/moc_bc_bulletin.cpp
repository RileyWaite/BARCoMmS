/****************************************************************************
** Meta object code from reading C++ file 'bc_bulletin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modules/BARCoMmS_Bulletin/bc_bulletin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bc_bulletin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BC_Bulletin_t {
    QByteArrayData data[22];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BC_Bulletin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BC_Bulletin_t qt_meta_stringdata_BC_Bulletin = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BC_Bulletin"
QT_MOC_LITERAL(1, 12, 4), // "rssi"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 9), // "itemAdded"
QT_MOC_LITERAL(4, 28, 5), // "dying"
QT_MOC_LITERAL(5, 34, 8), // "takeCFDP"
QT_MOC_LITERAL(6, 43, 5), // "char*"
QT_MOC_LITERAL(7, 49, 3), // "str"
QT_MOC_LITERAL(8, 53, 7), // "takeFSW"
QT_MOC_LITERAL(9, 61, 4), // "apid"
QT_MOC_LITERAL(10, 66, 2), // "id"
QT_MOC_LITERAL(11, 69, 11), // "pduReceived"
QT_MOC_LITERAL(12, 81, 10), // "ByteBuffer"
QT_MOC_LITERAL(13, 92, 4), // "goTo"
QT_MOC_LITERAL(14, 97, 14), // "eraseSearchBar"
QT_MOC_LITERAL(15, 112, 18), // "expandCollapseItem"
QT_MOC_LITERAL(16, 131, 17), // "expandCollapseAll"
QT_MOC_LITERAL(17, 149, 10), // "autoScroll"
QT_MOC_LITERAL(18, 160, 10), // "autoExpand"
QT_MOC_LITERAL(19, 171, 11), // "openSorting"
QT_MOC_LITERAL(20, 183, 9), // "sortItems"
QT_MOC_LITERAL(21, 193, 10) // "sortOption"

    },
    "BC_Bulletin\0rssi\0\0itemAdded\0dying\0"
    "takeCFDP\0char*\0str\0takeFSW\0apid\0id\0"
    "pduReceived\0ByteBuffer\0goTo\0eraseSearchBar\0"
    "expandCollapseItem\0expandCollapseAll\0"
    "autoScroll\0autoExpand\0openSorting\0"
    "sortItems\0sortOption"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BC_Bulletin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    0,   87,    2, 0x06 /* Public */,
       4,    0,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   89,    2, 0x0a /* Public */,
       8,    2,   92,    2, 0x0a /* Public */,
      11,    1,   97,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    0,  105,    2, 0x0a /* Public */,
      19,    0,  106,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void BC_Bulletin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BC_Bulletin *_t = static_cast<BC_Bulletin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rssi((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->itemAdded(); break;
        case 2: _t->dying(); break;
        case 3: _t->takeCFDP((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 4: _t->takeFSW((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->pduReceived((*reinterpret_cast< ByteBuffer(*)>(_a[1]))); break;
        case 6: _t->goTo(); break;
        case 7: _t->eraseSearchBar(); break;
        case 8: _t->expandCollapseItem(); break;
        case 9: _t->expandCollapseAll(); break;
        case 10: _t->autoScroll(); break;
        case 11: _t->autoExpand(); break;
        case 12: _t->openSorting(); break;
        case 13: _t->sortItems((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BC_Bulletin::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BC_Bulletin::rssi)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BC_Bulletin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BC_Bulletin::itemAdded)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (BC_Bulletin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BC_Bulletin::dying)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject BC_Bulletin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BC_Bulletin.data,
      qt_meta_data_BC_Bulletin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BC_Bulletin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BC_Bulletin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BC_Bulletin.stringdata0))
        return static_cast<void*>(const_cast< BC_Bulletin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BC_Bulletin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void BC_Bulletin::rssi(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BC_Bulletin::itemAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void BC_Bulletin::dying()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
