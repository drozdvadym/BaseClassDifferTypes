//
// -*- Mode: c++; tab-width: 4; -*-
// -*- ex: ts=4 -*-
//

//
// BaseClass.cpp (Vadym Drozd)
// BaseClassDifferTypes/BaseClass.cpp
//

//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
// EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//

////////////////////////////////////////////////////////////////////////////////
// include section
//

#include "BaseClass.h"


////////////////////////////////////////////////////////////////////////////////
// Local function feclaration
//

void VH_Load(ValueHolder& valh, std::istream& is);
void VH_Save(ValueHolder& valh, std::ostream& os);

////////////////////////////////////////////////////////////////////////////////
// BaseClass member function section
//

BaseClass & BaseClass::operator = (BaseClass & that)
{
    if (this != &that) {
        is_inited = false;
        members.clear();
    }

    return *this;
}

void BaseClass::RegisterOneMBR(ValHolderList& aList, ValueHolder mbr)
{
    if (mbr.type_id == id_baseClass)
        ((BaseClass *)mbr.value)->RegisterAllMBS(aList);
    else
        aList.push_back(mbr);
}

void BaseClass::init_members()
{
    if (!is_inited)
        RegisterAllMBS(members);

    is_inited = true;
}

void BaseClass::Load(const char *fileName) {
    init_members();

    std::cout << "Load:\n";
    for (size_t i = 0; i < members.size(); i++) {
        std::cout << members[i].valname << ": ";
        VH_Load(members[i], std::cin);
    }
}
void BaseClass::Save(const char *fileName) {
    init_members();

    std::cout << "Save:\n";
    for (size_t i = 0; i < members.size(); i++) {
        std::cout << members[i].valname << ": ";
        VH_Save(members[i], std::cout);
        std::cout << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Local function definitions
//

void VH_Load(ValueHolder& valh, std::istream& is)
{
    VH_SWITCH_FCN_CALL_BLOCK(LoadDifferTypes, valh, is);
}

void VH_Save(ValueHolder& valh, std::ostream& os)
{
    VH_SWITCH_FCN_CALL_BLOCK(SaveDifferTypes, valh, os);
}

//
//
//
