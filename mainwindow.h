#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include<parser.h>
QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Parser  * parser;
public slots:
 void equil();
 void erise();
 void addOne(){
     addChar('1');
 }
 void addTwo(){
      addChar('2');
 }
 void addThree(){
      addChar('3');
 }
 void addFour(){
      addChar('4');
 }
 void addFive(){
      addChar('5');
 }
 void addSix(){
      addChar('6');
 }
 void addSeven(){
      addChar('7');
 }
 void addEight(){
      addChar('8');
 }
 void addNine(){
      addChar('9');
 }
 void addZero(){
      addChar('0');
 }
 void addLeftBr(){
      addChar('(');
 }
 void addRightBr(){
      addChar(')');
 }
 void addDiv(){
      addChar('/');
 }
 void addMult(){
      addChar('*');
 }
 void addPlus(){
      addChar('+');
 }
 void addSub(){
      addChar('-');
 }
 void addMod(){
      addChar('%');
 }
 void addPow(){
      addChar('^');
 }
 void clearAll();
private:
    void addChar(QChar c);

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
