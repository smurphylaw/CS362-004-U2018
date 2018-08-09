CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: assignment5results.out

assignment5results.out: cardtest1.c cardtest2.c cardtest3.c cardtest4.c unittest1.c unittest2.c unittest3.c unittest4.c

	echo "unittest1.c" >> assignment5results.out
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> assignment5results.out
	gcov unittest1.c -b >> assignment5results.out
  
	echo "unittest2.c" >> assignment5results.out
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> assignment5results.out
	gcov unittest2.c -b >> assignment5results.out
  
	echo "unittest3.c" >> assignment5results.out
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> assignment5results.out
	gcov unittest3.c -b >> assignment5results.out
  
	echo "unittest4.c" >> assignment5results.out
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> assignment5results.out
	gcov unittest4.c -b >> assignment5results.out
  
	echo "cardtest1.c" >> assignment5results.out	
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> assignment5results.out
	gcov cardtest1.c -b >> assignment5results.out
  
	echo "cardtest2.c" >> assignment5results.out	
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> assignment5results.out
	gcov cardtest2.c -b >> assignment5results.out
  
	echo "cardtest3.c" >> assignment5results.out	
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> assignment5results.out
	gcov cardtest3.c -b >> assignment5results.out
  
	echo "cardtest4.c" >> assignment5results.out	
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> assignment5results.out
	gcov cardtest4.c -b >> assignment5results.out
  
	echo "randomtestadventurer.c" >> assignment5results.out
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> assignment5results.out
	gcov randomtestadventurer.c -b >> assignment5results.out

	echo "randomtestcard1.c" >> assignment5results.out
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> assignment5results.out
	gcov randomtestcard1.c -b >> assignment5results.out

	echo "randomtestcard2.c" >> assignment5results.out
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> assignment5results.out
	gcov randomtestcard2.c -b >> assignment5results.out

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
