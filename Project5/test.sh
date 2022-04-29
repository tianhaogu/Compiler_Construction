# set -x

OUT=$(rm samples/test_*.out)

for file in ./samples/*.decaf
do
    echo $file
    file=$(echo $file | cut -d'/' -f3 | cut -d'.' -f1) 
    if test -f "samples/$file.in"; then
        bash run samples/$file.decaf < samples/$file.in > samples/test_$file.out 2>&1
    else
        bash run samples/$file.decaf > samples/test_$file.out 2>&1
    fi
    DIFF=$(diff -w samples/$file.out samples/test_$file.out)
    if [ "$DIFF" != "" ]
    then
        echo $file
        # break
    fi
    # echo ""
    # break
done