#include "Scytale.h"
#include <sstream>
// Name: Scytale (Default Constructor)
// Desc: Constructor to build an empty Scytale Cipher
// Preconditions - None
// Postconditions - Creates a Scytale cipher
Scytale::Scytale() : Cipher() {
    m_key = 0;
}
// Name: Scytale (Overloaded Constructor)
// Desc: Constructor to build a populated Scytale Cipher
// Preconditions - Pass it the message, isEncrypted, and key (integer)
// Postconditions - Creates a Scytale cipher to be encrypted
Scytale::Scytale(string message, bool isEncrypted, int key) : Cipher(message, isEncrypted) {
    m_key = key;
}
// Name: Scytale (Destructor)
// Desc: Destructor - Anything specific part of Scytale to delete?
// Preconditions - ~Scytale exists
// Postconditions - Scytale destroyed
Scytale::~Scytale() {}
// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void Scytale::Encrypt() {
    //Retrieve current message and prepare encrypted output string
    string currMsg = GetMessage(), encryptedMsg = "";
    char padSymbol = 'X';
    //Grid to simulate columnar encryption
    vector<vector<char>> grid;
     //Determine rows using ceiling of message length / key
    int rows = ceil(double(currMsg.length()) / m_key), cols = m_key;
    unsigned long k = 0;
    //Fill grid row-wise with message characters
    for (int i = 0; i < rows; i++) {
        vector<char> characters;
        for (int j = 0; j < cols; j++) {
            if (k < currMsg.length()) {
                characters.push_back(currMsg[k]);
            } else {
                characters.push_back(padSymbol);
            }
            k++;
        }
        grid.push_back(characters);
    }
    
    //Read grid column-wise to build encrypted message
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            encryptedMsg += grid[i][j];
        }
    }
    //Set message as newly encrypted message
    SetMessage(encryptedMsg);
    //Toggle to indicate that the stored message is encrypted
    ToggleEncrypted();
} // So my ecryption isn't working the second time but works the first time.
// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void Scytale::Decrypt() {
    //Retrieve current message and prepare decrypted output string
    string currMsg = GetMessage(), decryptedMsg = "";
    char padSymbol = 'X';

    unsigned long k = 0;
    //Recalculate rows and columns based on message length and key
    int rows = ceil(double(currMsg.length()) / m_key), cols = m_key;
    //Reconstruct original message by reading column chunks properly
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (currMsg[i+k] != padSymbol) {
                decryptedMsg = decryptedMsg + currMsg[k+i]; 
            }
            k += rows;
        }
        k = 0;
    }
    //Set message as newly dncrypted message
    SetMessage(decryptedMsg);
    //Toggle to indicate that the stored message is decrypted
    ToggleEncrypted();
}
// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Scytale in this case)
string Scytale::ToString() {
    return "Scytale";
}
// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//                  message, delimiter, key are returned for output
string Scytale::FormatOutput() {
    //Initialize stringstream to format the output
    stringstream ss;
    //Add content to ss
    ss << 's' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage() << DELIMITER << m_key;
    //Convert to string and return
    string result = ss.str();
    return result;
}