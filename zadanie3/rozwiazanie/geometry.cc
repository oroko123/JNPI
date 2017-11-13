#include <cassert>

#include "geometry.h"

using namespace std;

/* VECTOR
*
*
*/

Vector::Vector(int32_t x, int32_t y) : x_c(x), y_c(y) { }

Vector Vector::reflection() const {
	return Vector(y_c, x_c);
}

Vector &Vector::operator+=(const Vector &rhs) {
	this->x_c += rhs.x_c;
	this->y_c += rhs.y_c;
	return *this;
}


bool Vector::operator==(const Vector &rhs) const {
	return this->x_c == rhs.x_c && this->y_c == rhs.y_c;
}

/* POSITION
*
*
*/

Position::Position(int32_t x, int32_t y) : v(x, y) { }

Position Position::reflection() const {
	return Position(v.y(), v.x());
}

const Position &Position::origin() {
	static const int32_t x_origin = 0;
	static const int32_t y_origin = 0;
	static const Position ret = Position(x_origin, y_origin);
	return ret;
}

Position &Position::operator+=(const Vector &rhs) {
	this->v += rhs;
	return *this;
}

bool Position::operator==(const Position &rhs) const {
	return this->v == rhs.v;
}

/* RECTANGLE
*
*
*/

Rectangle::Rectangle(int32_t width, int32_t height, Position pos) : p(pos), v(width, height) {
	assert(width > 0);
	assert(height > 0);
}

Rectangle::Rectangle(int32_t width, int32_t height) : p(Position::origin()), v(width, height) {
	assert(width > 0);
	assert(height > 0);
}

Rectangle Rectangle::reflection() const {
	Vector v_ref = v.reflection();
	return Rectangle(v_ref.x(), v_ref.y(), p.reflection());
}

int32_t Rectangle::area() const {
	return v.x() * v.y();
}


pair<Rectangle, Rectangle> Rectangle::split_horizontally(int32_t place) const {
	assert(place > 0 && place < this->height());

	Position x = Position(this->pos().x(), place + this->pos().y());

	Rectangle a(this->width(), place, this->pos());
	Rectangle b(this->width(), this->height() - place, x);
	return make_pair(a, b);
}

pair<Rectangle, Rectangle> Rectangle::split_vertically(int32_t place) const {
	assert(place > 0 && place < this->width());

	Position x = Position(place + this->pos().x(), this->pos().y());

	Rectangle a(place, this->height(), this->pos());
	Rectangle b(this->width() - place, this->height(), x);
	return make_pair(a, b);
}

Rectangle &Rectangle::operator+=(const Vector &rhs) {
	p += rhs;
	return *this;
}

bool Rectangle::operator==(const Rectangle &rhs) const {
	return this->p == rhs.p && this->v == rhs.v;
}

/* RECTANGLES
*
*
*/

Rectangles::Rectangles() { }

Rectangles::Rectangles(vector<Rectangle> v) : rect(v) { }

size_t Rectangles::size() const {
	return rect.size();
}

const Rectangle &Rectangles::operator[](size_t i) const {
	assert(i >= 0 && i < this->rect.size());
	return rect[i];
}

Rectangle &Rectangles::operator[](size_t i) {
	assert(i >= 0 && i < this->rect.size());
	return rect[i];
}

void Rectangles::split_horizontally(uint32_t idx, int32_t place) {
	assert(idx < this->rect.size());

	pair<Rectangle, Rectangle> recs = (*this)[idx].split_horizontally(place);
	Rectangle to_insert[] = {recs.first, recs.second};

	this->rect.erase(this->rect.begin() + idx);
	this->rect.insert(this->rect.begin() + idx, to_insert, to_insert + 2);
}

void Rectangles::split_vertically(uint32_t idx, int32_t place) {
	assert(idx < this->rect.size());

	pair<Rectangle, Rectangle> recs = (*this)[idx].split_vertically(place);
	Rectangle to_insert[] = {recs.first, recs.second};

	this->rect.erase(this->rect.begin() + idx);
	this->rect.insert(this->rect.begin() + idx, to_insert, to_insert + 2);
}

Rectangles &Rectangles::operator+=(const Vector &rhs) {
	for (size_t i = 0; i < rect.size(); i++) {
		rect[i] += rhs;
	}
	return *this;
}

bool Rectangles::operator==(const Rectangles &rhs) const {
	return this->rect == rhs.rect;
}


/* TWO ARGUMENT OPERATORS
*
*
*/


const Vector operator+(const Vector &lhs, const Vector &rhs) {
	Vector cp = lhs;
	return move(cp += rhs);
}

const Vector operator+(Vector &&lhs, const Vector &rhs) {
	return (lhs += rhs);
}

const Vector operator+(const Vector &lhs, Vector &&rhs) {
	return (rhs += lhs);
}

const Vector operator+(Vector &&lhs, Vector &&rhs) {
	return (rhs += lhs);
}


const Position operator+(const Position &lhs, const Vector &rhs) {
	Position cp = lhs;
	return move(cp += rhs);
}

const Position operator+(Position &&lhs, const Vector &rhs) {
	return (lhs += rhs);
}

const Position operator+(const Vector &lhs, const Position &rhs) {
	return rhs + lhs;
}

const Position operator+(const Vector &lhs, Position &&rhs) {
	return rhs + lhs;
}


const Rectangle operator+(const Rectangle &lhs, const Vector &rhs) {
	Rectangle cp = lhs;
	return move(cp += rhs);
}

const Rectangle operator+(Rectangle &&lhs, const Vector &rhs) {
	return (lhs += rhs);
}

const Rectangle operator+(const Vector &lhs, const Rectangle &rhs) {
	return rhs + lhs;
}

const Rectangle operator+(const Vector &lhs, Rectangle &&rhs) {
	return rhs + lhs;
}


const Rectangles operator+(const Rectangles &lhs, const Vector &rhs) {
	Rectangles cp = lhs;
	return move(cp += rhs);
}

const Rectangles operator+(Rectangles &&lhs, const Vector &rhs) {
	return (lhs += rhs);
}

const Rectangles operator+(const Vector &lhs, const Rectangles &rhs) {
	return rhs + lhs;
}

const Rectangles operator+(const Vector &lhs, Rectangles &&rhs) {
	return rhs + lhs;
}

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
	assert(rect1.width() == rect2.width());
	assert(Vector(0, rect1.height()) + rect1.pos() == rect2.pos());

	Rectangle ret(rect1.width(), rect1.height() + rect2.height(), rect1.pos());
	return ret;
}

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
	assert(rect1.height() == rect2.height());
	assert(Vector(rect1.width(), 0) + rect1.pos() == rect2.pos());

	Rectangle ret(rect1.width() + rect2.width(), rect1.height(), rect1.pos());
	return ret;
}
