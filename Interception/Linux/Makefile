compileLib: mem.c
	gcc -shared -fPIC mem.c -o mem.so -lcrypto -ldl

runpreload: mem.so
	LD_PRELOAD=./mem.so /bin/ls
