#include <stdlib.h>

#include "matrix.h"

struct matrix *matrix_init(unsigned int nlines, unsigned int ncols) {
	struct matrix *m = malloc(sizeof (struct matrix));
	if (!m) {
		return NULL;
	}
	m->lines = NULL;
	m->nlines = nlines;
	m->ncols = ncols;
	return m;
}

void matrix_free(struct matrix *m) {
	struct line *curline = m->lines;
	while (curline) {
		struct elem *curelem = curline->elems;
		while (curelem) {
			struct elem *tmp = curelem;
			curelem = curelem->next;
			free(tmp);
		}
		struct line *tmp = curline;
		curline = curline->next;
		free(tmp);
	}
	free(m);
}

int matrix_set(struct matrix *m, unsigned int i, unsigned int j, int val) {
	struct line **curline = &m->lines;
	while (*curline && (*curline)->i < i) {
		curline = &(*curline)->next;
	}
	if (!*curline || (*curline)->i > i) { /* line i does not exist */
		if (val == 0) {
			return 0;
		}
		struct line *oldline = *curline;
		*curline = malloc(sizeof (struct line));
		if (!*curline) {
			return -1;
		}
		(*curline)->next = oldline;
		(*curline)->elems = NULL;
		(*curline)->i = i;
	}

	struct elem **curelem = &(*curline)->elems;
	struct elem *firstelem = *curelem;
	while (*curelem && (*curelem)->j < j) {
		curelem = &(*curelem)->next;
	}
	if (!*curelem || (*curelem)->j > j) { /* element i,j does not exist */
		if (val == 0) {
			return 0;
		}
		struct elem *oldelem = *curelem;
		*curelem = malloc(sizeof (struct elem));
		if (!*curelem) {
			return -1;
		}
		(*curelem)->next = oldelem;
		(*curelem)->j = j;
		(*curelem)->value = val;
	}

	if (val == 0 && firstelem == *curelem) {
		free(firstelem);
		struct line *oldline = *curline;
		*curline = (*curline)->next;
		free(oldline);
	}

	return 0;
}

int matrix_get(const struct matrix *m, unsigned int i, unsigned int j) {
	struct line **curline = (struct line **) &m->lines;
	while (*curline && (*curline)->i < i) {
		curline = &(*curline)->next;
	}
	if (!*curline || (*curline)->i > i) { /* line i does not exist */
		return 0;
	}

	struct elem **curelem = &(*curline)->elems;
	while (*curelem && (*curelem)->j < j) {
		curelem = &(*curelem)->next;
	}
	if (!*curelem || (*curelem)->j > j) { /* element i,j does not exist */
		return 0;
	}

	return (*curelem)->value;
}

struct matrix *matrix_add(const struct matrix *m1, const struct matrix *m2) {
	if (m1->nlines != m2->nlines || m1->ncols != m2->ncols) {
		return NULL;
	}
	struct matrix *m3 = matrix_init(m1->nlines, m1->ncols);
	if (!m3) {
		return NULL;
	}
	for (unsigned int i = 0; i < m1->nlines; i++) {
		for (unsigned int j = 0; j < m1->ncols; j++) {
			int sum = matrix_get(m1, i, j) + matrix_get(m2, i, j);
			if (matrix_set(m3, i, j, sum) != 0) {
				matrix_free(m3);
				return NULL;
			}
		}
	}
	return m3;
}

struct matrix *matrix_transpose(const struct matrix *m) {
	struct matrix *t = matrix_init(m->ncols, m->nlines);
	if (!t) {
		return NULL;
	}
	for (unsigned int i = 0; i < m->nlines; i++) {
		for (unsigned int j = 0; j < m->ncols; j++) {
			int val = matrix_get(m, i, j);
			if (matrix_set(t, j, i, val) != 0) {
				matrix_free(t);
				return NULL;
			}
		}
	}
	return t;
}

struct matrix *matrix_convert(const int **array, unsigned int nlines,
			      unsigned int ncols) {
	struct matrix *m = matrix_init(nlines, ncols);
	if (!m) {
		return NULL;
	}
	for (unsigned int i = 0; i < nlines; i++) {
		for (unsigned int j = 0; j < ncols; j++) {
			if (matrix_set(m, i, j, array[i][j]) != 0) {
				matrix_free(m);
				return NULL;
			}
		}
	}
	return m;
}
