
if (($# == 2)); then
    ip=$1;
    file=$2;
    tar cf - "$file" | nc "$ip" 2020;
fi
