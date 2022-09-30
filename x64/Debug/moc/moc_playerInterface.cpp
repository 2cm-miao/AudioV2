/****************************************************************************
** Meta object code from reading C++ file 'playerInterface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../playerInterface.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playerInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AudioV2_t {
    uint offsetsAndSizes[30];
    char stringdata0[8];
    char stringdata1[5];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[15];
    char stringdata5[13];
    char stringdata6[18];
    char stringdata7[28];
    char stringdata8[6];
    char stringdata9[16];
    char stringdata10[9];
    char stringdata11[16];
    char stringdata12[9];
    char stringdata13[12];
    char stringdata14[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AudioV2_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_AudioV2_t qt_meta_stringdata_AudioV2 = {
    {
        QT_MOC_LITERAL(0, 7),  // "AudioV2"
        QT_MOC_LITERAL(8, 4),  // "open"
        QT_MOC_LITERAL(13, 0),  // ""
        QT_MOC_LITERAL(14, 8),  // "fileName"
        QT_MOC_LITERAL(23, 14),  // "openFileAction"
        QT_MOC_LITERAL(38, 12),  // "playFunction"
        QT_MOC_LITERAL(51, 17),  // "mediaStateChanged"
        QT_MOC_LITERAL(69, 27),  // "QMediaPlayer::PlaybackState"
        QT_MOC_LITERAL(97, 5),  // "state"
        QT_MOC_LITERAL(103, 15),  // "positionChanged"
        QT_MOC_LITERAL(119, 8),  // "position"
        QT_MOC_LITERAL(128, 15),  // "durationChanged"
        QT_MOC_LITERAL(144, 8),  // "duration"
        QT_MOC_LITERAL(153, 11),  // "setPosition"
        QT_MOC_LITERAL(165, 20)   // "spectumProcessAction"
    },
    "AudioV2",
    "open",
    "",
    "fileName",
    "openFileAction",
    "playFunction",
    "mediaStateChanged",
    "QMediaPlayer::PlaybackState",
    "state",
    "positionChanged",
    "position",
    "durationChanged",
    "duration",
    "setPosition",
    "spectumProcessAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioV2[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x08,    1 /* Private */,
       4,    0,   65,    2, 0x08,    3 /* Private */,
       5,    0,   66,    2, 0x08,    4 /* Private */,
       6,    1,   67,    2, 0x08,    5 /* Private */,
       9,    1,   70,    2, 0x08,    7 /* Private */,
      11,    1,   73,    2, 0x08,    9 /* Private */,
      13,    1,   76,    2, 0x08,   11 /* Private */,
      14,    0,   79,    2, 0x08,   13 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::LongLong,   10,
    QMetaType::Void, QMetaType::LongLong,   12,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void AudioV2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioV2 *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->open((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->openFileAction(); break;
        case 2: _t->playFunction(); break;
        case 3: _t->mediaStateChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::PlaybackState>>(_a[1]))); break;
        case 4: _t->positionChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 5: _t->durationChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 6: _t->setPosition((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->spectumProcessAction(); break;
        default: ;
        }
    }
}

const QMetaObject AudioV2::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_AudioV2.offsetsAndSizes,
    qt_meta_data_AudioV2,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AudioV2_t
, QtPrivate::TypeAndForceComplete<AudioV2, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMediaPlayer::PlaybackState, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *AudioV2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioV2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioV2.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int AudioV2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
