readme.txt
==========================
Improvement of performance
==========================
The single-threaded version of rendering takes 40 seconds to process a 131*131 
picture. By increasing the number of threads, we improve the performance of the
program. The number of seconds the program take to render a 131*131 picture is
inversely proportional to the number of threads. By running the program with 1,
2, 4, 8 threads, we approximate the execution time as a function fo threads: 
T(n) = 40/n. From 1 thread to 8 threads, the performance improves 35s. Overhead
is not a issue here to slow the performance because the number of threads is not
too large.
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m40.641s
user	0m40.636s
sys	0m0.003s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m20.794s
user	0m41.124s
sys	0m0.001s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m10.959s
user	0m43.136s
sys	0m0.003s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m5.769s
user	0m44.423s
sys	0m0.002s
mv 8-test.ppm.tmp 8-test.ppm

====================
Issues and decisions
====================
1. I didn't create the threadArgs array to pass into pthread_create function
at first and ran into segmentation fault.
2. I didn't move the print statements out of ThreadFunction and therefore the
pixels are printed multiple times.
3. I didn't change the way px increments in the for loop of rendering each pixel.
Every pixel was therefore rendered by every thread. I also didn't change the
starting index of the for loop.
4. I didn't make nthreads global, and ThreadFunction could not recognize it.
6. I didn't remove the if statement that exits the program when nthreads > 1.