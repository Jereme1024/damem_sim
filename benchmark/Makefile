CC=g++ -std=c++11
header=magic-instruction.h
#max=1000
#width=4096
#sqrtwidth=64

max=10
width=200
sqrtwidth=10

#max=100
#width=1000
#sqrtwidth=33

#max=100
#width=256
#sqrtwidth=16

#max=100
#width=2048
#sqrtwidth=16

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

flag=-Wall -O2
exe=multiplex transpose matrix_chain_order lu_decomposition optimal_bst \
wavelet_image_compression wavelet_image_decompression \
right-looking_cholesky_factorization left-looking_cholesky_factorization

all:	$(exe)

multiplex:	multiplex.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

transpose:	transpose.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

#matrix_chain_order:	matrix_chain_order.c $(header)
matrix_chain_order:	matrix_chain_order_2.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

lu_decomposition:	lu_decomposition.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

nas_gmtry_kernel:	nas_gmtry_kernel.c $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

#optimal_bst:	optimal_bst.c $(header)
optimal_bst:	optimal_bst_3.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

right-looking_cholesky_factorization:	right-looking_cholesky_factorization.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

#left-looking_cholesky_factorization:	left-looking_cholesky_factorization_2.c $(header)
left-looking_cholesky_factorization:	left-looking_cholesky_factorization.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DPOLICY=Arranger_one_dim $<

wavelet_image_compression:	wavelet_image_compression.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_one_dim $<

wavelet_image_decompression:	wavelet_image_decompression.cpp $(header)
	$(CC) -o padding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_padding $<
	$(CC) -o concatenating/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_concatenating $<
	$(CC) -o hyperpadding/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_hyperpadding $<
	$(CC) -o one_dim/$@ $(flag) -DMAX=$(max) -DWIDTH_DE=$(width) -DsqrtWIDTH_DE=$(sqrtwidth) -DPOLICY=Arranger_one_dim $<

clean:
	rm -f $(exe)
