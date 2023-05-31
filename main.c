#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#define FCY 4000000ULL
#include <libpic30.h>
#include "app.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************


void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void ConvertADCVoltage ( unsigned int ) ;
extern void Hex2Dec ( unsigned char ) ;


APP_DATA appData = {
.messageLine1 = "Explorer 16 Demo" ,
.messageLine2 = "Press S4 to cont" ,
.messageTime = "Chess timer " ,
.messageADC = " "
} ;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{


/* Call the System Intialize routine*/
SYS_Initialize ( ) ;

/* Display welcome message */
LCD_PutString ( (char*) &appData.messageLine1[0] , sizeof (appData.messageLine1 ) - 1 ) ;
LCD_PutString ( (char*) &appData.messageLine2[0] , sizeof (appData.messageLine2 ) - 1 ) ;

/* wait here until switch S3 is pressed */
while (!BUTTON_IsPressed ( BUTTON_S4 )) ;

/*Initialize Timer*/
TIMER_SetConfiguration ( TIMER_CONFIGURATION_RTCC ) ;

/*Initialize ADC configure it as 10 bit interrupt driven mode*/
ADC_SetConfiguration ( ADC_CONFIGURATION_AUTO_SAMPLE_CONVERT ) ;


int time1 = 300;
bool count1 = false;
int time1M = 0;
int time1S = 0;
int time2 = 300;
bool count2 = false;
int time2M = 0;
int time2S = 0;
bool g1Lose = false;
bool g2Lose = false;
bool game = false;
unsigned int pot = 0;
/* Infinite Loop */
while ( 1 )
{
if(!g1Lose && !g2Lose ){
if ( appData.adc_lcd_update )
{
if(!game){
ConvertADCVoltage ( appData.temp1 ) ;
float w = (appData.adones-'0') + (appData.adtens-'0')*0.1f + (appData.adhunds-'0') * 0.01f;
float x = w/3.3;
int y = x * 100;
if(y < 33){
time1 = 300;
time2 = 300;
}
if(y < 66 && y > 33){
time1 = 180;
time2 = 180;
}
if(y > 66){
time1 = 60;
time2 = 60;
}
}
time1M = time1/60;
time1S = time1 - (time1M * 60);
time2M = time2/60;
time2S = time2 - (time2M * 60);
LCD_PutChar ( 'G' ) ;
LCD_PutChar ( 'r' ) ;
LCD_PutChar ( 'a' ) ;
LCD_PutChar ( 'c' ) ;
LCD_PutChar ( 'z' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( '1' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( 'G' ) ;
LCD_PutChar ( 'r' ) ;
LCD_PutChar ( 'a' ) ;
LCD_PutChar ( 'c' ) ;
LCD_PutChar ( 'z') ;
LCD_PutChar ( ' ') ;
LCD_PutChar ( '2' ) ;
LCD_PutChar ( time1M / 10 + '0' ) ;
LCD_PutChar ( time1M % 10 + '0' ) ;
LCD_PutChar ( ':' ) ;
LCD_PutChar ( time1S/10 + '0' ) ;
LCD_PutChar ( time1S % 10 + '0' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( time2M/10 + '0' ) ;
LCD_PutChar ( time2M % 10 + '0' ) ;
LCD_PutChar ( ':' ) ;
LCD_PutChar ( time2S/10 + '0' ) ;
LCD_PutChar ( time2S % 10 + '0' ) ;

if(BUTTON_IsPressed ( BUTTON_S3 )){
game = true;
count1 = true;
count2 = false;
}
if(count1 && time2 > 0){
time2 = time2 - 1;
__delay_ms(1000);
}
if(BUTTON_IsPressed ( BUTTON_S6 )){
game = true;
count1 = false;
count2 = true;
}
if(count2 && time1 > 0){
time1 = time1 - 1;
__delay_ms(1000);
}

}
if(time1 == 0){
if(!g1Lose){
LCD_ClearScreen();
LCD_PutString("Gracz1 przegral!", 16);
LCD_PutString("* Koniec czasu *", 16);
g1Lose=true;
}
}
if(time2 == 0){
if(!g2Lose){
LCD_ClearScreen();
LCD_PutString("Gracz2 przegral!", 16);
LCD_PutString("* Koniec czasu *", 16);
g2Lose=true;
}
}
}
}
}
/*******************************************************************************

Function:
void Update_LCD( void )

Summary:
Function to update LCD

Description:
This function will update the time on the LCD

Precondition:
None.

Parameters:
None.

Returns:
None.

Remarks:

*/
/******************************************************************************/
void Update_LCD ( void )
{
LCD_PutChar ( 'T' ) ;
LCD_PutChar ( 'i' ) ;
LCD_PutChar ( 'm' ) ;
LCD_PutChar ( 'e' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( appData.tens + 0x30 ) ;
LCD_PutChar ( appData.ones + 0x30 ) ;

Hex2Dec ( appData.minutes ) ;
LCD_PutChar ( ':' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( appData.tens + 0x30 ) ;
LCD_PutChar ( appData.ones + 0x30 ) ;

Hex2Dec ( appData.seconds ) ;
LCD_PutChar ( ':' ) ;
LCD_PutChar ( ' ' ) ;
LCD_PutChar ( appData.tens + 0x30 ) ;
LCD_PutChar ( appData.ones + 0x30 ) ;

}

/*******************************************************************************

Function:
void ConvertADCVoltage ( unsigned int )

Summary:
Function to convert ADC data into volts

Description:
This is the file for the Explorer 16 Dem that converts raw 10 bit ADC data
to volts suitable for the LCD display

Precondition:
None.

Parameters:
None.

Returns:
None.

Remarks:

*/
/******************************************************************************/

void ConvertADCVoltage ( unsigned int adc_conv_data )
{
/* reset values */
appData.adones = 0 ;
appData.adtens = 0 ;
appData.adhunds = 0 ;
appData.adthous = 0 ;

while ( adc_conv_data > 0 )
{
/* test for 1 volt or greater */
if ( adc_conv_data > ( ONE_VOLT - 1 ) )
{
/* increment 1 volt counter */
appData.adones++ ;

/* subtract 1 volt */
adc_conv_data -= ONE_VOLT ;
}


/* test for 0.1 volt */
else if ( adc_conv_data > ( ONE_TENTH_VOLT - 1 ) )
{
/* increment tenths */
if ( appData.adtens < 9 )
{
appData.adtens++ ;
}
else
{
/* tenths has rolled over */
appData.adones++ ;

/* so increment ones and reset tenths */
appData.adtens = 0 ;
}

adc_conv_data -= ONE_TENTH_VOLT ;
}

/* test for 0.01 volt */
else if ( adc_conv_data > ( ONE_HUNDREDTH_VOLT - 1 ) )
{
/* increment hundredths */
if ( appData.adhunds < 9 )
{
appData.adhunds++ ;
}
else
{
/* hundredths has rolled over */
appData.adtens++ ;

/* so increment tenths and reset hundredths */
appData.adhunds = 0 ;
}

adc_conv_data -= ONE_HUNDREDTH_VOLT ;
}

else if ( adc_conv_data <= ( ONE_HUNDREDTH_VOLT - 1 ) )
{
appData.adthous++ ;
adc_conv_data -- ;
}
}

appData.adones += 0x30 ;
appData.adtens += 0x30 ;
appData.adhunds += 0x30 ;
appData.adthous += 0x30 ;
}

/*******************************************************************************

Function:
void Hex2Dec ( unsigned char )

Summary:
Explorer 16 Demo Hex to Decimal Conversion File

Description:
This is the file for the Explorer 16 Dem that converts the hexadecimal data
into decimal format.

Precondition:
None.

Parameters:
None.

Returns:
None.

Remarks:

*/
/******************************************************************************/

void Hex2Dec ( unsigned char count )
{
/* reset values */
appData.hunds = 0 ;
appData.tens = 0 ;
appData.ones = 0 ;

while ( count >= 10 )
{

if ( count >= 200 )
{
count -= 200 ;
appData.hunds = 0x02 ;
}

if (count >= 100)
{
count -= 100 ;
appData.hunds++ ;
}

if (count >= 10 )
{
count -= 10 ;
appData.tens++ ;
}
}

appData.ones = count ;
}