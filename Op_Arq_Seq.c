#include <stdio.h>

int main(){
	FILE* fout;
	fout=fopen("saida.txt","w");
	
	if (!fout){
		printf("Erro ao abrir arquivo");
		return -1;
	}
	int numRegistros,numCampos,j,i;
	printf("Informe o numero de registros: ");
	scanf("%d",&numRegistros);
	printf("Informe o numero de campos: ");
	scanf("%d",&numCampos);
	char* campos = malloc(15*sizeof(char));
	for (j=0;j<numRegistros;j++){
		for (i=0;i<numCampos;i++){
			printf("Digite Campo %d:",i);
			scanf("%15s",campos);
			fprintf(fout,"%-15s|",campos);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
}
