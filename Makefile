
# Util function that removes duplicates
uniq = $(if $1,$(firstword $1) $(call uniq,$(filter-out $(firstword $1),$1)))

TARGET = ezpcc
SRC_PATH = src
OUT_PATH = out

YY_SRCS = $(shell find $(SRC_PATH) -name '*.yy')
YY_GEN_SRCS = $(patsubst %.yy,$(OUT_PATH)/%.tab.cpp,$(YY_SRCS))
YY_GEN_HEADERS = $(patsubst %.yy,$(OUT_PATH)/%.tab.hpp,$(YY_SRCS))

LL_SRCS = $(shell find $(SRC_PATH) -name '*.ll')
LL_GEN_SRCS = $(patsubst %.ll,$(OUT_PATH)/%.lex.cpp,$(LL_SRCS))
LL_GEN_HEADERS = $(patsubst %.ll,$(OUT_PATH)/%.lex.hpp,$(LL_SRCS))

GEN_SRCS = $(YY_GEN_SRCS) $(LL_GEN_SRCS)
GEN_HEADERS = $(YY_GEN_HEADERS) $(LL_GEN_HEADERS)
# The include options for generated headers
GEN_HEADER_INCLUDE = $(addprefix -I,$(call uniq,$(dir $(GEN_HEADERS))))

SRCS = $(shell find $(SRC_PATH) -name '*.cpp') $(GEN_SRCS)
OBJS = $(patsubst %.cpp,$(OUT_PATH)/%.o,$(SRCS))

CXX = g++
CXXFLAGS = -Werror -c
DEPFLAGS = -MT $@ -MMD -MP
INCLUDES = -Iinclude/easy_protocol $(GEN_HEADER_INCLUDE)

# Code generation should run first
all :: gen

all :: $(OUT_PATH)/$(TARGET)

$(OUT_PATH)/$(TARGET) : $(OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(OBJS) 

$(OUT_PATH)/%.tab.cpp $(OUT_PATH)/%.tab.hpp : %.yy
	@mkdir -p $(@D)
# The target can be either hpp or cpp. Basename is used so that we won't mix them. 
	bison -d -o$(basename $@).cpp $<

$(OUT_PATH)/%.lex.cpp $(OUT_PATH)/%.lex.hpp : %.ll
	@mkdir -p $(@D)
# The target can be either hpp or cpp. Basename is used so that we won't mix them. 
	flex --header-file=$(basename $@).hpp -o$(basename $@).cpp $<

$(OUT_PATH)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $@ $<

# Code generation
.PHONY: gen
gen: $(GEN_SRCS) $(GEN_HEADERS)

include $(wildcard $(OBJS:.o=.d))

.PHONY: clean
clean:
	rm -rf $(OUT_PATH)
