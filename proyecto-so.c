


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
 
//********************************************************************** 


//Variables globales

char solicitud[255]; //Almacena la solcitud del usuario
float dificultad; //Guarda la dificultad actual del problema

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
     else if (pid == 0){
          //Hijo
          printf("Hi I'm Mr Meeseeks! Look at Meeeee. (%d, %d, %d, %d)\n", getpid(), getppid(), 1, 1);     	
     }
}


//Recibe la solicitud del usuario y la almacena en una variable global
void crearSolicitud(){
     printf("Escriba su solicitud a Mr. Meeseeks: ");
     scanf(" %[^\n]s",solicitud);
     printf("%s \n", solicitud);
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

     box();


     return 0;
}

//**********************************************************************
