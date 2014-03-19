#pragma once

#include "ValueHolder.h"
#include <list>

#include <iostream>

typedef std::list<ValueHolder> ValHolderList;

class BaseClass {
public:

	BaseClass() : members(0), is_inited(false) {}
	BaseClass(const BaseClass & bc) : members(0), is_inited(false) {}

	BaseClass & operator=(BaseClass & that);

	void Load(const char *filename);
	void Save(const char *filename);

	virtual void RegisterAllMBS(ValHolderList& aList) = 0;

	void RegisterOneMBR(ValHolderList& aList, ValueHolder mbr);

	virtual ~BaseClass() {}

private:
	ValHolderList members;
	bool      is_inited;

	void init_members();
};


////////////////////////////////////////////////////////////////////////////////
// some macro for simpler creating derived class of BasseClass

# define __myc_namembs(a) ((sizeof a) / (sizeof a[0]))

#define SAVE(ThisType) \
	void RegisterAllMBS(ValHolderList& aList) {

#define SAVE_PARENT(ThisType, ParentType) \
	SAVE(ThisType) ParentType::RegisterAllMBS(aList);

#define REG_MEMBER(ThisType, x) RegisterOneMBR(aList, ValueHolder(&x, ThisType))

#define REG_MEMBER_ARR(ThisType, x)                  \
for (size_t _i = 0; _i < __myc_namembs(x); _i++) \
	REG_MEMBER(ThisType, x[_i])

#define ENDSAVE }

//
//
//
