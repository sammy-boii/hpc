#include <stdio.h>

void sayHe110()
{
    printf("Hello world from OpenMP!\n");
}
void main()
{
#pragma omp parallel num_threads(4)
    sayHe110();
}