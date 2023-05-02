#ifndef Q_H
#define Q_H

// Limiting ASCII to basic character set from 0 to 127.
#define ASCII_COUNT 128

#ifdef INCLUDE_KEYWORD

const char key[] = {'D','i','g','i','P','e','n'};

#endif

// Encrypt a single letter of an input text.
void encrypt(char* letter, char key);

// Decrypt a single letter of an input text.
void decrypt(char* letter, char key);

#endif // Q_H
