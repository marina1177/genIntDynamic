
#!/bin/sh

PREFIX="test_"
SUFFIX=".bin"

file="${PREFIX}$(date +%Y-%m-%d:%k:%M:%S)${SUFFIX}"

if [ ! -e $file ] ; then
    break;
fi

# this is the next available file name
echo $file

make
./verle -g $file
