typedef struct
{
  char** keys;
  char** values;
  int item_count;
  char* to_check;
} dictionary;

void d_init(dictionary* d)
{
  d->item_count = 0;
  d->keys = malloc(0);
  d->values = malloc(0);
  d->to_check = malloc(0);
}

void d_add(dictionary* d, char* key, char* value)
{
  d->item_count++;
  d->keys = realloc(d->keys, sizeof(d->keys) + sizeof(key));
  d->values = realloc(d->values, sizeof(d->values) + sizeof(value));
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

void d_set_to_check(dictionary* d, char* key)
{
  d->to_check = realloc(d->to_check, sizeof(key));
  d->to_check = key;
}

char* d_get_to_check(dictionary* d)
{
  return d_get(*d, d->to_check);
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
  free(d->to_check);
}
