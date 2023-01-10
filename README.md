# assignment4
arithmetic code 和 huffman code 兩種壓縮演算法比較
## os
linux 
## bulid
    cc -o main src/main.c src/huffman.c src/arcd.c src/adaptive_model.c -I ./inc 
## run
    ./main
## 測試資料
測試資料為 test/testdata 
## 壓縮結果
壓縮結果檔案儲存於output
## 查看壓縮後檔案大小
    cd output
    stat output_srcd    //arthimetic 
    stat output_huffman //huffman

