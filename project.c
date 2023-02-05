#include "mbed.h"
#include "TextLCD.h"
#include "Keypad.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
TextLCD my_lcd(PTE20, PTE21, PTE22, PTE23, PTE29, PTE30, TextLCD::LCD16x2);
Keypad kpad(PTA12, PTD4, PTA2, PTA1, PTC9, PTC8, PTA5, PTA4);
SPI spi(PTD2, PTD3, PTD1);          // MOSI, MISO, SCLK
DigitalOut cs(PTD0);                // Chip select

unsigned char coulumn;

char key;
int released = 1;

unsigned int score = 0;
unsigned int highscore = 0;
unsigned int speed = 100;

const unsigned char num3[]= {
    0x00,0xC3,0xC3,0xDB,0xDB,0xFF,0x7E,0x00
};  //'3'
const unsigned char num2[]= {
    0x00,0xC3,0xE3,0xF3,0xDB,0xCF,0xC6,0x00
};  //'2'
const unsigned char num1[]= {
    0x00,0xC0,0xC4,0xFE,0xFF,0xC0,0xC0,0x00
};  //'1'

const unsigned char led1_1[]= {
    0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.1
const unsigned char led1_2[]= {
    0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.2
const unsigned char led1_3[]= {
    0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.3
const unsigned char led1_4[]= {
    0x0E,0x0E,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.4
const unsigned char led1_5[]= {
    0x1C,0x1C,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.5
const unsigned char led1_6[]= {
    0x38,0x38,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.6
const unsigned char led1_7[]= {
    0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.7
const unsigned char led1_8[]= {
    0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.8
const unsigned char led1_9[]= {
    0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.9
const unsigned char led1_10[]= {
    0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00
};  //1.10


const unsigned char led2_1[]= {
    0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00
};  //2.1
const unsigned char led2_2[]= {
    0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00
};  //2.2
const unsigned char led2_3[]= {
    0x00,0x00,0x07,0x07,0x00,0x00,0x00,0x00
};  //2.3
const unsigned char led2_4[]= {
    0x00,0x00,0x0E,0x0E,0x00,0x00,0x00,0x00
};  //2.4
const unsigned char led2_5[]= {
    0x00,0x00,0x1C,0x1C,0x00,0x00,0x00,0x00
};  //2.5
const unsigned char led2_6[]= {
    0x00,0x00,0x38,0x38,0x00,0x00,0x00,0x00
};  //2.6
const unsigned char led2_7[]= {
    0x00,0x00,0x70,0x70,0x00,0x00,0x00,0x00
};  //2.7
const unsigned char led2_8[]= {
    0x00,0x00,0xE0,0xE0,0x00,0x00,0x00,0x00
};  //2.8
const unsigned char led2_9[]= {
    0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00
};  //2.9
const unsigned char led2_10[]= {
    0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00
};  //2.10


const unsigned char led3_1[]= {
    0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00
};  //3.1
const unsigned char led3_2[]= {
    0x00,0x00,0x00,0x00,0x03,0x03,0x00,0x00
};  //3.2
const unsigned char led3_3[]= {
    0x00,0x00,0x00,0x00,0x07,0x07,0x00,0x00
};  //3.3
const unsigned char led3_4[]= {
    0x00,0x00,0x00,0x00,0x0E,0x0E,0x00,0x00
};  //3.4
const unsigned char led3_5[]= {
    0x00,0x00,0x00,0x00,0x1C,0x1C,0x00,0x00
};  //3.5
const unsigned char led3_6[]= {
    0x00,0x00,0x00,0x00,0x38,0x38,0x00,0x00
};  //3.6
const unsigned char led3_7[]= {
    0x00,0x00,0x00,0x00,0x70,0x70,0x00,0x00
};  //3.7
const unsigned char led3_8[]= {
    0x00,0x00,0x00,0x00,0xE0,0xE0,0x00,0x00
};  //3.8
const unsigned char led3_9[]= {
    0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00
};  //3.9
const unsigned char led3_10[]= {
    0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00
};  //3.10


const unsigned char led4_1[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01
};  //4.1
const unsigned char led4_2[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03
};  //4.2
const unsigned char led4_3[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07
};  //4.3
const unsigned char led4_4[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x0E
};  //4.4
const unsigned char led4_5[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C
};  //4.5
const unsigned char led4_6[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38
};  //4.6
const unsigned char led4_7[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x70
};  //4.7
const unsigned char led4_8[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0
};  //4.8
const unsigned char led4_9[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0
};  //4.9
const unsigned char led4_10[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80
};  //4.10

/// Send two bytes to SPI bus
void SPI_Write2(unsigned char MSB, unsigned char LSB)
{
    cs = 0;                         // Set CS Low
    spi.write(MSB);                 // Send two bytes
    spi.write(LSB);
    cs = 1;                         // Set CS High
}

/// MAX7219 initialisation
void Init_MAX7219(void)
{
    SPI_Write2(0x09, 0x00);         // Decoding off
    SPI_Write2(0x0A, 0x08);         // Brightness to intermediate
    SPI_Write2(0x0B, 0x07);         // Scan limit = 7
    SPI_Write2(0x0C, 0x01);         // Normal operation mode
    SPI_Write2(0x0F, 0x0F);         // Enable display test
    wait_ms(500);                   // 500 ms delay
    SPI_Write2(0x01, 0x00);         // Clear row 0.
    SPI_Write2(0x02, 0x00);         // Clear row 1.
    SPI_Write2(0x03, 0x00);         // Clear row 2.
    SPI_Write2(0x04, 0x00);         // Clear row 3.
    SPI_Write2(0x05, 0x00);         // Clear row 4.
    SPI_Write2(0x06, 0x00);         // Clear row 5.
    SPI_Write2(0x07, 0x00);         // Clear row 6.
    SPI_Write2(0x08, 0x00);         // Clear row 7.
    SPI_Write2(0x0F, 0x00);         // Disable display test
    wait_ms(500);                   // 500 ms delay
}

int main()
{
    cs = 1;                         // CS initially High
    spi.format(8,0);                // 8-bit format, mode 0,0
    spi.frequency(1000000);         // SCLK = 1 MHz
    Init_MAX7219();                 // Initialize the LED controller
    my_lcd.cls();
    my_lcd.printf("Press # to start");

    while (1) {
            key = kpad.ReadKey();                   //read the current key pressed
            
            if(key == '\0'){
                released = 1;                       //set the flag when all keys are released
                }
            if((key != '\0') && (released == 1)) {  //if a key is pressed AND previous key was released
                if (key == '#'){
                    break;
                }
            }
        }
    
    while(1){
    
    my_lcd.cls();
    
    for(int i=1; i<9; i++)      // Write first character (8 rows)
        SPI_Write2(i,num3[i-1]);
    wait(1);                    // 1 sec delay
    for(int i=1; i<9; i++)      // Write second character
        SPI_Write2(i,num2[i-1]);
    wait(1);                    // 1 sec delay
    for(int i=1; i<9; i++)      // Write second character
        SPI_Write2(i,num1[i-1]);
    wait(1);                    // 1 sec delay
    
    score = 0;
    speed = 100;

    while (1) {
        coulumn = rand()%4;
        my_lcd.cls();
        my_lcd.printf("Score:%ld",score);

        if(score > highscore){
             my_lcd.locate(0,1);
             my_lcd.printf("New Highscore!");
             my_lcd.locate(0,0);
        }
        
        if(0 == coulumn)
        {
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_1[i-1]);}
            wait_ms(speed);                    // 100 ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_2[i-1]);}
            wait_ms(speed);                    // 100 ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_3[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_4[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_5[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_6[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_7[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_8[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_9[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led1_10[i-1]);}
            wait_ms(speed);                    // speed ms delay
            
            key = kpad.ReadKey();
            if (key != 'A'){break;}
        }
        
        else if(1 == coulumn)
        {
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_1[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_2[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_3[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_4[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_5[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_6[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_7[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_8[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_9[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led2_10[i-1]);}
            wait_ms(speed);                    // speed ms delay
            
            key = kpad.ReadKey();
            if (key != '3'){break;}
        }
        
        else if(2 == coulumn)
        {
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_1[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_2[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_3[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_4[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_5[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_6[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_7[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_8[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_9[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led3_10[i-1]);}
            wait_ms(speed);                    // speed ms delay
            
            key = kpad.ReadKey();
            if (key != '2'){break;}
        }
        
        else
        {
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_1[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_2[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_3[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_4[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_5[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_6[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_7[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_8[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_9[i-1]);}
            wait_ms(speed);                    // speed ms delay
            for(int i=1; i<9; i++){      // Write first character (8 rows)
                SPI_Write2(i,led4_10[i-1]);}
            wait_ms(speed);                    // speed ms delay
            
            key = kpad.ReadKey();
            if (key != '1'){break;}
        }
        
        score = score + 1;
        speed = speed - 1;

    }
        
    while(1){
        my_lcd.cls();
        if(score >= highscore)
        {
            highscore = score;
            my_lcd.printf("New Highscore!");
        }
        else
        {
            my_lcd.printf("Game Over");
        }
        my_lcd.locate(0,1);
        my_lcd.printf("Final Score:%ld",score);
            key = kpad.ReadKey();                   //read the current key pressed
            
            if(key == '\0'){
                released = 1;                       //set the flag when all keys are released
                }
            if((key != '\0') && (released == 1)) {  //if a key is pressed AND previous key was released
                if (key == '#'){
                    break;
                }
            }
        wait(2);
        my_lcd.cls();
        my_lcd.locate(0,0);
        my_lcd.printf("Hold # to");
        my_lcd.locate(0,1);
        my_lcd.printf("restart the game");
            key = kpad.ReadKey();                   //read the current key pressed
            
            if(key == '\0'){
                released = 1;                       //set the flag when all keys are released
                }
            if((key != '\0') && (released == 1)) {  //if a key is pressed AND previous key was released
                if (key == '#'){
                    break;
                }
            }
        wait(2);
        }
    }
}
