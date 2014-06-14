header=magic-instruction.h
#max=1000
#width=4096
#sqrtwidth=64

max=10000
width=4096
sqrtwidth=64

#max=100
#width=25
#sqrtwidth=5

#width=9
#qrtwidth=3
#width=64
#sqrtwidth=8
#width=100
#sqrtwidth=10
#width=500
#sqrtwidth=22.3606798
#width=1000
#sqrtwidth=31.6227766
#width=4900
#sqrtwidth=70
#width=10000
#sqrtwidth=100

flag=-Wall -O0 
exe=multiplex transpose matrix_chain_order lu_decomposition optimal_bst \
wavelet_image_compression wavelet_image_decompression \
right-looking_cholesky_factorization left-looking_cholesky_factorization

all:	$(exe)

multiplex:	multiplex.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

transpose:	transpose.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

#matrix_chain_order:	matrix_chain_order.c $(header)
matrix_chain_order:	matrix_chain_order_2.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

lu_decomposition:	lu_decomposition.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

nas_gmtry_kernel:	nas_gmtry_kernel.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

#optimal_bst:	optimal_bst.c $(header)
optimal_bst:	optimal_bst_3.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

right-looking_cholesky_factorization:	right-looking_cholesky_factorization.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

#left-looking_cholesky_factorization:	left-looking_cholesky_factorization_2.c $(header)
left-looking_cholesky_factorization:	left-looking_cholesky_factorization.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) $<

wavelet_image_compression:	wavelet_image_compression.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) -DsqrtWIDTH=$(sqrtwidth) $<

wavelet_image_decompression:	wavelet_image_decompression.c $(header)
	gcc -o $@ $(flag) -DMAX=$(max) -DWIDTH=$(width) -DsqrtWIDTH=$(sqrtwidth) $<

clean:
	rm -f $(exe)