#include <stdio.h>
#include <stdlib.h>

// Function to compute average
float Compute_Average(float* scores, int num_subjects) {
    float sum = 0;
    for (int i = 0; i < num_subjects; i++) {
        sum += scores[i];
    }
    return (num_subjects > 0) ? (sum / num_subjects) : 0;
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    int* subjects = (int*) malloc(n * sizeof(int)); 
    float** scores = (float**) malloc(n * sizeof(float*));

    int i, j;
    for (i = 0; i < n; i++) {
        printf("Enter number of subjects for student %d: ", i + 1);
        scanf("%d", &subjects[i]);

        scores[i] = (float*) malloc(subjects[i] * sizeof(float));

        for (j = 0; j < subjects[i]; j++) {
            printf("Enter score %d for student %d: ", j + 1, i + 1);
            scanf("%f", &scores[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        float avg = Compute_Average(scores[i], subjects[i]);
        printf("Average for student %d: %.2f\n", i + 1, avg);
    }

    float highest = -1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < subjects[i]; j++) {
            if (scores[i][j] > highest) {
                highest = scores[i][j];
            }
        }
    }

    printf("Overall highest score among all students: %.2f\n", highest);

    for (i = 0; i < n; i++) {
        free(scores[i]);
    }

    free(scores);
    free(subjects);

    return 0;
}
