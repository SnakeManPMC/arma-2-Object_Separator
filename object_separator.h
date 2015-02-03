#ifndef OBJECT_SEPARATOR_H
#define OBJECT_SEPARATOR_H
#include <QFile>
#include <QMap>
#include <QStringList>
#include <QTextStream>

class Object_Separator
{
public:
	Object_Separator();
	void RunMe(int argc, char *argv[]);
	// for the replace objects string search
	QMap<QString, QStringList> coll;
	void Config_Read(char *argv[]);
};

#endif // OBJECT_SEPARATOR_H
