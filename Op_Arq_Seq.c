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
	FILE * fin = fopen("questao3.txt","r");
	f= malloc(sizeof(func));
//	printf("a\n");
	if (fscanf(file,"%d%*c%5[^|]|%15[^|]|%15[^|]|%d|%c|%15[^|]|%c|%d|\n",&(*f).id,(*f).num_mat,(*f).nome,(*f).cargo,&(*f).escolaridade,&(*f).sexo,(*f).local,&(*f).est_civil,&(*f).salario)==9){
	//	imprime_func(f);
		return f;
	}//else
}

void imprime_func(func* f){
	if (f!=NULL)
		printf("Funcionario: %d %s %s %s %d %c %s %c %d\n",(*f).id,(*f).num_mat,(*f).nome,(*f).cargo,(*f).escolaridade,(*f).sexo,(*f).local,(*f).est_civil,(*f).salario);
	
}

//questao 3 consulta por matricula
func* consulta_matricula(char* nome_arquivo,char* matricula){
	func* temp;
	FILE* f = fopen("questao3.txt","r");
//	int achou = 0;	
	if (matricula!= NULL){
		temp= leitura_funcionario(f);
		while(temp){
//			printf("%s %s ",(*temp).num_mat,matricula);
			if (!strcmp((*temp).num_mat,matricula)){
				fclose(f);
				return temp;		
			}
		temp=leitura_funcionario(f);
		}
	}
	fclose(f);
	return NULL;	
}



//questao 3 consulta por sexo
void  consulta_sexo(char* nome_arquivo,char sexo){
	func* temp;
	FILE* f = fopen("questao3.txt","r");
//	int achou = 0;	
//	if (matricula!= NULL){
		temp= leitura_funcionario(f);
		while(temp){
//			printf("%c %c \n",(*temp).sexo,sexo);
			if ((*temp).sexo==sexo)
				imprime_func(temp);
			temp=leitura_funcionario(f);
			
		}
//	}
//	return NULL;	
}

//questao 3 consulta de funcionario com base no salario
void  consulta_salario(char* nome_arquivo,int salario){
	func* temp;
	FILE* f = fopen("questao3.txt","r");
//	int achou = 0;	
//	if (matricula!= NULL){
		temp= leitura_funcionario(f);
		while(temp){
//			printf("%c %c \n",(*temp).sexo,sexo);
			if ((*temp).salario>=salario)
				imprime_func(temp);
			temp=leitura_funcionario(f);
			
		}
//	}
//	return NULL;	
}

//questao 3 consulta por media de salario
void  consulta_media_salario(char* nome_arquivo){
	func* temp;
	FILE* f = fopen("questao3.txt","r");
//	int achou = 0;	
//	if (matricula!= NULL){
		int cont;
		long soma;
		cont=0;
		soma=0;
		temp= leitura_funcionario(f);
		while(temp){
//			printf("%c %c \n",(*temp).sexo,sexo);
		//	if ((*temp).salario>=salario)
		//		imprime_func(temp);
			soma=soma + (*temp).salario;
			temp=leitura_funcionario(f);
			cont++;
		}
//		printf(" %llu %d\n",soma,cont);
		float media = soma/cont;
		fseek(f,0,SEEK_SET);
		temp=leitura_funcionario(f);
		while(temp){
//			printf("%c %c \n",(*temp).salario,media);
			if ((*temp).salario>=media)
				imprime_func(temp);
			temp=leitura_funcionario(f);
		}
//	}
//	return NULL;	
}

//questao 3 consulta por (cargo e sexo) ou matricula
void  consulta_cargo_sexo_matricula(char* nome_arquivo,char* cargo,char sexo1,int matricula,char sexo2){
	func* temp;
	FILE* f = fopen("questao3.txt","r");
	int achou = 0;	
//	if (matricula!= NULL){
		
	temp= leitura_funcionario(f);
	while(temp){
//			printf("%c %c \n",(*temp).sexo,sexo);
		if ((!strcmp((*temp).cargo,cargo)&&((*temp).sexo==sexo1))){
			achou=1;
			imprime_func(temp);
		}
			temp=leitura_funcionario(f);
	}
//	fclose(f);
	fseek(f,0,SEEK_SET);
//	temp= consulta_matricula("questao3.txt",matricula);
	temp= leitura_funcionario(f);

	while (temp){
	//	imprime_func(temp);
		if ( (atoi((*temp).num_mat)>matricula) && ((*temp).sexo==sexo2) ){
			achou=1;
		//	printf("achou");
			imprime_func(temp);
		}
		temp=leitura_funcionario(f);
	}
	fclose(f);
	if (!achou)
		printf("Sem resultados\n");
}

int main(){
//	escrita_arq_sequencial("saida.txt");
//	leitura_arq_sequencial("questao3.txt");
/*	FILE* f = fopen("questao3.txt","r");
	int i;
	for (i=0;i<5;i++) imprime_func(leitura_funcionario(f));
	fclose(f);
*/
	printf("resultado:\n ");
//	imprime_func(consulta_matricula("questao3.txt","950"));
//	consulta_sexo("questao3.txt",'F');
//	consulta_salario("questao3.txt",9000);
//	consulta_media_salario("questao3.txt");
	consulta_cargo_sexo_matricula("questao3.txt","programador",'F',700,'M');
}
