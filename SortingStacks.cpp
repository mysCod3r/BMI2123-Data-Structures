#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* link;
    Node(int data) 
    {
        this->data = data;
        this->link = NULL;
    };
};


class Stack {
public:
    Node* top;
    int counter;
    Stack()           // Constructor
    {
        top = NULL;   // Stack oluþturulurken top Null dýr.
        counter = 0;     // Stack oluþturulurken boyut 0 dýr
    }

    void push(int data)
    {
        Node* temp = new Node(data);
        temp->link = top;
        top = temp;
        counter += 1;
    }

    void pop()
    {
        if(top == NULL)
        {
            cout << "Error: The Stack is empty. Stack[pop]" << endl;
            return;
        }
        Node* temp = top;
        top = top->link;
        delete(temp);
        counter -= 1;
    }

    int size()
    {
        return counter;
    }

    int topValue()
    {
        if (top == NULL)
        {
            cout << "Error: The stack is empty. [Stack:topValue]" << endl;
            return NULL;
        }
        return top->data;
    }
};

class StackOperations {
public:
    void display(Stack stack) {
        if (stack.top == NULL)
        {
            cout << "Error: The stack is empty. [StackOperations:display]" << endl;
            return;
        }
        Node* temp;
        temp = stack.top;
        cout << "Top";
        while (temp != NULL)
        {
            cout << " -> " << temp->data;
            temp = temp->link;
        }
        cout << " //End" << endl;
    }

    Stack reversed(Stack stack)
    {

        Stack temp = stack;
        Stack reversedStack;
        while (temp.size() != 0) 
        {
            reversedStack.push(temp.topValue());
            temp.pop();
        }
        return reversedStack;
    }

    Stack twoToOne(Stack stack1, Stack stack2)
    {
        Stack newStack;
        Node* temp1 = stack1.top;
        Node* temp2 = stack2.top;
        while (temp1 != NULL || temp2 != NULL )
        {
            if (temp1 == NULL) {
                newStack.push(temp2->data);
                temp2 = temp2->link;
            }
            else if (temp2 == NULL)
            {
                newStack.push(temp1->data);
                temp1 = temp1->link;
            }
            else
            {
                if (temp1->data < temp2->data) {
                    newStack.push(temp1->data);
                    temp1 = temp1->link;
                }
                else if (temp2->data < temp1->data) {
                    newStack.push(temp2->data);
                    temp2 = temp2->link;
                }
                else
                {
                    newStack.push(temp1->data);
                    temp1 = temp1->link;
                    newStack.push(temp2->data);
                    temp2 = temp2->link;
                }
            }
        }
        return newStack;
    }

};



int main()
{
    StackOperations stackOperations;
    Stack stack1;
    Stack stack2;
    
    stack1.push(10);
    stack1.push(5);
    stack1.push(1);
    
    stack2.push(8);
    stack2.push(6);
    stack2.push(4);
    stack2.push(1);
    

    stackOperations.display(stack1);
    stackOperations.display(stack2);

    Stack combinedStack = stackOperations.twoToOne(stack1, stack2);

    stackOperations.display(combinedStack);
    combinedStack = stackOperations.reversed(combinedStack);
    stackOperations.display(combinedStack);

    cout << stack1.size() << endl;
    stack1.pop();
    stackOperations.display(stack1);
    
    cout << stack1.size() << endl;
    stack1.pop();
    stackOperations.display(stack1);

    cout << stack1.size() << endl;
    stack1.pop();
    stackOperations.display(stack1);
    stack1.pop();

    cout << stack1.size() << endl;
    stack2.pop();
    stackOperations.display(stack2);
    cout << stack2.size() << endl;

    return 1;
}
