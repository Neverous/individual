#include "maklib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int n;
static int* data;

static void Init() {
  static int initialized = 0;
  int i;
  if (initialized)
    return;
  assert(1 == scanf("%d", &n));
  data = (int*)malloc((n + 1) * sizeof(int));
  assert(data != NULL);
  for (i = 1; i <= n; ++i) {
    assert(1 == scanf("%d", data + i));
  }
  initialized = 1;
}

int Size() {
  Init();
  return n;
}

int ElementAt(int i) {
  Init();
  assert(1 <= i && i <= n);
  return data[i];
}
