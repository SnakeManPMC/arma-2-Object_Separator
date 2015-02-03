#include <QtCore/QCoreApplication>
#include "object_separator.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Object_Separator sep;
	sep.RunMe(argc, argv);
	
    return 0;
}
