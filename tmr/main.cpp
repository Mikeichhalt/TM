#include <QCoreApplication>
#include <QProcess>
#include <iostream>

#include <QDebug>

#include "../tm/tmdefines.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Q_UNUSED(a);

	QString input = QTextStream(stdin).readAll();

#ifdef INOUT_DEBUG
	std::cerr << "notErrTmr:" << qUtf8Printable(input) << std::endl;
#endif

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
		std::cout << qUtf8Printable(input);
		flush(std::cout);
#endif
		return EXIT_SUCCESS;
	}

	input.remove(0, 1);//remove T at start

	QProcess p;
	p.setProgram("./tm");
	auto params = QCoreApplication::arguments();
	params.removeFirst();
	p.setArguments(params);
	p.setProcessChannelMode(QProcess::ForwardedErrorChannel);

#ifdef INOUT_DEBUG
	std::cerr << "notErrTmrToTm:" << qUtf8Printable(input) << std::endl;
#endif

	p.start();
	p.write(qPrintable(input));
	p.closeWriteChannel();
	p.waitForFinished(-1);

	p.waitForReadyRead(-1);
	QString output(p.readAll());

#ifndef TM_DEBUG
	output.insert(0, TM_TCODE);
#endif

	std::cout << qUtf8Printable(output);
	flush(std::cout);

	return p.exitCode();
}
