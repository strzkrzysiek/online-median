SRC=src
INCLUDE=include
BIN=bin
GTEST_DIR=googletest/googletest
GTEST_BIN=gtest_bin

MAX_SPEED_FLAGS=-I$(SRC)/$(INCLUDE) -I$(GTEST_DIR)/include -Wall -Werror -O3 -DNDEBUG
DEBUG_FLAGS=-I$(SRC)/$(INCLUDE) -I$(GTEST_DIR)/include -Wall -Werror -g
LDFLAGS=-L./$(GTEST_BIN) -lgtest -lpthread

all: gtest onlinemedian

debug: gtest onlinemedian_debug

onlinemedian:
	mkdir -p $(BIN)
	g++ -c $(SRC)/Heap.cpp -o $(BIN)/Heap.o $(MAX_SPEED_FLAGS)
	g++ -c $(SRC)/Online_median_calculator.cpp -o $(BIN)/Online_median_calculator.o $(MAX_SPEED_FLAGS)
	g++ -c $(SRC)/Multiset_median_calculator.cpp -o $(BIN)/Multiset_median_calculator.o $(MAX_SPEED_FLAGS)
	g++ -c $(SRC)/main.cpp -o $(BIN)/main.o $(MAX_SPEED_FLAGS)
	g++ -o onlinemedian $(BIN)/Heap.o $(BIN)/Online_median_calculator.o \
	$(BIN)/Multiset_median_calculator.o $(BIN)/main.o  $(LDFLAGS)

onlinemedian_debug:
	mkdir -p $(BIN)
	g++ -c $(SRC)/Heap.cpp -o $(BIN)/Heap.o $(DEBUG_FLAGS)
	g++ -c $(SRC)/Online_median_calculator.cpp -o $(BIN)/Online_median_calculator.o $(DEBUG_FLAGS)
	g++ -c $(SRC)/Multiset_median_calculator.cpp -o $(BIN)/Multiset_median_calculator.o $(DEBUG_FLAGS)
	g++ -c $(SRC)/main.cpp -o $(BIN)/main.o $(DEBUG_FLAGS)
	g++ -o onlinemedian $(BIN)/Heap.o $(BIN)/Online_median_calculator.o \
	$(BIN)/Multiset_median_calculator.o $(BIN)/main.o  $(LDFLAGS)

gtest:
	mkdir -p $(GTEST_BIN)
	g++ -o $(GTEST_BIN)/gtest-all.o -isystem ${GTEST_DIR}/include \
	-I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv $(GTEST_BIN)/libgtest.a gtest_bin/gtest-all.o

clean:
	-rm -f onlinemedian
	-rm -rf $(GTEST_BIN)