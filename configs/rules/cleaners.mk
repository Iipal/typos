.PHONY: clean_asms clean_deps clean fclean
clean_asms:
	@$(DEL) $(OBJS:%.o=%.S)
clean_deps:
	@$(DEL) $(OBJS:%.o=%.d)
clean: $(LIBS_DIRS) clean_deps clean_asms
	@$(DEL) $(OBJS)
fclean: clean
 ifneq (,$(wildcard $(NAME)))
	@$(DEL) $(NAME)
	@$(ECHO) " | $(CLR_INVERT)deleted$(CLR_WHITE): $(NPWD)"
 endif

.PHONY: del del_libs
del:
	@$(DEL) $(OBJS)
	@$(DEL) $(NAME)

.PHONY: re pre
pre: del multi
re: fclean multi
