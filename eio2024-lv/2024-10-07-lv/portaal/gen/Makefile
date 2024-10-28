CXXFLAGS+=-std=c++17 -O2

all: ../bin/validator ../bin/gen_simple ../bin/gen_groups ../bin/gen_groups_from_file ../bin/add_coins

../bin:
	@mkdir -p $@

../bin/validator: validator.cpp testlib.h | ../bin
	$(CXX) $(CXXFLAGS) -o $@ $<

../bin/gen_simple: gen_simple.cpp testlib.h gen_util.h | ../bin
	$(CXX) $(CXXFLAGS) -o $@ $<

../bin/gen_groups: gen_groups.cpp testlib.h gen_util.h gen_grid.h | ../bin
	$(CXX) $(CXXFLAGS) -o $@ $<

../bin/gen_groups_from_file: gen_groups_from_file.cpp testlib.h gen_util.h gen_grid.h | ../bin
	$(CXX) $(CXXFLAGS) -o $@ $<

../bin/add_coins: add_coins.cpp testlib.h gen_util.h | ../bin
	$(CXX) $(CXXFLAGS) -o $@ $<
