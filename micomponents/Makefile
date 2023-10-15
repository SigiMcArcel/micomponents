

DESTDIR=
LIBDIR=/usr/lib
INCLUDEDIR=/usr/include

INCLUDES = -I. -I/.
CXX_FLAGS = -fpic -Wall
LD_FLAGS = -shared -lsndfile -lpthread -lasound

SOURCES=miButton.cpp miButtonLamp.cpp miPlayWaveButtonLamp.cpp miVolume.cpp
OBJECTS=$(SOURCES:.cpp=.o)

LIBRARYOUT=libmicomponents.so


.cpp.o:
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $<
$(LIBRARYOUT):$(OBJECTS)
	$(CXX) $(LD_FLAGS) $(OBJECTS) -o $(LIBRARYOUT)
clean:
	$(RM) $(LIBRARYOUT) *.o
	

install: $(LIBRARYOUT)
	mkdir -p $(DESTDIR)/$(LIBDIR)
	mkdir -p $(DESTDIR)/$(INCLUDEDIR)
	cp miButton.h $(DESTDIR)/$(INCLUDEDIR)
	cp miButtonLamp.h $(DESTDIR)/$(INCLUDEDIR)
	cp miPlayWaveButtonLamp.h $(DESTDIR)/$(INCLUDEDIR)
	cp miVolume.h $(DESTDIR)/$(INCLUDEDIR)
	cp $(LIBRARYOUT) $(DESTDIR)/$(LIBDIR)