


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

 
//********************************************************************** 


//Variables globales

char solicitud[255]; //Almacena la solcitud del usuario
float dificultad; //Guarda la dificultad actual del problema

static int *nivel; // Variable global que almacena el nivel de un Mr. Meeseek

//**********************************************************************


//Funciones


//	
void solicitarDificultad(){
    
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
     	  printf("Hi I'm Mr Meeseeks Dad! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1);
     	  wait(NULL);// espera a que el hijo termine, esto para no interrumpir el proceso de impresion.
     }
     else if (pid == 0){
          //Hijo
     	  *nivel += 1; // incrementa variable global
          printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), *nivel, 1); 
          //exit(EXIT_SUCCESS); // dice que ha terminado 	
     	  return;// tambien se puede usar para decir que ha terminado
     }
}


//Recibe la solicitud del usuario y la almacena en una variable global
void crearSolicitud(){
     printf("Escriba su solicitud a Mr. Meeseeks: ");
     scanf(" %[^\n]s",solicitud);
     solicitarDificultad();
     crearMeeseeks();
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
	 // con esto se hace para hacerlo global entre procesos
	 *nivel = 0;
	 // nivel es 0, si se crea un Mr. Meeseek este sera nivel 1.
     box();


     return 0;
}

//**********************************************************************
// gcc proyecto-so.c -o box
