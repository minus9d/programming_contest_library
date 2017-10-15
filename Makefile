vpath %.h include
vpath %.h include/data_structure
vpath %.h include/graph
vpath %.h include/number_theory
vpath %.cpp test
vpath %.cpp test/data_structure
vpath %.cpp test/graph
vpath %.cpp test/number_theory

CXX = g++
CPPFLAGS = -Iinclude -Itest
CXXFLAGS = -std=c++14

SOURCES = \
	bit.cpp \
	bellman-ford.cpp \
	dijkstra.cpp \
	warshall-floyd.cpp \
	n_choose_k.cpp \
	testmain.cpp

# .cppを.oに置換
OBJECTS = $(subst .cpp,.o,$(SOURCES))

# 実行ファイルの生成ルール
testmain: $(OBJECTS)
	$(CXX) $^ -o $@

# testmain.cpp以外のcppファイルのコンパイル用ルール
%.o: %.cpp %.h common.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# testmain.cppのコンパイル用ルール
# このルールを、この一つ上のルールより上に書いてしまうと、
# このルールにたどりつけなくなってしまうので注意
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

