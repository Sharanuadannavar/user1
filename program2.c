#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    float velocity;
    float angle;
    float timeoflight;
    float maxheight;
    float range;
} Proj;

// Convert degrees to radians
float degtoRad(float degree) {
    return degree * M_PI / 180.0;
}

// Input function
void inputdata(Proj* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("Experiment %d:\n", i + 1);
        printf("Enter velocity (m/s): ");
        scanf("%f", &(arr[i].velocity));
        printf("Enter angle (degrees): ");
        scanf("%f", &(arr[i].angle));
        printf("Enter time of flight (s): ");
        scanf("%f", &(arr[i].timeoflight));
    }
}

// Compute max height and range
void computeresults(Proj* arr, int n) {
    const float g = 9.8f;
    for (int i = 0; i < n; i++) {
        float anglerad = degtoRad(arr[i].angle);
        float v = arr[i].velocity;
        float sinangle = sin(anglerad);
        float sin2angle = sin(2 * anglerad);
        arr[i].maxheight = (v * v * sinangle * sinangle) / (2 * g);
        arr[i].range = (v * v * sin2angle) / g;
    }
}

// Display results
void displaydata(const Proj* arr, int n) {
    printf("\n%-15s %-15s %-15s %-15s %-15s\n", "Velocity (m/s)", "Angle (deg)", "Time (s)", "MaxHeight (m)", "Range (m)");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15.2f %-15.2f %-15.2f %-15.2f %-15.2f\n",
               arr[i].velocity, arr[i].angle, arr[i].timeoflight, arr[i].maxheight, arr[i].range);
    }
}

// Find experiment with max range
int findmaxrange(const Proj* arr, int n) {
    int maxindex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].range > arr[maxindex].range) {
            maxindex = i;
        }
    }
    return maxindex;
}

// Compare max height between two experiments
void comparemaxheight(const Proj* a, const Proj* b) {
    printf("\nComparing max height between two experiments:\n");
    printf("Experiment 1 Max Height = %.2f\n", a->maxheight);
    printf("Experiment 2 Max Height = %.2f\n", b->maxheight);

    if (fabs(a->maxheight - b->maxheight) < 1e-6) {
        printf("Both experiments have the same max height.\n");
    } else {
        printf("The experiments have different max heights.\n");
    }
}

// Main function
int main() {
    int n;
    printf("Enter number of experiments: ");
    scanf("%d", &n);

    Proj* experiments = (Proj*)malloc(n * sizeof(Proj));
    if (!experiments) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    inputdata(experiments, n);
    computeresults(experiments, n);
    displaydata(experiments, n);

    int maxindex = findmaxrange(experiments, n);
    printf("\nExperiment %d has the maximum range of %.2f meters.\n", maxindex + 1, experiments[maxindex].range);

    if (n >= 2) {
        Proj copyoffirst = experiments[0];
        comparemaxheight(&copyoffirst, &experiments[1]);
    }

    free(experiments);
    return 0 ;
};
