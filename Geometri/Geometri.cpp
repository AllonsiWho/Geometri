// Geometri.cpp 

#define delimetr "\n---------------------------------------------------\n"

#include <iostream>
#include <locale.h>
#include<Windows.h>

using namespace std;
namespace Geometry{
enum Color {
	/*Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue,
	LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White*/
	red=0x000000FF,
	green=0x0000FF00,
	blue=0x00FF0000,
	yellow=0x0000FFFF,
	white=0x00FFFFFF
};


void SetColor(Color text, Color background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получает дискриптор активного окна
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void SetCursor(int x, int y)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//получает дискриптор активного окна
	COORD myCoords = { x,y };//инициализируем передаваемыми значениями объект координат
	SetConsoleCursorPosition(hStdOut, myCoords);
}


class Shape
{
protected:
	Color color;
	int start_x;
	int start_y;
	int line_width;
public:
	int get_start_x()const
	{
		return start_x;
	}
	int get_start_y()const
	{
		return start_y;
	}
	int get_line_width()const
	{
		return line_width;
	}
	void set_start_x(int start_x)
	{
		if (start_x < 10)start_x = 10;
		if (start_x > 500)start_x = 500;
		this->start_x = start_x;
	}
	void set_start_y(int start_y)
	{
		if (start_y < 10)start_y = 10;
		if (start_y > 500)start_y = 500;
		this->start_x = start_y;
	}
	void set_line_width(int line_width)
	{
		if (line_width < 5)line_width = 5;
		if (line_width > 20)line_width = 20;
		this->line_width = line_width;
	}
	Shape(Color color,int start_x,int start_y,int line_width) :color(color) 
	{
			
	};
	~Shape() {}
	virtual double get_area()const = 0;
	virtual double get_perimetr()const = 0;
	virtual void draw()const = 0;

	virtual void info()const
	{
		cout << "Площадь фигуры= " << get_area() << endl;
		cout << "Периметр фигуры= " << get_perimetr() << endl;
		draw();

	}
};

//class Square : public Shape
//{
//	double side;
//public:
//	double get_side()const
//	{
//		return side;
//	}
//	void set_side(double side)
//	{
//		if (side < 5)side = 5;
//		if (side > 20)side = 20;
//		this->side = side;
//	}
//
//	// Constructors
//	Square(double side, Color color) : Shape(color)
//	{
//		set_side(side);
//		
//	}
//	~Square()
//	{
//
//	}
//	
//	double get_area()const override
//	{
//		
//		return side * side;
//	}
//
//	double get_perimetr()const override
//	{
//		cout << "Периметр квадрата= " << side * 4 << endl;
//		return 4 * side;
//	}
//	void draw()const override
//	{
//		for (int i = 0; i < side; i++)
//		{
//			for (int j = 0; j < side; j++)
//			{
//				//SetColor(color,color);
//				cout << "# ";
//				//SetColor(White, Black);
//			}
//			cout << endl;
//		}
//	}
//	void info()const
//	{
//		cout << typeid(*this).name() << endl;
//		cout << "Длина стороны квадрата= " << side << endl;
//		Shape::info();
//	}
//};
class Rectangle :public Shape
{
	double side1, side2;
public:
	double get_side_1()const
	{
		return side1;
	}
	double get_side_2()const
	{
		return side2;
	}
	void set_side_1(double side1)
	{
		if (side1 < 5)side1 = 5;
		if (side1 > 20)side1 = 20;
		this->side1 = side1;
	}
	void set_side_2(double side2)
	{
		if (side2 < 5)side2 = 5;
		if (side2 > 20)side2 = 20;
		this->side2 = side2;
	}
	Rectangle(double side1, double side2, Color color) :Shape(color)
	{
		set_side_1(side1);
		set_side_2(side2);
	}
	~Rectangle(){}

	double get_area()const override
	{
		return side1 * side2;
	}
	double get_perimetr()const override
	{
		return(side1 + side2) * 2;
	}
	void draw()const override
	{
		/*for (int i = 0; i < side1; i++)
		{
			for (int j = 0; j < side2; j++)
			{
				SetColor(color, color);
				cout << "# ";
				SetColor(White, Black);
			}
			cout << endl;
		}*/

		HWND hwnd = GetConsoleWindow();//Получаем обработчик окна консоли
		HDC hdc = GetDC(hwnd);//Получаем контекс устройства окна устрофства
		//Контекс устройства - это тоб на чем будем рисовать
		HPEN hPen = CreatePen(PS_SOLID, 5, color);
		//Pen(Карандаш) рисует контур фигуры,
		//Ps_SOLID-сплошная линия
		//5- толщина линии 5 пикселов

		HBRUSH hBrush = CreateSolidBrush(color);
		//Brush - это кисть, рисует заливку замкнутой фигуры.

		//Выбираем чем и на чем рисовать
		SelectObject(hdc,hPen);
		SelectObject(hdc,hBrush);
		//Когда все инструменты созданы и выбраны, можно вызвать функцию,
		//для рисования нужно фигуры
		::Rectangle(hdc, 300, 100, 600, 300);



		DeleteObject(hPen);
		DeleteObject(hBrush);



		ReleaseDC(hwnd, hdc);//Освыобождаем контекст устройства
	}
	void info()const
	{
		cout << typeid(*this).name() << endl;
		cout << "Сторона 1: " << side1 << endl;
		cout << "Сторона 2: " << side2 << endl;
		Shape::info();
	}

}; 
class Square :Rectangle
{
public:
	Square(double side, Color color) :Rectangle(side, side, color) {}

	~Square(){}




};



}



int main()
{
	setlocale(LC_ALL, "RUS");

	Geometry::Square obj(10, Geometry::red);
	
	//delimetr;
	//obj.info();
	Geometry::Rectangle rect(5, 12, Geometry::yellow);
	rect.info();



}

