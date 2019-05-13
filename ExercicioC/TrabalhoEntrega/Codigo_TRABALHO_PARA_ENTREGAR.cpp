/*
:::: TRABALHO ESTRUTURA DE DADOS I ::::

______________________________________________


:::: DADA AS SEGUINTES ESTRUTURAS ::::

struct listaDisciplina {
	int codigo; //codigo nunca pode ser o mesmo
	char nome[50];
	float nota;
	float frequencia;
	struct listaDisciplina *proximo;
};

struct listaAluno {
	int codigo;
	char nome[50];
	struct listaAluno *proximo;
	struct listaDisciplina *disc;
};


-> Escrever um programa em C que contenha funcoes p/ 
INSERIR ELEMENTOS NA LISTA DE ALUNOS,
ALTERAR ELEMENTOS NA LISTA DE ALUNOS,
EXCLUIR ELEMENTOS DA LISTA DE ALUNOS,
MOSTRAR ELEMENTOS DA LISTA DE ALUNOS.
	Na inclusao de elementos na lista de alunos, atribuir NULL para o 
campo disc. Criar menu com as opcoes. Essa descri��o contempla a primeira 
parte do trabalho.

-> Na segunda parte do trabalho, escrever fun��es p/
INSERIR,
ALTERAR,
EXCLUIR,
MOSTRAR ELEMENTOS NA LISTA DE DISCIPLINA.
	Cada aluno vai ter uma lista de disciplina associada. O ponteiro 
disc da listaAluno ser� o ponteiro inicio da lista de disciplina.
	O programa dever� mostrar os alunos e suas respectivas disciplinas, 
inidando se foi aprovado ou reprovado em alguma delas. Para ser aprovado a 
nora precisa ser maior ou igual a 6.0 e a frequencia ser maior ou igual a 
75.

-> VALIDACOES
	Um aluno so pode ser excluido se nao existir disciplina associada a 
ele, ou seja, disc deve ter o valor igual a NULL.
	Um aluno ter� um c�digo chave.
*/


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define NOMEALUNO 50
#define NOMEDISCIPLINA 50


struct listaDisciplina{
	int codigo;
	char nome[NOMEALUNO];
	float nota;
	float frequencia;
	struct listaDisciplina *proximo;
};
struct listaAluno{
	int codigo;
	char nome[NOMEALUNO];
	struct listaAluno *proximo;
	struct listaDisciplina *disc;
};

//Fun��es da estrutura aluno
struct listaAluno *insereInicioAluno(struct listaAluno *paluno, int px, char pn[NOMEALUNO]) {
	struct listaAluno *aux;
	aux = (listaAluno*)malloc(sizeof(listaAluno));
	aux->codigo = px;
	strcpy(aux->nome, pn);
	aux->disc = NULL;
	aux->proximo = paluno;
	paluno = aux;
	return paluno;
}
void insereDepoisAluno(struct listaAluno *paluno, int px, char pn[NOMEALUNO]) {
	struct listaAluno *aux;
	aux = (listaAluno*)malloc(sizeof(listaAluno));
	aux->codigo = px;
	strcpy(aux->nome, pn);
	aux->disc = NULL;
	aux->proximo = paluno->proximo;
	paluno->proximo = aux;
}
struct listaAluno *insereOrdenadoAluno(struct listaAluno *paluno, int px, char pn[NOMEALUNO]) {
	struct listaAluno *p, *q;
	if(paluno == NULL || px < paluno->codigo) {
		return insereInicioAluno(paluno, px, pn);
	}
	p = paluno;
	q = p;
	while(q != NULL && q->codigo < px){
		p = q;
		q = p->proximo;
	}
	if(q == NULL || q->codigo > px) {
		insereDepoisAluno(p, px, pn);
	}
	else {
		printf("\nAluno ja cadastrado!");
	}
	return paluno;
}
struct listaAluno *removeInicioAluno(struct listaAluno *paluno) {
	struct listaAluno *aux;
	if(paluno == NULL) {
		printf("nLista aluno vazia!");
		getch();
		return paluno;
	}
	aux = paluno;
	paluno = paluno->proximo;
	free(aux);
	return paluno;
}
void removeDepoisAluno(struct listaAluno *paluno) {
	struct listaAluno *aux;
	aux = paluno->proximo;
	paluno->proximo = aux->proximo;
	free(aux);
}
struct listaAluno *removeOrdenadoAluno(struct listaAluno *paluno, int px) {
	struct listaAluno *p, *q;
	if(paluno == NULL) {
		printf("\nNao ha aluno cadastrado!");
		getch();
		return paluno;
	}
	if(px == paluno->codigo) {
		return (removeInicioAluno(paluno));
	}
	p = paluno;
	q = p;
	while(q != NULL && q->codigo < px) {
		p = q;
		q = p->proximo;
	}
	if(q != NULL && q->codigo == px) {
		removeDepoisAluno(p);
	}
	else {
		printf("\nAluno nao cadastrado!");
	}
	return paluno;
}
void mostraAluno(struct listaAluno *paluno) {
	struct listaAluno *aux;
	aux = paluno;
	while(aux != NULL) {
		printf("\nAluno[%d] :::: Nome: %s, disciplina: %s", aux->codigo, aux->nome, aux->disc);
		aux = aux->proximo;
	}
	getch();
}
struct listaAluno *consultaAluno(struct listaAluno *paluno, int px) {
	struct listaAluno *p, *q;
	p = paluno;
	if(p == NULL) {
		printf("\nLista vazia!");
		getch();
		return p;
	}
	if(p->codigo == px) {
		printf("\nAluno[%d] :::: Nome: %s", p->codigo, p->nome);
		getch();
		return p;
	}
	q = p;
	while(q != NULL && q->codigo < px) {
		p = q;
		q = p->proximo;
	}
	if(q != NULL && q->codigo == px) {
		printf("\nAluno[%d] :::: Nome: %s", q->codigo, q->nome);
		getch();
	}
	else {
		printf("\nAluno nao cadastrado!");
		getch();
	}
	return q;
}
void alteraAluno(struct listaAluno *paluno, int px) {
	struct listaAluno *aux;
	aux = consultaAluno(paluno, px);
	if(aux->codigo == px) {
		printf("\nDigite o nome do aluno: ");
		fflush(stdin);
		gets(aux->nome);
	}
}

//Fun��es da estrutura disciplina
struct listaDisciplina *insereInicioDisciplina(struct listaDisciplina *pdisc, int px, char pn[NOMEDISCIPLINA], float pnt, float pf) {
	struct listaDisciplina *aux;
	aux = (struct listaDisciplina*)malloc(sizeof(struct listaDisciplina));
	aux->codigo = px;
	strcpy(aux->nome, pn);
	aux->nota = pnt;
	aux->frequencia = pf;
	aux->proximo = pdisc;
	pdisc = aux;
	return pdisc;
}
void insereDepoisDisciplina(struct listaDisciplina *pdisc, int px, char pn[NOMEDISCIPLINA], float pnt, float pf) {
	struct listaDisciplina *aux;
	aux = (struct listaDisciplina*)malloc(sizeof(struct listaDisciplina));
	aux->codigo = px;
	strcpy(aux->nome, pn);
	aux->nota = pnt;
	aux->frequencia = pf;
	aux->proximo = pdisc->proximo;
	pdisc->proximo = aux;
}
struct listaDisciplina *insereOrdenadoDisciplina(struct listaDisciplina *pdisc, int px, char pn[NOMEDISCIPLINA], float pnt, float pf) {
	struct listaDisciplina *p, *q;
	if(pdisc == NULL || px < pdisc->codigo) {
		return insereInicioDisciplina(pdisc, px, pn, pnt, pf);
	}
	p = pdisc;
	q = p;
	while(q != NULL && q->codigo < px) {
		p = q;
		q = p->proximo;
	}
	if(q == NULL || q->codigo > px) {
		insereDepoisDisciplina(p, px, pn, pnt, pf);
	}
	else {
		printf("\nDisciplina ja cadastrada!");
	}
	return pdisc;
}
struct listaDisciplina *removeInicioDisciplina(struct listaDisciplina *pdisc) {
	struct listaDisciplina *aux;
	if(pdisc == NULL) {
		printf("\nLista disciplina vazia!");
		getch();
		return pdisc;
	}
	pdisc = pdisc->proximo;
	return pdisc;
}
void removeDepoisDisciplina(struct listaDisciplina *pdisc) {
	struct listaDisciplina *aux;
	aux = pdisc->proximo;
	pdisc->proximo = aux->proximo;
	free(aux);
}
struct listaDisciplina *removeOrdenadoDisciplina(struct listaDisciplina *pdisc, int px) {
	struct listaDisciplina *p, *q;
	if(pdisc == NULL) {
		printf("\nNao ha disciplina cadastrada!");
		getch();
		return pdisc;
	}
	if(pdisc->codigo == px) {
		return removeInicioDisciplina(pdisc);
	}
	p = pdisc;
	q = p;
	while(q != NULL && q->codigo < px) {
		p = q;
		q = p->proximo;
	}
	if(q != NULL && q->codigo == px) {
		removeDepoisDisciplina(p);
	}
	else {
		printf("\nDisciplina nao cadastrada!");
	}
	return pdisc;
	
}
void mostraDisciplina(struct listaDisciplina *pdisc) {
	struct listaDisciplina *aux;
	if(pdisc == NULL) {
		printf("\nLista disciplina vazia!");
		getch();
	}
	aux = pdisc;
	while(aux != NULL) {
		printf("\nDisciplina[%d] :::: Nome: %s", aux->codigo, aux->nome);
		aux = aux->proximo;
	}
	getch();
}
struct listaDisciplina *consultaDisciplina(struct listaDisciplina *pdisc, int px) {
	struct listaDisciplina *p, *q;
	p = pdisc;
	if(p == NULL) {
		printf("\nLista disciplina vazia!");
		getch();
		return p;
	}
	if(p->codigo == px) {
		printf("\nDisciplina[%d] :::: Nome: %s", p->codigo, p->nome);
		getch();
		return p;
	}
	q = p;
	while(q != NULL && q->codigo < px) {
		p = q;
		q = p->proximo;
	}
	if(q != NULL && q->codigo == px) {
		printf("\nDisciplina[%d] :::: Nome: %s", q->codigo, q->nome);
		getch();
	}
	else {
		printf("\nDisciplina nao cadastrada!");
		getch();
	}
	return q;
}
void alteraDisciplina(struct listaDisciplina *pdisc, int px) {
	struct listaDisciplina *aux;
	aux = consultaDisciplina(pdisc, px);
	if(aux->codigo == px) {
		printf("\nDigite o nome da Disciplina: ");
		fflush(stdin);
		gets(aux->nome);
	}
}
void insereDisciplinaAluno(struct listaAluno *paluno, struct listaDisciplina *pdisc) {
	struct listaAluno *aux;
	struct listaDisciplina *discAluno;
	discAluno = NULL;
	discAluno = (listaDisciplina*)malloc(sizeof(listaDisciplina));
	aux = paluno;
	discAluno = pdisc;
	aux->disc = discAluno;
	
}

//Fun��es genericas
void opcaoAlunoDisciplina(int *op) {
	do{
		system("cls");
		printf("_____CONTROLE DISCIPLINAR_____\n\n");
		printf("\n1. ALUNO");
		printf("\n2. DISCIPLINA");
		printf("\n3. CADASTRAR DISCIPLINA PARA ALUNO");
		printf("\n4. SAIR");
		printf("\n\nDigite a opcao: ");
		scanf("%d", op);
	}while(*op < 1 || *op > 4);
}
void opcaoAluno(int *op) {
	do{
		system("cls");
		printf("_____ALUNO_____\n\n");
		printf("\n1. Buscar");
		printf("\n2. Inserir");
		printf("\n3. Alterar");
		printf("\n4. Mostar");
		printf("\n5. Excluir");
		printf("\n6. Menu Principal");
		printf("\n7. Sair");
		printf("\n\nDigite a opcao: ");
		scanf("%d", op);
	}while(*op < 1 || *op > 7);
}
void opcaoDisciplina(int *op) {
	do{
		system("cls");
		printf("_____DISCIPLINA_____\n\n");
		printf("\n1. Buscar");
		printf("\n2. Inserir");
		printf("\n3. Alterar");
		printf("\n4. Mostar");
		printf("\n5. Excluir");
		printf("\n6. Menu Principal");
		printf("\n7. Sair");
		printf("\n\nDigite a opcao: ");
		scanf("%d", op);
	}while(*op < 1 || *op > 7);
}
struct listaAluno *exeAluno(int *op, struct listaAluno *paluno) {
	int codigo;
	char nome[NOMEALUNO];
	opcaoAluno(op);
	switch(*op) {
		case 1:
			printf("\nCodigo do aluno para consulta: ");
			scanf("%d", &codigo);
			consultaAluno(paluno, codigo);
			break;
		case 2:
			printf("\nDigite o codigo do aluno: ");
			scanf("%d", &codigo);
			printf("\nDigite o nome do aluno: ");
			fflush(stdin);
			gets(nome);
			paluno = insereOrdenadoAluno(paluno, codigo, nome);
			break;
		case 3:
			printf("\nCodigo do aluno que deseja alterar: ");
			scanf("%d", &codigo);
			alteraAluno(paluno, codigo);
			break;
		case 4:
			mostraAluno(paluno);
			break;
		case 5:
			printf("\nCodigo do aluno que deseja remover: ");
			scanf("%d", &codigo);
			paluno = removeOrdenadoAluno(paluno, codigo);
			break;
		case 6:
			break;
		case 7:
			exit(0);
		default:
			break;
	}
	return paluno;
}
struct listaDisciplina *exeDisciplina(int *op, struct listaDisciplina *pdisc) {
	int codigo;
	char nome[NOMEALUNO];
	float nota, frequencia;
	opcaoDisciplina(op);
	switch(*op) {
		case 1:
				printf("\nCodigo da disciplina para consulta: ");
				scanf("%d", &codigo);
				consultaDisciplina(pdisc, codigo);
				break;
			case 2:
				printf("\nDigite o codigo da disciplina: ");
				scanf("%d", &codigo);
				printf("\nDigite o nome da disciplina: ");
				fflush(stdin);
				gets(nome);
				pdisc = insereOrdenadoDisciplina(pdisc, codigo, nome, nota, frequencia);
				break;
			case 3:
				printf("\nCodigo da disicplina que deseja alterar: ");
				scanf("%d", &codigo);
				alteraDisciplina(pdisc, codigo);
				break;
			case 4:
				mostraDisciplina(pdisc);	
				break;
			case 5:
				printf("\nCodigo da disicplina que deseja remover: ");
				scanf("%d", &codigo);
				pdisc = removeOrdenadoDisciplina(pdisc, codigo);
				break;
			case 6:
				break;
			case 7:
				exit(0);
			default:
				break;
	}
	return pdisc;
}
void exePrincipal(int *op, struct listaAluno *paluno, struct listaDisciplina *pdisc) {
	int codigo;
	do{
		opcaoAlunoDisciplina(op);
		
		if(*op == 4) exit(0);
		if(*op == 1) {
			do {
				paluno = exeAluno(op, paluno);
				if(*op == 6) exePrincipal(op, paluno, pdisc);
			}while(1);
		}
		if(*op == 2) {
			do {
				pdisc = exeDisciplina(op, pdisc);
				if(*op == 6) exePrincipal(op, paluno, pdisc);
			}while(1);
		}
		if(*op == 3) {
			mostraAluno(paluno);
			printf("\nCodigo do aluno para lancar disciplina: ");
			scanf("%d", &codigo);
			insereDisciplinaAluno(paluno, pdisc);
		}
	}while(1);
}

int main() {
	int op;
	struct listaAluno *al;
	struct listaDisciplina *disc;
	
	al = NULL;
	disc = NULL;
	
	al = insereOrdenadoAluno(al, 11, "Barros");
	al = insereOrdenadoAluno(al, 9, "Miguel");
	al = insereOrdenadoAluno(al, 10, "Sousa");
	al = insereOrdenadoAluno(al, 12, "Lucas");
	
	disc = insereOrdenadoDisciplina(disc, 1, "MD", 0, 0);
	disc = insereOrdenadoDisciplina(disc, 2, "ED", 0, 0);
	disc = insereOrdenadoDisciplina(disc, 5, "POO", 0, 0);
	disc = insereOrdenadoDisciplina(disc, 10, "Matem�tica discreta", 0, 0);
	
	
	exePrincipal(&op, al, disc);
		
	
	
	
	printf("\n\n\nFIM DO PROGRAMA!!!");
	getch();
	return 0;
}



