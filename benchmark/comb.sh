dirs="padding concatenating one_dim"
files="mul.csv lu.csv chain.csv optimal.csv right.csv left.csv wco.csv wde.csv"

for dir in $dirs
do
	echo "" > ${dir}_comb.csv

	cat "$dir/tp.csv" >> ${dir}_comb.csv

	for csv in $files
	do
		tail -n 1 $dir/$csv >> ${dir}_comb.csv
	done
done
