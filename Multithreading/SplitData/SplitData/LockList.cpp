#include "LockList.h"
#include <algorithm>

void LockList::AddToList(int val)
{
    std::lock_guard<std::mutex> guard(lockListMutex);
    lockList.push_back(val);
}

bool LockList::ListContains(int valToFind)
{
    std::lock_guard<std::mutex> guard(lockListMutex);
    return find(lockList.begin(), lockList.end(), valToFind) != lockList.end();
}