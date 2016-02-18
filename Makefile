
all:
	(cd build; make all)

install:
	(cd build; make install)

clean:
	(cd build; make clean);

distclean:
	rm -f config.status
	(cd build; make distclean)

