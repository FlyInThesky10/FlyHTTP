#pragma once

#include <functional>
#include <memory>
#include <pthread.h>

#include "Atomic.h"
#include "CountDownLatch.h"
#include "Types.h"

namespace flyhttp
{

class Thread : noncopyable {
public:
    typedef std::function<void ()> ThreadFunc;

    explicit Thread(ThreadFunc, const string& name = string());
    ~Thread();

    void start();
    int join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const string& name() const { return name_; }

    static int numCreated() { return numCreated_.get(); }

private:
    void setDefaultName();

    bool       started_;
    bool       joined_;
    pthread_t  pthreadId_;
    pid_t      tid_;
    ThreadFunc func_;
    string     name_;
    CountDownLatch latch_;

    static AtomicInt32 numCreated_;
};

}