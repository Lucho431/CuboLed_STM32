/*
 * botones_lfs.h
 *
 *  Created on: 24 ene. 2023
 *      Author: Luciano Salvatore
 */

#ifndef INC_BOTONES_LFS_H_
#define INC_BOTONES_LFS_H_

#include "main.h"

typedef enum{
    LOW_L,
    HIGH_L,
    FALL,
    RISE,
}T_INPUT;

typedef enum{
	IN_UP,
	IN_DOWN,
	IN_LEFT,
	IN_RIGHT,
	SIZEOF_POS_INPUT,
}T_POS_INPUT;


void lecturaTeclas(void);
void update_teclas (void);
T_INPUT getStatBoton (T_POS_INPUT);

#endif /* INC_BOTONES_LFS_H_ */
