SUBDIR = bin

all:	$(SUBDIR)

$(SUBDIR):
	@echo "\033[0;34mBe Aware:\033[0;m There will be a billion warnings from CFDP. To remove these, add \"CONFIG += warn_off\" to BARCoMmS.pro"
	@echo "Beginning make in three seconds...\n"
	@sleep 3
	$(MAKE) -C $@

clean:
	rm -fv bin/*.o
	rm -fv bin/*.cpp
	rm -fv bin/*.h
	@echo "Clean done"

.PHONY: $(SUBDIR)
