//
// -*- Mode: c++; tab-width: 4; -*-
// -*- ex: ts=4 -*-
//

//
// BaseClass.h (Vadym Drozd)
// BaseClassDifferTypes/BaseClass.h
//

//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
// EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//

#ifndef __BC_BASE_CLASS_H__
# define __BC_BASE_CLASS_H__

# pragma once

////////////////////////////////////////////////////////////////////////////////
// include section
//

# include "ValueHolder.h"
# include <vector>

# include <iostream>

////////////////////////////////////////////////////////////////////////////////
// declaration section
//

typedef std::vector<ValueHolder> ValHolderList;

class BaseClass
{
public:
    BaseClass() : members(0), is_inited(false) {}
    BaseClass(const BaseClass & bc) : members(0), is_inited(false) {}

    BaseClass & operator=(BaseClass & that);
    virtual ~BaseClass() {}

    virtual void RegisterAllMBS(ValHolderList& aList) = 0;
    void RegisterOneMBR(ValHolderList& aList, ValueHolder mbr);

    void Load(const char *filename);
    void Save(const char *filename);

private:
    ValHolderList members;
    bool          is_inited;

    void init_members();
};


////////////////////////////////////////////////////////////////////////////////
// some macro for simpler creating derived class of BasseClass
//

# define __myc_namembs(a) ((sizeof a) / (sizeof a[0]))

# define SAVE(ThisType) \
    void RegisterAllMBS(ValHolderList& aList) {

# define SAVE_PARENT(ThisType, ParentType) \
    SAVE(ThisType) ParentType::RegisterAllMBS(aList);

# define REG_MEMBER(ThisType, x) \
    RegisterOneMBR(aList, ValueHolder(&x, ThisType, #x))

# define REG_MEMBER_ARR(ThisType, x)              \
    for (size_t i = 0; i < __myc_namembs(x); i++) \
        REG_MEMBER(ThisType, x[i])                \

# define ENDSAVE }

#endif

//
//
//
