# Lab 4 -exercise 3
# This script displays a cat meme and a Chuck Norris joke

#!/bin/sh

cat_data=$(curl -s https://api.thecatapi.com/v1/images/search)
cat_url=$(echo $cat_data | jq '.[] | .url' | tr -d '"')
curl -s -o cat_img.png $cat_url

joke_data=$(curl -s https://api.chucknorris.io/jokes/random)

printf "Cat image:\n"
# The value '200' of width is determined by the restrictions of the VM
# The value '1' of loop is set to 1 so thah gifs are played only once
catimg cat_img.png -w 200 -l 1
printf "\nChuck Norris joke:\n"
echo $joke_data | jq '.value'

if [ -f cat_img.png ]; then
    rm cat_img.png
fi