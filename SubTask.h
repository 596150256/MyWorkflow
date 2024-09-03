#ifndef _SUBTASK_H_
#define _SUBTASK_H_

#include <stddef.h>
//
class parallelTask;

class subTask
{
public:
    virtual void dispatch() = 0;

private:
    virtual subTask* done() = 0;

protected:
    void subtask_done();

private:
    parallelTask* parent;

public:
    subTask()
    {
        this->parent = NULL;
    }

    virtual ~subTask() {}
    friend class parallelTask;
};

class parallelTask : public subTask
{
public:
    virtual void dispatch();

private:
    virtual subTask* done();

protected:
    subTask** subtasks;
    size_t subtasks_nr;

private:
    size_t nleft;

public:
    parallelTask(subTask** subtasks, size_t n)
    {
        this->subtasks = subtasks;
        this->subtasks_nr = n;
    }

    virtual ~parallelTask() {}
    friend class subTask;
};

#endif