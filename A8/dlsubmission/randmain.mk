randlibhw.so:
	$(CC) $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o
	$(CC) $(CFLAGS) -shared -o randlibhw.so randlibhw.o
randlibsw.so:
	$(CC) $(CFLAGS) -fPIC -c randlibsw.c -o	randlibsw.o
	$(CC) $(CFLAGS) -shared -o randlibsw.so randlibsw.o
randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain
