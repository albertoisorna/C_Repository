/* Funciones para utilizar la interfaz de graficos */
/* Copyright (C) Joaquin Ferruz Melero 2012 */

#ifndef __API_GRAFI_H__
#define __API_GRAFI_H__

#include <sys/types.h>


/* Precauciones al utilizar la interfaz grafica */
/* No utilizar NUNCA la senal SIGRTMAX cuando se ha abierto una interfaz  */
/* En QNX, no usar fork() despues de abrir la interfaz           */
/* En Linux, ejecutar el cliente con privilegios de administrador */


/* Resultados de funciones */

enum result_grafi_t {GRAFI_OK, GRAFI_COLISION, GRAFI_ELEM_INCORRECTO, GRAFI_FALLO_CREACION };

/* Tipos de datos */

typedef int elemento_t;   /* Identificador de vehiculo */
typedef long id_grafi_t;  /* Identificador de grafico */

/* Abrir una interfaz grafica */
/* nombre:  Nombre de la interfaz; caracteres alfanumericos;
            si es NULL, entonces se arranca la interfaz por defecto */
/* crear_servidor: 
    0: Conexion con un servidor existente; si no existe, se
       espera a que exista.
    1: Crear un servidor con ese nombre y conectar con el.Si
       existe, se cierra y se crea de nuevo */
/* Devuelve: Identificador de interfaz grafica o bien
    ERROR_FALLO_CREACION si no ha sido posible crear la ventana grafica */

id_grafi_t abrir_graficos(char *nombre, int crear_servidor);

/* cerrar una interfaz grafica */
/* id:                Identificador de la interfaz */
/* destruir_servidor:
    0: Solo desconectar
    1: Desconectar y destruir el servidor */

int cerrar_graficos(id_grafi_t id, int destruir_servidor);

/* Crear un vehiculo en la fila y columna indicadas */
/* Devuelve: identificador del vehiculo */

elemento_t crear_vehiculo_id(int finic, int cinic, id_grafi_t pgrafi); /* En interfaz pgrafi */
elemento_t crear_vehiculo(int fila, int col);                          /* En interfaz por defecto */

/* Crear un vehiculo vacio en la fila y columna indicadas */
/* Devuelve: identificador del vehiculo */

elemento_t crear_vehiculo_vacio_id(int finic, int cinic, id_grafi_t pgrafi); /* En interfaz pgrafi */
elemento_t crear_vehiculo_vacio(int fila, int col);                          /* En interfaz por defecto */

/* Crear un almacen en la fila y columna indicadas */
/* Devuelve: identificador del almacen */

elemento_t crear_almacen_id(int finic, int cinic, id_grafi_t p); /* En interfaz pgrafi */
elemento_t crear_almacen(int finic, int cinic);                  /* En interfaz por defecto */

/* Crear un pulsador en la fila y columna indicadas, que
    avisa con la senal "senal" y lleva la etiqueta "nombre" */
/* Devuelve: identificador del pulsador */

elemento_t crear_pulsador_id(float finic, float cinic, int senal, char *nombre,         /* En interfaz pgrafi */
                             id_grafi_t pgrafi);
elemento_t crear_pulsador(float finic, float cinic, int senal, char *nombre);           /* En interfaz por defecto */

elemento_t crear_pulsador_codigo_id(float finic, float cinic, int senal, char *nombre,  /* En interfaz pgrafi */
			            int codigo, id_grafi_t pgrafi);
elemento_t crear_pulsador_codigo(float finic, float cinic, int senal, char *nombre,     /* En interfaz por defecto */
				    int codigo);

				    
/* Crear entrada numerica */
/* Al cambiar el valor se devuelve con la senal como un entero, despues de 
    multiplicar el numero original por la escala */

elemento_t crear_ent_num_id(float finic, float cinic, int senal, char *nombre,          /* En interfaz pgrafi */
			    int codigo, float vinic, id_grafi_t pgrafi);
elemento_t crear_ent_num(float finic, float cinic, int senal, char *nombre,             /* En interfaz por defecto */
			    int codigo, float vinic);
			    
/* Devolver valor de entrada numerica */

float valor_ent_num(elemento_t id);

/* Cambiar valor de entrada numerica */

int   fijar_valor_ent_num(elemento_t id, float valor);

/* Cambiar visibilidad de un elemento */

void elem_visible(elemento_t id, int visible);

/* Destruir elemento */ 

void destruir_elemento(elemento_t elem);

/* Mover el elemento a la fila "fila" y la columna "col" */

int mueve(elemento_t veh, float fila, float col);

/* Cambiar velocidad del elemento: 
     vy: pix/seg en la direccion de las filas 
     vx: pix/seg en la direccion de las columnas 
     
     El movimiento solo para despues de una colision 
*/

void cambia_vel(elemento_t veh, float vy, float vx);

/* Cambiar posicion de elemento de manera instantanea */

void salta(elemento_t veh, float fila, float columna);

/* Cambiar el contenido del elemento */

void poner_cont(elemento_t veh, int cont);

/* Medir distancias en direccion N, S, E y O  */
/* Se mide con un haz de un pixel de ancho */

int sonar_nseo(elemento_t veh, float *d_n, float *d_s, float *d_e, float *d_o);

/* Leer estado de vehiculo */

struct estado_veh
{
  float fila;    /* Fila y columna actuales */
  float col;
  float vf;      /* Velocidad de fila y columna */
  float vc;
  int contenido; /* Contenido */
};

int leer_estado_veh(elemento_t veh, struct estado_veh *p);

/* Configurar escaner laser */
/* Se configura el laser del elemento id con:
   npuntos: Numero de puntos, espaciados uniformemente entre ang_min y ang_max.
   ang_min: Angulo minimo de medida.
   ang_max: Angulo maximo de medida.
   ancho_haz: Ancho del haz en radianes. Si vale 0, es una medida puntual.
   alcance: Distancia maxima que puede medir.
*/

int configurar_laser(elemento_t id, int npuntos, float ang_min, float ang_max, float ancho_haz, float alcance);

/* leer laser del elemento id. Se leen npuntos y van a la tabla
   que define ppuntos */

int leer_laser(elemento_t id, float *ppuntos, int npuntos);

/* Capturar raton, de modo que envie una senal con un codigo
   Actualmente solo se puede capturar el raton de una sola interfaz grafica */

typedef enum  { RATON_PULSACION, RATON_CONTINUO, RATON_DESACTIVAR } modo_captura_raton_t;

void capturar_raton_id(int senal, int codigo, modo_captura_raton_t modo, id_grafi_t p);  /* Raton de interfaz p */
void capturar_raton(int senal, int codigo);                                                   /* Raton de interfaz por defecto */

/* Leer la ultima posicion enviada por el raton:
   fila:    Puntero a la coordenada de fila
   col:     Puntero a la coordenada de columna
   pulsado: Puntero a un indicador que estara a 1 si se pulsa
            un boton, y a 0 en caso contrario */

int leer_estado_raton(float *fila, float *col, int *pulsado);


/* Cambiar escala de graficos */
/* Debe hacerse antes de dibujar nada */

void cambia_escala_id(int escala, id_grafi_t p);

/* Cambiar dimensiones de graficos */

void cambia_dimensiones_id(int ancho, int alto, id_grafi_t p);


/* Codigos del mapa, para crear_fondo_id */

#define PARED 1
#define PASILLO 0
#define META 2

/* Crear fondo */

void crear_fondo_id(int *pdat, int ancho, int alto, id_grafi_t p);

/* Destruir fondo */

void destruir_fondo_id(id_grafi_t p);

/* Devolver ids de elementos del fondo */

elemento_t **dar_ids_fondo_id(id_grafi_t p);


/* Imprimir matriz de enteros */ 

/* p: Puntero al primer elemento */
/* ancho y alto: Numero de filas y columnas */

void prmat(int *p, int ancho, int alto);

/* Crear matriz de enteros */
/* La zona de almacenamiento es contigua y por filas */

int **haz_mat_int(int ancho, int alto);

/* Destruir matriz de enteros */
/* No usar nunca si no se ha creado antes... */

void dest_mat_int(int **m, int alto);

/*                                                        */
/* Definiciones antiguas (no se recomienda utilizarlas)   */
/*                                                        */

/* Coordenadas de los puntos del camino */

#define FIL_A 1
#define COL_A 2 

#define FIL_B  2
#define COL_B  2 

#define FIL_C 3
#define COL_C 2 

/* Inicializar la interfaz grafica */
/* arrancar_prg: arrancar programa grafico (1) */
/* Devuelve identificador de servidor de graficos */
/* Atencion: En QNX fork solo funcionara ANTES de ejecutar ini_grafi  */

id_grafi_t ini_grafi(int arrancar_prg); 

/* Cerrar graficos */

void fin_grafi(void);

/* Conectar con servidor de graficos */
/*  Devuelve 0 si conecta; distinto de 0 si falla */

int conectar_grafi(id_grafi_t idgr);

/* Desconectar del servidor de graficos */

int desconectar_grafi();

/* Macro para crear elemento  */

#define crear_elem(f,c) crear_vehiculo_vacio(f,c)


/* Cambiar escala del dibujo (solo puede hacerse antes de
   abrir graficos)  */

void cambia_escala_dib(int escala);

/* Cambiar el mapa  */
/* p: Puntero al primer elemento */
/* ancho y alto: Numero de filas y columnas */
/* Valores a utilizar: PARED o PASILLO */
/* (solo puede hacerse antes de abrir graficos) */

void cambia_mapa(int *p, int ancho, int alto);

/* Devolver dimensiones del mapa */

void dar_dim_mapa(int *ancho, int *alto);

/* Devolver ids de elementos del fondo */

elemento_t **dar_ids_fondo(void);

/* Crear visor de tabla de flotantes */

typedef struct
{
    int n;
    elemento_t *visor;
    float *tabla;
} visor_tabla_float;

/* Crear y destruir */
visor_tabla_float *crear_visor_tabla_float(float *t, int n, char *nombre, int fila, int col); 
void destruir_visor_tabla_float(visor_tabla_float *pvis);                                     

/* Actualizar visor y leer tabla; se actualiza o lee la tabla de float con la
   que se inicializo el visor */

void actualizar_visor_tabla_float(visor_tabla_float *pvis);                              
void leer_visor_tabla_float(visor_tabla_float *pvis);                                              


/* Pulsador para bloquear y reanudar ejecucion */
/* Atencion: Al crear el pulsador se bloquea la senal SIGRTMAX-1, y en adelante
    se hace uso de ella para notificar la activacion del pulsador */
    
void crear_pulsador_sigue(int fila, int col);  /* Crear pulsador */
void esperar_pulsador_sigue(void);           /* Esperar pulsador */



#endif 
