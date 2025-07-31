#include <stdlib.h>

typedef struct {
    int id;
    char title[100];
    int priority;
    char deadline[30];
} Task;

typedef struct SNode {
    Task task;
    struct SNode *next;
} SNode;

typedef struct DNode {
    Task task;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct StackNode {
    Task task;
    struct StackNode *next;
} StackNode;
StackNode *top = NULL;

typedef struct QNode {
    Task task;
    struct QNode *next;
} QNode;
QNode *front = NULL;
QNode *rear = NULL;


//  Danh sách liên kết đơn (SNode)
//  Thêm vào cuối:
SNode *addTask_Single(SNode *head, Task task) {
    SNode *newNode = (SNode *)malloc(sizeof(SNode));
    newNode->task = task;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    SNode *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return head;
}

// Danh sách liên kết đôi (DNode)
//  Thêm vào cuối:
DNode *addTask_Double(DNode *head, Task task) {
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->task = task;
    newNode->next = newNode->prev = NULL;
    if (!head) return newNode;
    DNode *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Ngăn xếp (StackNode)
// Thêm vào đầu (push):
StackNode *addTask_Stack(StackNode *top, Task task) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->task = task;
    newNode->next = top;
    return newNode;
}

// Hàng đợi (QNode)
// Thêm vào cuối (enqueue):
void addTask_Queue(Task task) {
    QNode *newNode = (QNode *)malloc(sizeof(QNode));
    newNode->task = task;
    newNode->next = NULL;
    if (!rear)
        front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}


//  Xóa theo ID Danh sách liên kết đơn (SNode):
SNode *deleteTaskById_Single(SNode *head, int id) {
    SNode *temp = head, *prev = NULL;
    while (temp && temp->task.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return head;
    if (!prev)
        head = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    return head;
}

//  Xóa theo ID Danh sách liên kết đôi (DNode):
DNode *deleteTaskById_Double(DNode *head, int id) {
    DNode *temp = head;
    while (temp && temp->task.id != id)
        temp = temp->next;
    if (temp == NULL) return head;
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    free(temp);
    return head;
}

//  Xóa theo ID Ngăn xếp (StackNode)
StackNode *deleteTaskById_Stack(StackNode *top, int id) {
    StackNode *temp = top, *prev = NULL;
    while (temp && temp->task.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return top;
    if (prev == NULL)
        top = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    return top;
}

// Xóa theo ID Hàng đợi (QNode)
void deleteTaskById_Queue(int id) {
    QNode *temp = front, *prev = NULL;

    while (temp && temp->task.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return;
    if (!prev) {
        front = temp->next;
        if (!front) rear = NULL;
    } else {
        prev->next = temp->next;
        if (temp == rear)
            rear = prev;
    }
    free(temp);
}


// Theo Cach Mang
typedef struct {
    Task *tasks;
    int top;
    int capacity;
} Stack;

typedef struct {
    Task *tasks;
    int front;
    int rear;
    int capacity;
} Queue;

typedef struct {
    Task *tasks;
    int top;
    int capacity;
} Stack;

typedef struct {
    Task *tasks;
    int front;
    int rear;
    int capacity;
} Queue;

void push(Stack *stack, Task task) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack is full\n");
        return;
    }
    stack->tasks[++stack->top] = task;
}

void enqueue(Queue *queue, Task task) {
    if (queue->rear == queue->capacity - 1) {
        printf("Queue is full\n");
        return;
    }
    queue->tasks[++queue->rear] = task;
}

void deleteTaskById_Stack(Stack *stack, int id) {
    Stack *temp = createStack(stack->capacity);
    int found = 0;
    while (stack->top >= 0) {
        Task t = stack->tasks[stack->top--];
        if (t.id == id) {
            found = 1;
        } else {
            push(temp, t);
        }
    }
    while (temp->top >= 0) {
        push(stack, temp->tasks[temp->top--]);
    }
    free(temp->tasks);
    free(temp);
    if (found)
        printf("Đã xóa ID %d khỏi Stack\n", id);
    else
        printf("Không tìm thấy ID %d trong Stack\n", id);
}
void deleteTaskById_Queue(Queue *queue, int id) {
    int found = 0;
    int newRear = -1;
    Task *newTasks = (Task *)malloc(sizeof(Task) * queue->capacity);

    for (int i = queue->front; i <= queue->rear; i++) {
        if (queue->tasks[i].id != id) {
            newTasks[++newRear] = queue->tasks[i];
        } else {
            found = 1;
        }
    }

    queue->front = 0;
    queue->rear = newRear;
    for (int i = 0; i <= newRear; i++) {
        queue->tasks[i] = newTasks[i];
    }

    free(newTasks);

    if (found)
        printf("Đã xóa ID %d khỏi Queue\n", id);
    else
        printf("Không tìm thấy ID %d trong Queue\n", id);
}

// Sap Xep
void sortStack(Stack *stack) {
    for (int i = 0; i < stack->top; i++) {
        for (int j = i + 1; j <= stack->top; j++) {
            if (stack->tasks[i].priority > stack->tasks[j].priority) {
                Task t = stack->tasks[i];
                stack->tasks[i] = stack->tasks[j];
                stack->tasks[j] = t;
            }
        }
    }
}

void sortQueue(Queue *queue) {
    for (int i = queue->front; i < queue->rear; i++) {
        for (int j = i + 1; j <= queue->rear; j++) {
            if (queue->tasks[i].priority > queue->tasks[j].priority) {
                Task t = queue->tasks[i];
                queue->tasks[i] = queue->tasks[j];
                queue->tasks[j] = t;
            }
        }
    }
}

void sortList(Node *head) {
    for (Node *i = head; i != NULL; i = i->next) {
        for (Node *j = i->next; j != NULL; j = j->next) {
            if (i->task.priority > j->task.priority) {
                Task t = i->task;
                i->task = j->task;
                j->task = t;
            }
        }
    }
}
void sortArray(Call *arr, int size) {
    for (int i = 0; i <= size - 1; i++) {
        for (int j = i + 1; j <= size; j++) {
            if (arr[i].priority > arr[j].priority) {
                Call temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


// tim kiem
void searchStack(Stack *stack, const char *key) {
    for (int i = 0; i <= stack->top; i++) {
        if (strstr(stack->tasks[i].title, key)) {
            printf("Found in Stack: %s\n", stack->tasks[i].title);
        }
    }
}

void searchQueue(Queue *queue, const char *key) {
    for (int i = queue->front; i <= queue->rear; i++) {
        if (strstr(queue->tasks[i].title, key)) {
            printf("Found in Queue: %s\n", queue->tasks[i].title);
        }
    }
}void searchList(Node *head, const char *key) {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        if (strstr(temp->task.title, key)) {
            printf("Found in Linked List: %s\n", temp->task.title);
        }
    }
}
void searchArray(Call *arr, int size, char *title) {
    int found = 0;
    for (int i = 0; i <= size; i++) {
        if (strstr(arr[i].title, title)) {
            printf("Found: %s\n", arr[i].title);
            found = 1;
        }
    }
    if (!found) printf("Not found\n");
}


// ham cay
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}Node;
Node *root=NULL;
Node *createNode(int data) {
    Node *newNode= (Node *)malloc(sizeof(Node));
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

Node *insert(Node *root, int taget) {
    if (root== NULL) {
        return createNode(taget);
    }
    if (taget< root->data) {
        root->left=insert(root->left,taget);
    }else if (taget >root->data) {
        root->right=insert(root->right,taget);
    }else {
        printf("da ton tai");
    }
    return root;
}
int inorder(Node *root) {
    if (root == NULL) {
        printf("Rong");
        return 0;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
// Duyet theo level
void levelOrder(Node* root) {
    if (root == NULL) return;
    Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        Node* current = queue[front++];
        printf("%d ", current->data);
        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
}


int countLeaves(Node *root) {
    if (root== NULL) {
        return 0;
    }
    if (root->left== NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->left)+countLeaves(root->right);
}

int height(Node *root) {
    if (root== NULL) {
        return 0;
    }
    int leftRoot=height(root->left);
    int rightRoot= height(root->right);
    return (leftRoot > rightRoot ? leftRoot : rightRoot) +1;
}