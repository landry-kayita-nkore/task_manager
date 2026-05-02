#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task.h"

static int next_id = 1;

Task *task_create(const char *title, const char *desc, Priority p) {
    Task *t = malloc(sizeof(Task));
    if (!t) { fprintf(stderr, "Erreur: allocation memoire\n"); return NULL; }
    t->id = next_id++;
    t->priority = p;
    t->status = STATUS_PENDING;
    t->created_at = (long)time(NULL);
    t->next = NULL;
    strncpy(t->title, title, MAX_TITLE - 1);
    t->title[MAX_TITLE - 1] = '\0';
    strncpy(t->desc, desc, MAX_DESC - 1);
    t->desc[MAX_DESC - 1] = '\0';
    t->checksum = compute_checksum(t);
    return t;
}

void task_free(Task *t) { free(t); }

void task_free_list(Task *head) {
    Task *cur = head;
    while (cur) { Task *next = cur->next; free(cur); cur = next; }
}

void task_print(const Task *t) {
    const char *pr[] = {"LOW", "MEDIUM", "HIGH"};
    const char *st[] = {"PENDING", "IN_PROGRESS", "DONE"};
    printf("---------------------------\n");
    printf("ID       : %d\n", t->id);
    printf("Titre    : %s\n", t->title);
    printf("Desc     : %s\n", t->desc);
    printf("Priorite : %s\n", pr[t->priority]);
    printf("Statut   : %s\n", st[t->status]);
    printf("Checksum : %u %s\n", t->checksum, validate_checksum(t) ? "[OK]" : "[INVALIDE]");
    printf("---------------------------\n");
}
