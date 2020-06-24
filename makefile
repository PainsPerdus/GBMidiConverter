.PHONY : clean

bin/%.o : src/%.c include/%.h
	gcc -c $< -o $@

clean :
	rm -rf bin/*

bin/converter: bin/main.o
	gcc $^ -o $@