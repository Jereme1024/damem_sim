EXEC="left-looking_cholesky_factorization lu_decomposition matrix_chain_order multiplex optimal_bst right-looking_cholesky_factorization transpose wavelet_image_compression wavelet_image_decompression"

for EX in $EXEC
do
	echo "Run $EX"
	time ./$EX
done
