#!/bin/sh

work(){
    echo $*
    if [ $1 = 0 ]
    then 
        echo "$2 -> $4"
    else
        x=$(expr $1 - 1)
        work $x $2 $4 $3
        echo "$2 -> $4"
        work $x $3 $2 $4

    fi
}

while true
do
    echo "Please input the number of disks:"
    read x
    expr $x + 0 &>/dev/null
    if [ $? = 0 ] 
    then
        if [ $x -le 0 ] 
        then echo "Please input a correct number!"
        else
            work $x 1 2 3
            exit 0
        fi
    else
        echo "Please input a correct number!"
    fi
done

exit 0