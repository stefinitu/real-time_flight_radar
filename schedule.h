#include <sched.h> 
#include <linux/sched.h>
#include <stdint.h>

typedef struct sched_attr {
    int size;
    int sched_policy;
    int sched_runtime;
    int sched_period;
    int sched_deadline;
    int sched_priority;
    int32_t sched_nice;
} sched_attr;