#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define HERE printf("You need to implement this code HERE!")

typedef struct {
    void **internal_array; // Use void ** to store pointers to any type
    unsigned int elements;
    unsigned int capacity;
} DynamicArray;

// This should return an array with 0 entries, capable
// of holding only 1 entry initially, but it ends up expanding
// later on.
DynamicArray *allocate_array() {
    DynamicArray *dynamicarray = (DynamicArray *)malloc(sizeof(DynamicArray)); 
    dynamicarray->internal_array = (void **)malloc(sizeof(void *));
    dynamicarray->elements = 0;
    dynamicarray->capacity = 1;
    return dynamicarray;
}

// This returns the element at the index. Like Python lists
// and standard C arrays, the first element is at index 0.
// Returns NULL if the index is out of range.
void *get_element(unsigned int index, DynamicArray *data) {
    if (present(index, data)) {
        return data->internal_array[index];
    } else {
        return NULL;
    }
}

// Like get, but instead of returning the element it returns
// a POINTER to the element. 
// Returns NULL if the index is invalid.
void **set_element(unsigned int index, DynamicArray *data) {
    if (present(index, data)) {
        return &(data->internal_array[index]);
    } else {
        return NULL;
    }
}

// This should free all the memory in the dynamic array.
void deallocate_array(DynamicArray *data) {
    for (unsigned int i = 0; i < data->elements; i++) {
        free(data->internal_array[i]); // Assuming each element is dynamically allocated
    }
    free(data->internal_array);
    free(data);
}

// This should add on an element at the end, resizing the
// array if necessary.
void append(void *element, DynamicArray *data) {
    if (data->elements == data->capacity) {
        data->capacity *= 2;
        data->internal_array = (void **)realloc(data->internal_array, data->capacity * sizeof(void *));
    }
    data->internal_array[data->elements] = element; // Store the pointer
    data->elements++;
}

// A boolean test on "is the index in the range of the array".
bool present(unsigned int index, DynamicArray *data) {
    return index < data->elements;
}
