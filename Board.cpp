#include "stdafx.h"
#include "ChineseChess.h"
#include "Board.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBoard::CBoard()
{
	StackTop = 0;
	ply =0;
	MaxDepth = 5;
}

CBoard::~CBoard()
{

}

void CBoard::ClearBoard() //�����������
{
	int i;
	side = 0;
	for (i = 0; i < 256; i ++) 
	{
		board[i] = 0;
	}
}

//FEN�������Ӷ�Ӧ�������±�,�±�0��1��2��3��4��5��6�ֱ��Ӧ��ʾ�����ˣ����������ڣ���
int CBoard::CharToSubscript(char ch) 
{
	switch(ch)
	{
		case 'k':
		case 'K':return 0;
		case 'a':
		case 'A':return 1;
		case 'b':
		case 'B':return 2;
		case 'n':
		case 'N':return 3;
		case 'r':
		case 'R':return 4;
		case 'c':
		case 'C':return 5;
		case 'p':
		case 'P':return 6;
		default: return 7;
	}
}

//��������
void CBoard::AddPiece(int pos, int pc)
{
	board[pos] = pc;
	piece[pc] = pos;
}

//��FEN����ʾ�ľ���ת����һά����
void CBoard::StringToArray(const char *FenStr) 
{
	int i, j, k;
	int pcWhite[7] = {16,17,19,21,23,25,27};
	int pcBlack[7] = {32,33,35,37,39,41,43};
	const char *str;

	ClearBoard();
	str = FenStr;
	if (*str == '\0') 
	{
		return;
	}
  
	i = 3;
	j = 3;
	while (*str != ' ') 
	{
		if (*str == '/') 
		{
			j = 3;
			i++;
			if (i > 12) 
			{
				break;
			}
		} 
		else if (*str >= '1' && *str <= '9') 
		{
			for (k = 0; k < (*str - '0'); k ++) 
			{
				if (j >= 11) 
				{
					break;
				}
				j ++;
			}
		} 
		else if (*str >= 'A' && *str <= 'Z') 
		{
			if (j <= 11) 
			{
				k = CharToSubscript(*str);
				if (k < 7) 
				{
					if (pcWhite[k] < 32) 
					{
						AddPiece((i<<4)+j,pcWhite[k]);
						pcWhite[k]++;
					}
				}
				j ++;
			}
		}
		else if (*str >= 'a' && *str <= 'z') 
		{
			if (j <= 11) 
			{
				k = CharToSubscript(*str);
				if (k < 7) 
				{
					if (pcBlack[k] < 48) 
					{
						AddPiece((i<<4)+j,pcBlack[k]);
						pcBlack[k]++;
					}
				}
				j ++;
			}
		}
		
		str ++;
		if (*str == '\0') 
		{
			return;
		}
	}
  	str ++;
  
	if (*str == 'b')
	{
		side = 1;
	}
	else
	{
		side = 0;
	}
}
