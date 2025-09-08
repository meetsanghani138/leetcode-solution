/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumZero(int n, int* returnSize) {
    *returnSize = n;  
    int* result = (int*)malloc(n * sizeof(int));
    
    int index = 0;
    // If n is odd, include 0
    if (n % 2 == 1) {
        result[index++] = 0;
    }
    
    // Add pairs (-i, i)
    for (int i = 1; index < n; i++) {
        result[index++] = -i;
        result[index++] = i;
    }
    
    return result;
}