# C-multithreaded-version-of-Matrix-Multiplication
I Implemented a multithreaded version of Matrix Multiplication Calculator. It spawns multiple threads to compute the result concurrently.  -Given the input matrices A and B, and defining C as AB = C, compute the values of matrix C  
  -Ex. See next page  
-Use Pthread Lib. in Linux  
-Each thread calculates the product of a row and a column.  
-Thus, the number of created threads depends on the matrix dimensions.  

-Input file format: 
 -Two matrices separated by an empty line  
 -For each matrix  
    -The first row is the matrix dimension.  
    -The following rows are the rows of the matrix. 

-Output file format:  
 -Store the result  
 -The same format as the matrix in the input file

How to run this program: 
 gcc matrixPthread.c -o matrixPthread -lpthread 
 ./matrixPthread input_matrix.txt 
(input_matrix.txt is the name of the input file,you can modify its content to meet your needs. )

///////////////////////////////////   

The content and format of the input file,input_matrix.txt : 
3 3
1 2 1 
2 3 2
1 2 1

3 5
1 2 3 4 5
2 3 4 5 6
3 4 5 6 7

//////////////////////////////////////////////////  
 Matrix multiplication result will be stored in a file called "output_matrix.txt" 
 ex:
 3 5 
 8 12  16  20  24 
 14  21  28  35  42 
 8   12  16  20  24 
