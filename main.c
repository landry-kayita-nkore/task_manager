#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

void print_menu(void) {
    printf("\n=== TASK MANAGER ===\n");
    printf("1. Ajouter une tache\n");
    printf("2. Afficher toutes les taches\n");
    printf("3. Modifier le statut d'une tache\n");
    printf("4. Supprimer une tache\n");
    printf("5. Exporter en JSON\n");
    printf("6. Statistiques\n");
    printf("7. Sauvegarder et quitter\n");
    printf("Choix: ");
}

Task *add_task(Task *head) {
    char title[MAX_TITLE];
    char desc[MAX_DESC];
    int  priority;

    printf("Titre: ");
    fgets(title, MAX_TITLE, stdin);
    title[strcspn(title, "\n")] = '\0';

    printf("Description: ");
    fgets(desc, MAX_DESC, stdin);
    desc[strcspn(desc, "\n")] = '\0';

    printf("Priorite (0=LOW, 1=MEDIUM, 2=HIGH): ");
    scanf("%d", &priority);
    getchar();

    Task *t = task_create(title, desc, (Priority)priority);
    if (!t) return head;

    t->next = head;
    printf("Tache ajoutee avec succes ! ID: %d\n", t->id);
    return t;
}

Task *delete_task(Task *head, int id) {
    Task *cur  = head;
    Task *prev = NULL;

    while (cur) {
        if (cur->id == id) {
            if (prev) prev->next = cur->next;
            else head = cur->next;
            task_free(cur);
            printf("Tache %d supprimee.\n", id);
            return head;
        }
        prev = cur;
        cur  = cur->next;
    }
    printf("Tache %d introuvable.\n", id);
    return head;
}

void update_status(Task *head, int id) {
    Task *cur = head;
    while (cur) {
        if (cur->id == id) {
            int s;
            printf("Nouveau statut (0=PENDING, 1=IN_PROGRESS, 2=DONE): ");
            scanf("%d", &s);
            getchar();
            cur->status   = (Status)s;
            cur->checksum = compute_checksum(cur);
            printf("Statut mis a jour.\n");
            return;
        }
        cur = cur->next;
    }
    printf("Tache %d introuvable.\n", id);
}

int main(void) {
    Task *head = load_tasks();
    int   choice;
    int   id;

    printf("Task Manager - Landry Kayita-Nkore\n");

    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                head = add_task(head);
                break;
            case 2:
                if (!head) printf("Aucune tache.\n");
                else {
                    Task *cur = head;
                    while (cur) { task_print(cur); cur = cur->next; }
                }
                break;
            case 3:
                printf("ID de la tache a modifier: ");
                scanf("%d", &id); getchar();
                update_status(head, id);
                break;
            case 4:
                printf("ID de la tache a supprimer: ");
                scanf("%d", &id); getchar();
                head = delete_task(head, id);
                break;
            case 5:
                export_json(head);
                break;
            case 6:
                print_stats(head);
                break;
            case 7:
                save_tasks(head);
                task_free_list(head);
                printf("Au revoir!\n");
                return 0;
            default:
                printf("Choix invalide.\n");
        }
    }
}
