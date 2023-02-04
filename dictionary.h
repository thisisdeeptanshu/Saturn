typedef struct
{
  char** keys;
  char** values;
  int item_count;
  size_t size_k;
  size_t size_v;
} dictionary;

void d_init(dictionary* d)
{
  d->item_count = 0;
  d->keys = malloc(0);
  d->values = malloc(0);
  d->size_k = 0;
  d->size_v = 0;
}

void d_add(dictionary* d, char* key, char* value)
{
  d->size_k += (sizeof(char) * strlen(key));
  d->size_v += (sizeof(char) * strlen(value));

  d->item_count++;

  d->keys = realloc(d->keys, d->size_k);
  d->values = realloc(d->values, d->size_v);

  d->keys[d->item_count - 1] = key;
  d->values[d->item_count - 1] = value;
}

void d_remove(dictionary* d, char* key);

char* d_get(dictionary d, char* key)
{
  for (int i = 0; i < d.item_count; i++)
  {
    if (strcmp(d.keys[i], key) == 0) return d.values[i];
  }
  return "";
}

void d_uninit(dictionary* d)
{
  for (int i = 0; i < d->item_count; i++)
  {
    free(d->keys[i]);
    free(d->values[i]);
  }
  free(d->keys);
  free(d->values);
}
