## Çalışan Uygulama Test Görüntüleri
<table>
  <tr>
    <td>Ekleme</td>
    <td>Silme</td>
    <td>Güncelleme</td>
  </tr>
  
  <tr>
    <td><img src="https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/insert_normal.gif?raw=true"></td>
    <td><img src="https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/delete_normal.gif?raw=true"></td>
    <td><img src="https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/update.gif?raw=true"></td>
  </tr>

  <tr>
    <td>Var Olan Değeri Ekleme</td>
    <td>Olmayan Değeri Silme</td>
    <td>Normal Listeleme - İki Değer Arasını Listeleme</td>
  </tr>
  
  <tr>
    <td><img src="https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/insert_already_have.gif?raw=true"></td>
    <td><img src="https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/delete_doesnt_exist.gif?raw=true"></td>
    <td><img src="https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/list.gif?raw=true"></td>
  </tr>
  
  
</table>

## Rotasyonlar
Sol-Sol Durumu // Sağa Döndürme |
:-------------------------:|
![](https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/left-left_case.gif?raw=true)

Sol-Sağ Durumu // sola Döndürme + Sağa Döndürme |
:-------------------------:|
![](https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/left-right_case.gif?raw=true)

## Silme İşlemi
Sol-Sol Durumu // Sağa Döndürme |
:-------------------------:|
![](https://github.com/mysCod3r/BMI2123-Assigments/blob/master/cpp-avl-tree-dictionary/images/remove.gif?raw=true)




## Utility classı proje boyunca ihtiyacımız olan ek işlevleri yapmak amacıyla kullanılacaktır.
- Bu projede kullanıcıdan girdi alınan bir projedir.
- Ekleme ve silme işlemlerinde birebir aynı kelime girme zorunluluğu olduğu için kullanıcının hata yapma ihtimalini minimuma indirgemek amacıyla girilen string ifadelerin başından ve sonundan (varsa)boşlukları temizleyip tüm metni büyük harfe çevirmektedir.
- Bu sayade kullanıcı girdilerini ne şekilde yazarsa yazsın programa BÜYÜK HARF olarak kaydedilecektir.

```cpp
class Utility {
public:
    string toUpper(string str) {
        const char* typeOfWhitespaces = " \t\n\r\f\v";
        str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
        str.erase(0, str.find_first_not_of(typeOfWhitespaces));
        transform(str.begin(), str.end(), str.begin(), [](char const& c) {
            return std::toupper(c);
            });
        return str;
    }
};
```

## AVLNode modelimizi oluşturalım.
- Kelime için `key`
- Anlamı için `value`
- Sol alt için `left`
- Sağ alt için `right`
- Yükseklik için `height`
```cpp
class AVLNode{
public:
    string key;
    string value;
    AVLNode* left;
    AVLNode* right;    
    int height;
    AVLNode(string key, string value) {
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};
```

## AVLTree
- Ağaç objemizde ana fonksiyonlar `private` olarak yazılmış olup yardımcı fonksiyonlar `public` yazılmıştır.
- Yardımcı fonksiyonlarda sadece `kelime` ve `anlam` değerleri parametre olarak alınıp ana fonksiyonlara iletilmektedir.
- Ağaç node yapısı kullanılarak yazıldığı için `main` fonksiyonunda `node` modelini oluşturmak ve sürekli oluşturulan `node` u güncellemek gereksiz görüldüğü için program bu şekilde yazılmıştır. 

```cpp
class AVLTree {
    AVLNode* root = NULL;
    int count = 0;
    Utility u;

    int getHeight(AVLNode* node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    int getBalance(AVLNode* node) {
        if (node == NULL)
            return 0;
        return (getHeight(node->left) - getHeight(node->right));
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        // SOL EN ALTTAKİ YAPRAĞI BULMAK İÇİN:
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    AVLNode* insertNode(AVLNode* node, string key, string value) {
        if (node == NULL) {
            count = count + 1;
            cout << "Kelime başarıyla eklendi. " << endl;
            return new AVLNode(key, value);
        }
        if (key < node->key) {
            node->left = insertNode(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insertNode(node->right, key, value);
        }
        else {
            cout << "Bu değer zaten ağaçta mevcut. Anlamını güncellemek için [Güncelleme] fonksiyonunu çağırınız." << endl;
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        int balanceFactor = getBalance(node);
        // Left Left  Case // Right rotation 
        if (balanceFactor == 2 && getBalance(node->left) >= 0)
            return rightRotate(node);
        // Left Right Case // LR rotation 
        else if (balanceFactor == 2 && getBalance(node->left) == -1) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Right Case // Left rotation	
        else if (balanceFactor == -2 && getBalance(node->right) <= -0)
            return leftRotate(node);
        // Right Left Case // RL rotation 
        else if (balanceFactor == -2 && getBalance(node->right) == 1) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* deleteNode(AVLNode* node, string key) {
        if (node == NULL) {
            cout << "Silinmek istenen kelime ağaçta bulunamadı." << endl;
            return NULL;
        }

        // Silinmek istenen key current key den küçükse sola doğru ilerler
        else if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        // Silinmek istenen key current key den büyükse sağa doğru ilerler
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        // Silinecek key ağaçta bulunmuşsa:
        else {
            // Tek yapraklı ya da yapraksız case: 
            if (node->left == NULL) {
                AVLNode* temp = node->right;
                delete node;
                count -= 1;
                cout << "Kelime başarıyla silindi." << endl;
                return temp;
            }
            else if (node->right == NULL) {
                AVLNode* temp = node->left;
                delete node;
                count -= 1;
                cout << "Kelime başarıyla silindi." << endl;
                return temp;
            }
            else {
                // İki yapraklı case:
                // Silinecek yaprağın sağ alt ağacını al
                AVLNode* temp = minValueNode(node->right);
                // Bulunan ağaca taşı.
                node->key = temp->key;
                // Yer değiştirme işleminden sonra sil.
                node->right = deleteNode(node->right, temp->key);
            }
        }

        int balanceFactor = getBalance(node);
        // Left Left  Case // Right rotation 
        if (balanceFactor == 2 && getBalance(node->left) >= 0)
            return rightRotate(node);
        // Left Right Case // LR rotation 
        else if (balanceFactor == 2 && getBalance(node->left) == -1) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Right Case // Left rotation	
        else if (balanceFactor == -2 && getBalance(node->right) <= -0)
            return leftRotate(node);
        // Right Left Case // RL rotation 
        else if (balanceFactor == -2 && getBalance(node->right) == 1) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* searchNode(AVLNode* node, string key) {
        if (node == NULL)
            return NULL;
        else if (node->key == key)
            return node;
        else if (node->key > key)
            return searchNode(node->left, key);
        else
            return searchNode(node->right, key);
    }

    void inOrder(AVLNode* node) {
        if (node == NULL)
            return;

        inOrder(node->left);
        cout << node->key << " - ";
        inOrder(node->right);
    }
    
    void inOrderWithMeans(AVLNode* node) {
        if (node == NULL)
            return;

        inOrderWithMeans(node->left);
        cout << node->key << " : " << node->value << endl;
        inOrderWithMeans(node->right);
    }

    void searchBetween(AVLNode* node, string key1, string key2) {
        if (node == NULL)
            return;
        
        searchBetween(node->left, key1, key2);
        if ((node->key >= key1 && node->key <= key2) || (node->key <= key1 && node->key >= key2)) {
            cout << node->key << " : " << node->value << endl;
        }
        searchBetween(node->right, key1, key2);
    }

public:
    void insert(string key, string value) {
        key = u.toUpper(key);
        value = u.toUpper(value);
        root = insertNode(root, key, value);
    }

    void deletee(string key) {
        key = u.toUpper(key);
        root = deleteNode(root, key);
    }

    void update() {
        string key;
        string value;

        cout << "Güncellemek istediğiniz kelimeyi giriniz: ";
        //cin >> key;
        getline(cin >> ws, key);
        key = u.toUpper(key);
        AVLNode* node = searchNode(root, key);
        if (node == NULL)
            cout << "Bu kelime ağaçta bulunamadı." << endl;
        else {
            cout << "Kelimenin yeni anlamını giriniz: ";
            //cin >> value;
            getline(cin >> ws, value);
            value = u.toUpper(value);
            node->value = value;
            cout << "Kelime başarıyla güncellendi." << endl;

        }
    }
   
    void search(string key) {
        AVLNode* node = searchNode(root, key);
        key = u.toUpper(key);
        if (node == NULL)
            cout << "Bu kelime ağaçta bulunamadı." << endl;
        else
            cout << node->key << " : " << node->value << endl;
    }

    void listToAlphabetic()
    {
        inOrder(root);
    }

    void listToAlphabeticWithMeans()
    {
        inOrderWithMeans(root);
    }

    void searchTwoWords() {
        string key1;
        string key2;
        cout << "1. kelimeyi giriniz: ";
        //cin >> key1;
        getline(cin >> ws, key1);

        key1 = u.toUpper(key1);
        if (searchNode(root, key1) == NULL) {
            cout << "1. kelime ağaçta bulunamadı." << endl;
            return;
        }
        
        cout << "2. kelimeyi giriniz: ";
        //cin >> key2;
        getline(cin >> ws, key2);

        key2 = u.toUpper(key2);
        if (searchNode(root, key2) == NULL) {
            cout << "2. Kelime ağaçta bulunamadı." << endl;
            return;
        }

        searchBetween(root, key1, key2);
    }
  
    int counter() {
        return count;
    }

    bool treeEmptyControl() {
        if (counter() == 0) {
            cout << "Ağaçta hiç eleman yok. Ekleme yapmak için 1'i tuşlayın." << endl;
            return 0;
        }
        return 1;
    }
};

int main()
{
    setlocale(LC_ALL, "Turkish");

    AVLTree* tree = new AVLTree(); 
    Utility u;

    int inp;
    string key;
    string value;
    bool control;
    
    while (true)
    {
        cout << "---------------------------------" << endl;
        cout << "1- Ağaca eleman ekle." << endl;
        cout << "2- Ağaçtan eleman sil." << endl;
        cout << "3- Ağaçtan elemanın anlamını güncelle." << endl;
        cout << "4- Ağacı alftabetik olarak listele." << endl;
        cout << "5- Ağacı kelime anlamlarıyla birlikte alftabetik olarak listele." << endl;
        cout << "6- Ağaçtan kelimenin anlamını bul." << endl;
        cout << "7- Ağacı verilen iki kelimeye göre alfabetik listele." << endl;
        cout << "8- Ağaçta kaç eleman olduğunu göster." << endl;
        cout << "0- Cikis." << endl;
        cout << "---------------------------------" << endl;
        cout << "- Yapmak istediğiniz işlemi seçiniz:  ";

        cin >> inp;

        if (cin.fail())
        {
            cout << "HATA -- Bir sayı tuşlamadınız." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else 
        {
            if (inp == 1)
                control = 1;
            else
                control = tree->treeEmptyControl();

            switch (inp)
            {
                case 1:
                    cout << "Eklemek istediğiniz kelimeyi giriniz: ";
                    //cin >> key;
                    getline(cin >> ws, key);

                    cout << endl << "Kelimenin anlamını giriniz: ";
                    //cin >> value;
                    getline(cin >> ws, value);

                    key = u.toUpper(key);
                    value = u.toUpper(value);
                    tree->insert(key, value);
                    break;
                case 2:
                    if (!control) {
                        break;
                    }
                    cout << "Silmek istediğiniz kelimeyi giriniz: ";
                    //cin >> key;
                    getline(cin >> ws, key);
                    key = u.toUpper(key);
                    tree->deletee(key);
                    break;
                case 3:
                    if (!control) {
                        break;
                    }
                    tree->update();
                    break;
                case 4:
                    if (!control) {
                        break;
                    }
                    tree->listToAlphabetic();
                    cout << endl;
                    break;
                case 5:
                    if (!control) {
                        break;
                    }
                    tree->listToAlphabeticWithMeans();
                    cout << endl;
                    break;
                case 6:
                    if (!control) {
                        break;
                    }
                    cout << "Anlamını bulmak istediğiniz kelimeyi giriniz: ";
                    //cin >> key;
                    getline(cin >> ws, key);
                    key = u.toUpper(key);
                    tree->search(key);
                    break;
                case 7:
                    if (!control) {
                        break;
                    }
                    tree->searchTwoWords();
                    break;
                case 8:
                    if (!control) {
                        break;
                    }
                    cout << "Ağaçtaki eleman sayısı: " << tree->counter() << endl;
                    break;
                case 0:
                    cout << "Çıkış yapılıyor..." << endl;
                    cout << "**************************" << endl;
                    cout << "* Muhammed Yasin Şenocak *" << endl;
                    cout << "*  Computer Engineering  *" << endl;
                    cout << "*       201504021        *" << endl;
                    cout << "**************************" << endl;
                    exit(25);
                    break;
                default:
                    cout << "Hatalı tuşlama yaptınız. Lütfen geçerli bir sayı tuşlayınız.." << endl;
                    break;
            }
        }
    }
    return 1;
}
```