#ifndef SUPERWINDOW_H
#define SUPERWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGridLayout>
#include <QDebug>
#include <QDateTime>
#include <QElapsedTimer>
#include <QTimer>
#include <QTime>
#include "Piece.h"
#include "othello/OthelloState.hpp"
#include "othello/naive.hpp"
#include "othello/eva.hpp"
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <array>
#include <sstream>
#include <unistd.h>
#define PieceSize 8

typedef QVector< QVector<Piece*> > ChessPieces;
typedef QVector< QVector< QVector<Type> > > BACKUP;
typedef enum {
    HUMAN,
    NAIVE,
    EVA,
} PlayerType;

namespace Ui {
class SuperWindow;
}
using namespace std;
class SuperWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SuperWindow(QWidget *parent = 0);
    ~SuperWindow();

private:
    Ui::SuperWindow *ui;

    QTimer * timer;      //定时器 每秒更新时间
    QTime * TimeRecord;  //记录时间
    bool isStart;        //记录是否已经开始计时

    ChessPieces Pieces;
    int NumberOfPieceCanEat(int, int, int, int);
    int NumberOfPieceCanEatTotal(int, int);
    void DropThisPiece(int, int);
    void EatPieces(int, int, int, int);
    Type Player;
    Type Enemy;
    OthelloState state;
    int NumberOfBlack;
    int NumberOfWhite;
    int totalMove;
    int MaxBackUpMove;
    BACKUP BackUp;
    vector<OthelloState> BackUpState;
    void Refresh();

private slots:
    void getDropPiece(int, int );
    void Restart();
    void Undo();
    void Redo();
    void AI();
    void updateTime();
    void delay(int);
    void saveResult();
};

#endif // SUPERWINDOW_H
