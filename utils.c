#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

unsigned int compute_checksum(const Task *t) {
    unsigned int sum = 0;
    const char *p = t->title;
    while (*p) sum += (unsigned char)*p++;
    p = t->desc;
    while (*p) sum += (unsigned char)*p++;
    sum += t->id + t->priority + t->status;
    return sum;
}

int validate_checksum(const Task *t) {
    return compute_checksum(t) == t->checksum;
}

void save_tasks(Task *head) {
    FILE *f = fopen(DATA_FILE, "wb");
    if (!f) { fprintf(stderr, "Erreur ouverture fichier\n"); return; }
    Task *cur = head;
    while (cur) { fwrite(cur, sizeof(Task), 1, f); cur = cur->next; }
    fclose(f);
    printf("Taches sauvegardees.\n");
}

Task *load_tasks(void) {
    FILE *f = fopen(DATA_FILE, "rb");
    if (!f) return NULL;
    Task *head = NULL;
    Task *tail = NULL;
    Task tmp;
    while (fread(&tmp, sizeof(Task), 1, f) == 1) {
        Task *t = malloc(sizeof(Task));
        if (!t) break;
        memcpy(t, &tmp, sizeof(Task));
        t->next = NULL;
        if (!validate_checksum(t)) fprintf(stderr, "Checksum invalide ID %d\n", t->id);
        if (!head) head = t;
        else tail->next = t;
        tail = t;
    }
    fclose(f);
    return head;
}

void export_json(Task *head) {
    FILE *f = fopen("tasks.json", "w");
    if (!f) { fprintf(stderr, "Erreur creation JSON\n"); return; }
    const char *pr[] = {"LOW", "MEDIUM", "HIGH"};
    const char *st[] = {"PENDING", "IN_PROGRESS", "DONE"};
    fprintf(f, "[\n");
    Task *cur = head;
    while (cur) {
        fprintf(f, "  {\n");
        fprintf(f, "    \"id\": %d,\n", cur->id);
        fprintf(f, "    \"title\": \"%s\",\n", cur->title);
        fprintf(f, "    \"desc\": \"%s\",\n", cur->desc);
        fprintf(f, "    \"priority\": \"%s\",\n", pr[cur->priority]);
        fprintf(f, "    \"status\": \"%s\",\n", st[cur->status]);
        fprintf(f, "    \"checksum\": %u\n", cur->checksum);
        fprintf(f, "  }%s\n", cur->next ? "," : "");
        cur = cur->next;
    }
    fprintf(f, "]\n");
    fclose(f);
    printf("Export JSON -> tasks.json\n");
}

void print_stats(Task *head) {
    int total=0, pending=0, in_progress=0, done=0;
    int low=0, medium=0, high=0;
    Task *cur = head;
    while (cur) {
        total++;
        if (cur->status == STATUS_PENDING) pending++;
        if (cur->status == STATUS_IN_PROGRESS) in_progress++;
        if (cur->status == STATUS_DONE) done++;
        if (cur->priority == PRIORITY_LOW) low++;
        if (cur->priority == PRIORITY_MEDIUM) medium++;
        if (cur->priority == PRIORITY_HIGH) high++;
        cur = cur->next;
    }
    printf("\n=== STATISTIQUES ===\n");
    printf("Total      : %d\n", total);
    printf("En attente : %d\n", pending);
    printf("En cours   : %d\n", in_progress);
    printf("Terminees  : %d\n", done);
    printf("Priorite basse   : %d\n", low);
    printf("Priorite moyenne : %d\n", medium);
    printf("Priorite haute   : %d\n", high);
    printf("====================\n");
}
