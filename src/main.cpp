#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h7xx_hal.h"

#include "adc.h"
#include "dfsdm.h"
#include "fatfs.h"
#include "gpio.h"
#include "i2c.h"
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
void MPU_Config(void);
void MX_USB_HOST_Process(void);
extern UART_HandleTypeDef huart3;

int _write(int file, char *data, int len) {
  HAL_StatusTypeDef status =
      HAL_UART_Transmit(&huart3, (uint8_t *)data, len, 10);
  return (status == HAL_OK ? len : 0);
}

#ifdef __cplusplus
}
#endif

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main() {

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  // MX_I2C1_Init();
  // MX_USART2_UART_Init();
  // MX_ADC1_Init();
  // MX_ADC2_Init();
  // MX_TIM23_Init();
  // MX_TIM12_Init();
  // MX_TIM24_Init();
  // MX_DFSDM1_Init();
  // MX_SPI4_Init();
  /* USER CODE BEGIN 2 */
  MX_USART3_UART_Init();
  const char *data = "eof\r\n";
//  _write(0, (char *)data, 5);
//  HAL_UART_Transmit(&huart3, (uint8_t *)data, 5, 10);
  printf("init\r\n");

  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  printf("v.size() = %d\r\n", v.size());

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, _LED_00_Pin | _LED_01_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : _LED_00_Pin _LED_01_Pin */
  GPIO_InitStruct.Pin = _LED_00_Pin | _LED_01_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (true) {
    /* USER CODE END WHILE */
    // MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
//    HAL_GPIO_TogglePin(_LED_00_GPIO_Port, _LED_00_Pin);
//    HAL_GPIO_TogglePin(_LED_01_GPIO_Port, _LED_01_Pin);
////    setbuf(stdout, 0);
//    printf(".\r\n");
//    HAL_UART_Transmit(&huart3, (uint8_t *)data, 5, 10);
    HAL_Delay(100);
  }
  /* USER CODE END 3 */
}
