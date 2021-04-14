include configs/base.mk
include configs/os.mk
include configs/colors.mk

.PHONY: $(LIBS_DIRS) make_optional all multi STATUS_START
multi: make_optional $(LIBS_DIRS) STATUS_START
	@$(MAKE) -e $(MAKE_PARALLEL_FLAGS) all

all: $(NAME)

$(NAME): $(OBJS) $(ASMS)
 ifneq (,$(OBJS))
	@$(CC) $(addprefix -D,$(DEFINES)) \
		$(IFLAGS) \
		$(OBJS) \
		$(CFLAGS) \
		$(CFLAGS_OPTIONAL) \
		$(CFLAGS_LIBS) \
		$(LIBS_NAMES) \
		-o $(NAME)
 endif
	@$(MAKE) STATUS_END

define compilation
$(CC) $(addprefix -D,$(DEFINES)) \
	$(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) \
	-c $$1 -o $$2
$(ECHO) " | $$2: $(MSG_SUCCESS)"
endef

-include $(OBJS:.o=.d)
$(OBJS): %.o: %.c
	@$(call compilation,$<,$@)

$(ASMS): %.S: %.c
	@$(call compilation,$<,$@)

$(LIBS_DIRS):
 ifeq (,$(filter $(MAKECMDGOALS), pre debug))
	@$(MAKE) -C $@ $(MAKECMDGOALS)
 endif

-include configs/rules/STATUS.mk
-include configs/rules/cleaners.mk

-include configs/rules/optional.mk
.PHONY: debug debug_all sanitize sanitize_all assembly assembly_all debug_assembly debug_assembly_all
.PHONY: debug debug_all sanitize sanitize_all assembly assembly_all debug_assembly debug_assembly_all pedantic pedantic_all
