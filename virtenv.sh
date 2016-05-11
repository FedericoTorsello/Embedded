#!/bin/zsh

DIRECTORY=env
ACTIVATION=.$DIRECTORY/bin/activate

if [ ! -d ".$DIRECTORY" ]; then
	virtualenv --no-site-packages --distribute .$DIRECTORY && source $ACTIVATION
else
	if [ -e "$ACTIVATION" ]; then
		source $ACTIVATION
	fi
fi
