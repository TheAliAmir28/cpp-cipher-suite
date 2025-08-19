#include "Atbash.h"
#include <sstream>
// Name: Atbash (Default Constructor)
// Desc: Constructor to build an empty Atbash Cipher
// Preconditions - None
// Postconditions - Creates a Atbash cipher to be encrypted
Atbash::Atbash() : Cipher() {}
// Name: Atbash (Overloaded Constructor)
// Desc: Constructor to build a populated Atbash Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Atbash cipher to be encrypted
Atbash::Atbash(string message, bool isEncrypted) : Cipher(message, isEncrypted) {}
// Name: Atbash (Destructor)
// Desc: Destructor - Anything specific to Atbash to delete?
// Preconditions - ~Atbash exists
// Postconditions - Atbash destroyed
Atbash::~Atbash() {}
// Name: Encrypt
// Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
// Preconditions - Message exists
// Postconditions - Reverses the characters. Ignores punctuation.
void Atbash::Encrypt() {
    //Retrieve message and create space for new encrypted message
    string currMsg = GetMessage(), encrpytedMsg = "";
    //All alphabets that can be in retrieved message, lowercase and uppercase.
    string lChars = "abcdefghijklmnopqrstuvwxyz", uChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //Initiate character-by-character traversal
    for (unsigned long i = 0; i < currMsg.length(); i++) {
        //Keep track if the current character is an alphabet.
        bool alphaAppend = false;
        //Loop through both lChars and uChars to check match
        for (unsigned long j = 0; j < lChars.length(); j++) {
            if (currMsg[i] == lChars[j]) {
                //If the current character is lowercase alphabet, retrieve the exact reverse of that character from lChars.
                encrpytedMsg += lChars[lChars.length() - (j+1)];
                //Indicate that a alphabet was appended
                alphaAppend = true;
            } else if (currMsg[i] == uChars[j]) {
                //Same applies for an uppercase character.
                encrpytedMsg += uChars[uChars.length() - (j+1)];
                alphaAppend = true;
            }
        }
        //If the letter was not an alphabet, than it was punctuation or space which should be left untouched.
        if (!alphaAppend) {
            encrpytedMsg += currMsg[i];
        }
    }
    //Set new message as the encrypted message
    SetMessage(encrpytedMsg);
    //Toggle to indicate that the message is in fact encrypted.
    ToggleEncrypted();
}
// Name: Decrypt
// Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
// Preconditions - Message exists
// Postconditions - Reverses the characters. Ignores punctuation.
void Atbash::Decrypt() {
    //The decryption algorithm for Atbash is just encryption twice.
    Encrypt();
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Atbash in this case)
string Atbash::ToString() {
    return "Atbash";
}
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter are returned for output
string Atbash::FormatOutput() {
    //Intialize a stringstream variable
    stringstream ss;
    //Add content
    ss << 'a' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage();
    //convert it to string
    string result = ss.str();
    return result;
}