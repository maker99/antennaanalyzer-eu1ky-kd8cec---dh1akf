/*
 *   (c) Yury Kuchura
 *   kuchura@gmail.com
 *
 *   This code can be used on terms of WTFPL Version 2 (http://www.wtfpl.net/).
 */

#ifndef _MAINWND_H_
#define _MAINWND_H_


#include <ctype.h>
#include "main.h"

void MainWnd(void);
// static char    fileNames[13][13];  // unused in mainwnd
// extern uint16_t  FileNo;           // unused 
volatile int   Page;
// static uint32_t date, time; // unused
uint32_t RTCpresent;
volatile int NoDate;
ADC_HandleTypeDef Adc3Handle;
#endif
