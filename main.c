#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

int n, m; // n -строки, m - столбцы
double x, h;
double** table;

unsigned long long fact(unsigned int n) {
	unsigned long long res = 1;

	for (int i = 1; i <= n; i++) {
		res *= i;
	}

	return res;
}

void print_table() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%lf\t", table[i][j]);
		}

		printf("\n");
	}
}

double first_formula() {
	double res = table[0][1];
	
	for (int i = 2, k = 0; i < m; i++, k++) {
		double temp = 0;
		temp = table[0][i] / (pow(h, k + 1.0) * fact(k + 1.0));

		for (int j = 0; j < (i - 1); j++) {
			temp *= (x - table[j][0]);
		}

		res += temp;
	}

	return res;
}

double second_formula() {
	double res = table[n-1][1];

	for (int i = n - 2, k = 1, j = 2; i >= 0; i--, k++, j++) {
		double temp = table[i][j]/( fact(k) * pow(h, k) );

		for (int q = n - 1; q > i; q--) {
			temp *= (x - table[q][0]);
		}

		res += temp;
	}

	return res;
}

void calc_dy() {
	int offset = 1;

	for (int i = 2; i < m ; i++) {
		for (int j = 0; j < n - offset; j++) {
			table[j][i] = table[j+1][i-1] - table[j][i-1];
		}

		offset++;
	}
}


int main() {
	printf("n x\n");
	scanf("%i %lf", &n, &x);

	m = 2 + (n - 1);

	table = malloc( sizeof(double*) * n * m);

	for (int i = 0; i < n; i++) {
		table[i] = malloc(sizeof(double) * m);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			table[i][j] = 0.f;
		}
	}

	printf("\nCoordinates:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			scanf("%lf", &table[i][j]);
		}
	}

	if (n > 1) {
		h = fabs(table[0][0] - table[1][0]);
	}


	calc_dy();

	printf("\nTable:\n");

	print_table();

	double res;

	if ( fabs(table[0][0] - x) <= fabs(table[n-1][0] - x)) {
		res = first_formula();
	}
	else {
		res = second_formula();
	}

	printf("\nResult = %lf", res);


	//Очистка памяти
	for (int i = 0; i < n; i++) {
		free(table[i]);
	}

	free(table);

	getchar(); getchar();
	return 0;
}