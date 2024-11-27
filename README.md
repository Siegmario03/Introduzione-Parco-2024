Compiling note: To compile the project use g++ main.cpp impparallel.cpp sequential.cpp parallel.cpp benchmark.cpp -O3 -flto -fopenmp -fopenmp-simd -march=native -msse4.2 -ftree-vectorize in order to include all the files inside the executable.

Execution note: Execute with ./obj_file_name without passing any parameter or environment variables

Expected output: You should see in the terminal first of all the number of threads assigned for that segment and then a table containing the size of the matrix and the operation with corresponding time to execute; it takes some time when computing time with bigger 
  matrix because the program executes every measure n-times (by default 250) and then takes the average.

Notes on versions: The version of g++ used is 9.1.0, the version of C++ used is 14
