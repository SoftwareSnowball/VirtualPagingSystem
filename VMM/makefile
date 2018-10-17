P = build
FLAGS = -std=c++1y

vmmmake: 
	g++ -c -o $(P)/io.o io/fileio.cc $(FLAGS)
	g++ -c -o $(P)/man.o memorymanager/memory_manager.cc $(FLAGS)
	g++ -c -o $(P)/back.o memorymanager/backingstore/backingstore_manager.cc $(FLAGS)
	g++ -c -o $(P)/mem.o memorymanager/memory/main_memory.cc $(FLAGS)
	g++ -c -o $(P)/page.o memorymanager/memory/page.cc $(FLAGS)
	g++ -c -o $(P)/table.o memorymanager/memory/page_table.cc $(FLAGS)
	g++ -c -o $(P)/tlb.o memorymanager/memory/tlb.cc $(FLAGS)
	g++ -c -o $(P)/main.o main.cc $(FLAGS)

	cd $(BUILDPATH)
	g++ -o vmm.exe $P/io.o $P/back.o $P/mem.o $P/page.o $P/table.o $P/tlb.o $P/man.o $P/main.o

