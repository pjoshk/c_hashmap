#include <assert.h>
#include <stdio.h>
#include "./hashmap.c"

// int main() {
//   int arr[3][2] = {
//     {5, 100},
//     {10, 2897},
//     {3, 9769}    
//   };

//   map* m = map_create(3, arr, 5);
//   // map* m = map_new(5);
//   map_print(m);

//   map_set(m, 234, 100);
//   map_print(m);
//   map_set(m, 987, 200);

//   map_print(m);

//   printf("[DEBUG] map_get: %d", map_get(m, 10));

//   return 0;
// }
// #include "hashmap.h"

void test_empty_map() {
    map *m = map_new(10);
    assert(m != NULL);
    assert(map_size(m) == 0);
    assert(map_get(m, 42) == 0); // Assuming default return value for missing key is 0
    map_free(m);
}

void test_insert_and_get() {
    map *m = map_new(10);
    assert(map_set(m, 1, 100) == 1);
    assert(map_get(m, 1) == 100);
    assert(map_size(m) == 1);
    map_free(m);
}

void test_overwrite_value() {
    map *m = map_new(10);
    map_set(m, 1, 100);
    assert(map_get(m, 1) == 100);
    map_set(m, 1, 200);
    assert(map_get(m, 1) == 200);
    assert(map_size(m) == 1); // Size shouldn't increase
    map_free(m);
}

void test_delete_key() {
    map *m = map_new(10);
    map_set(m, 1, 100);
    assert(map_get(m, 1) == 100);
    assert(map_delete(m, 1) == 100);
    assert(map_get(m, 1) == 0); // Again, assuming 0 for missing key
    assert(map_size(m) == 0);
    map_free(m);
}

void test_delete_nonexistent_key() {
    map *m = map_new(10);
    assert(map_delete(m, 1234) == 0); // Should be safe
    map_free(m);
}

void test_map_create_from_array() {
    int arr[3][2] = {
        {1, 100},
        {2, 200},
        {3, 300}
    };
    map *m = map_create(3, arr, 10);
    assert(map_size(m) == 3);
    assert(map_get(m, 1) == 100);
    assert(map_get(m, 2) == 200);
    assert(map_get(m, 3) == 300);
    map_free(m);
}

void test_map_collision_handling() {
    // This depends on your hash function! If it's mod-based, keys like 1 and 11
    // will collide with capacity 10.
    map *m = map_new(10);
    map_set(m, 1, 111);
    map_set(m, 11, 222);
    assert(map_get(m, 1) == 111);
    assert(map_get(m, 11) == 222);
    assert(map_size(m) == 2);
    map_free(m);
}

int main() {
    test_empty_map();
    test_insert_and_get();
    test_overwrite_value();
    test_delete_key();
    test_delete_nonexistent_key();
    test_map_create_from_array();
    test_map_collision_handling();

    printf("All tests passed.\n");
    return 0;
}
