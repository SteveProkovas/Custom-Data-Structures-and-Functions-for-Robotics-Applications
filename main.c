#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define maximum length for data type string
#define MAX_DATA_TYPE_LENGTH 20

// Custom data structure for vectors (example)
typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

// Custom data structure for matrices (example)
typedef struct {
    float elements[4][4]; // Example for a 4x4 matrix
} Matrix4x4;

// Custom data structure for complex sensor readings (example)
typedef struct {
    float value1;
    float value2;
    // Add more fields as needed to represent complex sensor readings
} SensorData;

// Definition of the node structure
typedef struct node {
    char* name; // Changed to use dynamic memory allocation for variable names
    char data_type[MAX_DATA_TYPE_LENGTH];
    union {
        int integer_value;
        float float_value;
        bool boolean_value;
        Vector3D vector_value; // Example for vector data type
        Matrix4x4 matrix_value; // Example for matrix data type
        SensorData sensor_data; // Example for complex sensor readings data type
        // Add additional fields for other custom data structures
    } value;
    struct node* next;
} node;

// Definition of the pointer to a node
typedef node* node_pointer;

// Global variable for type checking (1 for int, 2 for float)
int type_flag;

// Display the contents of a list on the screen
void show_list(node_pointer list) {
    if (list == NULL) {
        printf("List is empty\n");
        return;
    }

    printf("\nList:\n====================\n");

    // Print each node in the list
    while (list != NULL) {
        printf("Name: %s, Data Type: %s\n", list->name, list->data_type);

        // Print value based on data type
        if (strcmp(list->data_type, "int") == 0)
            printf("Value: %d\n", list->value.integer_value);
        else if (strcmp(list->data_type, "float") == 0)
            printf("Value: %.2f\n", list->value.float_value);
        else if (strcmp(list->data_type, "bool") == 0)
            printf("Value: %s\n", list->value.boolean_value ? "true" : "false");
        else if (strcmp(list->data_type, "vector") == 0)
            printf("Value: (%.2f, %.2f, %.2f)\n", list->value.vector_value.x, list->value.vector_value.y, list->value.vector_value.z);
        else if (strcmp(list->data_type, "matrix") == 0)
            printf("Value: [matrix]\n"); // Print matrix value in a suitable format
        else if (strcmp(list->data_type, "sensor_data") == 0)
            printf("Value: [sensor data]\n"); // Print sensor data value in a suitable format

        // Add cases for other data types as needed

        list = list->next;
    }

    printf("====================\n\n");
}

// Modify other functions as needed to accommodate changes in data types and operations

int main() {
    // Create a list
    node_pointer list = NULL;

    // Add variables with different data types
    if (!add_variable(&list, "sensor_reading", "float") ||
        !add_variable(&list, "motor_speed", "int") ||
        !add_variable(&list, "robot_position_x", "float") ||
        !add_variable(&list, "robot_position_y", "float") ||
        !add_variable(&list, "robot_orientation", "float") ||
        !add_variable(&list, "is_obstacle_detected", "bool") ||
        !add_variable(&list, "target_position", "vector") ||
        !add_variable(&list, "transformation_matrix", "matrix") ||
        !add_variable(&list, "sensor_data_reading", "sensor_data")) {
        // Handle failure to add variables
        return 1;
    }

    // Display the list
    show_list(list);

    // Modify the code to interact with robotics frameworks, read sensor data, etc.

    // Clean up by deleting the list
    while (list != NULL) {
        node_pointer temp = list;
        list = list->next;
        free(temp->name);
        free(temp);
    }

    return 0;
}

