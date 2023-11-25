DESTDIR=
prefix=/usr
includedir=$(prefix)/include
libdir=$(prefix)/lib

INCLUDES = -I. -I/.
CXX_FLAGS = -fpic -Wall -Wl,--no-undefined
LD_FLAGS = -shared -lpthread -lmiutils -lmimodules -lmisound

SOURCES=miLamp.cpp miButton.cpp miButtonLamp.cpp miPlayWaveButtonLamp.cpp miVolume.cpp
OBJECTS=$(SOURCES:.cpp=.o)

LIBRARYOUT=libmicomponents.so


.cpp.o:
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $<
$(LIBRARYOUT):$(OBJECTS)
	$(CXX) $(LD_FLAGS) $(OBJECTS) -o $(LIBRARYOUT)
clean:
	$(RM) $(LIBRARYOUT) *.o
	

install: $(LIBRARYOUT)
	install -d $(DESTDIR)/${libdir}
	install -D -m 0644 $(LIBRARYOUT) $(DESTDIR)/${libdir}/$(LIBRARYOUT)
	install -d $(DESTDIR)/${includedir}
	install -d $(DESTDIR)/${includedir}/mi
	install -d $(DESTDIR)/${includedir}/mi/micomponents
	install -D -m 0644 miLamp.h $(DESTDIR)/${includedir}/mi/micomponents/miLamp.h
	install -D -m 0644 miButton.h $(DESTDIR)/${includedir}/mi/micomponents/miButton.h
	install -D -m 0644 miButtonLamp.h $(DESTDIR)/${includedir}/mi/micomponents/miButtonLamp.h
	install -D -m 0644 miPlayWaveButtonLamp.h $(DESTDIR)/${includedir}/mi/micomponents/miPlayWaveButtonLamp.h
	install -D -m 0644 miVolume.h $(DESTDIR)/${includedir}/mi/micomponents/miVolume.h
	install -D -m 0644 mibuttonLampMananger.h $(DESTDIR)/${includedir}/mi/micomponents/mibuttonLampMananger.h
	install -D -m 0644 miComponentInterface.h $(DESTDIR)/${includedir}/mi/micomponents/miComponentInterface.h