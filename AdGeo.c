/*
 * Advanced Geometry Analyzer and Shape Classification System
 *
 * Constraints:
 * - No Arrays
 * - No Pointers
 * - Use only: Functions, Loops, If/Switch, Math library
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* -- Constants for floating point comparison -- */
#define EPSILON 0.001

/* -- Function Prototypes -- */
double calculate_distance(double x1, double y1, double x2, double y2);
double calculate_slope(double x1, double y1, double x2, double y2);
void analyze_line(void);
void analyze_triangle(void);
void analyze_quadrilateral(void);
void analyze_circle(void);
void plot_points(double x1, double y1, double x2, double y2, double x3,
                 double y3, double x4, double y4, int n);
void plot_circle_shape(double cx, double cy, double radius);
int are_equal(double a, double b);

int main() {
  int choice;
  int running = 1;

  printf("==================================================\n");
  printf("   ADVANCED GEOMETRY ANALYZER & CLASSIFIER\n");
  printf("==================================================\n");

  while (running) {
    printf("\nSelect an Operation:\n");
    printf("1. Analyze 2 Points (Line Segment)\n");
    printf("2. Analyze 3 Points (Triangle Classification)\n");
    printf("3. Analyze 4 Points (Quadrilateral Classification)\n");
    printf("4. Analyze Circle (Center + Radius Point)\n");
    printf("0. Exit System\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      analyze_line();
      break;
    case 2:
      analyze_triangle();
      break;
    case 3:
      analyze_quadrilateral();
      break;
    case 4:
      analyze_circle();
      break;
    case 0:
      printf("Exiting system. Goodbye!\n");
      running = 0;
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}

/* * Helper: Calculates Euclidean distance between two points
 * Formula: sqrt((x2-x1)^2 + (y2-y1)^2)
 */
double calculate_distance(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/* * Helper: Compares two doubles with a small margin of error (Epsilon)
 * Because floating point math isn't always 100% precise.
 */
int are_equal(double a, double b) {
  double diff = a - b;
  if (diff < 0)
    diff = -diff; // Absolute value
  return (diff < EPSILON);
}

/* Feature 1: Line Analysis */
void analyze_line(void) {
  double x1, y1, x2, y2;
  double dist, slope;

  printf("\n--- Line Segment Analysis ---\n");
  printf("Enter Point 1 (x y): ");
  scanf("%lf %lf", &x1, &y1);
  printf("Enter Point 2 (x y): ");
  scanf("%lf %lf", &x2, &y2);

  dist = calculate_distance(x1, y1, x2, y2);

  printf("Length: %.2lf units\n", dist);

  /* Check for vertical line to avoid division by zero */
  if (are_equal(x1, x2)) {
    printf("Slope: Undefined (Vertical Line)\n");
    printf("Type: Vertical\n");
  } else {
    slope = (y2 - y1) / (x2 - x1);
    printf("Slope: %.2lf\n", slope);
    if (are_equal(slope, 0)) {
      printf("Type: Horizontal\n");
    } else if (slope > 0) {
      printf("Type: Ascending\n");
    } else {
      printf("Type: Descending\n");
    }
  }

  printf("\nVisualizing Line Endpoints:\n");
  plot_points(x1, y1, x2, y2, 0, 0, 0, 0, 2);
}

/* Feature 2: Triangle Analysis and Classification */
void analyze_triangle(void) {
  double x1, y1, x2, y2, x3, y3;
  double side_a, side_b, side_c;
  double perimeter, s, area;

  printf("\n--- Triangle Classification ---\n");
  printf("Enter Point 1 (x y): ");
  scanf("%lf %lf", &x1, &y1);
  printf("Enter Point 2 (x y): ");
  scanf("%lf %lf", &x2, &y2);
  printf("Enter Point 3 (x y): ");
  scanf("%lf %lf", &x3, &y3);

  /* Calculate lengths of sides */
  side_a = calculate_distance(x1, y1, x2, y2);
  side_b = calculate_distance(x2, y2, x3, y3);
  side_c = calculate_distance(x3, y3, x1, y1);

  printf("Side lengths: A=%.2lf, B=%.2lf, C=%.2lf\n", side_a, side_b, side_c);

  /* Check Validity (Triangle Inequality Theorem) */
  if ((side_a + side_b <= side_c) || (side_a + side_c <= side_b) ||
      (side_b + side_c <= side_a)) {
    printf("ERROR: These points do not form a valid triangle (Collinear).\n");
    return;
  }

  /* Perimeter */
  perimeter = side_a + side_b + side_c;
  printf("Perimeter: %.2lf\n", perimeter);

  /* Area using Heron's Formula */
  s = perimeter / 2;
  area = sqrt(s * (s - side_a) * (s - side_b) * (s - side_c));
  printf("Area: %.2lf sq units\n", area);

  /* Classification by Sides */
  printf("Classification: ");
  if (are_equal(side_a, side_b) && are_equal(side_b, side_c)) {
    printf("Equilateral Triangle\n");
  } else if (are_equal(side_a, side_b) || are_equal(side_b, side_c) ||
             are_equal(side_c, side_a)) {
    printf("Isosceles Triangle\n");
  } else {
    printf("Scalene Triangle\n");
  }

  /* Check for Right Angled (Pythagorean theorem) */
  /* We check a^2 + b^2 = c^2 for all combinations */
  double aa = pow(side_a, 2);
  double bb = pow(side_b, 2);
  double cc = pow(side_c, 2);

  if (are_equal(aa + bb, cc) || are_equal(aa + cc, bb) ||
      are_equal(bb + cc, aa)) {
    printf("Property: Right-Angled\n");
  }

  printf("\nVisualizing Triangle:\n");
  plot_points(x1, y1, x2, y2, x3, y3, 0, 0, 3);
}

/* Feature 3: Quadrilateral Analysis */
void analyze_quadrilateral(void) {
  double x1, y1, x2, y2, x3, y3, x4, y4;
  double s1, s2, s3, s4; /* Sides */
  double d1, d2;         /* Diagonals */

  printf("\n--- Quadrilateral Classification ---\n");
  printf(
      "Note: Please enter points in order (clockwise or counter-clockwise)\n");
  printf("Enter Point 1 (x y): ");
  scanf("%lf %lf", &x1, &y1);
  printf("Enter Point 2 (x y): ");
  scanf("%lf %lf", &x2, &y2);
  printf("Enter Point 3 (x y): ");
  scanf("%lf %lf", &x3, &y3);
  printf("Enter Point 4 (x y): ");
  scanf("%lf %lf", &x4, &y4);

  /* Calculate Sides */
  s1 = calculate_distance(x1, y1, x2, y2); /* Top? */
  s2 = calculate_distance(x2, y2, x3, y3); /* Right? */
  s3 = calculate_distance(x3, y3, x4, y4); /* Bottom? */
  s4 = calculate_distance(x4, y4, x1, y1); /* Left? */

  /* Calculate Diagonals */
  d1 = calculate_distance(x1, y1, x3, y3);
  d2 = calculate_distance(x2, y2, x4, y4);

  printf("Sides: %.2lf, %.2lf, %.2lf, %.2lf\n", s1, s2, s3, s4);
  printf("Diagonals: %.2lf, %.2lf\n", d1, d2);
  printf("Perimeter: %.2lf\n", s1 + s2 + s3 + s4);

  /* Classification Logic */
  printf("Shape Estimate: ");

  /* Check for Square: All sides equal AND diagonals equal */
  if (are_equal(s1, s2) && are_equal(s2, s3) && are_equal(s3, s4)) {
    if (are_equal(d1, d2)) {
      printf("Square\n");
    } else {
      printf("Rhombus (Diamond)\n");
    }
  }
  /* Check for Rectangle: Opposite sides equal AND diagonals equal */
  else if (are_equal(s1, s3) && are_equal(s2, s4)) {
    if (are_equal(d1, d2)) {
      printf("Rectangle\n");
    } else {
      printf("Parallelogram\n");
    }
  }
  /* Kite Check: Adjacent pairs equal */
  else if ((are_equal(s1, s2) && are_equal(s3, s4)) ||
           (are_equal(s2, s3) && are_equal(s4, s1))) {
    printf("Kite\n");
  } else {
    printf("General Quadrilateral / Trapezoid\n");
  }

  printf("\nVisualizing Quadrilateral:\n");
  plot_points(x1, y1, x2, y2, x3, y3, x4, y4, 4);
}

/* Feature 4: Circle Analysis */
void analyze_circle(void) {
  double cx, cy, px, py;
  double radius, area, circum;
  double PI = 3.141592653589793;

  printf("\n--- Circle Analysis ---\n");
  printf("Enter Center Point (x y): ");
  scanf("%lf %lf", &cx, &cy);
  printf("Enter a Point on Circumference (x y): ");
  scanf("%lf %lf", &px, &py);

  radius = calculate_distance(cx, cy, px, py);

  if (are_equal(radius, 0)) {
    printf("Error: Radius is zero. This is a point, not a circle.\n");
    return;
  }

  area = PI * pow(radius, 2);
  circum = 2 * PI * radius;

  printf("Radius: %.2lf\n", radius);
  printf("Diameter: %.2lf\n", radius * 2);
  printf("Circumference: %.2lf\n", circum);
  printf("Area: %.2lf\n", area);

  printf("\nVisualizing Circle:\n");
  plot_circle_shape(cx, cy, radius);
}

/* * Visualization Function for Points
 * Takes 4 sets of coordinates, but uses 'n' to decide how many to check.
 */
void plot_points(double x1, double y1, double x2, double y2, double x3,
                 double y3, double x4, double y4, int n) {
  int min_x, max_x, min_y, max_y;
  int x, y;

  /* Initialize bounds with first point */
  min_x = (int)x1;
  max_x = (int)x1;
  min_y = (int)y1;
  max_y = (int)y1;

  /* Expand bounds based on number of points */
  if (n >= 2) {
    if ((int)x2 < min_x)
      min_x = (int)x2;
    if ((int)x2 > max_x)
      max_x = (int)x2;
    if ((int)y2 < min_y)
      min_y = (int)y2;
    if ((int)y2 > max_y)
      max_y = (int)y2;
  }
  if (n >= 3) {
    if ((int)x3 < min_x)
      min_x = (int)x3;
    if ((int)x3 > max_x)
      max_x = (int)x3;
    if ((int)y3 < min_y)
      min_y = (int)y3;
    if ((int)y3 > max_y)
      max_y = (int)y3;
  }
  if (n >= 4) {
    if ((int)x4 < min_x)
      min_x = (int)x4;
    if ((int)x4 > max_x)
      max_x = (int)x4;
    if ((int)y4 < min_y)
      min_y = (int)y4;
    if ((int)y4 > max_y)
      max_y = (int)y4;
  }

  /* Add Padding and ensure Origin (0,0) is visible */
  if (min_x > 0)
    min_x = 0; // Ensure origin X is included
  if (max_x < 0)
    max_x = 0; // Ensure origin X is included
  if (min_y > 0)
    min_y = 0; // Ensure origin Y is included
  if (max_y < 0)
    max_y = 0; // Ensure origin Y is included

  min_x -= 2;
  max_x += 2;
  min_y -= 2;
  max_y += 2;

  printf("\n  Graph (Y runs Top to Bottom of visual):\n");

  /* Loop Y from Max to Min (so positive Y is at top) */
  for (y = max_y; y >= min_y; y--) {
    printf("%3d | ", y); // Print Y axis label

    for (x = min_x; x <= max_x; x++) {

      /* Check if this (x,y) matches any point */
      int found = 0;
      if (n >= 1 && (int)x1 == x && (int)y1 == y) {
        printf("1 ");
        found = 1;
      } else if (n >= 2 && (int)x2 == x && (int)y2 == y) {
        printf("2 ");
        found = 1;
      } else if (n >= 3 && (int)x3 == x && (int)y3 == y) {
        printf("3 ");
        found = 1;
      } else if (n >= 4 && (int)x4 == x && (int)y4 == y) {
        printf("4 ");
        found = 1;
      }

      if (found == 0) {
        if (x == 0 && y == 0)
          printf("+ "); // Origin
        else if (x == 0)
          printf("| "); // Y-axis
        else if (y == 0)
          printf("- "); // X-axis
        else
          printf(". "); // Empty space
      }
    }
    printf("\n");
  }
  printf("      "); // Spacing for X axis
  for (x = min_x; x <= max_x; x++) {
    printf("--");
  }
  printf("\n");
}

/* * Visualization Function for Circle
 */
void plot_circle_shape(double cx, double cy, double radius) {
  int min_x, max_x, min_y, max_y;
  int x, y;
  int r_int = (int)radius;
  int cx_int = (int)cx;
  int cy_int = (int)cy;

  /* Bounds based on center and radius */
  min_x = cx_int - r_int - 2;
  max_x = cx_int + r_int + 2;
  min_y = cy_int - r_int - 2;
  max_y = cy_int + r_int + 2;

  printf("\n  Graph (Approximate Circle):\n");

  for (y = max_y; y >= min_y; y--) {
    printf("%3d | ", y);
    for (x = min_x; x <= max_x; x++) {

      // Distance from current pixel to center
      double d = sqrt(pow(x - cx, 2) + pow(y - cy, 2));

      // Check if we are on the circumference (with some thickness)
      if (fabs(d - radius) < 0.6) {
        printf("O ");
      } else if (x == cx_int && y == cy_int) {
        printf("C "); // Center
      } else if (x == 0 && y == 0)
        printf("+ ");
      else if (x == 0)
        printf("| ");
      else if (y == 0)
        printf("- ");
      else
        printf(". ");
    }
    printf("\n");
  }
}
