#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include<stddef.h>

typedef struct map map;

// CRUD operations
// Create
map *map_new(size_t capacity);
map *map_create(size_t size, int arr[size][2], size_t capacity);

// Read
int map_get(map *map, int key);
size_t map_size(map *map);
void map_print(map *map);

// Update
size_t map_set(map *map, int key, int val);

// Delete
int map_delete(map *map, int key);
void map_free(map *map);

#endif
