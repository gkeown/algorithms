#include <stdlib.h>
#include <stdio.h>

int
factorial(int n)
{
    if ((n == 0) || (n == 1)) {
        return 1;
    } else {
        return (n * factorial(n-1));
    }
}

// int
// main(int argc, char *argv[])
// {
//     int n = 4;
//     int result = 0;
// 
//     result = factorial(n);
//     printf("factorial of %d = %d\n", n, result);
// 
//     return 0;
// }

int
isArraySorted(int array[], int len)
{
    if (len == 1) {
        return 1;
    }

    if (array[len-1] > array[len-2]) {
        printf("index %d = %d index %d = %d\n", len-1, array[len-1], len-2, array[len-2]);
        return isArraySorted(array, len-1);
    } else {
        return 0;
    }
}

/*
   int
   main(int argc, char *argv[])
   {
   int array[] = {1, 2, 3, 4, 5};
   int result = 0;
   int size = sizeof(array) / sizeof (int);
   result = isArraySorted(array, size);
   printf("Array is %s.\n", (result) ? "sorted" : "not sorted"); 
   }
 */

int array[] = {0, 0, 0, 0, 0};
void binary(int n)
{
    if (n < 1) {
        printf("n = 0\n");
    } else {
        array[n-1] = 0;
        printf("n = %d value = %d\n", n, array[n-1]);
        binary(n-1);
        array[n-1] = 1;
        printf("n = %d value = %d\n", n, array[n-1]);
        binary(n-1);
    }
}

int
main(int argc, char *argv[])
{
    binary(3);
}
