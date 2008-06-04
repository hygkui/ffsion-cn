#!/bin/bash


usage="Usage: ./run.sh [-s start] [-c clear] "
pre_set="please set the LD_LIBRARY_PATH"
clear_p="`echo $HOME`/.guohuan/myapp"
xulrunner="`echo $HOME`/tmp/xulrunner/1.9b3/xulrunner-sdk/bin/xulrunner"

flag_c=
flag_s= 


if [ -z $1 ];then
    echo $usage
else
    echo '-->'
fi

if [ -z $LD_LIBRARY_PATH ] ; then
    echo $pre_set
else
    echo 'your LD_LIBRARY_PATH='$LD_LIBRARY_PATH
fi



while getopts "sc" flag ; do
    case $flag in
        c ) flag_c=1;;
        s ) flag_s=1;;
        \? )
            echo $usage
            exit 1;;
        * ) 
            echo $usage
            exit 1 ;;
    esac
done

shift $(($OPTIND - 1))



if [ "$flag_c" ] ; then
    rm -rf $clear_p
fi

if [ "$flag_s" ] ; then
    $xulrunner 'application.ini'
fi
