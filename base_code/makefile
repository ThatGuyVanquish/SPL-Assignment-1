SRCS = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp,./bin/%.o, $(SRCS))
DEPS := $(patsubst %.o,%.d, $(OBJS))

# all targets
all: ./bin/studio

# build studio
./bin/studio: $(OBJS)
	@echo "Building ..."
	g++ $(OBJS) -o $@
	@echo "Finished building"

# build cpp files
./bin/%.o: ./src/%.cpp
	g++ -g -Wall -std=c++11 -I ./include -MMD -MP -c $< -o $@

# clean build files
clean:
	@rm -f ./bin/*

-include $(DEPS)
