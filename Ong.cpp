#include "Ong.h"
#include <sstream>
// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong() : Cipher() {}
// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted) : Cipher(message, isEncrypted) {}
// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong() {}
// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char letter) {
    //Spaces are untouched and simply appended
    if (letter == ' ') {
        return true;
    }
    //Declare an array of vowels, both lower case and upper case
    char lVowels[] = {'a', 'e', 'i', 'o', 'u'}, uVowels[] = {'A', 'E', 'I', 'O', 'U'};
    //Traverse both array
    for (unsigned long i = 0; i < sizeof(lVowels)/sizeof(lVowels[0]); i++) {
        //If letter matches any element within an either array
        if (lVowels[i] == letter || uVowels[i] == letter) {
            //True to indicate that it is a vowel
            return true;
        }
    }
    return false;
}
// Name: IsPunct (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsPunct(char c) {
    //This approach is contradictory. Here, I check if its an alphabet.
    string lChars = "abcdefghijklmnopqrstuvwxyz", uChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //Space is considered in the isVowel function
    if (c == ' ') {
        return false;
    }
    //Traverse both strings
    for (unsigned long i = 0; i < lChars.length(); i++) {
        //If a match occurs, it can be concluded that c is not a punct.
        if (lChars[i] == c || uChars[i] == c) {
            return false;
        }
    }
    //If the condition in the loop fails for all chars in lChars and uChars, return true to indicate that c is punctuation
    return true;
}
// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt() {
    //Retrieve current message and dedicate space for encrypted message.
    string currMsg = GetMessage(), encryptedMsg = "";
    //Traverse current message letter by letter
    for (unsigned long i = 0; i < currMsg.length(); i++) {
        //Check if each character is a vowel or punctuation
        bool isVowel = IsVowel(currMsg[i]), isPunct = IsPunct(currMsg[i]);
        //If the character is a space, simply append it.
        if (currMsg[i] == ' ') {
            encryptedMsg += currMsg[i];
            //If its not a vowel or punctuation...
        } else if (!isVowel && !isPunct) {
            //Add the character with 'ong' next to it.
            encryptedMsg = encryptedMsg + currMsg[i] + "ong";
            //If its either vowel or punctuation...
        } else if (isVowel || isPunct){
            //Simply add it
            encryptedMsg = encryptedMsg + currMsg[i];
        }
        // The '-' occurs at specific places within the encrypted text.
        if (i != (currMsg.length()-1) && currMsg[i] != ' ' 
            && currMsg[i+1] != ' ' && currMsg[i] != '.' 
            && currMsg[i+1] != ')' && currMsg[i+1] != '.') {
            encryptedMsg += "-";
        }
    }
    //Set message as newly encrypted message.
    SetMessage(encryptedMsg);
    //Toggle to indicate that the message is in fact encrypted.
    ToggleEncrypted();
}

// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt() {
    //Retrieve current message and dedicate space for decrypted message.
    string currMsg = GetMessage(), decryptedMsg = "";
    //Traverse current message character-by-character...
    for (unsigned long i = 0; i < currMsg.length(); i++) { 
        //Check if vowel and punctuation
        bool isVowel = IsVowel(currMsg[i]), isPunct = IsPunct(currMsg[i]);
        //If vowel or punctuation and the character is not a dash
        if ((isVowel || isPunct) && currMsg[i] != '-') {
            //Append the character to decryption message.
            decryptedMsg += currMsg[i];
            //If its not a Vowel and not a Punctuation, so a consonant...
        }   else if (!isVowel && !isPunct) {
            //Append that character
            decryptedMsg += currMsg[i];
            //Skip the next three characters in the encrypted message since that is 'ong'
            i+=3;
        }
    }
    //Set message as newly decrypted message
    SetMessage(decryptedMsg);
    //Toggle to indicate that the text is in fact decrypted.
    ToggleEncrypted();
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString() {
    return "Ong";
}
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput() {
    //Intialize a stringstream variable
    stringstream ss;
    //Add content
    ss << 'o' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage() << DELIMITER;
    //Sonvert to string
    string result = ss.str();
    return result;
}