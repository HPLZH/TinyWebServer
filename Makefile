PYTHON = python

webServer: webServer.c
	$(CC) webServer.c -o webServer

webServer.exe: webServer.c
	cl webServer.c

webServer.c: main.c
	$(PYTHON) makesf.py

.PHONY:
clean:
	$(RM) makesf.py
