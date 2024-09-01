// Ejemplo de QuickSort
#include <stdlib.h>
#include <stdio.h>

//comparar
int compare (const int * a, const int * b) //what is it returning?
{
   return ( *(int*)a - *(int*)b ); //What is a and b?
}

void par_qsort(int *data, int lo, int hi) //}, int (*compare)(const int *, const int*))
{
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = data[(hi + lo)/2];

  while(l <= h){
    while((data[l] - p) < 0) l++;
    while((data[h] - p) > 0) h--;
    if(l<=h){
      //swap
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      l++; h--;
    }
  }
  //recursive call
  par_qsort(data, lo, h);
  par_qsort(data, l, hi);
}


int main (int argc, char *argv[]){
  if (argc == 1)
    {
      printf("Usage: quickSort arrayLen #tasks\n");
      exit (1);
    }
  int N = atoi(argv[1]);
  int T = atoi(argv[2]);

  //int *x;
  int x[N];
  int j;

  //---- Asignación de memoria para el vector x ----
  ///if ( (x=(int *)malloc(N*sizeof(int))) == NULL )
   ///printf("memory allocation for x");

  //---- Inicialización con elementos aleatorios entre 1-N/2
  //TODO aca leer de archivo CSV, generando random para ejemplo
  printf("Generando lista random con %d elementos\n", N);
  int posibles_elementos = N/2;
  for (j=0; j<N; j++)
    x[j] = rand()%(posibles_elementos)+1;

  par_qsort(x, 0, N-1);

  printf("Primeros Elementos: %d, %d, %d\n", x[0], x[1], x[2]);
  printf("Medios Elementos: %d, %d, %d\n", x[N/4], x[N/4 +1], x[N/4 +2]);
  printf("Ultimos Elementos: %d, %d, %d\n", x[N-3], x[N-2], x[N-1]);
  return 0;
}
