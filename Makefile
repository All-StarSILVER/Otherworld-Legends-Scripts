booncalc.exe: booncalc.o expressioncalc.o
	g++ -o booncalc.exe booncalc.o expressioncalc.o

booncalc.o:
	g++ -c booncalc.cc

atkspdcalc.exe:
	g++ -o atkspdcalc.exe atkspdcalc.cc

critisbad.exe:
	g++ -o critisbad.exe critisbad.cc

rosibomb.exe: rosibomb.o expressioncalc.o
	g++ -o rosibomb.exe rosibomb.o expressioncalc.o

rosibomb.o:
	g++ -c rosibomb.cc

expressioncalc.o:
	g++ -c expressioncalc.cc

clean:
	rm *.exe *.o