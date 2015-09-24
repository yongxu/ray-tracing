#include<iostream>

#include"numerics.h"
#include"Parser.h"
#include"Scene.h"

int main() {
	Vec3 t{ 1,2,3 };
	Vec3 t2{ 1,2,3 };
	std::cout << "!!!!" << (t*t2).y << "\n";

	Parser p("input3.txt");
	Scene s(p);
	auto ctx = p.getContext();
	system("pause");
	return 0;
}