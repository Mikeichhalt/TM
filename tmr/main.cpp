#include <QCoreApplication>
#include <QProcess>

#include <QDebug>

#include "../tm/tmdefines.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Q_UNUSED(a);

	QString input = QTextStream(stdin).readAll();

	if(input.size() < 1){
		qFatal("input is to small");
		return EXIT_FAILURE;
	}

	auto code = input.at(0);
	if(code != TM_RCODE && code != TM_TCODE){
		qFatal("return code is missing");
		return EXIT_FAILURE;
	}

	if(code == TM_RCODE){
#ifdef TM_DEBUG
		qDebug() << "TM not called" << input;
#else
		qDebug("%s", qPrintable(input));
#endif
		return EXIT_SUCCESS;
	}

	input.remove(0, 1);//remove T at start
	input.resize(input.size() - 1);//remove \n at end

	QProcess p;
	p.setProgram("./tm");
	p.setArguments(QCoreApplication::arguments());
	p.setProcessChannelMode(QProcess::ForwardedErrorChannel);

	p.start();
	p.write(qPrintable(input));
	p.closeWriteChannel();
	p.waitForFinished(-1);

	QString output(p.readAll());

#ifndef TM_DEBUG
	output.insert(0, TM_TCODE);
#endif

	qDebug("%s", qPrintable(output));

	return p.exitCode();
}
