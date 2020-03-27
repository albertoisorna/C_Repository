/* Monitor para la practica 3 de INFI (11/2016) */

#define _POSIX_C_SOURCE 200112L

/* Cabeceras del sistema */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* Cabecera de la practica */

#include "practica3.h"
#include "monitor.h"

/* Mutex y variables de condicion */

pthread_mutex_t  mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  vc_entrada_disponible = PTHREAD_COND_INITIALIZER;
pthread_cond_t  vc_salida_disponible = PTHREAD_COND_INITIALIZER;


/* Estructura para las posiciones de almacenamiento de entrada o salida */

    struct almac {
        int contenido;     /* Numero de piezas que contiene */
        int reserva;        /* Numero de reservas de piezas o lugares para piezas */
        elemento_t id;    /* Id del grafico del almacen */
    };         

/* Almacenes de entrada */

struct almac tabla_alm_in[N_ALM_IN];   /* Tabla de almacenes de entrada */
int npiezas_disp;                                      /* Numero de piezas existentes a la entrada y no reservadas */

/* Almacen de salida */

struct almac alm_out;				/* Almacen de salida */

/* Tabla de mutex para acceso a pasillos */

pthread_mutex_t mut_pasillo[N_PASILLOS];

/* Identificador de graficos */

id_grafi_t  idgr;

/* Funciones de acceso al monitor */

/* Inicializacion del monitor */

void ini_monitor(id_grafi_t id) {
     int i;
     idgr = id;
         
     for(i=0; i<N_ALM_IN; i++) {
         tabla_alm_in[i].reserva = 0;         
         tabla_alm_in[i].contenido = 0;
         tabla_alm_in[i].id = crear_almacen_id(FILA_ALM_IN+i, COL_ALM_IN, idgr);               
     poner_cont(tabla_alm_in[i].id, tabla_alm_in[i].contenido);
     }
     npiezas_disp = 0;
 
     alm_out.reserva = 0;         
     alm_out.contenido = 0;
     alm_out.id = crear_almacen_id(FILA_ALM_OUT, COL_ALM_OUT, idgr);               
      
     for(i=0; i<N_PASILLOS; i++) 
        pthread_mutex_init(&mut_pasillo[i], NULL);
}

/* Pedir pasillo */

void pedir_pasillo(int npasillo) {	
     pthread_mutex_lock(&mut_pasillo[npasillo]);
}                                     

/* Liberar pasillo  */

void liberar_pasillo(int npasillo) {
     pthread_mutex_unlock(&mut_pasillo[npasillo]);
}                                     

/* Incrementar contenido del almacen de entrada */
/* Debe utilizarse para ejecutar la pulsacion de teclado correspondiente */
/*  nalm: Numero del almacen que ha de incrementarse */
/*  El contenido del almacen no puede superar 1 */

void inc_alm_in(int nalm) {
     pthread_mutex_lock(&mut);
     if (tabla_alm_in[nalm].contenido > 0)
	 tabla_alm_in[nalm].contenido = 1;
     else {
	tabla_alm_in[nalm].contenido++;
     	pthread_cond_signal(&vc_entrada_disponible);
	npiezas_disp++;}
     poner_cont(tabla_alm_in[nalm].id, tabla_alm_in[nalm].contenido);
     pthread_mutex_unlock(&mut);
}

/* Decrementar contenido del unico almacen de salida */
/* Debe utilizarse para ejecutar la pulsacion de teclado correspondiente */
/* El contenido no puede ser menor que cero */

void dec_alm_out(void) {
     pthread_mutex_lock(&mut);
     if (alm_out.contenido==0)
     alm_out.contenido = 0;
     else {
     alm_out.contenido = alm_out.contenido - 1;
     pthread_cond_signal(&vc_salida_disponible);
     }
     poner_cont(alm_out.id, alm_out.contenido);
     pthread_mutex_unlock(&mut);
}

/* Reservar un lugar para la pieza si es posible */
/* NO ESPERA a que haya lugar disponible */

/* nveh: Vehiculo que intenta descargar */
/* Devuelve 0 si no ha sido posible reservar, y 1 si se ha podido
    realizar la reserva y por tanto se puede descargar */

int reservar_salida(int nveh) {
     int res;
     int nlugares, nreservas;

     pthread_mutex_lock(&mut);
     if(alm_out.contenido + alm_out.reserva < MAX_PIEZAS_OUT) {
       alm_out.reserva++;
       res = 1;
     } 
     else {
        res = 0;
     }

     nlugares = MAX_PIEZAS_OUT - alm_out.contenido;
     nreservas = alm_out.reserva;

     pthread_mutex_unlock(&mut);    

     printf("reservar_salida: %d lugares disponibles, %d reservados\n", nlugares, nreservas);     
     
     if(res) printf("reservar_salida: reservado lugar para veh. %d\n", nveh);
     else    printf("reservar_salida: No hay lugar disponible para veh. %d\n", nveh);
     return res;
}

/* Esperar hasta haber reservado un lugar en el almacen de salida */
/* Utilizada por el vehiculo cuando llega cargado al aparcamiento */
/* nveh: Vehiculo que ha de esperar */
/* Debe devolver 0 (lugar disponible)  */ 
/* Si devolviese -1 el vehiculo desaparece y su hilo acaba */
/* Si devuelve cualquier otra cosa, el vehiculo se bloquea */

int esperar_salida_disponible(int nveh) {
     int result = 1;
     int nlugares, nreservas;

     printf("esperar_salida_disponible: Vehiculo %d esperando salida disponible\n", nveh);
     pthread_mutex_lock(&mut);
     
     while (alm_out.contenido + alm_out.reserva == MAX_PIEZAS_OUT){
     	pthread_cond_wait(&vc_salida_disponible,&mut); }
     alm_out.reserva++;
     result = 0;

     nlugares = MAX_PIEZAS_OUT - alm_out.contenido;
     nreservas = alm_out.reserva;
     
     pthread_mutex_unlock(&mut);

     printf("esperar_salida_disponible: %d lugares disponibles, %d reservados\n", nlugares, nreservas);
      
     return result;
}

/* Esperar a que exista una pieza no reservada en algun almacen de entrada */
/* Utilizada por el vehiculo cuando esta vacio en el aparcamiento */
/*  nveh: Vehiculo que ha de esperar */
/* Debe devolver un numero valido de almacen en el que el vehiculo deberia cargar */
/* Si devuelve -1 el vehiculo desaparece y su hilo acaba */
/* Si devuelve cualquier otra cosa, el vehiculo se bloquea */

int esperar_entrada_disponible(int nveh) {
   int i;
   int result = N_ALM_IN;
   struct almac *palm;
   int npiezas = 0;
   int nreservas = 0;

    pthread_mutex_lock(&mut);
    while (npiezas_disp==0){
          pthread_cond_wait(&vc_entrada_disponible,&mut);}

    for(i=0, palm = tabla_alm_in; 
          i<N_ALM_IN && result == N_ALM_IN; 
          i++, palm++) {
          if(palm->contenido !=0 && palm->reserva == 0)  {
             palm->reserva = 1;
             result = i;
             npiezas_disp--;

             if(palm->contenido != 0) npiezas++;
             if(palm->reserva != 0) nreservas++;

          }
     }  
     pthread_mutex_unlock(&mut);

     printf("esperar_entrada_disponible: Quedan %d piezas, %d reservadas\n", npiezas, nreservas);
     if(result == N_ALM_IN) 
            printf("esperar_entrada_disponible: Error, no parece haber pieza disponible, devuelvo %d al vehiculo %d\n", 
                      result, nveh);
     else printf("esperar_entrada_disponible: Pieza de almacen %d para vehiculo %d\n", 
                       result, nveh);
     return result;
}

/* Cargar de almacen de entrada */
/* Utilizada por el vehiculo cuando esta ante el almacen de entrada */
/* nveh: Numero de vehiculo que carga */

void cargar(int nalm, int nveh) {
     
     pthread_mutex_lock(&mut);
     tabla_alm_in[nalm].contenido -= 1;
     tabla_alm_in[nalm].reserva -= 1;
     poner_cont(tabla_alm_in[nalm].id, tabla_alm_in[nalm].contenido);
     pthread_mutex_unlock(&mut);
     
     printf("cargar: El vehiculo %d carga de la posicion %d\n", nveh, nalm);
}

/* Descargar de almacen de entrada */
/* Utilizada por el vehiculo cuando esta ante el almacen de salida */
/* nveh: Numero de vehiculo que carga */

void descargar(int nveh) {

     pthread_mutex_lock(&mut);
     alm_out.contenido++;
     alm_out.reserva--;
     poner_cont(alm_out.id, alm_out.contenido);
     pthread_mutex_unlock(&mut);    

     printf("descargar: El vehiculo %d descarga en el almacen de salida\n", nveh);
}

