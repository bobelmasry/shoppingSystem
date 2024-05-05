#include "item.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Item::Item(QString n, int s, double p, QString c, QString b) : stock(s), price(p), category(c), brand(b), name(n)
{
    QFile file(":/assets/products.csv");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << n << "," << s << "," << p << "," << c << "," << b << Qt::endl;

        if (out.status() != QTextStream::Ok)
        {
            qWarning() << "Error writing data to file:" << out.status();
        }
        else
        {
            qDebug() << "Data successfully written to file.";
        }
    }
    else
    {
        qWarning() << "Failed to open file for writing:" << file.errorString();
    }

    file.close();
}
