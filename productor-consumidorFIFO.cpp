// ********************************************************************************************
// PRODUCTOR-CONSUMIDOR FIFO
// Solución al problema del productor-consumidor FIFO basada en semáforos.
// Implementado en C/C++ multihebra, usando la funcionalidad de la librería POSIX
// COMPILAR: g++ -o productor-consumidorFIFO productor-consumidorFIFO.cpp fun_tiempo.c -lrt -lpthread
//
// Autor: Pedro Fernández Bosch (pedro@pedrobosch.es)
// Distemas Concurrentes y Distribuidos
// Departamento de Lenguajes y Sistemas Informáticos, Universidad de Granada
// Última modificación: 24/02/2015
// ********************************************************************************************

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <cstdio> 
#include <cstdlib>
#include <unistd.h>                                     //Libreria para usleep(100000);
#include "fun_tiempo.h"

using namespace std ;

sem_t sem_productor; 	
sem_t sem_consumidor;
sem_t mutex_pantalla; 					// Semaforo para controlar la salida por pantalla

const int num_iter = 100; 				// Numero de iteraciones
const int tam_vector = 5;				// TamaÃ±o del vector

int vector[tam_vector];					// Vector para producir o consumir
int pos_productor = 0;
int pos_consumidor = 0;

int producir_dato() {
    static int dato = 0;
    dato++;
    return dato;
}

void consumir_dato( int dato ) {
    sem_wait(&mutex_pantalla);
    cout << "Dato consumido: " << dato << endl << flush;
    sem_post(&mutex_pantalla);
}

void * productor( void * p ) {
    for( unsigned long i = 0 ; i < num_iter ; i++ )
    {
    	int dato = producir_dato();                     // Produce un dato
    	sem_wait(&sem_productor);
	vector[pos_productor%tam_vector] = dato;	
	pos_productor++;	
	sem_post(&sem_consumidor);	

	sem_wait(&mutex_pantalla);
	cout << "Dato producido: " << dato << endl << flush;
	sem_post(&mutex_pantalla);
    }
    return NULL ;
}

void * consumidor( void * p ) {
    for( unsigned long i = 0 ; i < num_iter ; i++ )
    {
	sem_wait(&sem_consumidor);
	int dato = vector[pos_consumidor%tam_vector];   // Consume el valor generado
	pos_consumidor++;	
	sem_post(&sem_productor);

	consumir_dato(dato);                            // Consume un dato
    }
    return NULL ;
}

int main(int argc, char **argv) {
    struct timespec inicio = ahora() ;                  // Calcular tiempo de inicio	

    sem_init(&sem_productor, 0,tam_vector);
    sem_init(&sem_consumidor,0,0);
    sem_init(&mutex_pantalla,0,1);

    pthread_t hebras[2];

    pthread_create(&(hebras[0]), NULL, productor, NULL);
    pthread_create(&(hebras[1]), NULL, consumidor, NULL);

    for(unsigned i=0; i < 2; ++i)
	pthread_join(hebras[i], NULL);

    sem_destroy(&sem_productor);
    sem_destroy(&sem_consumidor);

    struct timespec fin = ahora();                      // Calcular tiempo de fin
    cout << "Tiempo empleado == " << duracion(&inicio, &fin) << " segundos" << endl; // Tiempo TOTAL
}