#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QPoint>


class ChessBoard : public QObject
{
    Q_OBJECT
public:
    typedef int *   PINT;

public:
    explicit ChessBoard(int size,int x,int y,QObject *parent = 0);
    explicit ChessBoard(QObject *parent);

    ~ChessBoard();

    void init(int size,int x,int y);
    void reset();

    int size() const;
    int specialX()const;
    int specialY()const;
    int getMaxColorCount()const;
    int value(int x,int y)const;

protected:
    void calculate(int ** board, int tr, int tc, int dr, int dc, int size );

private:
    int         tile;
    PINT *      m_Board;
    int         m_Size;
    int         m_SpecialCubeX;
    int         m_SpecialCubeY;
};

#endif // CHESSBOARD_H
