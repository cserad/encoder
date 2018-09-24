#include "menu.h"

Menu::Menu()
{
    do {
        QString path;
        std::cout<<"Give path to dictionary:";
        QTextStream inputStream(stdin);
        path = inputStream.readLine();
        try {
            dict = new Dictionary(path);
        } catch (QException &exception) {
            qDebug() << exception.what();
        }
    } while(dict->getDictionaryToEncode()->isEmpty());
}

void Menu::printMenu()
{
    std::cout<<"ENCODE <string to be translated>\n";
    std::cout<<"DECODE <string to be translated>\n";
    std::cout<<"ENCODE_FILE <path to file to encode> <path to output file>\n";
    std::cout<<"DECODE_FILE <path to file to decode> <path to output file>\n";
    std::cout<<"EXIT\n";
}

bool Menu::getCommand()
{
    std::cout<<"Choose: ";
    QTextStream inputStream(stdin);
    QString input;
    input = inputStream.readLine();
    QString cmd = input.section(' ', 0, 0);
    if (cmd == "ENCODE") {
        QString tmp = input.section(' ', 1, -1);
        std::cout<<dict->encode(tmp).toStdString()<<std::endl;
        return true;
    } else if (cmd == "DECODE") {
        QString tmp = input.section(' ', 1, -1);
        std::cout<<dict->decode(tmp).toStdString()<<std::endl;
        return true;
    } else if (cmd == "ENCODE_FILE") {
        QString inPath = input.section(' ', 1, 1);
        QString outPath = input.section(' ', 2, 2);
        dict->encode(inPath, outPath);
        return true;
    } else if (cmd == "DECODE_FILE") {
        QString inPath = input.section(' ', 1, 1);
        QString outPath = input.section(' ', 2, 2);
        dict->decode(inPath, outPath);
        return true;
    } else if (cmd == "EXIT") {
        return false;
    } else {
        std::cout<<"Invalid command. Try again.\n";
        return true;
    }
}
