#include "Arduino.h"
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

char tecla_en;

long primeiro = 0;
long segundo  = 0;
double total  = 0;

const byte qtd_linha  = 4;
const byte qtd_coluna = 4;

char teclas[qtd_linha][qtd_coluna] = {
	{'1','2','3','+'},
	{'4','5','6','-'},
    {'7','8','9','C'},
    {'*','0','/','='}
};
byte pinos_linha[qtd_linha]	  = {0, 1, 2, 3};
byte pinos_coluna[qtd_coluna] = {4, 5, 6, 7};

Keypad teclado = Keypad(makeKeymap(teclas), pinos_linha, pinos_coluna, qtd_linha, qtd_coluna);

long get_segundo();

void setup() {
	lcd.begin(16, 2);
}

void loop() {
	tecla_en = teclado.getKey();

 	if(tecla_en != NO_KEY) {
      	switch(tecla_en){
            case '0' ... '9':
            lcd.setCursor(0,0);
            primeiro = primeiro * 10 + (tecla_en - '0');
            lcd.print(primeiro);
        break;


        case '+':
            primeiro = (total != 0 ? total : primeiro);
            lcd.print("+");
            segundo = get_segundo();
            total = primeiro + segundo;
          	lcd.setCursor(0,1);
          	lcd.print("                ");
            lcd.setCursor(0,1);
          	lcd.print("=");
            lcd.print(total);
            primeiro = 0;
          	segundo	 = 0;
        break;

        case '-':
            primeiro = (total != 0 ? total : primeiro);
            lcd.print("-");
            segundo = get_segundo();
            total = primeiro - segundo;
          	lcd.setCursor(0,1);
          	lcd.print("                ");
            lcd.setCursor(0,1);
          	lcd.print("=");
            lcd.print(total);
            primeiro = 0;
          	segundo	 = 0;
        break;

        case '*':
            primeiro = (total != 0 ? total : primeiro);
            lcd.print("*");
            segundo = get_segundo();
            total = primeiro * segundo;
          	lcd.setCursor(0,1);
          	lcd.print("                ");
            lcd.setCursor(0,1);
            lcd.print("=");
            lcd.print(total);
            primeiro = 0;
          	segundo = 0;
        break;

        case '/':
            primeiro = (total != 0 ? total : primeiro);
            lcd.print("/");
            segundo = get_segundo();
            segundo == 0 ? lcd.print("Valor invalido") : total = (float)primeiro / (float)segundo;
            lcd.setCursor(0,1);
          	lcd.print("                ");
          	lcd.setCursor(0,1);
          	lcd.print("=");
            lcd.print(total);
            primeiro = 0;
          	segundo = 0;
            break;

        case 'C':
            total = 0;
          	primeiro = 0;
            lcd.clear();
        break;
      }
    }
}

long get_segundo() {

    while(1) {
      	tecla_en = teclado.getKey();

      	if(tecla_en != NO_KEY) {
            if(tecla_en >= '0' && tecla_en <= '9') {
                segundo = segundo * 10 + (tecla_en - '0');
                lcd.print(segundo);
            }else if(tecla_en == '=') break;
        }
    }

  	return segundo;
}
