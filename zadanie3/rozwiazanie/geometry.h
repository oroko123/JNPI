#ifndef GEOMETRY_GEOMETRY_H
#define GEOMETRY_GEOMETRY_H

#include <vector>
#include <cstdint>
#include <cstddef>

class Vector {
	int32_t x_c, y_c;
public:
	Vector(int32_t x, int32_t y);

	Vector(const Vector &other) = default;
	
	Vector(Vector &&other) = default;
	
	Vector &operator=(const Vector &other) = default;
	
	Vector &operator=(Vector &&other) = default;

	int32_t x() const { return x_c; }
	int32_t y() const { return y_c; }

	Vector reflection() const;

	Vector &operator+=(const Vector &rhs);
	bool operator==(const Vector &rhs) const;

};


class Position {
	Vector v;
public:
	Position(int32_t x, int32_t y);
	
	Position(const Position &other) = default;
	
	Position(Position &&other) = default;
	
	Position &operator=(const Position &other) = default;
	
	Position &operator=(Position &&other) = default;

	static const Position &origin();

	int32_t x() const { return v.x(); }
	int32_t y() const { return v.y(); }

	Position reflection() const;

	Position &operator+=(const Vector &rhs);
	bool operator==(const Position &rhs) const;
};

class Rectangle {
	Position p;
	Vector v;
public:
	Rectangle(int32_t width, int32_t height, Position pos);
	Rectangle(int32_t width, int32_t height);
	
	Rectangle(const Rectangle &other) = default;
	
	Rectangle(Rectangle &&other) = default;
	
	Rectangle &operator=(const Rectangle &other) = default;
	
	Rectangle &operator=(Rectangle &&other) = default;

	int32_t width() const { return v.x(); }
	int32_t height() const { return v.y(); }
	Position pos() const { return p; }

	Rectangle reflection() const;
	int32_t area() const;
	std::pair<Rectangle, Rectangle> split_horizontally(int32_t place) const;
	std::pair<Rectangle, Rectangle> split_vertically(int32_t place) const;

	Rectangle &operator+=(const Vector &rhs);
	bool operator==(const Rectangle &rhs) const;
};

class Rectangles {
	std::vector<Rectangle> rect;
public:
	Rectangles();
	Rectangles(std::vector<Rectangle> v);
	
	Rectangles(const Rectangles &other) = default;
	
	Rectangles(Rectangles &&other) = default;
	
	Rectangles &operator=(const Rectangles &other) = default;
	
	Rectangles &operator=(Rectangles &&other) = default;

	size_t size() const;
	void split_horizontally(uint32_t idx, int32_t place);
	void split_vertically(uint32_t idx, int32_t place);

	const Rectangle &operator[](size_t i) const;
	Rectangle &operator[](size_t i);

	Rectangles &operator+=(const Vector &rhs);
	bool operator==(const Rectangles &rhs) const;
};

const Vector operator+(const Vector &lhs, const Vector &rhs);

const Vector operator+(Vector &&lhs, const Vector &rhs);

const Vector operator+(const Vector &lhs, Vector &&rhs);

const Vector operator+(Vector &&lhs, Vector &&rhs);


const Position operator+(const Position &lhs, const Vector &rhs);

const Position operator+(Position &&lhs, const Vector &rhs);

const Position operator+(const Vector &lhs, const Position &rhs);

const Position operator+(const Vector &lhs, Position &&rhs);


const Rectangle operator+(const Rectangle &lhs, const Vector &rhs);

const Rectangle operator+(Rectangle &&lhs, const Vector &rhs);

const Rectangle operator+(const Vector &lhs, const Rectangle &rhs);

const Rectangle operator+(const Vector &lhs, Rectangle &&rhs);


const Rectangles operator+(const Rectangles &lhs, const Vector &rhs);

const Rectangles operator+(Rectangles &&lhs, const Vector &rhs);

const Rectangles operator+(const Vector &lhs, const Rectangles &rhs);

const Rectangles operator+(const Vector &lhs, Rectangles &&rhs);


Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

#endif //GEOMETRY_GEOMETRY_H
