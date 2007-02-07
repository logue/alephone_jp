
EXPORTS = smpeg.exp
HEADERS = \
	../../smpeg.h

all: $(EXPORTS)

$(EXPORTS): $(HEADERS)
	perl gendef.pl $(HEADERS) >$@ || rm $@

clean:
	rm -f $(EXPORTS)
