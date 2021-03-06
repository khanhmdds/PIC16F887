#include <main.h>
#FUSES HS
#USE DELAY (CLOCK=20M)
#include <string.h>
#include <lcd.c>

#DEFINE SCK PIN_C0
#DEFINE SER PIN_C1
#DEFINE RCK PIN_C2
#DEFINE G PIN_C3

#DEFINE D PIN_B0
#DEFINE X PIN_B1
#DEFINE V PIN_B2

#DEFINE LCD_ENABLE_PIN PIN_D0
#DEFINE LCD_RS_PIN PIN_D1
#DEFINE LCD_RW_PIN PIN_D2
#DEFINE LCD_DATA4 PIN_D4
#DEFINE LCD_DATA5 PIN_D5
#DEFINE LCD_DATA6 PIN_D6
#DEFINE LCD_DATA7 PIN_D7

UNSIGNED INT8 MA7DOAN[10] = {0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
SIGNED INT8 GG;

void lcd_refresh()
{
lcd_send_byte(1,0);
lcd_send_byte(1,6);
}

VOID XUAT1BYTE(UNSIGNED INT8 BYTEXUAT)
{
   UNSIGNED INT8 I;
   #BIT BSER = BYTEXUAT.7
   FOR(I=0;I<8;I++)
   {
      OUTPUT_BIT(SER,BSER);
      OUTPUT_LOW(SCK);
      OUTPUT_HIGH(SCK);
      BYTEXUAT = BYTEXUAT << 1;
   }
}
VOID GIAIMA7DOAN()
{
   XUAT1BYTE(MA7DOAN[GG/10]);
   XUAT1BYTE(MA7DOAN[GG%10]);

   OUTPUT_LOW(RCK);
   OUTPUT_HIGH(RCK);
   OUTPUT_LOW(G);
}

void main()
{
   SET_TRIS_D(0);
   SET_TRIS_C(0);
   SET_TRIS_B(0);
   
   lcd_init();
   lcd_refresh();
   
   KT:
   
   lcd_gotoxy(1,1);
   lcd_putc("RED LIGHT   ");
   lcd_gotoxy(1,2);
   lcd_putc("STOP !!!   ");
      
   OUTPUT_HIGH(D);
   OUTPUT_LOW(X);
   OUTPUT_LOW(V);
   
   FOR(GG=22;GG>=0;GG--)
   {
      GIAIMA7DOAN();
      DELAY_MS(900);
   }
   
   OUTPUT_HIGH(X);
   OUTPUT_LOW(D);
   OUTPUT_LOW(V);    
      
   lcd_gotoxy(1,1);
   lcd_putc("GREEN LIGHT  ");
   lcd_gotoxy(1,2);
   lcd_putc("GO AHEAD  ");
   
   FOR(GG=15;GG>=0;GG--)
   {
      GIAIMA7DOAN();
      DELAY_MS(900);
   }
   
   OUTPUT_HIGH(v);
   OUTPUT_LOW(D);
   OUTPUT_LOW(X);
      
      
   lcd_gotoxy(1,1);
   lcd_putc("YELLOW LIGHT");
   lcd_gotoxy(1,2);
   lcd_putc("SLOW DOWN");
      
   FOR(GG=5;GG>=0;GG--)
   {
      GIAIMA7DOAN();
      DELAY_MS(900);
   }
   GOTO KT;
}
