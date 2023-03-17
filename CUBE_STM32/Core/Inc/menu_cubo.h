/*
 * menu_tablero.h
 *
 *  Created on: Jan 30, 2022
 *      Author: Luciano Salvatore
 */

#ifndef INC_MENU_TABLERO_H_
#define INC_MENU_TABLERO_H_

#include "stm32f1xx_hal.h"
#include "botones_lfs.h"
#include "ssd1306.h"
#include "fonts.h"

typedef struct t_menu {
	int8_t nombre;
	struct t_menu* menuAnterior;
	void (*inicia_menu) (void);
	void (*accion) (void);
} T_MENU;

typedef enum{
	MENU_OFF,
	MENU_PRINCIPAL,
	MENU_ELIGE_EFECTO,
	MENU_ADC,
	MENU_UART,
	SIZE_MENU_NOMBRE,
} T_MENU_NOMBRE;

//funciones publicas
void start_menu (void);
void check_menu (void);

#endif /* INC_MENU_TABLERO_H_ */
