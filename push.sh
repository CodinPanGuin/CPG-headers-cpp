#!/bin/bash
Branch=$(git branch --show-current) 
git pull 
git add --all .

if [ "$1" == "-m" ];
then
	echo ""
	git commit -m "$2"
else
	read commit
		echo ""
		git commit -m "$commit"
fi
echo ""
git push -u origin $Branch
echo ""
echo "you can run script with 2 arguments (your commit comment)"
echo "like so \"./push.sh -m \"commit\""
