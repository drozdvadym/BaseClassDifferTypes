#pragma once

#include <string>

typedef enum {
    id_unknown_type,
    id_int,
    id_float,
    id_double,
    id_uchar,
    id_string,
    id_baseClass
} type_id_t;

struct ValueHolder
{
    void      *value;
    type_id_t type_id;

    ValueHolder(void * aVal = nullptr, type_id_t aTypeId = id_unknown_type) :
        value(aVal), type_id(aTypeId)
    {
    }

    ~ValueHolder()
    {
    }
};

//
// Some useful macro for using Value Holder
//

#define VH_SWITCH_BEGIN(valHolder) \
    ValueHolder & _vh = valHolder; \
    switch (_vh.type_id) {

#define VH_SWITCH_END }

#define VH_CASE(type, type_id, FCN,...) \
    case type_id: FCN((type *)_vh.value, __VA_ARGS__); break;


#define VH_CASE_DFLT() default: std::cerr << "Unknown Type";


// Prototype - prototype of generated function.
// FcnToCall - name of function for call (bind) (FcnToCall must be defined for all types supported by ValueHolder)
// ValHolder - name of ValueHolder parameters in Prototype
// ...       - names of all other parameters separated by comma
// Example:
//     void SomeFcn(DiffType *val, int a, char b) { ..... }
//     VH_FCN_BIND_VOID(void DoIt(ValueHolder & vh, int a, char b ...), SomeFcn, a, b)
//

#define VH_FCN_BIND_VOID(Prototype, FcnToCall, ValHolder, ...)\
    Prototype{                                                \
    VH_SWITCH_BEGIN(ValHolder)                                \
    VH_CASE(int, id_int, FcnToCall, __VA_ARGS__);             \
    VH_CASE(float, id_float, FcnToCall, __VA_ARGS__);         \
    VH_CASE(double, id_double, FcnToCall, __VA_ARGS__);       \
    VH_CASE(unsigned char, id_uchar, FcnToCall, __VA_ARGS__); \
    VH_CASE(std::string, id_string, FcnToCall, __VA_ARGS__);  \
    VH_CASE_DFLT();                                           \
    VH_SWITCH_END;                                            \
}

//
//
//
