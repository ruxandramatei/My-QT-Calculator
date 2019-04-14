#include "calculator.h"
#include "ui_calculator.h"

double calculatorValue = 0.0;
double memoryValue = 0.0;
double result = 0.0;

bool divisionTrigger = false;
bool multiplyTrigger = false;
bool addTrigger = false;
bool subtractTrigger = false;
bool numberTrigger = false;
QString operationsMade = "";
QString lastSign = "";

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calculatorValue));
    ui->DisplayOperations->setText("");
    QPushButton *numericButtons[10];//array to hold reference to all push buttons
    for(int i = 0; i < 10; i++){
        QString buttonName = "Button" + QString::number(i);//Make button name
        numericButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numericButtons[i],SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add,SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equals,SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign,SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->Clear,SIGNAL(released()), this, SLOT(ClearButtonPressed()));

    connect(ui->MemRecall,SIGNAL(released()), this, SLOT(MemoryRecallPressed()));
    connect(ui->MemAdd,SIGNAL(released()), this, SLOT(AddMemoryPressed()));
    connect(ui->MemSubtract,SIGNAL(released()), this, SLOT(SubtractMemoryPressed()));

    connect(ui->ClearOperations,SIGNAL(released()), this, SLOT(ClearOperationsPressed()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();

    QString displayValue = ui->Display->text();
    if(displayValue == ""){
        ui->Display->setText(buttonValue);
        numberTrigger = true;

    }else{
        QString newDisplayValue = displayValue + buttonValue;
        double dblNewDisplayValue = newDisplayValue.toDouble();
        numberTrigger = true;
        ui->Display->setText(QString::number(dblNewDisplayValue));
    }
}

void Calculator::MathButtonPressed(){
     divisionTrigger = false;
     multiplyTrigger = false;
     addTrigger = false;
     subtractTrigger = false;

     QString displayValue = ui->Display->text();
     if(displayValue != ""){
        calculatorValue += displayValue.toDouble();
        operationsMade += lastSign + displayValue + " ";
     }

     QPushButton *button = (QPushButton *) sender();
     QString buttonValue = button->text();

     if(QString::compare(buttonValue, "/",Qt::CaseInsensitive) == 0){
         lastSign = "/ ";
        divisionTrigger = true;
     }else if(QString::compare(buttonValue, "*",Qt::CaseInsensitive) == 0){
         lastSign = "* ";
         multiplyTrigger = true;
      }else if(QString::compare(buttonValue, "+",Qt::CaseInsensitive) == 0){
         lastSign = "+ ";
         addTrigger = true;
      }else if(QString::compare(buttonValue, "-",Qt::CaseInsensitive) == 0){
         lastSign = "- ";
         subtractTrigger = true;
      }
     ui->Display->setText("");
}

void Calculator::EqualButtonPressed(){
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    if(addTrigger || subtractTrigger || multiplyTrigger || divisionTrigger){
        if(addTrigger){
            if(numberTrigger == true){
                operationsMade += "+ " + displayValue;
                calculatorValue = calculatorValue + dblDisplayValue;
                numberTrigger = false;
            }else{
                operationsMade = displayValue;
                calculatorValue = dblDisplayValue;
            }
            addTrigger = false;
        }else if(subtractTrigger){
            if(numberTrigger == true){
                operationsMade += "- " + displayValue;
                calculatorValue = calculatorValue - dblDisplayValue;
                numberTrigger = false;
            }else{
                operationsMade = displayValue;
                calculatorValue = dblDisplayValue;
            }
            subtractTrigger = false;
        }else if(multiplyTrigger){
            if(numberTrigger == true){
                operationsMade += "* " + displayValue;
                calculatorValue = calculatorValue * dblDisplayValue;
                numberTrigger = false;
            }else{
                operationsMade = displayValue;
                calculatorValue = dblDisplayValue;
            }
            multiplyTrigger = false;
        }else if(divisionTrigger){
            if(numberTrigger == true){
                operationsMade += "/ " + displayValue;
                calculatorValue = calculatorValue / dblDisplayValue;
                numberTrigger = false;
            }else{
                operationsMade = displayValue;
                calculatorValue = dblDisplayValue;
            }
            divisionTrigger = false;
        }
        result = calculatorValue;
        operationsMade += (" = " + QString::number(result));
        operationsMade += "\r\n";
    }else{
        operationsMade = "";
        result = dblDisplayValue;
    }
    ui->Display->setText(QString::number(result));
    ui->DisplayOperations->setText(operationsMade);
    calculatorValue = 0.0;
    lastSign = "";

}

void Calculator::ChangeNumberSign(){
    QString displayValue = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayValue)){
        double dblDisplayValue = displayValue.toDouble();
        double dblDisplayValueSign = -1 * dblDisplayValue;
        ui->Display->setText((QString::number(dblDisplayValueSign)));
    }
}

void Calculator::ClearButtonPressed(){
    QPushButton *button = (QPushButton *) sender();
    QString buttonValue = button->text();

    result = 0.0;
    calculatorValue = 0.0;
    ui->Display->setText(QString::number(result));
    numberTrigger = false;
    lastSign = "";
}

void Calculator::AddMemoryPressed(){
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    if(addTrigger || subtractTrigger || multiplyTrigger || divisionTrigger){
        if(addTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue + dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            addTrigger = false;
        }else if(subtractTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue - dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            subtractTrigger = false;
        }else if(multiplyTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue * dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            multiplyTrigger = false;
        }else if(divisionTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue / dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            divisionTrigger = false;
        }
    }else{
        calculatorValue = dblDisplayValue;
    }
    memoryValue += calculatorValue;
    calculatorValue = 0;
    ui->Display->setText("");
}

void Calculator::SubtractMemoryPressed(){
    QString displayValue = ui->Display->text();
    double dblDisplayValue = displayValue.toDouble();
    if(addTrigger || subtractTrigger || multiplyTrigger || divisionTrigger){
        if(addTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue + dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            addTrigger = false;
        }else if(subtractTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue - dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            subtractTrigger = false;
        }else if(multiplyTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue * dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            multiplyTrigger = false;
        }else if(divisionTrigger){
            if(numberTrigger == true){
                calculatorValue = calculatorValue / dblDisplayValue;
                numberTrigger = false;
            }else{
                calculatorValue = dblDisplayValue;
            }
            divisionTrigger = false;
        }
    }else{
        calculatorValue = dblDisplayValue;
    }
    memoryValue -= calculatorValue;
    calculatorValue = 0;
    ui->Display->setText("");
}

void Calculator::MemoryRecallPressed(){
    ui->Display->setText(QString::number(memoryValue));
    memoryValue = 0.0;
    calculatorValue = 0.0;
}

void Calculator::ClearOperationsPressed(){
    ui->DisplayOperations->setText("");
    operationsMade = "";
}
