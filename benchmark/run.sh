EXEC="transpose multiplex lu_decomposition matrix_chain_order optimal_bst right-looking_cholesky_factorization left-looking_cholesky_factorization wavelet_image_compression wavelet_image_decompression"
#EXEC="right-looking_cholesky_factorization left-looking_cholesky_factorization"

DIRS="padding concatenating hyperpadding"

for DIR in $DIRS
do
	cd $DIR
	pwd
	echo "== [[ Case $DIR ]] =="
	for EX in $EXEC
	do
		echo ""
		echo "-- Run $EX --"
		time $(pwd)/$EX
	done
	cd ..
done
