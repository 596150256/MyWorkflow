#include "SubTask.h"
#include <iostream>
#include <vector>
using namespace std;

class computeTask : public subTask
{
public:
    virtual void dispatch() override
    {
        cout << "Computing..." << endl;

        this->subtask_done();
    }

    virtual subTask* done() override
    {
        cout << "Compute done." << endl;
        return nullptr;
    }
};

class waitTask : public subTask
{
    virtual void dispatch() override
    {
        cout << "Waiting..." << endl;

        this->subtask_done();
    }

    virtual subTask* done() override
    {
        cout << "Wait complete." << endl;
        return nullptr;
    }
};

void test_oneLayer_parallel()
{
    cout << "test_oneLayer_parallel" << endl;

    subTask* tasks[] = {new computeTask(), new waitTask(), new computeTask()};

    parallelTask* mainTask = new parallelTask(tasks, 3);

    mainTask->dispatch();

    delete mainTask;
    for (auto task : tasks)
        delete task;
}

void test_twoLayer_parallel()
{
    cout << "test_twoLayer_parallel" << endl;
    
    subTask* tasks1[] = {new computeTask(), new waitTask(), new computeTask()};

    parallelTask* para1 = new parallelTask(tasks1, 3);

    subTask* tasks2[] = {new computeTask(), new waitTask(), new computeTask()};

    parallelTask* para2 = new parallelTask(tasks2, 3);

    subTask* tasks3[] = {new computeTask(), new waitTask(), new computeTask()};

    parallelTask* para3 = new parallelTask(tasks3, 3);

    subTask* paraTasks[] = {para1, para2, para3};

    parallelTask* mainTask = new parallelTask(paraTasks, 3);

    mainTask->dispatch();

    delete mainTask;
    for (auto task : paraTasks)
        delete task;

    for (auto task : tasks1)
        delete task;

    for (auto task : tasks2)
        delete task;

    for (auto task : tasks3)
        delete task;
}

int main() {
    test_oneLayer_parallel();
    test_twoLayer_parallel();
        
    return 0;
}