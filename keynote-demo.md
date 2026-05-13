# Demo Command

## Setup
```sh
git pull
make re
make plugin
```


## Simple shell
```sh
ls
ls | grep a
true && printenv
echo 'This is a command: $HOME'
echo "This is an another command with home directory: $HOME"


code <- ctrl + z tres reactif
grep a &
jobs
fg <- puis ctrl + c apres 2s
bg

history <- command up & down arrow

alias ll "ls -la"
ls src/*.o
set ignoreof = 3
```

## Bonus
```sh
make install <- suivie de la 42sh
ctrl + d; alias <- show startup alias
vim .czshrc; source <- delete un module ou change color
mv plugins/libmatrix.so . <- montrer avec l\'autocompletion que le plugin a disparu
mv libmatrix.so plugins
./42sh
matrix

```