EXEC="transpose multiplex lu_decomposition matrix_chain_order optimal_bst right-looking_cholesky_factorization left-looking_cholesky_factorization wavelet_image_compression wavelet_image_decompression"
#EXEC="transpose lu_decomposition matrix_chain_order optimal_bst right-looking_cholesky_factorization left-looking_cholesky_factorization wavelet_image_compression wavelet_image_decompression"
#EXEC="right-looking_cholesky_factorization left-looking_cholesky_factorization"

#DIRS="padding concatenating hyperpadding"
DIRS="padding concatenating one_dim"

#H_MEM="64"
#W_MEM="256"
#H_PAGE="2"
#W_PAGE="16"
#H_DS="1"
#W_DS="8"
#
#WIDTH="150"

H_MEM="256"
W_MEM="256"
H_PAGE="4"
W_PAGE="32"
H_DS="1"
W_DS="8"

WIDTH="500"

#H_MEM="1"
#W_MEM="65536"
#H_PAGE="1"
#W_PAGE="128"
#H_DS="1"
#W_DS="8"
#
#WIDTH="500"

for DIR in $DIRS
do
	cd $DIR
	pwd
	echo "== [[ Case $DIR ]] =="
	for EX in $EXEC
	do
		echo ""
		echo "-- Run $EX --"
		time $(pwd)/$EX $H_MEM $W_MEM $H_PAGE $W_PAGE $H_DS $W_DS $WIDTH
	done
	cd ..
done

./comb.sh
