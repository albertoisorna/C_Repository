/* Cabecera para el monitor de la practica 3 de INFI 11/16 */
/* Copyright (C) Joaquin Ferruz Melero 2016 */

#ifndef 	__MONITOR_H__
#define 	__MONITOR_H__

/* Funciones de acceso al monitor */

/* Inicializacion del monitor */
/* Hay que utilizarla antes de invocar cualquier otra */

void ini_monitor(id_grafi_t id);

/* Pedir pasillo */

void pedir_pasillo(int npasillo);

/* Liberar pasillo  */

void liberar_pasillo(int npasillo);

/* Incrementar contenido del almacen de entrada */
/* Debe utilizarse para ejecutar la pulsacion de teclado correspondiente */
/*  nalm: Numero del almacen que ha de incrementarse */
/*  El contenido del almacen no puede superar 1 */

void inc_alm_in(int nalm);

/* Decrementar contenido del unico almacen de salida */
/* Debe utilizarse para ejecutar la pulsacion de teclado correspondiente */
/* El contenido no puede ser menor que cero */

void dec_alm_out(void);


/* Reservar un lugar para la pieza si es posible */
/* NO ESPERA a que haya lugar disponible */
/* nveh: Vehiculo que intenta descargar */
/* Devuelve 0 si no ha sido posible reservar, y 1 si se ha podido
    realizar la reserva y por tanto se puede descargar */

int reservar_salida(int nveh);

/* Esperar hasta haber reservado un lugar en el almacen de salida */
/* Utilizada por el vehiculo cuando llega cargado al aparcamiento */
/* nveh: Vehiculo que ha de esperar */
/* Debe devolver 0 (lugar disponible)  */ 
/* Si devolviese -1 el vehiculo desaparece y su hilo acaba */
/* Si devuelve cualquier otra cosa, el vehiculo se bloquea */

int esperar_salida_disponible(int nveh);

/* Esperar a que exista una pieza no reservada en algun almacen de entrada */
/* Utilizada por el vehiculo cuando esta vacio en el aparcamiento */
/*  nveh: Vehiculo que ha de esperar */
/* Debe devolver un numero valido de almacen en el que el vehiculo deberia cargar */
/* Si devuelve -1 el vehiculo desaparece y su hilo acaba */
/* Si devuelve cualquier otra cosa, el vehiculo se bloquea */

int esperar_entrada_disponible(int nveh);

/* Cargar de almacen de entrada */
/* Utilizada por el vehiculo cuando esta ante el almacen de entrada */
/* nveh: Numero de vehiculo que carga */

void cargar(int nalm, int nveh);

/* Descargar de almacen de entrada */
/* Utilizada por el vehiculo cuando esta ante el almacen de salida */
/* nveh: Numero de vehiculo que carga */

void descargar(int nveh);

#endif
