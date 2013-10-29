#include <stdio.h>

typedef struct func{
	char num_mat[5];
	int id;
	char nome[15];
	char cargo[15];
	int escolaridade;
	char sexo;
	char local[15];
	char est_civil;
	int salario;
} func;
	
//questao 1 escrita de arquivo generica
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

//questao 2 leitura arquivo com 2 campos
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

func* leitura_funcionario(FILE* file){
	func* f;
	f= malloc(sizeof(func));
	if (fscanf(file,"%d%*c%5[^|]|%15[^|]|%15[^|]|%d|%c|%15[^|]|%c|%d",&(*f).id,(*f).num_mat,(*f).nome,(*f).cargo,&(*f).escolaridade,&(*f).sexo,(*f).local,&(*f).est_civil,&(*f).salario)==9){
		imprime_func(*f);
		return f;
	}else
		return NULL;
}

void imprime_func(func f){
	printf("Funcionario: %d %s %s %s %d %c %s %c %d\n",f.id,f.num_mat,f.nome,f.cargo,f.escolaridade,f.sexo,f.local,f.est_civil,f.salario);
}

//questao 3
int consulta_arq_sequencial(char* nome_arquivo,char* matricula,char sexo, int sal){
	func* temp;
	FILE* f = fopen("questao3.txt","r");
	
	if (matricula!= NULL){
		temp= leitura_funcionario(f);
		if ((*temp).num_mat==matricula)
			return 1;
		else
			return 0;
	}else {
		//if (
	}	 
	return 1;
}



int main(){
//	escrita_arq_sequencial("saida.txt");
	leitura_arq_sequencial("questao3.txt");
	FILE* f = fopen("questao3.txt","r");
	leitura_funcionario(f);
}
