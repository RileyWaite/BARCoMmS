/****************************************************************************
** Meta object code from reading C++ file 'classmessages.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/modules/BARCoMmS_CFDP/classmessages.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'classmessages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClassMessages_t {
    QByteArrayData data[18];
    char stringdata0[426];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClassMessages_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClassMessages_t qt_meta_stringdata_ClassMessages = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClassMessages"
QT_MOC_LITERAL(1, 14, 26), // "classMessages_appendOutput"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 14), // "MessageClasses"
QT_MOC_LITERAL(4, 57, 14), // "messageClasses"
QT_MOC_LITERAL(5, 72, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(6, 94, 23), // "on_checkBox_all_toggled"
QT_MOC_LITERAL(7, 118, 7), // "checked"
QT_MOC_LITERAL(8, 126, 7), // "checker"
QT_MOC_LITERAL(9, 134, 31), // "on_checkBox_indications_toggled"
QT_MOC_LITERAL(10, 166, 34), // "on_checkBox_debugMemoryUse_to..."
QT_MOC_LITERAL(11, 201, 28), // "on_checkBox_debugNAK_toggled"
QT_MOC_LITERAL(12, 230, 28), // "on_checkBox_debugPDU_toggled"
QT_MOC_LITERAL(13, 259, 31), // "on_checkBox_PDUFiledata_toggled"
QT_MOC_LITERAL(14, 291, 34), // "on_checkBox_PDUNonFiledata_to..."
QT_MOC_LITERAL(15, 326, 38), // "on_checkBox_PDURetransmittedF..."
QT_MOC_LITERAL(16, 365, 28), // "on_checkBox_stateAll_toggled"
QT_MOC_LITERAL(17, 394, 31) // "on_checkBox_stateChange_toggled"

    },
    "ClassMessages\0classMessages_appendOutput\0"
    "\0MessageClasses\0messageClasses\0"
    "on_buttonBox_accepted\0on_checkBox_all_toggled\0"
    "checked\0checker\0on_checkBox_indications_toggled\0"
    "on_checkBox_debugMemoryUse_toggled\0"
    "on_checkBox_debugNAK_toggled\0"
    "on_checkBox_debugPDU_toggled\0"
    "on_checkBox_PDUFiledata_toggled\0"
    "on_checkBox_PDUNonFiledata_toggled\0"
    "on_checkBox_PDURetransmittedFD_toggled\0"
    "on_checkBox_stateAll_toggled\0"
    "on_checkBox_stateChange_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClassMessages[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   82,    2, 0x08 /* Private */,
       6,    1,   83,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,
      16,    0,   94,    2, 0x08 /* Private */,
      17,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ClassMessages::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClassMessages *_t = static_cast<ClassMessages *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->classMessages_appendOutput((*reinterpret_cast< MessageClasses(*)>(_a[1]))); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_checkBox_all_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->checker(); break;
        case 4: _t->on_checkBox_indications_toggled(); break;
        case 5: _t->on_checkBox_debugMemoryUse_toggled(); break;
        case 6: _t->on_checkBox_debugNAK_toggled(); break;
        case 7: _t->on_checkBox_debugPDU_toggled(); break;
        case 8: _t->on_checkBox_PDUFiledata_toggled(); break;
        case 9: _t->on_checkBox_PDUNonFiledata_toggled(); break;
        case 10: _t->on_checkBox_PDURetransmittedFD_toggled(); break;
        case 11: _t->on_checkBox_stateAll_toggled(); break;
        case 12: _t->on_checkBox_stateChange_toggled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClassMessages::*_t)(MessageClasses );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClassMessages::classMessages_appendOutput)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ClassMessages::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClassMessages.data,
      qt_meta_data_ClassMessages,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClassMessages::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClassMessages::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClassMessages.stringdata0))
        return static_cast<void*>(const_cast< ClassMessages*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClassMessages::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ClassMessages::classMessages_appendOutput(MessageClasses _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
