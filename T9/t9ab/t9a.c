#include <signal.h>
#include "maleta.h"

int volatile sign;
void ring(){
  sign=0;
}

double llenarMaleta(double w[], double v[], int z[], int n, double maxW, int k) {
  double best=-1;
  sign=1;
  void(*hdlr)() = signal(SIGINT, ring);
  while (k-- && sign){
    int x[n];
    double sumW= 0, sumV= 0;
    for (int i=0; i<n; i++) {
      x[i]= (random0or1() && sumW+w[i]<=maxW) ? 1 : 0;
      if (x[i]==1){
        sumW += w[i];
        sumV += v[i];
      } 
    }
    if (sumV>best){
      best= sumV;
      for(int i=0; i<n; i++){
        z[i]= x[i];
      }
    }
  }
  signal(SIGINT, hdlr);
  return best;
}

