build:
	gcc src/main.c src/lista.c src/arquivos.c -o programa

clean:
	rm ./programa

fullClean:
	rm ./programa && rm -r -f ./data 