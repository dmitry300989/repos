#pragma once
#include <list>
#include <mutex>

class LockList
{
private:
    std::list<int> lockList;
    std::mutex lockListMutex;

public:
    void AddToList(int val);

    bool ListContains(int valToFind);
};
