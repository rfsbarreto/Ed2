#include <stdio.h>

//questao 1
int escrita_arq_sequencial(char* nome_arquivo){
	FILE* fout;
	fout=fopen(nome_arquivo,"w");
	
	if (!fout){
		printf("Erro ao abrir arquivo");
		exit(-1);
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
	return 0;
}

//questao 2
int leitura_arq_sequencial(char* nome_arquivo){
	FILE* fin = fopen(nome_arquivo,"r");
	if (!fin){
		printf("Erro ao abrir arquivo");
		exit(-1);
	}

	char* campo2= malloc(15*sizeof(char));
	char* campo1= malloc(15*sizeof(char));

	while (!(fscanf(fin,"%15[^|]|%15[^|]|\n",campo1,campo2)!=2)){
		printf("Numero: %s Nome: %s\n",campo1,campo2);
	}
	fclose(fin);
}

int get_qtd_campos(char* nome_arquivo){
	FILE* fin;
	fin=fopen(nome_arquivo,"r");
	char* temp;
	int cont=0;
	while(fscanf(fin,"%15[^|\n]|",temp)==1)
		cont++;
	return cont;
}

int main(){
	escrita_arq_sequencial("saida.txt");
	leitura_arq_sequencial("saida.txt");

}
