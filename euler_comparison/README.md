# C-vs-Python-Euler-Method-Implementation
C and Python implementation of Euler method for solving first order differential equations. Includes simple speed comparison.

> y_prime = 0.7 * y * (1-y/750) - 20 
    
    # Python Language - Elapsed: 0.0011363619705662131 seconds
    # C      Language - Elapsed: 0.000066 seconds

    # terminal Python Language - Elapsed: 0.0010130290174856782 seconds
    # terminal C Language      - Elapsed: 0.000271 seconds
 
 \
 gcc --version -> 9.3.0\
 python --version -> 3.8.5

---

#### About the (2nd) commit:
Memory leak fixed.
Valgrind was used for dynamic analysis.

Valgrind output: 
```
==== HEAP SUMMARY:
====     in use at exit: 16 bytes in 1 blocks
====   total heap usage: 3 allocs, 2 frees, 1,168 bytes allocated
==== 
==== Searching for pointers to 1 not-freed blocks
==== Checked 74,792 bytes

16 bytes in 1 blocks are definitely lost in loss record 1 of 1
====    at 0x483B7F3: malloc (in /valgrind/vgpreload_memcheck-amd64-linux.so)
====    by 0x109222: Create2DZerosArray (in /euler)
====    by 0x10930E: euler_calculate (in /euler)
====    by 0x109548: run_test (in /euler)
====    by 0x1095BC: main (in /C-vs-Python-Euler-Method-Implementation/euler)
==== 
==== LEAK SUMMARY:
====    definitely lost: 16 bytes in 1 blocks
====    indirectly lost: 0 bytes in 0 blocks
====      possibly lost: 0 bytes in 0 blocks
====    still reachable: 0 bytes in 0 blocks
====         suppressed: 0 bytes in 0 blocks
```
**Explanation:**  
As stated in the valgrind output, the memory leak occurred due to reasons that depend on the "malloc" function.    
In the previous code dynamic array which is created in the "Create2DZerosArray" function was freed.  
But the pointer to the ARRAY_2D struct which is created in the "euler_calculate" function was not freed.  
*This caused a memory leak.*  

For comparison, 
When the "euler_calculate" function is called 10 times. "definitely lost" increased 10 times.

```
==== LEAK SUMMARY:
====    definitely lost: 160 bytes in 10 blocks
====    indirectly lost: 0 bytes in 0 blocks
====      possibly lost: 0 bytes in 0 blocks
====    still reachable: 0 bytes in 0 blocks
====         suppressed: 0 bytes in 0 blocks
```
**As a result,**
```C
free(A) solved the memory leak.
