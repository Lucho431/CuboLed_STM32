/*
 * menu_cubo.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Luciano Salvatore
 */

#include "menu_cubo.h"
#include "display_cubo.h"

//variables menu
T_MENU* menuActual;
T_MENU* menuAux;
//variables funciones



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
	init_pantalla();
	init_menuPrincipal();
	menuActual = &menu[MENU_PRINCIPAL];
}

void check_menu (void){
	menuActual->accion();
}

/////////////////////////////////////////
//          INICIALIZADORES            //
/////////////////////////////////////////

void init_menuPrincipal (void){

//	set_pantalla(PANT_init_menuPrincipal);
	menuActual = &menu[MENU_PRINCIPAL];

} //end init_menuPrincipal()

void init_eligeEfecto (void){

} //end init_eligeEfecto()

void init_menuAdc (void){

} //end init_menuAdc()
/////////////////////////////////////////
//            ACCIONES                 //
/////////////////////////////////////////

void acc_menuPrincipal (void){



} //end acc_menuPrincipal()

void acc_eligeEfecto (void){

} //end acc_eligeEfecto()

void acc_menuAdc (void){

} //end acc_menuAdc()

void acc_config (void){

}
