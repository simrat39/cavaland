release:
	cmake -S . -B ./build/
	cmake --build ./build/ -j8

clear:
	rm -rf ./build/	

all:
	make clear
	make release

install:
	## Binary
	cp ./build/cavaland /usr/bin/
	## Shaders
	mkdir -p /usr/share/cavaland/
	cp -r ./shaders/ /usr/share/cavaland/

uninstall:
	## Binary
	rm -rf /usr/bin/cavaland
	## Shaders
	rm -rf /usr/share/cavaland/

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
