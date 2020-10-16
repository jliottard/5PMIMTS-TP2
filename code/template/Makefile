all: template max-template tab-template

%: %.cpp
	g++ --std=c++17 -g $< -o $@ -Wall -Wextra

clean:
	rm -f template max-template tab-template
