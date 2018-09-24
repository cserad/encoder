#include "dictionary.h"

Dictionary::Dictionary(QString path)
{
    try {
        QFile dictFile(path);
        if (!dictFile.open(QFile::ReadOnly)) {
            qDebug() << QStringLiteral("Couldn't open file.");
        }

        QByteArray dictData = dictFile.readAll();
        dictionaryToEncode = new QJsonDocument(QJsonDocument::fromJson(dictData));
    } catch (QException &exception) {
        qDebug() << exception.what();
    }
    //Make the dictionary to decode
    QJsonObject dictToEncodeObject = dictionaryToEncode->object();
    QJsonObject *dictToDecodeObject = new QJsonObject();

    for (const auto &key : dictToEncodeObject.keys()) {
        QJsonValue value = dictToEncodeObject.value(key);
        dictToDecodeObject->insert(value.toString(), key);
    }

    try {
        dictionaryToDecode = new QJsonDocument(*dictToDecodeObject);
    } catch (QException &exception) {
        qDebug() << exception.what();
    }
}

Dictionary::~Dictionary()
{
}

QJsonDocument *Dictionary::getDictionaryToEncode() const
{
    return dictionaryToEncode;
}

QJsonDocument *Dictionary::getDictionaryToDecode() const
{
    return dictionaryToDecode;
}

QString Dictionary::encode(QString input)
{
    QString output;
    input = input.toLower();

    for (const auto &i : input) {
        QString actual(i);
        QJsonValue value = dictionaryToEncode->object().value(actual);
        if (value == QJsonValue::Undefined) {
            return QString();
        } else {
            output += value.toString();
        }
    }
    return output;
}

QString Dictionary::decode(QString input)
{
    QString output;
    QString actual;
    input = input.toLower();

    for (const auto &i : input) {
        actual.append(i);
        QJsonValue value = dictionaryToDecode->object().value(actual);
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

void Dictionary::encode(QString in, QString out)
{
    QFile inFile(in);
    if (!inFile.open(QFile::ReadOnly)) {
        qDebug() << QStringLiteral("Couldn't open file.");
    }
    QTextStream inputStream(&inFile);
    QString input = inputStream.readAll();

    QString output = encode(input.trimmed());

    QFile outFile(out);
    if (!outFile.open(QFile::WriteOnly)) {
        qDebug() << QStringLiteral("Couldn't open file.");
    }
    QTextStream outputStream(&outFile);
    outputStream << output;
}

void Dictionary::decode(QString in, QString out)
{
    QFile inFile(in);
    if (!inFile.open(QFile::ReadOnly)) {
        qDebug() << QStringLiteral("Couldn't open file.");
    }
    QTextStream inputStream(&inFile);
    QString input = inputStream.readAll();

    QString output = decode(input.trimmed());

    QFile outFile(out);
    if (!outFile.open(QFile::WriteOnly)) {
        qDebug() << QStringLiteral("Couldn't open file.");
    }
    QTextStream outputStream(&outFile);
    outputStream << output;
}
