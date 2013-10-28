#include <stdio.h>

int main(){
	FILE* fout;
	fout=fopen("saida.txt","w");
	
	if (!fout){
		printf("Erro ao abrir arquivo");
		return -1;
	}
	int numRegistros,numCampos,j,i;
	scanf("Informe o numero de registros: %d \n",&numResgistros);
	scanf("Informe o numero de campos: %d \n",&numCampos);
	char* campos = malloc(15*sizeof(char));
	for (j=0;j<numRegistros;j++){
		for (i=0;i<numCampos;i++){
			scanf("Digite Campo %d: %15s\n",&campos);
			fprintf(fout,"%15s|");
		}
		fprintf(fout,"\n");
	}
}
