#include "chessboard.h"

ChessBoard::ChessBoard(int size, int x, int y, QObject *parent) :
    QObject(parent),
    tile(0),
    m_Board(NULL),
    m_Size(size),
    m_SpecialCubeX(x),
    m_SpecialCubeY(y)
{
    init(size,x,y);
}

ChessBoard::ChessBoard(QObject *parent):
    QObject(parent),
    tile(0),
    m_Board(NULL),
    m_Size(0),
    m_SpecialCubeX(0),
    m_SpecialCubeY(0)
{
}

ChessBoard::~ChessBoard()
{
    for(int i=0;i<m_Size;++i)
    {
        delete m_Board[i] ;
    }

    delete m_Board;
}

void ChessBoard::init(int size, int x, int y)
{
    m_Size = size;
    m_SpecialCubeX = x;
    m_SpecialCubeY = y;

    m_Board = new PINT[size];

    for(int i=0;i<size;++i)
    {
        m_Board[i] = new int[size];
        memset(m_Board[i],0,size * sizeof(int));
    }

    calculate(m_Board,0,0,x,y,size);
}

void ChessBoard::reset()
{
    tile = 0;

    calculate(m_Board,0,0,m_SpecialCubeX,m_SpecialCubeY,m_Size);
}

int ChessBoard::size() const
{
    return m_Size;
}

int ChessBoard::specialX() const
{
    return m_SpecialCubeX;
}

int ChessBoard::specialY() const
{
    return m_SpecialCubeY;
}

int ChessBoard::getMaxColorCount() const
{
    return tile;
}

int ChessBoard::value(int x, int y) const
{
    if(m_Board == NULL || x >= m_Size || y >= m_Size)
    {
        return -1;
    }

    return m_Board[x][y];
}

void ChessBoard::calculate(int **board, int tr, int tc, int dr, int dc, int size)
{
    if ( size==1 )
        return;
    int t=++tile;
    int s=size/2;

    if ( dr<tr+s && dc<tc+s )
        calculate (board, tr, tc, dr, dc, s );
    else
    {
        board[tr+s-1][tc+s-1]=t;
        calculate (board, tr, tc, tr+s-1, tc+s-1, s );
    }

    if ( dr<tr+s && dc>=tc+s )
        calculate (board, tr, tc+s, dr, dc, s );
    else
    {
        board[tr+s-1][tc+s]=t;
        calculate (board, tr, tc+s, tr+s-1, tc+s, s );
    }

    if ( dr>=tr+s && dc<tc+s )
        calculate (board, tr+s, tc, dr, dc, s );
    else
    {
        board[tr+s][tc+s-1]=t;
        calculate (board, tr+s, tc, tr+s, tc+s-1, s );
    }

    if ( dr>=tr+s && dc>=tc+s )
        calculate (board, tr+s, tc+s, dr, dc, s );
    else
    {
        board[tr+s][tc+s]=t;
        calculate (board, tr+s, tc+s, tr+s, tc+s, s );
    }
}

