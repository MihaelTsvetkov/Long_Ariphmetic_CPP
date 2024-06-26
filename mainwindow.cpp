﻿#include "mainwindow.h"
#include <QDebug>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("BigNumber Calculator");
    this->setFixedSize(400, 350);

    lineEditNumber1 = new QLineEdit(this);
    lineEditNumber2 = new QLineEdit(this);
    comboBoxOperation = new QComboBox(this);
    pushButtonCalculate = new QPushButton("Calculate", this);
    labelResult = new QLabel(this);
    labelError = new QLabel(this);

    lineEditNumber1->setGeometry(50, 50, 300, 30);
    lineEditNumber2->setGeometry(50, 100, 300, 30);
    comboBoxOperation->setGeometry(50, 150, 300, 30);
    pushButtonCalculate->setGeometry(50, 200, 300, 30);
    labelResult->setGeometry(50, 250, 300, 30);
    labelError->setGeometry(50, 300, 300, 30);
    labelError->setStyleSheet("QLabel { color : red; }");

    comboBoxOperation->addItem("+");
    comboBoxOperation->addItem("-");
    comboBoxOperation->addItem("*");

    QMenu* menu = menuBar()->addMenu("Options");
    actionReadPrevious = new QAction("Read Previous Answer", this);
    menu->addAction(actionReadPrevious);

    connect(pushButtonCalculate, &QPushButton::clicked, this, &MainWindow::on_pushButtonCalculate_clicked);
    connect(lineEditNumber1, &QLineEdit::textChanged, this, &MainWindow::validateInput);
    connect(lineEditNumber2, &QLineEdit::textChanged, this, &MainWindow::validateInput);
    connect(actionReadPrevious, &QAction::triggered, this, &MainWindow::readPreviousAnswer);

    validateInput();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButtonCalculate_clicked() {
    QString number1Str = lineEditNumber1->text();
    QString number2Str = lineEditNumber2->text();
    QString operation = comboBoxOperation->currentText();

    if (number1Str.isEmpty() || number2Str.isEmpty()) {
        labelError->setText("Input numbers are required.");
        return;
    }

    BigNumber number1(number1Str.toStdString());
    BigNumber number2(number2Str.toStdString());
    BigNumber result("0");

    if (operation == "+") {
        result = number1 + number2;
    }
    else if (operation == "-") {
        result = number1 - number2;
    }
    else if (operation == "*") {
        result = number1 * number2;
    }

    QString resultStr = QString::fromStdString(result.toString());
    labelResult->setText(resultStr);
    labelError->clear();

    writeAnswerToFile(resultStr);
}

void MainWindow::validateInput() {
    bool valid = true;
    if (hasInvalidCharacters(lineEditNumber1->text())) {
        labelError->setText("Invalid input in Number 1 field.");
        valid = false;
    }
    if (hasInvalidCharacters(lineEditNumber2->text())) {
        labelError->setText("Invalid input in Number 2 field.");
        valid = false;
    }
    if (valid) {
        labelError->clear();
    }
    updateButtonState();
}

bool MainWindow::hasInvalidCharacters(const QString& input) {
    for (QChar c : input) {
        if (!c.isDigit()) {
            return true;
        }
    }
    return false;
}

void MainWindow::updateButtonState() {
    bool enableButton = !hasInvalidCharacters(lineEditNumber1->text()) &&
        !hasInvalidCharacters(lineEditNumber2->text()) &&
        !lineEditNumber1->text().isEmpty() &&
        !lineEditNumber2->text().isEmpty();
    pushButtonCalculate->setEnabled(enableButton);
}

void MainWindow::writeAnswerToFile(const QString& answer) {
    QFile file("previous_answer.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << answer;
        file.close();
    }
    else {
        qWarning() << "Unable to open file for writing";
    }
}

void MainWindow::readPreviousAnswer() {
    QFile file("previous_answer.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString answer = in.readLine();
        labelResult->setText(answer);
        file.close();
    }
    else {
        qWarning() << "Unable to open file for reading";
    }
}
