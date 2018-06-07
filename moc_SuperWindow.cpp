/****************************************************************************
** Meta object code from reading C++ file 'SuperWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "BackEnd/SuperWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SuperWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SuperWindow_t {
    QByteArrayData data[10];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SuperWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SuperWindow_t qt_meta_stringdata_SuperWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SuperWindow"
QT_MOC_LITERAL(1, 12, 12), // "getDropPiece"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "Restart"
QT_MOC_LITERAL(4, 34, 4), // "Undo"
QT_MOC_LITERAL(5, 39, 4), // "Redo"
QT_MOC_LITERAL(6, 44, 2), // "AI"
QT_MOC_LITERAL(7, 47, 10), // "updateTime"
QT_MOC_LITERAL(8, 58, 5), // "delay"
QT_MOC_LITERAL(9, 64, 10) // "saveResult"

    },
    "SuperWindow\0getDropPiece\0\0Restart\0"
    "Undo\0Redo\0AI\0updateTime\0delay\0saveResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SuperWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x08 /* Private */,
       3,    0,   59,    2, 0x08 /* Private */,
       4,    0,   60,    2, 0x08 /* Private */,
       5,    0,   61,    2, 0x08 /* Private */,
       6,    0,   62,    2, 0x08 /* Private */,
       7,    0,   63,    2, 0x08 /* Private */,
       8,    1,   64,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void SuperWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SuperWindow *_t = static_cast<SuperWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getDropPiece((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->Restart(); break;
        case 2: _t->Undo(); break;
        case 3: _t->Redo(); break;
        case 4: _t->AI(); break;
        case 5: _t->updateTime(); break;
        case 6: _t->delay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->saveResult(); break;
        default: ;
        }
    }
}

const QMetaObject SuperWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SuperWindow.data,
      qt_meta_data_SuperWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SuperWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SuperWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SuperWindow.stringdata0))
        return static_cast<void*>(const_cast< SuperWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SuperWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
