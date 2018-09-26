#include "utils.h"

#include <QTextStream>

Utils::Utils()
{

}

QString Utils::getInput(const QString &text)
{
    QTextStream outputStream(stdout);
    QTextStream inputStream(stdin);

    outputStream<<text;
    outputStream.flush();

    return inputStream.readLine();
}
