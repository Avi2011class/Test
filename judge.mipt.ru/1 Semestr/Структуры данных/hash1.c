#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BU 100003
#define HASH(p) (p)
#define td typedef
td int i;
td size_t s;
struct O {
	i key;
	i value;
};
td struct O Q;
struct B {
	Q *data;
	s n;
	s allocated;
};
td struct B P;
struct H {
	P bu[BU];
};
td struct H N;


Q *hash_find_or_add(N *h, i k, i v)
{
	int hash = HASH(k);
	while (hash < 0) {
		hash += BU;
	}
	P *b = &h->bu[hash % BU];

	s i;
	for (i = 0; i < b->n; ++i) {
		if (!memcmp(&k, &b->data[i].key, sizeof(i))) {
			return &b->data[i];
		}
	}

	if (b->n >= b->allocated) {
		b->allocated = 2 * (b->allocated ? : 1);
		b->data =
		    realloc(b->data, sizeof(Q) * b->allocated);
	}

	Q *newly_created = &b->data[b->n++];
	newly_created->key = k;
	newly_created->value = v;
	return newly_created;
}

N *hash_create()
{
	return (N *)calloc(1, sizeof(N));
}

void hash_destroy(N *h)
{
	s i = 0;

	for (i = 0; i < BU; ++i) {
		free(h->bu[i].data);
		h->bu[i].n = 0;
		h->bu[i].allocated = 0;
	}

	free(h);
}

int main()
{
	N *h = hash_create();
	int value, r;
	Q *obj = NULL;

	while ((r = scanf("%d", &value)) != -1) {
		if (obj) {
			obj->value = value;
		}
		obj = hash_find_or_add(h, value, -1);
	}

	printf("%d\n", obj->value);

	hash_destroy(h);
	return 0;
}
