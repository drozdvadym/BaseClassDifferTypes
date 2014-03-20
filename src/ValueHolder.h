//
// -*- Mode: c++; tab-width: 4; -*-
// -*- ex: ts=4 -*-
//

//
// ValueHolder.h (Vadym Drozd)
// BaseClassDifferTypes/ValueHolder.h
//

//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
// EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//

#ifndef __BC_VALUE_HOLDER_H__
# define __BC_VALUE_HOLDER_H__

# pragma once

////////////////////////////////////////////////////////////////////////////////
// include section
//

# include <string>
# include <iostream>
# include <exception>
# include <stdexcept>

typedef enum {
    id_unknown_type,
    id_int,
    id_float,
    id_double,
    id_uchar,
    id_string,
    id_baseClass
} type_id_t;

////////////////////////////////////////////////////////////////////////////////
// declaration section
//

struct ValueHolder
{
    void      *value;
    type_id_t type_id;
    const char *valname;

    ValueHolder(
        void * aVal = NULL,
        type_id_t aTypeId = id_unknown_type,
        const char * aValName = ""
        ) :
        value(aVal), type_id(aTypeId), valname(aValName)
    {
    }
};

template <typename T>
void LoadDifferTypes(T * val, std::istream& is)
{
    is >> *val;
}

template <typename T>
void SaveDifferTypes(T * val, std::ostream& os)
{
    os << *val;
}


////////////////////////////////////////////////////////////////////////////////
// Some useful macro for using Value Holder
//

# define VH_SWITCH_BEGIN(valHolder) \
    ValueHolder & _vh = valHolder;  \
    switch (_vh.type_id) {

# define VH_SWITCH_END }

// type    - type of 'value' that stored in ValueHolder (int, float ...)
// type_id - id of that type (id_int, id_float ...)
// FCN     - name of function that will be use 'value'
// ...     - all other params that need for FCN
//
# define VH_CASE(type, type_id, FCN,...) \
    case type_id: FCN((type *)_vh.value, __VA_ARGS__); break

# define VH_CASE_DFLT() \
    default: throw std::runtime_error("Unknown type: ValueHolder Switch")

// FcnToCall - name of function for call.
//             (FcnToCall must be defined for all types supported by ValueHolder)
// ValHolder - name of ValueHolder variable
// ...       - names of all other parameters of FcnToCall separated by comma
// Example:
//     void SomeFcn(DiffType *val, int a, char b) { ..... }
//     void VH_SomeFcn(ValueHolder& vh, int a, char b) {
//         VH_SWITCH_FCN_CALL_BLOCK(SomeFcn, vh, a, b);
//     }
//
# define VH_SWITCH_FCN_CALL_BLOCK(FcnToCall, ValHolder, ...)      \
{                                                                 \
    VH_SWITCH_BEGIN(ValHolder)                                    \
        VH_CASE(int, id_int, FcnToCall, __VA_ARGS__);             \
        VH_CASE(float, id_float, FcnToCall, __VA_ARGS__);         \
        VH_CASE(double, id_double, FcnToCall, __VA_ARGS__);       \
        VH_CASE(unsigned char, id_uchar, FcnToCall, __VA_ARGS__); \
        VH_CASE(std::string, id_string, FcnToCall, __VA_ARGS__);  \
        VH_CASE_DFLT();                                           \
    VH_SWITCH_END                                                 \
}

#endif

//
//
//
