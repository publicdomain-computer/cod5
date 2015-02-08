
include makeinclude
include src/makeinclude
include appsrc/cxx/makeinclude

CFILES = $(SRC)
OBJECTS = $(CFILES:.cpp=$(OBJ))
CLCFILES = $(CXX_)
CLOBJECTS = $(CLCFILES:.cpp=$(OBJ))

all: $(OBJECTS)  bin/cxx$(EXEEXT) bin/$(LIBNAME)

tests: all
	(cd tests; sh test.sh)

bin/$(LIBNAME): $(OBJECTS)
	$(LIBCOMMAND)$@ $(OBJECTS) 


bin/cxx$(EXEEXT): $(CLOBJECTS) $(OBJECTS)
	$(CXX) $(LDFLAGS)  -obin/cxx$(EXEEXT) $(LDLIBS) \
		$(CLOBJECTS) $(OBJECTS)  


clean:
	$(RM) bin/*.exe
	$(RM) tests/*.exe
	$(RM) tests/*.o
	$(RM) bin/cxx
	$(RM) bin/test
	$(RM) bin/*.so
	$(RM) cl/*~
	$(RM) test/*~
	$(RM) include/cc/*~
	$(RM) include/io/*~
	$(RM) include/lang/*~
	$(RM) include/test/*~
	$(RM) include/win32/*~
	$(RM) include/gfx/*~
	$(RM) src/cc/*~
	$(RM) src/io/*~
	$(RM) src/lang/*~
	$(RM) src/test/*~
	$(RM) src/win32/*~
	$(RM) src/gfx/*~
	$(RM) $(OBJECTS)
	$(RM) $(TOBJECTS)
	$(RM) $(CLOBJECTS)
	$(RM) vc80.idb
	$(RM) -r debian/cod5
	$(RM) debian/cod5.substvars
	$(RM) debian/cod5.debhelper.log
	$(RM) debian/files

distclean: clean
	$(RM) config.status
	$(RM) build-stamp

depend:

install:
	mkdir "$(DESTDIR)/usr"
	mkdir "$(DESTDIR)/usr/bin"
	$(CP) bin/cxx$(EXEEXT) "$(DESTDIR)/usr/bin/cxx"
	chmod +x "$(DESTDIR)/usr/bin/cxx"

