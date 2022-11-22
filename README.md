
>## Node modelimizi oluşturalım.
>
>- Verilen değeri tutması için: `data`
>
>- Bir altındaki node adresi için: `link`
>```cpp
>class Node
>{
>public:
>    int data;
>    Node* link;
>    Node(int data) 
>    {
>        this->data = data;
>        this->link = NULL;
>    };
>};
>```


>## Stack modelimizi oluşturalım.
>
>- Stack in en üstteki node u için: `top`
>
>- Bir altındaki node adresi için: `counter`
>```cpp
>public:
>class Stack {
>    Node* top;
>    int counter;
>```
> - Stack oluşturulurken top NULL dır.
> - Stack oluşturulurken boyut 0 dır. 
> 
>   Constructor da bunları initial edelim.
>```cpp
>    Stack()           
>    {
>        top = NULL;    
>        counter = 0;   
>    }
>``` 
> - Yeni eleman eklerken Stack te bulunan `top` node, yeni eklediğimiz node un `link` ine bağlanır.
> - Stack in `top` nodu artık yeni eklediğimiz node olur.
> - Stack teki eleman sayısını bilmemiz için sayacımızı artırmayı unutmuyoruz.
>```cpp
>    void push(int data)
>    {
>        Node* temp = new Node(data);
>        temp->link = top;
>        top = temp;
>        counter += 1;
>    }
>```
> - Stacklerde sadece en üstteki elemana ulaşabildiğimiz için top eleman silinecek.
> - Geçici bir node oluşturup top node a eşitlenir.
> - top node bir alttaki node a eşitlenir.
> - Geçici node silinerek bellekteki yer temizlenir.
>```CPP
>    void pop()
>    {
>        if(top == NULL)
>        {
>            cout << "Error: The Stack is empty. Stack[pop]" << endl;
>            return;
>        }
>        Node* temp = top;
>        top = top->link;
>        delete(temp);
>        counter -= 1;
>    }
>
>```
> - Stack in sayacını geri döndürür.
>
>```cpp
>    int size()
>    {
>        return counter;
>    }
>```
> - Stack in en üstteki değerini döndürür.
> - Stack boşsa hata mesajı gösterilir.
>```cpp
>    int topValue()
>    {
>        if (top == NULL)
>        {
>            cout << "Error: The stack is empty. [Stack:topValue]" << endl;
>            return NULL;
>        }
>        return top->data;
>    }
>};
>```
>


> ## Stack işlemlerini yapmak için ayrı bir class oluşturalım.
>```cpp
>class StackOperations {
>public:
>```
> - Stack teki tüm elemanları yazdırmak için geçici bir node oluşturulur.
> - Node değeri NULL olana kadar döngüye girilir.
> - Node un değeri yazdırıldıktan sonra node bir sonraki node a eşitlenir.
> - Node null olunca döngüden çıkılır.
>```cpp
>    void display(Stack stack) {
>        if (stack.top == NULL)
>        {
>            cout << "Error: The stack is empty. [StackOperations:display]" << endl;
>            return;
>        }
>        Node* temp;
>        temp = stack.top;
>        cout << "Top";
>        while (temp != NULL)
>        {
>            cout << " -> " << temp->data;
>            temp = temp->link;
>        }
>        cout << " //End" << endl;
>    }
>```
> - Stack i bottom dan top a sıralayalım.
> - Geçici bir Stack oluşturulur ve orjinal Stack e eşitlenir.
> - Tersine çevireceğimiz stack oluşturulur.
> - Stack sayacı 0 olana kadar döngüye girilir.
> - Yeni Stack imize ekleyeceğimiz her eleman orjinal Stack in en üstündeki eleman olacağı için yeni Stack orjinal Stack in ters hali olacaktır.
> - Ekleme yapıldıkça geçici Stack ten eleman çıkartılır.
> - Stack sayacı 0 olunca döngüden çıkılır.
> - Yeni oluşturulan Stack return edilir.
>
>```cpp
>    Stack reversed(Stack stack)
>    {
>
>        Stack temp = stack;
>        Stack reversedStack;
>        while (temp.size() != 0) 
>        {
>            reversedStack.push(temp.topValue());
>            temp.pop();
>        }
>        return reversedStack;
>    }
>```
>
> - Birleştirileck Stack ler parametre ile alınır.
> - Birleştirilmiş olan Stack oluşturulur.
> - Gelen Stackler içerisindeki node ları düzenlemek için geçici node lar oluşturulur.
> - Node ların ikisi de NULL olana kadar döngüye girilir.
> - Node1 NULL ise kıyaslama yapılamayacağı için Node2 Birleştirilmiş Stack e eklenir.
> - Node2 NULL ise kıyaslama yapılamayacağı için Node1 Birleştirilmiş Stack e eklenir.
> - Node lar NULL değilse kıyaslama yapılır. Küçük olan Birleştirilmiş Stack e eklenir ve eklenen Node bir sonraki Node a eşitlenir.
> - Node ların ikisi de NULL olduktan sonra döngüden çıkılır.
>
>```cpp
>    Stack twoToOne(Stack stack1, Stack stack2)
>    {
>        Stack newStack;
>        Node* temp1 = stack1.top;
>        Node* temp2 = stack2.top;
>        while (temp1 != NULL || temp2 != NULL )
>        {
>            if (temp1 == NULL) {
>                newStack.push(temp2->data);
>                temp2 = temp2->link;
>            }
>            else if (temp2 == NULL)
>            {
>                newStack.push(temp1->data);
>                temp1 = temp1->link;
>            }
>            else
>            {
>                if (temp1->data < temp2->data) {
>                    newStack.push(temp1->data);
>                    temp1 = temp1->link;
>                }
>                else if (temp2->data < temp1->data) {
>                    newStack.push(temp2->data);
>                    temp2 = temp2->link;
>                }
>                else
>                {
>                    newStack.push(temp1->data);
>                    temp1 = temp1->link;
>                    newStack.push(temp2->data);
>                    temp2 = temp2->link;
>                }
>            }
>        }
>        return newStack;
>    }
>};
>```

>
> ## main methodumuzda işlemlerimizi uygulamaya geçelim.
>```cpp
>int main()
>{
>    // Stack işlemlerini yapabilmek için stackOperations objemizi oluşturalım.
>    StackOperations stackOperations;
>    // Kıyaslama yapacağımız ilk Stack imizi oluşturalım
>    Stack stack1;
>    // Kıyaslama yapacağımız ikinci Stack imizi oluşturalım
>    Stack stack2;
>    
>    // İlk Stack imize bir kaç eleman ekleyelim.
>    stack1.push(3);
>    stack1.push(2);
>    stack1.push(1);
>    
>    // İkinci Stack imize bir kaç eleman ekleyelim.
>    stack2.push(8);
>    stack2.push(6);
>    stack2.push(5);
>    stack2.push(4);
>    
>    // Oluşturulan Stacklerimizi ekranda görüntüleyelim.
>    stackOperations.display(stack1);
>    stackOperations.display(stack2);
>
>    // Birleştirilmiş Stack imizi oluşturup daha önce oluşturduğumuz Stacklerle işleme sokalım.
>    Stack combinedStack = stackOperations.twoToOne(stack1, stack2);
>    // Birleştirilmiş Stackimizi ekranda görelim.
>    stackOperations.display(combinedStack);
>    // Birleştirilmiş Stackimizi küçükten büyüğe sıralayalım.
>    combinedStack = stackOperations.reversed(combinedStack);
>    // Küçükten büyüğe sıralanmış Stack imizi ekranda görüntüleyelim..
>    stackOperations.display(combinedStack);
>    
>    
>    
>    
>    // Stack1 in eleman sayısını bastıralım.
>    cout << stack1.size() << endl;
>    // Stack1 den eleman çıkartalım.
>    stack1.pop();
>    // Stack1 in son halini ekranda görüntüleyelim.
>    stackOperations.display(stack1);
>    cout << stack1.size() << endl;
>    stack1.pop();
>    stackOperations.display(stack1);
>    cout << stack1.size() << endl;
>    // Stack1 de kalan son elemanı çıkartalım.
>    stack1.pop();
>    
>    stackOperations.display(stack1); // Boş kalan stackimizde görüntüleme yapmak istediğimizde hata mesajı verecektir.
>    
>    stack1.pop(); // Boş olan stackten eleman çıkarmak istediğimizde hata mesajı verecektir.
>    cout << stack1.size() << endl;
>    
>    stack2.pop();
>    stackOperations.display(stack2);
>    cout << stack2.size() << endl;
>
>    return 1;
>}
>```
> 