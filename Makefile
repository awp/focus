TAR = $(filter-out $@,$(MAKECMDGOALS))

.PHONY: $(MAKECMDGOALS)

$(TAR):
	@if [ $@ = "focus" ]; \
	then \
		scripts/build.sh $(TAR); \
	fi
	@if [ $@ = "update" ]; \
	then \
		scripts/update.sh $(TAR); \
	fi
	@if [ $@ = "local" ]; \
	then \
		scripts/local.sh $(TAR); \
	fi
