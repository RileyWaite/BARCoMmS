/****************************************************************************
** Meta object code from reading C++ file 'requests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modules/BARCoMmS_CFDP/requests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'requests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Requests_t {
    QByteArrayData data[8];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Requests_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Requests_t qt_meta_stringdata_Requests = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Requests"
QT_MOC_LITERAL(1, 9, 21), // "requests_appendOutput"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(4, 57, 8), // "requests"
QT_MOC_LITERAL(5, 66, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(6, 88, 21), // "on_buttonBox_rejected"
QT_MOC_LITERAL(7, 110, 7) // "clicked"

    },
    "Requests\0requests_appendOutput\0\0"
    "std::vector<std::string>\0requests\0"
    "on_buttonBox_accepted\0on_buttonBox_rejected\0"
    "clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Requests[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x08 /* Private */,
       6,    0,   38,    2, 0x08 /* Private */,
       7,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Requests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Requests *_t = static_cast<Requests *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requests_appendOutput((*reinterpret_cast< std::vector<std::string>(*)>(_a[1]))); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_buttonBox_rejected(); break;
        case 3: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Requests::*_t)(std::vector<std::string> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Requests::requests_appendOutput)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Requests::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Requests.data,
      qt_meta_data_Requests,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Requests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Requests::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Requests.stringdata0))
        return static_cast<void*>(const_cast< Requests*>(this));
    return QDialog::qt_metacast(_clname);
}

int Requests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Requests::requests_appendOutput(std::vector<std::string> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
