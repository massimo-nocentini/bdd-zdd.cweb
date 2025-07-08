
fetch:
	mkdir utils && \
		cd utils && \
		wget https://www-cs-faculty.stanford.edu/~knuth/programs/bdd-zdd-utils.tgz && \
		tar -xf bdd-zdd-utils.tgz && \
		rm bdd-zdd-utils.tgz

cweave:
	cd utils && \
		cweave zddread.w zddread-count.ch zddread-count.tex && tex zddread-count.tex && dvipdf zddread-count.dvi && \
		cweave zddread.w zddread-gf.ch zddread-gf.tex && tex zddread-gf.tex && dvipdf zddread-gf.dvi && \
		cweave zddread.w zddread-minsols-short.ch zddread-minsols-short.tex && tex zddread-minsols-short.tex && dvipdf zddread-minsols-short.dvi && \
		cweave zddread.w zddread-random.ch zddread-random.tex && tex zddread-random.tex && dvipdf zddread-random.dvi && \
		cweave zddread.w zddread-sols-all.ch zddread-sols-all.tex && tex zddread-sols-all.tex && dvipdf zddread-sols-all.dvi


