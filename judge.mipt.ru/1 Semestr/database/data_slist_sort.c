#include <stdlib.h>

void list_sort(struct Node **list)
{
    if (*list == NULL || (*list)->next == NULL) {
	return;
    }
    struct Node *sorted_list = NULL;
    while (*list != NULL) {
	struct Node **max = list;
	for (struct Node ** cur = &(*list)->next; *cur != NULL;
	     cur = &(*cur)->next) {
	    if ((*cur)->val > (*max)->val) {
		max = cur;
	    }
	}
	struct Node *tmp = *max;
	*max = tmp->next;
	if ((sorted_list == NULL) || (tmp->val != sorted_list->val)) {
	    tmp->next = sorted_list;
	    sorted_list = tmp;
	} else {
	    free(tmp);
	}
    }
    *list = sorted_list;
}
