#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "common.h"


void tweakSolution( memberType *member )
{
  int temp, x, y;

  x = getRand(MAX_LENGTH);
  do {
    y = getRand(MAX_LENGTH);
  } while (x == y);

  temp = member->solution[x];
  member->solution[x] = member->solution[y];
  member->solution[y] = temp;
}


void initializeSolution( memberType *member )
{
  int i;

  for (i = 0 ; i < MAX_LENGTH ; i++) {
    member->solution[i] = i;
  }

  for (i = 0 ; i < MAX_LENGTH ; i++) {
    tweakSolution( member );
  }

}

void emitSolution( memberType *member )
{
  char board[MAX_LENGTH][MAX_LENGTH];
  int x, y;

  bzero( (void *)board, MAX_LENGTH * MAX_LENGTH );

  for (x = 0 ; x < MAX_LENGTH ; x++) {
    board[x][member->solution[x]] = 'Q';
  }

  printf("board:\n");
  for (y = 0 ; y < MAX_LENGTH ; y++) {
    for (x = 0 ; x < MAX_LENGTH ; x++) {
      if (board[x][y] == 'Q') printf("Q ");
      else printf(". ");
    }
    printf("\n");
  }
  printf("\n\n");
}

void computeEnergy( memberType *member )
{
  int  i, j, x, y, tempx, tempy;
  char board[MAX_LENGTH][MAX_LENGTH];
  int conflicts;
  const int dx[4] = {-1,  1, -1,  1};
  const int dy[4] = {-1,  1,  1, -1};

  bzero( (void *)board, MAX_LENGTH * MAX_LENGTH );

  for (i = 0 ; i < MAX_LENGTH ; i++) {
    board[i][member->solution[i]] = 'Q';
  }

  conflicts = 0;

  for (i = 0 ; i < MAX_LENGTH ; i++) {

    x = i; y = member->solution[i];
    for (j = 0 ; j < 4 ; j++) {

      tempx = x ; tempy = y;
      while(1) {
        tempx += dx[j]; tempy += dy[j];
        if ((tempx < 0) || (tempx >= MAX_LENGTH) ||
               (tempy < 0) || (tempy >= MAX_LENGTH)) break;
        if (board[tempx][tempy] == 'Q') conflicts++;
      }

    }

  }

  member->energy = (float)conflicts;
}




void copySolution( memberType *dest, memberType *src )
{
  int i;

  for (i = 0 ; i < MAX_LENGTH ; i++) {
    dest->solution[i] = src->solution[i];
  }
  dest->energy = src->energy;
}




 int main()
 {
     int  timer=0, step, solution=0, useNew, accepted;
     float temperature, final_temperature, alpha;
     int steps_per_change, n_queens;

     memberType current, working, best;
     FILE *fp;

     printf("Введите количество ферзей (N > 20): ");
     scanf("%d", &n_queens);
     if (n_queens <= 20) {
         printf("N должно быть больше 20!\n");
         return 1;
     }

     printf("Начальная температура: ");
     scanf("%f", &temperature);
     printf("Конечная температура: ");
     scanf("%f", &final_temperature);
     printf("Коэффициент охлаждения (alpha, например 0.99): ");
     scanf("%f", &alpha);
     printf("Шагов на одну температуру: ");
     scanf("%d", &steps_per_change);

     if (n_queens > MAX_LENGTH) {
         printf("N превышает MAX_LENGTH (%d). Измените common.h и перекомпилируйте.\n", MAX_LENGTH);
         return 1;
     }

     fp = fopen("stats.txt", "w");
     srand(time(NULL));

     initializeSolution( &current );
     computeEnergy( &current );
     best.energy = 1000000.0;

     copySolution( &working, &current);

     while (temperature > final_temperature) {

         printf("Temperature : %f\n", temperature);
         accepted = 0;

         for (step = 0 ; step < steps_per_change ; step++) {

             useNew = 0;
             tweakSolution( &working );
             computeEnergy( &working );

             if (working.energy <= current.energy) {
                 useNew = 1;
             } else {
                 float test = getSRand();
                 float delta = working.energy - current.energy;
                 float calc = exp(-delta / temperature);
                 if (calc > test) {
                     accepted++;
                     useNew = 1;
                 }
             }

             if (useNew) {
                 copySolution( &current, &working );
                 if (current.energy < best.energy) {
                     copySolution( &best, &current );
                     solution = 1;
                     printf(">>> Новое лучшее решение: энергия = %.0f\n", best.energy);
                 }
             } else {
                 copySolution( &working, &current);
             }
         }

         fprintf(fp, "%d %f %f %d\n", timer++, temperature, best.energy, accepted);
         printf("Лучшая энергия = %f, принято плохих решений = %d\n", best.energy, accepted);
         temperature *= alpha;

         if (best.energy == 0) {
             printf("🎉 Найдено оптимальное решение!\n");
             break;
         }
     }

     fclose(fp);

     if (solution) {
         emitSolution( &best );
     } else {
         printf("Решение не найдено за отведённое время.\n");
     }

     return 0;
}
