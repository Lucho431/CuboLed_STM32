/*
 * botones_lfs.c
 *
 *  Created on: 24 ene. 2023
 *      Author: Luciano Salvatore
 */

#include "botones_lfs.h"

uint8_t read_boton[4] = {1, 1, 1, 1};
uint8_t last_boton[4] = {1, 1, 1, 1};

void lecturaTeclas (void){
	read_boton[IN_UP] = HAL_GPIO_ReadPin(IN_UP_GPIO_Port, IN_UP_Pin);
	read_boton[IN_DOWN] = HAL_GPIO_ReadPin(IN_DOWN_GPIO_Port, IN_DOWN_Pin);
	read_boton[IN_LEFT] = HAL_GPIO_ReadPin(IN_LEFT_GPIO_Port, IN_LEFT_Pin);
	read_boton[IN_RIGHT] = HAL_GPIO_ReadPin(IN_RIGHT_GPIO_Port, IN_RIGHT_Pin);
} //end lecturaTeclas ()

void update_teclas (void){
	last_boton [IN_UP] = read_boton[IN_UP];
	last_boton [IN_DOWN] = read_boton[IN_DOWN];
	last_boton [IN_LEFT] = read_boton[IN_LEFT];
	last_boton [IN_RIGHT] = read_boton[IN_RIGHT];
} //end update_teclas ()

T_INPUT getStatBoton (T_POS_INPUT b){
	if (read_boton[b] != 0){
		if (last_boton[b] != 0){
			return HIGH_L;
		}else{
			return RISE;
		}
	}else{
		if (last_boton[b] != 0){
			return FALL;
		}else{
			return LOW_L;
		}
	}
} //end getStatBoton ()
