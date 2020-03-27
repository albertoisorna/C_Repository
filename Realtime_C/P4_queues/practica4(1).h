/* Cabecera para practica 4 de INFI-GIERM (12/2016)  */
/* Copyright (C) Joaquin Ferruz Melero 2016 */

#ifndef 	__PRACTICA4_H__
#define 	__PRACTICA4_H__

/* Acceso a interfaz grafica */

#include "api_grafi.h"

#define N_VEH                 		5		/* Numero de vehiculos */
#define N_ALM_IN               	 	4		/* Numero de posiciones de almacenamiento */
#define N_PASILLOS             	3		/* Numero de pasillos */
#define MAX_PIEZAS_OUT 		3  	/* Maximo numero de piezas en almacen de salida */

/* Pasillos (ver figura) */

enum tipo_pasillo {APARCAMIENTO, ENTRADA, SALIDA};

/* Senales de pulsadores */

#define SIG_PULS_IN 		SIGRTMIN		 /* Senal para los pulsadores de entrada */
#define SIG_PULS_OUT 	SIGRTMIN+1  /* Senal para los pulsadores de salida */

/* Mensaje de peticion (recibido por pr4) */

enum tipo_pet {
    PET_PEDIR_PASILLO,    	/* Pedir acceso al pasillo */
    PET_LIB_PASILLO,        	/* Liberar pasillo */
    PET_ESP_ENTRADA, 		/* Pedir reserva de entrada */
    PET_RES_SALIDA, 			/* Pedir reserva de salida no bloqueante */
    PET_ESP_SALIDA,			/* Pedir reserva de salida */
	PET_CARGA,					/* Cargar de almacen de entrada */
	PET_DESCARGA,			/* Descargar en almacen de salida */
	PET_INC_IN,					/* Incrementar almacen de entrada */
	PET_DEC_OUT				/* Decrementar almacen de salida */
    };

struct msg_pet {
     enum tipo_pet tipo;   	/* Tipo de peticion */
     int npasillo;					/* Numero de pasillo (solo con PET_LIB_PASILLO y 
         									PET_PEDIR_PASILLO) */
	 int nalm;						/* Numero de almacen (solo con PET_CARGA y PET_INC_IN */
     int id_veh;					/* ID del vehiculo que envia la peticion */
};

/* Mensaje de respuesta (enviado por pr4) */

struct msg_resp {
	enum tipo_pet tipo;  		/* Tipo de peticion a la que se responde */
	int nalm;						/* Numero del almacen reservado 
											(solo con PET_ESP_ENTRADA) */
	int sal_reservada;			/* Indicador de salida reservada (1) o no reservada (0) 
											(solo con PET_RES_SALIDA o PET_ESP_SALIDA) */
};

/* Dimensiones del dibujo */

#define ANCHO                    	12
#define ALTO                   	  	  9
#define ESCALA_DIB            		40

/* Filas y columnas */

#define FILA_PULS_IN 3.25      	 	/* Fila de los pulsadores de entrada */
#define COL_PULS_IN 3.25       		/* Columna del primer pulsador de entrada */
#define FILA_PULS_OUT 0.25   		/* Fila del pulsador de salida */
#define COL_PULS_OUT 10.15 		/* Columna del pulsador de salida */

#define FILA_APARCAMIENTO   	1					/* Fila de los aparcamientos */
#define COL_APARCAMIENTO   	3					/* Columna del aparcamiento 0 */
#define FILA_ALM_IN          		3					/* Fila del primer almacen de entrada */
#define COL_ALM_IN            		0					/* Col. de los almacenes de entrada */
#define FILA_ALM_OUT          	1					/* Fila del almacen de salida */
#define COL_ALM_OUT            	10					/* Col. del almacen de salida */
#define FILA_DESV_OUT			4					/* Fila de la desviacion para ir a la salida */
#define COL_DESV_OUT     		ANCHO-2 		/* Col. de la desviacion para ir a la salida */
#define FILA_VUELTA    			ALTO-2     	/* Fila del pasillo inferior para volver al aparcamiento */
#define COL_VUELTA            	ANCHO-4   	/* Col. del pasillo de la derecha para volver al aparcamiento */

#endif
