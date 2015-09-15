#!/bin/bash


while read line
do
    name=$line

hadd $name.root   $name/*.root
done < $1
