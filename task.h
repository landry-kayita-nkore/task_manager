#ifndef TASK_H
#define TASK_H

#define MAX_TITLE 100
#define MAX_DESC  200
#define DATA_FILE "tasks.dat"

typedef enum {
    PRIORITY_LOW,
    PRIORITY_MEDIUM,
    PRIORITY_HIGH
} Priority;

typedef enum {
    STATUS_PENDING,
    STATUS_IN_PROGRESS,
    STATUS_DONE
} Status;

typedef struct Task {
    int         id;
    char        title[MAX_TITLE];
    char        desc[MAX_DESC];
    Priority    priority;
    Status      status;
    long        created_at;
    unsigned int checksum;
    struct Task *next;
} Task;

/* task.c */
Task       *task_create(const char *title, const char *desc, Priority p);
void        task_free(Task *t);
void        task_free_list(Task *head);
void        task_print(const Task *t);

/* utils.c */
unsigned int compute_checksum(const Task *t);
int          validate_checksum(const Task *t);
void         save_tasks(Task *head);
Task        *load_tasks(void);
void         export_json(Task *head);
void         print_stats(Task *head);

#endif
