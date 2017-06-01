//ater906 ID:8782051
#include <stdio.h>
int main(int argc, char *argv[]){
	if (argc == 2){
		FILE *file;
		char b;
		file = fopen(argv[1], "r");
		char a=fgetc(file);
		while((a != EOF)){
			b=fgetc(file);
			printf("0x%02x%02x\n",a&0xff,b&0xff);
			a= fgetc(file);
}
fclose(file);
}
}
