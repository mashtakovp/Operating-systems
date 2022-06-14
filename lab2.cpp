#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void help() {
	cout << "cp - копирование файлов\nmv - перемещение файлов\ninfo - информация о файле\nquit - выйти из программы\npwd - проверить ваш текущий каталог\ncd - выбор директории\n" << endl;
	cout << " chmod - изменение прав на файл, вам нужно выбрать один из следующих режимов и ввести номер режима, когда программа попросит вас : \n 1 - установить идентификатор пользователя\n 2-установить идентификатор группы\n 3 - sticky bit\n 4 - владелец может читать\n 5 - владелец может изменять\n 6 - владелец может выполнить файл или искать в каталоге\n 7 - группа владелец может читать\n 8 - группа владелец может изменять\n 9 - группа владелец может выполнить файл или искать в каталоге\n 10 - Все остальные могут читать\n 11 - все остальные могут изменять\n 12 - все остальные могут выполнить файл или искать в каталоге\n" << endl;
}
void copy() {
	string file_name;
	cout << "Введите имя файла, который вы хотите скопировать:" << endl;
	cin >> file_name;
	ifstream fin;
	fin.open(file_name);
	if (!fin) {
		cout << "Файл не может быть открыт " << file_name << endl;
		fin.close();
		return copy();
	}
	cout << "Название файла: " << file_name << endl;
	bool flag = true; // для проверки на совпадение имён файла
	string copy_name;
	while (flag) {
		cin >> copy_name;
		if (copy_name == file_name) {
			cout << "Другое название: " << endl;
			continue;
		}
		flag = false;
	}
	ofstream fout;
	fout.open(copy_name);
	string buffer;
	while (!fin.eof()) {
		getline(fin, buffer);
		fout << buffer << endl;
	}
	fin.close();
	fout.close();
	cout << "Скопировано!" << endl;
}

void move() {
	cout << "Введите название файла, который вы хотите переместить: ";
	string fileName1, fileName2;
	cin >> fileName1;



	cout << "Название второго файла: ";
	cin >> fileName2;

	string command = "mv " + fileName1 + " " + fileName2;
	system(command.c_str());
}

void getInfo() {
	cout << "Введите название файла: ";
	string str;
	cin >> str;
	const char* c = str.c_str();
	struct stat sb;
	if (stat(c, &sb) == -1) {
		perror("stat");
	}
	else {
		printf("Тип файла:                ");
		switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("блочное устройство\n");     break;
		case S_IFCHR:  printf("символьное устройство\n");  break;
		case S_IFDIR:  printf("каталог\n");                break;
		case S_IFIFO:  printf("FIFO/канал\n");             break;
		case S_IFLNK:  printf("символьная ссылка\n");      break;
		case S_IFREG:  printf("обычный файл\n");           break;
		case S_IFSOCK: printf("сокет\n");                  break;
		default:       printf("неизвестно?\n");            break;
		}
		printf("номер inode:              %ld\n", (long)sb.st_ino);
		printf("Режим доступа:            %lo (octal)\n",
			(unsigned long)sb.st_mode);
		printf("Кол-во ссылок:            %ld\n", (long)sb.st_nlink);
		printf("Владелец:                 UID=%ld   GID=%ld\n",
			(long)sb.st_uid, (long)sb.st_gid);
		printf("Предпоч. размер бл. в/в:  %ld байт\n",
			(long)sb.st_blksize);
		printf("Размер файла:             %lld байт\n",
			(long long)sb.st_size);
		printf("Выделено блоков:          %lld\n",
			(long long)sb.st_blocks);
		printf("Посл. изм. состояния:     %s", ctime(&sb.st_ctime));
		printf("Посл. доступ к файлу:     %s", ctime(&sb.st_atime));
		printf("Посл. изм. файла:         %s", ctime(&sb.st_mtime));
	}
}

void chmod() {
	cout << "Введите аргументы для  chmod( <fileName> <mode_t>): ";
	cin.clear();
	cin.ignore(1000, '\n');
	string filename;
	int md;
	const char* c = filename.c_str();
	cin >> filename >> md;
	switch (md) {
	case 1:
		if (chmod(c, S_ISUID) != -1) {
			printf("Успешно изменено \n");
			cout << "установить при выполнении идентификатор пользователя" << endl;
		}
		else printf("ERR \n");
		break;
	case 2:
		if (chmod(c, S_ISGID) != -1) {
			printf("Успешно изменено \n");
			cout << "установить при выполнении идентификатор группы" << endl;
		}
		else printf("ERR \n");
		break;
	case 3:
		if (chmod(c, S_ISVTX) != -1) {
			printf("Успешно изменено \n");
			cout << "sticky bit " << endl;
		}
		else printf("ERR \n");
		break;
	case 4:
		if (chmod(c, S_IRUSR) != -1) {
			printf("Успешно изменено \n");
			cout << "владелец может читать" << endl;
		}
		else printf("ERR \n");
		break;
	case 5:
		if (chmod(c, S_IWUSR) != -1) {
			printf("Успешно изменено \n");
			cout << "владелец может изменять " << endl;
		}
		else printf("ERR \n");
		break;
	case 6:
		if (chmod(c, S_IXUSR) != -1) {
			printf("Успешно изменено \n");
			cout << "владелец может выполнять файл или искать в каталоге" << endl;
		}
		else printf("ERR \n");
		break;
	case 7:
		if (chmod(c, S_IRGRP) != -1) {
			printf("Успешно изменено \n");
			cout << "группа-владелец может читать " << endl;
		}
		else printf("ERR \n");
		break;
	case 8:
		if (chmod(c, S_IWGRP) != -1) {
			printf("Успешно изменено \n");
			cout << "группа-владелец может изменять " << endl;
		}
		else printf("ERR \n");
		break;
	case 9:
		if (chmod(c, S_IXGRP) != -1) {
			printf("Успешно изменено \n");
			cout << "группа-владелец может выполнять файл или искать в каталоге " << endl;
		}
		else printf("ERR \n");
		break;
	case 10:
		if (chmod(c, S_IROTH) != -1) {
			printf("Успешно изменено \n");
			cout << "все остальные могут читать " << endl;
		}
		else printf("ERR \n");
		break;
		case 11
		:if (chmod(c, S_IWOTH) != -1) {
			printf("Успешно изменено \n");
			cout << "все остальные могут изменять" << endl;
		}
		else printf("ERR \n");
			break;
		case 12:
			if (chmod(c, S_IXOTH) != -1) {
				printf("Успешно изменено \n");
				cout << "все остальные могут выполнять файл или искать в каталоге " << endl;
			}
			else printf("ERR \n");
			break;
	}
}

void cd() {
	cout << "Введите аргументы для cd(<directoryPath>): ";
	string entry;
	cin.clear();
	cin.ignore(1000, '\n');
	getline(cin, entry);
	entry = "cd " + entry;
	system(entry.c_str());
	cin.clear();
}

void processCommand(string entry) {
	if (entry == "--help")  help();
	else if (entry == "cp") {
		copy();
	}
	else if (entry == "mv") {
		move();
	}
	else if (entry == "info") {
		getInfo();
	}
	else if (entry == "chmod") {
		chmod();
	}
	else if (entry == "pwd") {
		system("pwd");
	}
	else if (entry == "cd") {
		cd();
	}
	else {
		if (entry != "quit") cout << "Неккоректный ввод, для справки: --help\n";
	}
}

int main() {
	string entry;
	bool exit = false;
	while (!exit) {
		cout << "Введите команду: ";
		cin >> entry;
		processCommand(entry);
		if (entry == "quit") exit = true;
	}
	return 0;
}

