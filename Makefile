OBJEKTIT=quest.o apufunktiot.o kartta.o sankari.o komentotulkki.o nuoli.o
CCC=tutg++

quest: ${OBJEKTIT}
	${CCC} -o quest ${OBJEKTIT}

quest.o:apufunktiot.hh tiedot.hh kartta.hh sankari.hh quest.cc komentotulkki.hh komentotulkki.cc nuoli.hh nuoli.cc
	${CCC} -c quest.cc 

apufunktiot.o: apufunktiot.hh apufunktiot.cc sankari.hh sankari.cc tiedot.hh
	${CCC} -c apufunktiot.cc

apufunktiot.hh: tiedot.hh
	touch apufunktiot.hh

kartta.o: kartta.hh kartta.cc apufunktiot.hh apufunktiot.cc sankari.hh sankari.cc tiedot.hh
	${CCC} -c kartta.cc

sankari.o: sankari.hh sankari.cc
	${CCC} -c sankari.cc

sankari.hh: tiedot.hh
	touch sankari.hh

komentotulkki.o: komentotulkki.cc komentotulkki.hh
	${CCC} -c komentotulkki.cc

komentotulkki.hh: tiedot.hh
	touch komentotulkki.hh

nuoli.o: nuoli.hh nuoli.cc
	${CCC} -c nuoli.cc

nuoli.hh: tiedot.hh
	touch nuoli.hh

clean:
	rm -f quest ${OBJEKTIT} *~ core
