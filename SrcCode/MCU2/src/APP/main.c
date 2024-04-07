#include "STD_TYPES.h"
#include "MRCC/RCC.h"
#include "MGPIO/GPIO.h"
#include "MNVIC/MNVIC.h"
#include "HLED/LED.h"
#include "HSWITCH/SWITCH.h"
#include "SERVICE/SCHED/SCHED.h"
#include "HCLCD/LCD.h"
#include "MUSART/USART.h"


#include <stdio.h>



USART_RXBuffer rx_buff = {
    .Channel = USART1,
    .Data=NULL,
    .Size = 1,
    .Index = 0
};


typedef struct {
    u8 Mode;
    u8 NormalModeOperation;
    u8 StopWatchOperation;
} RecType_tstr;

RecType_tstr ReceiveType;

void recieve_callback(void) {
    // Assuming rx_buff.Data is a pointer to an array of characters
    u8 received_char = *(rx_buff.Data); // Accessing the first character of the data buffer
    switch (received_char) {
    case 'N': /* Normal Mode */
        ReceiveType.Mode = 'N'; // Assigning a single character
        break;
    case 'S': /* StopWatch Mode */
        ReceiveType.Mode = 'S'; // Assigning a single character
        break;
    case 'K': /* Ok to save edit */
        ReceiveType.NormalModeOperation = 'K'; // Assigning a single character
        break;
    case '+': /* Increase time/date in Normal Mode */
        ReceiveType.NormalModeOperation = '+'; // Assigning a single character
        break;
    case '-': /* Decrease time/date in Normal Mode */
        ReceiveType.NormalModeOperation = '-'; // Assigning a single character
        break;
    case 'U': /* Move Up in Normal Mode */
        ReceiveType.NormalModeOperation = '^'; // Assigning a single character
        break;
    case 'D': /* Move Down in Normal Mode */
        ReceiveType.NormalModeOperation = 'D'; // Assigning a single character
        break;
    case 'R': /* Move Right in Normal Mode */
        ReceiveType.NormalModeOperation = '>'; // Assigning a single character
        break;
    case 'L': /* Move Left in Normal Mode */
        ReceiveType.NormalModeOperation = '<'; // Assigning a single character
        break;
    case 'T': /* Start/continue in StopWatch Mode */
        ReceiveType.StopWatchOperation = 'T'; // Assigning a single character
        break;
    case 'C': /* Stop in StopWatch Mode */
        ReceiveType.StopWatchOperation = 'C'; // Assigning a single character
        break;
    default:
        break;
    }
}

int main()
{
    MRCC_ControlClockAHP1Peripheral(RCC_AHB1_GPIOA,RCC_ENABLE);
    MRCC_ControlClockABP2Peripheral(RCC_APB2_USART1,RCC_ENABLE);
    MNVIC_EnableInterrupt(NVIC_IRQ_USART1);
    USART_strCfg_t Usart1_Config;
    Usart1_Config.BaudRate=9600;
    Usart1_Config.Oversampling=OVERSAMPLING_16;
    Usart1_Config.ParityControl=USART_DisableParity;
    Usart1_Config.pUartInstance=USART1;
    Usart1_Config.ReceiverControl=USART_EnableRX;
    Usart1_Config.RXNE_Enable=USART_Enable;
    Usart1_Config.Stop_bits=USART_1StopBit;
    Usart1_Config.TransmitterControl=USART_EnableTX;
    Usart1_Config.TXCE_Enable=USART_Enable;
    Usart1_Config.TXE_Enable=USART_Enable;
    Usart1_Config.UartEnable=USART_Enable;
    Usart1_Config.Word_bits=USART_8Bits;

    GPIO_Pin_tstr TX_PIN = 
	{
		.Mode = GPIO_MODE_AF_PP,
		.Speed = GPIO_SPEED_HIGH,
		.Port = GPIOA,
		.Pin = GPIO_PIN_9,
		.AF = GPIO_AF_USART1_2
	};

	GPIO_Pin_tstr RX_PIN = 
	{
		.Mode = GPIO_MODE_AF_PP_PU,
		.Speed = GPIO_SPEED_HIGH,
		.Port = GPIOA,
		.Pin = GPIO_PIN_10,
		.AF = GPIO_AF_USART1_2
	};

	MGPIO_InitPinAF(&TX_PIN);
	MGPIO_InitPinAF(&RX_PIN);
    HLED_Init();
	USART_Init(&Usart1_Config);
	USART_RegisterCallBackFunction(UART1_RECEIVE,recieve_callback);
	


	
    

    //u8 loc_r1=0;
	while (1)
	{
		USART_ReceiveBufferAsynchronous(&rx_buff);
		/* USART_SendBytesynchronous(USART1,'M');
		USART_SendBytesynchronous(USART1,'A');
		USART_SendBytesynchronous(USART1,'Y');
		USART_SendBytesynchronous(USART1,'A');
		USART_SendBytesynchronous(USART1,'D');
		USART_SendBytesynchronous(USART1,'A');
		USART_ReceiveBytesynchronous(USART1,&loc_r1);
		if(loc_r1=='1')
		{
			HLED_Toggle(LED_RED);
		}
		else if(loc_r1=='2')
		{
			HLED_Toggle(LED_RED2);
		}
		USART_SendBytesynchronous(USART1,'D');  */
		




	}

return 0;

}

// ----------------------------------------------------------------------------
