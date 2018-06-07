#include "SuperWindow.h"
#include "ui_SuperWindow.h"

SuperWindow::SuperWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperWindow)
{
    srand(0);
    ui->setupUi(this);
    this->setWindowTitle("Qt-Reversi");

    isStart = false;     //初始为还未计时
    timer = new QTimer;  //初始化定时器
    TimeRecord = new QTime(0, 0, 0); //初始化时间
    
    ui->Timer->setDigitCount(8);
    ui->Timer->setSegmentStyle(QLCDNumber::Flat);
    ui->Timer->display(TimeRecord->toString("mm:ss"));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));

    ui->BlackAI->addItem("human", HUMAN);
    ui->BlackAI->addItem("naive", NAIVE);
    ui->BlackAI->addItem("eva", EVA);
    ui->WhiteAI->addItem("human", HUMAN);
    ui->WhiteAI->addItem("naive", NAIVE);
    ui->WhiteAI->addItem("eva", EVA);

    /* Pieces[PieceSize][PieceSize] */
    Pieces.resize(PieceSize);
    for(int i = 0; i < PieceSize; i++){
        Pieces[i].resize(PieceSize);
    }

    QGridLayout* ChessBoardLayout = new QGridLayout;

    ChessBoardLayout->setMargin(0);
    ChessBoardLayout->setSpacing(0);

    /* Construct Pieces[PieceSize][PieceSize] */
    for(int i = 0; i < PieceSize; i++)
    {
        for(int j = 0; j < PieceSize; j++)
        {
            Pieces[i][j] = new Piece();
            Pieces[i][j]->setIndex(i, j);
            Pieces[i][j]->setFixedSize(40, 40);
            Pieces[i][j]->setIconSize(Pieces[i][j]->size());
            connect(Pieces[i][j], SIGNAL(DropPiece(int,int)), this, SLOT(getDropPiece(int,int)));

            ChessBoardLayout->addWidget(Pieces[i][j], i*40, j*40);
        }
    }

    connect(ui->Restart, SIGNAL(clicked(bool)), this, SLOT(Restart()));
    connect(ui->Undo, SIGNAL(clicked(bool)), this, SLOT(Undo()));
    connect(ui->Redo, SIGNAL(clicked(bool)), this, SLOT(Redo()));
    connect(ui->AI, SIGNAL(clicked(bool)), this, SLOT(AI()));

    ui->BlackPieceImage->setPixmap(QPixmap(":/Image/BlackChess.png").scaled(40, 40, Qt::KeepAspectRatio));
    ui->WhitePieceImage->setPixmap(QPixmap(":/Image/WhiteChess.png").scaled(40, 40, Qt::KeepAspectRatio));
    ui->ChessBoardLabel->setLayout(ChessBoardLayout);

    /* The Game Begin */
    Restart();
}

SuperWindow::~SuperWindow()
{
    delete ui;
}

void SuperWindow::Restart()
{
    


    BackUp.clear();
    BackUpState.clear();

    BackUp.resize(PieceSize * PieceSize);
    BackUpState.resize(PieceSize * PieceSize);

    for(int i = 0; i < PieceSize * PieceSize; i++){
        BackUp[i].resize(PieceSize);
        for(int j = 0; j < PieceSize; j++){
            BackUp[i][j].resize(PieceSize);
        }
    }

    for(int i = 0; i < PieceSize; i++)
    {
        for(int j = 0; j < PieceSize; j++)
        {
            Pieces[i][j]->setIcon(QIcon());
            Pieces[i][j]->type = Empty;
            BackUp[0][i][j] = Pieces[i][j]->type;
        }
    }

    state = OthelloState(PieceSize);
    BackUpState[0] = state;

    Pieces[PieceSize/2-1][PieceSize/2-1]->setIcon(QIcon(QPixmap(":/Image/WhiteChess.png"))); Pieces[PieceSize/2-1][PieceSize/2-1]->type = White;
    Pieces[PieceSize/2-0][PieceSize/2-0]->setIcon(QIcon(QPixmap(":/Image/WhiteChess.png"))); Pieces[PieceSize/2-0][PieceSize/2-0]->type = White;
    Pieces[PieceSize/2-1][PieceSize/2-0]->setIcon(QIcon(QPixmap(":/Image/BlackChess.png"))); Pieces[PieceSize/2-1][PieceSize/2-0]->type = Black;
    Pieces[PieceSize/2-0][PieceSize/2-1]->setIcon(QIcon(QPixmap(":/Image/BlackChess.png"))); Pieces[PieceSize/2-0][PieceSize/2-1]->type = Black;
    BackUp[0][PieceSize/2-1][PieceSize/2-1] = White;
    BackUp[0][PieceSize/2-0][PieceSize/2-0] = White;
    BackUp[0][PieceSize/2-1][PieceSize/2-0] = Black;
    BackUp[0][PieceSize/2-0][PieceSize/2-1] = Black;

    NumberOfBlack = 2;
    NumberOfWhite = 2;
    Player = Black;
    Enemy  = White;

    totalMove = MaxBackUpMove = 0;
    ui->BlackNumber->display(NumberOfBlack);
    ui->WhiteNumber->display(NumberOfWhite);

    AI();
}

void SuperWindow::getDropPiece(int row, int column)
{
    if(Pieces[row][column]->type != Empty){
        return;
    }

    int MaxEat = 0;

    for(int deltaY = -1; deltaY <= 1; deltaY++){
        for(int deltaX = -1; deltaX <= 1; deltaX++){

            if((deltaX == 0 && deltaY == 0) || row+deltaY == -1 || row+deltaY == PieceSize || column+deltaX == -1 || column+deltaX == PieceSize){
                continue;
            }

            int Eat = NumberOfPieceCanEat(row, column, deltaX, deltaY);

            if(Eat == 0){
                continue;
            }

            EatPieces(row, column, deltaX, deltaY);

            if(Player == Black){
                NumberOfBlack += Eat;
                NumberOfWhite -= Eat;
            }else{
                NumberOfWhite += Eat;
                NumberOfBlack -= Eat;
            }

            if(MaxEat < Eat){
                MaxEat = Eat;
            }
        }
    }

    if (MaxEat == 0){
        return;
    }

    DropThisPiece(row, column);

}

void SuperWindow::Undo()
{
    if(totalMove == 0){
        return;
    }

    totalMove--;

    for(int i = 0; i < PieceSize; i++)
    {
        for(int j = 0; j < PieceSize; j++)
        {
            Pieces[i][j]->type = BackUp[totalMove][i][j];
        }
    }
    state = BackUpState[totalMove];

    qSwap(Player, Enemy);
    Refresh();
}

void SuperWindow::Redo()
{
    if(MaxBackUpMove <= totalMove){
        return;
    }

    totalMove++;
    for(int i = 0; i < PieceSize; i++)
    {
        for(int j = 0; j < PieceSize; j++)
        {
            Pieces[i][j]->type = BackUp[totalMove][i][j];
        }
    }
    state = BackUpState[totalMove];

    qSwap(Player, Enemy);
    Refresh();
}

int SuperWindow::NumberOfPieceCanEat(int row, int column, int deltaX, int deltaY)
{
    int deltaRow = row + deltaY,
        deltaColumn = column + deltaX,
        eat = 0;

    while (deltaColumn != -1 && deltaRow != -1 && deltaColumn != PieceSize && deltaRow != PieceSize) {
        if(Pieces[deltaRow][deltaColumn]->type != Enemy){
            break;
        }

        deltaRow += deltaY;
        deltaColumn += deltaX;
        eat++;
    }

    if(deltaColumn == -1 || deltaRow == -1 || deltaColumn == PieceSize || deltaRow == PieceSize){
        return 0;
    }

    if(Pieces[deltaRow][deltaColumn]->type != Player || eat == 0){
        return 0;
    }

    return eat;
}

int SuperWindow::NumberOfPieceCanEatTotal(int row, int column)
{
    int TotalEat = 0;
    for(int deltaY = -1; deltaY <= 1; deltaY++){
        for(int deltaX = -1; deltaX <= 1; deltaX++){

            if((deltaX == 0 && deltaY == 0) || row+deltaY == -1 || row+deltaY == PieceSize || column+deltaX == -1 || column+deltaX == PieceSize){
                continue;
            }

            TotalEat += NumberOfPieceCanEat(row, column, deltaX, deltaY);
        }
    }

    return TotalEat;
}
void SuperWindow::saveResult() {
    puts("saving");
    PlayerType bp, wp;
    bp = (PlayerType)(ui->BlackAI->currentIndex());
    wp = (PlayerType)(ui->WhiteAI->currentIndex());
    
    string ai_names[5] = {"human", "naive", "eva"};
    int x = 0, y = 0, z = 0;
    string filename = ai_names[bp]+" vs "+ai_names[wp]+".txt";
    
    
    FILE* f = fopen(filename.c_str(), "r");
    if(f) {
        fscanf(f, "%d %d %d",&x,&y,&z);
        fclose(f);
    }

    if(NumberOfBlack == NumberOfWhite) z++;
    else if(NumberOfBlack > NumberOfWhite) x++;
    else if(NumberOfBlack < NumberOfWhite) y++;
    printf("Black Win: %d  White Win: %d  Tie: %d\n", x, y, z);
    
    f = fopen(filename.c_str(), "w");
    fprintf(f, "%d %d %d %.2lf", x, y, z, 1.0 * x / (x + y));
    fclose(f);
}
void SuperWindow::DropThisPiece(int row, int column)
{
    totalMove++;
    MaxBackUpMove = totalMove;

    if(row == -1) {
        BackUpState[totalMove] = BackUpState[totalMove-1];
        BackUp[totalMove] = BackUp[totalMove-1];
        state.skip();

    }
    else {
        cout << "move: " << row << " " << column << endl;
        state.DoMove(row, column);
        BackUpState[totalMove] = state;

        if(Player == Black){
            Pieces[row][column]->setIcon(QIcon(QPixmap(":/Image/BlackChess.png")));
            NumberOfBlack++;
        }else{
            Pieces[row][column]->setIcon(QIcon(QPixmap(":/Image/WhiteChess.png")));
            NumberOfWhite++;
        }

        Pieces[row][column]->type = Player;
        for(int i = 0; i < PieceSize; i++){
            for(int j = 0; j < PieceSize; j++){
                BackUp[totalMove][i][j] = Pieces[i][j]->type;
            }
        }

    }
//    state.ShowBoard();
    cout << " " << endl;

    ui->BlackNumber->display(NumberOfBlack);
    ui->WhiteNumber->display(NumberOfWhite);

    PlayerType pt, ept;
    if(Player == Black) {
        pt = (PlayerType)(ui->BlackAI->currentIndex());
        ept = (PlayerType)(ui->WhiteAI->currentIndex());
    } else {
        pt = (PlayerType)(ui->WhiteAI->currentIndex());
        ept = (PlayerType)(ui->BlackAI->currentIndex());
    }

    qSwap(Player, Enemy);


    if(totalMove >= PieceSize * PieceSize - 4) {
        saveResult();
        delay(5000);
        Restart();
        return;
    }


    unordered_set<PII, pair_hash> moves;
    state.GetAllMoves(moves);
    std::cout << "nex valid moves: " << moves.size() << std::endl;


    if(moves.size() == 0) {
        DropThisPiece(-1, -1);
    }
    else if(ept != HUMAN) {
        delay(200);
        AI();
    }
    else {
        PII m;
        clock_t start_time;
        start_time = clock();
        int time_limit = 2;
        m = naive::step(state, start_time, time_limit);
    }

   
}

void SuperWindow::EatPieces(int row, int column, int deltaX, int deltaY)
{
    int deltaRow = row + deltaY,
        deltaColumn = column + deltaX;

    if(deltaRow != -1 && deltaColumn != -1 && deltaRow != PieceSize && deltaColumn != PieceSize){
        /* Start Eating */
        int EatRow = row + deltaY,
            EatColumn = column + deltaX;

        while (EatRow != -1 && EatColumn != -1 && EatRow != PieceSize && EatColumn != PieceSize && Pieces[EatRow][EatColumn]->type != Player) {

            if(Player == Black){
                Pieces[EatRow][EatColumn]->setIcon(QIcon(QPixmap(":/Image/BlackChess.png")));
                Pieces[EatRow][EatColumn]->type = Black;
            }else{
                Pieces[EatRow][EatColumn]->setIcon(QIcon(QPixmap(":/Image/WhiteChess.png")));
                Pieces[EatRow][EatColumn]->type = White;
            }

            EatRow += deltaY;
            EatColumn += deltaX;
        }
    }
}

void SuperWindow::updateTime()
{
    // *TimeRecord = TimeRecord->addSecs(1);
    // ui->Timer->display(TimeRecord->toString("mm:ss"));
}
void SuperWindow::delay(int msec)
{
    QTime dieTime= QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void SuperWindow::AI()
{
    
    // TimeRecord->setHMS(0,0,0); //时间设为0
    // ui->Timer->display(TimeRecord->toString("mm:ss")); //显示00:00:00
    
    int MaxRow = 0, MaxColumn = 0;

    state = BackUpState[totalMove];
    pair<int, int> m = make_pair(-1, -1);
    PlayerType pt, ept;
    if(Player == Black) {
        pt = (PlayerType)(ui->BlackAI->currentIndex());
        ept = (PlayerType)(ui->WhiteAI->currentIndex());
    } else {
        pt = (PlayerType)(ui->WhiteAI->currentIndex());
        ept = (PlayerType)(ui->BlackAI->currentIndex());
    }
    
    clock_t start_time;
    start_time = clock();
    int time_limit = 5;

    if(pt == NAIVE) {
        m = naive::step(state, start_time, time_limit);
    }
    else if(pt == EVA) {
        m = eva::step(state, start_time, time_limit);
    }
    else {
        return;
    }

    TimeRecord->setHMS(0, (clock()-start_time)/(double)CLOCKS_PER_SEC/60, (clock()-start_time)/(double)CLOCKS_PER_SEC);
    ui->Timer->display(TimeRecord->toString("mm:ss"));

    MaxRow = m.first;
    MaxColumn = m.second;

    if (MaxRow != -1) {
        for(int deltaY = -1; deltaY <= 1; deltaY++){
            for(int deltaX = -1; deltaX <= 1; deltaX++){

                if((deltaX == 0 && deltaY == 0) || MaxRow+deltaY == -1 || MaxRow+deltaY == PieceSize || MaxColumn+deltaX == -1 || MaxColumn+deltaX == PieceSize){
                    continue;
                }

                int Eat = NumberOfPieceCanEat(MaxRow, MaxColumn, deltaX, deltaY);

                if(Eat == 0){
                    continue;
                }

                EatPieces(MaxRow, MaxColumn, deltaX, deltaY);

                if(Player == Black){
                    NumberOfBlack += Eat;
                    NumberOfWhite -= Eat;
                }else{
                    NumberOfWhite += Eat;
                    NumberOfBlack -= Eat;
                }
            }
        }
    }
    
    DropThisPiece(MaxRow, MaxColumn);
}

void SuperWindow::Refresh()
{
    NumberOfBlack = NumberOfWhite = 0;
    for(int i = 0; i < PieceSize; i++)
    {
        for(int j = 0; j < PieceSize; j++)
        {
            Pieces[i][j]->setIcon(QIcon());
            if(Pieces[i][j]->type == White){
                NumberOfWhite++;
                Pieces[i][j]->setIcon(QIcon(QPixmap(":/Image/WhiteChess.png")));
            }else if(Pieces[i][j]->type == Black){
                NumberOfBlack++;
                Pieces[i][j]->setIcon(QIcon(QPixmap(":/Image/BlackChess.png")));
            }else{
                Pieces[i][j]->setIcon(QIcon());
            }
        }
    }
    ui->BlackNumber->display(NumberOfBlack);
    ui->WhiteNumber->display(NumberOfWhite);
}
