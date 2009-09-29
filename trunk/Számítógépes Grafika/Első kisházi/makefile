OBJS=
QTINCLUDES= \
	-I/usr/include/qt4/ \
	-I/usr/include/qt4/QtGui \
	-I/usr/include/qt4/QtCore

CXXFLAGS= -Wall -g #$(QTINCLUDES)
LIBS= -lglut #-lQtCore -lQtGui

nagyhazi: 
	g++ -o hazi elso.cpp $(CXXFLAGS) $(LIBS) $(OBJS)
clean: 
	rm *.o -r -f
