
build:
	clang -Wall -O3 -I/usr/local/sgb/include -fPIC -o zddread-count zddread-count.c -lgb
	clang -Wall -O3 -I/usr/local/sgb/include -fPIC -o zddread-gf zddread-gf.c -lgb
	clang -Wall -O3 -I/usr/local/sgb/include -fPIC -o zddread-minsols-short zddread-minsols-short.c -lgb
	clang -Wall -O3 -I/usr/local/sgb/include -fPIC -o zddread-random zddread-random.c -lgb
	clang -Wall -O3 -I/usr/local/sgb/include -fPIC -o zddread-sols-all zddread-sols-all.c -lgb

install:
	install -Dm755 zddread-sols-all /usr/local/bin/zddread-sols-all
	install -Dm755 zddread-random /usr/local/bin/zddread-random
	install -Dm755 zddread-minsols-short /usr/local/bin/zddread-minsols-short
	install -Dm755 zddread-gf /usr/local/bin/zddread-gf
	install -Dm755 zddread-count /usr/local/bin/zddread-count