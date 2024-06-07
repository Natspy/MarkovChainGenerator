

#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

    std::string text = "xyzxyzxyzxyzxyzxyzxyz";
    MarkovChain markovChain(text, 2);

    std::cout << "Frequency of 'xy': " << markovChain.freq("xy") << std::endl;
    std::cout << "Frequency of 'xy' followed by 'z': " << markovChain.freq("xy", "z") << std::endl;
    std::cout << "Random event following 'xy': " << markovChain.rand("xy") << std::endl;
    std::cout << "Generated sequence starting with 'xy': " << markovChain.gen("xy", 20) << std::endl;

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}

