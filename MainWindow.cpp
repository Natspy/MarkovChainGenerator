#include "QApplication"
#include "MainWindow.h"

#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QVBoxLayout>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    auto *centralWidget = new QWidget(this);

    auto *layout = new QVBoxLayout(centralWidget);

    loadButton = new QPushButton("Load Log File", this);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFile);

    kEventField = new QLineEdit(this);
    kEventField->setPlaceholderText("Enter initial k-event");

    lengthField = new QLineEdit(this);
    lengthField->setPlaceholderText("Enter length of sequence");

    generateButton = new QPushButton("Generate Sequence", this);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generateSequence);

    textArea = new QTextEdit(this);
    textArea->setPlaceholderText("Welcome to Markov Text Chain Generator!\nPlease provide the text file to generate from.");
    textArea->setReadOnly(true);

    layout->addWidget(loadButton);
    layout->addWidget(kEventField);
    layout->addWidget(lengthField);
    layout->addWidget(generateButton);
    layout->addWidget(textArea);

    setCentralWidget(centralWidget);
    setWindowTitle("Markov Chain Text Generator");
    resize(400, 300);
}


void MainWindow::loadFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Log File", "", "Text Files (*.txt)");
    if (!filePath.isEmpty()) {
        try {
            ifstream file(filePath.toStdString());
            if (!file.is_open()) {
                throw runtime_error("Failed to open file: " + filePath.toStdString());
            }
            string text;
            string line;
            while (getline(file, line)) {
                text += line;
            }

            markov = make_unique<MarkovChain>(text, 2);
            textArea->append("Loaded file: " + filePath + "\n");
        } catch (const exception &ex) {
            QMessageBox::warning(this, "Error", "Error reading file: " + QString::fromStdString(ex.what()));
        }
    }
}

void MainWindow::generateSequence() {
    if (markov) {
        QString kevent = kEventField->text();
        if (kevent.isEmpty() || lengthField->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Initial k-event or length of sequence cannot be empty!");
            return;
        }
        bool ok;
        int length = lengthField->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Error", "Please enter a valid integer for the length.");
            return;
        }
        QString result = QString::fromStdString(markov->gen(kevent.toStdString(), length));
        textArea->append("Generated sequence: " + result + "\n");
    } else {
        QMessageBox::warning(this, "Error", "Please load a log file first.");
    }
}

MainWindow::~MainWindow() {
    delete loadButton;
    delete kEventField;
    delete lengthField;
    delete generateButton;
    delete textArea;
}
