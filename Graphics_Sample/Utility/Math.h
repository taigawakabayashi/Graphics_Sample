#pragma once
#ifndef MATH_H
#define MATH_H

#include <DirectXMath.h>
#include <cmath>
#include <functional>

#pragma warning( disable : 4201 )

#define PI_F (3.141592654f)

using namespace DirectX;

#pragma region Vector2Int

struct Vector2Int {

public:

	int32_t x;
	int32_t y;

	Vector2Int() = default;

	Vector2Int(const Vector2Int&) = default;
	Vector2Int& operator=(const Vector2Int&) = default;

	Vector2Int(Vector2Int&&) = default;
	Vector2Int& operator=(Vector2Int&&) = default;

	Vector2Int(const XMINT2& _value) {

		this->x = _value.x;
		this->y = _value.y;
	}
	Vector2Int& operator= (const XMINT2& _value) {

		this->x = _value.x;
		this->y = _value.y;

		return *this;
	}

	static Vector2Int zero() {

		return Vector2Int(0, 0);
	}

	static Vector2Int one() {

		return Vector2Int(1, 1);
	}

	static Vector2Int up() {

		return Vector2Int(0, 1);
	}

	static Vector2Int down() {

		return Vector2Int(0, -1);
	}

	static Vector2Int left() {

		return Vector2Int(-1, 0);
	}

	static Vector2Int right() {

		return Vector2Int(1, 0);
	}

	operator XMINT2() {

		return XMINT2(x, y);
	}

	bool operator!=(Vector2Int _v) {

		return (this->x != _v.x || this->y != _v.y);
	}

	bool operator==(Vector2Int _v) {

		return (this->x == _v.x && this->y == _v.y);
	}

	Vector2Int& operator+=(const Vector2Int& _v) {

		this->x += _v.x;
		this->y += _v.y;

		return *this;
	}

	Vector2Int& operator-=(const Vector2Int& _v) {

		this->x -= _v.x;
		this->y -= _v.y;

		return *this;
	}

	Vector2Int& operator*=(const Vector2Int& _v) {

		this->x *= _v.x;
		this->y *= _v.y;

		return *this;
	}

	Vector2Int& operator*=(const int32_t& _v) {

		this->x *= _v;
		this->y *= _v;

		return *this;
	}

	Vector2Int& operator/=(const Vector2Int& _v) {

		if (_v.x != 0) {

			this->x /= _v.x;
		}
		else {

			this->x = static_cast<int32_t>(std::nan(""));
		}

		if (_v.y != 0) {

			this->y /= _v.y;
		}
		else {

			this->y = static_cast<int32_t>(std::nan(""));
		}

		return *this;
	}

	Vector2Int& operator/=(const int32_t& _i) {

		if (_i != 0) {

			this->x /= _i;
			this->y /= _i;
		}
		else {

			this->x /= static_cast<int32_t>(std::nan(""));
			this->y /= static_cast<int32_t>(std::nan(""));
		}

		return *this;
	}

	// 長さ
	int32_t Length() {

		return static_cast<int32_t>(sqrt((x * x) + (y * y)));
	}

	constexpr Vector2Int(int32_t _x, int32_t _y) : x(_x), y(_y) {}
};

Vector2Int operator+ (const XMINT2& _x, const Vector2Int& _v);
Vector2Int operator+ (const Vector2Int& _v, const XMINT2& _x);
Vector2Int operator+ (const Vector2Int& _v1, const Vector2Int& _v2);

Vector2Int operator- (const XMINT2& _x, const Vector2Int& _v);
Vector2Int operator- (const Vector2Int& _v, const XMINT2& _x);
Vector2Int operator- (const Vector2Int& _v1, const Vector2Int& _v2);

Vector2Int operator* (const XMINT2& _x, const Vector2Int& _v);
Vector2Int operator* (const Vector2Int& _v, const XMINT2& _x);
Vector2Int operator* (const int32_t& _i, const Vector2Int& _v);
Vector2Int operator* (const Vector2Int& _v, const int32_t& _i);
Vector2Int operator* (const Vector2Int& _v1, const Vector2Int& _v2);

Vector2Int operator/ (const XMINT2& _x, const Vector2Int& _v);
Vector2Int operator/ (const Vector2Int& _v, const XMINT2& _x);
Vector2Int operator/ (const Vector2Int& _v, const int32_t& _i);
Vector2Int operator/ (const Vector2Int& _v1, const Vector2Int& _v2);
#pragma endregion

#pragma region Vector3Int

struct Vector3Int {

public:

	int32_t x;
	int32_t y;
	int32_t z;

	Vector3Int() = default;

	Vector3Int(const Vector3Int&) = default;
	Vector3Int& operator=(const Vector3Int&) = default;

	Vector3Int(Vector3Int&&) = default;
	Vector3Int& operator=(Vector3Int&&) = default;

	Vector3Int(const XMINT3& _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;
	}
	Vector3Int& operator= (const XMINT3& _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;

		return *this;
	}

	static Vector3Int zero() {

		return Vector3Int(0, 0, 0);
	}

	static Vector3Int one() {

		return Vector3Int(1, 1, 1);
	}

	static Vector3Int up() {

		return Vector3Int(0, 1, 0);
	}

	static Vector3Int down() {

		return Vector3Int(0, -1, 0);
	}

	static Vector3Int left() {

		return Vector3Int(-1, 0, 0);
	}

	static Vector3Int right() {

		return Vector3Int(1, 0, 0);
	}

	operator XMINT3() {

		return XMINT3(x, y, z);
	}

	bool operator!=(Vector3Int _v) {

		return (this->x != _v.x || this->y != _v.y || this->z != _v.z);
	}

	bool operator==(Vector3Int _v) {

		return (this->x == _v.x && this->y == _v.y && this->z == _v.z);
	}

	Vector3Int& operator+=(const Vector3Int& _v) {

		this->x += _v.x;
		this->y += _v.y;
		this->z += _v.z;

		return *this;
	}

	Vector3Int& operator-=(const Vector3Int& _v) {

		this->x -= _v.x;
		this->y -= _v.y;
		this->z -= _v.z;

		return *this;
	}

	Vector3Int& operator*=(const Vector3Int& _v) {

		this->x *= _v.x;
		this->y *= _v.y;
		this->z *= _v.z;

		return *this;
	}

	Vector3Int& operator*=(const int32_t& _i) {

		this->x *= _i;
		this->y *= _i;
		this->z *= _i;

		return *this;
	}

	Vector3Int& operator/=(const Vector3Int& _v) {

		if (_v.x != 0) {

			this->x /= _v.x;
		}
		else {

			this->x = static_cast<int32_t>(std::nan(""));
		}

		if (_v.y != 0) {

			this->y /= _v.y;
		}
		else {

			this->y = static_cast<int32_t>(std::nan(""));
		}

		if (_v.z != 0) {

			this->z /= _v.z;
		}
		else {

			this->z = static_cast<int32_t>(std::nan(""));
		}

		return *this;
	}

	Vector3Int& operator/=(const int32_t& _i) {

		if (_i != 0) {

			this->x /= _i;
			this->y /= _i;
			this->z /= _i;
		}
		else {

			this->x /= static_cast<int32_t>(std::nan(""));
			this->y /= static_cast<int32_t>(std::nan(""));
			this->z /= static_cast<int32_t>(std::nan(""));
		}

		return *this;
	}

	// 長さ
	int32_t Length() {

		return static_cast<int32_t>(sqrt((x * x) + (y * y) + (z * z)));
	}

	constexpr Vector3Int(int32_t _x, int32_t _y, int32_t _z) : x(_x), y(_y), z(_z) {}
	constexpr Vector3Int(int32_t _x, int32_t _y) : x(_x), y(_y), z(0) {}
};

Vector3Int operator+ (const XMINT3& _x, const Vector3Int& _v);
Vector3Int operator+ (const Vector3Int& _v, const XMINT3& _x);
Vector3Int operator+ (const Vector3Int& _v1, const Vector3Int& _v2);

Vector3Int operator- (const XMINT3& _x, const Vector3Int& _v);
Vector3Int operator- (const Vector3Int& _v, const XMINT3& _x);
Vector3Int operator- (const Vector3Int& _v1, const Vector3Int& _v2);

Vector3Int operator* (const XMINT3& _x, const Vector3Int& _v);
Vector3Int operator* (const Vector3Int& _v, const XMINT3& _x);
Vector3Int operator* (const int32_t& _i, const Vector3Int& _v);
Vector3Int operator* (const Vector3Int& _v, const int32_t& _i);
Vector3Int operator* (const Vector3Int& _v1, const Vector3Int& _v2);

Vector3Int operator/ (const XMINT3& _x, const Vector3Int& _v);
Vector3Int operator/ (const Vector3Int& _v, const XMINT3& _x);
Vector3Int operator/ (const Vector3Int& _v, const int32_t& _i);
Vector3Int operator/ (const Vector3Int& _v1, const Vector3Int& _v2);
#pragma endregion

#pragma region Vector2

struct Vector2 {

public:

	float x;
	float y;

	Vector2() = default;

	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2(const Vector2Int& _value) {

		this->x = static_cast<float>(_value.x);
		this->y = static_cast<float>(_value.y);
	}
	Vector2& operator= (const Vector2Int& _value) {

		this->x = static_cast<float>(_value.x);
		this->y = static_cast<float>(_value.y);

		return *this;
	}

	Vector2(const XMFLOAT2& _value) {

		this->x = _value.x;
		this->y = _value.y;
	}
	Vector2& operator= (const XMFLOAT2& _value) {

		this->x = _value.x;
		this->y = _value.y;

		return *this;
	}

	Vector2(const XMVECTOR& _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];
	}
	Vector2& operator= (const XMVECTOR& _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];

		return *this;
	}

	static Vector2 zero() {

		return Vector2(0.0f, 0.0f);
	}

	static Vector2 one() {

		return Vector2(1.0f, 1.0f);
	}

	static Vector2 up() {

		return Vector2(0.0f, 1.0f);
	}

	static Vector2 down() {

		return Vector2(0.0f, -1.0f);
	}

	static Vector2 left() {

		return Vector2(-1.0f, 0.0f);
	}

	static Vector2 right() {

		return Vector2(1.0f, 0.0f);
	}

	operator XMFLOAT2() {

		return XMFLOAT2(x, y);
	}

	operator XMVECTOR() {

		return XMVECTOR{ x, y };
	}

	bool operator!=(Vector2 _v) {

		return (this->x != _v.x || this->y != _v.y);
	}

	bool operator==(Vector2 _v) {

		return (this->x == _v.x && this->y == _v.y);
	}

	Vector2& operator+=(const Vector2& _v) {

		this->x += _v.x;
		this->y += _v.y;

		return *this;
	}

	Vector2& operator-=(const Vector2& _v) {

		this->x -= _v.x;
		this->y -= _v.y;

		return *this;
	}

	Vector2& operator*=(const Vector2& _v) {

		this->x *= _v.x;
		this->y *= _v.y;

		return *this;
	}

	Vector2& operator*=(const float& _v) {

		this->x *= _v;
		this->y *= _v;

		return *this;
	}

	Vector2& operator/=(const Vector2& _v) {

		if (_v.x != 0.0f) {

			this->x /= _v.x;
		}
		else {

			this->x = static_cast<float>(std::nan(""));
		}

		if (_v.y != 0.0f) {

			this->y /= _v.y;
		}
		else {

			this->y = static_cast<float>(std::nan(""));
		}

		return *this;
	}

	Vector2& operator/=(const float& _v) {

		if (_v != 0.0f) {

			this->x /= _v;
			this->y /= _v;
		}
		else {

			this->x /= static_cast<float>(std::nan(""));
			this->y /= static_cast<float>(std::nan(""));
		}

		return *this;
	}

	// 長さ
	float Length() {

		return sqrt((x * x) + (y * y));
	}

	// 正規化
	bool Normalize() {

		float length = this->Length();

		if (length != 0) {

			x /= length;
			y /= length;

			return true;
		}
		else {

			return false;
		}
	}

	// 内積(正規化済み)
	float NormalizedDot(Vector2 _v) {

		Vector2 temp = *this;

		temp.Normalize();
		_v.Normalize();

		return (temp.x * _v.x) + (temp.y * _v.y);
	}

	// 内積
	float Dot(Vector2 _v) {

		return (x * _v.x) + (y * _v.y);
	}

	// なす角(度数角度)
	float DegreesAngle(Vector2 _v) {

		return XMConvertToDegrees(acosf(NormalizedDot(_v)));
	}

	// なす角(ラジアン角度)
	float RadianAngle(Vector2 _v) {

		return acosf(NormalizedDot(_v));
	}

	constexpr Vector2(float _x, float _y) : x(_x), y(_y) {}
};

Vector2 operator+ (const XMFLOAT2& _x, const Vector2& _v);
Vector2 operator+ (const Vector2& _v, const XMFLOAT2& _x);
Vector2 operator+ (const Vector2& _v1, const Vector2& _v2);

Vector2 operator- (const XMFLOAT2& _x, const Vector2& _v);
Vector2 operator- (const Vector2& _v, const XMFLOAT2& _x);
Vector2 operator- (const Vector2& _v1, const Vector2& _v2);

Vector2 operator* (const XMFLOAT2& _x, const Vector2& _v);
Vector2 operator* (const Vector2& _v, const XMFLOAT2& _x);
Vector2 operator* (const float& _f, const Vector2& _v);
Vector2 operator* (const Vector2& _v, const float& _f);
Vector2 operator* (const Vector2& _v1, const Vector2& _v2);

Vector2 operator/ (const XMFLOAT2& _x, const Vector2& _v);
Vector2 operator/ (const Vector2& _v, const XMFLOAT2& _x);
Vector2 operator/ (const Vector2& _v, const float& _f);
Vector2 operator/ (const Vector2& _v1, const Vector2& _v2);
#pragma endregion

#pragma region Vector3

struct Vector3 {

public:

	float x;
	float y;
	float z;

	Vector3() = default;

	Vector3(const Vector3&) = default;
	Vector3& operator=(const Vector3&) = default;

	Vector3(Vector3&&) = default;
	Vector3& operator=(Vector3&&) = default;

	Vector3(const Vector3Int& _value) {

		this->x = static_cast<float>(_value.x);
		this->y = static_cast<float>(_value.y);
		this->z = static_cast<float>(_value.z);
	}
	Vector3& operator= (const Vector3Int& _value) {

		this->x = static_cast<float>(_value.x);
		this->y = static_cast<float>(_value.y);
		this->z = static_cast<float>(_value.z);

		return *this;
	}

	Vector3(const XMFLOAT3& _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;
	}
	Vector3& operator= (const XMFLOAT3& _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;

		return *this;
	}

	Vector3(const XMVECTOR& _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];
		this->z = _value.m128_f32[2];
	}
	Vector3& operator= (const XMVECTOR& _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];
		this->z = _value.m128_f32[2];

		return *this;
	}

	static Vector3 zero() noexcept {

		return Vector3(0.0f, 0.0f, 0.0f);
	}

	static Vector3 one() {

		return Vector3(1.0f, 1.0f, 1.0f);
	}

	static Vector3 up() {

		return Vector3(0.0f, 1.0f, 0.0f);
	}

	static Vector3 down() {

		return Vector3(0.0f, -1.0f, 0.0f);
	}

	static Vector3 left() {

		return Vector3(-1.0f, 0.0f, 0.0f);
	}

	static Vector3 right() {

		return Vector3(1.0f, 0.0f, 0.0f);
	}

	static Vector3 forward() {

		return Vector3(0.0f, 0.0f, 1.0f);
	}

	static Vector3 back() {

		return Vector3(0.0f, 0.0f, -1.0f);
	}

	operator XMFLOAT3() {

		return XMFLOAT3(x, y, z);
	}

	operator XMVECTOR() {

		return XMVECTOR{ x, y, z };
	}

	bool operator!=(Vector3 _v) {

		return (this->x != _v.x || this->y != _v.y || this->z != _v.z);
	}

	bool operator==(Vector3 _v) {

		return (this->x == _v.x && this->y == _v.y && this->z == _v.z);
	}

	Vector3& operator+=(const Vector3& _v) {

		this->x += _v.x;
		this->y += _v.y;
		this->z += _v.z;

		return *this;
	}

	Vector3& operator-=(const Vector3& _v) {

		this->x -= _v.x;
		this->y -= _v.y;
		this->z -= _v.z;

		return *this;
	}

	Vector3& operator*=(const Vector3& _v) {

		this->x *= _v.x;
		this->y *= _v.y;
		this->z *= _v.z;

		return *this;
	}

	Vector3& operator*=(const float& _v) {

		this->x *= _v;
		this->y *= _v;
		this->z *= _v;

		return *this;
	}

	Vector3& operator/=(const Vector3& _v) {

		if (_v.x != 0.0f) {

			this->x /= _v.x;
		}
		else {

			this->x = static_cast<float>(std::nan(""));
		}

		if (_v.y != 0.0f) {

			this->y /= _v.y;
		}
		else {

			this->y = static_cast<float>(std::nan(""));
		}

		if (_v.z != 0.0f) {

			this->z /= _v.z;
		}
		else {

			this->z = static_cast<float>(std::nan(""));
		}

		return *this;
	}

	Vector3& operator/=(const float& _f) {

		if (_f != 0.0f) {

			this->x /= _f;
			this->y /= _f;
			this->z /= _f;
		}
		else {

			this->x /= static_cast<float>(std::nan(""));
			this->y /= static_cast<float>(std::nan(""));
			this->z /= static_cast<float>(std::nan(""));
		}

		return *this;
	}

	// 長さ
	float Length() {

		return sqrt((x * x) + (y * y) + (z * z));
	}

	// 正規化
	bool Normalize() {

		float length = this->Length();

		if (length != 0) {

			x /= length;
			y /= length;
			z /= length;

			return true;
		}
		else {

			return false;
		}
	}

	// 内積(正規化済み)
	float NormalizedDot(Vector3 _v) {

		Vector3 temp = *this;

		temp.Normalize();
		_v.Normalize();

		return (temp.x * _v.x) + (temp.y * _v.y) + (temp.z * _v.z);
	}

	// 内積
	float Dot(Vector3 _v) {

		return (x * _v.x) + (y * _v.y) + (z * _v.z);
	}

	//　外積(正規化済み)
	Vector3 NormalizedCloss(Vector3 _v) {

		Vector3 closs = Vector3::zero();
		Vector3 temp = *this;

		temp.Normalize();
		_v.Normalize();

		closs.x = (temp.y * _v.z - temp.z * _v.y);
		closs.y = (temp.z * _v.x - temp.x * _v.z);
		closs.z = (temp.x * _v.y - temp.y * _v.x);

		return closs;
	}

	// 外積
	Vector3 Closs(Vector3 _v) {

		Vector3 closs = Vector3::zero();

		closs.x = (y * _v.z - z * _v.y);
		closs.y = (z * _v.x - x * _v.z);
		closs.z = (x * _v.y - y * _v.x);

		return closs;
	}

	// なす角(度数角度)
	float DegreesAngle(Vector3 _v) {

		return XMConvertToDegrees(acosf(NormalizedDot(_v)));
	}

	// なす角(ラジアン角度)
	float RadianAngle(Vector3 _v) {

		return acosf(NormalizedDot(_v));
	}

	constexpr Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	constexpr Vector3(float _x, float _y) : x(_x), y(_y), z(0) {}
};

Vector3 operator+ (const XMFLOAT3& _x, const Vector3& _v);
Vector3 operator+ (const Vector3& _v, const XMFLOAT3& _x);
Vector3 operator+ (const Vector3& _v1, const Vector3& _v2);

Vector3 operator- (const XMFLOAT3& _x, const Vector3& _v);
Vector3 operator- (const Vector3& _v, const XMFLOAT3& _x);
Vector3 operator- (const Vector3& _v1, const Vector3& _v2);

Vector3 operator* (const XMFLOAT3& _x, const Vector3& _v);
Vector3 operator* (const Vector3& _v, const XMFLOAT3& _x);
Vector3 operator* (const float& _f, const Vector3& _v);
Vector3 operator* (const Vector3& _v, const float& _f);
Vector3 operator* (const Vector3& _v1, const Vector3& _v2);

Vector3 operator/ (const XMFLOAT3& _x, const Vector3& _v);
Vector3 operator/ (const Vector3& _v, const XMFLOAT3& _x);
Vector3 operator/ (const Vector3& _v, const float& _f);
Vector3 operator/ (const Vector3& _v1, const Vector3& _v2);
#pragma endregion

#pragma region Vector4

struct Vector4 {

public:

	float x;
	float y;
	float z;
	float w;

	Vector4() = default;

	Vector4(const Vector4&) = default;
	Vector4& operator=(const Vector4&) = default;

	Vector4(Vector4&&) = default;
	Vector4& operator=(Vector4&&) = default;

	Vector4(const XMFLOAT4& _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;
		this->w = _value.w;
	}
	Vector4& operator= (const XMFLOAT4& _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;
		this->w = _value.w;

		return *this;
	}

	Vector4(const XMVECTOR& _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];
		this->z = _value.m128_f32[2];
		this->w = _value.m128_f32[3];
	}
	Vector4& operator= (const XMVECTOR& _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];
		this->z = _value.m128_f32[2];
		this->w = _value.m128_f32[3];

		return *this;
	}

	static Vector4 zero() {

		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	static Vector4 one() {

		return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	operator XMFLOAT4() {

		return XMFLOAT4(x, y, z, w);
	}

	operator XMVECTOR() {

		return XMVECTOR{ x, y, z,w };
	}

	bool operator!=(Vector4 _v) {

		return (this->x != _v.x || this->y != _v.y || this->z != _v.z || this->w != _v.w);
	}

	bool operator==(Vector4 _v) {

		return (this->x == _v.x && this->y == _v.y && this->z == _v.z && this->w == _v.w);
	}

	Vector4& operator+=(const Vector4& _v) {

		this->x += _v.x;
		this->y += _v.y;
		this->z += _v.z;
		this->w += _v.w;

		return *this;
	}

	Vector4& operator-=(const Vector4& _v) {

		this->x -= _v.x;
		this->y -= _v.y;
		this->z -= _v.z;
		this->w -= _v.w;

		return *this;
	}

	Vector4& operator*=(const Vector4& _v) {

		this->x *= _v.x;
		this->y *= _v.y;
		this->z *= _v.z;
		this->w *= _v.w;

		return *this;
	}

	Vector4& operator*=(const float& _f) {

		this->x *= _f;
		this->y *= _f;
		this->z *= _f;
		this->w *= _f;

		return *this;
	}

	Vector4& operator/=(const Vector4& _v) {

		if (_v.x != 0.0f) {

			this->x /= _v.x;
		}
		else {

			this->x = static_cast<float>(std::nan(""));
		}

		if (_v.y != 0.0f) {

			this->y /= _v.y;
		}
		else {

			this->y = static_cast<float>(std::nan(""));
		}

		if (_v.z != 0.0f) {

			this->z /= _v.z;
		}
		else {

			this->z = static_cast<float>(std::nan(""));
		}

		if (_v.w != 0.0f) {

			this->w /= _v.w;
		}
		else {

			this->w = static_cast<float>(std::nan(""));
		}

		return *this;
	}

	Vector4& operator/=(const float& _f) {

		if (_f != 0.0f) {

			this->x /= _f;
			this->y /= _f;
			this->z /= _f;
			this->w /= _f;
		}
		else {

			this->x /= static_cast<float>(std::nan(""));
			this->y /= static_cast<float>(std::nan(""));
			this->z /= static_cast<float>(std::nan(""));
			this->w /= static_cast<float>(std::nan(""));
		}

		return *this;
	}

	// 長さ
	float Length() {

		return sqrt((x * x) + (y * y) + (z * z));
	}

	// 正規化
	bool Normalize() {

		float length = this->Length();

		if (length != 0) {

			x /= length;
			y /= length;
			z /= length;

			return true;
		}
		else {

			return false;
		}
	}

	// 内積(正規化済み)
	float NormalizedDot(Vector4 _v) {

		Vector4 temp = *this;

		temp.Normalize();
		_v.Normalize();

		return (temp.x * _v.x) + (temp.y * _v.y) + (temp.z * _v.z);
	}

	// 内積
	float Dot(Vector4 _v) {

		return (x * _v.x) + (y * _v.y) + (z * _v.z);
	}

	// なす角(度数角度)
	float DegreesAngle(Vector4 _v) {

		return XMConvertToDegrees(acosf(NormalizedDot(_v)));
	}

	// なす角(ラジアン角度)
	float RadianAngle(Vector4 _v) {

		return acosf(NormalizedDot(_v));
	}

	constexpr Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	constexpr Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(0) {}
	constexpr Vector4(float _x, float _y) : x(_x), y(_y), z(0), w(0) {}
};

Vector4 operator+ (const XMFLOAT4& _x, const Vector4& _v);
Vector4 operator+ (const Vector4& _v, const XMFLOAT4& _x);
Vector4 operator+ (const Vector4& _v1, const Vector4& _v2);

Vector4 operator- (const XMFLOAT4& _x, const Vector4& _v);
Vector4 operator- (const Vector4& _v, const XMFLOAT4& _x);
Vector4 operator- (const Vector4& _v1, const Vector4& _v2);

Vector4 operator* (const XMFLOAT4& _x, const Vector4& _v);
Vector4 operator* (const Vector4& _v, const XMFLOAT4& _x);
Vector4 operator* (const float& _f, const Vector4& _v);
Vector4 operator* (const Vector4& _v, const float& _f);
Vector4 operator* (const Vector4& _v1, const Vector4& _v2);

Vector4 operator/ (const XMFLOAT4& _x, const Vector4& _v);
Vector4 operator/ (const Vector4& _v, const XMFLOAT4& _x);
Vector4 operator/ (const Vector4& _v, const float& _f);
Vector4 operator/ (const Vector4& _v1, const Vector4& _v2);
#pragma endregion

#pragma region Matrix4x4

struct Matrix4x4
{
public:

	union
    {
        float m[4][4];

        struct
        {
            float m_11, m_12, m_13, m_14;
            float m_21, m_22, m_23, m_24;
            float m_31, m_32, m_33, m_34;
            float m_41, m_42, m_43, m_44;
        };
    };

	Matrix4x4() = default;

	Matrix4x4(const Matrix4x4&) = default;
	Matrix4x4& operator=(const Matrix4x4&) = default;

	Matrix4x4(Matrix4x4&&) = default;
	Matrix4x4& operator=(Matrix4x4&&) = default;

	Matrix4x4(const XMFLOAT4X4& _value)
	{
		m_11 = _value._11;
		m_12 = _value._12;
		m_13 = _value._13;
		m_14 = _value._14;

		m_21 = _value._21;
		m_22 = _value._22;
		m_23 = _value._23;
		m_24 = _value._24;

		m_31 = _value._31;
		m_32 = _value._32;
		m_33 = _value._33;
		m_34 = _value._34;

		m_41 = _value._41;
		m_42 = _value._42;
		m_43 = _value._43;
		m_44 = _value._44;
	}
	Matrix4x4& operator=(const XMFLOAT4X4 _value) 
	{
		m_11 = _value._11;
		m_12 = _value._12;
		m_13 = _value._13;
		m_14 = _value._14;

		m_21 = _value._21;
		m_22 = _value._22;
		m_23 = _value._23;
		m_24 = _value._24;

		m_31 = _value._31;
		m_32 = _value._32;
		m_33 = _value._33;
		m_34 = _value._34;

		m_41 = _value._41;
		m_42 = _value._42;
		m_43 = _value._43;
		m_44 = _value._44;

		return *this;
	}

	Matrix4x4(const XMMATRIX& _value)
	{
		m_11 = _value.r[0].m128_f32[0];
		m_12 = _value.r[0].m128_f32[1];
		m_13 = _value.r[0].m128_f32[2];
		m_14 = _value.r[0].m128_f32[3];

		m_21 = _value.r[1].m128_f32[0];
		m_22 = _value.r[1].m128_f32[1];
		m_23 = _value.r[1].m128_f32[2];
		m_24 = _value.r[1].m128_f32[3];

		m_31 = _value.r[2].m128_f32[0];
		m_32 = _value.r[2].m128_f32[1];
		m_33 = _value.r[2].m128_f32[2];
		m_34 = _value.r[2].m128_f32[3];

		m_41 = _value.r[3].m128_f32[0];
		m_42 = _value.r[3].m128_f32[1];
		m_43 = _value.r[3].m128_f32[2];
		m_44 = _value.r[3].m128_f32[3];
	}
	Matrix4x4& operator=(const XMMATRIX _value)
	{
		m_11 = _value.r[0].m128_f32[0];
		m_12 = _value.r[0].m128_f32[1];
		m_13 = _value.r[0].m128_f32[2];
		m_14 = _value.r[0].m128_f32[3];

		m_21 = _value.r[1].m128_f32[0];
		m_22 = _value.r[1].m128_f32[1];
		m_23 = _value.r[1].m128_f32[2];
		m_24 = _value.r[1].m128_f32[3];

		m_31 = _value.r[2].m128_f32[0];
		m_32 = _value.r[2].m128_f32[1];
		m_33 = _value.r[2].m128_f32[2];
		m_34 = _value.r[2].m128_f32[3];

		m_41 = _value.r[3].m128_f32[0];
		m_42 = _value.r[3].m128_f32[1];
		m_43 = _value.r[3].m128_f32[2];
		m_44 = _value.r[3].m128_f32[3];

		return *this;
	}

	operator XMMATRIX() 
	{
		XMMATRIX temp(m_11, m_12, m_13, m_14,
					  m_21, m_22, m_23, m_24,
					  m_31, m_32, m_33, m_34,
					  m_41, m_42, m_43, m_44);
		return temp;
	}

	operator XMFLOAT4X4() 
	{
		XMFLOAT4X4 temp(m_11, m_12, m_13, m_14,
						m_21, m_22, m_23, m_24,
						m_31, m_32, m_33, m_34,
						m_41, m_42, m_43, m_44);
		return temp;
	}

	Matrix4x4& operator+=(const Matrix4x4 _m) 
	{
		this->m_11 += _m.m_11;
		this->m_12 += _m.m_12;
		this->m_13 += _m.m_13;
		this->m_14 += _m.m_14;

		this->m_21 += _m.m_21;
		this->m_22 += _m.m_22;
		this->m_23 += _m.m_23;
		this->m_24 += _m.m_24;

		this->m_31 += _m.m_31;
		this->m_32 += _m.m_32;
		this->m_33 += _m.m_33;
		this->m_34 += _m.m_34;

		this->m_41 += _m.m_41;
		this->m_42 += _m.m_42;
		this->m_43 += _m.m_43;
		this->m_44 += _m.m_44;

		return *this;
	}

	Matrix4x4& operator-=(const Matrix4x4 _m)
	{
		this->m_11 -= _m.m_11;
		this->m_12 -= _m.m_12;
		this->m_13 -= _m.m_13;
		this->m_14 -= _m.m_14;

		this->m_21 -= _m.m_21;
		this->m_22 -= _m.m_22;
		this->m_23 -= _m.m_23;
		this->m_24 -= _m.m_24;

		this->m_31 -= _m.m_31;
		this->m_32 -= _m.m_32;
		this->m_33 -= _m.m_33;
		this->m_34 -= _m.m_34;

		this->m_41 -= _m.m_41;
		this->m_42 -= _m.m_42;
		this->m_43 -= _m.m_43;
		this->m_44 -= _m.m_44;

		return *this;
	}

	Matrix4x4& operator*=(const Matrix4x4 _m)
	{
		this->m_11 = (this->m_11 * _m.m_11) + (this->m_12 * _m.m_21) + (this->m_13 * _m.m_31) + (this->m_14 * _m.m_41);
		this->m_12 = (this->m_11 * _m.m_12) + (this->m_12 * _m.m_22) + (this->m_13 * _m.m_32) + (this->m_14 * _m.m_42);
		this->m_13 = (this->m_11 * _m.m_13) + (this->m_12 * _m.m_23) + (this->m_13 * _m.m_33) + (this->m_14 * _m.m_43);
		this->m_14 = (this->m_11 * _m.m_14) + (this->m_12 * _m.m_24) + (this->m_13 * _m.m_34) + (this->m_14 * _m.m_44);

		this->m_21 = (this->m_21 * _m.m_11) + (this->m_22 * _m.m_21) + (this->m_23 * _m.m_31) + (this->m_24 * _m.m_41);
		this->m_22 = (this->m_21 * _m.m_12) + (this->m_22 * _m.m_22) + (this->m_23 * _m.m_32) + (this->m_24 * _m.m_42);
		this->m_23 = (this->m_21 * _m.m_13) + (this->m_22 * _m.m_23) + (this->m_23 * _m.m_33) + (this->m_24 * _m.m_43);
		this->m_24 = (this->m_21 * _m.m_14) + (this->m_22 * _m.m_24) + (this->m_23 * _m.m_34) + (this->m_24 * _m.m_44);

		this->m_31 = (this->m_31 * _m.m_11) + (this->m_32 * _m.m_21) + (this->m_33 * _m.m_31) + (this->m_34 * _m.m_41);
		this->m_32 = (this->m_31 * _m.m_12) + (this->m_32 * _m.m_22) + (this->m_33 * _m.m_32) + (this->m_34 * _m.m_42);
		this->m_33 = (this->m_31 * _m.m_13) + (this->m_32 * _m.m_23) + (this->m_33 * _m.m_33) + (this->m_34 * _m.m_43);
		this->m_34 = (this->m_31 * _m.m_14) + (this->m_32 * _m.m_24) + (this->m_33 * _m.m_34) + (this->m_34 * _m.m_44);

		this->m_41 = (this->m_41 * _m.m_11) + (this->m_42 * _m.m_21) + (this->m_43 * _m.m_31) + (this->m_44 * _m.m_41);
		this->m_42 = (this->m_41 * _m.m_12) + (this->m_42 * _m.m_22) + (this->m_43 * _m.m_32) + (this->m_44 * _m.m_42);
		this->m_43 = (this->m_41 * _m.m_13) + (this->m_42 * _m.m_23) + (this->m_43 * _m.m_33) + (this->m_44 * _m.m_43);
		this->m_44 = (this->m_41 * _m.m_14) + (this->m_42 * _m.m_24) + (this->m_43 * _m.m_34) + (this->m_44 * _m.m_44);

		return *this;
	}

	// 単位行列
	static Matrix4x4 IdentityMatrix() 
	{
		Matrix4x4 temp(1.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

		return temp;
	}

	// 平行移動行列
	static Matrix4x4 TranslationMatrix(float _posX, float _posY, float _posZ)
	{
		Matrix4x4 temp(1.0f,  0.0f,  0.0f, 0.0f,
					   0.0f,  1.0f,  0.0f, 0.0f,
					   0.0f,  0.0f,  1.0f, 0.0f,
					  _posX, _posY, _posZ, 1.0f);

		return temp;
	}

	// 平行移動行列
	static Matrix4x4 TranslationMatrix(Vector3 _pos)
	{
		Matrix4x4 temp(1.0f,   0.0f,   0.0f, 0.0f,
					   0.0f,   1.0f,   0.0f, 0.0f,
					   0.0f,   0.0f,   1.0f, 0.0f,
					 _pos.x, _pos.y, _pos.z, 1.0f);

		return temp;
	}

	// スケール行列
	static Matrix4x4 ScalingMatrix(float _scaleX, float _scaleY, float _scaleZ)
	{
		Matrix4x4 temp(_scaleX,    0.0f,    0.0f, 0.0f,
						  0.0f, _scaleY,    0.0f, 0.0f,
						  0.0f,    0.0f, _scaleZ, 0.0f,
						  0.0f,    0.0f,    0.0f, 1.0f);

		return temp;
	}

	// スケール行列
	static Matrix4x4 ScalingMatrix(Vector3 _scale)
	{
		Matrix4x4 temp(_scale.x,     0.0f,     0.0f, 0.0f,
						   0.0f, _scale.y,     0.0f, 0.0f,
						   0.0f,     0.0f, _scale.z, 0.0f,
						   0.0f,     0.0f,     0.0f, 1.0f);

		return temp;
	}

	// 回転行列
	static Matrix4x4 RotationXMatrix(float _angle)
	{
		float cosX = cosf((_angle) * (PI_F / 180.0f));
		float sinX = sinf((_angle) * (PI_F / 180.0f));

		Matrix4x4 temp(1.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, cosX, sinX, 0.0f,
					   0.0f, -sinX, cosX, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

		return temp;
	}

	// 回転行列
	static Matrix4x4 RotationYMatrix(float _angle)
	{
		float cosY = cosf((_angle) * (PI_F / 180.0f));
		float sinY = sinf((_angle) * (PI_F / 180.0f));

		Matrix4x4 temp(cosY, 0.0f, -sinY, 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f,
					   sinY, 0.0f, cosY, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

		return temp;
	}

	// 回転行列
	static Matrix4x4 RotationZMatrix(float _angle)
	{
		float cosZ = cosf((_angle) * (PI_F / 180.0f));
		float sinZ = sinf((_angle) * (PI_F / 180.0f));

		Matrix4x4 temp(cosZ, sinZ, 0.0f, 0.0f,
					  -sinZ, cosZ, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

		return temp;
	}

	// 回転行列
	static Matrix4x4 RotationZXYMatrix(float _angleX, float _angleY, float _angleZ)
	{
		float cosX = cosf((_angleX) * (PI_F / 180.0f));
		float sinX = sinf((_angleX) * (PI_F / 180.0f));
		float cosY = cosf((_angleY) * (PI_F / 180.0f));
		float sinY = sinf((_angleY) * (PI_F / 180.0f));
		float cosZ = cosf((_angleZ) * (PI_F / 180.0f));
		float sinZ = sinf((_angleZ) * (PI_F / 180.0f));

		Matrix4x4 temp = Matrix4x4::IdentityMatrix();

		temp.m_11 = (sinX * sinY * sinZ) + (cosY * cosZ);
		temp.m_12 = cosX * sinZ;
		temp.m_13 = (sinX * cosY * sinZ) + (-sinY * cosZ);

		temp.m_21 = (sinX * sinY * cosZ) + (-sinZ * cosY);
		temp.m_22 = cosX * cosZ;
		temp.m_23 = (sinX * cosY * cosZ) + (-sinY * -sinZ);

		temp.m_31 = cosX * sinY;
		temp.m_32 = -sinX;
		temp.m_33 = cosX * cosY;

		return temp;
	}

	// 回転行列
	static Matrix4x4 RotationZXYMatrix(Vector3 _angle)
	{
		float cosX = cosf((_angle.x) * (PI_F / 180.0f));
		float sinX = sinf((_angle.x) * (PI_F / 180.0f));
		float cosY = cosf((_angle.y) * (PI_F / 180.0f));
		float sinY = sinf((_angle.y) * (PI_F / 180.0f));
		float cosZ = cosf((_angle.z) * (PI_F / 180.0f));
		float sinZ = sinf((_angle.z) * (PI_F / 180.0f));

		Matrix4x4 temp = Matrix4x4::IdentityMatrix();

		temp.m_11 = (sinX * sinY * sinZ) + (cosY * cosZ);
		temp.m_12 = cosX * sinZ;
		temp.m_13 = (sinX * cosY * sinZ) + (-sinY * cosZ);

		temp.m_21 = (sinX * sinY * cosZ) + (-sinZ * cosY);
		temp.m_22 = cosX * cosZ;
		temp.m_23 = (sinX * cosY * cosZ) + (-sinY * -sinZ);

		temp.m_31 = cosX * sinY;
		temp.m_32 = -sinX;
		temp.m_33 = cosX * cosY;

		return temp;
	}

	// ビュー変換行列
	static Matrix4x4& ViewMatrix(Vector3 _eye, Vector3 _lookat, Vector3 _up)
	{
		Vector3 axisX;
		Vector3 axisY;
		Vector3 axisZ, axisZ2;
		Matrix4x4 temp;

		axisZ2 = axisZ = _lookat - _eye;
		axisZ.Normalize();

		axisX = _up.Closs(axisZ);
		axisX.Normalize();
		axisY = axisZ.Closs(axisX);
		axisY.Normalize();

		temp.m_11 = axisX.x;
		temp.m_21 = axisX.y;
		temp.m_31 = axisX.z;

		temp.m_12 = axisY.x;
		temp.m_22 = axisY.y;
		temp.m_32 = axisY.z;

		temp.m_13 = axisZ.x;
		temp.m_23 = axisZ.y;
		temp.m_33 = axisZ.z;

		temp.m_14 = 0.0f;
		temp.m_24 = 0.0f;
		temp.m_34 = 0.0f;
		temp.m_44 = 1.0f;

		temp.m_41 = -_eye.Dot(axisX);
		temp.m_42 = -_eye.Dot(axisY);
		temp.m_43 = -_eye.Dot(axisZ);

		return temp;
	}

	// 透視投影行列
	static Matrix4x4& PerspectiveMatrix(float _fov, float _aspectRatio, float _nearZ, float _farZ)
	{
		float tempAngle = (_fov * (PI_F / 180.0f)) / 2.0f;

		float temp = 1.0f / (tanf(tempAngle));

		Matrix4x4 tempMtx = Matrix4x4::IdentityMatrix();

		tempMtx.m_11 = (temp / _aspectRatio);
		tempMtx.m_22 = temp;
		tempMtx.m_33 = (_farZ) / (_farZ - _nearZ);
		tempMtx.m_43 = (-_nearZ * _farZ) / (_farZ - _nearZ);
		tempMtx.m_34 = 1.0f;
		tempMtx.m_44 = 0.0f;

		return tempMtx;
	}

	// 平行投影行列
	static Matrix4x4& OrthoMatrix(float _height, float _width, float _nearZ, float _farZ)
	{
		Matrix4x4 tempMtx = Matrix4x4::IdentityMatrix();

		tempMtx.m_11 = 2.0f / _height;
		tempMtx.m_22 = 2.0f / _width;
		tempMtx.m_33 = 1.0f / (_farZ - _nearZ);
		tempMtx.m_43 = _nearZ / (_nearZ - _farZ);
		tempMtx.m_34 = 0.0f;
		tempMtx.m_44 = 1.0f;

		return tempMtx;
	}

	// 零行列
	static Matrix4x4 ZeroMatrix() 
	{
		Matrix4x4 temp(0.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 0.0f);

		return temp;
	}

	// 平行移動
	Matrix4x4& Translation(float _posX, float _posY, float _posZ) 
	{
		Matrix4x4 temp(1.0f,  0.0f,  0.0f,  0.0f,
					   0.0f,  1.0f,  0.0f,  0.0f,
					   0.0f,  0.0f,  1.0f,  0.0f,
					  _posX, _posY, _posZ,  1.0f);

		return *this = temp;
	}

	// 平行移動
	Matrix4x4& Translation(Vector3 _pos)
	{
		Matrix4x4 temp(1.0f,   0.0f,   0.0f,  0.0f,
					   0.0f,   1.0f,   0.0f,  0.0f,
					   0.0f,   0.0f,   1.0f,  0.0f,
					 _pos.x, _pos.y, _pos.z,  1.0f);

		return *this = temp;
	}

	// 拡大・縮小
	Matrix4x4& Scaling(float _scaleX, float _scaleY, float _scaleZ) 
	{
		Matrix4x4 temp(_scaleX,	   0.0f,    0.0f, 0.0f,
						  0.0f, _scaleY,    0.0f, 0.0f,
						  0.0f,    0.0f, _scaleZ, 0.0f,
						  0.0f,    0.0f,    0.0f, 1.0f);

		return *this = temp;
	}

	// 拡大・縮小
	Matrix4x4& Scaling(Vector3 _scale)
	{
		Matrix4x4 temp(_scale.x,	 0.0f,	   0.0f, 0.0f,
						   0.0f, _scale.y,	   0.0f, 0.0f,
						   0.0f,	 0.0f, _scale.z, 0.0f,
						   0.0f,	 0.0f,     0.0f, 1.0f);

		return *this = temp;
	}

	// 回転(X軸回り)
	Matrix4x4& RotationX(float _angle) 
	{
		float cosX = cosf((_angle) * (PI_F / 180.0f));
		float sinX = sinf((_angle) * (PI_F / 180.0f));

		Matrix4x4 temp(1.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, cosX, sinX, 0.0f,
					   0.0f,-sinX, cosX, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

		return *this = temp;
	}

	// 回転(Y軸回り)
	Matrix4x4& RotationY(float _angle)
	{
		float cosY = cosf((_angle) * (PI_F / 180.0f));
		float sinY = sinf((_angle) * (PI_F / 180.0f));

		Matrix4x4 temp(cosY, 0.0f,-sinY, 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f,
					   sinY, 0.0f, cosY, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

		return *this = temp;
	}

	// 回転(Z軸回り)
	Matrix4x4& RotationZ(float _angle)
	{
		float cosZ = cosf((_angle) * (PI_F / 180.0f));
		float sinZ = sinf((_angle) * (PI_F / 180.0f));

		Matrix4x4 temp(cosZ, sinZ, 0.0f, 0.0f,
					  -sinZ, cosZ, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

		return *this = temp;
	}

	// 回転(Z->X->Y)
	Matrix4x4& RotationZXY(float _angleX, float _angleY, float _angleZ) 
	{
		float cosX = cosf((_angleX) * (PI_F / 180.0f));
		float sinX = sinf((_angleX) * (PI_F / 180.0f));
		float cosY = cosf((_angleY) * (PI_F / 180.0f));
		float sinY = sinf((_angleY) * (PI_F / 180.0f));
		float cosZ = cosf((_angleZ) * (PI_F / 180.0f));
		float sinZ = sinf((_angleZ) * (PI_F / 180.0f));

		Matrix4x4 temp;

		temp.m_11 = (sinX * sinY * sinZ) + (cosY * cosZ);
		temp.m_12 = cosX * sinZ;
		temp.m_13 = (sinX * cosY * sinZ) + (-sinY * cosZ);

		temp.m_21 = (sinX * sinY * cosZ) + (-sinZ * cosY);
		temp.m_22 = cosX * cosZ;
		temp.m_23 = (sinX * cosY * cosZ) + (-sinY * -sinZ);

		temp.m_31 = cosX * sinY;
		temp.m_32 = -sinX;
		temp.m_33 = cosX * cosY;

		temp.m_44 = 1.0f;

		return *this = temp;
	}

	// 回転(Z->X->Y)
	Matrix4x4& RotationZXY(Vector3 _angle)
	{
		float cosX = cosf((_angle.x) * (PI_F / 180.0f));
		float sinX = sinf((_angle.x) * (PI_F / 180.0f));
		float cosY = cosf((_angle.y) * (PI_F / 180.0f));
		float sinY = sinf((_angle.y) * (PI_F / 180.0f));
		float cosZ = cosf((_angle.z) * (PI_F / 180.0f));
		float sinZ = sinf((_angle.z) * (PI_F / 180.0f));

		Matrix4x4 temp = Matrix4x4::IdentityMatrix();

		temp.m_11 = (sinX * sinY * sinZ) + (cosY * cosZ);
		temp.m_12 = cosX * sinZ;
		temp.m_13 = (sinX * cosY * sinZ) + (-sinY * cosZ);

		temp.m_21 = (sinX * sinY * cosZ) + (-sinZ * cosY);
		temp.m_22 = cosX * cosZ;
		temp.m_23 = (sinX * cosY * cosZ) + (-sinY * -sinZ);

		temp.m_31 = cosX * sinY;
		temp.m_32 = -sinX;
		temp.m_33 = cosX * cosY;

		return *this = temp;
	}

	// X軸を取得
	Vector3& GetAxisX() 
	{
		Vector3 temp;

		temp.x = this->m_11;
		temp.x = this->m_12;
		temp.x = this->m_13;

		return temp;
	}

	// Y軸を取得
	Vector3& GetAxisY()
	{
		Vector3 temp;

		temp.x = this->m_21;
		temp.x = this->m_22;
		temp.x = this->m_23;

		return temp;
	}

	// Z軸を取得
	Vector3& GetAxisZ()
	{
		Vector3 temp;

		temp.x = this->m_31;
		temp.x = this->m_32;
		temp.x = this->m_33;

		return temp;
	}

	// ビュー変換
	Matrix4x4& View(Vector3 _eye, Vector3 _lookat, Vector3 _up) 
	{
		Vector3 axisX;
		Vector3 axisY;
		Vector3 axisZ, axisZ2;
		Matrix4x4 temp;

		axisZ2 = axisZ = _lookat - _eye;
		axisZ.Normalize();

		axisX = _up.Closs(axisZ);
		axisX.Normalize();
		axisY = axisZ.Closs(axisX);
		axisY.Normalize();

		temp.m_11 = axisX.x;
		temp.m_21 = axisX.y;
		temp.m_31 = axisX.z;

		temp.m_12 = axisY.x;
		temp.m_22 = axisY.y;
		temp.m_32 = axisY.z;

		temp.m_13 = axisZ.x;
		temp.m_23 = axisZ.y;
		temp.m_33 = axisZ.z;

		temp.m_14 = 0.0f;
		temp.m_24 = 0.0f;
		temp.m_34 = 0.0f;
		temp.m_44 = 1.0f;

		temp.m_41 = -_eye.Dot(axisX);
		temp.m_42 = -_eye.Dot(axisY);
		temp.m_43 = -_eye.Dot(axisZ);

		return *this = temp;
	}

	// 透視投影変換
	Matrix4x4& Perspective(float _fov, float _aspectRatio, float _nearZ, float _farZ)
	{
		float tempAngle = (_fov * (PI_F / 180.0f)) / 2.0f;

		float temp = 1.0f / (tanf(tempAngle));

		Matrix4x4 tempMtx = Matrix4x4::IdentityMatrix();

		tempMtx.m_11 = (temp / _aspectRatio);
		tempMtx.m_22 = temp;
		tempMtx.m_33 = (_farZ) / (_farZ - _nearZ);
		tempMtx.m_43 = (-_nearZ * _farZ) / (_farZ - _nearZ);
		tempMtx.m_34 = 1.0f;
		tempMtx.m_44 = 0.0f;

		return *this = tempMtx;
	}

	// 平行投影変換
	Matrix4x4& Ortho(float _height, float _width, float _nearZ, float _farZ)
	{
		Matrix4x4 tempMtx = Matrix4x4::IdentityMatrix();

		tempMtx.m_11 = 2.0f / _height;
		tempMtx.m_22 = 2.0f / _width;
		tempMtx.m_33 = 1.0f / (_farZ - _nearZ);
		tempMtx.m_43 = _nearZ / (_nearZ - _farZ);
		tempMtx.m_34 = 0.0f;
		tempMtx.m_44 = 1.0f;

		return *this = tempMtx;
	}

	// 転置
	Matrix4x4& Transpose() 
	{
		std::swap(this->m_12, this->m_21);
		std::swap(this->m_13, this->m_31);
		std::swap(this->m_14, this->m_41);

		std::swap(this->m_23, this->m_32);
		std::swap(this->m_24, this->m_42);
		std::swap(this->m_34, this->m_43);

		return *this;
	}

	// 行列式
	float Determinant() 
	{
		float temp = 0.0f;

		float temp1 = m_11 * (m_22 * m_33 * m_44 + m_23 * m_34 * m_42 + m_24 * m_32 * m_43 - m_24 * m_33 * m_42 - m_23 * m_32 * m_44 - m_22 * m_34 * m_43);
		float temp2 = m_21 * (m_12 * m_33 * m_44 + m_13 * m_34 * m_42 + m_14 * m_32 * m_43 - m_14 * m_33 * m_42 - m_13 * m_32 * m_44 - m_12 * m_34 * m_43);
		float temp3 = m_31 * (m_12 * m_23 * m_44 + m_13 * m_24 * m_42 + m_14 * m_22 * m_43 - m_14 * m_23 * m_42 - m_13 * m_22 * m_44 - m_12 * m_24 * m_43);
		float temp4 = m_41 * (m_12 * m_23 * m_34 + m_13 * m_24 * m_32 + m_14 * m_22 * m_33 - m_14 * m_23 * m_32 - m_13 * m_22 * m_34 - m_12 * m_24 * m_33);

		temp = temp1 - temp2 + temp3 - temp4;

		return temp;
	}

	// 逆行列
	Matrix4x4& Inverse() 
	{
		Matrix4x4 temp = *this;

		float determinant = temp.Determinant();

		if (determinant != 0) 
		{
			temp.m_11 = (m_22 * m_33 * m_44 + m_23 * m_34 * m_42 + m_24 * m_32 * m_43 - m_24 * m_33 * m_42 - m_23 * m_32 * m_44 - m_22 * m_34 * m_43) / determinant;
			temp.m_12 = (-m_12 * m_33 * m_44 - m_13 * m_34 * m_42 - m_14 * m_32 * m_43 + m_14 * m_33 * m_42 + m_13 * m_32 * m_44 + m_12 * m_34 * m_43) / determinant;
			temp.m_13 = (m_12 * m_23 * m_44 + m_13 * m_24 * m_42 + m_14 * m_22 * m_43 - m_14 * m_23 * m_42 - m_13 * m_22 * m_44 - m_12 * m_24 * m_43) / determinant;
			temp.m_14 = (-m_12 * m_23 * m_34 - m_13 * m_24 * m_32 - m_14 * m_22 * m_33 + m_14 * m_23 * m_32 + m_13 * m_22 * m_34 + m_12 * m_24 * m_33) / determinant;

			temp.m_21 = (-m_21 * m_33 * m_44 - m_23 * m_34 * m_41 - m_24 * m_31 * m_43 + m_24 * m_33 * m_41 + m_23 * m_31 * m_44 + m_21 * m_34 * m_43) / determinant;
			temp.m_22 = (m_11 * m_33 * m_44 + m_13 * m_34 * m_41 + m_14 * m_31 * m_43 - m_14 * m_33 * m_41 - m_13 * m_31 * m_44 - m_11 * m_34 * m_43) / determinant;
			temp.m_23 = (-m_11 * m_23 * m_44 - m_13 * m_24 * m_41 - m_14 * m_21 * m_43 + m_14 * m_23 * m_41 + m_13 * m_21 * m_44 + m_11 * m_24 * m_43) / determinant;
			temp.m_24 = (m_11 * m_23 * m_34 + m_13 * m_24 * m_31 + m_14 * m_21 * m_33 - m_14 * m_23 * m_31 - m_13 * m_21 * m_34 - m_11 * m_24 * m_33) / determinant;

			temp.m_31 = (m_21 * m_32 * m_44 + m_22 * m_34 * m_41 + m_24 * m_31 * m_42 - m_24 * m_32 * m_41 - m_22 * m_31 * m_44 - m_21 * m_34 * m_42) / determinant;
			temp.m_32 = (-m_11 * m_32 * m_44 - m_12 * m_34 * m_41 - m_14 * m_31 * m_42 + m_14 * m_32 * m_41 + m_12 * m_31 * m_44 + m_11 * m_34 * m_42) / determinant;
			temp.m_33 = (m_11 * m_22 * m_44 + m_12 * m_24 * m_41 + m_14 * m_21 * m_42 - m_14 * m_22 * m_41 - m_12 * m_21 * m_44 - m_11 * m_24 * m_42) / determinant;
			temp.m_34 = (-m_11 * m_22 * m_34 - m_12 * m_24 * m_31 - m_14 * m_21 * m_32 + m_14 * m_22 * m_31 + m_12 * m_21 * m_34 + m_11 * m_24 * m_32) / determinant;

			temp.m_41 = (-m_21 * m_32 * m_43 - m_22 * m_33 * m_41 - m_23 * m_31 * m_42 + m_23 * m_32 * m_41 + m_22 * m_31 * m_43 + m_21 * m_33 * m_42) / determinant;
			temp.m_42 = (m_11 * m_32 * m_43 + m_12 * m_33 * m_41 + m_13 * m_31 * m_42 - m_13 * m_32 * m_41 - m_12 * m_31 * m_43 - m_11 * m_33 * m_42) / determinant;
			temp.m_43 = (-m_11 * m_22 * m_43 - m_12 * m_23 * m_41 - m_13 * m_21 * m_42 + m_13 * m_22 * m_41 + m_12 * m_21 * m_43 + m_11 * m_23 * m_42) / determinant;
			temp.m_44 = (m_11 * m_22 * m_33 + m_12 * m_23 * m_31 + m_13 * m_21 * m_32 - m_13 * m_22 * m_31 - m_12 * m_21 * m_33 - m_11 * m_23 * m_32) / determinant;
		}

		return *this = temp;
	}

	constexpr Matrix4x4(float _m00, float _m01, float _m02, float _m03,
						float _m10, float _m11, float _m12, float _m13,
						float _m20, float _m21, float _m22, float _m23,
						float _m30, float _m31, float _m32, float _m33)
		:	m_11(_m00), m_12(_m01), m_13(_m02), m_14(_m03),
			m_21(_m10), m_22(_m11), m_23(_m12), m_24(_m13),
			m_31(_m20), m_32(_m21), m_33(_m22), m_34(_m23),
			m_41(_m30), m_42(_m31), m_43(_m32), m_44(_m33) {}

	explicit Matrix4x4(_In_reads_(16) const float* _pArray) 
	{
		assert(_pArray != nullptr);

		m[0][0] = _pArray[0];
		m[0][1] = _pArray[1];
		m[0][2] = _pArray[2];
		m[0][3] = _pArray[3];

		m[1][0] = _pArray[4];
		m[1][1] = _pArray[5];
		m[1][2] = _pArray[6];
		m[1][3] = _pArray[7];

		m[2][0] = _pArray[8];
		m[2][1] = _pArray[9];
		m[2][2] = _pArray[10];
		m[2][3] = _pArray[11];
		
		m[3][0] = _pArray[12];
		m[3][1] = _pArray[13];
		m[3][2] = _pArray[14];
		m[3][3] = _pArray[15];
	}

	float       operator() (size_t Row, size_t Column) const { return m[Row][Column]; }
	float&		operator() (size_t Row, size_t Column) { return m[Row][Column]; }
};

Matrix4x4 operator+ (const XMMATRIX& _x, const Matrix4x4& _m);
Matrix4x4 operator+ (const Matrix4x4& _m, const XMMATRIX& _x);
Matrix4x4 operator+ (const XMFLOAT4X4& _f, const Matrix4x4& _m);
Matrix4x4 operator+ (const Matrix4x4& _m, const XMFLOAT4X4& _f);
Matrix4x4 operator+ (const Matrix4x4& _m1, const Matrix4x4& _m2);

Matrix4x4 operator- (const XMMATRIX& _x, const Matrix4x4& _m);
Matrix4x4 operator- (const Matrix4x4& _m, const XMMATRIX& _x);
Matrix4x4 operator- (const XMFLOAT4X4& _f, const Matrix4x4& _m);
Matrix4x4 operator- (const Matrix4x4& _m, const XMFLOAT4X4& _f);
Matrix4x4 operator- (const Matrix4x4& _m1, const Matrix4x4& _m2);

Matrix4x4 operator* (const XMMATRIX& _x, const Matrix4x4& _m);
Matrix4x4 operator* (const Matrix4x4& _m, const XMMATRIX& _x);
Matrix4x4 operator* (const XMFLOAT4X4& _f, const Matrix4x4& _m);
Matrix4x4 operator* (const Matrix4x4& _m, const XMFLOAT4X4& _f);
Matrix4x4 operator* (const Matrix4x4& _m1, const Matrix4x4& _m2);

Vector4 operator* (const Matrix4x4& _m, const Vector4& _v);
Vector4 operator* (const Vector4& _v, const Matrix4x4& _m);
#pragma endregion

template <class T>  class Property {

public:

	T& _value;

	operator T()
	{
		// getが設定されてれば登録されたほうを呼ぶ
		return this->_value;
	}

	void operator=(const Property& _pro) {

		this->_value = _pro._value;
	};

	void operator =(const T _v)
	{
		_value = _v;
	}
};

class Transform {

	Vector3 Pos;		//ワールドでの位置
	Vector3 Angle;		//ZXYの順で回転させる際のオイラー角
	Vector3 Scale;		//ワールドでのスケール

public:

	Property<Vector3> position{ Pos };
	Property<Vector3> scale{ Scale };
	Property<Vector3> angle{ Angle };
};

#endif // !MATH_H
