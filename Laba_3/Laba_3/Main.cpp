/*Результатом должна быть консольная программа с текстовым меню. Программа
должна содержать шаблонный класс для управления данными согласно заданию.
Для хранения данных необходимо выбрать оптимальный с точки зрения задания
контейнер.*/

/*
1. Предусмотреть операции добавления, изменения и удаления элемента
контейнера.
2. Реализовать ввод и вывод элементов контейнера с использованием потоковых
итераторов на экран и в файл.
3. Реализовать операции поиска по заданным критериям и выборки подмножества
элементов по заданным критериям. Реализовать поиск в двух вариантах: линейный
поиск и двоичный поиск на отсортированном контейнере.
4. Предусмотреть вывод подмножества выборки на экран и в файл.
*/

/*Информация об автомобиле представлена структурой с полями: фамилия
владельца, код марки, наименование марки, требуемая марка бензина, мощность
двигателя, объем бака, остаток бензина, объем масла. Поиск по марке
автомобиля, марке бензина, мощности двигателя, фамилии владельца.*/


/*Реализовать виртуальную автомастерскую.
Предусмотреть режим автовладельца и работника мастерской (выбирается в меню). */

/*В режиме автовладельца должна быть возможность
–сдать автомобиль в обслуживание
–забрать его
(предусмотреть поиск по необходимым полям в списке автомобилей).*/

/*В режиме сотрудника мастерской предусмотреть
–просмотр списка автомобилей с текущим статусом
(должна поддерживаться фильтрация и сортировка по выбранному полю),
–операции заправки автомобиля маслом и бензином.
Предусмотреть хранение и просмотр истории обслуживания автомобилей.*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::ostream;
using std::istream;
using std::deque;
using std::string;
using std::ofstream;
using std::ifstream;
using std::istream_iterator;
using std::ostream_iterator;
using std::ios_base;
using std::generate;
using std::transform;
using std::for_each;
using std::srand;
using std::advance;
using std::sort;

const string FILE_NAME_DATA_BASE = "Data_base.txt";
const string mass_p[9] = { "VIN автомобиля: ", "Фамилия владельца: ", "Код марки: ", "Наименование марки: ",
						  "Марка бензина: ", "Мощность двигателя: ", "Объем бака: ", "Остаток бензина: ", "Объем масла: " };

//структура с информацией об авто
struct Car
{
	string id_car;//уникальный id авто
	string name_owner;//фио владельца
	string code_brand;//код марки
	string name_brand;//наименование марки
	string name_petrol;//требуемая марка бензина
	int engine_power;//мощность двигателя
	int capacity_tank;//объем бака
	int gasoline_petrol;//остаток бензина
	int capacity_oil;//объем масла
	Car(string _id_car, string _name_owner, string _code_brand, string _name_brand, string _name_petrol, 
		int _engine_power, int _capacity_tank, int _gasoline_petrol, int _capacity_oil):
		id_car(_id_car), name_owner(_name_owner), code_brand(_code_brand), name_brand(_name_brand), name_petrol(_name_petrol),
		engine_power(_engine_power), capacity_tank(_capacity_tank),	gasoline_petrol(_gasoline_petrol), capacity_oil(_capacity_oil) { }

	Car() : Car("", "", "", "", "", 0, 0, 0, 0) { }
	
	// добавил конструктор копирования
	Car(const Car& el):id_car (el.id_car), name_owner(el.name_owner), code_brand(el.code_brand), name_brand(el.name_brand), name_petrol(el.name_petrol), 
		engine_power(el.engine_power), capacity_tank(el.capacity_tank), gasoline_petrol(el.gasoline_petrol), capacity_oil(el.capacity_oil) { }

	Car& operator=(const Car& el)
	{
		id_car = el.id_car;
		name_owner = el.name_owner;
		code_brand = el.code_brand;
		name_brand = el.name_brand;
		name_petrol = el.name_petrol;
		engine_power = el.engine_power;
		capacity_tank = el.capacity_tank;
		gasoline_petrol = el.gasoline_petrol;
		capacity_oil = el.capacity_oil;
		return *this;
	};
};
int Enter_value(istream &in)
{
	int value;
	while (!(in >> value))//пока не будет введено нормальное число, выполняем цикл
	{        
		cout << "Неверный формат" << endl;//сообщаем об ошибке ввода
		cout << "Повторите ввод" << endl;
		in.clear();
		in.ignore(10000, '\n');
	}
	return value;
}
string Enter_string(istream &in)
{
	string str;
	getline(in, str);
	return str;
}
//---------------------------------------------------------------------------
//перегрузка "<<" и ">>"

void input(istream &in, ostream &ot, Car &el, string m_p, const string mass[9])
{
	Car tmp;
	ot << m_p;
	ot << mass[0];
	tmp.id_car = Enter_string(in);
	ot << mass[1];
	tmp.name_owner = Enter_string(in);
	ot << mass[2];
	tmp.code_brand = Enter_string(in);
	ot << mass[3];
	tmp.name_brand = Enter_string(in);
	ot << mass[4];
	tmp.name_petrol = Enter_string(in);
	ot << mass[5];
	tmp.engine_power = Enter_value(in);
	ot << mass[6];
	tmp.capacity_tank = Enter_value(in);
	ot << mass[7];
	tmp.gasoline_petrol = Enter_value(in);
	ot << mass[8];
	tmp.capacity_oil = Enter_value(in);
	el = tmp;
}
istream& operator>>(istream &in, Car &el)
{
	string m_p = "Введите данные:\n\n";
	std::ostringstream ost;
	typeid(in) == typeid(ifstream) ? input(in, ost, el, "", mass_p) : input(in, cout, el, m_p, mass_p);
	return in;
}

void print(ostream &out, ostream &ot, const Car &el, string m_p, const string mass[9])
{
	ot << m_p;
	ot << mass[0]; out << el.id_car << endl;
	ot << mass[1]; out << el.name_owner << endl;
	ot << mass[2]; out << el.code_brand << endl;
	ot << mass[3]; out << el.name_brand << endl;
	ot << mass[4]; out << el.name_petrol << endl;
	ot << mass[5]; out << el.engine_power << endl;
	ot << mass[6]; out << el.capacity_tank << endl;
	ot << mass[7]; out << el.gasoline_petrol << endl;
	ot << mass[8]; out << el.capacity_oil << endl;
}

ostream& operator<<(ostream &out, const Car &el)
{
	string m_p = "Данные:\n";
	std::ostringstream ost;
	typeid(out) == typeid(ofstream)? print(out, ost, el,"", mass_p): print(out, out, el, m_p, mass_p);
	return out;
}
//-------------------------------------------------------------------------
//по марке автомобиля, марке бензина, мощности двигателя, фамилии владельца, id владельца.
struct Is_id_car
{
	string id_car;
	Is_id_car(string _id_car) : id_car(_id_car) { }
	bool operator()(const Car &el) { return el.id_car == id_car; }
};
struct Is_name_owner
{
	string name_owner;
	Is_name_owner(string _name_owner) : name_owner(_name_owner) { }
	bool operator()(const Car &el) { return el.name_owner == name_owner; }
};

struct Is_name_brand
{
	string name_brand;
	Is_name_brand(string _name_brand) :name_brand(_name_brand) { }
	bool operator()(const Car &el) { return el.name_brand == name_brand; }
};
struct Is_engine_power
{
	int engine_power;
	Is_engine_power(int _engine_power) :engine_power(_engine_power) { }
	bool operator()(const Car &el) { return el.engine_power == engine_power; }
};

struct Is_name_petrol
{
	string name_petrol;
	Is_name_petrol(string _name_petrol) :name_petrol(_name_petrol) { }
	bool operator()(const Car &el) { return el.name_petrol == name_petrol; }
};

//Шаблоный класс
template<typename T>
class Data_list
{
	deque<T> Deq;
	deque<T> Help_deq;
public:
	Data_list() :Deq(), Help_deq() { }
	//Функции для использования стандартных функций deque
	deque<Car>::iterator Deq_begin() { return Deq.begin(); }
	deque<Car>::iterator Help_deq_begin() { return Help_deq.begin(); }
	deque<Car>::iterator Deq_end() { return Deq.end(); }
	deque<Car>::iterator Help_deq_end() { return Help_deq.end(); }
	int Deq_size() { return Deq.size(); }
	int Help_deq_size() { return Help_deq.size(); }
	void Deq_clear() { Deq.clear(); }
	void Help_deq_clear() { Help_deq.clear(); }
	void Deq_push(T car){ Deq.push_back(car); }
	void Help_deq_push(T car) { Help_deq.push_back(car); }
	//---------------------------------------------------

	void Add_data()
	{
		istream_iterator<T> is;
		is = cin;
		Deq.push_back(*is);
	}

	void Load_to_file(ofstream& _file, typename deque<T>::iterator x)
	{
		ostream_iterator<T> is(_file, "\n");
		*is = *x;
		cout << "Данные успешно добавлены в базу данных" << endl;
	}
	void Print_some_data()
	{
		copy(Help_deq.begin(), Help_deq.end(), ostream_iterator<T>(cout, "\n"));
	}

	void Delete_data(typename deque<T>::iterator x)
	{
		Deq.erase(x);
	}

	void Load_to_file_some_data(ofstream& _file)
	{
		copy(Deq.begin(), Deq.end(), ostream_iterator<T>(_file, "\n"));
	}
	void Load_from_file_some_data(ifstream& _file)
	{
		while (_file.peek() != EOF)
		{
			Deq.push_back(*istream_iterator<T>(_file));
			_file.get();
			_file.get();
		}
	}
	void Print_data(typename deque<T>::iterator x)
	{
		cout << *x << endl;
	}

	void Help_sort_deq(deque<Car>::iterator& i)
	{
		Car avto1, avto2, tmp;
		deque<Car>::iterator x = i;
		for (deque<Car>::iterator j = (i + 1); j < Help_deq.end(); j++)
		{
			avto1 = *x;
			avto2 = *j;
			if (avto1.id_car > avto2.id_car)
			{
				x = j;
			}
		}
		std::swap(*i, *x);
	}
	void Sort_deq()
	{
		for (deque<Car>::iterator i = Help_deq.begin(); i < (Help_deq.end() - 1); i++)
			Help_sort_deq(i);
	}

	void If_tmp_deq_empty(Car car, deque<int>& count_deq, deque<Car>& tmp_deq)
	{
		tmp_deq.push_back(car);
		count_deq.push_back(1);
	}

	void Help_selection_id(Car car, Car& car2, deque<int>& count_deq, deque<Car>& tmp_deq, bool& control)
	{
		int num;
		deque<Car>::iterator j;
		deque<int>::iterator x;
		for (j = tmp_deq.begin(), x = count_deq.begin(); j < tmp_deq.end(); j++, x++)
		{
			num = *x;
			car2 = *j;
			if (car.id_car == car2.id_car)
			{
				*j = car;
				num++;
				*x = num;
				control = true;
				return;
			}
		}
	}
	void Work_with_rent(deque<Car>& tmp_deq, deque<int>& count_deq)
	{
		deque<Car>::iterator j;
		deque<int>::iterator x;
		for (j = tmp_deq.begin(), x = count_deq.begin(); j < tmp_deq.end(); j++, x++)
		{
			if (*x % 2 != 0)
				Help_deq.push_back(*j);
		}
		if (Help_deq.size() == 0)
		{
			system("cls");
			cout << "Автомобилей в мастерской не найдено" << endl;
		}
	}
	
	void selection_id()
	{
		Car car,car2;
		deque<int> count_deq;
		deque<Car> tmp_deq;
		int count = 0;
		bool control;
		Car avto1, avto2;
		if (Help_deq.size() == 0)
		{
			cout << "Автомобилей в мастерской не найдено" << endl;
			return;
		}
		for (deque<Car>::iterator i = Help_deq.begin(); i < Help_deq.end(); i++)
		{
			control = false;
			car = *i;
			if (tmp_deq.size() == 0)
			{
				If_tmp_deq_empty(car, count_deq, tmp_deq);
				continue;
			}
			Help_selection_id(car, car2, count_deq, tmp_deq, control);
			if (!control)
			{
				tmp_deq.push_back(car);
				count_deq.push_back(1);
			}
		}
		Help_deq.clear();
		Work_with_rent(tmp_deq, count_deq);
	}
	void copy_if_id_car(string id_car) 
	{ 
		copy_if(Deq.begin(), Deq.end(), back_inserter(Help_deq), Is_id_car(id_car)); 
	}
	void copy_if_name_owner(string name_owner) 
	{ 
		copy_if(Deq.begin(), Deq.end(), back_inserter(Help_deq), Is_name_owner(name_owner)); 
	}
	void copy_if_name_brand(string name_brand) 
	{
		copy_if(Deq.begin(), Deq.end(), back_inserter(Help_deq), Is_name_brand(name_brand)); 
	}
	void copy_if_engine_power(int engine_power)
	{ 
		copy_if(Deq.begin(), Deq.end(), back_inserter(Help_deq), Is_engine_power(engine_power)); 
	}
	void copy_if_name_petrol(string name_petrol) 
	{ 
		copy_if(Deq.begin(), Deq.end(), back_inserter(Help_deq), Is_name_petrol(name_petrol)); 
	}

};

bool Come_back (int tmp)
{
	if (tmp == 0)
		return true;
	if (tmp != 1)
	{
		cout << "Неверный формат" << endl;
		system("PAUSE");
		return true;
	}
	return false;
}

void Sub_text_menu()
{
	cout << "Выберите действие: " << endl;
	cout << "1. Выборка с одинаковой фамилией владельца" << endl;
	cout << "2. Выборка с одинаковой маркой автомобиля" << endl;
	cout << "3. Выборка с одинаковой мощностью двигателя" << endl;
	cout << "4. Выборка с одинаковой маркой бензина" << endl;
	cout << "0. Отмена" << endl;
}

void Selection(Data_list<Car>& a)
{
	int tmp;
	string name_owner;
	string name_brand;
	string name_petrol;
	int engine_power;
	bool control = true;
	while (control)
	{
		system("cls");
		a.Help_deq_clear();
		Sub_text_menu();
		tmp = Enter_value(cin);
		switch (tmp)
		{
		case 1:
			cout << "Фамилия владельца: "; 
			cin.get();
			name_owner = Enter_string(cin);
			a.copy_if_name_owner(name_owner);
			a.selection_id();
			a.Print_some_data();
			system("PAUSE");
			break;

		case 2:
			cout << "Название марки: ";
			cin.get();
			name_brand = Enter_string(cin);
			a.copy_if_name_brand(name_brand);
			a.selection_id();
			a.Print_some_data();
			system("PAUSE");
			break;
		case 3:
			cout << "Мощность двигателя: "; 
			engine_power = Enter_value(cin);
			a.copy_if_engine_power(engine_power);
			a.selection_id();
			a.Print_some_data();
			system("PAUSE");
			break;
		case 4:
			cout << "Марка бензина: ";
			cin.get();
			name_petrol = Enter_string(cin);
			a.copy_if_name_petrol(name_petrol);
			a.selection_id();
			a.Print_some_data();
			system("PAUSE");
			break;
		case 0:
			control = false;
			break;
		default:
			cout << "Неверный формат" << endl;
			system("PAUSE");
			break;
		}
	}
}

void Search(Data_list<Car>& acc)
{
	string id_car;
	cout << "Введите VIN автомобиля (указан в свидетельсве о регистрации): ";
	cin.get();
	id_car = Enter_string(cin);
	acc.Help_deq_clear();
	acc.copy_if_id_car(id_car);
	if (acc.Help_deq_size() == 0)
	{
		system("cls");
		cout << "Автомобиль с таким VIN не был в мастерской" << endl;
		system("PAUSE");
		return;
	}
	system("cls");
	acc.Print_some_data();
	system("PAUSE");
}

void Gas_and_oil(Data_list<Car>& acc)
{
	Car avto, tmp_avto;
	deque<Car>::iterator x;
	int tmp;
	string id_car;
	cout << "Введите VIN автомобиля (указан в свидетельсве о регистрации): ";
	cin.get();
	id_car = Enter_string(cin);
	acc.Help_deq_clear();
	acc.copy_if_id_car(id_car);
	if (acc.Help_deq_size() == 0)
	{
		system("cls");
		cout << "Автомобиля нет в мастерской" << endl;
		system("PAUSE");
		return;
	}
	acc.selection_id();
	if (acc.Help_deq_size() == 0)
		return;
	system("cls");
	acc.Print_some_data();
	cout << endl;
	cout << "1. Заправить" << endl;
	cout << "0. Отмена" << endl;
	tmp = Enter_value(cin);
	if (Come_back(tmp))
		return;
	avto = *acc.Help_deq_begin();
	avto.gasoline_petrol = avto.capacity_tank;
	*acc.Help_deq_begin() = avto;
	system("cls");
	cout << "Заправлено" << endl;
	acc.Print_some_data();
	system("PAUSE");
	for (deque<Car>::iterator i = (acc.Deq_end() - 1); i >= acc.Deq_begin(); i--)
	{
		tmp_avto = *i;
		if (id_car == tmp_avto.id_car)
		{
			*i = avto;
			return;
		}
	}

}
void Text_logging()
{
	cout << "Войти как:" << endl;
	cout << "1. Сотрудник мастерской" << endl;
	cout << "2. Автовладелец" << endl;
	cout << "0. Выход" << endl;
}
void Text_mechanic_menu()
{
	/*В режиме сотрудника мастерской предусмотреть
	–просмотр списка автомобилей с текущим статусом
	(должна поддерживаться фильтрация и сортировка по выбранному полю),
	–операции заправки автомобиля маслом и бензином.
	Предусмотреть хранение и просмотр истории обслуживания автомобилей.*/
	cout << "1. Просмотр автомобилей с текущем статусом" << endl;
	cout << "2. Запправить масло и бензин" << endl;
	cout << "3. Поиск автомобиля" << endl;
	cout << "4. Показать автомобили в мастерской" << endl;
	cout << "0. Назад" << endl;
}
void Text_client_menu()
{
	cout << "1. Сдать автомобиль в обслуживание" << endl;
	cout << "2. Забрать автомобиль из обслуживания" << endl;
	cout << "0. Назад" << endl;
}
void Restart_file(Data_list<Car>& acc)
{
	std::ofstream _file(FILE_NAME_DATA_BASE);
	acc.Load_to_file_some_data(_file);
}

void Print(Data_list<Car>& acc)
{
	
	for (deque<Car>::iterator i = acc.Deq_begin(); i < acc.Deq_end(); i++)
	{
		acc.Help_deq_push(*i);
	}
	acc.selection_id();
	acc.Print_some_data();
	acc.Help_deq_clear();
	system("PAUSE");
}
void Mechanic_menu(Data_list<Car>& acc)
{
	while (true)
	{
		system("cls");
		Text_mechanic_menu();
		int tmp;
		tmp = Enter_value(cin);
		switch (tmp)
		{
		case 1:
			Selection(acc);
			break;
		case 2:
			Gas_and_oil(acc);
			Restart_file(acc);
			break;
		case 3:
			Search(acc);
			break;
		case 4:
			Print(acc);
			break;
		case 0:
			Restart_file(acc);
			return;
		default:
			cout << "Неверный формат" << endl;
			system("PAUSE");
			break;
		}
	}
}
void Client_menu_p1(Data_list<Car>& acc)
{
	int count = 0;
	ofstream _file(FILE_NAME_DATA_BASE, ios_base::app);
	int tmp;
	Car avto, tmp_avto;
	system("cls");
	cout << "1. Ввести данные" << endl;
	cout << "0. Отмена" << endl;
	tmp = Enter_value(cin);
	if (Come_back(tmp))
		return;
	cin.get();
	acc.Add_data();
	deque<Car>::iterator x = (acc.Deq_end() - 1);
	avto = *x;
	for (deque<Car>::iterator i = acc.Deq_begin(); i < acc.Deq_end(); i++)
	{
		tmp_avto = *i;
		if (avto.id_car == tmp_avto.id_car)
			count++;
	}
	if ((count % 2) == 1)
	{
		acc.Load_to_file(_file, x);
		system("PAUSE");
		return;
	}
	acc.Help_deq_clear();
	acc.Delete_data(x);
	cout << endl << "Автомобиль " << avto.id_car << " уже находится в мастерской" << endl << endl;
	system("PAUSE");
}

void Client_menu_p2(Data_list<Car>& acc)
{
	int count = 0;
	string id_car;
	ofstream _file(FILE_NAME_DATA_BASE, ios_base::app);
	int tmp;
	Car avto, tmp_avto;
	system("cls");
	cout << "1. Ввести данные" << endl;
	cout << "0. Отмена" << endl;
	tmp = Enter_value(cin);
	if (Come_back(tmp))
		return;
	if (acc.Deq_size() == 0)
	{
		cout << endl << "В мастерской пусто" << endl << endl;
		system("PAUSE");
		return;
	}
	system("cls");
	cout << "Введите VIN автомобиля (указан в свидетельстве о регистрации): ";
	cin.get();
	id_car = Enter_string(cin);
	for (deque<Car>::iterator i = acc.Deq_begin(); i < acc.Deq_end(); i++)
	{
		tmp_avto = *i;
		if (id_car == tmp_avto.id_car)
		{
			count++;
			avto = *i;
		}
	}
	acc.Deq_push(avto);
	deque<Car>::iterator x = (acc.Deq_end() - 1);
	if ((count % 2) == 1)
	{
		cout << "Автомобиль отдан" << endl;
		acc.Load_to_file(_file, x);
		system("PAUSE");
		return;
	}
	acc.Help_deq_clear();
	acc.Delete_data(x);
	cout << endl << "Автомобиль " << id_car << " не находится в мастерской" << endl << endl;
	system("PAUSE");
}
void Client_menu(Data_list<Car>& acc)
{	 
	while (true)
	{
		system("cls");
		Text_client_menu();
		int tmp;
		tmp = Enter_value(cin);
		switch (tmp)
		{
		case 1:
			Client_menu_p1(acc);
		break;
		case 2:
			Client_menu_p2(acc);
			break;
		case 0:
			return;
		default:
			cout << "Неверный формат" << endl;
			system("PAUSE");
			break;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool control = true;
	Data_list<Car> acc;
	int tmp;
ifstream _file(FILE_NAME_DATA_BASE, ios_base::in);
	while (control)
	{
		system("cls");
		Text_logging();
		tmp = Enter_value(cin);
		switch (tmp)
		{
		case 1:
		{
			acc.Load_from_file_some_data(_file);
			if (acc.Deq_size() == 0)
			{
				cout << "База данных пуста" << endl;
				system("PAUSE");
			}
			else
				Mechanic_menu(acc);
			break;
		}
		case 2:
			acc.Load_from_file_some_data(_file);
			Client_menu(acc);
			break;
		case 0:
			control = false;
			break;
		default:
			cout << "Неверный формат" << endl;
			system("PAUSE");
			break;
		}
	}
	system("PAUSE");
	return 0;
}