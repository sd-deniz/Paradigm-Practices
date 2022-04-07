#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // one of the most light header file
#include <time.h>
#include <assert.h>


typedef float DATATYPE;

typedef struct tagARRAY_2D {
    // "H_ARRAY_2D", "H" is the initial letter of the word "handle"
    size_t size; // size of the first dimension of a 2 dimensional array
    DATATYPE (*array)[2];
}ARRAY_2D, *H_ARRAY_2D;


H_ARRAY_2D Create2DZerosArray(size_t size)
{
    H_ARRAY_2D h_array2d;
    if ((h_array2d = (H_ARRAY_2D)malloc(sizeof(ARRAY_2D))) == NULL)
    {
        return NULL;
    }

    if ((h_array2d->array = (DATATYPE (*)[2])calloc(size*2, sizeof(DATATYPE))) == NULL)
    {
        free(h_array2d);
        printf("Failed to create an array.\n");
        return NULL;
    }

    h_array2d->size = size;

    return h_array2d;
}


void plot_2d_array(H_ARRAY_2D A)
{
    for(int i=0;i<A->size ;i++){
        printf("\ni:%d, x:%f, y:%f ", i, A->array[i][0], A->array[i][1]);
    }
}


void euler_calculate(
        float (*derivative)(float),
        float delta_t,
        float x_init, float y_init,
        float x_limit)
    {
    /*
    ! Maximum array size depends on OS type, total number of steps, memory et cetera.

    Euler's formula required to create an approximation to the function.
    y1 = y0 + m*(x1-x0)
    m = dy/dx,
        m is f'(y0), modify the derivative depends on the needs
    ---
    Arguments:
        derivative  (*f)(float) : m
        x_init      (float)     : x0
        y_init      (float)     : y0
        delta_t     (float)     : delta_t -> the time step
        x_limit     (float)     : x_limit -> end point of the function
    */
    long int array_size = (int)((x_limit - x_init) / delta_t + 1);
    // A->array is a (array_size, 2) matrix which will be (x, y) pairs for each delta_t
    H_ARRAY_2D A = Create2DZerosArray(array_size);
    assert(A != NULL);

    A -> array[0][0] = x_init;
    A -> array[0][1] = y_init;

    float y0 = y_init, y1 = 0;
    float x0 = x_init, x1 = 0;

    for(int i=1; i<array_size; i++){
        x1 = x0 + delta_t;
        y1 = y0 + derivative(y0)*delta_t;
        A -> array[i][0] = x1;
        A -> array[i][1] = y1;
        y0 = y1;
        x0 = x1;
    }

    // plot_2d_array(A);
    free(A->array);
    free(A);
 }


float y_prime(float y)
{
    return 0.7 * y * (1-y/750) - 20;
}



void run_test(){
    // Important! clock() is not a proper&correct way to measure the performence.
    clock_t begin = clock();

    // Euler method test
    for(int i=0; i<100; i++){
        euler_calculate(y_prime, 2, 0, 30, 30);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nC Language: Elapsed: %f seconds\n", time_spent);
}


int main(){
    run_test();
    // Python Language - Elapsed: 0.0011363619705662131 seconds
    // C      Language - Elapsed: 0.000066 seconds

    // terminal Python Language - Elapsed: 0.0010130290174856782 seconds
    // terminal C Language      - Elapsed: 0.000271 seconds
}
