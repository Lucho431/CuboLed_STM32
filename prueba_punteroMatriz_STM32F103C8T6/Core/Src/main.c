/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
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
	uint8_t** matriz; //puntero a la matriz correspondiente.
	uint8_t** matrizAux; //puntero a la matriz auxiliar correspondiente.
	uint8_t* dibujo; //puntero al dibujo de la pieza
}T_PIEZA;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t flag_uart = 0;
char texto[100];
int16_t txtLenght;
uint8_t index_texto = 0;
uint8_t rx[3];
uint8_t rx_j;
uint8_t rx_k;

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

//variables externas (no externalizadas en este proyecto)
uint8_t cube[8][8];

/*
//matrices para las piezas
uint8_t m_pieza8[2][2]= {{4,6},{2,0}};
uint8_t m_pieza27[3][3]={{7,8,9},{144,155,166},{10,20,30}};
uint8_t m_pieza64[4][4];
uint8_t m_aux8[2][2];
uint8_t m_aux27[3][3];
uint8_t m_aux64[4][4];
*/

//punteros para las matrices de piezas
uint8_t** m_pieza8;
uint8_t** m_pieza27;
uint8_t** m_pieza64;
uint8_t** m_aux8;
uint8_t** m_aux27;
uint8_t** m_aux64;

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

//T_PIEZA pieza [SIZE_TIPO_PIEZA] = {
//												{PUNTO, 1, NULL, NULL, NULL},
//												{LINEA_2, 2, (uint8_t**)m_pieza8, m_aux8, (uint8_t*)dib_linea2},
//												{LINEA_3, 3, m_pieza27, m_aux27, (uint8_t*)dib_linea3},
//												{LINEA_4, 4, m_pieza64, m_aux64, (uint8_t*)dib_linea4},
//												{PIEZA_T, 3, m_pieza27, m_aux27, (uint8_t*)dib_t},
//												{PIEZA_S, 3, m_pieza27, m_aux27, (uint8_t*)dib_s},
//												{PIEZA_L, 3, m_pieza27, m_aux27, (uint8_t*)dib_l},
//												{ESQUINA, 2, m_pieza8, m_aux8, (uint8_t*)dib_esq},
//												{CUADRADO, 2, m_pieza8, m_aux8, (uint8_t*)dib_cuad},
//												{PIEZA_U, 3, m_pieza27, m_aux27, (uint8_t*)dib_u},
//												{PIEZA_S_GRANDE, 3, m_pieza27, m_aux27, (uint8_t*)dib_s_2},
//};

T_PIEZA pieza [SIZE_TIPO_PIEZA] = {
												{PUNTO, 1, NULL, NULL, NULL},
												{LINEA_2, 2, NULL, NULL, (uint8_t*)dib_linea2},
												{LINEA_3, 3, NULL, NULL, (uint8_t*)dib_linea3},
												{LINEA_4, 4, NULL, NULL, (uint8_t*)dib_linea4},
												{PIEZA_T, 3, NULL, NULL, (uint8_t*)dib_t},
												{PIEZA_S, 3, NULL, NULL, (uint8_t*)dib_s},
												{PIEZA_L, 3, NULL, NULL, (uint8_t*)dib_l},
												{ESQUINA, 2, NULL, NULL, (uint8_t*)dib_esq},
												{CUADRADO, 2, NULL, NULL, (uint8_t*)dib_cuad},
												{PIEZA_U, 3, NULL, NULL, (uint8_t*)dib_u},
												{PIEZA_S_GRANDE, 3, NULL, NULL, (uint8_t*)dib_s_2},
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  txtLenght = sprintf(texto, "arranca prueba de matrices:\n");
  HAL_UART_Transmit_IT(&huart1, (uint8_t*)texto, txtLenght);
  HAL_UART_Receive_IT(&huart1, rx, 3);


  //creacion de las matrices:
  m_pieza8 = (uint8_t **)malloc (2*sizeof(uint8_t *));
  for (int8_t i=0; i < 2; i++)
	  m_pieza8[i] = (uint8_t *) malloc (2*sizeof(uint8_t));

  m_pieza27 = (uint8_t **)malloc (3*sizeof(uint8_t *));
  for (int8_t i=0; i < 3; i++)
	  m_pieza27[i] = (uint8_t *) malloc (3*sizeof(uint8_t));

  m_pieza64 = (uint8_t **)malloc (4*sizeof(uint8_t *));
  for (int8_t i=0; i < 4; i++)
	  m_pieza64[i] = (uint8_t *) malloc (4*sizeof(uint8_t));

  m_aux8 = (uint8_t **)malloc (2*sizeof(uint8_t *));
  for (int8_t i=0; i < 2; i++)
	  m_aux8[i] = (uint8_t *) malloc (2*sizeof(uint8_t));

  m_aux27 = (uint8_t **)malloc (3*sizeof(uint8_t *));
  for (int8_t i=0; i < 3; i++)
	  m_aux27[i] = (uint8_t *) malloc (3*sizeof(uint8_t));

  m_aux64 = (uint8_t **)malloc (4*sizeof(uint8_t *));
  for (int8_t i=0; i < 4; i++)
	  m_aux64[i] = (uint8_t *) malloc (4*sizeof(uint8_t));


  for (uint8_t i = 0; i < SIZE_TIPO_PIEZA; i++){
	  switch (pieza[i].nombre){
		  case LINEA_2:
		  case ESQUINA:
		  case CUADRADO:
			  pieza[i].matriz = m_pieza8;
			  pieza[i].matrizAux = m_aux8;
		  break;
		  case LINEA_3:
		  case PIEZA_T:
		  case PIEZA_S:
		  case PIEZA_L:
		  case PIEZA_U:
		  case PIEZA_S_GRANDE:
			  pieza[i].matriz = m_pieza27;
			  pieza[i].matrizAux = m_aux27;
		  break;
		  case LINEA_4:
			  pieza[i].matriz = m_pieza64;
			  pieza[i].matrizAux = m_aux64;
		  break;
		  default:
		  break;
	  } //fin switch
  } //fin for

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (flag_uart != 0){

		  for (uint8_t j = 0; j < 8; j++){
			  for (uint8_t k = 0; k < 8; k++){
				  //ocupacion[j][k] =0; //en el init del juego
				  //ocupacion[j][k] = '-'; //solo aplica para las pruebas por uart
				  cube[j][k] = 0; //solo aplica para las pruebas por uart
			  } //end for k
		  } //end for j

		  index_pieza = rx[0] - '0';
		  rx_j = rx[1] - '0';
		  rx_k = rx[2] - '0';


		  //crea la pieza
		  for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
			  for (int8_t k = 0; k < pieza[index_pieza].lado; k++){

				  if (k == 1){
					  pieza[index_pieza].matriz[j][k] = pieza[index_pieza].dibujo[j];
				  }else{
					  pieza[index_pieza].matriz[j][k] = 0;
				  }
			  } //end for k
		  } //end for j

		  //posicion inicial de la pieza (desde la esquina 0,0,0 de la pieza)
//		  pos_piezaX = (8 - pieza[index_pieza].lado) >> 1;
//		  pos_piezaY = (8 - pieza[index_pieza].lado) >> 1;
		  pos_piezaZ = 6;

//		  pos_piezaX = 0;
//		  pos_piezaY = 0;
		  pos_piezaX = 8 - pieza[index_pieza].lado;
		  pos_piezaY = 8 - pieza[index_pieza].lado;

		  //ubico la pieza dentro del cubo (solo para la prueba por uart)
		  for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
			  for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
				  for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
					  if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
						  cube[j + pos_piezaY][k + pos_piezaZ] |= (0x01 << (i + pos_piezaX) );
					  }else{
						  cube[j + pos_piezaY][k + pos_piezaZ] &= ~(0x01 << (i + pos_piezaX));
					  } //end if (pieza[index_pieza]...
				  } //end for z
			  } //end for y
		  } //end for x

/*
		  //giro eje Z
		  // NOTA: coordenandas de la matriz: matriz[y][z] |=  (0x01 << x);
		  for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){
			  for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
				  for (int8_t i = 0; i < pieza[index_pieza].lado; i++){

					  if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
						  pieza[index_pieza].matrizAux[i][k] |= (0b1 << (pieza[index_pieza].lado- 1 - j) );
					  }else{
						  pieza[index_pieza].matrizAux[i][k] &= ~(0b1 << (pieza[index_pieza].lado - 1 - j) ); //nunca use esta expresion para setear ceros.
					  } //end if (pieza[index_pieza]->matriz[j][k] & (0b1 << i) )

				  } //end for x
			  } //end for y
		  } //end for z

		  //giro eje x
		  // NOTA: coordenandas de la matriz: matriz[y][z] |=  (0x01 << x);
		  for (int8_t i = 0; i < pieza[index_pieza].lado; i++ ){
			  for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
				  for (int8_t k = 0; k < pieza[index_pieza].lado; k++){

					  if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
						  pieza[index_pieza].matrizAux[pieza[index_pieza].lado - 1 - k][j] |= (0b1 << i);
					  }else{
						  pieza[index_pieza].matrizAux[pieza[index_pieza].lado - 1 - k][j] &= ~(0b1 << i); //nunca use esta expresion para setear ceros.
					  } //end if (pieza[index_pieza]->matriz[j][k] & (0b1 << i) )

				  } //end for x
			  } //end for y
		  } //end for z

		  //giro eje y
		  // NOTA: coordenandas de la matriz: matriz[y][z] |=  (0x01 << x);
		  for (int8_t j = 0; j < pieza[index_pieza].lado; j++ ){
			  for (int8_t k = 0; k < pieza[index_pieza].lado; k++){
				  for (int8_t i = 0; i < pieza[index_pieza].lado; i++){

					  if (pieza[index_pieza].matriz[j][k] & (0b1 << i) ){
						  pieza[index_pieza].matrizAux[j][pieza[index_pieza].lado - 1 - i] |= (0b1 << k );
					  }else{
						  pieza[index_pieza].matrizAux[j][pieza[index_pieza].lado - 1 - i] &= ~(0b1 << k ); //nunca use esta expresion para setear ceros.
					  } //end if (pieza[index_pieza].matriz[j][k] & (0b1 << i) )

				  } //end for x
			  } //end for y
		  } //end for z

		  //reasigno matrices
		  for (int8_t k = 0; k < pieza[index_pieza].lado; k++ ){
			  for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
				  pieza[index_pieza].matriz[j][k] = pieza[index_pieza].matrizAux[j][k];
			  } //fin for j
		  } //fin for k

		  //dibuja pieza (sola, fuera del cubo)
		  index_texto = 0;
		  for (int8_t j = 0; j < pieza[index_pieza].lado; j++){
			  for (int8_t i = 0; i < pieza[index_pieza].lado; i++){
				  if (pieza[index_pieza].matriz[j][i] & (0b1 << rx_j) ){
					  texto[index_texto] = '@';
				  }else{
					  texto[index_texto] = '_';
				  } //fin if
				  index_texto++;
			  } //fin for i
			  texto[index_texto] = '\n';
			  index_texto++;
		  } //fin for j

		  texto[index_texto] = '\n';
		  index_texto++;
*/

		  //dibuja capa del cubo (con pieza si se encuentra)
		  index_texto = 0;
		  for (int8_t j = 0; j < 8; j++){
			  for (int8_t i = 0; i < 8; i++){
				  if (cube[j][rx_k] & (0b1 << i) ){
					  texto[index_texto] = '@';
				  }else{
					  texto[index_texto] = '_';
				  } //fin if
				  index_texto++;
			  } //fin for i
			  texto[index_texto] = '\n';
			  index_texto++;
		  } //fin for j

		  texto[index_texto] = '\n';
		  index_texto++;

		  //txtLenght = sprintf(texto, "valor: %d\n", pieza[index_pieza].matriz[rx_j][rx_k]);
		  HAL_UART_Transmit_IT(&huart1, (uint8_t*)texto, index_texto);
		  flag_uart = 0;
	  } //fin if flag_uart

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	flag_uart = 1;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	HAL_UART_Receive_IT(&huart1, rx, 3);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
