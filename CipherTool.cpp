#include "CipherTool.h"
// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string filename) : m_filename(filename) {}
// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool() {
    //Traverse the vector that stores all pointers
    for (unsigned i = 0; i < m_ciphers.size(); i++) {
        //Relieve space. Each object will call its own destructor which is enabled by late-binding
        delete m_ciphers[i];
    }
    //Clear the vector of all dangling pointers
    m_ciphers.clear();
}
// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (a is Atbash, s is Scytale, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile() {
    //Open file
    ifstream inputstream;
    inputstream.open(m_filename);
    string cipherType, encryptionFlag, message, strKeyForScytale;
    int scytaleKey = 0;

    //Retrieve each line within the file using multiple getline calls
    // This loop broke my soul for 4 hours because getline() doesn't play fair.
    while (getline(inputstream, cipherType, DELIMITER) && getline(inputstream, encryptionFlag, DELIMITER) && getline(inputstream, message, DELIMITER)) {
        //If cipher type is scytale, then there is an extra component 'key' which we need to read.
        if (cipherType == "s") {
            if (getline(inputstream, strKeyForScytale, '\n')) {
                //The key is initially a string but we need to convert it to int for construction
                scytaleKey = stoi(strKeyForScytale);
            }
        } else {
            getline(inputstream, strKeyForScytale, '\n');
        }
        //Encryption flag is initially a string and construction requires a bool type so conversion is necessary
        bool boolEncryptionFlag = StringToBoolean(encryptionFlag);

        //Create the respective cipher and add it it m_ciphers
        if (cipherType == "a") {
            Cipher* newAtbash = new Atbash(message, boolEncryptionFlag);
            m_ciphers.push_back(newAtbash);
        } else if (cipherType == "o") {
            Cipher* newOng = new Ong(message, boolEncryptionFlag);
            m_ciphers.push_back(newOng);
        } else if (cipherType == "s") {
            Cipher* newScytale = new Scytale(message, boolEncryptionFlag, scytaleKey);
            m_ciphers.push_back(newScytale);
        }
    }
    //Close file
    inputstream.close();
} //SO THIS CURRENT CODE OF MINE WORKS BETTER BUT IT JUST DOESN'T PROCESS THE FINAL LINE IN THE TEXT FILE

// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input) {
    return input == "1" ? true : false;
}
// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers() {
    //Traverse all ciphers in m_ciphers
    for (unsigned long i = 0; i < m_ciphers.size(); i++) {
        //Display their number, their content (using overloaded operator), and their cipher type
        cout << i+1 << "." << " " << *m_ciphers[i] << " (" << m_ciphers[i]->ToString() << ")" << endl;
        cout << endl;
    }
}
// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool encrypt) {
    //If trying to encrypt
    if (encrypt == true) {
        //Keep track of how many encrypted
        int totalEncrypted = 0;
        //Traverse all ciphers in m_ciphers
        for (unsigned long i = 0; i < m_ciphers.size(); i++) {
            //If the message is not encrypted already
            if (m_ciphers[i]->GetIsEncrypted() == false) {
                //Encrypt it
                m_ciphers[i]->Encrypt();
                //Increment tracker
                totalEncrypted++;
            }
        }
        cout << totalEncrypted << " ciphers Encrypted" << endl;
    //If trying to decrypt
    } else if (encrypt == false) {
        //Keep track of how many decrypted
        int totalDecrypted = 0;
        //Traverse all ciphers in m_ciphers
        for (unsigned long i = 0; i < m_ciphers.size(); i++) {
            //If the message is not decrypted already
            if (m_ciphers[i]->GetIsEncrypted() == true) {
                //Decrypt it
                m_ciphers[i]->Decrypt();
                //Increment tracker
                totalDecrypted++;
            }
        }
        cout << totalDecrypted << " ciphers Decrypted" << endl;
    }
}
// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export() {
    string filename;
    //Tracker of how many ciphers exported
    int totalExported = 0;
    //Get file name from user
    cout << "\nWhat would you like to call the export file?" << endl;
    cin >> filename;
    //Open file to write to
    ofstream storageFile(filename);
    for (unsigned long i = 0; i < m_ciphers.size(); i++) {
        //Format the cipher
        string text = m_ciphers[i]->FormatOutput();
        //Store it in the desired file
        storageFile << text << endl;
        //Increment Tracker
        totalExported++;
    }
    storageFile.close();
    //Display message
    cout << totalExported << " ciphers exported" << endl;
}
// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu() {
    int menuChoice;
    //Display menu and get choice until the choice is valid
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Display All Ciphers" << endl;
        cout << "2. Encrypt All Ciphers" << endl;
        cout << "3. Decrypt All Ciphers" << endl;
        cout << "4. Export all Ciphers" << endl;
        cout << "5. Quit" << endl;  
        cin >> menuChoice;
    } while (menuChoice < 1 || menuChoice > 5);
    //return choice for further processes
    return menuChoice;
}
// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start() {
    //Load the file given
    LoadFile();
    int userMenuChoice = 0;
    //Welcome message
    cout << "Welcome to UMBC Encryption" << endl;
    //While the user doesn't decide to quit
    while (userMenuChoice != 5) {
        userMenuChoice = Menu();
        //Execute the proper functionality based on the choice
        if (userMenuChoice == 1) {
            DisplayCiphers();
        } else if (userMenuChoice == 2) {
            EncryptDecrypt(true);
        } else if (userMenuChoice == 3) {
            EncryptDecrypt(false);
        } else if (userMenuChoice == 4) {
            Export();
        } else if (userMenuChoice != 5) {
            cout << "Invalid choice. Please try again!" << endl;
        }
    }
    //Final message
    cout << "Thank you for using UMBC Encryption" << endl;
}