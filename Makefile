
include makeinclude
include src/makeinclude
include appsrc/cxx/makeinclude

CFILES = $(SRC)
OBJECTS = $(CFILES:.cpp=$(OBJ))
TCFILES = $(TEST)
TOBJECTS = $(TCFILES:.cpp=$(OBJ))
CLCFILES = $(CXX_)
CLOBJECTS = $(CLCFILES:.cpp=$(OBJ))

all: $(OBJECTS) bin/$(LIBNAME) $(TOBJECTS) bin/test$(EXEEXT) bin/cxx$(EXEEXT)

bin/$(LIBNAME): $(OBJECTS)
	$(LIBCOMMAND)$@ $(OBJECTS) 

bin/test$(EXEEXT): $(TOBJECTS) $(OBJECTS)
	$(CXX) $(LDFLAGS) -mconsole -obin/test$(EXEEXT) $(LDLIBS) \
		-Wb-E,bin/libtest.exe.def \
		$(TOBJECTS) $(OBJECTS)  


clean:
	$(RM) bin/*.exe
	$(RM) bin/cl
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
	$(RM) vc80.idb

distclean: clean
	$(RM) config.status
	$(RM) build-stamp

depend:

install:

