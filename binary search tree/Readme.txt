這次作業中共有 3 個檔案
    - HW3.cpp
    - sample.txt
    - Readme.txt

main.cpp 為主要的程式碼
sample.txt 為輸入測資的地方
執行後，資料夾內會出現一個新的檔案：output.txt
output.txt 即是輸出的結果

若是想測試不同的測資，不用將 output.txt 刪掉
新的輸出會覆蓋掉舊的輸出

----------------------------------------------

環境設定：
為避免出現無法編譯的情況，麻煩助教先設定一下 dev c++ 的環境

（這段是中文版，英文版請看下一段）
在畫面頂端的工具列中找到【工具】>>【編譯選項】>>【編譯器】
並在「編譯時加入以下命令」欄位中，輸入 -std=c++11 並按下確定
!最後記得重啟 dev c++！

英文版則是【Tools】>>【Compiler Options】>>【General】
在 Add the following commands when calling the compiler: 欄位中
輸入 -std=c++11 並按下 OK
!最後記得重啟 dev c++！

若還是不清楚，可以參考 
中文文章：https://blog.csdn.net/qq_43381887/article/details/100654246
英文影片（2:10 開始）：https://www.youtube.com/watch?v=0mvfY84jV-U

------------------------------------------------------

執行程式：
用 dev c++ 直接開啟 main.cpp

開啟的方式有兩種：
1.先關閉 dev c++，從檔案總管直接雙擊 main.cpp 原則上預設會用 dev c++ 開啟
2.重啟完 dev C++ 後，從左上角的工具列按【檔案】>>【開啟】然後選擇 main.cpp

按下 compile、run 在 console 會依規定出現 "enter filename : "
輸入檔案名稱後，程式會開啟檔案並讀入、運算
console 上也依照規定，print 出迷宮、路徑、成功與否
資料夾內會多出一個 output.txt，內容也是規定的 output

------------------------------------------------------

程式講解：

所有的 function 都要傳入 std::ofstream，為了輸出到 output.txt，下面就不特別解釋 std::ofstream 了
有些 function 過程會輸出到 console & output.txt，都是照著題目要求輸出，下面也不特別解釋

這一些是 Binary search tree 裡面的 function :

    - Node* search(const int& num, std::ofstream& o);
        參數：欲搜尋的數字 num
        回傳：有找到的話，return 那個 node 的 pointer
             沒找到的話，return 0 (NULL pointer)
        
    - void insert(const int& num, std::ofstream& o);
        參數：愈插入的數字 num
        回傳：void
    
    - void delet(Node* & root, const int& num, std::ofstream& o);
        參數：當下的 Node pointer、愈刪除的數字 num （因為是用 recursion 實作，所以 prototype 命名的 root 不是指 BST 的 root，而是當下的 pointer）
        回傳：void

    - void inorder(Node* current, std::ofstream& o);
        參數：當下的 pointer
        回傳：void
        -------------
        這是拿來做 recursion 的 inorder function
        下面一位 inorder 是拿來啟動的，它會將 BST 的 root 傳入這個 inorder function（封裝性考量）

    - void inorder(std::ofstream& o);
        參數：
        回傳：void
        -------------
        這個 inorder 是拿來啟動的，它會將 BST 的 root 傳入上一個 inorder function（封裝性考量）
        以 inorder travers 整個 BST 並輸出

    - void preorder(Node* current, std::ofstream& o);
        參數：當下的 pointer
        回傳：void
        -------------
        這是拿來做 recursion 的 preorder function
        下面一位 preorder 是拿來啟動的，它會將 BST 的 root 傳入這個 preorder function（封裝性考量）

    - void preorder(std::ofstream& o);
        參數：
        回傳：void
        -------------
        這個 preorder 是拿來啟動的，它會將 BST 的 root 傳入上一個 preorder function（封裝性考量）
        以 preorder travers 整個 BST 並輸出
    
    - void postorder(Node* current, std::ofstream& o);
        參數：當下的 pointer
        回傳：void
        -------------
        這是拿來做 recursion 的 postorder function
        下面一位 postorder 是拿來啟動的，它會將 BST 的 root 傳入這個 postorder function（封裝性考量）

    - void postorder(std::ofstream& o);
        參數：
        回傳：void
        -------------
        這個 postorder 是拿來啟動的，它會將 BST 的 root 傳入上一個 postorder function（封裝性考量）
        以 preorder travers 整個 BST 並輸出
    
    - void level_order(std::ofstream& o);
        參數：
        回傳：void
        -------------
        以 level order travers 整個 BST 並輸出


以下是 global 的 function :

這些 functions 有些會負責從 sample.txt 讀入資料進來，所以需要傳入 std::ifstream，下面就不解釋 std::ifstream 了
而 std::ofstream& 是為了按照規定 output 至 output.txt，下面也不特別解釋
這些 functions 會呼叫對應的 BST function

    - void insert(std::ifstream& inFile, BST& tree, std::ofstream& o);
        參數：整顆 BST
        回傳：void
        -------------
        會在輸入為 'i'/'I' 時啟動
        一直從 sample.txt 讀入資料，並呼叫 BST::insert(const int& num, std::ofstream& o);
        直到讀入 -1 才會終止

    - void delet(std::ifstream& inFile, BST& tree, std::ofstream& o);
        參數：整顆 BST
        回傳：void
        -------------
        會在輸入為 'd'/'D' 時啟動
        一直從 sample.txt 讀入資料，並呼叫 BST::delet(Node* & root, const int& num, std::ofstream& o);
        直到讀入 -1 才會終止

    - void search(std::ifstream& inFile, BST& tree, std::ofstream& o);
        參數：整顆 BST
        回傳：void
        -------------
        會在輸入為 's'/'S' 時啟動
        一直從 sample.txt 讀入數字，並呼叫 BST::search(const int& num, std::ofstream& o);
        直到讀入 -1 才會終止

    - void print(BST& tree, std::ofstream& o);
        參數：整顆 BST
        回傳：void
        -------------
        會在輸入為 'p'/'P' 時啟動
        依序呼叫 BST::preorder, BST::inorder, BST::postorder, BST::level_order

------------------------------------------------------

此外，main.cpp 註解會用英文是因為，dev c++ 很鬧，使用中文註解，我怕會莫名奇妙變亂碼

感恩助教，祝助教身體健康，咖咖勳勳 XD