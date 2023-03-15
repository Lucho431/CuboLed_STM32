/*
 * blockOut.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Luciano Salvatore
 */

#ifndef INC_BLOCKOUT_H_
#define INC_BLOCKOUT_H_

#include "stm32f1xx_hal.h"

typedef enum{
	PUNTO,
	LINEA_2,
	LINEA_3,
	LINEA_4,
	PIEZA_T,
	PIEZA_S,
	PIEZA_L,
	ESQUINA,
	CUADRADO,
	PIEZA_U,
	PIEZA_S_GRANDE,
	SIZE_TIPO_PIEZA,
}T_TIPO_PIEZA;

typedef enum{
	JUEGO_IDLE,
	ARRANCA_JUEGO,
	CHECK_PIEZA,
	CHECK_MOV_GIROS,
	CHECK_CAIDA,
	CHECK_PISO_LLENO,
}T_ESTATUS_JUEGO;

typedef struct t_pieza{
	T_TIPO_PIEZA nombre;
	uint8_t lado; //dimension de la matriz: lado*lado*lado.
	uint8_t matriz[4][4]; //puntero a la matriz correspondiente.
	uint8_t matrizAux[4][4]; //puntero a la matriz auxiliar correspondiente.
	uint8_t dibujo[4]; //puntero al dibujo de la pieza
}T_PIEZA;


void runBlockOut (void);

#endif /* INC_BLOCKOUT_H_ */
