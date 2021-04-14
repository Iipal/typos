.EXPORT_ALL_VARIABLES:

NAME := $(notdir $(CURDIR))
NPWD := $(CURDIR)/$(NAME)

# all source code .c files must to places in to "srcs" folder(or sub-dirs) only.
ifneq (,$(wildcard ./srcs))
SRCS := $(shell find srcs -name "*.c")
OBJS := $(SRCS:.c=.o)
ASMS := # reversed for 'assembly' and 'assembly_all' rules where ASMS:=$(OBJS:%.o=%.S) and OBJS:= sets to nothing
else
$(error "all source code .c files must to places in to "srcs" folder(or sub-dirs) only.")
endif

# all header .h files must be placed in to "includes" folder(or sub-dirs) only.
I_PATHS := $(shell find . -name "includes" 2> /dev/null)
ifneq (,$(I_PATHS))
IFLAGS := $(addprefix -I,$(foreach ip,$(I_PATHS),$(abspath $(shell find $(ip) -type d))))
else
$(error "all header .h files must be placed in to "includes" folder(or sub-dirs) only.")
endif

# Set and to parse additional library headers dependencies.
# Set only parent-folder for all headers, all sub-dirs will be added automatically.
HEADER_DEPS :=
ifneq (,$(HEADER_DEPS))
# Checks if each path in HEADER_DEPS is valid.
 ifneq (,$(filter-out $(foreach dep,$(HEADER_DEPS),$(wildcard $(dep))),$(HEADER_DEPS)))
$(error "Some of the configs/base.mk:$$HEADER_DEPS additional library headers dependencies have are an invalid path.")
 endif
IFLAGS += $(addprefix -I,$(shell find $(foreach d,$(HEADER_DEPS),$(abspath $d)) -type d))
endif

# All submodules or additional libs must to be placed in to 'libs' folder
#  and has it's own folder and Makefile with the same rules as this.
ifneq (,$(wildcard ./libs))
LIBS_DIRS  := $(abspath $(filter-out ./libs,$(shell find ./libs -maxdepth 1 -type d)))
LIBS_NAMES := $(join $(LIBS_DIRS),$(addsuffix .a,$(addprefix /,$(notdir $(LIBS_DIRS)))))
endif

# Compiler settings.
CC                    := clang
CFLAGS                := -Wall -Wextra -Werror -Wunused -MMD -std=c11
CFLAGS_PEDANTIC       := -Wpedantic
CFLAGS_DEBUG          := -g3
CFLAGS_SANITIZE       := $(CFLAGS_DEBUG) -fsanitize=address
CFLAGS_OPTIMIZE       := -march=native -mtune=native -Ofast -pipe -flto -fpic
CFLAGS_ASSEMBLY       := $(filter-out -flto -fpic,$(CFLAGS_OPTIMIZE)) -S -masm=intel
CFLAGS_DEBUG_ASSEMBLY := $(CFLAGS_DEBUG) -S -masm=intel

CFLAGS_OPTIONAL := $(CFLAGS_OPTIMIZE)
