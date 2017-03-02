#ifndef _MATRIX_H
#define _MATRIX_H

/* struct elem
 * Structure représentant une valeur de la matrice, faisant partie d'une liste
 * simplement chaînée.
 *
 * @next pointe vers l'élément suivant de la liste. NULL si dernier élément.
 * @j contient le numéro de colonne de l'élément (>= 0).
 * @value contient la valeur courante.
 */
struct elem {
	struct elem *next;
	unsigned int j;
	int value;
};

/* struct line
 * Structure représentant une ligne d'une matrice creuse, faisant partie d'une
 * liste simplement chaînée.
 *
 * @next pointe vers l'élément suivant de la liste. NULL si dernier élément.
 * @elems pointe vers la tête d'une liste simplement chaînée contenant les
 *	  valeurs de la ligne, dans un ordre d'indices croissant.
 * @i contient le numéro de ligne courant (>= 0).
 *
 * Comme nous sommes dans une matrice creuse, @elems ne contient pas forcément
 * autant d'éléments qu'il y a de colonnes. Les éléments manquants ont donc
 * une valeur de 0. @elems ne peut jamais valoir NULL (autrement dit, quand
 * une struct line existe, elle doit contenir au moins un élément différent
 * de 0).
 */
struct line {
	struct line *next;
	struct elem *elems;
	unsigned int i;
};

/* struct matrix
 * Structure représentant une matrice creuse.
 *
 * @lines pointe vers la tête d'une liste simplement chaînée contenant les
 *	  lignes de la matrice dans un ordre d'indices croissant.
 * @nlines contient le nombre de lignes de la matrice.
 * @ncols contient le nombre de colonnes de la matrice.
 *
 * Sachant que la matrice est creuse, le nombre d'éléments de la liste @lines
 * peut être inférieur à @nlines. Il ne peut bien entendu jamais être supérieur
 * à @nlines. Si une ligne n'est pas présente dans @lines, cela signifie que
 * tous ses éléments valent 0. Lorsque @lines vaut NULL, cela signifie que tous
 * les éléments de la matrice valent 0.
 */
struct matrix {
	struct line *lines;
	unsigned int nlines;
	unsigned int ncols;
};

/* matrix_init
 * Créer une nouvelle matrice creuse.
 *
 * @nlines: nombre de lignes
 * @ncols: nombre de colonnes
 * @return: pointeur vers la matrice ou NULL si erreur
 *
 * Préconditions: @nlines > 0 && @ncols > 0
 * Postconditions: Les éléments de la nouvelle matrice sont initialisés à 0.
 *		   @m->nlines > 0 && @m->ncols > 0
 */
struct matrix *matrix_init(unsigned int nlines, unsigned int ncols);

/* matrix_free
 * Libère la mémoire allouée à une matrice.
 *
 * @matrix: Matrice à libérer.
 *
 * Préconditions: /
 * Postconditions: La mémoire de @matrix est libérée.
 */
void matrix_free(struct matrix *matrix);

/* matrix_set
 * Défini la valeur d'un élément de la matrice.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @val: valeur à définir
 * @return: -1 si erreur, 0 sinon
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: L'élément (@i,@j) de la matrice @matrix vaut @val.
 */
int matrix_set(struct matrix *matrix, unsigned int i, unsigned int j, int val);

/* matrix_get
 * Récupère la valeur d'un élément de la matrice.
 *
 * @matrix: Matrice
 * @i: numéro de ligne
 * @j: numéro de colonne
 * @return: valeur de l'élément (@i,@j) de la matrice
 *
 * Préconditions: 0 <= @i < @matrix->nlines && 0 <= @j < @matrix->ncols
 * Postconditions: @matrix est inchangé.
 */
int matrix_get(const struct matrix *matrix, unsigned int i, unsigned int j);

/* matrix_add
 * Additionne deux matrices.
 *
 * @m1: premier opérande
 * @m2: deuxième opérande
 * @return: Matrice creuse résultant de l'addition de @m1 et @m2,
 *	    ou NULL si erreur
 *
 * Préconditions: @m1 != NULL && @m2 != NULL
 * Postconditions: @m1 et @m2 inchangés.
 */
struct matrix *matrix_add(const struct matrix *m1, const struct matrix *m2);

/* matrix_transpose
 * Calcule la transposée d'une matrice.
 *
 * @matrix: opérande
 * @return: Matrice creuse étant la transposée de @matrix
 *
 * Préconditions: @matrix != NULL
 * Postconditions: @matrix est inchangé.
 */
struct matrix *matrix_transpose(const struct matrix *matrix);

/* matrix_convert
 * Transforme un tableau bidimensionnel en une matrice creuse.
 *
 * @array: tableau de valeurs à transformer
 * @nlines: nombre de lignes du tableau
 * @ncols: nombre de colonnes du tableau
 * @return: matrice creuse correspondante au tableau ou NULL si erreur
 *
 * Préconditions: array != NULL && 0 <= i < @nlines => array[i] != NULL
 * Postconditions: array est inchangé && 0 <= i < @nlines, 0 <= j < @ncols
 *		   => matrix_get(@return, i, j) == array[i][j]
 */
struct matrix *matrix_convert(const int **array, unsigned int nlines,
			      unsigned int ncols);

#endif
