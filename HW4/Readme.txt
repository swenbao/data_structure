這次作業中共有 5 個檔案
    - dijkstra.cpp
    - prim.cpp
    - sample_d.txt
    - sample_p.txt
    - Readme.txt

程式碼執行後，資料夾內會出現新的檔案：output_p.txt / output_d.txt 即是輸出的結果

若是想測試不同的測資，不用將存在的 output.txt 刪掉
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
2.重啟完 dev c++ 後，從左上角的工具列按【檔案】>>【開啟】然後選擇 main.cpp

按下 compile、run 在 console 會依規定出現 "enter filename : "
輸入檔案名稱後，程式會開啟檔案並讀入、運算

------------------------------------------------------

這次的程式沒有寫 main 以外的 function

------------------------------------------------------

感恩助教，祝助教身體健康，不要確診，確診真的很麻煩