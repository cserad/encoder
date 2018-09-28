#include "menu.h"

#include "utils.h"

#include <QTextStream>
#include <QException>
#include <QDebug>

Menu::Menu()
{
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
    QString input;

    input = Utils::getInput(QStringLiteral("Choose:"));

    QString cmd = input.section(' ', 0, 0);

    if (cmd == "ENCODE") {
        QString tmp = input.section(' ', 1, -1);

        outputStream<<dict.encode(tmp.toLower())<<QStringLiteral("\n");

        return true;

    } else if (cmd == "DECODE") {
        QString tmp = input.section(' ', 1, -1);

        outputStream<<dict.decode(tmp.toLower())<<QStringLiteral("\n");

        return true;

    } else if (cmd == "ENCODE_FILE") {
        QString inPath = input.section(' ', 1, 1);
        QString outPath = input.section(' ', 2, 2);

        dict.encodeFile(Dictionary::FileModes::Encode, inPath, outPath);

        return true;

    } else if (cmd == "DECODE_FILE") {
        QString inPath = input.section(' ', 1, 1);
        QString outPath = input.section(' ', 2, 2);

        dict.encodeFile(Dictionary::FileModes::Decode, inPath, outPath);

        return true;

    } else if (cmd == "EXIT") {
        return false;
    } else {
        outputStream<<QStringLiteral("Invalid command. Try again.\n");

        return true;
    }
}

void Menu::loadDict()
{
    while(!dict.dictCreated) {
        QString path;
        path = Utils::getInput(QStringLiteral("Give path to dictionary:"));

        try {
            dict = Dictionary(path);
        } catch (QException &exception) {
            qDebug() << exception.what();
        }
    }
}
