/* Practica 3 INFI (11/2016) */

#define _POSIX_C_SOURCE 200112L

/* Cabeceras del sistema */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

/* Cabecera de graficos */

#include "api_grafi.h"

/* Cabecera de la practica */

#include "practica3.h"
#include "monitor.h"

/* Mapa */

#define P PARED                    /* Definido en api_grafi.h */
#define C PASILLO                  /*   "              "           "     */

int mapa[ALTO][ANCHO] = 
                  {
                    {P, P, P, P, P, P, P, P, P, P, P, P},
                    {P, P, P, C, C, C, C, C, P, P, C, P},
                    {P, P, C, C, C, C, C, C, C, C, C, P},
                    {C, C, C, P, P, P, P, P, C, P, C, P},
                    {C, C, C, P, P, P, P, P, C, C, C, P},
                    {C, C, C, P, P, P, P, P, C, P, P, P},
                    {C, C, C, P, P, P, P, P, C, P, P, P},
                    {P, P, C, C, C, C, C, C, C, P, P, P},
                    {P, P, P, P, P, P, P, P, P, P, P, P},
                  };

/* Manejadores */

void mcomun(int sig, siginfo_t *info, void *p)
{
     printf("mcomun: Entra indebidamente manejador para senal SIGRTMIN+%d\n", 
        sig-SIGRTMIN);
}

/* Funcion para inicializar los graficos */

id_grafi_t inic_graficos(void);
                                     
/* main */

int main(int argc, char **argv) {

   pthread_t tveh[N_VEH];
   struct arg_veh *parg;
   id_grafi_t idgr;
   siginfo_t info;
   sigset_t spuls;
   struct sigaction accion;

   int npuls;
   int sig;
   int i;               

   /* Inicializar tratamiento de senales */

   accion.sa_flags = SA_SIGINFO;
   sigemptyset(&accion.sa_mask);
   accion.sa_sigaction = mcomun;

   sigaction(SIG_PULS_IN, &accion, NULL);
   sigaction(SIG_PULS_OUT, &accion, NULL);

   sigemptyset(&spuls);
   sigaddset(&spuls, SIG_PULS_IN);
   sigaddset(&spuls, SIG_PULS_OUT);
   pthread_sigmask(SIG_BLOCK, &spuls, NULL);

    /* Crear graficos */

    idgr = inic_graficos();

    /* Inicializar monitor */
    
    ini_monitor(idgr);

    /* Crear hilos de vehiculo */
    
    for(i=0; i<N_VEH; i++) {
           printf("pr3: Creando veh %d\n", i);
          parg = malloc(sizeof(struct arg_veh));
          parg->fila = FILA_APARCAMIENTO;
          parg->col = COL_APARCAMIENTO + i;
          parg->id = i;
          parg->idgr = idgr;
	  pthread_create(&tveh[i],NULL,hilo_veh,parg);
    }

   /* Bucle de atencion de senales de pulsadores */

   printf("pr3: comenzando bucle\n");   
   
   while(1) {
  
       printf("pr3: Esperando alguna senal de pulsador\n");
       sig = sigwaitinfo(&spuls, &info);
       npuls = info.si_value.sival_int;
       if(sig == SIG_PULS_IN) {
            printf("pr3: Incrementando almacen de carga %d\n", npuls);                
            inc_alm_in(npuls);
       } else 
       if(sig == SIG_PULS_OUT) {
            printf("pr3: decrementando almacen de descarga\n");                
            dec_alm_out();
       } else 
       if(sig == -1) {
            printf("pr3: Error en sigwaitinfo: %s\n", strerror(errno));
       } else {
            printf("pr3: Recibida senal inesperada SIGRTMIN+%d\n", sig-SIGRTMIN);                
       }
   }
   
   /* Aqui no llega */
      
   cerrar_graficos(idgr, 1);
   printf("pr3: acabando\n");
   return 0;
}

/* Crear graficos */
/* NO ES NECESARIO MODIFICARLA */

id_grafi_t inic_graficos(void) {

   id_grafi_t  idgr;
   int i;
   char nombre[20];
            
   /* Crear y abrir graficos */

   printf("pr3: arrancando graficos\n");
   idgr = abrir_graficos("Practica 3", 1);
   if(idgr != GRAFI_FALLO_CREACION) printf("pr3: Graficos creados\n");
   else {
      printf("pr3: No puede crearse la ventana grafica\n");
      exit(1);
   }
   
   /* Cambiar escala y fondo */
        
   cambia_escala_id(ESCALA_DIB, idgr); 
   crear_fondo_id((int *)mapa, ANCHO, ALTO, idgr);

   /* Crear pulsadores */
   
   for(i=0; i<N_ALM_IN; i++) {
      sprintf(nombre, "IN%d", i); 
      crear_pulsador_codigo_id(FILA_PULS_IN+i, COL_PULS_IN, SIG_PULS_IN, nombre, i, idgr);
  }

  sprintf(nombre, "OUT"); 
  crear_pulsador_codigo_id(FILA_PULS_OUT, COL_PULS_OUT, SIG_PULS_OUT, nombre, 0, idgr);

   return idgr;
}

