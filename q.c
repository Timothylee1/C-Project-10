/*!
@file       q.c
@author     Timothy Lee (timothykexin.lee@digipen.edu.sg)
@course     RSE 1201
@section    Assignment 7
@Assignment Text file I/O, iterations, pointers, and functions   
@date       30/10/2021
@brief      This file contains code for definitions of functions encrypt(char* , char) & 
            decrypt(char*, char). These functions serve to encrypt and decrpyt respectively,
            a single character of an input text, using the function parameters. The second
            parameter of each functions serve as the specific character key.
*//*______________________________________________________________________________________*/
#include <stdio.h>

/*!
@brief  This function encrypt() contains code to encrypt a single letter of an input text
        that the function parameter *letter is pointing to. It encrypts the character with
        the cipher key character. It casts *letter and key the type int and assigns smth 
        the value. It then checks if smth is greater than 127, the limit of the basic ASCII
        character set, if it is, it warps the int value down to fit the ASCII range before
        casting smth the type char and assigning it back to *letter. 

@param  letter declared as pointer of type char
        key is declared as type char
        smth is declared as type int
		
@return Returns nothing
*//*_______________________________________________________________________________________*/
// Encrypt a single letter of an input text.
void encrypt(char* letter, char key){
        //casting char data types to int is automated with reference to ASCII
        int smth = *letter + key;
        smth > 127 ? smth-= 128 : smth; //ensure 0 to 127 ASCII range 
        *letter = (char)smth; //convert back to char
}

/*!
@brief  This function decrypt() contains code to decrypt a single letter of an input text
        that the function parameter *letter is pointing to. It decrypts the character with
        the cipher key character. It then reverses the encryption process by subtracting 
        the int value *letter is pointing by the int value of key and assigns that value to 
        check. It then verifies if check is a negative number and if it is, it adds back 
        what was subtracted in the encryption process. After which it casts check the type 
        char assigns it back to *letter. 

@param  letter declared as pointer of type char
        key is declared as type char
        check is declared as type int
		
@return Returns nothing
*//*_______________________________________________________________________________________*/
//Decrypt a single letter of an input text.
void decrypt(char* letter, char key){
        //casting char data types to int is automated with reference to ASCII
        int check = *letter - key;
        //if negative int, add 128 which was subtracted when encrypting
        *letter = check < 0 ? (char) (check += 128) : (char) check;
 }

