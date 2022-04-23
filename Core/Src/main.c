
#include "main.h"
#include "gpio.h"
#include "application.h"


void SystemClock_Config(void);


/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  
  HAL_Init();//在osal中进行systic初始化

  SystemClock_Config();

  MX_GPIO_Init();
  
  osal_main();//让OSAL接管调度
  //while (1)
  //{
    
  //}
  
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

   /* 配置主时钟内部电压调整率 */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
    
   /* 初始化HSI时钟            */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV4;     //使能HSI
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;       //使能LSE，供给RTC,LPTIM
	
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

   /* 配置系统时钟SYSCLK，HCLK，PCLK1，PCLK1时钟频率 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;           //AHB_CLK=SYSCLK/1=4MHz
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;            //APB1_CLK=AHB_CLK/1=4MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;            //APB2_CLK=AHB_CLK/1=4MHz

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_LPTIM1;//RCC_PERIPHCLK_USART1|
  //PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;           //配置Usart1时钟来自PCLK2
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;         //配置Lpuart1时钟来自PCLK1
  PeriphClkInit.LptimClockSelection = RCC_LPTIM1CLKSOURCE_LSE;              //配置Lptim时钟来自LSE
  
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void _Error_Handler(char *file, int line)
{
    NVIC_SystemReset();					//软复位
}

#ifdef USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
