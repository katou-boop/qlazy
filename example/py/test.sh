#!/bin/bash

py_list=`ls *.py`
for py in ${py_list[@]}; do
    echo "***** ${py} *****"
    python ${py}
    read -p "Hit enter: "
    echo ""
done
