vpath %.h include
vpath %.h include/data_structure
vpath %.h include/graph
vpath %.h include/number_theory
vpath %.cpp test
vpath %.cpp test/data_structure
vpath %.cpp test/graph
vpath %.cpp test/number_theory

CXX := g++
CPPFLAGS := -Iinclude -Itest
CXXFLAGS := -std=c++14

sources := \
	bit.cpp \
	bellman-ford.cpp \
	dijkstra.cpp \
	warshall-floyd.cpp \
	n_choose_k.cpp \
	testmain.cpp

# .cppを.oに置換
objects := $(subst .cpp,.o,$(sources))

# 実行ファイルの生成ルール
# ここで、$(LINK.cc)の定義は、
#   $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
# に等しい。これはmake --print-data-baseで調べることができる
# $^は、重複を除いたすべてのprerequisiteを指す
testmain: $(objects)
	$(LINK.cc) $^ -o $@

# testmain.cpp以外のcppファイルのコンパイル用ルール
# ここで、$(COMPILE.cc)の定義は、
#   $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
# に等しい。
# $< は、一番目に書かれたprerequisiteを指す
%.o: %.cpp %.h common.h
	$(COMPILE.cc) $< -o $@

# testmain.cppのコンパイル用ルール
# このルールを、この一つ上のルールより上に書いてしまうと、
# このルールにたどりつけなくなってしまうので注意
%.o: %.cpp
	$(COMPILE.cc) $< -o $@
