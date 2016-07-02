#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <math.h>


    int **Matrix;
    int FirstRow,FirstColumn,SecondRow,SecondColumn,TotalRow,TotalColumn;
    
    int i,Row,Column;
    int **FirstMatrix;
    int **SecondMatrix;
    int **Multiplication;
    //this is for passing more than one arguments to thread function
    struct arg_struct 
    {
        int thread_row;
        int thread_column;
    
    };

void print_matrix(int rows, int cols, int **mat){
    int i=0,j=0;
  for(i=0; i<rows; i++){    /* Iterate of each row */
        for(j=0; j<cols; j++){  /* In each row, go over each col element  */
            printf("%d ",mat[i][j]); /* Print each row element */
        }
        printf("\n");
    }
}


void free_matrix(int rows, int **mat){
    int i=0;
    for(i=0;i<rows;i++)    
        free(mat[i]);
    free(mat);
}
    

void* multiply_matrix(void *arguments)
{
    
    struct arg_struct *args = arguments;
    
    int thread_sum=0;//store the calculation result in this thread.

    //calculate the multiplication of the current row of first matrix and column of second matrix.
    for (i = 0; i < SecondRow; i++) 
        {

         
          thread_sum = thread_sum + (FirstMatrix[args -> thread_row][i]*SecondMatrix[i][args -> thread_column]);
           
        }
        //store the result to the Multiplication matrix .
        Multiplication[args -> thread_row][args -> thread_column] = thread_sum;
        
    pthread_exit(NULL);
    return NULL;   
    

}
int main(int argc,char* argv[]) 
{

/////////////// read input matrixes

    FILE *fp;
    pthread_t  *threads;//to generate an array of thread.
    struct arg_struct *args;
    args=( struct arg_struct *) malloc((FirstRow*SecondColumn)* sizeof( struct arg_struct));
   

    if (argc != 2) {
        fprintf(stderr, "Usage: %s file.txt\n", argv[0]);
        exit(1);
    }
    if (!(fp = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(1);
    }
    
    for(i=1;i<=2;i++)
    {
        /////////////////////read matrix////////////
            fscanf(fp, "%d%d",&TotalRow,&TotalColumn);
            printf("Input Matrix%d : Row= %d,Column= %d\n",i,TotalRow,TotalColumn);
               
            //setup 2D array to store input matrix
            Matrix = (int **) malloc(sizeof(int *)*TotalRow);
            for(Row=0; Row<TotalRow; Row++)
                Matrix[Row] = (int *) malloc(sizeof(int)*TotalColumn); 



           // read a matrix
            for (Row = 0; Row < TotalRow; Row++)
                for (Column = 0; Column < TotalColumn; Column++)
                    fscanf(fp,"%d", &Matrix[Row][Column]);
/////////////////////////end read matrix//////
            if(i==1)
            {
                FirstMatrix=Matrix;
                FirstRow=TotalRow;
                FirstColumn=TotalColumn;
                print_matrix(FirstRow,FirstColumn,FirstMatrix);
            }

            else
            {
                SecondMatrix=Matrix;
                SecondRow=TotalRow;
                SecondColumn=TotalColumn;
                print_matrix(SecondRow,SecondColumn,SecondMatrix);

                
            }

           
           

    }
     
   
    fclose(fp);

 ///////////////finish read input matrixes

    
//setup 2D array to store the result after multiplication

    Multiplication = (int **) malloc(sizeof(int *)*FirstRow);
    for(Row=0; Row<FirstRow; Row++)
        Multiplication[Row] = (int *) malloc(sizeof(int)*SecondColumn); 

    //setup an array of threads with the same size as Multiplication
    threads = (pthread_t *) malloc((FirstRow*SecondColumn)* sizeof(pthread_t));
    
    //setup an array of the arguments of thread functions with the same size as Multiplication
    args=( struct arg_struct *) malloc((FirstRow*SecondColumn)* sizeof( struct arg_struct));
   
    int num_of_thread=0;//indicate num of thread.
    
    //measure elapsed time .
    /*
    double micros = 0.0;
    float millis = 0.0;
    clock_t start, end;
    start = clock();
    */

    //multiply two matrixes
    for (Row = 0; Row < FirstRow; Row++) 
    {
      for (Column = 0; Column < SecondColumn; Column++) 
      {
        //record the current row of first matrix and column of second matrix so as to pass these data to thread function.
        args[num_of_thread].thread_row = Row;
        args[num_of_thread].thread_column = Column;
        
        
        if(pthread_create(&threads[num_of_thread], NULL, multiply_matrix,(void *)&args[num_of_thread] ) <0)
        {
            perror("Could not create thread!");
            return 1;
        }
        num_of_thread++;//increase the index of threads and args.
      }
    }

    //block main thread until all the treads come to an end.
    for (i = 0; i < (FirstRow*SecondColumn); i++)
    {
        pthread_join(threads[i], NULL);

    }
    
    //measure elapsed time .
    /*
    end = clock();

    micros = end - start;
    millis = micros / 1000000.0;
    printf("\nFinished in %f seconds.\n\n", millis);
    */
    /////////////////////
    //print calculation result
    printf("Product of entered matrices: Row= %d,Column= %d\n",FirstRow,SecondColumn);
 
    print_matrix(FirstRow,SecondColumn,Multiplication);

    printf("\n");

    

    //write the result to an output file.
    fp = fopen( "output_matrix.txt", "w" ); // Open file for writing

    fprintf(fp, "%d %d\n",FirstRow,SecondColumn );
    for (Row = 0; Row < FirstRow; Row++)
    {       for (Column = 0; Column < SecondColumn; Column++)
                    fprintf(fp,"%d ", Multiplication[Row][Column]);
                fprintf(fp, "\n" );
    }       
    
   
    fclose(fp);
    //end writing the result ot an output file.
    








    free_matrix( TotalRow, Matrix);/* Free the matrix */
    free_matrix( FirstRow, Multiplication);/* Free the result matrix */
   
    FirstMatrix=NULL;//point FirstMatrix pointer to NULL to disable the pointer
    SecondMatrix=NULL;//point SecondMatrix pointer to NULL to disable the pointer
    Matrix=NULL;//point Matrix pointer to NULL to disable the pointer
    Multiplication=NULL;//point Multiplication pointer to NULL to disable the pointer
    return 0;
}