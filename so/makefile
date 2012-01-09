test : test.c libsay.so
	gcc test.c -lsay -L. -o test 
libsay.so : say.c so_sub_2.c
	gcc -shared -fPIC say.c so_sub_2.c -o libsay.so
