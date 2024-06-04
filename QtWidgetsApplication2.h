#ifndef QTWIDGETSAPPLICATION2_H
#define QTWIDGETSAPPLICATION2_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include "bignumber.h"

class QtWidgetsApplication2 : public QMainWindow {
    Q_OBJECT

public:
    QtWidgetsApplication2(QWidget* parent = nullptr);
    ~QtWidgetsApplication2();

private slots:
    void on_pushButtonCalculate_clicked();
    void validateInput();

private:
    QLineEdit* lineEditNumber1;
    QLineEdit* lineEditNumber2;
    QComboBox* comboBoxOperation;
    QPushButton* pushButtonCalculate;
    QLabel* labelResult;
    QLabel* labelError;

    bool hasInvalidCharacters(const QString& input);
    void updateButtonState();
};

#endif // QTWIDGETSAPPLICATION2_H
