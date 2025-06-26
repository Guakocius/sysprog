#!/bin/zsh
declare -a FILES=("benotung" "fachnote" "fachnoten_liste")
SRC="../../aufgabe5"
declare -a OBJ_FILES=()
for f in "${FILES[@]}"; do
  if [ -e "$f.o" ]; then
    read -n 1 -p "Do you want to overwrite $f.o?" yn
    case $yn in
      [Yy]* ) rm "$f.o"; break;;
      [Nn]* ) exit;;
      * ) echo "[Y/N]";;
    esac
  fi
  g++ -c -o "$f.o" "$SRC/$f.cpp"
  ar rcs libaufgabe6.a "$f.o"
done

