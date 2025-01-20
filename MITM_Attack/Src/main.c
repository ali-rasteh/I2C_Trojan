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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

// Define the transfer direction variable to be used in the I2C callback funcitons
__IO uint32_t     Transfer_Direction = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Defining I2C_page_size for the i2c transactions
#define I2C_page_size	32

// Memory is the temporary memory keeping the values send and received on the I2C
uint8_t memory[I2C_page_size];
// offset is the offset of the register to be written in temporary memory
uint8_t offset = 0;
// eeprom_page_address is the address of the EEPROM page to be read or written
uint16_t eeprom_page_address = 0; 	// index of current RAM cell
// address_bytes is a flag that shows the transaction is writing the EEPROM address bytes
uint8_t address_bytes = 1;	// index of the memory address field in I2C transaction
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

// These are the variables used for reading and writing with HAL APIs
uint16_t I2C_DevAddress;
uint16_t I2C_MemAddress;
uint16_t I2C_MemAddSize;
uint8_t I2C_pData_write[I2C_page_size];
uint8_t I2C_pData_read[I2C_page_size];
uint16_t I2C_Size;
uint32_t I2C_Timeout;
HAL_StatusTypeDef I2C_result;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
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

	uint16_t i;

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */

  // Calling HAL_I2C_EnableListen_IT to enable the interrupt for the corresponding I2C line
  if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK)
  {
	  /* Transfer error in reception process */
	  Error_Handler();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 160;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void debugPrint(UART_HandleTypeDef *huart, char _out[]){
	HAL_UART_Transmit(huart, (uint8_t *) _out, strlen(_out), 10);
}

void debugPrintln(UART_HandleTypeDef *huart, char _out[]){
	HAL_UART_Transmit(huart, (uint8_t *) _out, strlen(_out), 10);
	char newline[2] = "\r\n";
	HAL_UART_Transmit(huart, (uint8_t *) newline, 2, 10);
}

/**
  * @brief  Tx Transfer completed callback.
  * @param  I2cHandle: I2C handle.
  * @retval None
*/

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
	//debugPrint(&huart2,"HAL_I2C_SlaveTxCpltCallback\r\n");
	// increasing offset for the next transaction
	offset++;
	HAL_I2C_Slave_Seq_Transmit_IT(I2cHandle, &memory[offset], 1, I2C_NEXT_FRAME);
}


/**
  * @brief  Rx Transfer completed callback.
  * @param  I2cHandle: I2C handle
  * @retval None
*/
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
	//debugPrint(&huart2,"HAL_I2C_SlaveRxCpltCallback\r\n");

	if(address_bytes == 1) {
		// setting address_bytes to zero to get the data bytes in the next transactions
		address_bytes = 0;
	} else {
		// increasing offset for the next transaction
		offset++;
	}
	HAL_I2C_Slave_Seq_Receive_IT(I2cHandle, &memory[offset], 1, I2C_NEXT_FRAME);

	// if the offset is 31 it seems that we have received all the values for this page so we go to write the values to the EEPROM
	if (offset == 31){
		I2C_DevAddress = 0xA0;
		I2C_MemAddSize = I2C_MEMADD_SIZE_16BIT;
		I2C_Size = I2C_page_size;
		//I2C_Timeout = HAL_MAX_DELAY;
		I2C_Timeout = 10;

		// if the eeprom_page_address is 0x0200 we should discard the write as the HW wants!
		if (eeprom_page_address != 0x0200){
			I2C_result = HAL_I2C_Mem_Write(&hi2c2, I2C_DevAddress, eeprom_page_address, I2C_MemAddSize, memory, I2C_Size, I2C_Timeout);
		}
	}
}



/**
  * @brief  Slave Address Match callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  TransferDirection: Master request Transfer Direction (Write/Read), value of @ref I2C_XferOptions_definition
  * @param  AddrMatchCode: Address Match Code
  * @retval None
*/
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	// address is used to get the real page address of EEPROM
	uint8_t address[2];

	//debugPrint(&huart2,"HAL_I2C_AddrCallback\r\n");

  Transfer_Direction = TransferDirection;
  if (Transfer_Direction == I2C_DIRECTION_TRANSMIT)
  {
	  /*##- Start the transmission process #####################################*/
	  /* While the I2C in reception process, user can transmit data*/
	  // Transmitting the data from memory to I2C
	  I2C_DevAddress = 0xA0;
	  I2C_MemAddSize = I2C_MEMADD_SIZE_16BIT;
	  I2C_Size = I2C_page_size;
	  //I2C_Timeout = HAL_MAX_DELAY;
	  I2C_Timeout = 10;

	  // if the eeprom_page_address is 0x0200 we should discard the read process and send another value given by the HW!
	  if (eeprom_page_address != 0x0200){
		  // Reading the value at eeprom_page_address to return on the slave I2C
		  I2C_result = HAL_I2C_Mem_Read(&hi2c2, I2C_DevAddress, eeprom_page_address, I2C_MemAddSize, memory, I2C_Size, I2C_Timeout);
	  }
	  else{
		  // Defining the constant value at 0x0200 address
		  memory[0] = 0x09;
		  memory[1] = 0xF9;
		  memory[2] = 0x11;
		  memory[3] = 0x02;
		  memory[4] = 0x9D;
		  memory[5] = 0x74;
		  memory[6] = 0xE3;
		  memory[7] = 0x5B;
		  memory[8] = 0xD8;
		  memory[9] = 0x41;
		  memory[10] = 0x56;
		  memory[11] = 0xC5;
		  memory[12] = 0x63;
		  memory[13] = 0x56;
		  memory[14] = 0x88;
		  memory[15] = 0xC0;
		  memory[16] = 0x09;
		  memory[17] = 0xF9;
		  memory[18] = 0x11;
		  memory[19] = 0x02;
		  memory[20] = 0x9D;
		  memory[21] = 0x74;
		  memory[22] = 0xE3;
		  memory[23] = 0x5B;
		  memory[24] = 0xD8;
		  memory[25] = 0x41;
		  memory[26] = 0x56;
		  memory[27] = 0xC5;
		  memory[28] = 0x63;
		  memory[29] = 0x56;
		  memory[30] = 0x88;
		  memory[31] = 0xC0;
	  }

	  // Start sending the value on the I2C slave line
	  if (HAL_I2C_Slave_Seq_Transmit_IT(hi2c, &memory[offset], 1, I2C_NEXT_FRAME) != HAL_OK)
	  {
		/* Transfer error in transmission process */
		Error_Handler();
	  }
  }
  else
  {
	  if(address_bytes == 1){
		  // if address_bytes then we should get the address of the page of the EEPROM
		  /*##- Put I2C peripheral in reception process ###########################*/
		  if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, &address[0], 2, I2C_NEXT_FRAME) != HAL_OK)
		  {
			/* Transfer error in reception process */
			Error_Handler();
		  }
		  // Making eeprom_page_address from the received address
		  eeprom_page_address = ((uint16_t)(address[0]))<<8+address[1];
	  }
	  else {
		  // Receiving the data and putting it into the memory
		  if (HAL_I2C_Slave_Seq_Receive_IT(hi2c, &memory[offset], 1, I2C_NEXT_FRAME) != HAL_OK)
		  {
			/* Transfer error in reception process */
			Error_Handler();
		  }
	  }
  }

}

/**
  * @brief  Listen Complete callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	//debugPrint(&huart2,"HAL_I2C_ListenCpltCallback\r\n");

	// resetting the value of address_bytes
	address_bytes = 1;
	// Resetting the value of offset to zero for the future transactions
	offset = 0;
	// Enabling the interrupt again
	if(HAL_I2C_EnableListen_IT(hi2c) != HAL_OK)
	{
		/* Transfer error in reception process */
		Error_Handler();
	}
}

/**
  * @brief  I2C error callbacks.
  * @param  I2cHandle: I2C handle
  * @retval None
  */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  /** Error_Handler() function is called when error occurs.
    * 1- When Slave doesn't acknowledge its address, Master restarts communication.
    * 2- When Master doesn't acknowledge the last data transferred, Slave doesn't care in this example.
    */
  if (HAL_I2C_GetError(I2cHandle) != HAL_I2C_ERROR_AF)
  {
    Error_Handler();
  }
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
