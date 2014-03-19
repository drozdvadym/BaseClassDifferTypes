#include "BaseClass.h"


//
// Local function feclaration
//

//
// define and declare prototypes for functions that will be generated 
// @{

void VH_Load(ValueHolder& valh, std::istream& ios);
void VH_Save(ValueHolder& valh, std::ostream& ios);

#define VH_LOAD_PROTO void VH_Load(ValueHolder& valh, std::istream& ios)
#define VH_SAVE_PROTO void VH_Save(ValueHolder& valh, std::ostream& ios)

// @}

//
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
    for (auto &mbr : members)
        VH_Load(mbr, std::cin);
}
void BaseClass::Save(const char *fileName) {
    init_members();

	std::cout << "Save:\n";
    for (auto &mbr : members)
        VH_Save(mbr, std::cout);
}

//
// Local function definitions
//

template <typename T>
void LoadDifferTypes(T * val, std::istream& is)
{
    is >> *val;
}

template <typename T>
void SaveDifferTypes(T * val, std::ostream& os)
{
    os << *val << std::endl;
}

//
// Generate functions
//

VH_FCN_BIND_VOID(VH_LOAD_PROTO, LoadDifferTypes, valh, ios);
VH_FCN_BIND_VOID(VH_SAVE_PROTO, SaveDifferTypes, valh, ios);
