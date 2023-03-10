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
}T_ESTATUS_JUEGO;



typedef struct t_pieza{
	T_TIPO_PIEZA nombre;
	uint8_t lado; //dimension de la matriz: lado*lado*lado.
	uint8_t* matriz; //puntero a la matriz correspondiente.
	uint8_t* dibujo; //puntero al dibujo de la pieza	
}T_PIEZA;


//variables del juego
uint8_t flag_pieza = 0; // indica si hay una pieza viva
uint8_t opcupacion[8][8] = {0}; //matriz de ocupacion
T_ESTATUS_JUEGO estatus_juego = JUEGO_IDLE;
uint8_t index_pieza;
uint8_t pos_piezaX;
uint8_t pos_piezaY;
uint8_t pos_piezaZ;

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
														{PUNTO, 1, NULL, NULL},
														{LINEA_2, 2, m_pieza8, dib_linea2},
														{LINEA_3, 3, m_pieza27, dib_linea3},
														{LINEA_4, 4, m_pieza64, dib_linea4},
														{PIEZA_T, 3, m_pieza27, dib_t},
														{PIEZA_S, 3, m_pieza27, dib_s},
														{PIEZA_L, 3, m_pieza27, dib_l},
														{ESQUINA, 2, m_pieza8, dib_esq},
														{CUADRADO, 2, m_pieza8, dib_cuad},
														{PIEZA_U, 3, m_pieza27, dib_u},
														{PIEZA_S_GRANDE, 3, m_pieza27, dib_s_2},														
};


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
			for (uint8_t i = 0; i < lado; i++){
				pieza[index_pieza]->matriz[i][1] = pieza[index_pieza]->dibujo[i];
			} //end for
			
			//posicion inicial de la pieza (desde la esquina 0,0,0 de la pieza)
			pos_piezaX = (8 - lado) >> 1;
			pos_piezaY = (8 - lado) >> 1;
			pos_piezaZ = 7;
			
			//dibuja la pieza
			for (uint8_t i = pos_piezaX; i < pos_piezaX + lado; i++ ){
				for (uint8_t j = pos_piezaY; j < pos_piezaY + lado; j++){
					for (uint8_t k = pos_piezaZ; k < pos_piezaZ + lado; k++){
						if ( !(ocupacion[j][k] & (0b1 << i)) ){
							cube[j][k] |= (0x01 << i);
						}else{
							//GAME OVER
							estatus_juego = JUEGO_IDLE;
							break;
						} //end if...
					} //end for z
				} //end for y
			} //end for x
			
			flag_pieza = 1;
			
		} //end if !flag_pieza
		estatus_juego = CHECK_MOV_GIROS;
	break;
	case CHECK_MOV_GIROS:
	
	break:
	case CHECK_CAIDA:
	
	break;
	default:
	break;
} //end switch estatus_juego

/*
 * PASOS:
 * 
 * 1: si no hay pieza, dibujo pieza al azar.
 * 
 * 2: si creo la pieza y toca celda ocupada, fin del juego.
 * 
 * 3: compruebo botones de rotacion o movimiento. Si no hay obstaculos, procede con la acción.
 * 
 * 4: comprueba la caida, si está ocupada la celda donde va a caer, me congelo donde estoy y relleno la matriz de ocupación. Mato la pieza.
 * Si no está ocupada, bajo uno y espero el tiempo de caida.
 * 
 */

