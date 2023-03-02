/****************************************************************************
** Meta object code from reading C++ file 'Create3Hmi.hh'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/create3_sim/irobot_create_ignition/irobot_create_ignition_plugins/Create3Hmi/Create3Hmi.hh"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Create3Hmi.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ignition__gui__Create3Hmi_t {
    QByteArrayData data[4];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ignition__gui__Create3Hmi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ignition__gui__Create3Hmi_t qt_meta_stringdata_ignition__gui__Create3Hmi = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ignition::gui::Create3Hmi"
QT_MOC_LITERAL(1, 26, 15), // "OnCreate3Button"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 6) // "button"

    },
    "ignition::gui::Create3Hmi\0OnCreate3Button\0"
    "\0button"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ignition__gui__Create3Hmi[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ignition::gui::Create3Hmi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Create3Hmi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnCreate3Button((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ignition::gui::Create3Hmi::staticMetaObject = { {
    &Plugin::staticMetaObject,
    qt_meta_stringdata_ignition__gui__Create3Hmi.data,
    qt_meta_data_ignition__gui__Create3Hmi,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ignition::gui::Create3Hmi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ignition::gui::Create3Hmi::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ignition__gui__Create3Hmi.stringdata0))
        return static_cast<void*>(this);
    return Plugin::qt_metacast(_clname);
}

int ignition::gui::Create3Hmi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Plugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
