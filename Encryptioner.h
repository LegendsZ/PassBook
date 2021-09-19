#pragma once
#include <string>
#include <vector>

class Encrptioner {
private:
	const std::vector<std::string> codeVec ={"xvy","jal","nyu","jup","rvp","dzi","sam","qcf","tpm","jod","ypi","uvq","zrf","kor","rab","xnd","pwb","nnf","hey","xzg","fvx","ygh","szm","bps","nwf","svm","rog","xro","izo","ohs","usw","qxt","tof","wyv","tyl","odl","jvv","djl","luz","kbp","qbq","qrk","nht","prx","mqt","sca","bmh","grs","gxl","tht","wdu","ccf"};
	const std::vector<std::string> abcs = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
public:
	std::string Encrypt(std::string toEncrypt) {
		std::string sendBack;
		for (int i = 0; i < toEncrypt.length(); i++) {
			if ((toEncrypt[i] - 65) >= 0 && (toEncrypt[i] - 65) < 52) {
				sendBack += codeVec.at(toEncrypt[i] - 65);
			}
			else {
				sendBack += toEncrypt.at(i);
			}
		}
		return sendBack;
	}



	std::string Decrypt(std::string toDecrypt) {
		//i dont know what the password was called so I just said password. its the encrypted thing.
		std::string decrptdPass = "";

		for (int x = 0; x < toDecrypt.length(); x += 3) //might ahve a extra character than a multiple of 3. //account for that
		{
			std::string pass;
			pass = toDecrypt.substr(x, 3);

			for (int s = 0; s <= codeVec.size();s++)
			{
				if (pass == codeVec[i]) {
					decrptdPass += abcs[i];
					return;
				}

			}

		}
		return decrptdPass
	}
}