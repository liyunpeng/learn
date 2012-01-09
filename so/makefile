/tmp/test : test.c /tmp/libsay.so
	gcc test.c -lsay -L/tmp/ -o /tmp/test 
/tmp/libsay.so : say.c so_sub_2.c
	gcc -shared -fPIC say.c so_sub_2.c -o /tmp/libsay.so
