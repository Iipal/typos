make_optional:
 ifneq (,$(filter $(MAKECMDGOALS),debug debug_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_DEBUG))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_DEBUG)
 endif
 ifneq (,$(filter $(MAKECMDGOALS),sanitize sanitize_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_SANITIZE))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_SANITIZE)
 endif
 ifneq (,$(filter $(MAKECMDGOALS),assembly assembly_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_ASSEMBLY))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_ASSEMBLY)
	@$(eval ASMS:=$(OBJS:.o=.S))
	@$(eval OBJS:=)
 endif
 ifneq (,$(filter $(MAKECMDGOALS),debug_assembly debug_assembly_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_DEBUG_ASSEMBLY))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_DEBUG_ASSEMBLY)
	@$(eval ASMS:=$(OBJS:.o=.S))
	@$(eval OBJS:=)
 endif
 ifneq (,$(filter $(MAKECMDGOALS),pedantic pedantic_all))
	@$(eval DEFINES+=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_PEDANTIC)
	@$(eval CFLAGS+=$(CFLAGS_PEDANTIC))
 endif

debug_all: pre
debug: multi

sanitize_all: pre
sanitize: multi

assembly_all: pre
assembly: multi

debug_assembly_all: pre
debug_assembly: multi

pedantic_all: pre
pedantic: multi
