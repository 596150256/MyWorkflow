/*
    Just for studying
    Author: Tj
*/

#ifndef _EXECUTOR_H_
#define _EXECUTOR_H_

#include <stddef.h>
#include <pthread.h>
#include "list.h"

class ExecQueue
{
public:
    int init();
    void deinit();

private:
    struct list_head session_list;
    pthread_mutex_t mutex;

public:
    virtual ~ExecQueue() { }
    friend class Executor;
};

#define ES_STATE_FINISHED 0
#define ES_STATE_ERROR    1
#define ES_STATE_CANCELED 2

class ExecSession
{
private:
    virtual void execute() = 0;
    virtual void handle(int state, int error) = 0;

protected:
    ExecQueue *get_queue() const { return this->queue; }

private:
    ExecQueue *queue;

public:
    virtual ~ExecSession() { }
    friend class Executor;
};

class Executor
{
public:
    int init(size_t nthreads);
    void deinit();

    int request(ExecSession *session, ExecQueue *queue);

public:
    int increase_thread();
    int decrease_thread();

private:
    struct __thrdpool *thrdpool;

private:
    static void executor_thread_routine(void *context);
    static void executor_cancel(const struct thrdpool_task *task);

public:
    virtual ~Executor() { }
};

#endif