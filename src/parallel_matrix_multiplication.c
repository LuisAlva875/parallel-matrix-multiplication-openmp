#include<stdio.h>    //Declaracion de librerias
#include<stdlib.h>
#include<math.h>
#include <omp.h>
#define nRengA 1000
#define nColumA 1000

#define nRengB  1000
#define nColumB  1000

int **a;
int **b;
int **c;
void crearMatrizA(int **a);        //Metodo para crear la matriz A
void crearMatrizB(int **b);
void multiSec(int **a, int **b, int **c);  //Metodo para multiplicar en secuencial las matrices
void printMatr(int **a, int ren, int col);   //Metodo para imprimir las matrices
void multiParal(int **a,int **b,int **c); //Metodo para multiplicar en paralelo las matrices
main(){
    int i;

    a=(int **)malloc(sizeof (int*)*nRengA);
    for (i=0;i<nRengA;i++){
        a[i]=(int*)malloc(sizeof(int)*nColumA);  //Creacion de la matriz  dinamica
    }
    crearMatrizA(a);              //Llenamos la matriz A con numeros aleatorios
    //printMatr(a,nRengA,nColumA);   //Se imprime el arreglo
    b=(int **)malloc(sizeof (int*)*nRengB);
    for (i=0;i<nRengB;i++){
        b[i]=(int*)malloc(sizeof(int)*nColumB);
    }
    crearMatrizB(b);
    //printMatr(b,nRengB,nColumB);
    c=(int **)malloc(sizeof (int*)*nRengB);   //Se crea una tercera matriz para guardar el resultado de la multiplicacion
    for (i=0;i<nRengB;i++){
        c[i]=(int*)malloc(sizeof(int)*nColumB);
    }



    double timeIni,timeFin, serial, paralelo,SpeedUp,Eficiencia,Toverhead;
    int procesadores;
    printf("Multiplicando matrices\n");

    timeIni=omp_get_wtime();
    multiSec(a,b,c);    //Se multiplican la matrices secuencialmente
    timeFin=omp_get_wtime();
    printf("Matriz Secuencial\n\n");
    //printMatr(c,nRengA,nColumB);    //Se imprime el resultado
    serial=timeFin-timeIni;   //Tiempo secuencial

    printf("\n");

    timeIni=omp_get_wtime();
    multiParal(a,b,c);    //Se multiplican la matrices paralelamente
    timeFin=omp_get_wtime();
    paralelo=timeFin-timeIni;      //Tiempo paralelo
    printf("Matriz paralela \n\n");
    //printMatr(c,nRengA,nColumB);    //Se imprime el resultado


    printf("El tiempo en secuencial es = %f\n", serial);
    printf("El tiempo en paralelo es = %f\n\n",paralelo );
    procesadores=omp_get_num_procs();   //Obtiene el numero de hilos
    printf("El numero de hilos es = %d\n\n", procesadores);
    SpeedUp=serial/paralelo;
    printf("SpeedUp = %f\n\n",SpeedUp);
    Eficiencia=SpeedUp/procesadores;
    printf("Eficiencia = %f\n\n",Eficiencia);
    Toverhead=(paralelo-serial)/procesadores;
    printf("Tiempo Overhead = %f\n\n", Toverhead);

}
void crearMatrizA(int **a){
    int x,i;
    printf("Matriz A de %d x %d \n\n",nRengA,nColumA);
    for (x=0;x<nRengA;x++){
        for (i=0;i<nColumA;i++){
             a[x][i]=rand()%10;

        }
    }
}
void crearMatrizB(int **b){
    int x,i;
    printf("Matriz B de %d x %d \n\n",nRengB,nColumB);
    for (x=0;x<nRengB;x++){
        for (i=0;i<nColumB;i++){
             b[x][i]=rand()%10;
        }
    }
}
void multiSec(int **a, int **b, int **c){  //Metodo para multiplicar secuencialmente
    int i,j,k,x;
    for (i=0;i<nRengA; i++){
        for (j=0;j<nColumB;j++){
                c[i][j]=0;
            for(k=0; k<nColumA;k++){
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
}
void printMatr(int **a, int ren, int col){  //Metodo para imprimir
    for (int x=0;x<ren;x++){
			for (int i=0;i<col;i++){
				printf("%d\t",a[x][i]);

			}
			printf("\n");
    }
    printf("\n");

}
void multiParal(int **a,int **b,int **c){  //Metodo que realiza la multiplicacion en paralelo
    #pragma omp parallel //
    {

        #pragma omp for  // Usa todos los hilos para realizar la multiplicacion
        for (int i=0;i<nRengA;i++){
            for (int j=0;j<nColumB;j++){
                c[i][j]=0;
                for (int k=0;k<nColumA;k++){
                    c[i][j]+=a[i][k]* b[k][j];
                }
            }

        }
    }

}

