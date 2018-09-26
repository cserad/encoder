#include "dictionary.h"

#include <QFile>
#include <QDebug>
#include <QJsonObject>
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
        dictionary = QJsonDocument(QJsonDocument::fromJson(dictData));
    } catch (QException &exception) {
        qDebug() << exception.what();
    }

    //Make the dictionary to decode

    QJsonObject dictToEncodeObject = dictionary.object();
    QJsonObject dictToDecodeObject = QJsonObject();

    for (const auto &key : dictToEncodeObject.keys()) {
        QJsonValue value = dictToEncodeObject.value(key);
        dictToDecodeObject.insert(value.toString(), key);
    }

    try {
        reverseDictionary = QJsonDocument(dictToDecodeObject);
    } catch (QException &exception) {
        qDebug() << exception.what();
    }
}

Dictionary::~Dictionary()
{
}

QJsonDocument Dictionary::getDictionary() const
{
    return dictionary;
}

QJsonDocument Dictionary::getReverseDictionary() const
{
    return reverseDictionary;
}

QString Dictionary::encode(const QString &input)
{
    QString output;

    for (const auto &i : input) {
        QString actual(i);

        QJsonValue value = dictionary.object().value(actual);

        if (value == QJsonValue::Undefined) {
            return QString();
        } else {
            output += value.toString();
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

        QJsonValue value = reverseDictionary.object().value(actual);

        if (value != QJsonValue::Undefined) {
            output += value.toString();
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
}
