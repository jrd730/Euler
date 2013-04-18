/*
	Each character on a computer is assigned a unique code and the preferred standard is ASCII 
	(American Standard Code for Information Interchange). For example, uppercase A = 65, 
	asterisk (*) = 42, and lowercase k = 107.

	A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each 
	byte with a given value, taken from a secret key. The advantage with the XOR function is that 
	using the same encryption key on the cipher text, restores the plain text; for example,
	65 XOR 42 = 107, then 107 XOR 42 = 65.

	For unbreakable encryption, the key is the same length as the plain text message, and the key 
	is made up of random bytes. The user would keep the encrypted message and the encryption key 
	in different locations, and without both "halves", it is impossible to decrypt the message.

	Unfortunately, this method is impractical for most users, so the modified method is to use a 
	password as a key. If the password is shorter than the message, which is likely, the key is 
	repeated cyclically throughout the message. The balance for this method is using a sufficiently
	long password key for security, but short enough to be memorable.

	Your task has been made easy, as the encryption key consists of three lower case characters.
	Using cipher1.txt (right click and 'Save Link/Target As...'), a file containing the encrypted
	ASCII codes, and the knowledge that the plain text must contain common English words, decrypt 
	the message and find the sum of the ASCII values in the original text.

*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

set <string> :: iterator it;
set <string> words;
//
// load quote enclosed words from words.txt into a set
//
void loadWords (){
	ifstream fin("words.txt");
	bool isWord = false;
	string w("");
	while (fin.good()){
		char c = fin.get();
		if (isWord && isalpha (c)){
			w += c;
		}
		if (c == '"'){
			isWord = !isWord;
			if (!isWord){
				words.insert (w);
				w = "";
			}
		}
	}
}

vector <char> cipher;
//
// load a comma separated list of ascii values into a vector
//
void loadCipher ()
{
	ifstream fin ("cipher1.txt");	
	string s("");
	while (fin.good()){
		char c = fin.get();
		if (c >= '0' && c <= '9'){
			s += c;
		}
		else if (s.length() > 0){
			cipher.push_back ((char) atoi (s.c_str()) );
			s = "";
		}
	}
}

int main ()
{
	loadWords ();
	//for (it = words.begin(); it != words.end(); it++){ cout << *it << endl;}
	loadCipher ();
	//for (int i=0; i < cipher.size(); i++){ cout << (int)cipher[i] << endl;}
	
	// base decryption key ranges from "aaa" to "zzz"
	string tryKey ("aaa");
	
	// The number of consecutive characters sampled from the cipher from which to try to find words.
	// If enough letters are matched in the sample, then the current key is likely correct.
	int sampleSize = 30; 

	// the percentage of letters in the decoded cipher that must be matched to words 
	// in order for the current key to be considered correct
	double passRate = .4;

	bool done = false;

	// a brute force method for trying all possible encryption keys
	for (; tryKey[0] <= 'z'; tryKey[0]++){
		for (; tryKey[1] <= 'z'; tryKey[1]++){
			for (; tryKey[2] <= 'z'; tryKey[2]++){

				// decrypt only a small sample of the original cipher
				char sample[sampleSize];
				for (int i=0; i < sampleSize; i++){
					sample[i] = cipher[i] ^ tryKey[i%3];
					if (isalpha(sample[i])){ sample[i] = (char)toupper(sample[i]);}
				}

				// match groups of decoded characters to words from the dictionary
				int charsMatched = 0;
				for (int i=0; i < sampleSize; i++){
					string s("");
					for (int j=i; j < sampleSize; j++){
						s += sample[j];
						if (words.find(s) != words.end()){
							charsMatched += (j-i+1);
							//if (s.length() > longestMatch) {longestMatch = s.length();}
							i = j;
							s = "";
							break;
						}
					}
				}
				double percentMatched = (double)charsMatched/(double)sampleSize;
				// if this condition is met then the current key is likely to be correct
				if (percentMatched >= passRate){
					for (int i=0; i < sampleSize; i++){ 
						cout << sample [i];
					} cout << " " << percentMatched << endl;
					done = true;
					break;
				}
			}
			if (done) break;
			tryKey[2] = 'a';
		}
		if (done) break;
		tryKey[1] = 'a';	
	}

	int val = 0;
	// decode and print the entire decoded cipher with current key
	for (int i=0; i < cipher.size(); i++){
		cipher[i] = cipher[i] ^ tryKey[i%3];
		val += cipher[i];
		cout << cipher[i];
	}
	cout << "\nKey: " << tryKey << " Total sum of original text: " << val << endl;
}