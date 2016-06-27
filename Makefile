CXXFLAGS   = -Wall -Wextra -g -fstack-protector-all -std=c++11 -O3
LDFLAGS    =
EXECUTABLE = Args.exe #the .exe is to avoid conflicts with directory names.
EXTENSION  = cpp
SOURCES    = $(basename $(shell find . -name '*.$(EXTENSION)'))

.PHONY: all
all:
	make $(EXECUTABLE)

$(EXECUTABLE): $(addsuffix .o,$(SOURCES))
	$(CXX) $(LDFLAGS) $^ -o $@

%.d: %.$(EXTENSION)
	$(CXX) $(CXXFLAGS) -MM $< -o $@
	echo sed -i 's/:/ $@:/' $@
	printf '\t$$(CC) $$(CXXFLAGS) -c $$< -o $$@\n' >>$@

-include $(addsuffix .d,$(SOURCES))

.PHONY: build
build:
	make $(EXECUTABLE) -s
	make clean -s

.PHONY: push
push:
	rm $(EXECUTABLE)
	make clean -s
	git add ../.

.PHONY: clean
clean:
	find . -name '*.o' -delete
	find . -name '*.d' -delete
	find . -name '*~'  -delete
