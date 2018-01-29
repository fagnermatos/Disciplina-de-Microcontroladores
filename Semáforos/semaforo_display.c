#include "SanUSB1.h"

#pragma interrupt interrupcao 
void interrupcao() {
}


unsigned char set_seg[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
//int i;

int i;
int z;


void display(){
	for(i = 9; i>=0; i--){
		PORTB = set_seg[i];
		tempo_ms(5000);
	}
}    
    
int flag = 0;

void delay(){
    int i = 0;
	for(i ; i< 10; i++){
		if(!entrada_pin_e3) {
			flag = 1;
		}
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

void main(){
	TRISB = 0b00000000;
	nivel_baixo(pin_c0);
	clock_int_4MHz();
	while(1){   
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
