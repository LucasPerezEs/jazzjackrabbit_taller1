/****************************************************************************
** Meta object code from reading C++ file 'MultiplayerMenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../client_src/setupscreen/MultiplayerMenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultiplayerMenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MultiplayerMenu_t {
    QByteArrayData data[14];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MultiplayerMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MultiplayerMenu_t qt_meta_stringdata_MultiplayerMenu = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MultiplayerMenu"
QT_MOC_LITERAL(1, 16, 16), // "refreshRequested"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 19), // "createGameRequested"
QT_MOC_LITERAL(4, 54, 8), // "gameName"
QT_MOC_LITERAL(5, 63, 8), // "uint32_t"
QT_MOC_LITERAL(6, 72, 10), // "maxPlayers"
QT_MOC_LITERAL(7, 83, 17), // "joinGameRequested"
QT_MOC_LITERAL(8, 101, 6), // "gameID"
QT_MOC_LITERAL(9, 108, 7), // "elegido"
QT_MOC_LITERAL(10, 116, 18), // "createMapRequested"
QT_MOC_LITERAL(11, 135, 0), // ""
QT_MOC_LITERAL(12, 136, 19), // "ClientNameRequested"
QT_MOC_LITERAL(13, 156, 10), // "clientName"


    },
    "MultiplayerMenu\0refreshRequested\0\0"
    "createGameRequested\0gameName\0uint32_t\0"
    "maxPlayers\0joinGameRequested\0gameID\0"
    "elegido\0createMapRequested\0\0ClientNameRequested\0clientName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MultiplayerMenu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    2,   35,    2, 0x06 /* Public */,
       7,    2,   40,    2, 0x06 /* Public */,
      10,    0,   45,    2, 0x06 /* Public */,
      12,    0,   45,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 5,    4,    6,

       0        // eod
};

void MultiplayerMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MultiplayerMenu *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->refreshRequested(); break;
        case 1: _t->createGameRequested((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const uint32_t(*)>(_a[2]))); break;
        case 2: _t->joinGameRequested((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->createMapRequested(); break;
        case 4: _t->ClientNameRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MultiplayerMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiplayerMenu::refreshRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MultiplayerMenu::*)(const QString & , const uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiplayerMenu::createGameRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MultiplayerMenu::*)(const QString & , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiplayerMenu::joinGameRequested)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MultiplayerMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiplayerMenu::createMapRequested)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MultiplayerMenu::*)(const QString &);
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MultiplayerMenu::ClientNameRequested)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MultiplayerMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_MultiplayerMenu.data,
    qt_meta_data_MultiplayerMenu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MultiplayerMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultiplayerMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MultiplayerMenu.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MultiplayerMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MultiplayerMenu::refreshRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MultiplayerMenu::createGameRequested(const QString & _t1, const uint32_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MultiplayerMenu::joinGameRequested(const QString & _t1, const int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MultiplayerMenu::createMapRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MultiplayerMenu::ClientNameRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1)))};
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
