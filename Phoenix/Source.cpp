#include "ConsoleHelper.h"
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#define ESTADO_JOGO_MENU_PRINCIPAL 0
#define ESTADO_JOGO_GAMEPLAY 1
#define ESTADO_JOGO_FIM 2
using namespace System;
using namespace Threading;
int main()
{
	double cps = CLOCKS_PER_SEC;
	clock_t inicio;
	double tempoJogo;
	inicio = clock();
	/*struct inimigo
	{
		int x;
		int y;
		bool visivel;
	};
	inimigo i1, i2, i3, i4, i5, i6;
	i1.x = 0;
	i1.y = 5;
	i1.visivel = true;
	i2.x = 5;
	i2.y = 10;
	i2.visivel = true;
	i3.x = 10;
	i3.y = 15;
	i3.visivel = true;
	i4.x = 0;
	i4.y = 5;
	i4.visivel = true;
	i5.x = 10;
	i5.y = 5;
	i5.visivel = true;
	i6.x = 15;
	i6.y = 10;
	i6.visivel = true;
	*/
	int playervisivel;
	int inimigo1_x = 0;
	int inimigo1_y = 5;
	bool inimigo1visivel = true;
	bool inimigo2visivel = true;
	int inimigo1_direcao = 1;
	const double VELOCIDADE_ATUALIZACAO_INIMIGO1 = 0.00000001f;
	double inimigo1_proximo_movimento = clock() / cps + VELOCIDADE_ATUALIZACAO_INIMIGO1;
	int inimigo2_x = 10;
	int inimigo2_y = 15;
	int inimigo2_direcao = 1;
	const double VELOCIDADE_ATUALIZACAO_INIMIGO2 = 0.1f;
	double inimigo2_proximo_movimento = clock() / cps + VELOCIDADE_ATUALIZACAO_INIMIGO2;
	const int TAMANHO_INIMIGO = 8;
	int projetil_x = 0;
	int projetil_y = 0;
	bool projetil_em_movimento = false;
	int estadoDoJogo = ESTADO_JOGO_MENU_PRINCIPAL;
	int player_y = 60;
	int player_x = 70;
	int inimigo1_tiro = false;
	int inimigo1_tirox;
	int inimigo1_tiroy = inimigo1_y;
	int inimigo2_tirox;
	int inimigo2_tiroy = inimigo2_y;
	int inimigo2_tiro = false;
	Console::SetWindowSize(120, 70);
	Console::SetBufferSize(120, 70);
	Console::CursorVisible = false;
	ConsoleKeyInfo tecla;
	for (;;)
	{
		switch (estadoDoJogo)
		{
		case ESTADO_JOGO_MENU_PRINCIPAL:
			Console::BackgroundColor = ConsoleColor::White;
			Console::Clear();
			
			ConsoleHelper::ImprimirASCIIExtended(30, 20, "ÛÛÛÛÛÛ  ÛÛ   ÛÛ  ÛÛÛÛÛÛ  ÛÛÛÛÛÛÛ ÛÛÛ    ÛÛ ÛÛ ÛÛ   ÛÛ ");
			ConsoleHelper::ImprimirASCIIExtended(30, 21, "ÛÛ   ÛÛ ÛÛ   ÛÛ ÛÛ    ÛÛ ÛÛ      ÛÛÛÛ   ÛÛ ÛÛ  ÛÛ ÛÛ  ");
			ConsoleHelper::ImprimirASCIIExtended(30, 22, "ÛÛÛÛÛÛ  ÛÛÛÛÛÛÛ ÛÛ    ÛÛ ÛÛÛÛÛ   ÛÛ ÛÛ  ÛÛ ÛÛ   ÛÛÛ   ");
			ConsoleHelper::ImprimirASCIIExtended(30, 23, "ÛÛ      ÛÛ   ÛÛ ÛÛ    ÛÛ ÛÛ      ÛÛ  ÛÛ ÛÛ ÛÛ  ÛÛ ÛÛ  ");
			ConsoleHelper::ImprimirASCIIExtended(30, 24, "ÛÛ      ÛÛ   ÛÛ  ÛÛÛÛÛÛ  ÛÛÛÛÛÛÛ ÛÛ   ÛÛÛÛ ÛÛ ÛÛ   ÛÛ");
			ConsoleHelper::ImprimirASCIIExtended(30, 28, "Pressione <ENTER> para comecar...");
			ConsoleKeyInfo tecla;
			if (Console::KeyAvailable)
			{
				tecla = Console::ReadKey(true);
				if (tecla.Key == ConsoleKey::Enter)
				{
					estadoDoJogo = ESTADO_JOGO_GAMEPLAY;
				}
			}
			break;
		case ESTADO_JOGO_GAMEPLAY:
			playervisivel = true;
			Console::BackgroundColor = ConsoleColor::Red;
			Console::Clear();
			if (projetil_em_movimento)
			{
				Console::SetCursorPosition(projetil_x, projetil_y);
				Console::ForegroundColor = ConsoleColor::White;
				ConsoleHelper::ImprimirASCIIExtended("Û");
			}
			if (Console::KeyAvailable)
			{
				tecla = Console::ReadKey(true);
				if (tecla.Key == ConsoleKey::LeftArrow && player_x > 0)
				{
					player_x--;
				}
				else if (tecla.Key == ConsoleKey::RightArrow && player_x < 113)
				{
					player_x++;
				}
				else if (tecla.Key == ConsoleKey::Spacebar)
				{
					projetil_em_movimento = true;
					projetil_x = player_x+3;
					projetil_y = player_y - 1;
				}
			}
			if (projetil_em_movimento)
			{
				projetil_y--;
				if (projetil_y == 0)
				{
					projetil_em_movimento = false;
				}
			}
			if (inimigo1_tiro)
			{
				Console::SetCursorPosition(inimigo1_tirox, inimigo1_tiroy);
				Console::ForegroundColor = ConsoleColor::White;
				ConsoleHelper::ImprimirASCIIExtended("Û");
			}
			if (inimigo1_x == player_x)
			{
				inimigo1_tirox = inimigo1_x + 4;
				inimigo1_tiroy = inimigo1_y;
				inimigo1_tiro = true;
			}
			if (inimigo1_tiro)
			{
				inimigo1_tiroy++;
				if (inimigo1_tiroy == 60)
				{
					inimigo1_tiro = false;
				}
			}
			if (inimigo2_tiro)
			{
				Console::SetCursorPosition(inimigo2_tirox, inimigo2_tiroy);
				Console::ForegroundColor = ConsoleColor::White;
				ConsoleHelper::ImprimirASCIIExtended("Û");
			}
			if (inimigo2_x == player_x)
			{
				inimigo2_tirox = inimigo2_x + 4;
				inimigo2_tiroy = inimigo2_y;
				inimigo2_tiro = true;
			}
			if (inimigo2_tiro)
			{
				inimigo2_tiroy++;
				if (inimigo2_tiroy == 60)
				{
					inimigo2_tiro = false;
				}
			}
			tempoJogo = clock() / cps;
			if (tempoJogo > inimigo1_proximo_movimento)
			{
				inimigo1_x = inimigo1_x + inimigo1_direcao;
				if (inimigo1_x + TAMANHO_INIMIGO == Console::WindowWidth || inimigo1_x == 0)
					inimigo1_direcao = inimigo1_direcao * -1;

				inimigo1_proximo_movimento = clock() / cps + VELOCIDADE_ATUALIZACAO_INIMIGO1;
			}
			if (tempoJogo > inimigo2_proximo_movimento)
			{
				inimigo2_x = inimigo2_x + inimigo2_direcao;
				if (inimigo2_x + TAMANHO_INIMIGO == Console::WindowWidth || inimigo2_x == 0)
					inimigo2_direcao = inimigo2_direcao * -1;

				inimigo2_proximo_movimento = clock() / cps + VELOCIDADE_ATUALIZACAO_INIMIGO2;
			}
			if (projetil_y == inimigo1_y)
			{
				if (projetil_x >= inimigo1_x && projetil_x <= inimigo1_x + TAMANHO_INIMIGO)
				{
					inimigo1visivel = false;
					projetil_em_movimento = false;
				}
			}
			
			if (projetil_y == inimigo2_y)
			{
				if (projetil_x >= inimigo2_x && projetil_x <= inimigo2_x + TAMANHO_INIMIGO)
				{
					inimigo2visivel = false;
					projetil_em_movimento = false;
				}
			}
			if (inimigo1_tiroy == player_y)
			{
				if (inimigo1_tirox >= player_x || inimigo1_tirox <= inimigo1_x)
				{
					playervisivel = false;
					inimigo1_tiro = false;
				}
			}
			if (inimigo2_tirox == player_x)
			{
				if (inimigo2_tiroy >= player_y && inimigo2_tiroy <= inimigo2_y + 8)
				{
					playervisivel = false;
					inimigo2_tiro = false;
				}
			}
			// Ü = ▄
			// ß = ▀
			// Û = █
			if (inimigo1visivel)
			{
				ConsoleHelper::ImprimirASCIIExtended(inimigo1_x, inimigo1_y, ConsoleColor::Red, ConsoleColor::Green, " Û ÛÛ Û ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo1_x, inimigo1_y + 1, ConsoleColor::Red, ConsoleColor::Magenta, "ÛÛ    ÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo1_x, inimigo1_y + 2, ConsoleColor::Red, ConsoleColor::Magenta, "ÛÛÛ  ÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo1_x, inimigo1_y + 3, ConsoleColor::Red, ConsoleColor::Magenta, "ÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo1_x, inimigo1_y + 4, ConsoleColor::Red, ConsoleColor::Magenta, "Û ÛÛÛÛ Û");
				ConsoleHelper::ImprimirASCIIExtended(inimigo1_x, inimigo1_y + 5, ConsoleColor::Red, ConsoleColor::Magenta, "Û  ÛÛ  Û");
				ConsoleHelper::ImprimirASCIIExtended(inimigo1_x, inimigo1_y + 6, ConsoleColor::Red, ConsoleColor::Green, "Û Û  Û Û");
			}
			if (inimigo2visivel)
			{
				ConsoleHelper::ImprimirASCIIExtended(inimigo2_x, inimigo2_y, ConsoleColor::Red, ConsoleColor::Green, " Û ÛÛ Û ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo2_x, inimigo2_y + 1, ConsoleColor::Red, ConsoleColor::Magenta, "ÛÛ    ÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo2_x, inimigo2_y + 2, ConsoleColor::Red, ConsoleColor::Magenta, "ÛÛÛ  ÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo2_x, inimigo2_y + 3, ConsoleColor::Red, ConsoleColor::Magenta, "ÛÛÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(inimigo2_x, inimigo2_y + 4, ConsoleColor::Red, ConsoleColor::Magenta, "Û ÛÛÛÛ Û");
				ConsoleHelper::ImprimirASCIIExtended(inimigo2_x, inimigo2_y + 5, ConsoleColor::Red, ConsoleColor::Magenta, "Û  ÛÛ  Û");
				ConsoleHelper::ImprimirASCIIExtended(inimigo2_x, inimigo2_y + 6, ConsoleColor::Red, ConsoleColor::Green, "Û Û  Û Û");
			}
			if (playervisivel)
			{
				ConsoleHelper::ImprimirASCIIExtended(player_x, player_y, ConsoleColor::Red, ConsoleColor::Magenta, "Û  Û  Û");
				ConsoleHelper::ImprimirASCIIExtended(player_x, player_y - 1, ConsoleColor::Red, ConsoleColor::Magenta, " Û Û Û ");
				ConsoleHelper::ImprimirASCIIExtended(player_x, player_y - 2, ConsoleColor::Red, ConsoleColor::Magenta, "  ÛÛÛ  ");
				ConsoleHelper::ImprimirASCIIExtended(player_x, player_y - 3, ConsoleColor::Red, ConsoleColor::Magenta, " Û Û Û ");
				ConsoleHelper::ImprimirASCIIExtended(player_x, player_y - 4, ConsoleColor::Red, ConsoleColor::Magenta, "Û  Û  Û");
			}
			if (inimigo1visivel == false && inimigo2visivel == false)
			{
				Console::Clear();
				ConsoleHelper::ImprimirASCIIExtended(30, 20, "PARABENS, VOCE GANHOU!!!");
			}
			/*if (playervisivel == false)
			{
				estadoDoJogo = ESTADO_JOGO_FIM;
			}
			break;
			case ESTADO_JOGO_FIM:
				Console::BackgroundColor = ConsoleColor::DarkRed;
				Console::Clear();
				ConsoleHelper::ImprimirASCIIExtended(30, 20, " ÛÛÛÛÛÛ   ÛÛÛÛÛ  ÛÛÛ    ÛÛÛ ÛÛÛÛÛÛÛ      ÛÛÛÛÛÛ  ÛÛ    ÛÛ ÛÛÛÛÛÛÛ ÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(30, 21, "ÛÛ       ÛÛ   ÛÛ ÛÛÛÛ  ÛÛÛÛ ÛÛ          ÛÛ    ÛÛ ÛÛ    ÛÛ ÛÛ      ÛÛ   ÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(30, 22, "ÛÛ   ÛÛÛ ÛÛÛÛÛÛÛ ÛÛ ÛÛÛÛ ÛÛ ÛÛÛÛÛ       ÛÛ    ÛÛ ÛÛ    ÛÛ ÛÛÛÛÛ   ÛÛÛÛÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(30, 23, "ÛÛ    ÛÛ ÛÛ   ÛÛ ÛÛ  ÛÛ  ÛÛ ÛÛ          ÛÛ    ÛÛ  ÛÛ  ÛÛ  ÛÛ      ÛÛ   ÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(30, 24, " ÛÛÛÛÛÛ  ÛÛ   ÛÛ ÛÛ      ÛÛ ÛÛÛÛÛÛÛ      ÛÛÛÛÛÛ    ÛÛÛÛ   ÛÛÛÛÛÛÛ ÛÛ   ÛÛ");
				ConsoleHelper::ImprimirASCIIExtended(30, 28, "Tecla ENTER para tentar novamente!");
				if (Console::KeyAvailable)
				{
					tecla = Console::ReadKey(true);
					if (tecla.Key == ConsoleKey::Enter)
					{
						estadoDoJogo = ESTADO_JOGO_GAMEPLAY;
					}
				}
			break;
			*/
		}//fecha o switch

		Threading::Thread::Sleep(16);
	}
	system("pause");
	return 0;
}