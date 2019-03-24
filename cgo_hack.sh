#/bin/bash

# Usage: $1 package function1 function2

# TODO: preserve git state of the other repo

PACKAGE=$1

pushd $GOPATH/src/$PACKAGE

git stash
git reset --hard HEAD

# replaced 'package export' with 'package main'
sed -i 's/^package [[:alpha:]]*/package main/g' *.go

# add 'import "C"'
sed -i '/^package main/a import "C"' *.go

# delete *_test.go
rm *_test.go

# add '//export <function>'
# TODO: loop over functions
for FUNCTION in ${@:2}
do
    CFUNC=$FUNCTION
    sed -i "/^func $FUNCTION(/i \/\/export $CFUNC" *.go
done

# create template main function
cat >main.go <<EOF
package main
import "C"

func main() {}
EOF

# call go build -o libsiaencoding.so -buildmode=c-shared
CLIBNAME=lib$(basename $PACKAGE).so
go build -o $CLIBNAME -buildmode=c-shared

git reset --hard HEAD
git stash pop

# move the files to the directory
WD=$(pwd)
popd
cp $WD/*.so $WD/*.h .
