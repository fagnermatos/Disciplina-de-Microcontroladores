#include "SanUSB1.h"

#pragma interrupt interrupcao 
void interrupcao() {
}

unsigned char set_seg[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
int i;
int z;
int dezena;
int unidade;

void display(){
	for(i=0;i<99;i++){ //CONTA DE 00 A 99
		for(z=0;z<15;z++){ //REPETE CADA N?MERO POR 15 VEZES POIS O DELAY ... CURTO E N?O DARIA TEMPO VER!
			dezena=i/10;//QUEBRA A VARIAVEL i EM 2 PARTES, PRIMEIRO EM DEZENA
			//SE O N?MERO FOR 27, DEZENA=2 E UNIDADE=7
			unidade=i%10;//DEPOIS EM UNIDADE
			nivel_alto(pin_a5);//SELECIONA 1. DISPLAY
			nivel_baixo(pin_c0);
			PORTB=set_seg[dezena];//MOSTRA O VALOR DE DEZENA
			tempo_ms(50);
			nivel_alto(pin_c0);//SELECIONA 2. DISPLAY
			nivel_baixo(pin_a5);
			PORTB=set_seg[unidade];//MOSTRA O VALOR DE UNIDADE
			tempo_ms(50);
		}
	}
}    
    
int flag = 0;

void delay(){
    int i = 0;
    for(i ; i< 10; i++){
        if(!entrada_pin_e3) {
            flag = 1;
    } 
        
    if(flag == 1 && entrada_pin_a0){    
        nivel_alto(pin_a0);
        nivel_alto(pin_a4);
        nivel_baixo(pin_a1);
        nivel_baixo(pin_a2);
        nivel_baixo(pin_a3);
	display();
        PORTB = 0xff;
        flag = 0;
       }
    }
}

void main(){
	TRISB = 0b00000000;
	nivel_baixo(pin_c0);
	clock_int_4MHz();
	    
	while(1){
		PORTB = 0xff;

		nivel_alto(pin_a0);
		nivel_alto(pin_a3);
		nivel_baixo(pin_a2);
		nivel_baixo(pin_a1);
		nivel_baixo(pin_a4);
		tempo_ms(20000);
		delay();

		nivel_alto(pin_a2);
		nivel_alto(pin_a3);
		nivel_baixo(pin_a1);
		nivel_baixo(pin_a4);
		nivel_baixo(pin_a0);
		tempo_ms(20000);
		delay();

		nivel_alto(pin_a1);
		nivel_alto(pin_a3);
		nivel_baixo(pin_a0);
		nivel_baixo(pin_a4);
		nivel_baixo(pin_a2);
		tempo_ms(10000);
		delay();
	}
}
