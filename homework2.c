/*
 * Homework #2 
 *
 * Name: Jaewan Kim
 *
 * Sources used: None
 *
 * People consulted: None
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/* Exercise 1
 *
 * flip: Flip the elements of an array in-place
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: Nothing, modifies a in-place
 */
void flip(int *a, int len) {
    assert(a != NULL);
    assert(len > 0);
    int b[len];
    for (int i=0; i< len; i++) {
        b[i] = a[i];
    }
    for (int i=0; i< len; i++) {
        a[i] = b[len-i-1];
    }

    return;
}

/* Exercise 2
 *
 * shift: Shift the elements of an array in-place to the right by one
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: Nothing, modifies a in-place
 */
void shift(int *a, int len) {
    assert(a != NULL);
    assert(len > 0);
    int last = a[len-1];

    for (int i=len-1; i>0; i--){
        a[i] = a[i-1];
    }

    a[0]=last;
    
    return;
}

/* Exercise 3
 *
 * first_letter: Create an array of characters that contains
 *     the first letter of each word in a sentence
 *
 * sentence: the sentence
 * num_words: the length of the output array (out parameter)
 *
 * Returns: An array of characters
 */
char *first_letter(char *sentence, int *num_words) {
    assert(sentence != NULL);
    assert(num_words != NULL);
    *num_words = 1;
    for (int i=0; sentence[i] != '\0'; i++){
        if(sentence[i] == ' '){
            *num_words += 1;
        }
    }
    char *ret = (char *) calloc(sizeof(char), *num_words);
    if (ret == NULL) {
        fprintf(stderr, "Ran out of space in some function \n");
        exit(1);
    }

    int j = 1;
    ret[0]=sentence[0];
    for (int i=0; sentence[i] != '\0'; i++){
        if(sentence[i] == ' '){
            ret[j]=sentence[i+1];
            j++;
        }
    }
    
    return ret;
}

/* Exercise 4
 *
 * count_zeros_and_runs: Count the number of zeros and the 
 *     number of runs of zeros in an array
 *
 * a: the array
 * len: the length of the array
 * num_zeros: the number of zeros (out parameter)
 * num_runs: the number of runs (out parameter)
 *
 * Returns: Nothing, returns number of zeros and runs as out parameters
 */
void count_zeros_and_runs(int *a, int len, int *num_zeros, int *num_runs) {
    assert(a != NULL);
    assert(len > 0);
    assert(num_zeros != NULL);
    assert(num_runs != NULL);
    *num_zeros =0;
    *num_runs=0;

    for (int i=1; i<len; i++){
        if (a[i]==0){
            *num_zeros +=1;
            if(a[i-1]!=0){
                *num_runs +=1;
            }
        }
    }
    
    if(a[0]==0){
        *num_zeros +=1;
        *num_runs +=1;
    }
    return;
}

/* Exercise 5
 *
 * saves_space: Determine whether or not the Null encoding of
 *     an array saves space
 *
 * a: the array
 * len: the length of the array
 *
 * Returns: true if Null encoded array has fewer elements than the
 *     original, false otherwise
 */
bool saves_space(int *a, int len) {
    assert(a != NULL);
    assert(len > 0);
    int zeros=0;
    int runs=0;

    count_zeros_and_runs(a, len, &zeros, &runs);

    bool ret = ((double) zeros / runs) > 2;
    
    return ret;
}

/* Exercise 6
 *
 * encode: Null encode an array
 *
 * a: the array
 * len: the length of the array
 * encoded_len: the length of the encoded array (out parameter)
 *
 * Returns: the Null encoded array and its length as an out parameter
 */
int *encode(int *a, int len, int *encoded_len) {
    assert(a != NULL);
    assert(len > 0);
    assert(encoded_len != NULL);

    int zero=0;
    int run=0;
    count_zeros_and_runs(a, len, &zero, &run);
    
    *encoded_len = len - zero + (run * 2);
    int *encoded = (int *) calloc (sizeof(int), *encoded_len);
    if (encoded == NULL) {
        fprintf(stderr, "Ran out of space in encoded_len \n");
        exit(1);
    }

    int count=0;
    int ind = 0;
    int i =0;
    if(a[0]==0){
        for(int j=0; a[i+j] == 0 && (i+j)<len; j++){
            count++;
        }
        encoded[ind]=0;
        ind++;
        encoded[ind]=count;
        ind++;
        i += count;
        count=0;
    }
    for (; i<len; i++){
        if((a[i]==0) && (a[i-1] != 0)){
            for(int j=0; a[i+j] == 0 && (i+j)<len; j++){
                count++;
            }
            encoded[ind]=0;
            ind++;
            encoded[ind]=count;
            ind++;
            count=0;
        }else if(a[i]!=0){
            encoded[ind] = a[i];
            ind++;
        }
    }
    return encoded;
}

/* Exercise 7
 *
 * decode: Decode a Null encoded array
 *
 * a: the array
 * len: the length of the array
 * decoded_len: the length of the decoded array (out parameter)
 *
 * Returns: the decoded array and its length as an out parameter
 */
int *decode(int *a, int len, int *decoded_len) {
    assert(a != NULL);
    assert(len > 0);
    assert(decoded_len != NULL);

    int num_zero=0;
    int num_run=0;
    for (int i =0; i<len; i++){
        if (a[i]==0){
            num_zero += a[i+1];
            num_run ++;
        }
    }

    *decoded_len = len + num_zero - (num_run * 2);
    int *decoded = (int *) calloc (sizeof(int), *decoded_len);
    if (decoded == NULL) {  
        fprintf(stderr, "Ran out of space in decoded_len \n");
        exit(1);
    }
    int ind =0;
    for (int i=0; i<len; i++){
        if(a[i]==0){
            for (int j=0; j<a[i+1];j++){
                decoded[ind]=0;
                ind++;
            }
            i++;
        }else{
         decoded[ind]=a[i];
         ind++;}
    }
    return decoded;
}
