# GNUmakefile

-include GNUmakefile.config

CXX          ?= clang++
CXX_STD      ?= -std=c++14
ifdef DEBUG
CXX_OPTIMIZE ?= -O0 -g3
else
CXX_DEFINE   += -DNDEBUG
CXX_OPTIMIZE ?= -O3 -g0
endif
CXX_WARNING  ?= -W -Wall -Wextra
CXXFLAGS      = $(CXX_STD) $(CXX_MARCH) $(CXX_MTUNE) \
		$(CXX_OPTIMIZE) $(CXX_WARNING) \
		$(CXX_DEFINE)

HEADERS       = include/*.hpp \
		include/rngmte/*.hpp \
		include/rngmte/cpu/*.hpp \
		include/rngmte/simd/*.hpp

TEST_SRC      = test/rngmte-test.cpp

.PHONY:		all build clean

all:		build

clean:
		rm -rf build

build:		build/rngmte-test build/rngsfmte-test

build/rngmte-test: $(TEST_SRC) $(HEADERS)
		@[ -d build ] || mkdir build
		$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $@
		build/rngmte-test -vtp
		build/rngmte-test -jp

build/rngsfmte-test: $(TEST_SRC) $(HEADERS)
		@[ -d build ] || mkdir build
		$(CXX) $(CXXFLAGS) $(TEST_SRC) -DTEST_SFMTE -o $@
		build/rngsfmte-test -vtp
		build/rngsfmte-test -jp

-include GNUmakefile.local
