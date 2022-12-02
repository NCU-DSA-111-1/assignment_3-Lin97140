#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "arcd.h"
#include "adaptive_model.h"
#include <time.h>
#include "huffman.h"

void output(const arcd_buf_t buf, const unsigned buf_bits, void *const io)
{
    (void)buf_bits;
    FILE *const f = (FILE *)io;
    fwrite(&buf, sizeof(buf), 1, f);
}

unsigned input(arcd_buf_t *const buf, void *const io)
{
    FILE *const f = (FILE *)io;
    return 8 * fread(buf, sizeof(*buf), 1, f);
}

typedef unsigned char symbol_t;
static const arcd_char_t EOS = 1 << (8 * sizeof(symbol_t));

int main()
{
    FILE *in = fopen("testdata", "rb");
    FILE *out_arcd = fopen("output_arcd", "wb");
    FILE *out_huffman = fopen("output_huffman", "wb");
    time_t start, finish;
    double interval = 0;
    adaptive_model model;
    adaptive_model_create(&model, EOS + 1);
    arcd_enc enc;
    symbol_t sym;

    start = clock(); //開始計時

    arcd_enc_init(&enc, adaptive_model_getprob, &model, output, out_arcd); //開始壓縮
    while (0 < fread(&sym, sizeof(sym), 1, in))
    {
        arcd_enc_put(&enc, sym);
    }
    arcd_enc_put(&enc, EOS);
    arcd_enc_fin(&enc); //壓縮結束
    finish = clock();   //停止計時
    interval = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("arcd : time = %f s\n", interval);
    adaptive_model_free(&model);

    fclose(in);
    fclose(out_arcd);

    in = fopen("testdata", "rb");
    start = clock();                      //開始計時
    huffman_encode_file(in, out_huffman); //開始壓縮
    finish = clock();                     //停止計時
    interval = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("huffman : time %f s\n", interval);
    int x;
    fclose(in);
    fclose(out_huffman);
    /*
        in = fopen("output_huffman", "rb");
        FILE *out = fopen("huffman_decode", "wb");
        huffman_decode_file(in, out);
        fclose(in);
        fclose(out);
    */
    return 0;
}