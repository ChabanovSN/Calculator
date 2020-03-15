#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Супер-пупер калькулятор"));
    parser = new Parser();

    QAction * action(new QAction(this));
            action->setShortcuts(QList<QKeySequence>() << (Qt::CTRL + Qt::Key_Enter) << (Qt::CTRL + Qt::Key_Return));
            connect(action, SIGNAL(triggered(bool)), this, SLOT(equil()));
            this->addAction(action);


    connect(ui->equil,SIGNAL(clicked(bool)),this,SLOT(equil()));
    connect(ui->erise,SIGNAL(clicked(bool)),this,SLOT(erise()));
    connect( ui->one,SIGNAL(clicked(bool)),this,SLOT(addOne()));
    connect( ui->two,SIGNAL(clicked(bool)),this,SLOT(addTwo()));
    connect( ui->three,SIGNAL(clicked(bool)),this,SLOT(addThree()));
    connect( ui->four,SIGNAL(clicked(bool)),this,SLOT(addFour()));
    connect( ui->five,SIGNAL(clicked(bool)),this,SLOT(addFive()));
    connect( ui->six,SIGNAL(clicked(bool)),this,SLOT(addSix()));
    connect( ui->seven,SIGNAL(clicked(bool)),this,SLOT(addSeven()));
    connect( ui->eight,SIGNAL(clicked(bool)),this,SLOT(addEight()));
    connect( ui->nine,SIGNAL(clicked(bool)),this,SLOT(addNine()));
    connect( ui->zero,SIGNAL(clicked(bool)),this,SLOT(addZero()));
    connect( ui->leftBr,SIGNAL(clicked(bool)),this,SLOT(addLeftBr()));
    connect( ui->rightBr,SIGNAL(clicked(bool)),this,SLOT(addRightBr()));
    connect( ui->div,SIGNAL(clicked(bool)),this,SLOT(addDiv()));
    connect( ui->mult,SIGNAL(clicked(bool)),this,SLOT(addMult()));
    connect( ui->plus,SIGNAL(clicked(bool)),this,SLOT(addPlus()));
    connect( ui->substr,SIGNAL(clicked(bool)),this,SLOT(addSub()));
    connect( ui->mod,SIGNAL(clicked(bool)),this,SLOT(addMod()));
    connect( ui->pow,SIGNAL(clicked(bool)),this,SLOT(addPow()));
    connect(ui->clr,SIGNAL(clicked(bool)),this,SLOT(clearAll()));



}

void MainWindow::equil(){
    QString str = ui->screen->toPlainText();
    str.number(parser->evaluate(str));
    QString error =  parser->exeption->toString();

    if(error != "NULL"){
       // qDebug()<<"EXCEPTION !! "<<error;
        ui->screen->setPlainText(error);
    }
    else{
        ui->screen->clear();
        ui->screen->setPlainText(QString::number(parser->evaluate(str)));
        update();
    }
}

void MainWindow::erise(){
    QString str = ui->screen->toPlainText();
    str = str.left(str.length()-1);
    ui->screen->setPlainText(str);
}

void MainWindow::addChar(QChar c){
    //qDebug()<<"addChar(QChar c) "<<c;
    QString str = ui->screen->toPlainText();
    str += c;
    ui->screen->setPlainText(str);
}

void MainWindow::clearAll(){
    ui->screen->clear();
}



MainWindow::~MainWindow()
{
    delete ui;
    delete parser;
}

