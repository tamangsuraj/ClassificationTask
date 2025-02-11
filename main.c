

#include <stdio.h>
#include <stdlib.h>

// Initializing
double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

// Function to calculate sums
double calculate_sum_x(double x[], int n){
    double sum = 0;
    for (int i = 0; i < n; i++){
        sum += x[i];
    }
    return sum;
}

double calculate_sum_y(double y[], int n){
    double sum = 0;
    for (int i = 0; i < n; i++){
        sum += y[i];
    }
    return sum;
}

double calculate_sum_xy(double x[], double y[], int n){
    double sum = 0;
    for (int i = 0; i < n; i++){
        sum += x[i] * y[i];
    }
    return sum;
}

double calculate_sum_xx(double x[], int n){
    double sum = 0;
    for (int i = 0; i < n; i++){
        sum += x[i] * x[i];
    }
    return sum;
}

int main() {
    char *filenames[] = {"datasetLR1.txt", "datasetLR2.txt", "datasetLR3.txt", "datasetLR4.txt"};
    double x[600], y[600]; 
    int n = 0; // Number of data points

    printf("\nReading coordinates from files..\n");
    
    // Read coordinates from all files
    for (int f = 0; f < 4; f++) {
        FILE *file = fopen(filenames[f], "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }

        while (fscanf(file, "%lf, %lf", &x[n], &y[n]) == 2) {
            n++;
            if (n >= 600) {
                printf("Warning: Maximum points limit reached.\n");
                break;
            }
        }
        fclose(file);
    }

    if (n <= 2) {
        printf("Error: Not enough data points.\n");
        return 1;
    }

    // Calculate sums
    sum_x = calculate_sum_x(x, n);
    sum_y = calculate_sum_y(y, n);
    sum_xy = calculate_sum_xy(x, y, n);
    sum_xx = calculate_sum_xx(x, n);

    // Calculate denominator (n * sum_xx - sum_x * sum_x)
    double denominator = n * sum_xx - sum_x * sum_x;
    if (denominator == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return 1;
    }

    // Calculate A and B for the linear regression equation
    double A = (sum_y * sum_xx - sum_x * sum_xy) / denominator;
    double B = (n * sum_xy - sum_x * sum_y) / denominator;

    // Output the linear regression equation
    printf("\nLinear Regression Equation:\n");
    printf("y = %.2lfx + %.2lf\n", B, A);

    // Take the user input value to calculate y
    double input_x, output_y;
    printf("\nEnter value of x to calculate y: ");
    scanf("%lf", &input_x);

    // Calculate y using the regression equation
    output_y = B * input_x + A;
    printf("For x = %.2lf, y = %.2lf\n", input_x, output_y);

    return 0;
}
