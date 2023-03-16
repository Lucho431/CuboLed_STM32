/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "74_HC595_SPI_lfs.h"
#include "botones_lfs.h"
#include "menu_cubo.h"
#include "blockOut.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	POS_X = 0,
	NEG_X,
	POS_Z,
	NEG_Z,
	POS_Y,
	NEG_Y,
}T_POS;

typedef enum{
	RAIN = 0,
	PLANE_BOING,
	SEND_VOXELS,
	WOOP_WOOP,
	CUBE_JUMP,
	FIREWORKS,
	GLOW,
	TEXT,
	LIT,
	TOTAL_EFFECTS,
}T_EFFECT;

typedef enum{
	NEW_FW,
	RISING_ROCKET,
	EXPLODING,
	FALLING,
}T_FW_STATUS;

typedef struct{
	int8_t partX;
	int8_t partY;
	int8_t partZ;
	int8_t velX;
	int8_t velY;
	int8_t velZ;
	int8_t acelZ;
	uint8_t resting;
} T_FW_PARTICLE;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

#define RAIN_TIME 0x8FFC
#define PLANE_BOING_TIME 0x8FFC
#define SEND_VOXELS_TIME 0x8FFC
#define WOOP_WOOP_TIME 0x8FFC
#define CUBE_JUMP_TIME 0x7FFF
#define GLOW_TIME 0x8FFC
#define TEXT_TIME 0x8FFC
#define CLOCK_TIME 0x8FFC
#define FIREWORK_TIME 0x5FFC
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//caracteres
uint8_t characters[10][8] = {
  {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C}, //0
  {0x10, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x3C}, //1
  {0x3C, 0x42, 0x40, 0x40, 0x3C, 0x02, 0x02, 0x7E}, //2
  {0x3C, 0x40, 0x40, 0x3C, 0x40, 0x40, 0x42, 0x3C}, //3
  {0x22, 0x22, 0x22, 0x22, 0x7E, 0x20, 0x20, 0x20}, //4
  {0x7E, 0x02, 0x02, 0x3E, 0x40, 0x40, 0x42, 0x3C}, //5
  {0x3C, 0x02, 0x02, 0x3E, 0x42, 0x42, 0x42, 0x3C}, //6
  {0x3C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40}, //7
  {0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x3C}, //8
  {0x3C, 0x42, 0x42, 0x42, 0x3C, 0x40, 0x40, 0x3C}, //9
};

//variables cubo
uint8_t cube[8][8];
uint8_t cube_vector[9];
uint8_t cube_level = 0;
T_EFFECT currentEffect = FIREWORKS;

uint8_t flag_nextLevel = 0;

uint16_t timer;

uint64_t randomTimer;
uint16_t randomSeed;

uint8_t loading;

//variables controles
uint8_t flag_tim3; //cada 10 ms.
uint8_t antiRebote = 1;

//variables aurt
uint8_t rxChar;
uint8_t flag_uart = 0;
extern char entradaJoystick;

//variables planeBoing()
uint8_t planePosition = 0;
uint8_t planeDirection = 0;
uint8_t looped = 0;

//variables sendVoxels()
uint8_t selX = 0;
uint8_t selY = 0;
uint8_t selZ = 0;
uint8_t sendDirection = 0;
uint8_t sending = 0;

//variables woopWoop()
uint8_t cubeSize = 0;
uint8_t cubeExpanding = 1;

//variables cubeJump()
uint8_t xPos;
uint8_t yPos;
uint8_t zPos;

//variables glow()
uint8_t glowing;
uint16_t glowCount = 0;

//variables text()
uint8_t charCounter = 0;
uint8_t charPosition = 0;

//variables fireWork()
uint8_t exploded;
T_FW_STATUS statusFireWork = NEW_FW;
uint8_t rocketX = 0;
uint8_t rocketY = 0;
uint8_t rocketZ = 0;
uint8_t numParticles;
T_FW_PARTICLE particle[40];
uint8_t deadParticles = 0;
uint8_t explocionCicle = 2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void renderCube (void);

void clearCube(void);
void drawCube(uint8_t, uint8_t, uint8_t, uint8_t);
void shift(uint8_t);
void setVoxel(uint8_t, uint8_t, uint8_t);
uint8_t getVoxel(uint8_t, uint8_t, uint8_t);
void clearVoxel(uint8_t, uint8_t, uint8_t);
void setPlane(uint8_t, uint8_t);
void rain(void);
void planeBoing(void);
void sendVoxels(void);
void woopWoop(void);
void cubeJump(void);
void fireWork(void);
void glow(void);
void text(char[], uint8_t);
void lit(void);
void lightCube(void);
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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  spi_74HC595_init(&hspi1, OUT_STORE_GPIO_Port, OUT_STORE_Pin);

  loading = 1;
  randomTimer = 0;
//  currentEffect = RAIN;

  HAL_ADC_Start(&hadc1);
  randomSeed = (uint16_t) HAL_ADC_GetValue(&hadc1);
  srand(randomSeed);
  HAL_ADC_Stop(&hadc1);
  HAL_GPIO_WritePin(OUT_LED1_GPIO_Port, OUT_LED1_Pin, 0); //led verde: on
  HAL_GPIO_WritePin(OUT_LED2_GPIO_Port, OUT_LED2_Pin, 1); //led rojo: off
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);

  HAL_TIM_Base_Start_IT(&htim2); // frecuencia de refresco
  HAL_TIM_Base_Start_IT(&htim3); // sincronizmo (10 * ms)

  HAL_UART_Receive_IT(&huart1, &rxChar, 1);

  start_menu();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  update_teclas();
	  check_menu();

	  if (flag_tim3 != 0){
		  if (antiRebote != 0){ //para leer cada 20 ms.
			  antiRebote--;
		  }else{
			  lecturaTeclas();

			  antiRebote = 1;
		  } //end if antiRebote

		  if (flag_uart != 0){

			  entradaJoystick = (char)rxChar;
			  HAL_UART_Receive_IT(&huart1, &rxChar, 1);
			  flag_uart = 0;
		  } //end if flag_uart

		  flag_tim3 = 0;
	  } //end if flag_tim3

	  randomTimer++;

	  if (getStatBoton(IN_UP) == FALL){ //UP
		  clearCube();
		  loading = 1;
		  timer = 0;
		  currentEffect++;
		  if (currentEffect == TOTAL_EFFECTS) {
			  currentEffect = 0;
		  }
		  srand(randomTimer);
		  randomTimer = 0;
		  HAL_GPIO_WritePin(OUT_LED1_GPIO_Port, OUT_LED1_Pin, 1); //led verde: off
		  HAL_GPIO_WritePin(OUT_LED2_GPIO_Port, OUT_LED2_Pin, 0); //led rojo: on
		  HAL_Delay(500);
		  HAL_GPIO_WritePin(OUT_LED1_GPIO_Port, OUT_LED1_Pin, 0); //led verde: on
		  HAL_GPIO_WritePin(OUT_LED2_GPIO_Port, OUT_LED2_Pin, 1); //led rojo: off
	  } //end if getStatBoton...

	  if (getStatBoton(IN_DOWN) == FALL){ //DOWN
		  clearCube();
		  loading = 1;
		  timer = 0;
		  currentEffect--;
		  if (currentEffect != 0) {
			  currentEffect--;
		  }else{
			  currentEffect = TOTAL_EFFECTS - 1;
		  }
		  srand(randomTimer);
		  randomTimer = 0;
		  HAL_GPIO_WritePin(OUT_LED1_GPIO_Port, OUT_LED1_Pin, 1); //led verde: off
		  HAL_GPIO_WritePin(OUT_LED2_GPIO_Port, OUT_LED2_Pin, 0); //led rojo: on
		  HAL_Delay(500);
		  HAL_GPIO_WritePin(OUT_LED1_GPIO_Port, OUT_LED1_Pin, 0); //led verde: on
		  HAL_GPIO_WritePin(OUT_LED2_GPIO_Port, OUT_LED2_Pin, 1); //led rojo: off
	  } //end if getStatBoton...


	  switch (currentEffect) {
		  case RAIN: rain(); break;
		  case PLANE_BOING: planeBoing(); break;
		  case SEND_VOXELS: sendVoxels(); break;
		  case WOOP_WOOP: woopWoop(); break;
		  case CUBE_JUMP: cubeJump(); break;
		  case FIREWORKS: fireWork(); break;
		  case GLOW: glow(); break;
		  case TEXT: text("0123456789", 10); break;
		  case LIT: lit(); break;
		  default: cubeJump();
	  } //end switch currentEffect

//	  drawCube(0, 0, 0, 8);
//	  fireWork();

	  if (flag_nextLevel != 0){
		  renderCube();
		  flag_nextLevel = 0;
	  }

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void renderCube (void) {
 /* for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(SS, LOW);
    SPI.transfer(0x01 << i);
    for (uint8_t j = 0; j < 8; j++) {
      SPI.transfer(cube[i][j]);
    }
    digitalWrite(SS, HIGH);
  }*/

	cube_vector[0] = (uint8_t) (0x01 << cube_level);

	for (uint8_t j = 0; j < 8; j++) {
		cube_vector[j+1] = cube[cube_level][j];
	} //end for j

	spi_74HC595_Transmit(cube_vector, sizeof(cube_vector));
	cube_level++;
	if (cube_level == 8){
		cube_level = 0;
	}
	__NOP();

} //end renderCube()

void rain (void) {
  if (loading != 0) {
    clearCube();
    loading = 0;
  }
  timer++;
  if (timer > RAIN_TIME) {
    timer = 0;
    shift(NEG_Y);
    uint8_t numDrops = rand() % 5;
    for (uint8_t i = 0; i < numDrops; i++) {
      setVoxel(rand() % 8, 7, rand() % 8);
    }
  }
} //end rain()

void planeBoing (void) {
  if (loading) {
    clearCube();
    uint8_t axis = rand() % 3;
    planePosition = (rand() % 2) * 7;
    setPlane(axis, planePosition);
    if (axis == XAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_X;
      } else {
        planeDirection = NEG_X;
      }
    } else if (axis == YAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_Y;
      } else {
        planeDirection = NEG_Y;
      }
    } else if (axis == ZAXIS) {
      if (planePosition == 0) {
        planeDirection = POS_Z;
      } else {
        planeDirection = NEG_Z;
      }
    }
    timer = 0;
    looped = 0;
    loading = 0;
  }

  timer++;
  if (timer > PLANE_BOING_TIME) {
    timer = 0;
    shift(planeDirection);
    if (planeDirection % 2 == 0) {
      planePosition++;
      if (planePosition == 7) {
        if (looped != 0) {
          loading = 1;
        } else {
          planeDirection++;
          looped = 1;
        }
      }
    } else {
      planePosition--;
      if (planePosition == 0) {
        if (looped != 0) {
          loading = 1;
        } else {
          planeDirection--;
          looped = 1;
        }
      }
    }
  }
} //end planeBoing()

void sendVoxels() {
  if (loading != 0) {
    clearCube();
    for (uint8_t x = 0; x < 8; x++) {
      for (uint8_t z = 0; z < 8; z++) {
        setVoxel(x, (rand() % 2) * 7, z);
      }
    }
    loading = 0;
  }

  timer++;
  if (timer > SEND_VOXELS_TIME) {
    timer = 0;
    if (!sending) {
      selX = rand() % 8;
      selZ = rand() % 8;
      if (getVoxel(selX, 0, selZ)) {
        selY = 0;
        sendDirection = POS_Y;
      } else if (getVoxel(selX, 7, selZ)) {
        selY = 7;
        sendDirection = NEG_Y;
      }
      sending = 1;
    } else {
      if (sendDirection == POS_Y) {
        selY++;
        setVoxel(selX, selY, selZ);
        clearVoxel(selX, selY - 1, selZ);
        if (selY == 7) {
          sending = 0;
        }
      } else {
        selY--;
        setVoxel(selX, selY, selZ);
        clearVoxel(selX, selY + 1, selZ);
        if (selY == 0) {
          sending = 0;
        }
      }
    }
  }
} //end sendVoxels()

void woopWoop() {
  if (loading) {
    clearCube();
    cubeSize = 2;
    cubeExpanding = 1;
    loading = 0;
  }

  timer++;
  if (timer > WOOP_WOOP_TIME) {
    timer = 0;
    if (cubeExpanding) {
      cubeSize += 2;
      if (cubeSize == 8) {
        cubeExpanding = 0;
      }
    } else {
      cubeSize -= 2;
      if (cubeSize == 2) {
        cubeExpanding = 1;
      }
    }
    clearCube();
    drawCube(4 - cubeSize / 2, 4 - cubeSize / 2, 4 - cubeSize / 2, cubeSize);
  }
} //end woopWoop()

void glow() {
  if (loading) {
    clearCube();
    glowCount = 0;
    glowing = 1;
    loading = 0;
  }

  timer++;
  if (timer > GLOW_TIME) {
    timer = 0;
    if (glowing) {
      if (glowCount < 448) {
        do {
        	selX = rand() % 8;
        	selY = rand() % 8;
        	selZ = rand() % 8;
        } while (getVoxel(selX, selY, selZ));
        setVoxel(selX, selY, selZ);
        glowCount++;
      } else if (glowCount < 512) {
        lightCube();
        glowCount++;
      } else {
        glowing = 0;
        glowCount = 0;
      }
    } else {
      if (glowCount < 448) {
        do {
          selX = rand() % 8;
          selY = rand() % 8;
          selZ = rand() % 8;
        } while (!getVoxel(selX, selY, selZ));
        clearVoxel(selX, selY, selZ);
        glowCount++;
      } else {
        clearCube();
        glowing = 1;
        glowCount = 0;
      }
    }
  }
} //end glow()

void text(char string[], uint8_t len) {
  if (loading) {
    clearCube();
    charPosition = -1;
    charCounter = 0;
    loading = 0;
  }
  timer++;
  if (timer > TEXT_TIME) {
    timer = 0;

    shift(NEG_Z);
    charPosition++;

    if (charPosition == 7) {
      charCounter++;
      if (charCounter > len - 1) {
        charCounter = 0;
      }
      charPosition = 0;
    }

    if (charPosition == 0) {
      for (uint8_t i = 0; i < 8; i++) {
        cube[i][0] = characters[string[charCounter] - '0'][i];
      }
    }
  }
} //end text()

void fireWork (void){

	if (loading != 0) {
	    clearCube();
	    loading = 0;
	}

	timer++;
	if (timer > FIREWORK_TIME){

		timer = 0;
		clearCube();

		switch (statusFireWork){
			case NEW_FW:
				rocketX = 2 + (rand() % 4); //between 2 and 5.
				rocketY = 2 + (rand() % 4); //between 2 and 5.
				rocketZ = 0;
				setVoxel(rocketX, rocketZ, rocketY);
				statusFireWork = RISING_ROCKET;
			break;
			case RISING_ROCKET:
				rocketZ++;
				if (rocketZ > 4){
					statusFireWork = EXPLODING;
//					statusFireWork = NEW_FW;
					deadParticles = 0;
					explocionCicle = 0;
					numParticles = (30 + (rand() % 10) ); //num of particles between 30 and 40.
					for(uint8_t i = 0 ; i < numParticles; i++){
						particle[i].partX = rocketX;
						particle[i].partY = rocketY;
						particle[i].partZ = rocketZ;
						particle[i].velX = -2 + (rand() % 5);
						particle[i].velY = -2 + (rand() % 5);
						particle[i].velZ = -1 + (rand() % 3);
						particle[i].resting = 0;
					}
				}
				setVoxel(rocketX, rocketZ, rocketY);
			break;
			case EXPLODING:
				explocionCicle++;
				for(uint8_t i = 0 ; i < numParticles; i++){
					particle[i].partX += particle[i].velX;
					particle[i].partY += particle[i].velY;
					particle[i].partZ += particle[i].velZ;

					if(particle[i].partX < (rocketX - explocionCicle)) particle[i].partX = (rocketX - explocionCicle);
					if(particle[i].partY < (rocketY - explocionCicle)) particle[i].partY = (rocketY - explocionCicle);
					if(particle[i].partZ < (rocketZ - explocionCicle)) particle[i].partZ = (rocketZ - explocionCicle);

					if(particle[i].partX > (rocketX + explocionCicle)) particle[i].partX = (rocketX + explocionCicle);
					if(particle[i].partY > (rocketY + explocionCicle)) particle[i].partY = (rocketY + explocionCicle);
					if(particle[i].partZ > (rocketZ + explocionCicle)) particle[i].partZ = (rocketZ + explocionCicle);

					particle[i].velX = -2 + (rand() % 5);
					particle[i].velY = -2 + (rand() % 5);
					particle[i].velZ = rand() % 2;

					if(particle[i].partZ >= 0){
						if(particle[i].partZ < 8)
							setVoxel(particle[i].partX, particle[i].partZ, particle[i].partY);
					}else{
						deadParticles++;
					}
				}

				if (explocionCicle == 3){
					statusFireWork = FALLING;
				}

			break;
			case FALLING:
				for(uint8_t i = 0 ; i < numParticles; i++){
//					particle[i].velZ--;

//					particle[i].velX--;
//					particle[i].velY--;
//					particle[i].velZ--;

					particle[i].partX += particle[i].velX;
					particle[i].partY += particle[i].velY;
					particle[i].partZ += particle[i].velZ;

					particle[i].velX = 0;
					particle[i].velY = 0;
//					particle[i].velZ = 0;
					if (particle[i].velZ > -1) particle[i].velZ--;

					if(particle[i].partX < 0) particle[i].partX = 0;
					if(particle[i].partY < 0) particle[i].partY = 0;
//					if(particle[i].partZ < 0) particle[i].partZ = 0;
					if(particle[i].partX > 7) particle[i].partX = 7;
					if(particle[i].partY > 7) particle[i].partY = 7;
//					if(particle[i].partZ > 7) particle[i].partZ = 7;

					if(particle[i].partZ >= 0){
						if(particle[i].partZ < 8)
							setVoxel(particle[i].partX, particle[i].partZ, particle[i].partY);
					}else{

						if (particle[i].resting < 6){
							setVoxel(particle[i].partX, 0, particle[i].partY);
							particle[i].resting++;
						}else{
							deadParticles++;
						}
					}

				} //end for i

				if (deadParticles >= numParticles)
					statusFireWork = NEW_FW;
			break;
			default:
			break;
		} //end switch (statusFireWork)
	} //end if (timer > FIREWORK_TIME)
} //end fireWork ()

void lit() {
  if (loading) {
    clearCube();
    for(uint8_t i=0; i<8; i++) {
      for(uint8_t j=0; j<8; j++) {
        cube[i][j] = 0xFF;
      }
    }
    loading = 0;
  }
} //end lit()

void cubeJump() {
  if (loading) {
    clearCube();
    xPos = (rand() % 2) * 7;
    yPos = (rand() % 2) * 7;
    zPos = (rand() % 2) * 7;
    cubeSize = 8;
    cubeExpanding = 0;
    loading = 0;
  }

  timer++;
  if (timer > CUBE_JUMP_TIME) {
    timer = 0;
    clearCube();
    if (xPos == 0 && yPos == 0 && zPos == 0) {
      drawCube(xPos, yPos, zPos, cubeSize);
    } else if (xPos == 7 && yPos == 7 && zPos == 7) {
      drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 0 && zPos == 0) {
      drawCube(xPos + 1 - cubeSize, yPos, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 7 && zPos == 0) {
      drawCube(xPos, yPos + 1 - cubeSize, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 0 && zPos == 7) {
      drawCube(xPos, yPos, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 7 && zPos == 0) {
      drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos, cubeSize);
    } else if (xPos == 0 && yPos == 7 && zPos == 7) {
      drawCube(xPos, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
    } else if (xPos == 7 && yPos == 0 && zPos == 7) {
      drawCube(xPos + 1 - cubeSize, yPos, zPos + 1 - cubeSize, cubeSize);
    }
    if (cubeExpanding) {
      cubeSize++;
      if (cubeSize == 8) {
        cubeExpanding = 0;
        xPos = (rand() % 2) * 7;
        yPos = (rand() % 2) * 7;
        zPos = (rand() % 2) * 7;
      }
    } else {
      cubeSize--;
      if (cubeSize == 1) {
        cubeExpanding = 1;
      }
    }
  }
} //end cubeJump()


void setVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] |= (0x01 << x);
}

void clearVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] ^= (0x01 << x);
}

uint8_t getVoxel(uint8_t x, uint8_t y, uint8_t z) {
  return (cube[7 - y][7 - z] & (0x01 << x)) == (0x01 << x);
}

void setPlane(uint8_t axis, uint8_t i) {
  for (uint8_t j = 0; j < 8; j++) {
    for (uint8_t k = 0; k < 8; k++) {
      if (axis == XAXIS) {
        setVoxel(i, j, k);
      } else if (axis == YAXIS) {
        setVoxel(j, i, k);
      } else if (axis == ZAXIS) {
        setVoxel(j, k, i);
      }
    }
  }
}

void shift(uint8_t dir) {

  switch (dir){
	  case POS_X:
		for (uint8_t y = 0; y < 8; y++) {
			for (uint8_t z = 0; z < 8; z++) {
				cube[y][z] = cube[y][z] << 1;
			}
		}
	  break;
	  case NEG_X:
		for (uint8_t y = 0; y < 8; y++) {
		  for (uint8_t z = 0; z < 8; z++) {
			cube[y][z] = cube[y][z] >> 1;
		  }
		}
	  break;
	  case POS_Y:
		for (uint8_t y = 1; y < 8; y++) {
		  for (uint8_t z = 0; z < 8; z++) {
			cube[y - 1][z] = cube[y][z];
		  }
		}
		for (uint8_t i = 0; i < 8; i++) {
		  cube[7][i] = 0;
		}
	  break;
	  case NEG_Y:
		for (uint8_t y = 7; y > 0; y--) {
		  for (uint8_t z = 0; z < 8; z++) {
			cube[y][z] = cube[y - 1][z];
		  }
		}
		for (uint8_t i = 0; i < 8; i++) {
		  cube[0][i] = 0;
		}
	  break;
	  case POS_Z:
		for (uint8_t y = 0; y < 8; y++) {
		  for (uint8_t z = 1; z < 8; z++) {
			cube[y][z - 1] = cube[y][z];
		  }
		}
		for (uint8_t i = 0; i < 8; i++) {
		  cube[i][7] = 0;
		}
	  break;
	  case NEG_Z:
		for (uint8_t y = 0; y < 8; y++) {
		  for (uint8_t z = 7; z > 0; z--) {
			cube[y][z] = cube[y][z - 1];
		  }
		}
		for (uint8_t i = 0; i < 8; i++) {
		  cube[i][0] = 0;
		}
	  break;
	  default:
	  break;
  } //end switch dir

} //end shift()

void drawCube(uint8_t x, uint8_t y, uint8_t z, uint8_t s) {
  for (uint8_t i = 0; i < s; i++) {
    setVoxel(x, y + i, z);
    setVoxel(x + i, y, z);
    setVoxel(x, y, z + i);
    setVoxel(x + s - 1, y + i, z + s - 1);
    setVoxel(x + i, y + s - 1, z + s - 1);
    setVoxel(x + s - 1, y + s - 1, z + i);
    setVoxel(x + s - 1, y + i, z);
    setVoxel(x, y + i, z + s - 1);
    setVoxel(x + i, y + s - 1, z);
    setVoxel(x + i, y, z + s - 1);
    setVoxel(x + s - 1, y, z + i);
    setVoxel(x, y + s - 1, z + i);
  }
} //end drawCube()

void lightCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0xFF;
    }
  }
} //end lightCube()

void clearCube(void) {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0;
    }
  }
} //end clearCube()


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		flag_nextLevel = 1;
	}
	if(htim->Instance == TIM3){
		flag_tim3 = 1;
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	flag_uart = 1;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
