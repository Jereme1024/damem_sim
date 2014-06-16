EXEC="left-looking_cholesky_factorization lu_decomposition matrix_chain_order multiplex optimal_bst right-looking_cholesky_factorization transpose wavelet_image_compression wavelet_image_decompression"

echo "== [[ Padding ]] =="
for EX in $EXEC
do
	echo "Run $EX"
	time padding/$EX
done

echo "== [[ Concatenating ]] =="
for EX in $EXEC
do
	echo "Run $EX"
	time concatenating/$EX
done

echo "== [[ Hyperpadding ]] =="
for EX in $EXEC
do
	echo "Run $EX"
	time hyperpadding/$EX
done
