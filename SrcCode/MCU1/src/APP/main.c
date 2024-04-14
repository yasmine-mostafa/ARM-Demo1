/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

/*#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"*/

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace-impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
/*#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"*/


#include "Error.h"
#include "STD_TYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "LED_CFG.h"
#include "LED.h"
#include "SWITCH_CFG.h"
#include "SWITCH.h"
#include "NVIC.h"
#include "SYSTICK_CFG.h"
#include "SYSTICK.h"
#include "SERVICE/Includes/SCHED_CFG.h"
#include "SERVICE/Includes/SCHED.h"
#include "LCD_CFG.h"
#include "LCD.h"
#include "USART.h"
#include "Keypad.h"
#include "HUSART.h"

int
main(void)
{
	//RCC_EnablePeripheral(Bus_AHB1,PERIPHERAL_GPIOA);
	RCC_EnablePeripheral(Bus_AHB1,PERIPHERAL_GPIOB);
	//RCC_EnablePeripheral(Bus_APB2,PERIPHERAL_USART1);


/*
	GPIO_Config_t GPIO_UART_TX=
	{
			.Port=GPIO_PORTA,
			.Pin=GPIO_PIN9,
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

	GPIO_Config_t GPIO_UART_RX=
	{
			.Port=GPIO_PORTA,
			.Pin=GPIO_PIN10,
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

/*	USART_strCfg_t USART_Config =
	{
			.pUartInstance=USART1,
			.Stop_bits=USART_1StopBit,
			.Word_bits=USART_8Bits,
			.ParityControl=USART_DisableParity,
			.TransmitterControl=USART_EnableTX,
			.ReceiverControl=USART_EnableRX,
			.TXE_Enable=USART_Enable,
			.RXNE_Enable=USART_Enable,
			.TXCE_Enable=USART_Enable,
			.UartEnable=USART_Enable,
			.BaudRate=9600,
			.Oversampling=OVERSAMPLING_16
	};*/


	USART_Config_t USART_Config=
	{
		.USART_ID=USART1,
		.BaudRate=9600,
		.OverSampling=OVERSAMPLING_16,
		.WordLength=WORD_LENGTH_8,
		.ParityEnable=PARITY_DISABLED,
		.StopBits=STOP_BITS_1
	};

/*
	GPIO_InitPinAF(&GPIO_UART_TX,GPIO_AF_USART1_2);
	GPIO_InitPinAF(&GPIO_UART_RX,GPIO_AF_USART1_2);

	USART_Init(USART_Config);*/
	HUSART_Init(USART_Config);

	//STK_Init(CLK_AHB,MODE_ENABLE_INT);

	LCD_InitAsynch();

	LED_Init();
	KEYPAD_Init();


	LED_Init();
	SCHED_Init();
	//NVIC_EnableIRQ(IRQ_USART1);
	SCHED_Start();
}

//#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
