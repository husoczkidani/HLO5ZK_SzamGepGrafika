#include "matrix.h"

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
	printf("\n");
    print_matrix(b);
    printf("\n");
	
    add_matrices(a, b, c);

    print_matrix(c);
	printf("\n");
	
	init_identity_matrix(c);
	printf("Identity Matrix\n");
	print_matrix(a);

	mult_scalar_matrix(c ,1000, a);
	printf("\n");
	printf("Multiply by scalar\n");
	print_matrix(b);

    multiply_matrices(a,b,c);
    printf("\n");
    printf("Matrix multiplied by matrix\n");
    print_matrix(c);

	return 0;
}

