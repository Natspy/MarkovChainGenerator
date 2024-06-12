

#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {

    string text = "xyzxyzxyzxyzxyzxyzxyz";
    MarkovChain markovChain(text, 2);

    cout << "Random event following 'xy': " << markovChain.rand("xy") << endl;
    cout << "Generated sequence starting with 'xy': " << markovChain.gen("xy", 20) << endl;

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}

