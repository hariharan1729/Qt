/****************************************************************************
** Meta object code from reading C++ file 'WeatherChartItem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../WeatherApp/src/WeatherChartItem.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WeatherChartItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_WeatherChartItem_t {
    uint offsetsAndSizes[26];
    char stringdata0[17];
    char stringdata1[12];
    char stringdata2[5];
    char stringdata3[13];
    char stringdata4[1];
    char stringdata5[12];
    char stringdata6[5];
    char stringdata7[8];
    char stringdata8[9];
    char stringdata9[12];
    char stringdata10[15];
    char stringdata11[6];
    char stringdata12[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_WeatherChartItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_WeatherChartItem_t qt_meta_stringdata_WeatherChartItem = {
    {
        QT_MOC_LITERAL(0, 16),  // "WeatherChartItem"
        QT_MOC_LITERAL(17, 11),  // "QML.Element"
        QT_MOC_LITERAL(29, 4),  // "auto"
        QT_MOC_LITERAL(34, 12),  // "update_chart"
        QT_MOC_LITERAL(47, 0),  // ""
        QT_MOC_LITERAL(48, 11),  // "QQuickItem*"
        QT_MOC_LITERAL(60, 4),  // "item"
        QT_MOC_LITERAL(65, 7),  // "sendReq"
        QT_MOC_LITERAL(73, 8),  // "cityName"
        QT_MOC_LITERAL(82, 11),  // "update_axes"
        QT_MOC_LITERAL(94, 14),  // "QAbstractAxis*"
        QT_MOC_LITERAL(109, 5),  // "axisX"
        QT_MOC_LITERAL(115, 5)   // "axisY"
    },
    "WeatherChartItem",
    "QML.Element",
    "auto",
    "update_chart",
    "",
    "QQuickItem*",
    "item",
    "sendReq",
    "cityName",
    "update_axes",
    "QAbstractAxis*",
    "axisX",
    "axisY"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_WeatherChartItem[] = {

 // content:
      10,       // revision
       0,       // classname
       1,   14, // classinfo
       3,   16, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   34,    4, 0x02,    1 /* Public */,
       7,    1,   37,    4, 0x02,    3 /* Public */,
       9,    2,   40,    4, 0x02,    5 /* Public */,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,   11,   12,

       0        // eod
};

Q_CONSTINIT const QMetaObject WeatherChartItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickItem::staticMetaObject>(),
    qt_meta_stringdata_WeatherChartItem.offsetsAndSizes,
    qt_meta_data_WeatherChartItem,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // Q_OBJECT / Q_GADGET
        WeatherChartItem,
        // method 'update_chart'
        void,
        QQuickItem *,
        // method 'sendReq'
        void,
        const QString &,
        // method 'update_axes'
        void,
        QAbstractAxis *,
        QAbstractAxis *
    >,
    nullptr
} };

void WeatherChartItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WeatherChartItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->update_chart((*reinterpret_cast< std::add_pointer_t<QQuickItem*>>(_a[1]))); break;
        case 1: _t->sendReq((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->update_axes((*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QAbstractAxis*>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QQuickItem* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractAxis* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *WeatherChartItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeatherChartItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WeatherChartItem.stringdata0))
        return static_cast<void*>(this);
    return QQuickItem::qt_metacast(_clname);
}

int WeatherChartItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
