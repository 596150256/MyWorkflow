#include "SubTask.h"

void subTask::subtask_done()
{
    subTask* cur = this;
    parallelTask* parent;

    while (1)
    {
        parent = cur->parent;
        cur = cur->done();
        if (cur)
        {
            cur->parent = parent;
            cur->dispatch();
        }
        else if (parent)
        {
            if (__sync_sub_and_fetch(&parent->nleft, 1) == 0)
            {
                cur = parent;
                continue;
            }
        }
        break;
    }
}

void parallelTask::dispatch()
{
    subTask** end = this->subtasks + this->subtasks_nr;
    subTask** p = this->subtasks;

    this->nleft = this->subtasks_nr;
    if (this->nleft != 0)
    {
        do
        {
            (*p)->parent = this;
            (*p)->dispatch();            
        } while (++p != end);
    }
    else
        this->subtask_done();
}

subTask* parallelTask::done()
{
    return NULL;
}