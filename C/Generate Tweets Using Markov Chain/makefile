.PHONY: tweets, snakes

OBJECT = markov_chain.o linked_list.o
TWEETS = tweets_generator.c $(OBJECT)
SNAKE = snakes_and_ladders.c $(OBJECT)
CCFLAGS = -Wall -Wextra -Wvla

MARKOV_FILES = markov_chain.h markov_chain.c
LINKED_LIST_FILES = linked_list.h linked_list.c

tweets: $(TWEETS)
	gcc $(CCFLAGS) $^ -std=c99 -o tweets_generator

snake: $(SNAKE)
	gcc $(CCFLAGS) $^ -std=c99 -o snakes_and_ladders

markov_chain.o: $(MARKOV_FILES)
	gcc $^ -c

linked_list.o: $(LINKED_LIST_FILES)
	gcc $^ -c