#this makefile is used to build project!
#authoe: LY
#date: 2021/7/14
#version: 1.0
all_src=Gauss_Column.o Mymain.o 
Gauss: $(all_src)
	g++ -o Gauss -std=c++11 $(all_src)
$(all_src): %.o: %.cpp
	g++ -o $@ -c $< -std=c++11 -g
.PHONY: clean
clean:
	rm *.o Gauss