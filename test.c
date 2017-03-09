#include <stdlib.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

#include "matrix.h"

void test_matrix_init(void) {
	struct matrix *m = matrix_init(10, 20);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m);
	CU_ASSERT_PTR_NULL(m->lines);
	CU_ASSERT_EQUAL(m->nlines, 10);
	CU_ASSERT_EQUAL(m->ncols, 20);
	matrix_free(m);
}

void test_matrix_set(void) {
	struct matrix *m = matrix_init(10, 20);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m);

	CU_ASSERT_EQUAL(matrix_set(m, 0, 0, 1), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 0, 1, 2), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 5, 15, 3), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 5, 15, 3), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 5, 16, 0), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 1, 0, 4), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 1, 2, 6), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 1, 1, 5), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 2, 2, 1), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 2, 2, 0), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 3, 1, 1), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 3, 0, 0), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 3, 1, 0), 0);
	CU_ASSERT_EQUAL(matrix_set(m, 4, 0, 0), 0);

	struct line *line0 = m->lines;
	CU_ASSERT_PTR_NOT_NULL_FATAL(line0);
	CU_ASSERT_EQUAL(line0->i, 0);

		struct elem *elem00 = line0->elems;
		CU_ASSERT_PTR_NOT_NULL_FATAL(elem00);
		CU_ASSERT_EQUAL(elem00->j, 0);
		CU_ASSERT_EQUAL(elem00->value, 1);

		struct elem *elem01 = elem00->next;
		CU_ASSERT_PTR_NOT_NULL_FATAL(elem01);
		CU_ASSERT_EQUAL(elem01->j, 1);
		CU_ASSERT_EQUAL(elem01->value, 2);

	struct line *line1 = line0->next;
	CU_ASSERT_PTR_NOT_NULL_FATAL(line1);
	CU_ASSERT_EQUAL(line1->i, 1);

		struct elem *elem10 = line1->elems;
		CU_ASSERT_PTR_NOT_NULL_FATAL(elem10);
		CU_ASSERT_EQUAL(elem10->j, 0);
		CU_ASSERT_EQUAL(elem10->value, 4);

		struct elem *elem11 = elem10->next;
		CU_ASSERT_PTR_NOT_NULL_FATAL(elem11);
		CU_ASSERT_EQUAL(elem11->j, 1);
		CU_ASSERT_EQUAL(elem11->value, 5);

		struct elem *elem12 = elem11->next;
		CU_ASSERT_PTR_NOT_NULL_FATAL(elem12);
		CU_ASSERT_EQUAL(elem12->j, 2);
		CU_ASSERT_EQUAL(elem12->value, 6);

	struct line *line5 = line1->next;
	CU_ASSERT_PTR_NOT_NULL_FATAL(line5);
	CU_ASSERT_EQUAL(line5->i, 5);

		struct elem *elem515 = line5->elems;
		CU_ASSERT_PTR_NOT_NULL_FATAL(elem515);
		CU_ASSERT_EQUAL(elem515->j, 15);
		CU_ASSERT_EQUAL(elem515->value, 3);
		CU_ASSERT_PTR_NULL(elem515->next);

	CU_ASSERT_PTR_NULL(line5->next);

	matrix_free(m);
}

void test_matrix_get(void) {
	struct matrix *m = matrix_init(10, 20);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m);

	CU_ASSERT_EQUAL_FATAL(matrix_set(m, 0, 0, 1), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m, 0, 1, 2), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m, 5, 15, 3), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m, 5, 15, 3), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m, 1, 0, 4), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m, 1, 2, 6), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m, 1, 1, 5), 0);

	CU_ASSERT_EQUAL(matrix_get(m, 0, 0), 1);
	CU_ASSERT_EQUAL(matrix_get(m, 0, 1), 2);
	CU_ASSERT_EQUAL(matrix_get(m, 0, 2), 0);
	CU_ASSERT_EQUAL(matrix_get(m, 1, 0), 4);
	CU_ASSERT_EQUAL(matrix_get(m, 1, 1), 5);
	CU_ASSERT_EQUAL(matrix_get(m, 1, 2), 6);
	CU_ASSERT_EQUAL(matrix_get(m, 2, 5), 0);
	CU_ASSERT_EQUAL(matrix_get(m, 5, 15), 3);
	CU_ASSERT_EQUAL(matrix_get(m, 9, 19), 0);

	matrix_free(m);
}

void test_matrix_add(void) {
	struct matrix *m1 = matrix_init(10, 20);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m1);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 0, 0, 1), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 0, 1, 2), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 5, 15, 3), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 5, 15, 3), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 1, 0, 4), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 1, 2, 6), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 1, 1, 5), 0);

	struct matrix *m2 = matrix_init(10, 20);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m2);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m2, 0, 0, 1), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m2, 0, 1, 2), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m2, 5, 15, 3), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m2, 5, 15, 3), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m2, 1, 0, 4), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m2, 1, 2, 6), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m2, 1, 1, 5), 0);

	struct matrix *m3 = matrix_add(m1, m2);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m3);
	CU_ASSERT_EQUAL(matrix_get(m3, 0, 0), 2);
	CU_ASSERT_EQUAL(matrix_get(m3, 0, 1), 4);
	CU_ASSERT_EQUAL(matrix_get(m3, 0, 2), 0);
	CU_ASSERT_EQUAL(matrix_get(m3, 1, 0), 8);
	CU_ASSERT_EQUAL(matrix_get(m3, 1, 1), 10);
	CU_ASSERT_EQUAL(matrix_get(m3, 1, 2), 12);
	CU_ASSERT_EQUAL(matrix_get(m3, 2, 5), 0);
	CU_ASSERT_EQUAL(matrix_get(m3, 5, 15), 6);
	CU_ASSERT_EQUAL(matrix_get(m3, 9, 19), 0);

	struct matrix *m4 = matrix_init(1, 2);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m4);
	struct matrix *m5 = matrix_init(2, 1);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m4);
	CU_ASSERT_PTR_NULL(matrix_add(m4, m5));

	matrix_free(m1);
	matrix_free(m2);
	matrix_free(m3);
	matrix_free(m4);
	matrix_free(m5);
}

void test_matrix_transpose(void) {
	struct matrix *m1 = matrix_init(2, 3);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m1);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 0, 0, 1), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 0, 1, 2), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 0, 2, 3), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 1, 0, 4), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 1, 1, 5), 0);
	CU_ASSERT_EQUAL_FATAL(matrix_set(m1, 1, 2, 6), 0);

	struct matrix *m2 = matrix_transpose(m1);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m2);
	CU_ASSERT_EQUAL(matrix_get(m2, 0, 0), 1);
	CU_ASSERT_EQUAL(matrix_get(m2, 0, 1), 4);
	CU_ASSERT_EQUAL(matrix_get(m2, 1, 0), 2);
	CU_ASSERT_EQUAL(matrix_get(m2, 1, 1), 5);
	CU_ASSERT_EQUAL(matrix_get(m2, 2, 0), 3);
	CU_ASSERT_EQUAL(matrix_get(m2, 2, 1), 6);

	matrix_free(m1);
	matrix_free(m2);
}

void test_matrix_convert(void) {
	int **a = malloc(2 * sizeof (int *));
	a[0] = malloc(2 * sizeof (int));
	a[0][0] = 1;
	a[0][1] = 0;
	a[1] = malloc(2 * sizeof (int));
	a[1][0] = 0;
	a[1][1] = 4;

	struct matrix *m = matrix_convert((const int **) a, 2, 2);
	CU_ASSERT_PTR_NOT_NULL_FATAL(m);
	CU_ASSERT_EQUAL(matrix_get(m, 0, 0), 1);
	CU_ASSERT_EQUAL(matrix_get(m, 0, 1), 0);
	CU_ASSERT_EQUAL(matrix_get(m, 1, 0), 0);
	CU_ASSERT_EQUAL(matrix_get(m, 1, 1), 4);

	matrix_free(m);
	free(a[0]);
	free(a[1]);
	free(a);
}

int main(void) {
	if (CU_initialize_registry() != CUE_SUCCESS) {
		return CU_get_error();
	}

	CU_pSuite suite = CU_add_suite("matrix", NULL, NULL);
	if (!suite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (!CU_add_test(suite, "matrix_init", test_matrix_init) ||
	    !CU_add_test(suite, "matrix_set", test_matrix_set) ||
	    !CU_add_test(suite, "matrix_get", test_matrix_get) ||
	    !CU_add_test(suite, "matrix_add", test_matrix_add) ||
	    !CU_add_test(suite, "matrix_transpose", test_matrix_transpose) ||
	    !CU_add_test(suite, "matrix_convert", test_matrix_convert)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_cleanup_registry();

	return 0;
}
