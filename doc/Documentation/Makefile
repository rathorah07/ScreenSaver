all: design.pdf

doc: design.pdf

design.pdf: clean design.tex
	pdflatex design
	makeindex design.idx
	pdflatex design
	latex_count=8 ; \
	while egrep -s 'Rerun (LaTeX|to get cross-references right)' design.log && [ $$latex_count -gt 0 ] ;\
	    do \
	      echo "Rerunning latex...." ;\
	      pdflatex design ;\
	      latex_count=`expr $$latex_count - 1` ;\
	    done
	makeindex design.idx
	pdflatex design


clean:
	rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out *.brf *.blg *.bbl *.pdf
