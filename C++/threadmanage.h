#ifndef THREADMANAGE_H
#define THREADMANAGE_H

#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <condition_variable>

using namespace std;
class ThreadManage
{
private:
    std::mutex mMutex;
    std::thread mThread;
    std::condition_variable mCondition_Variable;
    bool mTerminate = false;
public:
    enum class ThreadType {
        detach,
        join
    };

    ThreadManage();
    void waitNotifyVariable();
    template <class C, typename B>
    void runThread(C* obj, B (C::*func), ThreadType type)
    {
//        (obj->*func)(std::forward<A>(args)...);
        mThread = std::thread(func , obj);
        switch (type) {
        case ThreadType::detach:
            mThread.detach();
            break;
        case ThreadType::join:
            mThread.join();
            break;
        default:
            mThread.join();
            break;
        }
    }
    void notifyVariable();
};

#endif // THREADMANAGE_H
