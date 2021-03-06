//ater906 ID:8782051
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#define HALT 0xf025
#define LD 0x2
#define LEA 0xe
int main(int argc, char *argv[]){
	if (argc == 2){
		FILE *file;
		file =  fopen(argv[1], "r");
		uint16_t array[100];
		uint16_t directRegister[8]={0,0,0,0,0,0,0};
		char cc[3] = {'N','Z','P'};
		int getCcPos;//cc position
		char highorigin = fgetc(file); //first byte of lc3 (origin)
		char loworigin = fgetc(file); //second byte of lc3 (origin
		uint16_t origin = (highorigin << 8)|loworigin &0xff; //appends the 2 bytes to get 16bit (origin)
		uint16_t byte;
		char highbyte = fgetc(file);//initialize first byte of each statement after origin line
		char lowbyte;//initialize for second byte of each statement after origin line
		int count = 0; //counts how many instruction there is in obj file
		int counter; //counter for how many instuctions until it reaches HALT
		uint16_t instruction,check,getDr;
		int i = 0;//index of array
		int pcOffSet;
		int ccValue = 0;
		char checkCc;
		uint16_t checkBit;
		while((highbyte != EOF)){ //while loop where it keeps executing until end of file
			lowbyte = fgetc(file);
			byte = (highbyte << 8)| lowbyte &0xff;//one line instruction
			array[count] = byte;//will add statement to array (contains all instructions obj file
			if(array[count] == HALT)
				{counter=count;}//will copy ther count to counter when it gets a halt instruction
				else {}
				count +=1;
				highbyte = fgetc(file);//gets the first 8bits of the instruction
				}
		for(i;i<(counter);i++){//will go through array to check if any instruction is ld
			instruction = array[i];
			check = (instruction >> 12)& 0xf;
			if (check == LD){//means its a ld instruction
				getDr = instruction >>9;
				getDr = getDr & 0x7;
				pcOffSet= instruction & 0x1ff;
				if(((pcOffSet >> 8) & 0x1) == 1){
					pcOffSet = (~(pcOffSet&0xff)+1)+254;
					if(pcOffSet == 0){
						pcOffSet = -256;}
					}
				directRegister[getDr] = array[i+1+pcOffSet]; //will store value of memory address
				ccValue = array[i+1+pcOffSet];
				}
			if (check == LEA){//means its a lea instruction
				getDr = instruction >>9;
				getDr = getDr & 0x7;
				pcOffSet= instruction & 0x1ff;
				if(((pcOffSet >> 8) & 0x1) == 1){
					pcOffSet = (~(pcOffSet&0xff)+1)+254;
					if(pcOffSet == 0){
						pcOffSet = -256;}
					}
				directRegister[getDr] = origin+i+1+pcOffSet; //will store memory address
				ccValue = origin+i+1+pcOffSet;
				checkBit = ccValue >> 15;
				if (checkBit == 0){
					if (ccValue > 0){
						getCcPos = 2;}
					if (ccValue == 0){getCcPos =1;}
						}
				else{getCcPos = 0;}
				printf("after executing instruction\t0x%04x\n",array[i]);
				printf("R0\t0x%04x\n", directRegister[0]);
				printf("R1\t0x%04x\n", directRegister[1]);
				printf("R2\t0x%04x\n", directRegister[2]);
				printf("R3\t0x%04x\n", directRegister[3]);
				printf("R4\t0x%04x\n", directRegister[4]);
				printf("R5\t0x%04x\n", directRegister[5]);
				printf("R6\t0x%04x\n", directRegister[6]);
				printf("R7\t0x%04x\n", directRegister[7]);
				printf("PC\t0x%04x\n",origin+i+1);
				printf("IR\t0x%04x\n", array[i]);
				printf("CC\t%c\n", cc[getCcPos]);
				printf("==================\n");
				}
			}
		fclose(file);
		}
	}
