#ifndef PPM_H
#define PPM_H

/**
 * @file ppm.h
 * @brief D�clarations et fonctions utilitaires pour manipuler des images au format PPM.
 *
 * Ce fichier d�finit des structures et des fonctions pour cr�er, manipuler
 * et exporter des images au format PPM (Portable Pixmap Format).
 * Il offre une abstraction simple pour g�rer des images couleur (RGB).
 */

/**
 * @struct ppm_pixel
 * @brief Repr�sente un pixel d'une image PPM.
 *
 * Les valeurs des composantes rouge (r), verte (g), et bleue (b)
 * sont stock�es sous forme de valeurs non sign�es sur 8 bits.
 */
struct ppm_pixel {
  unsigned char r; /**< Composante rouge du pixel. */
  unsigned char g; /**< Composante verte du pixel. */
  unsigned char b; /**< Composante bleue du pixel. */
};

/**
 * @brief Initialise un pixel avec des valeurs de couleur.
 *
 * @param px Pointeur vers le pixel � initialiser.
 * @param r Composante rouge du pixel (0-255).
 * @param g Composante verte du pixel (0-255).
 * @param b Composante bleue du pixel (0-255).
 */
static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) {
  px->r = r;
  px->g = g;
  px->b = b;
}

/**
 * @struct ppm_image
 * @brief Repr�sente une image PPM.
 *
 * Contient les dimensions de l'image (largeur et hauteur) et un tableau
 * dynamique de pixels.
 */
struct ppm_image {
  unsigned int width;  /**< Largeur de l'image. */
  unsigned int height; /**< Hauteur de l'image. */
  struct ppm_pixel *px; /**< Tableau dynamique de pixels. */
};

/**
 * @brief Initialise une image PPM avec une largeur et une hauteur sp�cifiques.
 *
 * Alloue la m�moire n�cessaire pour les pixels.
 *
 * @param im Pointeur vers la structure ppm_image � initialiser.
 * @param w Largeur de l'image en pixels.
 * @param h Hauteur de l'image en pixels.
 * @return 0 en cas de succ�s, 1 en cas d'erreur (ex. : allocation �chou�e).
 */
int ppm_image_init(struct ppm_image *im, int w, int h);

/**
 * @brief Lib�re les ressources associ�es � une image PPM.
 *
 * Lib�re la m�moire allou�e pour les pixels et r�initialise la structure.
 *
 * @param im Pointeur vers la structure ppm_image � lib�rer.
 * @return 0 en cas de succ�s, 1 si l'image est d�j� lib�r�e ou invalide.
 */
int ppm_image_release(struct ppm_image *im);

/**
 * @brief D�finit un pixel d'une image PPM � des coordonn�es sp�cifiques.
 *
 * @param im Pointeur vers la structure ppm_image.
 * @param x Coordonn�e horizontale (colonne) du pixel (0 = x < largeur).
 * @param y Coordonn�e verticale (ligne) du pixel (0 = y < hauteur).
 * @param r Composante rouge du pixel (0-255).
 * @param g Composante verte du pixel (0-255).
 * @param b Composante bleue du pixel (0-255).
 */
static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) {
  struct ppm_pixel *px = im->px + im->width * y + x;
  ppm_setpixel(px, r, g, b);
}

/**
 * @brief Exporte une image PPM vers un fichier au format PPM.
 *
 * @param im Pointeur vers la structure ppm_image � exporter.
 * @param path Chemin du fichier de sortie.
 * @return 0 en cas de succ�s, 1 en cas d'erreur (ex. : fichier inaccessible).
 */
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */

