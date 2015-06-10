#include "object_separator.h"
#include <QtCore/QCoreApplication>
#include <cstdio>
#include <cstdlib>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QStringList>
#include <QDebug>

Object_Separator::Object_Separator()
{
}


void Object_Separator::RunMe(int argc, char *argv[])
{
    QString line;

    if (argc < 4)
    {
	qDebug() << "Command line: \n" << "object_list other_output special_output my_special_objects";
        exit(0);
    }

    // open _objects.txt
    QFile file(argv[1]);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open " << file.fileName();
        exit(1);
    }

    qDebug() << "objects: " << file.fileName();

    // create _objects_other.txt
    QFile file_other(argv[2]);
    if (!file_other.open(QIODevice::WriteOnly | QIODevice::Text))
    {
            // error
            qDebug() << "There was error on" << file_other.fileName();
            exit(1);
    }

    qDebug() << "other: " << file_other.fileName();

    // create _objects_special.txt
    QFile file_special(argv[3]);
    if (!file_special.open(QIODevice::WriteOnly | QIODevice::Text))
    {
            // error
            qDebug() << "There was error on" << file_special.fileName();
            exit(1);
    }

    qDebug() << "special: " << file_special.fileName();

    // config file
    Config_Read(argv);

    // input file _objects.txt
    QTextStream objects(&file);

    // output file _objects_other.txt
    QTextStream other(&file_other);

    // output file objects_special.txt
    QTextStream specialobj(&file_special);

    while (!objects.atEnd())
    {
        line = objects.readLine();
        // compare and write accordingly to _other and _special files
        line = line.toLower();
        QMap<QString, QStringList>::iterator it;

        for ( it=coll.begin(); it != coll.end(); ++it )
        {
            if ( line.compare( it.key() ) == 0)
            {
                // write out the special object
                specialobj << line;
                // break the loop, we found our match.
                break;
            }
        }
    }

    file.close();
    file_other.close();
    file_special.close();
}


// read our replace list from config file
void Object_Separator::Config_Read(char *argv[])
{
    // open config file, list of special objects
    QFile file(argv[4]);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Unable to open " << file.fileName();
        exit(1);
    }
    QTextStream in(&file);

    qDebug() << "Opened config file: " << file.fileName();

    QString line;
    QStringList list;

    while (!in.atEnd())
    {
        line = in.readLine();
        line = line.toLower();

        for (int i = 0; i < list.size(); i++)
        {
            coll.insert( list[0], QStringList() << list[i] );
        }
    }
    qDebug() << "Read " << coll.size() << " config lines.";

    file.close();
}
