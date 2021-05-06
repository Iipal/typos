.PHONY: STATUS_START
DELIMITER_LINE:="--------------------------------------------------------------------------------"
__DELIM_LEN:=$(shell eval expr "$(SRC_MAX_LENGTH) - 1")
__DELIM_START_MAKE:=" | $(shell echo $(DELIMITER_LINE) | cut -c1-$(__DELIM_LEN)) |"
__DELIM_INFO:=" $(shell echo $(DELIMITER_LINE) | cut -c1-$(SRC_MAX_LENGTH))"
__DELIM_INFO_START:="/"$(__DELIM_INFO)
ifeq ($(shell test 23 -eq $(SRC_MAX_LENGTH); echo $$?),0)
  __DELIM_INFO_START+="|"
else
  __DELIM_INFO_START+="/"
endif

STATUS_START:
 ifneq (,$(OBJS))
	@$(ECHO) $(__DELIM_START_MAKE)
	@$(ECHO) " | making: $(CLR_UNDERLINE)$(NAME)$(CLR_WHITE) ..."
	@$(ECHO) $(__DELIM_START_MAKE)
 endif

.PHONY: STATUS_END
STATUS_END:
	@$(ECHO) $(__DELIM_INFO_START)
 ifneq (,$(NAME))
  ifneq (,$(OBJS))
	@$(ECHO) "| COMPILED SUCCESSFULY    : $(MSG_SUCCESS) $(NAME) "
  endif
 endif
 ifneq (,$(CC))
	@$(ECHO) "| compiler                : $(CC)"
 endif
 ifneq (,$(DEFINES))
	@$(ECHO) "| defines                 : $(foreach dfns,$(DEFINES),$(CLR_INVERT)$(dfns)$(CLR_WHITE) )"
 endif
 ifneq (,$(LFLAGS))
	@$(ECHO) "| linked                  : $(LFLAGS)"
 endif
 ifneq (,$(CFLAGS))
	@$(ECHO) "| compiler          flags : $(CFLAGS)"
 endif
 ifneq (,$(CFLAGS_OPTIONAL))
	@$(ECHO) "| compiler optional flags : $(CLR_UNDERLINE)$(CFLAGS_OPTIONAL)$(CLR_WHITE)"
 endif
	@$(ECHO) "\\ ----------------------- /"
