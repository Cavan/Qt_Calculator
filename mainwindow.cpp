#include "mainwindow.h"
#include "ui_mainwindow.h"


double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i < 10;++i){
        QString btnName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(btnName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearDisplayPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();
    QString displayValue = ui->Display->text();
    if((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0)){
        ui->Display->setText(btnVal);
    } else{
        QString newVal = displayValue + btnVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void MainWindow::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();
    if(QString::compare(btnVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(btnVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(btnVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }else {
        subTrigger = true;
    }
    ui->Display->setText("");
}



void MainWindow::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dbDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dbDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dbDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dbDisplayVal;
        } else{
            solution = calcVal / dbDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}


void MainWindow::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9]*");
    if(reg.exactMatch(displayVal)){
        double dbDisplayVal = displayVal.toDouble();
        double dbDisplayValSign = -1 * dbDisplayVal;
        ui->Display->setText(QString::number(dbDisplayValSign));


    }
}

void MainWindow::ClearDisplayPressed(){
    QString displayVal = "0.0";
    ui->Display->setText(QString::number(0.0));
}




