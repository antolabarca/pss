#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "maleta.h"

double llenarMaletaSec(double w[], double v[], int z[], int n, double maxW, int k);

int leer(int fd, void *buf, int n){
	if(n==0){
		return 0;
	}
	do{
		int rc=read(fd, buf, n);
		if (rc<=0){
			return 1;// fracaso: error o fin del archivo/pipe/socket
		}
		n-=rc;  // descontamos los bytes leídos
		buf=(char*)buf + rc; // avanzamos el buffer
	}
	while(n>0); // mientras no leamos todo lo que esperamos
	return 0;      // exito
}

double llenarMaleta(double w[], double v[], int z[], int n, double maxW, int k){
	pid_t pids[8];
	int infds[8];
	int step = (k+8)/8;

	for(int p=0;p<8;p++){
		int fds[2];
		pipe(fds);
		pids[p]=fork();
		if(pids[p] == 0){ //proceso hijo
			close(fds[0]);
			srandom(getUSecsOfDay()*getpid());
			double a = llenarMaletaSec(w, v, z, n, maxW, step);
			double ans[n+1];
			ans[0]=a;
			for (int i = 1; i <= n; ++i){
				ans[i]=z[i-1];
			}
			write(fds[1], &ans, (n+1)*sizeof(double));
			exit(0);
		}
		else {//proceso  padre
			close(fds[1]);
			infds[p] = fds[0];
		}
	}

	double best = -1;	
	for(int p=0; p<8; p++){
		double ans[n+1]; 
		waitpid(pids[p], NULL, 0);
		leer(infds[p],&ans,(n+1)*sizeof(double)); // recibo  la  info del  hijo
		close(infds[p]);
		if(ans[0] > best){
			best=ans[0];
			for (int i=0; i<n; ++i) {
				z[i]=ans[i+1];
			}
		}
	}
	return  best;
}
