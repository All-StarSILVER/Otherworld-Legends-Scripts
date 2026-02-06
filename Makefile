all: booncalc.exe atkspdcalc.exe critisbad.exe rosibomb.exe

booncalc.exe: booncalc.o utils/expressioncalc.o
	g++ -o booncalc.exe booncalc.o utils/expressioncalc.o

booncalc.o:
	g++ -c booncalc.cc

atkspdcalc.exe:
	g++ -o atkspdcalc.exe atkspdcalc.cc

critisbad.exe:
	g++ -o critisbad.exe critisbad.cc

rosibomb.exe: rosibomb.o utils/expressioncalc.o
	g++ -o rosibomb.exe rosibomb.o utils/expressioncalc.o

rosibomb.o:
	g++ -c rosibomb.cc

utils/expressioncalc.o:
	cd utils; g++ -c expressioncalc.cc; cd ..;

clean:
	rm *.exe *.o; rm utils/*.o;

clean_o:
	rm *.o