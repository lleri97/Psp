
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#define SIZE 512
/*
int main(){
	/*	
	int id_proc = getpid();
	int id_p = getppid();
	int id_usu = getuid();
	
	printf ("Proceso: %d\n", id_proc);
	printf ("Padre: %d\n", id_p);
	printf ("Usuario: %d\n", id_usu);
	
	int pid;
	pid = fork();
	if(pid==0){
		//proceso hijo
		printf("Soy el hijo %d, del padre %d\n",getpid(),getppid());
		kill(getppid(),SIGKILL);
	}else{
		//proceso padre
		printf("Soy el padre %d, mi hijo %d\n",getpid(),pid);
		pause();
		
	}
	//ambos
	printf("Voy a acabar %d\n", getpid());
	


}
}
	*/
	int main(int argc, char *argv[])
{
    pid_t pid1, pid2,readbytes;
    int status1, status2;
    int ph[2],hn[2];
    pipe(ph);
    pipe(hn);
    char buffer[SIZE];
 
    if ( (pid1=fork()) == 0 ){ /* hijo (1a generacion) = padre */
        if ( (pid2=fork()) == 0 )
        { /* hijo (2a generacion)  = nieto */
            printf("Soy el nieto (%d, hijo de %d)\n",getpid(), getppid());
            close(hn[1]);
				read( hn[0], buffer,SIZE);
				
					write(hn[1],buffer,readbytes);
				
				close(hn[0]);
				
				
        }
        else
        { /* padre (2a generacion) = padre */
			printf("Soy el padre (%d, hijo de %d)\n",getpid(), getppid());
            wait(&status2);
            close(ph[1]);//Cerramos el lado de escritura
            read(ph[0],buffer, SIZE);
			
			
            
            close(ph[0]);
            close(hn[0]);
				write(hn[1],buffer,strlen(buffer));
			close(hn[0]);
            
        }
    }
    else
    { /* padre (1a generacion) = abuelo */
		printf("Soy el abuelo (%d, hijo de %d)\n", getpid(),getppid());
        wait(&status1);
        close(ph[0]);//Cerramos el lado de lectura
		strcpy(buffer, "Soy el padre hablando por el tubo\0");
		write(ph[1], buffer,strlen(buffer));
		close(ph[1]);
        
    }
    
 
    return 0;
}


	


