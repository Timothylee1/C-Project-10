/*!
@file       main.c
@author     Timothy Lee (timothykexin.lee@digipen.edu.sg)
@course     RSE 1201
@section    Assignment 7
@Assignment Text file I/O, iterations, pointers, and functions   
@date       30/10/2021
@brief      This file contains code for function main(void) that either encrypts or decrypts
            text in a text file, depending on user selection. It utilizes the Vigenere 
            cipher encryption process and the ASCII character set to encrypt text in the 
            input file to create a cipher text that will be stored in a text file. From q.h
            library, the specified keyword is "DigiPen", the encryption process looks like:

            ----------------------------------------------------------------------------
            | Input Text         |        'A'      | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' |
            ----------------------------------------------------------------------------
            | Input ASCII Code   |        65       |  66 |  67 |  68 |  69 |  70 |  71 |
            ----------------------------------------------------------------------------
            | Keyword ASCII Code |        68       | 105 | 103 | 105 |  80 | 101 | 110 |
            ----------------------------------------------------------------------------
            | Cipher Text        |        ?        |  +  |  *  |  -  | NAK |  +  |  5  |
            ----------------------------------------------------------------------------
            | Cipher ASCII Code  | (65+68)-128 = 5 |  43 |  42 |  45 |  21 |  43 |  53 |
            ----------------------------------------------------------------------------

            Note: The basic ASCII character set includes codes 0 through 127, if the 
            cipher code goes outside this range, it should warp around. If characters with
            code 65 and 68 gets added together, the result should be 5 and if we subtract, 
            the result should be 65 again. 
*//*______________________________________________________________________________________*/

#include <stdio.h>		// file and console I/O
#include <ctype.h>              // mapping characters using isspace()

#define INCLUDE_KEYWORD         // const char key[] = {'D','i','g','i','P','e','n'};
#include "q.h"			// include declarations and the decryption keyword

/*!
@brief  This function main() contains code to encrypt or decrypt text in a text file, 
        depending on user selection. 
        
        For ENCRYPT, it opens a specified file to read, plain.txt file, and another to write, 
        cipher.txt file. It has a variable type char,letter, that copies the character from 
        plain.txt file in sequence and calls the function encrypt() with the arguments 
        &letter and key[j]. key[] is a char type array that contains the keywords cipher, j
        represents the element number. j will keep increasing with each character copied 
        from the file until it reaches the set limit of array, then it will reset to 0.
        After the function encrypt() finish executing, the encrypted character is appeneded
        into the cipher.txt file. This process is repeated till it reaches the end of the
        plain.txt file. It then closes both files and terminates the program.

        For DECRYPT, the default selection, similar to ENCRYPT, it opens a specified file to
        read, cipher.txt file, and another to write, out_plain.txt file. It reverse engineers
        the ENCRYPT process. the variable type char, letter, copies the character from cipher.
        txt file in sequence and calls the function decrypt() with the arguments &letter and 
        key[j]. After the function decrypt() finish executing, the decryped character is 
        appeneded into the out_plain.txt file. After which, there is a nested if code to 
        check for whitespace and count the number of words in the decrypted text file. This 
        process is repeated till it reaches the end of the plain.txt file. It then prints 
        the word count to the stderr stream before closing both files and terminating the 
        program.

@param  num, j, keynum, check, words delcared as int data types
        letter declared as char data types
        cf, pf, of declared as pointer of type file
        key is an array name defined in q.h library that is declared above.
		
@return Returns 0 
*//*_______________________________________________________________________________________*/
int main(void)
{
        
        // TODO: encrypt characters from plain.txt and put them in file cipher.txt
	#ifdef ENCRYPT

        FILE *cf = fopen("cipher.txt", "w");    //open cipher.txt to write
        FILE *pf = fopen("plain.txt", "r");     //open plain.txt to read 

        int num, j = 0;
        int keynum = 6;                         //number of elements in key[7] = {0,1,...}
        char letter;                            //to make a copy of character in file and store this variable's memory location 

        while ( (num = fgetc(pf)) != EOF)  {
                letter = (char) num;            //cast result to char
                encrypt(&letter, key[j]);       //point to address letter
                if (j == keynum)                //ensures key[] element in range
                        j = 0;
                else 
                        j++;
                fputc(letter, cf);              //append char into file
        }

        fclose(pf);                             //closes plain.txt file
        fclose(cf);                             //closes cipher.txt file
	
        // TODO: decrypt cipher.txt into out_plain.txt
	// TODO: write count of words into stderr
        #else

        FILE *cf = fopen("cipher.txt", "r");    //open cipher.txt to read 
	FILE *of = fopen("out_plain.txt", "w"); //write/overwrite out_plain.txt to read/write from start

        int num, j = 0, check = 0, words = 0;
        int keynum = 6;                         //number of elements in key[7] = {0,1,...}
        char letter;                            //to make a copy of character in file and store this variable's memory location 

        while ( (num = fgetc(cf)) != EOF)  {
                letter = (char) num;            //cast result to char
                decrypt(&letter, key[j]);       //point to address letter
                if (j == keynum)                //ensures key[] element in range
                        j = 0;
                else 
                        j++;
                fputc(letter, of);              //puts char into file

                if (isspace(letter)) {          //if letter is whitespace
                        if (check){
                                check = 0;      //resets
                                words++;        //increment
                        }
                } else 
                        check = 1;              //ensures presence of word
        }
        fprintf(stderr, "Words: %d\n", words);  //prints to stderr word count  
        fclose(cf);                             //closes cipher.txt file
        fclose(of);                             //closes output.txt file

	#endif

	return 0;
}
