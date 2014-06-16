for file in $(ls *.cpp)
do
	sed "s/Arrranger_concatenating/Arranger_hyperpadding/g" $file > $file
done
