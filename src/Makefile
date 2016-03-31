lab3: main.o bitoperation.o pager.o random.o vmm.o prepare.o
	g++ -o lab3 main.o bitoperation.o pager.o random.o vmm.o prepare.o

main.o: main.cpp
	g++ -c main.cpp

bitoperation.o: bitoperation.cpp bitoperation.h
	g++ -c bitoperation.cpp

pager.o: pager.cpp pager.h
	g++ -c pager.cpp

random.o: random.cpp random.h
	g++ -c random.cpp

vmm.o: vmm.cpp vmm.h
	g++ -c vmm.cpp

prepare.o: prepare.cpp prepare.h
	g++ -c prepare.cpp