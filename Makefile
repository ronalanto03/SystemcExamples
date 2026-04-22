# ============================================================================
# Top-level Makefile for SystemcExamples.
#
# Builds (or runs, or cleans) every example under scu/moduleTest/.
# Relies on each sub-directory's Makefile, which in turn includes
# scu/moduleTest/common.mk.
#
# Targets:
#     all (default)  Build every example.
#     run-all        Build and run every example sequentially.
#     clean          Clean every example.
#     list           Print every example directory.
#
# Required environment variable:
#     SYSTEMC_HOME   Path to the SystemC install prefix (see README).
# ============================================================================

# Every directory that actually contains a Makefile under moduleTest/.
EXAMPLE_DIRS := $(sort $(dir $(wildcard scu/moduleTest/*/Makefile \
                                       scu/moduleTest/*/*/Makefile)))

.PHONY: all run-all clean list help $(EXAMPLE_DIRS)

all:
	@set -e; for dir in $(EXAMPLE_DIRS); do \
	    echo "==> building $$dir"; \
	    $(MAKE) -C $$dir all; \
	done

run-all:
	@set -e; for dir in $(EXAMPLE_DIRS); do \
	    echo "==> running $$dir"; \
	    $(MAKE) -C $$dir run; \
	done

clean:
	@for dir in $(EXAMPLE_DIRS); do \
	    $(MAKE) -C $$dir clean; \
	done

list:
	@for dir in $(EXAMPLE_DIRS); do echo $$dir; done

help:
	@echo 'SystemcExamples - top-level Makefile'
	@echo
	@echo 'Targets:'
	@echo '  all      Build every example (default).'
	@echo '  run-all  Build and execute every example.'
	@echo '  clean    Remove build artifacts from every example.'
	@echo '  list     Print every example directory.'
	@echo
	@echo 'Required variables:'
	@echo '  SYSTEMC_HOME   Path to the SystemC install prefix.'
