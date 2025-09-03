#include <stdio.h>
#include <stdlib.h>

// ---------- Define Structs First ----------
typedef struct {
    int pass;
    int total;
} Class;

typedef struct {
    Class *arr;
    int size;
    int capacity;
} MaxHeap;

// ---------- Gain Function ----------
double gain(int pass, int total) {
    return (double)(pass + 1) / (total + 1) - (double)pass / total;
}

// ---------- Heap Utilities ----------
void swap(Class *a, Class *b) {
    Class tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapifyDown(MaxHeap *heap, int idx) {
    int largest = idx;
    int left = 2 * idx + 1, right = 2 * idx + 2;

    if (left < heap->size &&
        gain(heap->arr[left].pass, heap->arr[left].total) >
        gain(heap->arr[largest].pass, heap->arr[largest].total)) {
        largest = left;
    }
    if (right < heap->size &&
        gain(heap->arr[right].pass, heap->arr[right].total) >
        gain(heap->arr[largest].pass, heap->arr[largest].total)) {
        largest = right;
    }
    if (largest != idx) {
        swap(&heap->arr[idx], &heap->arr[largest]);
        heapifyDown(heap, largest);
    }
}

void heapifyUp(MaxHeap *heap, int idx) {
    if (idx == 0) return;
    int parent = (idx - 1) / 2;
    if (gain(heap->arr[idx].pass, heap->arr[idx].total) >
        gain(heap->arr[parent].pass, heap->arr[parent].total)) {
        swap(&heap->arr[idx], &heap->arr[parent]);
        heapifyUp(heap, parent);
    }
}

void push(MaxHeap *heap, Class c) {
    heap->arr[heap->size] = c;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

Class pop(MaxHeap *heap) {
    Class root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return root;
}

// ---------- Solution Function ----------
double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    MaxHeap heap;
    heap.arr = (Class*)malloc(sizeof(Class) * (classesSize + extraStudents));
    heap.size = 0;
    heap.capacity = classesSize + extraStudents;

    // Insert all classes into heap
    for (int i = 0; i < classesSize; i++) {
        Class c = { classes[i][0], classes[i][1] };
        push(&heap, c);
    }

    // Assign extra students
    for (int i = 0; i < extraStudents; i++) {
        Class c = pop(&heap);
        c.pass++;
        c.total++;
        push(&heap, c);
    }

    // Calculate final average
    double sum = 0.0;
    for (int i = 0; i < heap.size; i++) {
        sum += (double)heap.arr[i].pass / heap.arr[i].total;
    }

    free(heap.arr);
    return sum / classesSize;
}
