#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#if defined _WIN32
  char *PATH_SEPARATOR = "\\";
#else
  char *PATH_SEPARATOR = "/";
#endif

/*
 * Structs
 * ------- */

enum color { red = 0, green, blue, yellow, cyan, magenta, black };

char *color_array[] = { "red", "green", "blue", "yellow", "cyan", "magenta", "black" };

char *color_to_string(enum color c);
enum color string_to_color(char *c);

typedef struct rect {
  int id;
  int x;
  int y;
  int w;
  int h;
  enum color c;
  int f;
} rect_t;

typedef struct node {
  rect_t data;
  struct node *next;
} node_t;

/*
 * Simple list methods
 * ------------------- */

int is_smaller_than(rect_t *r1, rect_t *r2);
node_t *add(node_t *root, rect_t *data);

void debug(node_t *root);
void print(node_t *root);
void get_file_name(char *path, char *file_name);
void draw(node_t *root, char* filename, int width, int height);

/*
 * Main
 * ---- */

int main(int argc, char *argv[]) {
  int i, j, n, width, height, min_area, max_area, min_id, max_id;
  char file_name[20];
  node_t *root = NULL, *t;

  FILE *fin = fopen(argv[1], "r");

  if (fin == (FILE *) NULL) { fprintf(stderr, "File error!\n"); return -1; }

  fscanf(fin, "%d %d %d", &n, &width, &height);

  min_area = width * height;
  max_area = 0;

  for (i = 0; i < n ; i++) {
    int x, y, w, h, f;
    char c[8];

    rect_t *data;

    data = malloc(sizeof(rect_t));

    fscanf(fin, "%d %d %d %d %s %d", &x, &y, &w, &h, c, &f);

    if ((x + w > width) || (y + h > height)) {
      printf("rectangle %d has wrong definition\n", i);
      return -1;
    }

    data->id = i;
    data->x = x;
    data->y = y;
    data->w = w;
    data->h = h;
    data->c = string_to_color(c);
    data->f = f;

    if (w * h < min_area) {
      min_id = i;
      min_area = w * h;
    }

    if (w * h > max_area) {
      max_id = i;
      max_area = w * h;
    }

    root = add(root, data);
  }

  printf("min area: %d: %d\n", min_id, min_area);
  printf("max area: %d: %d\n", max_id, max_area);
  printf("\n");

  /* debug(root); */

  print(root);

  get_file_name(argv[1], file_name);
  draw(root, file_name, width, height);

  fclose(fin);

  return 0;
}

/*
 * Enum functions
 * ------------------- */

char *color_to_string(enum color c) {
  return color_array[c];
}

enum color string_to_color(char *c) {
  unsigned int n = sizeof(color_array)/sizeof(color_array[0]);
  unsigned int i;

  for (i = 0; i < n; i++) {
      if (strcmp(color_array[i], c) == 0) {
          return i;
      }
  }

  return 0;
}

/*
 * Simple list methods
 * ------------------- */

int is_smaller_than(rect_t *r1, rect_t *r2) {
  int a1 = (r1->w * r1->h), a2 = (r2->w * r2->h);

  return a1 < a2 || (a1 == a2 && r1->id < r2->id);
}

node_t *add(node_t *root, rect_t *data) {
  node_t *pointer, *new;

  new = malloc(sizeof(node_t));

  new->data = *data;

  if (root == NULL || is_smaller_than(data, &root->data)) { /* Empty list case */
    new->next = root;
    return new;
  }

  pointer = root;

  while (pointer->next != NULL && is_smaller_than(&pointer->next->data, data)) {
    pointer = pointer->next;
  }

  new->next = pointer->next;
  pointer->next = new;

  return root;
}

/*
 * Debug
 * ----- */

void debug(node_t *root) {
  node_t *node = root;

  printf("--------------------------------------------------\n");
  printf("|  id |   x |   y |   w |   h |   color | filled |\n");
  printf("--------------------------------------------------\n");

  while (node != NULL) {
    printf("| %3d | %3d | %3d | %3d | %3d | %7s | %8s |\n", node->data.id, node->data.x, node->data.y, node->data.w, node->data.h, color_to_string(node->data.c), node->data.f ? "✔" : "✗");
    node = node->next;
  }

  printf("--------------------------------------------------\n");
}

/*
 * Print
 * ----- */

void print(node_t *root) {
  int i;
  node_t *t;

  printf("rectangles by area:\n");

  t = root;

  while (t != NULL) {
    printf("%d: %d\n", t->data.id, (t->data.w * t->data.h));
    t = t->next;
  }

  printf("\n");
  printf("rectangles by color:\n");

  for (i = red; i <= black; i++) {
    int first = 1;

    printf("%s:", color_to_string(i));

    t = root;

    while (t != NULL) {
      if (t->data.c == i) {
        printf("%s %d", first ? "" : ",", t->data.id);
        first = 0;
      }

      t = t->next;
    }

    printf("\n");
  }
}

/*
 * Bonus
 * ----- */

/* String Split - How to play with strings in C - https://bit.ly/3pousUu */
void get_file_name(char *path, char *file_name) {
  char *temp = strtok(path, PATH_SEPARATOR);

  while (temp != NULL) {
    strcpy(file_name, temp);
    temp = strtok(NULL, PATH_SEPARATOR);
  }

  temp = strtok(file_name, ".");

  strcpy(file_name, temp);
  strcat(file_name, ".xpm");
}

void draw(node_t *root, char* filename, int width, int height) {
  int i, j;
  FILE *fout = fopen(filename, "w");
  char **buffer, c;
  node_t *t;

  if (fout == (FILE *) NULL) { fprintf(stderr, "File error!\n"); exit(-1); }

  buffer = malloc(height * sizeof(char*));

  for (i = 0; i < height; i++) {
    buffer[i] = malloc(width * sizeof(char));

    for (j = 0; j < width; j++) {
      buffer[i][j] = ' ';
    }
  }

  t = root;

  while (t != NULL) {
    switch (t->data.c) {
      case red:
      case green:
      case blue:
      case yellow:
      case cyan:
      case magenta:
        c = color_to_string(t->data.c)[0];
        break;
      case black:
        c = '.';
        break;
    }

    for (i = t->data.y; i < t->data.y + t->data.h; i++) {
      for (j = t->data.x; j < t->data.x + t->data.w; j++) {
        int top_line = t->data.y;
        int bottom_line = t->data.y + t->data.h - 1;
        int left_line = t->data.x;
        int right_line = t->data.x + t->data.w - 1;

        if (t->data.f || i == top_line || j == left_line || i == bottom_line || j == right_line) {
          buffer[j][i] = c; /* FIX: */
        }
      }
    }

    t = t->next;
  }

  fprintf(fout, "/* XPM */\n");
  fprintf(fout, "static char * o[]utput_xpm = {\n");
  fprintf(fout, "/* <Values> */\n");
  fprintf(fout, "/* <width/columns> <height/rows> <colors> <chars per pixel>*/\n");
  fprintf(fout, "\"%d %d 8 1\",\n", width, height);
  fprintf(fout, "/* <Colors> */\n");
  fprintf(fout, "\"r c #ff0000\",\n");
  fprintf(fout, "\"g c #00ff00\",\n");
  fprintf(fout, "\"b c #0000ff\",\n");
  fprintf(fout, "\"y c #ffff00\",\n");
  fprintf(fout, "\"c c #00ffff\",\n");
  fprintf(fout, "\"m c #ff00ff\",\n");
  fprintf(fout, "\". c #000000\",\n");
  fprintf(fout, "\"  c #ffffff\",\n");
  fprintf(fout, "/* <Pixels> */\n");

  for (i = 0; i < height; i++) {
    fprintf(fout, "\"");

    for (j = 0; j < width; j++) {
      fprintf(fout, "%c", buffer[i][j]);
    }

    fprintf(fout, "\"%s\n", (i < height - 1) ? "," : "");
  }

  fprintf(fout, "};\n");

  fclose(fout);
}
