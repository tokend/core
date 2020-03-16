#pragma once

#include "EntryHelper.h"
#include "DataFrame.h"

namespace stellar 
{
class DataHelper : public EntryHelper 
{
public:
    virtual DataFrame::pointer
    loadData(uint64_t id) = 0;
};
}