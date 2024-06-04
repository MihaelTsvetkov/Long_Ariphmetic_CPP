#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "bignumber.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCalculate_clicked();
    void validateInput();
    void readPreviousAnswer();

private:
    QLineEdit* lineEditNumber1;
    QLineEdit* lineEditNumber2;
    QComboBox* comboBoxOperation;
    QPushButton* pushButtonCalculate;
    QLabel* labelResult;
    QLabel* labelError;
    QAction* actionReadPrevious;

    bool hasInvalidCharacters(const QString& input);
    void updateButtonState();
    void writeAnswerToFile(const QString& answer);
};

#endif // MAINWINDOW_H
