


/**********************************************************************
 * Instituto Tecnologico de Costa Rica - Sede Central (Cartago)       *
 * Escuela de Ingenieria en Computacion                               *
 * Curso: Principios de Sistemas Operativos			      *
 * 								      *
 * Proyecto: Mr. Meeseeks					      *
 * Prof. Esteban Arias					   	      *
 *								      *
 * Autores: Andres Arriaga y Michael Perez			      *
 *							Octubre, 2018 *
 **********************************************************************/



//Librerias a importar

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>

 
//********************************************************************** 


//Variables globales

char solicitud[255]; //Almacena la solcitud del usuario
float dificultad; //Guarda la dificultad actual del problema
float tiempoEspera; //Almacena el tiempo de espera antes de decidir si resolver o no un problema

static int *nivel; // Variable global que almacena el nivel de un Mr. Meeseek
static int *cantidadMeeseeks; //Contador de procesos
static int *ready;

//**********************************************************************


//Funciones

void resolverSolicitud();
void calcularTiempoEspera();
void crearMeeseeks();



// crea meeseeks dependiendo de la dificultad
void resolver(){

    if(*ready)
	exit(0);
    dificultad += *cantidadMeeseeks/2;
    pid_t pid2;
    //calcularTiempoEspera();
    //sleep(tiempoEspera);

     	if(dificultad > 85.0){
     	//Solucion segura
          printf("I'm Mr Meeseeks! Look at Meeeee. The job %s is done! (%d, %d, %d, %d)\n", solicitud, getpid(), getppid(), *nivel, 1);
	*ready = 1;
	exit(0);
     	}
     	else if(dificultad > 45.0){
     	//Solucion casi segura
          
	  *nivel += 1;
	  pid2 = fork();
	  if(pid2 == 0){
	       printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1);	         
	       *cantidadMeeseeks += 1;
	       resolver();	  
	       exit(0);
	  }
	  else{

		while(wait(NULL) > 0){}
		return;
	  }

     	}
     	else if(dificultad > 0.0){
     	//Solucion dificil
	 
          *nivel += 1;
	  pid2 = fork();
	  	if(pid2 == 0){
			printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1);	  		*cantidadMeeseeks += 1;	
			resolver();
			exit(0);
			
				
		}

                else{
			pid2 = fork();
			if(pid2 == 0){
				printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1);	  		*cantidadMeeseeks += 1;	
				resolver();
				exit(0);
			}
     			else{
				while(wait(NULL) > 0){}
				return;			
			}
			while(wait(NULL) > 0){}
				return;	
			
	  	}
     	}
     	else{
     	//Solucion imposible

     	}
}


// 
void resolverSolicitud(){
     pid_t pid;

     pid = fork();



     if(pid < 0){
           /*Error*/
	  fprintf(stderr, "Fork Failed");
     }
     else if(pid != 0){
          //Padre
     	*nivel += 1;
	  while(wait(NULL) > 0){
		
	  }
          return;
 
     }
     else if(pid == 0){
	  //Hijo

     	printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1);	  
     	resolver();
	return;
     } 
     
}



//Random para el tiempo de espera
void calcularTiempoEspera(){
    srand ( time(NULL) );
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    tiempoEspera =  0.5 + scale * ( 5.0 - 0.5 );      /* [min, max] */    
}


//	
void solicitarDificultad(){
     int tipoSolicitud;
     printf("Desea que la dificultad sea automatica? (1/0): ");
     scanf("%d", &tipoSolicitud);
     if(tipoSolicitud){
          srand ( time(NULL) );
          dificultad =  rand () % (100-0+1) + 0;

     }
     else{
          printf("Digite el nivel de dificultad [0-100]: ");
          scanf("%f", &dificultad);
     }

}

//Crea un proceso hijo denominado Mr. Meeseeks
void crearMeeseeks(){
     pid_t pid;
     pid = fork();
     if(pid < 0){
          /*Error*/
	  fprintf(stderr, "Fork Failed");
     }
     else if(pid != 0){
     	  // Padre
     	  *nivel += 1; // Incrementa variable global
     	  //printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1);
     	  while(wait(NULL) > 0){

            
          }
	  return;
          // espera a que el hijo termine, esto para no interrumpir el proceso de impresion.
          
     }
     else if (pid == 0){
          // Hijo
     	  printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1); 
          //exit(EXIT_SUCCESS); // dice que ha terminado 	
	  resolverSolicitud();
     	  return;// tambien se puede usar para decir que ha terminado
     }
}


//Recibe la solicitud del usuario y la almacena en una variable global
void crearSolicitud(){
     printf("Escriba su solicitud a Mr. Meeseeks: ");
     scanf(" %[^\n]s",solicitud);
     solicitarDificultad();
     resolverSolicitud();
     
}

//Funcion que inicia el programa
void box(){
     printf("Bienvenido: Ahora usted tiene la caja de Meeseeks. \n");
     int presionar;
     printf("Desea presionar el boton? (1/0): ");
     scanf("%d", &presionar);
     if(presionar){
	crearSolicitud();
     }
}


//**********************************************************************


//Main

int main(){
	 
	 nivel = mmap(NULL, sizeof *nivel, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
         cantidadMeeseeks = mmap(NULL, sizeof *cantidadMeeseeks, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	ready = mmap(NULL, sizeof *ready, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	 // con esto se hace para hacerlo global entre procesos
	 *nivel = 0;
         *cantidadMeeseeks = 0;	
	 *ready = 0;
	 // nivel es 0, si se crea un Mr. Meeseek este sera nivel 1.
     box();


     return 0;
}

//**********************************************************************
// gcc proyecto-so.c -o box
