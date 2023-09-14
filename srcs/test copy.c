#include "push_swap.h"

// Fonction d'affichage des opérations
void      print_operations(const char *operation)
{         
          printf("\n%s\n\n", operation);
}

// Fonction pour empiler un élément dans la pile A
void push_to_a(Node_a **stack_a, int data)
{
          Node_a *new_node = (Node_a *)malloc(sizeof(Node_a));
          if (!new_node)
          {
                    // Gestion de l'erreur d'allocation mémoire
                    exit(EXIT_FAILURE);
          }
          new_node->data = data;
          new_node->next = *stack_a;
          *stack_a = new_node;
}

// Fonction pour empiler un élément dans la pile B
void push_to_b(Node_b **stack_b, int data)
{
          Node_b *new_node = (Node_b *)malloc(sizeof(Node_b));
          if (!new_node)
          {
                    // Gestion de l'erreur d'allocation mémoire
                    exit(EXIT_FAILURE);
          }
          new_node->data = data;
          new_node->next = *stack_b;
          *stack_b = new_node;
}


// Fonction pour effectuer l'opération "sa" (swap A)
void      sa(Node_a **stack_a) 
{
          if (*stack_a && (*stack_a)->next) {
                    int temp = (*stack_a)->data;
                    (*stack_a)->data = (*stack_a)->next->data;
                    (*stack_a)->next->data = temp;

                    print_operations("sa");
          }
}

// Fonction pour effectuer l'opération "sb" (swap B)
void      sb(Node_b **stack_b) 
{
          if (*stack_b && (*stack_b)->next) {
                    int temp = (*stack_b)->data;
                    (*stack_b)->data = (*stack_b)->next->data;
                    (*stack_b)->next->data = temp;

                    print_operations("sb");
          }
}

// Fonction pour effectuer l'opération "ss" (swap both)
void      ss(Node_a **stack_a, Node_b **stack_b)
{
          sa(stack_a);
          sb(stack_b);

          print_operations("ss");
}

// Fonction pour effectuer l'opération "pa" (push from B to A)
void      pa(Node_a **stack_a, Node_b **stack_b)
{
          if (*stack_b)
          {
                    int data = (*stack_b)->data;
                    push_to_a(stack_a, data); // Empiler dans A
                    Node_b *temp = *stack_b;
                    *stack_b = (*stack_b)->next;
                    free(temp);
                    print_operations("pa"); // Afficher l'opération "pa"
          }
}

// Fonction pour effectuer l'opération "pb" (push from A to B)
void      pb(Node_a **stack_a, Node_b **stack_b)
{
          if (*stack_a)
          {
                    int data = (*stack_a)->data;
                    push_to_b(stack_b, data); // Empiler dans B
                    Node_a *temp = *stack_a;
                    *stack_a = (*stack_a)->next;
                    free(temp);
                    print_operations("pb"); // Afficher l'opération "pb"
          }
}


// Fonction pour effectuer l'opération "ra" (rotate A)
void      ra(Node_a **stack_a) 
{
          if (*stack_a && (*stack_a)->next) {
                    Node_a *temp = *stack_a;
                    while (temp->next)
                    {
                              temp = temp->next;
                    }
                    temp->next = *stack_a;
                    *stack_a = (*stack_a)->next;
                    temp->next->next = NULL;

                    print_operations("ra");
          }
}

// Fonction pour effectuer l'opération "rb" (rotate B)
void      rb(Node_b **stack_b)
{
          if (*stack_b && (*stack_b)->next)
          {
                    Node_b *temp = *stack_b;
                    while (temp->next)
                    {
                              temp = temp->next;
                    }
                    temp->next = *stack_b;
                    *stack_b = (*stack_b)->next;
                    temp->next->next = NULL;

                    print_operations("rb");
          }
}

// Fonction pour effectuer l'opération "rr" (rotate both)
void      rr(Node_a **stack_a, Node_b **stack_b)
{
          ra(stack_a);
          rb(stack_b);

          print_operations("rr");
}

// Fonction pour effectuer l'opération "rra" (reverse rotate A)
void      rra(Node_a **stack_a) 
{
          if (*stack_a && (*stack_a)->next){
                    Node_a *prev = NULL;
                    Node_a *current = *stack_a;
                    while (current->next)
                    {
                              prev = current;
                              current = current->next;
                    }
                    prev->next = NULL;
                    current->next = *stack_a;
                    *stack_a = current;

                    print_operations("rra");
          }
}

// Fonction pour effectuer l'opération "rrb" (reverse rotate B)
void      rrb(Node_b **stack_b) 
{
          if (*stack_b && (*stack_b)->next) {
                    Node_b *prev = NULL;
                    Node_b *current = *stack_b;
                    while (current->next)
                    {
                              prev = current;
                              current = current->next;
                    }
                    prev->next = NULL;
                    current->next = *stack_b;
                    *stack_b = current;

                    print_operations("rrb");
          }
}

// Fonction pour effectuer l'opération "rrr" (reverse rotate both)
void      rrr(Node_a **stack_a, Node_b **stack_b) 
{
          rra(stack_a);
          rrb(stack_b);
}


// Fonction pour vérifier si la pile A est triée
int is_sorted(Node_a *stack_a) 
{
          Node_a *current = stack_a;
          while (current && current->next) {
                    if (current->data > current->next->data)
                    {
                              return 0; // La pile n'est pas triée
                    }
                    current = current->next;
          }
          return 1; // La pile est triée
}

void print_stacks(Node_a *stack_a, Node_b *stack_b)
{
    Node_a *current_a = stack_a;
    Node_b *current_b = stack_b;

    while (current_a || current_b)
    {
        if (current_a)
        {
            printf("%-10d", current_a->data);
            current_a = current_a->next;
        }
        else
        {
            printf("%-10s", ""); // Espacement pour aligner avec la pile B
        }

        if (current_b)
        {
            printf("%-10d", current_b->data);
            current_b = current_b->next;
        }

        printf("\n");
    }
}


// Fonction pour trier la pile A en utilisant l'algorithme
void push_swap_algorithm(Node_a **stack_a, Node_b **stack_b) {
    int max = INT_MIN;
    int min = INT_MAX;

    // Trouver le maximum et le minimum dans la pile A
    Node_a *current = *stack_a;
    Node_b *currentb = *stack_b;

    while (current) {
        if (current->data > max) {
            max = current->data;
        }
        if (current->data < min) {
            min = current->data;
        }
        current = current->next;
    }

    // Commencer à trier la pile A
    while (*stack_a) {
        int cheapest = INT_MAX;
        Node_a *cheapest_node = NULL;
        Node_a *temp = *stack_a; // Utilisez une variable temporaire

        while (temp) {
            int operations = 0;

            // Calculer le nombre d'opérations nécessaires pour déplacer l'élément vers la pile B
            if (temp->data == max || temp->data == min) {
                operations = 2;
            } else {
                int rotations_a = 0;
                int rotations_b = 0;

                // Calculer le nombre de rotations nécessaires pour déplacer l'élément vers le haut de la pile B
                Node_a *temp2 = *stack_a; // Utilisez une autre variable temporaire pour les rotations
                while (temp2 && temp2->data != max) {
                    temp2 = temp2->next;
                    rotations_a++;
                }

                temp2 = *stack_a; // Réinitialisez temp2
                while (temp2 && temp2->data != min) {
                    temp2 = temp2->next;
                    rotations_b++;
                }

                operations = rotations_a + rotations_b + 1; // Nombre total d'opérations
            }

            if (operations < cheapest) {
                cheapest = operations;
                cheapest_node = temp;
            }

            temp = temp->next;
        }

          if (cheapest_node) {
                    // Effectuer les rotations nécessaires pour déplacer l'élément vers le haut de la pile B
                    int rotations_a = 0;
                    int rotations_b = 0;

                    current = *stack_a;
                    while (current != NULL && current != cheapest_node) {
                              current = current->next;
                              rotations_a++;
                    }

                    currentb = *stack_b;
                    while (currentb != NULL && current->data != min) {
                              currentb = currentb->next;
                              rotations_b++;
                    }

                    int stack_a_size = 0;
                    current = *stack_a;
                    while (current != NULL) {
                              current = current->next;
                              stack_a_size++;
                    }

                    int stack_b_size = 0;
                    currentb = *stack_b;
                    while (currentb != NULL) {
                              currentb= currentb->next;
                              stack_b_size++;
                    }

                    if (rotations_a <= stack_a_size / 2) {
                              // Faites "ra" rotations si "ra" est dans la première moitié de la pile A
                              while (rotations_a > 0) {
                                        ra(stack_a);
                                        rotations_a--;
                              }
                    } else {
                                        rra(stack_a);
                                        rotations_a--;
                              
                    }

                              
                    if (rotations_b <= stack_b_size / 2) {
                              // Faites "rb" rotations si "rb" est dans la première moitié de la pile B
                              while (rotations_b > 0) {
                                        rb(stack_b);
                                        rotations_b--;
                              }
                    } else {
                                        rrb(stack_b);
                                        rotations_b--;
                              
                    }

                    pb(stack_a, stack_b);

                    print_stacks(*stack_a, *stack_b);
          }

    }

    // Toutes les valeurs sont triées dans la pile B, il suffit de les ramener dans la pile A

}


int       ft_checktwins(Node_a *list_a, int value) {

          Node_a *current = list_a;
          while (current != NULL) {
                    if (current->data == value) {
                              return 0;
                    }
                    current = current->next;
          }

          return (1);
}

Node_a      *insertNodeA(Node_a *head, int value) {

          Node_a *node_a = malloc(sizeof(Node_a));
          if (node_a == NULL) {
                    exit(1);
          }

          node_a->data = value;
          node_a->next = NULL;

          if (head == NULL) {
                    return node_a;
          }

          Node_a *current = head;
          while (current->next != NULL) {
                    current = current->next;
          }
          current->next = node_a;

          return (head);
}

int main(int argc, char **argv)
{
          Node_a *list_a = NULL;
          Node_b *list_b = NULL;  

          int i = 1;
          while (i < argc) {
                    char **temp = ft_split(argv[i], ' ');
                    int j = 0;
                    long result = ft_atoi(temp[j]);
                    while (temp[j] != NULL) {
                              if (result == 0) {
                                        ft_error(2);
                              } else {
                                        if (ft_checktwins(list_a, result) == 1) {
                                                  list_a = insertNodeA(list_a, result);
                                        }
                                        j++;
                              }
                    }
                    i++;
          }


          // Appelez la fonction de tri avec vos piles A et B
          push_swap_algorithm(&list_a, &list_b);


          // Libérez la mémoire

          return (0);
}
