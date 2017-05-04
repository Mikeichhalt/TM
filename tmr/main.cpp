#include <QCoreApplication>
#include <QProcess>

#include <QDebug>

#include "../tm/tmdefines.h"

QStringList modifiedParams();

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Q_UNUSED(a);

	QProcess p;
	p.setProgram("./tm");
	p.setArguments(modifiedParams());

	p.setProcessChannelMode(QProcess::ForwardedChannels);
	p.setInputChannelMode(QProcess::ForwardedInputChannel);
	p.start();
	p.waitForFinished(-1);
	return p.exitCode();
	//return QProcess::execute("./tm", modifiedParams());
}

QStringList modifiedParams(){
	auto params = QCoreApplication::arguments();
	params.removeFirst();
	return params;//TODO fix modifiedParams

	QStringList newParams;

	//0 R : $ R _
	newParams.append(QString("%1 %2 : %3 %2 _")
					 .arg(TM_STARTSTATE)
					 .arg(TM_RCODE)
					 .arg(TM_STOPSTATE));

	//0 T : % # >
	newParams.append(QString("%1 %2 : %3 %4 >")
					 .arg(TM_STARTSTATE)
					 .arg(TM_TCODE)
					 .arg(TM_FORBIDDENSTATE)
					 .arg(TM_BLANK));

	foreach(QString param, params) {
		if(param.at(0) == TM_STARTSTATE)
			param[0] = TM_FORBIDDENSTATE;
		if(param.at(6) == TM_STARTSTATE)
			param[6] = TM_FORBIDDENSTATE;

		newParams.append(param);
	}

	return newParams;
}
