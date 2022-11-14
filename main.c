#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//-------------------------------------------------------------------------
double func(double x) {
  return (0.25*pow((x-25),2)+pow((x+25),3)/100+1);
}
//-------------------------------------------------------------------------
double half_dev(double a, double b, double eps, unsigned int Deb_metod, unsigned int Iter_num) {
  double c = 0;
  unsigned int times=0;
  int var;
  while ((b - a) >= eps)
  {
    c = (a + b) / 2;
    if (func(c) == 0) {
      break;
    }
    else if (func(c) * func(a) < 0) {
      b = c;
    }
    else {
      a= c;
    }
    printf("root  = %.15lf\n", c);
    if(Deb_metod==2)
    {
      times ++;
      if (times >= Iter_num)
      {
        times = 0;
        var=TooManyIter();
        if(var==2)
        {
          Deb_metod = 1;
        }
        else if(var==3)
        {
          break;
        }
      }
    }
  }
  c = (a + b) / 2;
  return c;
}
//-------------------------------------------------------------------------
double method_chord(int a, int b, double eps, unsigned int Deb_metod, unsigned int Iter_num) {
  double c = 0;
  double var;
  unsigned int times=0;
  while (abs(c - b) > eps)
  {
    var=c;
    c = b - func(b) * (a - b) / (func(a) - func(b));
    a = b;
    b = var;
    printf("root  = %.15lf\n",fabs(c));
    if(Deb_metod==2)
    {
      times ++;
      if (times >= Iter_num)
      {
        times = 0;
        int var;
        var=TooManyIter();
        if(var==2)
        {
          Deb_metod = 1;
        }
        else if(var==3)
        {
          break;
        }
      }
    }
  }
  return fabs(c);
}
//-------------------------------------------------------------------------
int TooManyIter() {
  printf("\nThe number of iterations is exceeded.\n");
  printf("\n 1 - continue with the same number of iterations");
  printf("\n 2 - run the program until roots of the equation are found");
  printf("\n 3 - stop the program and display the result");
  printf("\n Choose what to do:");
  int WhatToDo;
  scanf("%d", &WhatToDo);
  while (WhatToDo <1 || WhatToDo >3) {
    printf("\n Error, please try again: ");
    scanf("%d", &WhatToDo);
  }
  return WhatToDo;
}
//-------------------------------------------------------------------------
int main() {
  double startT;
  int Metod_Used;
  int a,b;
  double epsilon;
  unsigned int Debug_metod;
  unsigned int iter_number=0;
  //-------------------------------------------------------------------------
  printf("Chose metod: \n1 - Half devision method \n2 - Chord method\nMetod:");
  scanf("%d", &Metod_Used);
  while (Metod_Used != 1 && Metod_Used != 2) {
    printf("\nError, please try again: ");
    scanf("%d", &Metod_Used);
  }
  printf("\n1-Debug;  \n2-Debug with parametrs;\nEnter: ");
  scanf("%d", &Debug_metod);
  while (Debug_metod != 1 &&Debug_metod != 2) {
    printf("\nError, please try again:");
    scanf("%d", &Debug_metod);
  }
  if (Debug_metod == 2) {
    printf("\nNumber of iterations:");
    scanf("%d", &iter_number);
  }
  printf("\nEnter a:");
  scanf("%d",&a);
  printf("\nEnter b:");
  scanf("%d",&b);
  printf("\nEnter epsilon:");
  scanf("%d",&epsilon);
  system("cls");
  //-------------------------------------------------------------------------
  startT = clock();
  if (Metod_Used == 1) {
    printf("\nHalf devision method= %.20lf", half_dev(a, b, epsilon, Debug_metod, iter_number));
  } else {
    printf("\nMethod_chord = %lf", method_chord(a, b, epsilon, Debug_metod, iter_number));
  }
  printf("\nTime spend on calculations: %f Sec\n", clock() - startT);
  return 0;
}
