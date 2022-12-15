all: template max-template tab-template

%: %.cpp
	g++ -g $< -o $@ -Wall -Wextra

clean:
	rm -f template max-template tab-template
