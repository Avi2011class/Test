#include <stdlib.h>

void
merge2(struct Node *__1, struct Node *__2)
{
    if (__1 != NULL) {
	__1->next = __2;
    }
    if (__2 != NULL) {
	__2->prev = __1;
    }
}

void
merge3(struct Node *_1, struct Node *_2, struct Node *_3)
{
    merge2(_1, _2);
    merge2(_2, _3);
}

void
list_sort(struct Node **list)
{
    if (*list == NULL || (*list)->next == NULL) {
	return;
    }
    struct Node     src;
    merge3(NULL, &src, *list);

    struct Node    *result = NULL;

    while (src.next != NULL) {
	struct Node    *max = src.next;
	for (struct Node * cur = max->next; cur != NULL; cur = cur->next) {
	    if (cur->val > max->val) {
		max = cur;
	    }
	}
	struct Node    *tmp = max;
	merge2(tmp->prev, tmp->next);
	if ((result == NULL) || (tmp->val != result->val)) {
	    merge3(NULL, tmp, result);
	    result = tmp;
	} else {
	    free(tmp);
	}
    }
    *list = result;
}
