#this makefile is used to build project in order to solve the problem of Ax = b!
#authoe: LY
#date: 2021/7/14
#version: 1.0
all_src=Gauss_Column.o Mymain.o 
Gauss: $(all_src) eigenvalue
	g++ -o Gauss -std=c++11 $(all_src)
$(all_src): %.o: %.cpp
	g++ -o $@ -c $< -std=c++11 -g
eigenvalue: eigenvalue.o
	gcc -o eigenvalue eigenvalue.o
eigenvalue.o: eigenvalue.c
	gcc -c -o eigenvalue.o eigenvalue.c
.PHONY: clean
clean:
	rm *.o Gauss