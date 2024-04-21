#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* initializeINTAL() {
    char* intal = (char*)malloc(1001 * sizeof(char)); // Allocate memory for 1000 characters + 1 for null terminator
    if (intal == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    
    for (int i = 0; i < 1000; i++) {
        intal[i] = '0'; // Initialize each character to '0'
    }
    intal[1000] = '\0'; // Null-terminate the string
    
    return intal;
}

int compareINTAL(const char* intal_a, const char* intal_b) {
    // Compare lengths
    int len_a = strlen(intal_a);
    int len_b = strlen(intal_b);
    if (len_a > len_b) {
        return 1;
    } else if (len_a < len_b) {
        return -1;
    }
    
    // Compare individual digits
    for (int i = len_a - 1; i >= 0; i--) {
        if (intal_a[i] > intal_b[i]) {
            return 1;
        } else if (intal_a[i] < intal_b[i]) {
            return -1;
        }
    }
    
    // All characters are equal
    return 0;
}

char* addINTAL(const char* intal_a, const char* intal_b) {
    int len_a = strlen(intal_a);
    int len_b = strlen(intal_b);
    int max_len = len_a > len_b ? len_a : len_b;
    char* result = (char*)malloc((max_len + 2) * sizeof(char)); // Allocate memory for sum + 1 for possible carry + 1 for null terminator
    if (result == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    
    int carry = 0;
    int k = 0;
    for (int i = len_a - 1, j = len_b - 1; i >= 0 || j >= 0; i--, j--) {
        int sum = carry;
        if (i >= 0) {
            sum += intal_a[i] - '0';
        }
        if (j >= 0) {
            sum += intal_b[j] - '0';
        }
        result[k++] = '0' + sum % 10;
        carry = sum / 10;
    }
    if (carry) {
        result[k++] = '0' + carry;
    }
    result[k] = '\0';
    
    // Reverse the result string
    int left = 0, right = k - 1;
    while (left < right) {
        char temp = result[left];
        result[left++] = result[right];
        result[right--] = temp;
    }
    
    return result;
}

char* subtractINTAL(const char* intal_a, const char* intal_b) {
    if (compareINTAL(intal_a, intal_b) < 0) {
        // Swap intal_a and intal_b if intal_a is smaller
        const char* temp = intal_a;
        intal_a = intal_b;
        intal_b = temp;
    }
    
    int len_a = strlen(intal_a);
    int len_b = strlen(intal_b);
    int max_len = len_a;
    char* result = (char*)malloc((max_len + 1) * sizeof(char)); // Allocate memory for difference + 1 for null terminator
    if (result == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    result[max_len] = '\0';
    
    int borrow = 0;
    int k = max_len - 1;
    for (int i = len_a - 1, j = len_b - 1; i >= 0; i--, j--) {
        int subtrahend = intal_a[i] - '0';
        if (j >= 0) {
            subtrahend -= (intal_b[j] - '0');
        }
        subtrahend -= borrow;
        if (subtrahend < 0) {
            subtrahend += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[k--] = '0' + subtrahend;
    }
    
    // Remove preceding zeros
    while (result[0] == '0' && result[1] != '\0') {
        for (int i = 0; i < max_len; i++) {
            result[i] = result[i + 1];
        }
        result[max_len - 1] = '\0';
    }
    
    return result;
}

char* multiplyINTAL(const char* intal_a, const char* intal_b) {
    if (strcmp(intal_a, "0") == 0 || strcmp(intal_b, "0") == 0) {
        char* zero = (char*)malloc(2 * sizeof(char)); // Allocate memory for "0" + null terminator
        if (zero == NULL) {
            // Handle memory allocation failure
            return NULL;
        }
        strcpy(zero, "0");
        return zero;
    } else if (strcmp(intal_a, "1") == 0) {
        return strdup(intal_b); // Return a duplicate of intal_b
    } else if (strcmp(intal_b, "1") == 0) {
        return strdup(intal_a); // Return a duplicate of intal_a
    }
    
    int len_a = strlen(intal_a);
    int len_b = strlen(intal_b);
    int result_len = len_a + len_b;
    char* result = (char*)calloc(result_len + 1, sizeof(char)); // Allocate memory for product + 1 for null terminator
    if (result == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    
    for (int i = len_b - 1; i >= 0; i--) {
        int carry = 0;
        int ptr1 = 0;
        int ptr2 = result_len - 1 - (len_b - 1 - i);
        for (int j = len_a - 1; j >= 0; j--) {
            int product = (intal_b[i] - '0') * (intal_a[j] - '0') + (result[ptr2] - '0') + carry;
            result[ptr2] = '0' + product % 10;
            carry = product / 10;
            ptr2--;
        }
        if (carry) {
            result[ptr2] = '0' + carry;
        }
    }
    
    // Remove preceding zeros
    while (result[0] == '0' && result[1] != '\0') {
        for (int i = 0; i < result_len; i++) {
            result[i] = result[i + 1];
        }
        result[result_len - 1] = '\0';
    }
    
    return result;
}

char* FibonacciINTAL(unsigned int n) {
    char* intal_a = initializeINTAL();
    if (n == 0) {
        return intal_a;
    }
    
    char* intal_b = (char*)malloc(2 * sizeof(char)); // Allocate memory for "1" + null terminator
    if (intal_b == NULL) {
        // Handle memory allocation failure
        free(intal_a);
        return NULL;
    }
    strcpy(intal_b, "1");
    
    if (n == 1) {
        free(intal_a);
        return intal_b;
    }
    
    char* temp;
    for (unsigned int i = 2; i <= n; i++) {
        temp = addINTAL(intal_a, intal_b);
        free(intal_a);
        intal_a = intal_b;
        intal_b = temp;
    }
    free(intal_a);
    return intal_b;
}

char* factorialINTAL(unsigned int n) {
    char* intal_result = initializeINTAL();
    if (n == 0 || n == 1) {
        return intal_result;
    }
    
    char* intal_num = (char*)malloc(2 * sizeof(char)); // Allocate memory for "1" + null terminator
    if (intal_num == NULL) {
        // Handle memory allocation failure
        free(intal_result);
        return NULL;
    }
    strcpy(intal_num, "1");
    
    char* temp;
    for (unsigned int i = 2; i <= n; i++) {
        temp = addINTAL(intal_num, "1");
        free(intal_num);
        intal_num = temp;
        temp = multiplyINTAL(intal_num, intal_result);
        free(intal_result);
        intal_result = temp;
    }
    free(intal_num);
    return intal_result;
}

int main() {
    int choice;
    unsigned int n;
    char intal1[1001], intal2[1001];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Compare INTALs\n");
        printf("2. Add INTALs\n");
        printf("3. Subtract INTALs\n");
        printf("4. Multiply INTALs\n");
        printf("5. Fibonacci INTAL\n");
        printf("6. Factorial INTAL\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the first INTAL: ");
                scanf("%s", intal1);
                printf("Enter the second INTAL: ");
                scanf("%s", intal2);
                switch (compareINTAL(intal1, intal2)) {
                    case 1:
                        printf("First INTAL is greater.\n");
                        break;
                    case -1:
                        printf("Second INTAL is greater.\n");
                        break;
                    case 0:
                        printf("Both INTALs are equal.\n");
                        break;
                }
                break;
            case 2:
                printf("Enter the first INTAL: ");
                scanf("%s", intal1);
                printf("Enter the second INTAL: ");
                scanf("%s", intal2);
                printf("Sum: %s\n", addINTAL(intal1, intal2));
                break;
            case 3:
                printf("Enter the first INTAL: ");
                scanf("%s", intal1);
                printf("Enter the second INTAL: ");
                scanf("%s", intal2);
                printf("Difference: %s\n", subtractINTAL(intal1, intal2));
                break;
            case 4:
                printf("Enter the first INTAL: ");
                scanf("%s", intal1);
                printf("Enter the second INTAL: ");
                scanf("%s", intal2);
                printf("Product: %s\n", multiplyINTAL(intal1, intal2));
                break;
            case 5:
                printf("Enter the value of n for Fibonacci INTAL: ");
                scanf("%u", &n);
                printf("Fibonacci INTAL at position %u: %s\n", n, FibonacciINTAL(n));
                break;
            case 6:
                printf("Enter the value of n for factorial INTAL: ");
                scanf("%u", &n);
                printf("Factorial INTAL of %u: %s\n", n, factorialINTAL(n));
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 7.\n");
                break;
        }
    }
    
    return 0;
}
