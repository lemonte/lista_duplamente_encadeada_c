#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------ Geanderson e Luiz --------

typedef char string[20];

typedef struct tipoNo
{
	string nome;
	char sexo;
	tipoNo *ante, *prox;
} TNo;

typedef struct tipoLista
{
	int total;
	tipoNo *inicio;
	tipoNo *fim;
} TLista;

TLista lista;

void inicializa(TLista *L);
int menu();
void insere(TLista *L);
void exibe(TNo *atual);
void mostraLista(TLista *L);
void mostraListaInversa(TLista *L);
void reordenarPorSexoENome(TLista *L);
void remove(TLista *L);
void ordenarPorNome(TLista *L);

void trocarValores(TNo *n1, TNo *n2)
{
	TNo pivo;
	pivo.sexo = n1->sexo;
	strcpy(pivo.nome, n1->nome);
	n1->sexo = n2->sexo;
	strcpy(n1->nome, n2->nome);
	n2->sexo = pivo.sexo;
	strcpy(n2->nome, pivo.nome);
}

bool verificaEntradaSexoFeminino(char valor)
{
	if ((valor == 'F' || valor == 'f'))
		return true;
	return false;
}
bool verificaEntradaSexoMasculino(char valor)
{
	if ((valor == 'm' || valor == 'M'))
		return true;
	return false;
}

void reordenarPorSexoENome(TLista *L)
{
	if (L->total > 1)
	{
		TNo *sexo1 = L->inicio;
		while (sexo1 != NULL)
		{
			TNo *sexo2 = sexo1->prox;

			while (sexo2 != NULL)
			{
				if (sexo1->sexo < sexo2->sexo)
				{
					trocarValores(sexo1, sexo2);
				}
				sexo2 = sexo2->prox;
			}
			sexo1 = sexo1->prox;
		}

		TNo *nome1 = L->inicio;
		while (nome1 != NULL)
		{
			TNo *nome2 = nome1->prox;

			while (nome2 != NULL)
			{
				if (strcmp(nome1->nome, nome2->nome) == 1)
				{
					if ((verificaEntradaSexoFeminino(nome1->sexo) && verificaEntradaSexoFeminino(nome2->sexo)) || (verificaEntradaSexoMasculino(nome1->sexo) && verificaEntradaSexoMasculino(nome2->sexo)))
						trocarValores(nome1, nome2);
				}
				nome2 = nome2->prox;
			}
			nome1 = nome1->prox;
		}
	}
}

int main()
{
	int op;

	inicializa(&lista);

	do
	{
		op = menu();

		switch (op)
		{
		case 1:
			insere(&lista);
			break;
		case 2:
			ordenarPorNome(&lista);
			mostraLista(&lista);
			break;
		case 3:
			mostraListaInversa(&lista);
			break;
		case 4:
			// ordenarPorNome(&lista);
			reordenarPorSexoENome(&lista);
			mostraLista(&lista);
			break;
		case 5:
			remove(&lista);
			break;
		} // switch

	} while (op != 0);
}

void inicializa(TLista *L)
{
	L->inicio = NULL;
	L->fim = NULL;
	L->total = 0;
}

int menu()
{
	int opcao;
	system("CLS"); // Limpa a Tela e posiciona o
								 // CURSOR no canto esquerdo superior da mesma
	printf("\n\n\n\t     =====| MENU |=====\n\n");
	printf("0 - SAIR (Encerrar Programa).\n\n");
	printf("1 - Inserir.\n");
	printf("2 - Exibir Lista por Nome.\n");
	printf("3 - Exibir Lista Completa Invertida.\n");
	printf("4 - Exibir Lista Por Nome e Sexo.\n");
	printf("5 - Excluir.\n\n");
	printf("\tInforme OPCAO desejada: ");

	scanf("%d", &opcao);

	if ((opcao > 5) || (opcao < 0))
	{
		printf("\n\n\n");
		printf("\t+-------------------------------------------------+");
		printf("\t|   ERRO:                                         |");
		printf("\t|                                                 |");
		printf("\t|   OPCAO INVALIDA!!!                             |");
		printf("\t|                                                 |");
		printf("\t|   Tente outra vez.                              |");
		printf("\t+-------------------------------------------------+\n\n");
		system("PAUSE");
	}
	return opcao;
}

int removeElemento(TLista *L, TNo *atual, TNo *previo, TNo *proximo, string parametro)
{
	int removido = 0;
	while (atual != NULL)
	{
		if (strcmp(atual->nome, parametro) == 0)
		{
			proximo = atual->prox;
			previo = atual->ante;

			if (previo == NULL)
			{
				L->inicio = proximo;
				if (proximo != NULL)
					proximo->ante = NULL;
				if (atual == L->fim)
					L->fim = NULL;
			}
			else
			{
				previo->prox = proximo;
				if (proximo != NULL)
				{
					proximo->ante = previo;
				}
				else
				{
					L->fim = previo;
				}
			}

			free(atual);
			L->total--;
			removido = 1;
			break;
		} // if

		atual = atual->prox;
	}
	return removido;
}
void inserirPorNome(TLista *L, TNo *novo)
{
	int inserido = 0;
	if (L->inicio == NULL)
	{
		// Lista VAZIA: inserir o primeiro N?.
		L->inicio = novo;
		L->fim = novo;
	}
	else
	{
		// Lista possui pelo menos um N?: Inserir dados em
		// ordem crescente.
		TNo *atual = L->inicio;
		TNo *previo = NULL;

		while (atual != NULL)
		{
			if (strcmp(atual->nome, novo->nome) == -1)
			{
				inserido = 1;
				novo->prox = atual;
				novo->ante = atual->ante;

				if (novo->ante == NULL)
				{
					// Inserir novo no in?cio da Lista
					L->inicio = novo;
					atual->ante = novo;
				}
				else
				{
					// Inserir novo em algum ponto no meio da Lista
					previo = atual->ante;
					previo->prox = novo;

					atual->ante = novo;
				} // if else
				break;
			} // if

			atual = atual->prox; // movimenta ponteiro ATUAL para
													 // o N? SEGUINTE.
		}											 // while

		if (!inserido)
		{
			// Inserir novo no final da Lista
			L->fim->prox = novo;
			novo->ante = L->fim;
			L->fim = novo;
		} // if

	} // if ... else

	L->total++;
}
void removerElemento(TLista *L, TNo *elemento)
{
	if (elemento->ante == NULL)
	{
		L->inicio = elemento->prox;
		elemento->prox->ante = NULL;
	}
	else
	{
		if (elemento->prox == NULL)
		{
			L->fim = elemento->ante;
			elemento->ante->prox = NULL;
		}
		else
		{
			TNo *aux = elemento->ante;
			elemento->ante->prox = elemento->prox;
			elemento->prox->ante = elemento->ante;
		}
	}
	L->total = L->total - 1;
}
void ordenarPorNome(TLista *L)
{
	TNo *atual = L->inicio;
	while (atual != NULL)
	{
		removerElemento(L, atual);
		inserirPorNome(L, atual);
		atual = atual->prox;
	}
}


void insere(TLista *L)
{
	TNo *novo = (TNo *)malloc(sizeof(TNo));
	printf("\n\n\n");
	printf("\t=====| INSERE NOVO NO |=====\n\n");
	printf("\tInforme NOME:");
	scanf(" %s", novo->nome);
	printf("\tInforme SEXO:");
	do
	{
		printf("\tInforme SEXO:");
		scanf(" %c", &novo->sexo);
	} while (!verificaEntradaSexoMasculino(novo->sexo) && !verificaEntradaSexoFeminino(novo->sexo));
	novo->ante = NULL;
	novo->prox = NULL;
	inserirPorNome(L, novo);
}

void exibe(TNo *atual)
{
	printf("\n+-------------------+");
	printf("\n\t%s\n", atual->nome);
	printf("\n\t%c\n", atual->sexo);
}

void mostraLista(TLista *L)
{
	TNo *atual = L->fim;

	printf("\n\n\n");
	printf("\t=====| EXIBE LISTA COMPLETA |=====\n\n");

	while (atual != NULL)
	{
		exibe(atual);
		atual = atual->ante;
	} // while
	printf("\n\nTotal de Nos: %d\n\n", L->total);
	system("PAUSE");
}

void mostraListaInversa(TLista *L)
{
	TNo *atual = L->inicio;

	printf("\n\n\n");
	printf("\t=====| EXIBE LISTA INVERTIDA |=====\n\n");

	while (atual != NULL)
	{
		exibe(atual);
		atual = atual->prox;
	} // while
	printf("\n\nTotal de Nos: %d\n\n", L->total);
	system("PAUSE");
}

void remove(TLista *L)
{
	TNo *atual = L->inicio, *previo = NULL, *proximo = NULL;
	string parametro;
	int removido = 0;

	printf("\n\n\t=====| REMOVER No |=====\n\n");
	printf("\tInforme VALOR a ser REMOVIDO: ");
	scanf("%s", parametro);
	removido = removeElemento(L, atual, previo, proximo, parametro);
	// while

	if (removido)
	{
		printf("\n\n\n");
		printf("+--------------------------------------+\n");
		printf("|  AVISO:                              |\n");
		printf("|                                      |\n");
		printf("|  No REMOVIDO com SUCESSO !!!         |\n");
		printf("|                                      |\n");
		printf("+--------------------------------------+\n\n\n");
		system("PAUSE");
	}
	else
	{
		printf("\n\n\n");
		printf("+--------------------------------------+\n");
		printf("|  ALERTA:                             |\n");
		printf("|                                      |\n");
		printf("|  No NAO ENCONTRADO e nem REMOVIDO!!! |\n");
		printf("|                                      |\n");
		printf("+--------------------------------------+\n\n\n");
		system("PAUSE");
	}
}
