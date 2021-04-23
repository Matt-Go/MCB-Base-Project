pdf-engine = --pdf-engine=xelatex
variables = --variable geometry="margin=1in"

default :

clean :
	rm -rf *.pdf

%.pdf : %.md
	pandoc $< $(pdf-engine) -o $@ $(variables)
