#include <iostream>
#include <random>
#include <time.h>
#include <string>
#include <cpr/cpr.h>
#include "data.hpp"
#include <thread>
//generate fake data
class random { public:
	std::string generate_ip() {
		srand(time(NULL));
		unsigned int rNum = 0;
		std::string ip = "";
		for (int i = 0; i < 4; i++) {
			rNum = rand() % 255 + 1;
			ip += std::to_string(rNum)+'.';
		}
		//remove the last dot if exist
		if (ip.back() == '.') ip.back() = '\0';
		return ip;
	}

	inline std::string generate_tail() {
		 srand(time(NULL));
		 return tails[rand() % 4 + 1];	
	}

	std::string generate_email(unsigned int size) {
		srand(time(NULL));
		unsigned int rNum = 0;
		std::string email = "";
		for (int i = 0; i < size - 1; i++) {
			rNum = rand() % size + 1;
			email += alphabet[i];
		}
		email.append(generate_tail());
		return email;
	}
	 // generate random password 
	std::string generate_password() {
		srand(time(NULL));
		
		std::string password = "";
		for (int i = 0; i < 8; i++) {
			unsigned int rNum = rand() % 20 + 1;
			password += alphabet[rNum];
		}
		return password;
	}

	std::string generate_6words() {
		srand(time(NULL));
		std::string sixwords = "";
		for (int i = 0; i < 6; i++) {
			unsigned int rNum = rand() % 20 + 1;
			sixwords += alphabet[rNum];
		}
		return sixwords.data();
	}
	std::string generate_id() {
		srand(time(NULL));
		std::string id = "";
		for (int i = 0; i < 4; i++) {
			unsigned int rNum = rand() % 9 + 1;
			id += numbers[rNum];
		}
		return id.data();
	}


private:
	char numbers[11]{ "0123456789" };
	char alphabet[37]{"abcdefghijklmnopqrstuvwxyz0123456789"};
	const char* tails[5]{ "@gmail.com", "yahoo.com", "@yandex.ru", "@hotmail.com" ,"@outlook.fr"};
	//
};




void send_data() {
	srand(time(NULL));
	unsigned int rNum = 5 + rand() % 10 + 1;
	std::string password = random().generate_password();
	std::string email = random().generate_email(rNum);
	std::string ip = random().generate_ip();
	std::string sixwords = random().generate_6words();
	std::string id = random().generate_id();
	//add parameters id=&p=&e=&i=111.124.54.14&n=ssbbaa

	cpr::Response response = cpr::Post(cpr::Url{ URL }, cpr::Parameters{ {"id",id},{"p",password},{"e",email},{"i",ip}, {"n",sixwords} });

	//check if the data is dent
	if (response.status_code == 200) {
		system("color 2");
		system("cls");
		std::cout << "*data sent! \n";
		std::cout << "*URL! \n"<<response.url<<"\n";
		std::cout << "*Response: \n" << response.text << "\n";
	}
	else {
		std::cout << "The service has been successfully blocked. " << response.status_code;
	}
}

  


int main() { // its working!
//	PTR  ptr = &send_data;
	typedef void(*PTR)(void);
	while (true) {
		std::vector<PTR>fns;
		for (int i = 0; i < 9000; i++) {
			fns.push_back(send_data);
		}
		std::vector<std::vector<PTR>>container;

		for (int i = 0; i <= 9000; i++) {
			container.push_back(fns);
		}
		for (int i = 0; i < container.size() - 1; i++) {
			for (auto y : container.at(i)) {
				y();
			}
		}
	}
	return 0;
}