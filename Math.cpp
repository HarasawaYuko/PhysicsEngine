#include "Math.h"

Vec2::Vec2()
	:x(0) , y(0)
{}

Vec2::Vec2(const float x , const float y) 
	:x(x) , y(y)
{}

void Vec2::set(const float x , const float y) {
	this->x = x;
	this->y = y;
}

Vec2 Vec2::operator+(const Vec2 vec) const {
	return Vec2(x + vec.x , y + vec.y);
}

Vec2 Vec2::operator-(const Vec2 vec) const {
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator*(const float k) const {
	return Vec2(x * k, y *k);
}

Vec2 Vec2::operator/(const float k) const {
	return Vec2(x / k, y / k);
}

//二次元ベクトルの内積
float Vec2::dot(const Vec2 vec) const{
	return x * vec.x + y * vec.y;
}

//二次元ベクトルの外積
float Vec2::cross(const Vec2 vec)const{
	return x * vec.y - y * vec.x;
}

//大きさの取得
float Vec2::norm() const {
	return (float)sqrt(x * x + y * y);
}

//二乗の取得
float Vec2::squared()const {
	return (float)(x * x + y * y);
}

//２点間の距離
float Vec2::distance(const Vec2 vec) const{
	Vec2 sub = *this - vec;
	return sub.norm();
}

Vec2 Vec2::normalize()const {
	float length = norm();
	return Vec2(x / length, y / length);
}

Vec2 Vec2::rotation(const float & ang)const {
	float rad = getRad(ang);
	float x_ = x*cos(rad) - y*sin(rad);
	float y_ = x*sin(rad) + y*cos(rad);
	return Vec2(x_ , y_);
}

Vec2 Vec2::normal()const {
	return Vec2(-y ,x);
}

std::string Vec2::toString() const
{
	return std::to_string(x) + "," + std::to_string(y);
}

/**行列の実装**/

//row 列　column 行
Matrix::Matrix(const int row, const int column) 
	:row(row) , column(column)
{
	matrix.resize(row);
	for (int i = 0; i < row; i++) {
		matrix[i].resize(column);
	}
}

void Matrix::identity() {
	//単位行列のみ
	if (row != column) {
		return;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (i == j) {
				matrix[i][j] = 1.f;
			}
			else {
				matrix[i][j] = 0.f;
			}
		}
	}
}


//行列積 right...右辺
Matrix Matrix::product(const Matrix& right) {
	//行列の形を確認する
	if (this->row != right.column) {
		assert(false);
		return Matrix(0 ,0);
	}
	Matrix result = Matrix(this->column , right.row);
	for (int i = 0; i < this->column; i++) {
		for (int j = 0; j < right.row; j++) {
			float element = 0.f;
			for (int k = 0; k < this-> row ; k++) {
				element += this->matrix[k][i] * right.matrix[j][k];
			}
			result.matrix[j][i] = element;
		}
	}
	return result;
}


std::string Matrix::toString() const {
	std::string str;
	for (int i = 0; i < column ; i++) {
		for (int j = 0; j < row; j++) {
			char tmp[255];
			sprintf_s(tmp ,"%6.1f", matrix[j][i]);
			str += std::string(tmp);
			str += ",";
		}
		str += "\n";
	}
	return str;
}

Matrix Matrix::operator+(const float k)const {
	Matrix result = Matrix(row , column);
	for (int i = 0; i < row;i++) {
		for (int j = 0; j < column;j++) {
			result.matrix[i][j] = matrix[i][j] + k;
		}
	}
	return result;
}

Matrix Matrix::operator+(const Matrix& mat)const {
	Matrix result = Matrix(row, column);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			result.matrix[i][j] = matrix[i][j] + mat.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator*(const float k)const {
	Matrix result = Matrix(row , column);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			result.matrix[i][j] = matrix[i][j] * k;
		}
	}
	return result;
}

Matrix Matrix::operator*(const Matrix& mat)const {
	Matrix result = Matrix(row, column);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			result.matrix[i][j] = matrix[i][j] * mat.matrix[i][j];
		}
	}
	return result;
}

Segment::Segment(const Vec2 s , const Vec2 e) 
	:start(s) , end(e)
{}

//度数法をラジアンに変換する
float getRad(const float ang) {
	return (ang * Pi) / 180.f;
}

//ラジアンを度数法に変換する
float getDegree(const float rad) {
	return rad * (180.f / Pi);
}

//点と直線の距離
float getDistanceLine(const Vec2& point , const Segment& seg) {
	return abs((point - seg.start).cross(seg.end - seg.start)) / (seg.end - seg.start).norm();
}

/*
点と線分の距離
patternに線分と点の位置関係を記録
0...startが最短 1...endが最短　2...線分上の点が最短
*/
float getDistance(const Vec2& point, const Segment &seg , int* pattern) {
	//位置関係で場合分け
	Vec2 StoE = seg.end - seg.start;
	Vec2 StoP = point - seg.start;
	Vec2 EtoP = point - seg.end;
	if (StoE.dot(StoP) < 0) {
		*pattern = 0;
		return point.distance(seg.start);
	}
	if ((StoE * -1).dot(EtoP) < 0 ) {
		*pattern = 1;
		return point.distance(seg.end);
	}
	*pattern = 2;
	return getDistance(point , seg);
}

/*
* 点と線分の距離
* Patternなし
*/
float getDistance(const Vec2& point, const Segment& seg) {
	//位置関係で場合分け
	Vec2 StoE = seg.end - seg.start;
	Vec2 StoP = point - seg.start;
	Vec2 EtoP = point - seg.end;
	if (StoE.dot(StoP) < 0) {
		return point.distance(seg.start);
	}
	if ((StoE * -1).dot(EtoP) < 0) {
		return point.distance(seg.end);
	}
	return getDistanceLine(point, seg);
}



//cen->p0 と cen->p1 のなす角を求める(反時計回り)
float getTheta(const Vec2& cen , const Vec2& p0 , const Vec2&p1) {
	Vec2 v1 = (p0 - cen).normalize();
	Vec2 v2 = (p1 - cen).normalize();
	//時計回り
	if (v1.cross(v2) < 0) {//180 < x < 360の時
		return 2*Pi - acos(v1.dot(v2));
	}
	else {//0 < x < 180の時
		return acos(v1.dot(v2));
	}
}

//ローカル座標をワールド座標に変換
Vec2 LtoW(const Vec2& local, const Vec2& worldCen , float ang) {
	return local.rotation(ang) + worldCen;
}

//ワールド座標をローカル座標に変換
Vec2 WtoL(const Vec2 &world , const Vec2& worldCen , float ang) {
	return (world - worldCen).rotation(-ang);
}