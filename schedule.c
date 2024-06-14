#include <pthread.h>
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h> 
#include <linux/sched.h>
#include "schedule.h"
#include "/usr/include/python3.10/Python.h"
#include <linux/types.h>
#include <sys/syscall.h>   
#include <sys/sysinfo.h>
#include <stddef.h>
#define _GNU_SOURCE


pthread_t thread_id, thread_id1, thread_id2;
time_t rawtime1, rawtime2;

void catch_signal(int sig) {
pthread_cancel(thread_id);
pthread_join(thread_id, NULL);
pthread_cancel(thread_id1);
pthread_join(thread_id1, NULL);
pthread_cancel(thread_id2);
pthread_join(thread_id2, NULL);
PyGILState_Ensure();
Py_Finalize();
exit(0);
}

void * heavyThread(void *arg) //KOREAN AIR THREAD
{
printf("Acquired by 1\n");
PyGILState_STATE gstate;
gstate = PyGILState_Ensure();
struct timespec sleep_time, rem;

int ret;
struct sched_attr attr;
struct sched_param param;
attr.sched_priority=96;
attr.sched_policy=SCHED_FIFO;
attr.sched_runtime=30000000;
attr.sched_deadline=100000000;
attr.sched_period = 100000000;
pthread_attr_setschedparam(&attr, &param);
ret=syscall(SYS_sched_setattr, pthread_self(),&attr,0);


while (1) {
PyObject* sysPath = PySys_GetObject("path");
    PyList_Append(sysPath, PyUnicode_FromString("."));

 PyObject *pName = PyUnicode_FromString("flight");
    PyObject *pModule = PyImport_Import(pName);
    Py_INCREF(pName);

    if (pModule != NULL) {
    PyObject *pDict = PyModule_GetDict(pModule);
    PyObject *pFunc = PyDict_GetItem(pDict, PyUnicode_FromString("flight"));
    PyObject_CallObject(pFunc, NULL);
    Py_INCREF(pFunc);
    Py_INCREF(pModule);
    }

sleep(1);
}

PyGILState_Release(gstate); // Release GIL
pthread_exit(NULL);
}


void * thread(void *arg) //INCHEON AIRPORT THREAD
{
printf("Acquired by 2\n");
  PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

struct timespec sleep_time, rem;
char* releaseTime, finishTime;

int ret;
struct sched_attr attr;
struct sched_param param;
attr.sched_priority=99;
attr.sched_policy=SCHED_FIFO;
attr.sched_runtime=15000000;
attr.sched_deadline=60000000;
attr.sched_period = 60000000;
pthread_attr_setschedparam(&attr, &param);
ret=syscall(SYS_sched_setattr, pthread_self(),&attr,0);

    while(1){
PyObject *sysPath2 = PySys_GetObject("path");
        PyList_Append(sysPath2, PyUnicode_FromString("."));

        PyObject *pName2 = PyUnicode_FromString("flight2");
        PyObject *pModule2 = PyImport_Import(pName2);
        Py_INCREF(pName2);

        if (pModule2 != NULL) {
            PyObject *pDict2 = PyModule_GetDict(pModule2);
            PyObject *pFunc2 = PyDict_GetItem(pDict2, PyUnicode_FromString("flight"));
            if (PyCallable_Check(pFunc2)) {
                PyObject_CallObject(pFunc2, NULL);
            } else {
                //PyErr_Print();
            }
            Py_INCREF(pFunc2);
            Py_INCREF(pModule2);
        } else {
            //PyErr_Print();
        }

    int sleep_time_seconds = 1;
    sleep(sleep_time_seconds);
    }
    PyGILState_Release(gstate);
    pthread_exit(NULL);
}

void * threadAsiana(void *arg) //ASIANA AIRLINES THREAD
{
printf("Acquired by 3\n");
  PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

struct timespec sleep_time, rem;
char* releaseTime, finishTime;

int ret;
struct sched_attr attr;

struct sched_param param;
attr.sched_priority=90;
attr.sched_policy=SCHED_FIFO;
attr.sched_runtime=20000000;
attr.sched_deadline=80000000;
attr.sched_period = 80000000;
pthread_attr_setschedparam(&attr, &param);
ret=syscall(SYS_sched_setattr, pthread_self(),&attr,0);

    while(1){
PyObject *sysPath2 = PySys_GetObject("path");
        PyList_Append(sysPath2, PyUnicode_FromString("."));

        PyObject *pName2 = PyUnicode_FromString("flight3");
        PyObject *pModule2 = PyImport_Import(pName2);
        Py_INCREF(pName2);

        if (pModule2 != NULL) {
            PyObject *pDict2 = PyModule_GetDict(pModule2);
            PyObject *pFunc2 = PyDict_GetItem(pDict2, PyUnicode_FromString("flight"));
            if (PyCallable_Check(pFunc2)) {
                PyObject_CallObject(pFunc2, NULL);
            } else {
                //PyErr_Print();
            }
            Py_INCREF(pFunc2);
            Py_INCREF(pModule2);
        } else {
            //PyErr_Print();
        }

    int sleep_time_seconds = 1;
    sleep(sleep_time_seconds);
    }
    PyGILState_Release(gstate);
    pthread_exit(NULL);
}

int main(void) {
struct sched_param param;

signal(SIGTERM, catch_signal);
signal(SIGINT, catch_signal);

int argc;
char **argv;
Py_Initialize();
PyEval_InitThreads();

PyThreadState* thread_state = PyEval_SaveThread();
pthread_attr_t attr;
pthread_attr_init(&attr);

pthread_attr_setstacksize(&attr, 1024*1024); 

pthread_create (&thread_id1, NULL, thread, (void *)argv);
pthread_create (&thread_id, NULL, heavyThread, NULL);
pthread_create (&thread_id2, NULL, threadAsiana, (void *)argv);

 while (1) {
        sleep(100); 
    }
PyThreadState_Swap(thread_state);
return 0;
}
