#include "object_separator.h"
#include <QtCore/QCoreApplication>
#include <QFile>
#include <QTextStream>
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
    QTextStream otherobj(&file_other);

    // output file objects_special.txt
    QTextStream specialobj(&file_special);

    // p3d path + file name only
    QString p3donly;
    QStringList p3donlylist;

    // bool for match found
    bool matchfound;
    long numOther = 0, numSpecial = 0;

    // depew header
    QString depewheader = objects.readLine();

    // initialize the headers for our new export files
    otherobj << depewheader << "\n";
    specialobj << depewheader << "\n";

    while (!objects.atEnd())
    {
        line = objects.readLine();
        line = line.toLower();
	// parse the real depew output into p3d path + file anme only
	p3donlylist = line.split(";");
	p3donly = p3donlylist[0];

	// compare and write accordingly to _other and _special files
	for (int i = 0; i < special_objects.size(); i++)
	{
		if ( p3donly.compare( special_objects[i] ) == 0)
		{
			// break the loop, we found our match.
			matchfound = true;
			break;
		}
	}

	if (matchfound)
	{
		// write out the special object
		specialobj << line << "\n";
		// stats ;)
		numSpecial++;
	}
	else
	{
		otherobj << line << "\n";
		numOther++;
	}
	// reset it back to falsehoood!
	matchfound = false;
    }

    qDebug() << "All done!\nObject Statistics:\nOther: " << numOther << "\nSpecial: " << numSpecial << "\n";

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

    while (!in.atEnd())
    {
        line = in.readLine();
        line = line.toLower();
	special_objects.append(line);
    }
    qDebug() << "Read " << special_objects.size() << " config lines.";

    file.close();
}
