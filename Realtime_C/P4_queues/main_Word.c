{\rtf1\ansi\deff0\deftab480

{\fonttbl
{\f000 Courier New;}
{\f001 Courier New;}
{\f002 Courier New;}
{\f003 Courier New;}
{\f004 Courier New;}
{\f005 Courier New;}
{\f006 Courier New;}
{\f007 Courier New;}
{\f008 Courier New;}
{\f009 Courier New;}
{\f010 Courier New;}
{\f011 Courier New;}
}

{\colortbl
\red000\green000\blue000;
\red255\green255\blue255;
\red000\green128\blue000;
\red255\green255\blue255;
\red000\green128\blue000;
\red255\green255\blue255;
\red255\green128\blue000;
\red255\green255\blue255;
\red000\green000\blue255;
\red255\green255\blue255;
\red128\green128\blue128;
\red255\green255\blue255;
\red128\green064\blue000;
\red255\green255\blue255;
\red000\green000\blue128;
\red255\green255\blue255;
\red000\green000\blue000;
\red255\green255\blue255;
\red000\green128\blue128;
\red255\green255\blue255;
\red128\green000\blue255;
\red255\green255\blue255;
\red000\green000\blue000;
\red255\green255\blue255;
}

\f0\fs20\cb23\cf22 \highlight13\cf12 #include <msp430.h>\par
#include "grlib.h"\par
#include "partituras.h"\par
\highlight1\cf0 \par
\highlight13\cf12 #include "Crystalfontz128x128_ST7735.h"\par
#include "HAL_MSP430G2_Crystalfontz128x128_ST7735.h"\par
#include <stdio.h>\par
\highlight1\cf0 \par
\par
\par
\par
\par
\par
\highlight5\cf4 //funcion para tocar nota\par
\highlight21\cf20 void\highlight1\cf0  \highlight17\cf16 toca_nota\highlight15\cf14\b (\highlight21\cf20\b0 unsigned\highlight1\cf0  \highlight21\cf20 char\highlight1\cf0  \highlight17\cf16 nota\highlight15\cf14\b )\highlight1\cf0\b0 \par
\highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \highlight17\cf16 TA0CCR0\highlight15\cf14\b =\highlight17\cf16\b0 Nota\highlight15\cf14\b [\highlight17\cf16\b0 nota\highlight15\cf14\b ];\highlight1\cf0\b0 \tab \tab \highlight19\cf18 ///controlar la frecuencia de la nota\par
\highlight1\cf0 \tab \highlight17\cf16 TA0CCR1\highlight15\cf14\b =(\highlight17\cf16\b0 Nota\highlight15\cf14\b [\highlight17\cf16\b0 nota\highlight15\cf14\b ])>>\highlight7\cf6\b0 4\highlight15\cf14\b ;\highlight1\cf0\b0   \highlight5\cf4 //controlar volumen(graves suenan mas bajo y agudas mas alto si no se cambiara)\par
\highlight1\cf0 \par
\highlight15\cf14\b \}\highlight1\cf0\b0 \par
\par
\par
\highlight21\cf20 void\highlight1\cf0  \highlight17\cf16 conf_reloj\highlight15\cf14\b (\highlight21\cf20\b0 char\highlight1\cf0  \highlight17\cf16 VEL\highlight15\cf14\b )\{\highlight1\cf0\b0 \par
\tab \highlight17\cf16 BCSCTL2\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 SELM_0\highlight1\cf0  \highlight15\cf14\b |\highlight1\cf0\b0  \highlight17\cf16 DIVM_0\highlight1\cf0  \highlight15\cf14\b |\highlight1\cf0\b0  \highlight17\cf16 DIVS_0\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \highlight9\cf8\b switch\highlight15\cf14 (\highlight17\cf16\b0 VEL\highlight15\cf14\b )\{\highlight1\cf0\b0 \par
\tab \highlight9\cf8\b case\highlight1\cf0\b0  \highlight7\cf6 1\highlight15\cf14\b :\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b if\highlight1\cf0\b0  \highlight15\cf14\b (\highlight17\cf16\b0 CALBC1_1MHZ\highlight1\cf0  \highlight15\cf14\b !=\highlight1\cf0\b0  \highlight7\cf6 0xFF\highlight15\cf14\b )\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight7\cf6 0x00\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 BCSCTL1\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALBC1_1MHZ\highlight15\cf14\b ;\highlight1\cf0\b0       \highlight3\cf2 /* Set DCO to 1MHz */\highlight1\cf0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALDCO_1MHZ\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b break\highlight15\cf14 ;\highlight1\cf0\b0 \par
\tab \highlight9\cf8\b case\highlight1\cf0\b0  \highlight7\cf6 8\highlight15\cf14\b :\highlight1\cf0\b0 \par
\par
\tab \tab \highlight9\cf8\b if\highlight1\cf0\b0  \highlight15\cf14\b (\highlight17\cf16\b0 CALBC1_8MHZ\highlight1\cf0  \highlight15\cf14\b !=\highlight1\cf0\b0  \highlight7\cf6 0xFF\highlight15\cf14\b )\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 __delay_cycles\highlight15\cf14\b (\highlight7\cf6\b0 100000\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight7\cf6 0x00\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 BCSCTL1\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALBC1_8MHZ\highlight15\cf14\b ;\highlight1\cf0\b0       \highlight3\cf2 /* Set DCO to 8MHz */\highlight1\cf0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALDCO_8MHZ\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b break\highlight15\cf14 ;\highlight1\cf0\b0 \par
\tab \highlight9\cf8\b case\highlight1\cf0\b0  \highlight7\cf6 12\highlight15\cf14\b :\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b if\highlight1\cf0\b0  \highlight15\cf14\b (\highlight17\cf16\b0 CALBC1_12MHZ\highlight1\cf0  \highlight15\cf14\b !=\highlight1\cf0\b0  \highlight7\cf6 0xFF\highlight15\cf14\b )\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 __delay_cycles\highlight15\cf14\b (\highlight7\cf6\b0 100000\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight7\cf6 0x00\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 BCSCTL1\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALBC1_12MHZ\highlight15\cf14\b ;\highlight1\cf0\b0      \highlight3\cf2 /* Set DCO to 12MHz */\highlight1\cf0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALDCO_12MHZ\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b break\highlight15\cf14 ;\highlight1\cf0\b0 \par
\tab \highlight9\cf8\b case\highlight1\cf0\b0  \highlight7\cf6 16\highlight15\cf14\b :\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b if\highlight1\cf0\b0  \highlight15\cf14\b (\highlight17\cf16\b0 CALBC1_16MHZ\highlight1\cf0  \highlight15\cf14\b !=\highlight1\cf0\b0  \highlight7\cf6 0xFF\highlight15\cf14\b )\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 __delay_cycles\highlight15\cf14\b (\highlight7\cf6\b0 100000\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight7\cf6 0x00\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 BCSCTL1\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALBC1_16MHZ\highlight15\cf14\b ;\highlight1\cf0\b0      \highlight3\cf2 /* Set DCO to 16MHz */\highlight1\cf0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALDCO_16MHZ\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b break\highlight15\cf14 ;\highlight1\cf0\b0 \par
\tab \highlight9\cf8\b default\highlight15\cf14 :\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b if\highlight1\cf0\b0  \highlight15\cf14\b (\highlight17\cf16\b0 CALBC1_1MHZ\highlight1\cf0  \highlight15\cf14\b !=\highlight1\cf0\b0  \highlight7\cf6 0xFF\highlight15\cf14\b )\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight7\cf6 0x00\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 BCSCTL1\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALBC1_1MHZ\highlight15\cf14\b ;\highlight1\cf0\b0       \highlight3\cf2 /* Set DCO to 1MHz */\highlight1\cf0 \par
\tab \tab \tab \highlight17\cf16 DCOCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 CALDCO_1MHZ\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\tab \tab \highlight9\cf8\b break\highlight15\cf14 ;\highlight1\cf0\b0 \par
\par
\tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\tab \highlight17\cf16 BCSCTL1\highlight1\cf0  \highlight15\cf14\b |=\highlight1\cf0\b0  \highlight17\cf16 XT2OFF\highlight1\cf0  \highlight15\cf14\b |\highlight1\cf0\b0  \highlight17\cf16 DIVA_0\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \highlight17\cf16 BCSCTL3\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 XT2S_0\highlight1\cf0  \highlight15\cf14\b |\highlight1\cf0\b0  \highlight17\cf16 LFXT1S_2\highlight1\cf0  \highlight15\cf14\b |\highlight1\cf0\b0  \highlight17\cf16 XCAP_1\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\par
\highlight15\cf14\b \}\highlight1\cf0\b0 \par
\highlight17\cf16 Graphics_Context\highlight1\cf0  \highlight17\cf16 g_sContext\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\highlight17\cf16 Cancion\highlight1\cf0  \highlight17\cf16 Song\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\par
\highlight3\cf2 /*\par
 * main.c\par
 */\highlight1\cf0 \par
\highlight21\cf20 int\highlight1\cf0  \highlight17\cf16 main\highlight15\cf14\b (\highlight21\cf20\b0 void\highlight15\cf14\b )\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \highlight17\cf16 WDTCTL\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight17\cf16 WDTPW\highlight1\cf0  \highlight15\cf14\b |\highlight1\cf0\b0  \highlight17\cf16 WDTHOLD\highlight15\cf14\b ;\highlight1\cf0\b0 \tab \highlight5\cf4 // Stop watchdog timer\par
\highlight1\cf0 \par
\tab \highlight17\cf16 Graphics_Rectangle\highlight1\cf0  \highlight17\cf16 rectangulo\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 5\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 5\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 123\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 123\highlight1\cf0 \par
\tab \highlight15\cf14\b \};\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_Rectangle\highlight1\cf0  \highlight17\cf16 marco\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 1\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 1\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 127\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 127\highlight1\cf0 \par
\tab \highlight15\cf14\b \};\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_Rectangle\highlight1\cf0  \highlight17\cf16 barra\highlight1\cf0  \highlight15\cf14\b =\highlight1\cf0\b0  \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 30\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 30\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 31\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 50\highlight1\cf0 \par
\tab \highlight15\cf14\b \};\highlight1\cf0\b0 \par
\par
\par
\tab \highlight21\cf20 int\highlight1\cf0  \highlight17\cf16 i\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \highlight17\cf16 conf_reloj\highlight15\cf14\b (\highlight7\cf6\b0 16\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Song\highlight15\cf14\b =\highlight17\cf16\b0 Coplita1\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\par
\par
\par
\tab \highlight17\cf16 Crystalfontz128x128_Init\highlight15\cf14\b ();\highlight1\cf0\b0 \par
\par
\tab \highlight3\cf2 /* Set default screen orientation */\highlight1\cf0 \par
\tab \highlight17\cf16 Crystalfontz128x128_SetOrientation\highlight15\cf14\b (\highlight17\cf16\b0 LCD_ORIENTATION_UP\highlight15\cf14\b );\highlight1\cf0\b0 \par
\par
\par
\tab \highlight3\cf2 /* Initializes graphics context */\highlight1\cf0 \par
\tab \highlight17\cf16 Graphics_initContext\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0  \highlight15\cf14\b &\highlight17\cf16\b0 g_sCrystalfontz128x128\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_setForegroundColor\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0  \highlight17\cf16 GRAPHICS_COLOR_PURPLE\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_setBackgroundColor\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0  \highlight17\cf16 GRAPHICS_COLOR_BLACK\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_clearDisplay\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_setFont\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0  \highlight15\cf14\b &\highlight17\cf16\b0 g_sFontCm16b\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_drawRectangle\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,&\highlight17\cf16\b0 marco\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \highlight17\cf16 Graphics_setBackgroundColor\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0  \highlight17\cf16 GRAPHICS_COLOR_THISTLE\highlight15\cf14\b );\highlight1\cf0\b0 \par
\par
\tab \highlight17\cf16 Graphics_setForegroundColor\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0  \highlight17\cf16 GRAPHICS_COLOR_WHITE\highlight15\cf14\b );\highlight1\cf0\b0 \par
\par
\tab \highlight17\cf16 Graphics_drawRectangle\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,&\highlight17\cf16\b0 rectangulo\highlight15\cf14\b );\highlight1\cf0\b0 \par
\par
\tab \highlight17\cf16 Graphics_drawStringCentered\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight11\cf10 "CANCION"\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 15\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 63\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 20\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 TRANSPARENT_TEXT\highlight15\cf14\b );\highlight1\cf0\b0 \par
\par
\tab \highlight17\cf16 Graphics_drawStringCentered\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 Song\highlight15\cf14\b .\highlight17\cf16\b0 nombre\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 15\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 63\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight7\cf6 40\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 TRANSPARENT_TEXT\highlight15\cf14\b );\highlight1\cf0\b0 \par
\par
\tab \highlight17\cf16 P2DIR\highlight15\cf14\b |=\highlight17\cf16\b0 BIT6\highlight15\cf14\b ;\highlight1\cf0\b0   \highlight5\cf4 //salida buffer P2.6\par
\highlight1\cf0 \tab \highlight17\cf16 P2SEL\highlight15\cf14\b |=\highlight17\cf16\b0 BIT6\highlight15\cf14\b ;\highlight1\cf0\b0 \tab \highlight5\cf4 //gpio P2.6\par
\highlight1\cf0 \tab \highlight17\cf16 P2SEL2\highlight15\cf14\b &=~(\highlight17\cf16\b0 BIT6\highlight15\cf14\b +\highlight17\cf16\b0 BIT7\highlight15\cf14\b );\highlight1\cf0\b0 \tab \highlight5\cf4 //pwm P2.6\par
\highlight1\cf0 \tab \highlight17\cf16 P2SEL\highlight15\cf14\b &=~\highlight17\cf16\b0 BIT7\highlight15\cf14\b ;\highlight1\cf0\b0 \tab \highlight5\cf4 //gpio P2.7\par
\highlight1\cf0 \tab \highlight17\cf16 TA0CCTL1\highlight15\cf14\b =\highlight17\cf16\b0 OUTMOD_7\highlight15\cf14\b ;\highlight1\cf0\b0  \highlight5\cf4 //salida P2.7\par
\highlight1\cf0 \tab \highlight17\cf16 TA0CTL\highlight15\cf14\b =\highlight17\cf16\b0 TASSEL_2\highlight15\cf14\b |\highlight17\cf16\b0 MC_1\highlight15\cf14\b ;\highlight1\cf0\b0 \tab \highlight5\cf4 //SMCLK,DIV=1,UP\par
\highlight1\cf0 \tab \highlight17\cf16 TA1CCTL0\highlight15\cf14\b =\highlight17\cf16\b0 CCIE\highlight15\cf14\b ;\highlight1\cf0\b0  \highlight5\cf4 //CCIE=1 activa las interrupciones\par
\highlight1\cf0 \tab \highlight17\cf16 TA1CTL\highlight15\cf14\b =\highlight17\cf16\b0 TASSEL_1\highlight15\cf14\b |\highlight17\cf16\b0 MC_1\highlight15\cf14\b ;\highlight1\cf0\b0 \tab \highlight5\cf4 //SMCLK,DIV=1,UP\par
\highlight1\cf0 \par
\tab \highlight17\cf16 TA1CCR0\highlight15\cf14\b =\highlight17\cf16\b0 Song\highlight15\cf14\b .\highlight17\cf16\b0 tempo\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\par
\tab \highlight17\cf16 __bis_SR_register\highlight15\cf14\b (\highlight17\cf16\b0 GIE\highlight15\cf14\b );\highlight1\cf0\b0  \highlight5\cf4 //activar interrupciones\par
\highlight1\cf0 \tab \highlight17\cf16 i\highlight15\cf14\b =\highlight7\cf6\b0 0\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\par
\tab \highlight9\cf8\b while\highlight15\cf14 (\highlight7\cf6\b0 1\highlight15\cf14\b )\{\highlight1\cf0\b0 \par
\tab \tab \highlight17\cf16 LPM0\highlight15\cf14\b ;\highlight5\cf4\b0 //Salimo del modo bajo consumo\par
\highlight1\cf0 \tab \tab \highlight9\cf8\b if\highlight15\cf14 (\highlight17\cf16\b0 Song\highlight15\cf14\b .\highlight17\cf16\b0 notas\highlight15\cf14\b [\highlight17\cf16\b0 i\highlight15\cf14\b ]!=\highlight7\cf6\b0 1\highlight15\cf14\b )\{\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 toca_nota\highlight15\cf14\b (\highlight17\cf16\b0 Song\highlight15\cf14\b .\highlight17\cf16\b0 notas\highlight15\cf14\b [\highlight17\cf16\b0 i\highlight15\cf14\b ]);\highlight1\cf0\b0 \par
\tab \tab \highlight15\cf14\b \}\highlight9\cf8 else\highlight1\cf0\b0 \par
\tab \tab \tab \highlight17\cf16 TA0CCR1\highlight15\cf14\b =\highlight7\cf6\b0 1\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\par
\tab \tab \highlight17\cf16 Graphics_drawString\highlight15\cf14\b (&\highlight17\cf16\b0 g_sContext\highlight15\cf14\b ,\highlight1\cf0\b0  \highlight5\cf4 //Dibujamos en pantalla la nota que estamos tocando\par
\highlight1\cf0 \tab \tab \tab \tab \highlight17\cf16 Notas_N\highlight15\cf14\b [\highlight17\cf16\b0 Song\highlight15\cf14\b .\highlight17\cf16\b0 notas\highlight15\cf14\b [\highlight17\cf16\b0 i\highlight15\cf14\b ]],\highlight1\cf0\b0 \par
\tab \tab \tab \tab \highlight7\cf6 15\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \tab \highlight7\cf6 20\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \tab \highlight7\cf6 60\highlight15\cf14\b ,\highlight1\cf0\b0 \par
\tab \tab \tab \tab \highlight17\cf16 OPAQUE_TEXT\highlight15\cf14\b );\highlight1\cf0\b0 \par
\tab \tab \highlight17\cf16 i\highlight15\cf14\b ++;\highlight1\cf0\b0 \par
\par
\tab \tab \highlight9\cf8\b if\highlight15\cf14 (\highlight17\cf16\b0 Song\highlight15\cf14\b .\highlight17\cf16\b0 notas\highlight15\cf14\b [\highlight17\cf16\b0 i\highlight15\cf14\b ]==\highlight7\cf6\b0 0\highlight15\cf14\b )\highlight1\cf0\b0  \highlight17\cf16 i\highlight15\cf14\b =\highlight7\cf6\b0 0\highlight15\cf14\b ;\highlight1\cf0\b0  \highlight5\cf4 // La ultima nota de la partitura es un cero e indica que acaba la cancion e inicializamos la variable\par
\highlight1\cf0 \par
\tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\tab \highlight9\cf8\b return\highlight1\cf0\b0  \highlight7\cf6 0\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\highlight15\cf14\b \}\highlight1\cf0\b0 \par
\highlight13\cf12 #pragma vector=TIMER1_A0_VECTOR \highlight5\cf4 //Asignamos la interrupcion\par
\highlight1\cf0 \tab \highlight17\cf16 __interrupt\highlight1\cf0  \highlight21\cf20 void\highlight1\cf0  \highlight17\cf16 TIMER1_A0_ISR_HOOK\highlight15\cf14\b (\highlight21\cf20\b0 void\highlight15\cf14\b )\highlight1\cf0\b0 \par
\tab \highlight15\cf14\b \{\highlight1\cf0\b0 \par
\tab \tab \highlight17\cf16 LPM0_EXIT\highlight15\cf14\b ;\highlight1\cf0\b0 \par
\tab \highlight15\cf14\b \}\highlight1\cf0\b0 \par
\par
}
