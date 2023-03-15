/*
 * blockOut.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Luciano Salvatore
 */

#include "blockOut.h"

//variables del juego
uint8_t flag_pieza = 0; // indica si hay una pieza viva
uint8_t flag_movGiroProhibido = 0; // indica si no está permitido el giro o  movimiento
uint8_t flag_timeoutCaer = 0;
uint8_t opcupacion[8][8] = {0}; //matriz de ocupacion
T_ESTATUS_JUEGO estatus_juego = JUEGO_IDLE;
int8_t index_pieza;
int8_t pos_piezaX;
int8_t pos_piezaY;
int8_t pos_piezaZ;
char entradaJoystick;
uint8_t completaPiso = 0; //cuando llega a 8, es un piso lleno.
uint8_t ocupacion[8][8]= {{0}};

T_PIEZA piezaActiva;

//variables externas
extern uint8_t cube[8][8];
//matrices para las piezas
uint8_t m_pieza8[2][2];
uint8_t m_pieza27[3][3];
uint8_t m_pieza64[4][4];
uint8_t m_aux8[2][2];
uint8_t m_aux27[3][3];
uint8_t m_aux64[4][4];
//dibujos de las piezas
uint8_t dib_linea2[2]= {2,2};
uint8_t dib_linea3[3]= {2,2,2};
uint8_t dib_linea4[4]= {4,4,4,4};
uint8_t dib_t[3] = {2,7,0};
uint8_t dib_s[3] = {3,6,0};
uint8_t dib_l[3] = {4,4,6};
uint8_t dib_esq[2] = {2,3};
uint8_t dib_cuad[2] = {3,3};
uint8_t dib_u[3] = {5,7};
uint8_t dib_s_2[3] = {3,2,6};

T_PIEZA pieza [SIZE_TIPO_PIEZA] = {
												{PUNTO, 1, NULL, NULL, NULL},
												{LINEA_2, 2, (uint8_t**)m_pieza8, (uint8_t**)m_aux8, (uint8_t*)dib_linea2},
												{LINEA_3, 3, (uint8_t**)m_pieza27, (uint8_t**)m_aux27, (uint8_t*)dib_linea3},
												{LINEA_4, 4, (uint8_t**)m_pieza64, (uint8_t**)m_aux64, (uint8_t*)dib_linea4},
												{PIEZA_T, 3, (uint8_t**)m_pieza27, (uint8_t**)m_aux27, (uint8_t*)dib_t},
												{PIEZA_S, 3, (uint8_t**)m_pieza27, (uint8_t**)m_aux27, (uint8_t*)dib_s},
												{PIEZA_L, 3, (uint8_t**)m_pieza27, (uint8_t**)m_aux27, (uint8_t*)dib_l},
												{ESQUINA, 2, (uint8_t**)m_pieza8, (uint8_t**)m_aux8, (uint8_t*)dib_esq},
												{CUADRADO, 2, (uint8_t**)m_pieza8, (uint8_t**)m_aux8, (uint8_t*)dib_cuad},
												{PIEZA_U, 3, (uint8_t**)m_pieza27, (uint8_t**)m_aux27, (uint8_t*)dib_u},
												{PIEZA_S_GRANDE, 3, (uint8_t**)m_pieza27, (uint8_t**)m_aux27, (uint8_t*)dib_s_2},
};

void runBlockOut (void){

	for (uint8_t j = 0; j < 8; j++){
		for (uint8_t k = 0; k < 8; k++){
			cube[j][k] =0;
		} //end for k
	} //end for j

	switch(estatus_juego){
		case JUEGO_IDLE:
			estatus_juego = ARRANCA_JUEGO;
		break;
		case ARRANCA_JUEGO:
			//tareas de inicialización
			estatus_juego = CHECK_PIEZA;
		break;
		case CHECK_PIEZA:
			if (!flag_pieza){ //si no hay pieza...
				index_pieza = rand() % SIZE_TIPO_PIEZA;

				// NOTA: coordenandas de la matriz: matriz[y][z] |=  (0x01 << x);

				//crea la pieza
				for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
					pieza[index_pieza].matriz[i][1] = pieza[index_pieza].dibujo[i];
				} //end for

				//posicion inicial de la pieza (desde la esquina 0,0,0 de la pieza)
				pos_piezaX = (8 - pieza[index_pieza].lado) >> 1;
				pos_piezaY = (8 - pieza[index_pieza].lado) >> 1;
				pos_piezaZ = 7;

				//dibuja la pieza
				for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
					for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
						for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
							if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
								cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
							}else{
								cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX));
							} //end if (pieza[index_pieza]...
						} //end for z
					} //end for y
				} //end for x

				//comprueba ocupación
				for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
					for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
						for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
							if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) && (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
								//GAME OVER
								estatus_juego = JUEGO_IDLE;
								break; //sale del for o del case??
							} //end if...
						} //end for z
					} //end for y
				} //end for x

				flag_pieza = 1;

			} //end if !flag_pieza
			estatus_juego = CHECK_MOV_GIROS;
		break;
		case CHECK_MOV_GIROS:
			switch (entradaJoystick){
				case 'u': // mueve +y
					if (pos_piezaY + pieza[index_pieza].lado < 7){
						pos_piezaY++;

						//comprueba ocupación
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) & (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
										//anula el movimiento
										pos_piezaY--;
										break; //sale del for o del case??
									} //end if...
								} //end for z
							} //end for y
						} //end for x

						//dibuja la pieza
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
										cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
									}else{
										cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX));
									} //end if (pieza[index_pieza]...
								} //end for z
							} //end for y
						} //end for x

					} //end if (pos_piezaY + pieza[index_pieza].lado < 7)
				break;
				case 'd': // mueve -y
					if (pos_piezaY > 0){
						pos_piezaY--;

						//comprueba ocupación
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) & (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
										//anula el movimiento
										pos_piezaY++;
										break; //sale del for o del case??
									} //end if...
								} //end for z
							} //end for y
						} //end for x

						//dibuja la pieza
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
										cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
									}else{
										cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX) );
									} //end if (pieza[index_pieza]...
								} //end for z
							} //end for y
						} //end for x

					} //end if (pos_piezaY > 0)
				break;
				case 'l': // mueve +x
					if (pos_piezaX + pieza[index_pieza].lado < 7){
						pos_piezaX++;

						//comprueba ocupación
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) & (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
										//anula el movimiento
										pos_piezaX--;
										break; //sale del for o del case??
									} //end if...
								} //end for z
							} //end for y
						} //end for x

						//dibuja la pieza
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
										cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
									}else{
										cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX) );
									} //end if (pieza[index_pieza]...
								} //end for z
							} //end for y
						} //end for x

					} //end if (pos_piezaX + pieza[index_pieza].lado < 7)
				break;
				case 'r': // mueve -x
					if (pos_piezaX > 0){
						pos_piezaX--;

						//comprueba ocupación
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) && (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
										//anula el movimiento
										pos_piezaX++;
										break; //sale del for o del case??
									} //end if...
								} //end for z
							} //end for y
						} //end for x

						//dibuja la pieza
						for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
							for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
								for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
									if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
										cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
									}else{
										cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX) );
									} //end if (pieza[index_pieza]...
								} //end for z
							} //end for y
						} //end for x

					} //end if (pos_piezaX > 0)
				break;
				case '1': // giro eje z
					// NOTA: coordenandas de la matriz: matriz[y][z] |=  (0x01 << x);
					for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){

								if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
									pieza[index_pieza].matrizAux[i][k] |= (0b1 << (pieza[index_pieza].lado - j) );
								}else{
									pieza[index_pieza].matrizAux[i][k] ^= (0b1 << (pieza[index_pieza].lado - j) ); //nunca use esta expresion para setear ceros.
								} //end if (pieza[index_pieza].matriz[j][k] & (0b1 << i) )

							} //end for x
						} //end for y
					} //end for z

					//comprueba ocupación
					flag_movGiroProhibido = 0;
					for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
								if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) && (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
									//anula el movimiento
									flag_movGiroProhibido = 1;
									break; //sale del for o del case??
								} //end if...
							} //end for z
						} //end for y
					} //end for x

					if (flag_movGiroProhibido != 0) break;

					//dibuja la pieza
					for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							pieza[index_pieza].matriz[j][k] = pieza[index_pieza].matrizAux[j][k];
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
								if (pieza[index_pieza].matrizAux[j][k] & (0b1 << i) ){
									cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
								}else{
									cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX) );
								} //end if (pieza[index_pieza]...
							} //end for z
						} //end for y
					} //end for x

				break;
				case '2': // giro eje x
					// NOTA: coordenandas de la matriz: matriz[y][z] |=  (0x01 << x);
					for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							for (int8_t k = 0; k < pieza[index_pieza].lado; k++){

								if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
									pieza[index_pieza].matrizAux[pieza[index_pieza].lado - k][j] |= (0b1 << i);
								}else{
									pieza[index_pieza].matrizAux[pieza[index_pieza].lado - k][j] ^= (0b1 << i); //nunca use esta expresion para setear ceros.
								} //end if (pieza[index_pieza].matriz[j][k] & (0b1 << i) )

							} //end for x
						} //end for y
					} //end for z

					//comprueba ocupación
					flag_movGiroProhibido = 0;
					for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
								if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) && (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
									//anula el movimiento
									flag_movGiroProhibido = 1;
									break; //sale del for o del case??
								} //end if...
							} //end for z
						} //end for y
					} //end for x

					if (flag_movGiroProhibido != 0) break;

					//dibuja la pieza
					for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							pieza[index_pieza].matriz[j][k] = pieza[index_pieza].matrizAux[j][k];
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
								if (pieza[index_pieza].matrizAux[j][k] & (0b1 << i) ){
									cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
								}else{
									cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX) );
								} //end if (pieza[index_pieza]...
							} //end for z
						} //end for y
					} //end for x
				break;
				case '3': // giro eje y
					// NOTA: coordenandas de la matriz: matriz[y][z] |=  (0x01 << x);
					for (int8_t j = 0; j < pieza[index_pieza].lado; j++ ){
						for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){

								if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
									pieza[index_pieza].matrizAux[j][pieza[index_pieza].lado - i] |= (0b1 << (pieza[index_pieza].lado - k) );
								}else{
									pieza[index_pieza].matrizAux[j][pieza[index_pieza].lado - i] ^= (0b1 << (pieza[index_pieza].lado - k) ); //nunca use esta expresion para setear ceros.
								} //end if (pieza[index_pieza].matriz[j][k] & (0b1 << i) )

							} //end for x
						} //end for y
					} //end for z

					//comprueba ocupación
					flag_movGiroProhibido = 0;
					for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
								if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) && (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
									//anula el movimiento
									flag_movGiroProhibido = 1;
									break; //sale del for o del case??
								} //end if...
							} //end for z
						} //end for y
					} //end for x

					if (flag_movGiroProhibido != 0) break;

					//dibuja la pieza
					for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							pieza[index_pieza].matriz[j][k] = pieza[index_pieza].matrizAux[j][k];
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
								if (pieza[index_pieza].matrizAux[j][k] & (0b1 << i) ){
									cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
								}else{
									cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX) );
								} //end if (pieza[index_pieza]...
							} //end for z
						} //end for y
					} //end for x

				break;
				case '4': // cae la pieza

				default:
				break;
			} //end switch entradaJoystick

			entradaJoystick = 0;

		break;
		case CHECK_CAIDA:
			if (flag_timeoutCaer != 0){
				pos_piezaZ--;

				//comprueba ocupación
				flag_movGiroProhibido = 0;
				for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){

					if (k + pos_piezaZ >= 0){ //comprueba que esté dentro del cubo el ciclo actual

						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
								if ( (ocupacion[j + pos_piezaY][k + pos_piezaZ] & ( 0b1 << (i + pos_piezaX) )) && (pieza[index_pieza].matriz[j][k] & (0b1 << i) ) ){
									//anula el movimiento
									flag_movGiroProhibido = 1;
									break; //sale del for o del case??
								} //end if...
							} //end for x
						} //end for y

					}else{ //si está debajo del cubo...

						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
								if ( pieza[index_pieza].matriz[j][k] != 0  ){
									//anula el movimiento
									flag_movGiroProhibido = 1;
									break; //sale del for o del case??
								} //end if...
							} //end for x
						} //end for y

					} // end if  k + pos_piezaZ >= 0

				} //end for z

				if (flag_movGiroProhibido != 0){
					pos_piezaZ++;
					flag_pieza = 0;
					//llena la matriz de ocupacion
					for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){
						for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
							ocupacion[j + pos_piezaY][k + pos_piezaZ] |= pieza[index_pieza].matriz[j][k];
							for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
								if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
									cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
								}else{
									cube[j + pos_piezaY][k + pos_piezaZ] ^= (0x01 << (i + pos_piezaX) );
								} //end if (pieza[index_pieza]...
							} //end for z
						} //end for y
					} //end for x
					flag_movGiroProhibido = 0;
				} //end if (flag_movGiroProhibido != 0)

				flag_timeoutCaer = 0;
			} //end if flag_timeoutCaer != 0

			estatus_juego = CHECK_PISO_LLENO;
		break;
		case CHECK_PISO_LLENO:
			completaPiso = 0;

			for (int8_t k = 0; k < 8; k++){

				for (int8_t j = 0; j < 8; j++){
					if (ocupacion[j][k] == 0xFF){
						completaPiso++;
					}else{
						completaPiso = 0;
						j = 8; //asquerosidad para terminar el bucle
					} //end if (ocupacion[j][k] == 0xFF)
				} //end for j

				 if (completaPiso == 8){
					 for (int8_t q = k; q < 8; q++){

						 if (q == 7){ //llegue al piso 7
							 for (int8_t j = 0; j < 8; j++){
								 ocupacion[j][k] = 0;
							 } //end for j
						 }else{ //si no llegue al piso 7
							for (int8_t j = 0; j < 8; j++){
								 ocupacion[j][k] = ocupacion[j][k + 1];
							 } //end for j
						 } //end if q == 7

					 } //end for q
					 completaPiso = 0;
				 } //end if (completaPiso == 8)
			} //end for k

			estatus_juego = CHECK_PIEZA;
		default:
		break;
	} //end switch estatus_juego

	for (uint8_t i = 0; i < 8; i++){
		for (uint8_t j = 0; j < 8; j++){
			for (uint8_t k = 0; k < 8; k++){
				if (ocupacion[j][k] & (0b1 << i) ){
					cube[j][k] |= (0x01 << i );
				} //end if ocupacion...
			} //end for k
		} //end for j
	} //end for i

} //end runBlockOut()
