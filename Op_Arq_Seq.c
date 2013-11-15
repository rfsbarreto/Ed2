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

	if (fscanf(file,"%d%*c%5[^|]|%15[^|]|%15[^|]|%d|%c|%15[^|]|%c|%d|\n",&(*f).id,(*f).num_mat,(*f).nome,(*f).cargo,&(*f).escolaridade,&(*f).sexo,(*f).local,&(*f).est_civil,&(*f).salario)==9){
	
		return f;
	}
}

void imprime_func(func* f){
	if (f!=NULL)
		printf("Funcionario: %d %s %s %s %d %c %s %c %d\n",(*f).id,(*f).num_mat,(*f).nome,(*f).cargo,(*f).escolaridade,(*f).sexo,(*f).local,(*f).est_civil,(*f).salario);
	
}

//questao 3 consulta por matricula
func* consulta_matricula(char* nome_arquivo,char* matricula){
	func* temp;
	FILE* f = fopen("questao3.txt","r");

	if (matricula!= NULL){
		temp= leitura_funcionario(f);
		while(temp){

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
/* Entrada: nome_arquivo-> usado para arbetura do arquivo; sexo -> campo utilizado na consulta
*	Retorno: Vazio
*  Esta funcao imprime durante a execucao os registros do arquivo onde o sexo e igual ao passado por parametro. 
***********************************************************************************************************/
void  consulta_sexo(char* nome_arquivo,char sexo){
	func* temp;
	FILE* f = fopen("questao3.txt","r");

		temp= leitura_funcionario(f);
		while(temp){

			if ((*temp).sexo==sexo)
				imprime_func(temp);
			temp=leitura_funcionario(f);
			
		}
	
}

//questao 3 consulta de funcionario com base no salario
/* Entrada: nome_arquivo-> usado para arbetura do arquivo; salario -> campo utilizado na consulta
*	Retorno: Vazio
*  Esta funcao imprime durante a execucao os registros do arquivo cujo salarios são maiore que o salario passado por parametro. 
***********************************************************************************************************/
void  consulta_salario(char* nome_arquivo,int salario){
	func* temp;
	FILE* f = fopen("questao3.txt","r");

		temp= leitura_funcionario(f);
		while(temp){

			if ((*temp).salario>=salario)
				imprime_func(temp);
			temp=leitura_funcionario(f);
			
		}
	
}

//questao 3 consulta por media de salario
/* Entrada: nome_arquivo-> usado para arbetura do arquivo;
*	Retorno: Vazio
*  Esta funcao calcula a media salarial dos registros e 
*  imprime durante a execucao os registros do arquivo cujo campos são maiores que a media salarial. 
***********************************************************************************************************/
void  consulta_media_salario(char* nome_arquivo){
	func* temp;
	FILE* f = fopen("questao3.txt","r");

		int cont;
		long soma;
		cont=0;
		soma=0;
		temp= leitura_funcionario(f);
		while(temp){

			soma=soma + (*temp).salario;
			temp=leitura_funcionario(f);
			cont++;
		}

		float media = soma/cont;
		fseek(f,0,SEEK_SET);
		temp=leitura_funcionario(f);
		while(temp){

			if ((*temp).salario>=media)
				imprime_func(temp);
			temp=leitura_funcionario(f);
		}

	
}

//questao 3 consulta por (cargo e sexo) ou matricula
/* Entrada: nome_arquivo-> usado para arbetura do arquivo; cargo,sexo1,matricula,sexo2-> parametros de busca
*	Retorno: Vazio
*  Esta funcao imprime durante a execucao os registros do arquivo cujo campos satisfazem a consulta:
*   (reg.cargo=cargo e reg.sexo=sexo) ou (reg.matricula=matricula e reg.sexo=sexo) 
***********************************************************************************************************/
void  consulta_cargo_sexo_matricula(char* nome_arquivo,char* cargo,char sexo1,int matricula,char sexo2){
	func* temp;
	FILE* f = fopen("questao3.txt","r");
	int achou = 0;	

		
	temp= leitura_funcionario(f);
	while(temp){
			
		if ((!strcmp((*temp).cargo,cargo)&&((*temp).sexo==sexo1))){
			achou=1;
			imprime_func(temp);
		}
			temp=leitura_funcionario(f);
	}

	fseek(f,0,SEEK_SET);

	temp= leitura_funcionario(f);

	while (temp){

		if ( (atoi((*temp).num_mat)>matricula) && ((*temp).sexo==sexo2) ){
			achou=1;
		
			imprime_func(temp);
		}
		temp=leitura_funcionario(f);
	}
	fclose(f);
	if (!achou)
		printf("Sem resultados\n");
}


int menu(){
	int m = 10;
		printf("0 - para sair \n");
		printf("1 - consulta por matricula\n");
		printf("2 - consulta por sexo\n");
		printf("3 - consulta por salario\n");
		printf("4 - consulta por media salario\n");
		printf("5 - consulta por cargo,sexo e matricula\n");
		
		while(m != 0){
			printf("Entre com uma das opcoes acima:",m);
			scanf("%d",&m);
			printf(" \n\n");
			
			switch (m){
			case 0:
				system("exit");
				break;
			
			case 1:
				printf("resultado:\n ");
				imprime_func(consulta_matricula("questao3.txt","950"));
				printf(" \n\n");
				break;
			case 2:
				printf("resultado:\n ");
				consulta_sexo("questao3.txt",'F');
				break;
			case 3:
				printf("resultado:\n ");
				consulta_salario("questao3.txt",9000);
				break;
			case 4:
				printf("resultado:\n ");
				consulta_media_salario("questao3.txt");
				break;
			case 5:
				printf("resultado:\n ");
				consulta_cargo_sexo_matricula("questao3.txt","programador",'F',700,'M');
				break;
			default:
				printf("valor invalido\n");
			}
			
		}
		return 0;
}
int main(){
	
	int n=10;
	int i;	
	FILE* f;// = fopen("questao3.txt","r");
	
	printf("1 - para escrita (questao 1) \n");
	printf("2 - para leitura (questao 2) \n");
	printf("3 - para leitura (questao 2) \n");
	printf("4 - para consulta(questao 3) \n");
	printf("0 - para sair \n");
	
	while(n != 0){
		printf(" \n\n");
		printf("Entre com uma das opcoes acima:",n);
		scanf("%d",&n);
	
	
		switch (n){
			case 0:
				system("exit");
				break;
				
			case 1:
				printf(" \n\n");
				escrita_arq_sequencial("saida.txt");

			break;
			
			case 2:
				printf(" \n\n");
				leitura_arq_sequencial("saida.txt");
			
			break;
			
			case 3:

			f = fopen("questao3.txt","r");
			for (i=0;i<5;i++) imprime_func(leitura_funcionario(f));
			fclose(f);
			break;
			
			case 4:
				menu();
				printf(" \n\n");
			
			default :
			printf("opcao invalida\n");
		}
	}
	
}
