 #ifndef OTHELLO_H
#define OTHELLO_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <vector>
#include "othello.h"
#include "ui_othello.h"
#include <QDebug>
#include <QGridLayout>
#include <QtCore/qglobal.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class Othello;
}
QT_END_NAMESPACE

class Othello : public QMainWindow
{
    Q_OBJECT

public:
    Othello(QWidget *parent = nullptr);


private:
    Ui::Othello *ui;
    std::vector<std::vector<QPushButton*>> buttons; // Initialize a 2D vector with size
    std::vector<int> turnMax_x;

private slots:
    bool buttonClick(std::vector<std::vector<QPushButton*>>buttons,int x, int y, int player, int opponent, bool IsAi,  QPushButton *btn, bool inspect,  QWidget* window, QGridLayout *layout, QLabel* label = new QLabel(""));

    bool isMovesLeft(vector<vector<QPushButton*>> buttons, int player, int opponent,QWidget* window, QGridLayout *layout);

    void turnButtonsXright(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);
    void turnButtonsXleft(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);
    void turnButtonsYup(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);
    void turnButtonsYdown(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);
    void turnButtonsVerRightUp(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);
    void turnButtonsVerRightDown(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);
    void turnButtonsVerLeftUp(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);
    void turnButtonsVerLeftDown(vector<vector<QPushButton*>> buttons, int y, int x, int j, int color);

    int correctAiMove(vector<vector<QPushButton*>> buttons, int player, int opponent,QWidget* window,  QGridLayout *layout,QLabel* label = new QLabel(""));

    void endGame(vector<vector<QPushButton*>> buttons, int player, int opponent,QWidget* window,  QGridLayout *layout,QLabel* label = new QLabel(""));

    void restartApplication();

    void changeColor(int player);



   // void correctMove(vector<vector<QPushButton*>> buttons, int x, int y, vector<int> turnMax_x);


/*
    void AiMove(vector<vector<QPushButton*>> buttons);
    void AiMove();
    void TurnButtons();
    void situation();
    void TurnButtons();
*/

private:
    QPushButton *button;
};
#endif // Othello_H


