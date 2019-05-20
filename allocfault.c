#include <stdio.h>
#include <stdlib.h>
#include <klee/klee.h>

int main()
{
    int num0, num1, num2, num3, num4;

    klee_make_symbolic(&num0, sizeof(int), "num0");

    if(num0 == 10)
    {
        klee_make_symbolic(&num1, sizeof(int), "num1");
        if(num1 == 999)
        {
            klee_make_symbolic(&num2, sizeof(int), "num2");
            if(num2 == 1234)
            {
                klee_make_symbolic(&num3, sizeof(int), "num3");
                if(num3 == 555)
                {
                    klee_make_symbolic(&num4, sizeof(int), "num4");
                    if(num4 == 47)
                    {
                        int i;
                        int* arr = (int* ) malloc(sizeof(int)*5);

                        for(i = 0; i < 100; i++)
                        {
                            arr[i] = i;
                            printf("%d", arr[i]);
                        }

                        free(arr);

                        for(i = 0; i < 100; i++)
                        {
                            printf("%d", arr[i]);
                        }
                    }
                }
            }
        }
    }

    return 0;
}