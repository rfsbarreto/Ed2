#include <stdio.h>

int main(){
	FILE* fout;
	fout=fopen("saida.txt","r");
	
	if (!fout){
		printf("Erro ao abrir arquivo");
		return -1;
	}
	
}
