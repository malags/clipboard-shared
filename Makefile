#!make

include .env
export $(shell sed 's/=.*//' .env)

clipboard:
	@echo "host: ${HOST_URL}"
	@echo "compiling clipboard.c"
	@gcc  -Wall -D __HOST_URL__='$(subst /,\/, ${HOST_URL} )' -o clipboard clipboard.c -l curl