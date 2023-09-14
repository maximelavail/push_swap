#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int capacity;
} t_stack;

#define INITIAL_CAPACITY 100

void initialize_stack(t_stack *stack) {
    stack->array = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
}

void push(t_stack *stack, int value) {
    if (stack->size == stack->capacity) {
        // Si la capacité est épuisée, doublez-la
        stack->capacity *= 2;
        stack->array = (int *)realloc(stack->array, stack->capacity * sizeof(int));
    }
    stack->array[stack->size] = value;
    stack->size++;
}

int is_empty(t_stack *stack) {
    return stack->size == 0;
}

void swap(t_stack *stack) {
    if (stack->size >= 2) {
        int temp = stack->array[stack->size - 1];
        stack->array[stack->size - 1] = stack->array[stack->size - 2];
        stack->array[stack->size - 2] = temp;
    }
}

void rotate(t_stack *stack) {
    if (stack->size >= 2) {
        int temp = stack->array[0];
        for (int i = 0; i < stack->size - 1; i++) {
            stack->array[i] = stack->array[i + 1];
        }
        stack->array[stack->size - 1] = temp;
    }
}

void reverse_rotate(t_stack *stack) {
    if (stack->size >= 2) {
        int temp = stack->array[stack->size - 1];
        for (int i = stack->size - 1; i > 0; i--) {
            stack->array[i] = stack->array[i - 1];
        }
        stack->array[0] = temp;
    }
}

// Fonction pour afficher une opération
void print_operation(const char *operation) {
    printf("%s\n", operation);
}

// Fonction pour effectuer un swap entre les piles A et B
void swap_ab(t_stack *stack_a, t_stack *stack_b) {
    swap(stack_a);
    swap(stack_b);
    print_operation("swap a");
    print_operation("swap b");
}

// Fonction pour effectuer un rotate entre les piles A et B
void rotate_ab(t_stack *stack_a, t_stack *stack_b) {
    rotate(stack_a);
    rotate(stack_b);
    print_operation("rotate a");
    print_operation("rotate b");
}

// Fonction pour effectuer un reverse_rotate entre les piles A et B
void reverse_rotate_ab(t_stack *stack_a, t_stack *stack_b) {
    reverse_rotate(stack_a);
    reverse_rotate(stack_b);
    print_operation("reverse_rotate a");
    print_operation("reverse_rotate b");
}

// Fonction pour effectuer un push de A vers B
void push_ab(t_stack *stack_a, t_stack *stack_b) {
    if (!is_empty(stack_a)) {
        push(stack_b, stack_a->array[stack_a->size - 1]);
        stack_a->size--;
        print_operation("push a");
        print_operation("push b");
    }
}

void quick_sort(t_stack *stack_a, t_stack *stack_b) {
    // Copie temporaire de la pile A
    t_stack temp_a;
    initialize_stack(&temp_a);
    while (!is_empty(stack_a)) {
        push(&temp_a, stack_a->array[stack_a->size - 1]);
        stack_a->size--;
    }

    while (!is_empty(&temp_a)) {
        int pivot = temp_a.array[0]; // Choisissez le premier élément comme pivot

        // Initialisation des piles temporaires
        t_stack smaller, larger;
        initialize_stack(&smaller);
        initialize_stack(&larger);

        // Partition des éléments de la pile temporaire en fonction du pivot
        int i = 1;
        while (i < temp_a.size) {
            if (temp_a.array[i] < pivot) {
                push(&smaller, temp_a.array[i]);
            } else {
                push(&larger, temp_a.array[i]);
            }
            i++;
        }

        // Triez les piles plus petites et plus grandes (utilisez stack_b comme pile temporaire)
        quick_sort(&smaller, stack_b);
        quick_sort(&larger, stack_b);

        // Videz la pile temporaire dans la pile A
        while (!is_empty(stack_a)) {
            push(stack_b, stack_a->array[stack_a->size - 1]);
            stack_a->size--;
        }

        // Fusionnez les piles triées dans la pile A
        while (!is_empty(&smaller)) {
            push(stack_a, smaller.array[smaller.size - 1]);
            smaller.size--;
        }

        // Placez le pivot en haut de la pile A
        push(stack_a, pivot);

        while (!is_empty(&larger)) {
            push(stack_a, larger.array[larger.size - 1]);
            larger.size--;
        }
    }

    // Libérez la mémoire utilisée par la pile temporaire
    free(temp_a.array);
}

// Fonction pour libérer la mémoire de la pile
void free_stack(t_stack *stack) {
    free(stack->array);
    stack->size = 0;
    stack->capacity = 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Utilisation : %s <éléments à trier>\n", argv[0]);
        return 1;
    }

    t_stack stack_a, stack_b;
    initialize_stack(&stack_a);
    initialize_stack(&stack_b);

    // Remplissez la pile A avec les éléments passés en ligne de commande
    int i = 1;
    while (i < argc) {
        int element = atoi(argv[i]);
        push(&stack_a, element);
        i++;
    }

    // Triez la pile A en utilisant quick_sort
    quick_sort(&stack_a, &stack_b);

    // Affichez les éléments triés dans la pile A (la pile B devrait être vide)
    printf("Elements triés dans la pile A:\n");
    while (!is_empty(&stack_a)) {
        printf("%d\n", stack_a.array[stack_a.size - 1]);
        stack_a.size--;
    }

    // Libérez la mémoire utilisée par les piles
    free_stack(&stack_a);
    free_stack(&stack_b);

    return 0;
}
