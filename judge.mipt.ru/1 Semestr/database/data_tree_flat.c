#include <stdlib.h>
#include <string.h>

int
cr_suf (const void *__1, const void *__2)
{
  if (*(int *) (__1) > *(int *) (__2))
    return 1;
  else if (*(int *) (__1) < *(int *) (__2))
    return -1;
  else
    return 0;
}

struct Node *
cr_rec (int *array, int L, int R)
{
  if (L == R)
    {
      return NULL;
    }
  int M = L + (R - L) / 2;
  struct Node *res = malloc (sizeof (struct Node));
  if (M < R)
    {
      res->x = array[M];
      res->left = cr_rec (array, L, M);
      res->right = cr_rec (array, M + 1, R);
    }
  else
    {
      res->x = array[L];
      res->left = NULL;
      res->right = NULL;
    }
  return res;
}

struct Node *
create_flat (int *a, int n)
{
  int *sorted = malloc (n * sizeof (*a));
  memcpy (sorted, a, n * sizeof (*a));
  qsort (sorted, n, sizeof (*sorted), cr_suf);
  struct Node *tree = cr_rec (sorted, 0, n);
  free (sorted);
  return tree;
}
