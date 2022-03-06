# set -x

OUT=$(rm samples/test_*.out)

for file in ./samples/*.decaf
do
    echo $file
    file=$(echo $file | cut -d'/' -f3 | cut -d'.' -f1) 
    ./dcc < samples/$file.decaf > samples/test_$file.out 2>&1
    DIFF=$(diff -w samples/$file.out samples/test_$file.out)
    if [ "$DIFF" != "" ]
    then
        echo $DIFF
        echo $file
        break
    fi
    break
done