/****************************************************************************
** Meta object code from reading C++ file 'updatecycles.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modules/BARCoMmS_CFDP/updatecycles.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updatecycles.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UpdateCycles_t {
    QByteArrayData data[7];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpdateCycles_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpdateCycles_t qt_meta_stringdata_UpdateCycles = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UpdateCycles"
QT_MOC_LITERAL(1, 13, 25), // "updateCycles_appendOutput"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 10), // "updateRate"
QT_MOC_LITERAL(4, 51, 19), // "updateCycles_toggle"
QT_MOC_LITERAL(5, 71, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(6, 93, 21) // "on_buttonBox_rejected"

    },
    "UpdateCycles\0updateCycles_appendOutput\0"
    "\0updateRate\0updateCycles_toggle\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpdateCycles[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UpdateCycles::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UpdateCycles *_t = static_cast<UpdateCycles *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateCycles_appendOutput((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->updateCycles_toggle(); break;
        case 2: _t->on_buttonBox_accepted(); break;
        case 3: _t->on_buttonBox_rejected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UpdateCycles::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateCycles::updateCycles_appendOutput)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UpdateCycles::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateCycles::updateCycles_toggle)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject UpdateCycles::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_UpdateCycles.data,
      qt_meta_data_UpdateCycles,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UpdateCycles::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpdateCycles::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateCycles.stringdata0))
        return static_cast<void*>(const_cast< UpdateCycles*>(this));
    return QDialog::qt_metacast(_clname);
}

int UpdateCycles::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void UpdateCycles::updateCycles_appendOutput(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UpdateCycles::updateCycles_toggle()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
