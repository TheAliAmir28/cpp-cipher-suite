#include "Cipher.h"
#include "Atbash.h"
#include "Ong.h"
#include "Scytale.h"
#include "CipherTool.h"
#include <iostream>
using namespace std;

int main() {
    CipherTool myTool("proj4_data2.txt");
    myTool.Start();
    return 0;
}