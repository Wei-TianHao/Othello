#include "Piece.h"

Piece::Piece(QWidget *parent) :
    QPushButton(parent)
{
    type = Empty;
}

void Piece::setIndex(int i, int j)
{
    row = i;
    column = j;
}

void Piece::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit DropPiece(row, column);
    }
}

