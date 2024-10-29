#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

long long int global_var1 = 1;
long long int global_var2 = 2;
long long int global_var3 = 3;

void recur_func(long long int n, uintptr_t prev_address)
{
    long long int local_var = n;
    uintptr_t current_address = (uintptr_t)&local_var;
    printf("Stack (%lld): = %p (%" PRIuPTR ")", n, (void*)&local_var, current_address);

    if (prev_address != 0)
    {
        printf(", decrease = %" PRIdPTR, prev_address - current_address);
    }
    printf("\n");

    if (n > 1)
        recur_func(n - 1, current_address);
}

int main()
{
    printf("global_var1 = %p (%" PRIuPTR ")\n", (void*)&global_var1, (uintptr_t)&global_var1);
    printf("global_var2 = %p (%" PRIuPTR ")\n", (void*)&global_var2, (uintptr_t)&global_var2);
    printf("global_var3 = %p (%" PRIuPTR ")\n", (void*)&global_var3, (uintptr_t)&global_var3);
    
    long long int *heap_ptr1 = (long long int *)malloc(sizeof(long long int));
    printf("malloc() heap_1 = %p (%" PRIuPTR ")\n", (void*)heap_ptr1, (uintptr_t)heap_ptr1);

    long long int *heap_ptr2 = (long long int *)malloc(sizeof(long long int));
    printf("malloc() heap_2 = %p (%" PRIuPTR "), increase = %" PRIdPTR "\n", (void*)heap_ptr2, (uintptr_t)heap_ptr2, (uintptr_t)heap_ptr2 - (uintptr_t)heap_ptr1);

    long long int *heap_ptr3 = (long long int *)malloc(sizeof(long long int));
    printf("malloc() heap_3 = %p (%" PRIuPTR "), increase = %" PRIdPTR "\n", (void*)heap_ptr3, (uintptr_t)heap_ptr3, (uintptr_t)heap_ptr3 - (uintptr_t)heap_ptr2);
    
    recur_func(3, 0);

    free(heap_ptr1);
    free(heap_ptr2);
    free(heap_ptr3);

    return 0;
}
