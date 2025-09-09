// ✅ helper function defined before use
bool isNoZero(int num) {
    while (num > 0) {
        if (num % 10 == 0) return 0; // contains a zero
        num /= 10;
    }
    return 1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getNoZeroIntegers(int n, int* returnSize) {
    int* ans = (int*)malloc(2 * sizeof(int));

    for (int a = 1; a < n; a++) {
        int b = n - a;
        if (isNoZero(a) && isNoZero(b)) {
            ans[0] = a;
            ans[1] = b;
            *returnSize = 2;
            return ans;
        }
    }
    
    *returnSize = 0; // not needed, problem guarantees a solution
    return ans;
}