/*
 * menu_cubo.c
 *
 *  Created on: Jan 30, 2022
 *      Author: Luciano Salvatore
 */

#include "menu_cubo.h"

//variables menu
T_MENU* menuActual;
T_MENU* menuAux;
//variables tomas
uint8_t flag_tomas = 0;
//variables funciones
uint8_t pulsoLargo_skimmer = 0;
uint8_t pulsoLargo_luz = 0;


void acc_menuPrincipal (void);
void acc_eligeEfecto (void);
void acc_menuAdc (void);

void init_menuPrincipal (void);
void init_eligeEfecto (void);
void init_menuAdc (void);

T_MENU menu[SIZE_MENU_NOMBRE] = {
		{MENU_PRINCIPAL, NULL, init_menuPrincipal, acc_menuPrincipal}, //MENU_PRINCIPAL
		{MENU_ELIGE_EFECTO, NULL, init_eligeEfecto, acc_eligeEfecto}, //MENU_ELIGE_EFECTO
		{MENU_ADC, NULL, init_menuAdc, acc_menuAdc}, //MENU_ADC
};

/////////////////////////////////////////
//         FUNCIONES PUBLICAS          //
/////////////////////////////////////////
void start_menu (void){
	//init_pantalla();
	init_menuPrincipal();
	menuActual = &menu[MENU_PRINCIPAL];
}

void check_menu (void){
	menuActual->accion();
}

void check_duracionPulsadores (void){

	if (pulsoLargo_skimmer != 0){
		pulsoLargo_skimmer--;
	}

	if (pulsoLargo_luz != 0){
		pulsoLargo_luz--;
	}
} //end check_duracionPulsadores ()

void check_pulsadores (void){
	__NOP();
}

/////////////////////////////////////////
//          INICIALIZADORES            //
/////////////////////////////////////////

void init_menuPrincipal (void){

//	set_pantalla(PANT_init_menuPrincipal);
//	menuActual = &menu[MENU_PRINCIPAL];
}

void init_config (void){
	__NOP();
}


/////////////////////////////////////////
//            ACCIONES                 //
/////////////////////////////////////////

void acc_menuPrincipal (void){
/*
	if (getStatBoton(IN_A)==FALL){

		//si se estaba llenando la pileta, va al menu de llenado.
		//caso contrario, permite entrar a la configuracion de llenado.
		switch (status_menuLlenado){
			case LLENANDO:
			case LLENANDO_CHECK:
			case PILETA_LLENA:
				menuActual = &menu[MENU_LLENADO];
				menuActual->menuAnterior = &menu[MENU_PRINCIPAL];
				menuActual->inicia_menu();
			break;
			default:
				menuActual = &menu[MENU_SET_LLENADO];
				menuActual->menuAnterior = &menu[MENU_PRINCIPAL];
				menuActual->inicia_menu();
			break;
		} //end switch status_menuLlenado
		return;
	}

	if (getStatBoton(IN_B)==FALL){
		menuActual = &menu[MENU_SKIMMER];
		menuActual->menuAnterior = &menu[MENU_PRINCIPAL];
		menuActual->inicia_menu();
		return;
	}

	if (getStatBoton(IN_C)==FALL){
		menuActual = &menu[MENU_HIDRO];
		menuActual->menuAnterior = &menu[MENU_PRINCIPAL];
		menuActual->inicia_menu();
		return;
	}
*/
} //end acc_menuPrincipal()

void acc_config (void){

}
