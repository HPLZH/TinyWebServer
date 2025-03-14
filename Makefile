PYTHON = python

webserver: config.o fileaccess.o header.o linuxencoding.o linuxmain.o linuxthread.o main.o mime.o response.o task.o url.o
	 gcc $^ -o webserver

webServer1: webServer.c
	$(CC) webServer.c -o webServer

webServer1.exe: webServer.c
	cl webServer.c

webServer.c: main.c
	$(PYTHON) makesf.py

%.o: %.c
	gcc -c $^ -o $@

.PHONY:
clean:
	$(RM) makesf.py
