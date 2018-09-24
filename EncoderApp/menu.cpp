#include "menu.h"

Menu::Menu()
{
    while(dict->getDictionaryToEncode()->isEmpty()) {
        QString path;
        QTextStream outputStream(stdout);
        outputStream<<QStringLiteral("Give path to dictionary:");
        outputStream.flush();
        QTextStream inputStream(stdin);
        path = inputStream.readLine();
        try {
            dict = new Dictionary(path);
        } catch (QException &exception) {
            qDebug() << exception.what();
        }
    }
}

void Menu::printMenu()
{
    QTextStream outputStream(stdout);
    outputStream<<QStringLiteral("ENCODE <string to be translated>\n");
    outputStream<<QStringLiteral("DECODE <string to be translated>\n");
    outputStream<<QStringLiteral("ENCODE_FILE <path to file to encode> <path to output file>\n");
    outputStream<<QStringLiteral("DECODE_FILE <path to file to decode> <path to output file>\n");
    outputStream<<QStringLiteral("EXIT\n");
}

bool Menu::getCommand()
{
    QTextStream outputStream(stdout);
    outputStream<<QStringLiteral("Choose: ");
    outputStream.flush();
    QTextStream inputStream(stdin);
    QString input;
    input = inputStream.readLine();
    QString cmd = input.section(' ', 0, 0);
    if (cmd == "ENCODE") {
        QString tmp = input.section(' ', 1, -1);
        outputStream<<dict->encode(tmp)<<QStringLiteral("\n");
        return true;
    } else if (cmd == "DECODE") {
        QString tmp = input.section(' ', 1, -1);
        outputStream<<dict->decode(tmp)<<QStringLiteral("\n");
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
        outputStream<<QStringLiteral("Invalid command. Try again.\n");
        return true;
    }
}
