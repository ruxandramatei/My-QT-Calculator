#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots: //this methods will be executed whenever a signal is executed
        void NumPressed();
        void MathButtonPressed();
        void EqualButtonPressed();
        void ChangeNumberSign();
        void ClearButtonPressed();
        void AddMemoryPressed();
        void SubtractMemoryPressed();
        void MemoryRecallPressed();
        void ClearOperationsPressed();
};

#endif // CALCULATOR_H
