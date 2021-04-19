#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(int *p, int *q) {
	int t;

	t = *p;
	*p = *q;
	*q = t;
}

void sort(int a[], int n) {
	int i, j, temp;

	for (i = 0;i < n - 1;i++) {
		for (j = 0;j < n - i - 1;j++) {
			if (a[j] > a[j + 1])
				swap(&a[j], &a[j + 1]);
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 1) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	if (argc < 3) {
		fprintf(stderr, "missing arguments\n");
		return 1;
	}
	FILE * c_stats;
	FILE * grades_file;
	int grade, median, max_grade, min_grade, num_of_stud = 0;
	float avg, passing_amount;

	// check number of students
	grades_file = fopen(argv[1], "rb");
	if (grades_file == NULL)
	{
		printf("Error. file \"grades.txt\" doesn't exist.\n");
		return 1;
	}
	while (fscanf(grades_file, "%d", &grade) != -1) {
		num_of_stud++;
	}
	fclose(grades_file);
	//
	int* grades_arr = (int*)malloc(num_of_stud * sizeof(int));
	// put grades into array, use it to calculate avarage and median
	grades_file = fopen(argv[1], "rb");
	if (grades_file == NULL)
	{
		printf("Error. file \"grades.txt\" doesn't exist.\n");
		return 1;
	}
	int indx = 0;
	while (fscanf(grades_file, "%d", &grade) != -1) {
		grades_arr[indx] = grade;
		indx++;
	}
	fclose(grades_file);
	sort(grades_arr, num_of_stud);
	float sum = 0;
	int passers = 0;
	for (int i = 0; i < num_of_stud; i++) {
		sum += grades_arr[i];
		if (grades_arr[i] >= 55)
			passers++;
	}
	avg = sum / (float)num_of_stud;
	median = grades_arr[(num_of_stud + 1) / 2];
	min_grade = grades_arr[0];
	max_grade = grades_arr[num_of_stud - 1];
	passing_amount = passers * 100.0 / (float)num_of_stud;
	int histogram[10][10];
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			histogram[i][j] = 0;
		}
	for (int i = 0; i < num_of_stud; i++) {
		grade = grades_arr[i] - 1;
		if (grade != -1)
			histogram[grade / 10][grade % 10]++;
	}

	c_stats = fopen(argv[2], "w");
	if (c_stats == NULL)
	{
		printf("Error\n");
		return 1;
	}

	fprintf(c_stats, "num of students = %d\n", num_of_stud);
	fprintf(c_stats, "avg = %.3f\n", avg);
	fprintf(c_stats, "the median is - %d\n", median);
	fprintf(c_stats, "max grade = %d, min grade = %d\n", max_grade, min_grade);
	fprintf(c_stats, "pass rate = %.2f\n", passing_amount);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			fprintf(c_stats, "%d", histogram[i][j]);
			if (j != 9)
				fprintf(c_stats, " ");
		}
		if (i != 9)
			fprintf(c_stats, "\n");
	}
	fclose(c_stats);




	return 0;
}
