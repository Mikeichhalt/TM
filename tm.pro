TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
TARGET = tm

SOURCES += main.c

DISTFILES += tm_dotAdd \
	tm_plus1 \
	tm_O \
	tm_nothing \
    tm_21

CONFIG(release, debug|release) {
	DEFINES += TRIM_OUTPUT
}
CONFIG(debug, debug|release) {
	DEFINES += TM_DEBUG
}

copydata.commands = $(COPY) $$PWD/tm_* $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
