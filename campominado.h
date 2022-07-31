#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
//de 1 a 8 são bombas adjacentes, mas esse número está escondido.
//de 9 a 16 são bombas adjacentes, com o número visivel.
#define DESCONHECIDO (0)
#define BOMBA (-1)
#define LIMITE (-2)
#define VAZIO (-3)
#define EXPLO (-4)
#define VISIVEL + 8

void switchCampoPrint(int **m, int largura, int altura, int cursorX, int cursorY, int *cheat, int *instrucoes, int teclado); //decide o print do campo e das instrucoes
void printArray(int **m, int largura, int altura, int cursorX, int cursorY); //Elemtentos do Array
void printCampo(int **m, int largura, int altura, int cursorX, int cursorY); //Campo sem instrucoes
void printInst(int **m, int largura, int altura, int cursorX, int cursorY); //Campo com instrucoes
int **revelar(int **m, int largura, int altura, int cursorX, int cursorY); //marca como revelado no campo
void preparar_tabuleiro(int **m, int largura, int altura, int bombas); //marca as bombas e números não revelados
int vizinhanca(int **m, int x, int y, int largura, int altura); //checa as 8 posições em volta de uma no array
void mover(char teclado, int *cursorX, int *cursorY); //move o cursor
int desconhecidos(int **m, int largura, int altura); //retorna quantos elementos são desconhecidos pelo jogador
void malloc2d(int **m, int largura, int altura); // cria matriz 2d
void marcar(int **m, int largura, int altura); //marca as bombas como vistas
void zerarVetor(int *v, int tamanho); //coloca todas as posições de um vetor como 0
void free2d(int **m, int largura); //libera uma matriz 2d
void switchCampo(int elemento); //decide o que print-ar de acordo com o valor no campo
void inst(); // imprime as instruções
void vitoria(int **m, int largura, int altura, int cursorX, int cursorY, int cheat); //imprime o campo e a mensagem de vitoria
void derrota(int **m, int largura, int altura, int cursorX, int cursorY, int cheat); //idem derrota

int desconhecidos(int **m, int largura, int altura)
{
	int x, y,desconhecidos=0;
	for (x = 0; x < largura; x++)
	{
		for (y = 0; y < altura; y++)
		{
			if (m[x][y] == BOMBA || m[x][y] == DESCONHECIDO || (m[x][y] > 0 && m[x][y] <9))
				desconhecidos++;
		}
	}
	return desconhecidos;
}

void marcar(int **m, int largura, int altura)
{
	int x, y, desconhecidos = 0;
	for (x = 0; x < largura; x++)
	{
		for (y = 0; y < altura; y++)
		{
			if (m[x][y] == BOMBA)
				m[x][y] = EXPLO;
		}
	}
}

int **revelar(int **m, int largura, int altura, int cursorX, int cursorY)
{
	if (m[cursorX][cursorY] != DESCONHECIDO)
	{
		m[cursorX][cursorY] = m[cursorX][cursorY] VISIVEL;
		return m;
	}
	else
	{
		if (m[cursorX][cursorY] != BOMBA)
		{
			m[cursorX][cursorY] = -3;
			if (cursorX < largura - 1 && m[cursorX + 1][cursorY] < 9 && m[cursorX + 1][cursorY] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX + 1, cursorY);
			}
			if (cursorX > 0 && m[cursorX - 1][cursorY] < 9 && m[cursorX - 1][cursorY] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX - 1, cursorY);
			}
			if (cursorY > 0 && m[cursorX][cursorY - 1] < 9 && m[cursorX][cursorY - 1] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX, cursorY - 1);
			}
			if (cursorY < altura - 1 && m[cursorX][cursorY + 1] < 9 && m[cursorX][cursorY + 1] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX, cursorY + 1);
			}
			if (cursorY < altura - 1 && cursorX < largura - 1 && m[cursorX + 1][cursorY + 1] < 9 && m[cursorX + 1][cursorY + 1] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX + 1, cursorY + 1);
			}
			if (cursorY > 0 && cursorX > 0 && m[cursorX - 1][cursorY - 1] < 9 && m[cursorX - 1][cursorY - 1] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX - 1, cursorY - 1);
			}
			if (cursorX < largura - 1 && cursorY > 0 && m[cursorX + 1][cursorY - 1] < 9 && m[cursorX + 1][cursorY - 1] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX + 1, cursorY - 1);
			}
			if (cursorX > 0 && cursorY < altura - 1 && m[cursorX - 1][cursorY + 1] < 9 && m[cursorX - 1][cursorY + 1] != VAZIO)
			{
				m = revelar(m, largura, altura, cursorX - 1, cursorY + 1);
			}
			return m;
		}
		else
		{
			return m;
		}
	}
}

void malloc2d(int **m,int largura, int altura)
{
	int x, y;
	for (x = 0; x < largura; x++)
	{
		m[x] = (int*)malloc(altura*sizeof(int));
		if (m[x] != NULL)
		{
			zerarVetor(m[x], altura);
		}
		else
		{
			printf("Sem memória suficiente");
			exit(1);
		}
	}
}

void zerarVetor(int *v, int tamanho)
{
	int x;
	for (x = 0; x < tamanho; x++)
	{
		v[x] = 0;
	}
}

void printCampo(int **m, int largura, int altura, int cursorX, int cursorY)
{
	int x, y;
	for (x = 0; x < largura; x++)
	{
		for (y = 0; y < altura; y++)
		{
			if (x != cursorX || y != cursorY)
			{
				printf(" ");
				switchCampo(m[x][y]);
				printf("  ");
			}
			else
			{

				printf("{");
				switchCampo(m[x][y]);
				printf("} ");
			}
		}
		printf("\n");
	}
}

void printInst(int **m, int largura, int altura, int cursorX, int cursorY)
{
	int x, y;
	for (x = 0; x < largura; x++)
	{
		for (y = 0; y < altura; y++)
		{
			if (x != cursorX || y != cursorY)
			{
				printf(" ");
				switchCampo(m[x][y]);
				printf("  ");
			}
			else
			{

				printf("{");
				switchCampo(m[x][y]);
				printf("} ");
			}
		}
		printf("\n");
	}
	printf("\nPressione i para abrir instrucoes\n");
}

void printArray(int **m, int largura, int altura, int cursorX, int cursorY)
{
	int x, y;
	for (x = 0; x < largura; x++)
	{
		for (y = 0; y < altura; y++)
		{
			if (x != cursorX || y != cursorY)
			{
				printf(" %d ",m[x][y]);
			}
			else
			{
				printf("{%d}", m[x][y]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void inst()
{
	printf("\nInstrucoes:\n");
	printf("{ } Representa o cursor\n");
	printf("Pressione w para cima\n");
	printf("Pressione a para a esquerda\n");
	printf("Pressione s para baixo \n");
	printf("Pressione d para a direita\n");
	printf("Pressione q para revelar\n");
	printf("Qualquer outra tecla para sair\n");
	printf("- Representa uma regiao desconhecida\n");
	printf("* Representa uma bomba\n");
	printf("O Representa um espaco vazio\n");
	printf("Pressione i para fechar instrucoes\n");
	printf("Pressione 0 ou / para sair do jogo\n\n");
}
void free2d(int **m, int largura)
{
	for (int x = 0; x < largura; x++)
	{
		free(m[x]);
		m[x] = NULL;
	}
	free(m);
	m = NULL;
}

void preparar_tabuleiro(int **m, int largura, int altura, int bombas)
{
	int x;
	int	randX = (rand() % (largura - 1));
	int randY = (rand() % (altura - 1));
	for (x = 0; x < bombas; x++)
	{
		while (m[randX][randY] != 0)
		{
			randX = (rand() % (largura - 1));
			randY = (rand() % (altura - 1));
		}
		m[randX][randY] = BOMBA;
	}
	for (int x = 0; x < largura; x++)
	{
		for (int y = 0; y < altura; y++)
		{
			if (m[x][y] != -1)
			{
				m[x][y] = vizinhanca(m, x, y, largura, altura);
			}
		}
	}
}

void switchCampo(int elemento)
{
	switch (elemento)
	{
		case DESCONHECIDO:
		case BOMBA:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			printf("-");
			break;
		case LIMITE:
			printf("+");
			break;
		case VAZIO:
			printf("O");
			break;
		case EXPLO:
			printf("*");
			break;
		default:
			printf("%d",elemento-(VISIVEL));
			break;
	}
}

int vizinhanca(int **m, int x, int y, int largura, int altura)
{
	int bombas = 0;
	if (x < largura-1)
	{
		if (m[x + 1][y] == -1)
		{
			bombas++;
		}
		if (y > 0)
		{
			if (m[x + 1][y - 1] == -1)
			{
				bombas++;
			}
		}
		if (y < altura)
		{
			if (m[x + 1][y + 1] == -1)
			{
				bombas++;
			}
		}
	}
	if (x > 0)
	{
		if (m[x - 1][y] == -1)
		{
			bombas++;
		}
		if (y > 0)
		{
			if (m[x - 1][y - 1] == -1)
			{
				bombas++;
			}
		}
		if (y < altura)
		{
			if (m[x - 1][y + 1] == -1)
			{
				bombas++;
			}
		}
	}
	if (y < largura)
	{
		if (m[x][y + 1] == -1)
		{
			bombas++;
		}
	}
	if (y > 0)
	{
		if (m[x][y - 1] == -1)
		{
			bombas++;
		}
	}
		return bombas;
}

void mover(char teclado, int *cursorX, int *cursorY)
{
	switch (teclado)
	{
	case 'a':
			(*cursorY)--;
		break;
	case 'd':
			(*cursorY)++;
		break;
	case 'w':
			(*cursorX)--;
	break;
	case 's':
			(*cursorX)++;
	break;
	}
}

void switchCampoPrint(int **m, int largura, int altura, int cursorX, int cursorY, int *cheat, int *instrucoes, int teclado)
{
	switch (teclado)
	{
	case 'a':
	case 'd':
	case 'w':
	case 's':
		system("cls");
		if (*cheat == 1)
			printArray(m, largura, altura, cursorX, cursorY);
		if (*instrucoes == 1)
		{
			printCampo(m, largura, altura, cursorX, cursorY);
			inst();
		}
		else
			printInst(m, largura, altura, cursorX, cursorY);
		break;
	case 'e':
		system("cls");
		if (*cheat == 0)
		{
			*cheat = 1;
			printArray(m, largura, altura, cursorX, cursorY);
		}
		else
		{
			*cheat = 0;
		}
		if (*instrucoes == 1)
		{
			printCampo(m, largura, altura, cursorX, cursorY);
			inst();
		}
		else
		{
			printInst(m, largura, altura, cursorX, cursorY);
		}
		break;
	case 'q':
		system("cls");
		if (*cheat == 1)
		{
			printArray(m, largura, altura, cursorX, cursorY);
		}
		if (*instrucoes == 1)
		{
			printCampo(m, largura, altura, cursorX, cursorY);
			inst();
		}
		else
		{
			printInst(m, largura, altura, cursorX, cursorY);
		}
		break;
	case 'i':
		system("cls");
		if (*cheat == 1)
		{
			printArray(m, largura, altura, cursorX, cursorY);
		}
		if (*instrucoes == 0)
		{
			*instrucoes = 1;
			printCampo(m, largura, altura, cursorX, cursorY);
			inst();
		}
		else
		{
			*instrucoes = 0;
			printInst(m, largura, altura, cursorX, cursorY);
		}
		break;
	default:
		break;
	}
}

void derrota(int **m, int largura, int altura, int cursorX, int cursorY, int cheat)
{
	system("cls");
	m[cursorX][cursorY] = EXPLO;
	if (cheat == 1)
		printArray(m, largura, altura, cursorX, cursorY);
	printCampo(m, largura, altura, cursorX, cursorY);
	printf("\nDerrota\n");
}

void vitoria(int **m, int largura, int altura, int cursorX, int cursorY, int cheat)
{
	system("cls");
	marcar(m, largura, altura);
	if (cheat == 1)
		printArray(m, largura, altura, cursorX, cursorY);
	printCampo(m, largura, altura, cursorX, cursorY);
	printf("\nVitoria\n");
}