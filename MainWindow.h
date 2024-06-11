#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextEdit>

#include "MarkovChain.h"

using namespace std;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    private slots:
        void loadFile();
        void generateSequence();


private:
    QPushButton *loadButton;
    QLineEdit *kEventField;
    QLineEdit *lengthField;
    QPushButton *generateButton;
    QTextEdit *textArea;
    unique_ptr<MarkovChain> markov;
};

#endif // MAINWINDOW_H
