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
uint8_t cursor_principal = 0; //posicion cursor del menú principal
uint8_t cursor_efecto = 0; //posicion del cursor de elección de efecto.
//variables funciones


void acc_menuOff (void);
void acc_menuPrincipal (void);
void acc_eligeEfecto (void);
void acc_menuAdc (void);

void init_menuOff (void);
void init_menuPrincipal (void);
void init_eligeEfecto (void);
void init_menuAdc (void);

T_MENU menu[SIZE_MENU_NOMBRE] = {
		{MENU_OFF, NULL, init_menuOff, acc_menuOff}, //MENU_OFF
		{MENU_PRINCIPAL, NULL, init_menuPrincipal, acc_menuPrincipal}, //MENU_PRINCIPAL
		{MENU_ELIGE_EFECTO, NULL, init_eligeEfecto, acc_eligeEfecto}, //MENU_ELIGE_EFECTO
		{MENU_ADC, NULL, init_menuAdc, acc_menuAdc}, //MENU_ADC
};

/////////////////////////////////////////
//         FUNCIONES PUBLICAS          //
/////////////////////////////////////////
void start_menu (void){
	//init_pantalla();
	SSD1306_Init();
	init_menuPrincipal();
	menuActual = &menu[MENU_PRINCIPAL];
}

void check_menu (void){
	menuActual->accion();
}

/////////////////////////////////////////
//          INICIALIZADORES            //
/////////////////////////////////////////
void init_menuOff (void){

}

void init_menuPrincipal (void){

//	set_pantalla(PANT_init_menuPrincipal);
	SSD1306_Clear();
	SSD1306_GotoXY(0, 0);
	SSD1306_Puts("MENU PRINCIPAL", &Font_7x10, 1);
	SSD1306_GotoXY(14, 15);
	SSD1306_Puts("Elige efecto", &Font_11x18, 1);
	SSD1306_GotoXY(14, 22);
	SSD1306_Puts("Jugar Block Out", &Font_11x18, 1);
	menuActual = &menu[MENU_PRINCIPAL];
	cursor_principal = 0;

} //end init_menuPrincipal()

void init_eligeEfecto (void){

} //end init_eligeEfecto()

void init_menuAdc (void){

} //end init_menuAdc()
/////////////////////////////////////////
//            ACCIONES                 //
/////////////////////////////////////////
void acc_menuOff (void){

} //end acc_menuOff()

void acc_menuPrincipal (void){

} //end acc_menuPrincipal()

void acc_eligeEfecto (void){

} //end acc_eligeEfecto()

void acc_menuAdc (void){

} //end acc_menuAdc()

void acc_config (void){

}
