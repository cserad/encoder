#include "dictionary.h"

#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QException>

bool Dictionary::dictCreated = false;

Dictionary::Dictionary()
{
}

Dictionary::Dictionary(const QString &path)
{
    try {
        QFile dictFile(path);
        if (!dictFile.open(QFile::ReadOnly)) {
            qDebug() << QStringLiteral("Couldn't open file.");
        } else {
            dictCreated = true;
        }

        QByteArray dictData = dictFile.readAll();
        dictFile.close();

        QJsonDocument document = QJsonDocument::fromJson(dictData);
        dictionary = document.toVariant().toMap();

    } catch (QException &exception) {
        qDebug() << exception.what();
    }

    //Make the dictionary to decode

    QVariantMap tmp;

    foreach(const QString &key, dictionary.keys()) {
        QVariant value = dictionary.value(key);
        tmp.insert(value.toString(), key);
    }

    try {
        reverseDictionary = QVariantMap(tmp);
    } catch (QException &exception) {
        qDebug() << exception.what();
    }
}

Dictionary::~Dictionary()
{
}

QString Dictionary::encode(const QString &input)
{
    QString output;

    for (const auto &it : input) {
        if (dictionary.find(it) != dictionary.end()) {
            output += dictionary.value(it).toString();
        } else {
            return QString();
        }
    }

    return output;
}

QString Dictionary::decode(const QString &input)
{
    QString output;
    QString actual;

    for (const auto &i : input) {
        actual.append(i);

        if (reverseDictionary.find(actual) != reverseDictionary.end()) {
            output += reverseDictionary.value(actual).toString();
            actual.clear();
        }
    }

    if (actual.isEmpty()) {
        return output;
    } else {
        return QString();
    }
}

void Dictionary::encodeFile(const int &direction, const QString &in, const QString &out)
{
    QFile inFile(in);

    if (!inFile.open(QFile::ReadOnly)) {
        qDebug() << QStringLiteral("Couldn't open file.");
    }

    QTextStream inputStream(&inFile);
    QString input = inputStream.readAll();
    inFile.close();

    input = input.toLower().trimmed();

    QString output;

    if (direction == 0) {
        output = encode(input);
    } else {
        output = decode(input);
    }

    QFile outFile(out);

    if (!outFile.open(QFile::WriteOnly)) {
        qDebug() << QStringLiteral("Couldn't open file.");
    }

    QTextStream outputStream(&outFile);
    outputStream << output;

    outFile.close();
}
