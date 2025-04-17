#include<stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum ERROR_TYPE {
  CAPACITY_EXCEEDED = 1,
  UNREACHABLE_CODE
};

typedef struct kv_pair {
  int key;
  int val;
} kv_pair;

typedef struct map {
  kv_pair* buffer;
  size_t size;
  size_t capacity;
} map;

int hash(map *m, int x){
  return x%m->capacity;
}

map *map_new(size_t capacity){
  map* m = malloc(sizeof(map));
  m->capacity = capacity;
  m->size = 0;
  m->buffer = malloc(sizeof(kv_pair)*capacity);

  return m;
}

void map_print(map *map){
  printf("{\n");
  for(int i=0; i<map->capacity; i++){
    printf("  %d -> (%d, %d)\n", i, map->buffer[i].key, map->buffer[i].val);
  }
  printf("}\n");
};

int map_get_buffer_idx(map *map, int key){
  int idx = hash(map, key);
  int idx_key = map->buffer[idx].key;
  if(idx_key != key){
    for(int i=idx; i<map->capacity; i++){
    for(int i=idx; i<idx+map->capacity; i++){
      int buffer_idx = i%map->capacity;
      if(map->buffer[buffer_idx].key == key){
        return buffer_idx;
      } else if(map->buffer[buffer_idx].key == 0) {
        return -1;
      }
    }
  }
  } else {
    return idx;
  }

  exit(UNREACHABLE_CODE);
}

int map_get(map *map, int key){
  int idx = hash(map, key);
  int idx_key = map->buffer[idx].key;
  if(idx_key != key){
    for(int i=idx; i<idx+map->capacity; i++){
      int buffer_idx = i%map->capacity;
      if(map->buffer[buffer_idx].key == key){
        return map->buffer[buffer_idx].val;
      } else if(map->buffer[buffer_idx].key == 0) {
        return 0;
      }
    }
  } else {
    return map->buffer[idx].val;
  }

  exit(UNREACHABLE_CODE);
};

size_t map_set(map *map, int key, int val){
  if(map->size >= map->capacity) {
    exit(CAPACITY_EXCEEDED);
  }

  int idx = hash(map, key);
  if(map->buffer[idx].key == 0){
      map->buffer[idx].key = key;
      map->buffer[idx].val = val;
      return ++(map->size);
  }
  for(int i=idx+1; i<idx+map->capacity; i++){
    int buffer_idx = i%map->capacity;
    if(map_get(map, buffer_idx) == 0){
      map->buffer[buffer_idx].key = key;
      map->buffer[buffer_idx].val = val;
      return ++(map->size);
    }
  }
  exit(UNREACHABLE_CODE);
};

size_t map_size(map *map){
  return map->size;
};

int map_delete(map *map, int key){
  int result = map_get(map, key);
  int idx = map_get_buffer_idx(map, key);
  if(idx == -1){
    return 0;
  }
  map->buffer[idx].key = 0;
  map->buffer[idx].val = 0;
  
  map->size -= 1;
  return result;
};

map *map_create(size_t size, int arr[size][2], size_t capacity){
  map* m = map_new(capacity);

  for(int i=0; i<size; i++){
    map_set(m, arr[i][0], arr[i][1]);
  }

  return m;
};

void map_free(map *map){
  free(map->buffer);
  free(map);
};














