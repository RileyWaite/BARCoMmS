/****************************************************************************
** Meta object code from reading C++ file 'bc_ditl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modules/BARCoMmS_DITL/bc_ditl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bc_ditl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BC_DITL_t {
    QByteArrayData data[10];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BC_DITL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BC_DITL_t qt_meta_stringdata_BC_DITL = {
    {
QT_MOC_LITERAL(0, 0, 7), // "BC_DITL"
QT_MOC_LITERAL(1, 8, 5), // "dying"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 15), // "treeItemClicked"
QT_MOC_LITERAL(4, 31, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 48, 29), // "on_actionShowLegend_triggered"
QT_MOC_LITERAL(6, 78, 23), // "on_actionZoom_triggered"
QT_MOC_LITERAL(7, 102, 11), // "pduReceived"
QT_MOC_LITERAL(8, 114, 10), // "ByteBuffer"
QT_MOC_LITERAL(9, 125, 7) // "ditlLog"

    },
    "BC_DITL\0dying\0\0treeItemClicked\0"
    "QTreeWidgetItem*\0on_actionShowLegend_triggered\0"
    "on_actionZoom_triggered\0pduReceived\0"
    "ByteBuffer\0ditlLog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BC_DITL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   45,    2, 0x08 /* Private */,
       5,    0,   50,    2, 0x08 /* Private */,
       6,    0,   51,    2, 0x08 /* Private */,
       7,    1,   52,    2, 0x08 /* Private */,
       9,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void BC_DITL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BC_DITL *_t = static_cast<BC_DITL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dying(); break;
        case 1: _t->treeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->on_actionShowLegend_triggered(); break;
        case 3: _t->on_actionZoom_triggered(); break;
        case 4: _t->pduReceived((*reinterpret_cast< ByteBuffer(*)>(_a[1]))); break;
        case 5: _t->ditlLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BC_DITL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BC_DITL::dying)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject BC_DITL::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BC_DITL.data,
      qt_meta_data_BC_DITL,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BC_DITL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BC_DITL::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BC_DITL.stringdata0))
        return static_cast<void*>(const_cast< BC_DITL*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BC_DITL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void BC_DITL::dying()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
