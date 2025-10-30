#include "othello.h"
#include "ui_othello.h"
#include <QDebug>
#include <QGridLayout>
#include <vector>
#include <QtCore/qglobal.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <QCoreApplication>
#include <QProcess>
#include <QTimer>


using namespace std;

Othello::Othello(QWidget *parent) : QMainWindow(parent) {
    QWidget *window = new QWidget;
    QGridLayout *layout = new QGridLayout;

    QLabel *label = new QLabel(" ", window);



    std::random_device rd;   // Seed generator
    std::mt19937 gen(rd());  // Mersenne Twister engine seeded with random_device
    std::uniform_int_distribution<> distr(0,1);

    int player = distr(gen);

    int opponent = abs(player-1);



    bool running = true;

    int size = 8;
    vector<vector<QPushButton*>> buttons(size, vector<QPushButton*>(size)); // Initialize a 2D vector with size

    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            QPushButton* button = new QPushButton(" ", this);
            button->setFixedSize(80, 80);

            if(i == 3 && j == 3 || i == 4 && j == 4) {
                button->setStyleSheet(
                    "QPushButton {"
                    "border-radius: 40px;"        // Half of the width/height for round shape
                    "background-color: #000000;"  // Button background color (black)
                    "color: white;"               // Text color
                    "border: 2px solid #2980b9;"  // Optional border with darker shade
                    "}"
                    );

                 button->setProperty("state", 0);
            } else if(i == 3 && j == 4 || i == 4 && j == 3) {
                button->setStyleSheet(
                    "QPushButton {"
                    "border-radius: 40px;"        // Half of the width/height for round shape
                    "background-color: #ffffff;"  // Button background color (white)
                    "color: white;"               // Text color
                    "border: 2px solid #2980b9;"  // Optional border with darker shade
                    "}"
                    );

                 button->setProperty("state", 1);
            } else {
                button->setStyleSheet(
                    "QPushButton {"
                    "border-radius: 40px;"        // Half of the width/height for round shape
                    "background-color: #808080;"  // Button background color (grey)
                    "color: white;"               // Text color
                    "border: 2px solid #2980b9;"  // Optional border with darker shade
                    "}"
                    );

                button->setProperty("state", -1);


            }

            // Add button to the vector
            buttons[i][j] = button;
        }
    }

    // Connect buttons to their slot
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            //"!"
            buttons = buttons;
            player = player;
            opponent = opponent;
            QPushButton *btn = buttons[i][j];
            connect(btn, &QPushButton::clicked, [this, i, j, buttons, window, btn, player, opponent, layout, label]() {
            buttonClick(buttons, j,i,player,opponent, false, btn, false, window, layout, label);});


            layout->addWidget(buttons[i][j], i, j);
        }
    }


    //do a function that reads the board and checks for victory (call funciton here)
    //if returns true, create a victory or defeat label

        layout->setHorizontalSpacing(10);
        layout->setVerticalSpacing(10);
        layout->setContentsMargins(0, 0, 500, 0);
        window->setLayout(layout);


        QPushButton *restart = new QPushButton("RESTART", window);
        restart->move(1000, 100);


        QString s_color = " ";

        if(player == 1){
            s_color = "WHITE";
        }
        else{
            s_color = "BLACK";
        }

        QPushButton *color = new QPushButton(QString("your color: %1").arg(s_color), window);
        color->move(1000, 200);

        connect(color, &QPushButton::clicked, [this, player](){
            changeColor(player);
        });


        connect(restart, &QPushButton::clicked, [this](){
            restartApplication();
        });



        label->move(1000, 200);


        window->show();





}


//call the check correct move in this function
//correct move function returns the coordinates of the gap to be turned to a certain color
//coordinates are passed to turnbutton function similar to now
//a 2 nested for loop is made where in each iteration correct move function is checked for each button
//if current button is correct, it's coordinates are passed to a vector
//a random choice is made from the vector coordinates which is then passed toif(!inspect){turnButtons function to create an ai move

void Othello::changeColor(int player){
    player = abs(player-1);
    qDebug()<<player;
}

bool Othello::buttonClick(vector<vector<QPushButton*>> buttons, int x, int y, int player, int opponent, bool IsAi, QPushButton *btn, bool inspect,  QWidget* window,  QGridLayout *layout, QLabel* label) {

    bool correct = false;

    vector<int> row;


    int size = 8;


    if(btn->property("state").toInt()==-1){

    if(x<size-1){

        QPushButton *btn2 = buttons[y][x+1];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop
            for(int j = x+1; j <= size-1; j++){
                if(buttons[y][j]->property("state").toInt()==-1){
                    break;
                }

                if(buttons[y][j]->property("state").toInt()==player){



                    if(!inspect){turnButtonsXright(buttons,y,x,j,player);}
                    correct = true;
                    break;
                }


            }

        }

    }

    if(x>0){

        QPushButton *btn2 = buttons[y][x-1];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop
            for(int j = x-1; j >= 0; j--){
                if(buttons[y][j]->property("state").toInt()==-1){
                    break;
                }

                if(buttons[y][j]->property("state").toInt()==player){



                    if(!inspect){turnButtonsXleft(buttons,y,x,j,player);}

                    correct = true;
                    break;
                }


            }

        }

    }


    //down

    if(y<size-1){

        QPushButton *btn2 = buttons[y+1][x];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop
            for(int j = y+1; j < size-1; j++){
                if(buttons[j][x]->property("state").toInt()==-1){
                    break;
                }

                if(buttons[j][x]->property("state").toInt()==player){

                    if(!inspect){turnButtonsYup(buttons,y,x,j,player);}

                    correct = true;
                    break;
                }


            }

        }



    }

    //up

    if(y>0){

        QPushButton *btn2 = buttons[y-1][x];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop
            for(int j = y-1; j >= 0; j--){
                if(buttons[j][x]->property("state").toInt()==-1){
                    break;
                }

                if(buttons[j][x]->property("state").toInt()==player){



                    if(!inspect){turnButtonsYdown(buttons,y,x,j,player);}

                    correct = true;
                    break;
                }


            }

        }

    }

    //vertical right up

    if(y>0 && x<size-1){
        QPushButton *btn2 = buttons[y-1][x+1];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop

            for(int i = y-1, j = x+1; i >= 0 && j < size; i--, j++){

                if(buttons[i][j]->property("state").toInt()==-1){

                    break;
                }


                if(buttons[i][j]->property("state").toInt()==player){

                    if(!inspect){turnButtonsVerRightUp(buttons,y,x,j,player);}

                    correct = true;
                    break;
                }


            }

        }

    }

    //vertical right down

    //problem when turning the buttons

    if(x > 0 && y<size-1 ){
        QPushButton *btn2 = buttons[y+1][x-1];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop

            for(int i = y+1, j = x-1;j > 0 && i < size; i++, j--){


                if(buttons[i][j]->property("state").toInt()==-1){

                    break;
                }


                if(buttons[i][j]->property("state").toInt()==player){


                    if(!inspect){turnButtonsVerRightDown(buttons,y,x,j,player);}

                    correct = true;
                    break;
                }


            }

        }

    }

    //vertical left up

    if(x > 0 && y>0){
        QPushButton *btn2 = buttons[y-1][x-1];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop

            for(int i = y-1, j = x-1;j > 0 && i > 0; i--, j--){


                if(buttons[i][j]->property("state").toInt()==-1){

                    break;
                }


                if(buttons[i][j]->property("state").toInt()==player){


                    if(!inspect){turnButtonsVerLeftUp(buttons,y,x,j,player);}

                    correct = true;
                    break;
                }


            }

        }

    }

    //vertical left down

    if(x < size-1 && y<size-1){
        QPushButton *btn2 = buttons[y+1][x+1];

        if(btn2->property("state").toInt()==opponent){
            //max_x for loop

            for(int i = y+1, j = x+1;j < size-1 && i <size-1; i++, j++){



                if(buttons[i][j]->property("state").toInt()==-1){

                    break;
                }


                if(buttons[i][j]->property("state").toInt()==player){


                    if(!inspect){turnButtonsVerLeftDown(buttons,y,x,j,player);}

                    correct = true;
                    break;
                }


            }

        }

    }

    }




    if(!IsAi && correct == true){

        if(isMovesLeft(buttons, abs(player-1),abs(opponent-1), window, layout) == true){
            correctAiMove(buttons, abs(player-1),abs(opponent-1), window, layout);

        }

        else{
            qDebug()<<"no moves left for AI!";

            if(isMovesLeft(buttons, player, opponent, window, layout) == false){
                endGame(buttons, player, opponent, window, layout, label);
                qDebug()<<"GAME B";
            }


        }

}





    return correct;


//*******************************************************


}


int Othello::correctAiMove(vector<vector<QPushButton*>> buttons, int player, int opponent, QWidget* window, QGridLayout *layout, QLabel* label){

    int size = 8;
    int min = 0;
    int max = size-1;

    std::random_device rd;   // Seed generator
    std::mt19937 gen(rd());  // Mersenne Twister engine seeded with random_device
    std::uniform_int_distribution<> distr(min, max);


    bool correct = false;

    while(!correct){
        int x = distr(gen);
        int y = distr(gen);

        QPushButton *btn = buttons[y][x];

        correct = buttonClick(buttons, x, y, player, opponent, true, btn, false, window, layout);


}

        if(isMovesLeft(buttons,  abs(player-1),abs(opponent-1), window, layout) == false){
            if(isMovesLeft(buttons,  player, opponent, window, layout) == false){
                qDebug()<<"GAME C";
                 endGame(buttons, opponent, player, window, layout);
                 return 0;

            }

            correctAiMove(buttons, player, opponent, window, layout, label);
        }





}




bool Othello::isMovesLeft(vector<vector<QPushButton*>> buttons, int player, int opponent, QWidget* window,  QGridLayout *layout){
    int size = 8;

    for(int y = 0; y<size; y++){
        for(int x = 0; x<size; x++){
            QPushButton *btn = buttons[y][x];

            if(buttonClick(buttons, x,y, player, opponent, true, btn, true, window, layout)== true){
                return true;
            }



        }
    }

    return false;
}


//****************************************************






//*************************************************


void Othello::endGame(vector<vector<QPushButton*>> buttons, int player, int opponent,QWidget* window,  QGridLayout *layout, QLabel* label){
    int size = 8;

    int player_score = 0;
    int op_score = 0;

    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            QPushButton *btn = buttons[i][j];

            if(btn->property("state").toInt() == player){
                player_score++;
            }
            else if(btn->property("state").toInt() == opponent){
                op_score++;
            }
        }
    }



    qDebug()<<player_score;
    qDebug()<<op_score;

    QString color;

    if(player_score > op_score){

        label->setText("YOU WIN!");

        color = "#00FF00";
    }
    else if( player_score < op_score){
        label->setText("YOU LOSE!");

        color = "#FF0000";
    }


    else{

        label->setText("TIE!");

        color = "#0000FF";

    }

    label->setStyleSheet(QString("QLabel { color: %1; font-size: 40px; }").arg(color));

    label->show();




}



void Othello::restartApplication() {
    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();

    // Start a new instance of the application with the same arguments
    QProcess::startDetached(program, arguments);

    // Exit the current application instance after a short delay
    QTimer::singleShot(0, qApp, &QCoreApplication::quit);
}





//********************************************************



void Othello::turnButtonsXright(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){


    for(int i = x; i<= j; i++){
        QPushButton *btn = buttons[y][i];
        if(color == 0){

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );
            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }
    }




void Othello::turnButtonsXleft(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){


    for(int i = x; i>= j; i--){
        QPushButton *btn = buttons[y][i];
        if(color == 0){

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }
}




void Othello::turnButtonsYup(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){


    for(int i = y; i<= j; i++){
        QPushButton *btn = buttons[i][x];
        if(color == 0){

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }
}





void Othello::turnButtonsYdown(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){


    for(int i = y; i >= j; i--){
        QPushButton *btn = buttons[i][x];
        if(color == 0){

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }
}

void Othello::turnButtonsVerRightUp(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){

// j = x+2;

    for(int u = y, r = x; r <= j; u--, r++){
        QPushButton *btn = buttons[u][r];
        if(color == 0){


            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }
}

void Othello::turnButtonsVerRightDown(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){
    for(int u = y, r = x; r >= j; u++, r-- ){
        QPushButton *btn = buttons[u][r];
        if(color == 0){


            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }

}
void Othello::turnButtonsVerLeftUp(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){
    for(int u = y, r = x; r >= j; u--, r-- ){

        QPushButton *btn = buttons[u][r];
        if(color == 0){


            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }

}
void Othello::turnButtonsVerLeftDown(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color){

    for(int u = y, r = x; r <= j; u++, r++){


        QPushButton *btn = buttons[u][r];
        if(color == 0){

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #000000;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 0);

        }

        else{

            btn->setStyleSheet(
                "QPushButton {"
                "border-radius: 40px;"        // Half of the width/height for round shape
                "background-color: #ffffff;"  // Button background color (grey)
                "color: white;"               // Text color
                "border: 2px solid #2980b9;"  // Optional border with darker shade
                "}"
                );

            btn->setProperty("state", 1);
        }

    }

}





//*****************************************************


/*
vector<int> rowX1;
vector<vector<int>> correctMovesXR;
vector<int> correctMovesXRLim;

vector<int> rowX2;
vector<vector<int>> correctMovesXL;
vector<int> correctMovesXLLim;


vector<int> rowY1;
vector<vector<int>> correctMovesY1;
vector<int> correctMovesY1Lim;


vector<int> rowY2;
vector<vector<int>> correctMovesY2;
vector<int> correctMovesY2Lim;



vector<int> rowVRU;
vector<vector<int>> correctMovesVRU;
vector<int> correctMovesVRULim;

vector<int> rowVRD;
vector<vector<int>> correctMovesVRD;
vector<int> correctMovesVRDLim;



vector<int> rowVLU;
vector<vector<int>> correctMovesVLU;
vector<int> correctMovesVLULim;

vector<int> rowVLD;
vector<vector<int>> correctMovesVLD;
vector<int> correctMovesVLDLim;


vector<vector<int>> combinedCorrect;*/




