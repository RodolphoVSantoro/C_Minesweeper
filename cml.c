#include "cMinadoLinux.h"

int main()
{
	srand((unsigned)time(NULL));
	int largura, altura, bombas;
	printf("Largura:\n");
	scanf("%d",&largura);
	printf("Altura:\n");
	scanf("%d",&altura);
	printf("Quantidade de Bombas\n");
	scanf("%d",&bombas);
	clear;
	int teclado;
	int cursorX = largura / 2, cursorY = altura / 2;
	int cheat = 0, instrucoes = 0, contX, contY;
	int **m = (int**)malloc((largura)*sizeof(int*));
	
	malloc2d(m, largura, altura);
	preparar_tabuleiro(m, largura, altura, bombas);
	printInst(m, largura, altura, cursorX, cursorY);
	while ((teclado = getch()) != '0' && teclado != '/')
	{
		if ((teclado == 'a' && cursorY > 0) || (teclado == 'd' && cursorY < altura - 1) || (teclado == 'w' && cursorX > 0) || (teclado == 's' && cursorX < largura - 1))
		{
			mover(teclado, &cursorX, &cursorY);
			switchCampoPrint(m, largura, altura, cursorX, cursorY, &cheat, &instrucoes, teclado);
		}
		else
		{
			if (teclado == 'q')
			{
				if (m[cursorX][cursorY] == BOMBA)
				{
					derrota(m, largura, altura, cursorX, cursorY, cheat);
					break;
				}
				else
				{
					if (m[cursorX][cursorY] >= DESCONHECIDO && m[cursorX][cursorY] < 9)
					{
						m = revelar(m, largura, altura, cursorX, cursorY);
						if(desconhecidos(m,largura,altura) == bombas)
						{
							vitoria(m, largura, altura, cursorX, cursorY, cheat);
							break;
						}
						switchCampoPrint(m, largura, altura, cursorX, cursorY, &cheat, &instrucoes, teclado);
					}
				}
			}
			else
			{
				switchCampoPrint(m, largura, altura, cursorX, cursorY, &cheat, &instrucoes, teclado);
			}
		}
	}
	free2d(m, largura);
	pause;
	return 0;
}
