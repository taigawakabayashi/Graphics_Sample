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

struct Vector2Int 
{
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

	// í∑Ç≥
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

struct Vector3Int 
{
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

	// í∑Ç≥
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

struct Vector2 
{
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

	// í∑Ç≥
	float Length() {

		return sqrt((x * x) + (y * y));
	}

	// ê≥ãKâª
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

	// ì‡êœ(ê≥ãKâªçœÇ›)
	float NormalizedDot(Vector2 _v) {

		Vector2 temp = *this;

		temp.Normalize();
		_v.Normalize();

		return (temp.x * _v.x) + (temp.y * _v.y);
	}

	// ì‡êœ
	float Dot(Vector2 _v) {

		return (x * _v.x) + (y * _v.y);
	}

	// Ç»Ç∑äp(ìxêîäpìx)
	float DegreesAngle(Vector2 _v) {

		return XMConvertToDegrees(acosf(NormalizedDot(_v)));
	}

	// Ç»Ç∑äp(ÉâÉWÉAÉìäpìx)
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

struct Vector3 
{
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

	// í∑Ç≥
	float Length() {

		return sqrt((x * x) + (y * y) + (z * z));
	}

	// ê≥ãKâª
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

	// ì‡êœ(ê≥ãKâªçœÇ›)
	float NormalizedDot(Vector3 _v) {

		Vector3 temp = *this;

		temp.Normalize();
		_v.Normalize();

		return (temp.x * _v.x) + (temp.y * _v.y) + (temp.z * _v.z);
	}

	// ì‡êœ
	float Dot(Vector3 _v) {

		return (x * _v.x) + (y * _v.y) + (z * _v.z);
	}

	//Å@äOêœ(ê≥ãKâªçœÇ›)
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

	// äOêœ
	Vector3 Closs(Vector3 _v) {

		Vector3 closs = Vector3::zero();

		closs.x = (y * _v.z - z * _v.y);
		closs.y = (z * _v.x - x * _v.z);
		closs.z = (x * _v.y - y * _v.x);

		return closs;
	}

	// Ç»Ç∑äp(ìxêîäpìx)
	float DegreesAngle(Vector3 _v) {

		return XMConvertToDegrees(acosf(NormalizedDot(_v)));
	}

	// Ç»Ç∑äp(ÉâÉWÉAÉìäpìx)
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

struct Vector4 
{
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

	// í∑Ç≥
	float Length() {

		return sqrt((x * x) + (y * y) + (z * z));
	}

	// ê≥ãKâª
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

	// ì‡êœ(ê≥ãKâªçœÇ›)
	float NormalizedDot(Vector4 _v) {

		Vector4 temp = *this;

		temp.Normalize();
		_v.Normalize();

		return (temp.x * _v.x) + (temp.y * _v.y) + (temp.z * _v.z);
	}

	// ì‡êœ
	float Dot(Vector4 _v) {

		return (x * _v.x) + (y * _v.y) + (z * _v.z);
	}

	// Ç»Ç∑äp(ìxêîäpìx)
	float DegreesAngle(Vector4 _v) {

		return XMConvertToDegrees(acosf(NormalizedDot(_v)));
	}

	// Ç»Ç∑äp(ÉâÉWÉAÉìäpìx)
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
		Matrix4x4 temp;

		temp.m_11 = (this->m_11 * _m.m_11) + (this->m_12 * _m.m_21) + (this->m_13 * _m.m_31) + (this->m_14 * _m.m_41);
		temp.m_12 = (this->m_11 * _m.m_12) + (this->m_12 * _m.m_22) + (this->m_13 * _m.m_32) + (this->m_14 * _m.m_42);
		temp.m_13 = (this->m_11 * _m.m_13) + (this->m_12 * _m.m_23) + (this->m_13 * _m.m_33) + (this->m_14 * _m.m_43);
		temp.m_14 = (this->m_11 * _m.m_14) + (this->m_12 * _m.m_24) + (this->m_13 * _m.m_34) + (this->m_14 * _m.m_44);

		temp.m_21 = (this->m_21 * _m.m_11) + (this->m_22 * _m.m_21) + (this->m_23 * _m.m_31) + (this->m_24 * _m.m_41);
		temp.m_22 = (this->m_21 * _m.m_12) + (this->m_22 * _m.m_22) + (this->m_23 * _m.m_32) + (this->m_24 * _m.m_42);
		temp.m_23 = (this->m_21 * _m.m_13) + (this->m_22 * _m.m_23) + (this->m_23 * _m.m_33) + (this->m_24 * _m.m_43);
		temp.m_24 = (this->m_21 * _m.m_14) + (this->m_22 * _m.m_24) + (this->m_23 * _m.m_34) + (this->m_24 * _m.m_44);

		temp.m_31 = (this->m_31 * _m.m_11) + (this->m_32 * _m.m_21) + (this->m_33 * _m.m_31) + (this->m_34 * _m.m_41);
		temp.m_32 = (this->m_31 * _m.m_12) + (this->m_32 * _m.m_22) + (this->m_33 * _m.m_32) + (this->m_34 * _m.m_42);
		temp.m_33 = (this->m_31 * _m.m_13) + (this->m_32 * _m.m_23) + (this->m_33 * _m.m_33) + (this->m_34 * _m.m_43);
		temp.m_34 = (this->m_31 * _m.m_14) + (this->m_32 * _m.m_24) + (this->m_33 * _m.m_34) + (this->m_34 * _m.m_44);

		temp.m_41 = (this->m_41 * _m.m_11) + (this->m_42 * _m.m_21) + (this->m_43 * _m.m_31) + (this->m_44 * _m.m_41);
		temp.m_42 = (this->m_41 * _m.m_12) + (this->m_42 * _m.m_22) + (this->m_43 * _m.m_32) + (this->m_44 * _m.m_42);
		temp.m_43 = (this->m_41 * _m.m_13) + (this->m_42 * _m.m_23) + (this->m_43 * _m.m_33) + (this->m_44 * _m.m_43);
		temp.m_44 = (this->m_41 * _m.m_14) + (this->m_42 * _m.m_24) + (this->m_43 * _m.m_34) + (this->m_44 * _m.m_44);

		return *this = temp;
	}

	// íPà çsóÒ
	static Matrix4x4 IdentityMatrix()
	{
		Matrix4x4 temp(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return temp;
	}

	// ïΩçsà⁄ìÆçsóÒ
	static Matrix4x4 TranslationMatrix(float _posX, float _posY, float _posZ)
	{
		Matrix4x4 temp(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			_posX, _posY, _posZ, 1.0f);

		return temp;
	}

	// ïΩçsà⁄ìÆçsóÒ
	static Matrix4x4 TranslationMatrix(Vector3 _pos)
	{
		Matrix4x4 temp(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			_pos.x, _pos.y, _pos.z, 1.0f);

		return temp;
	}

	// ÉXÉPÅ[ÉãçsóÒ
	static Matrix4x4 ScalingMatrix(float _scaleX, float _scaleY, float _scaleZ)
	{
		Matrix4x4 temp(_scaleX, 0.0f, 0.0f, 0.0f,
			0.0f, _scaleY, 0.0f, 0.0f,
			0.0f, 0.0f, _scaleZ, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return temp;
	}

	// ÉXÉPÅ[ÉãçsóÒ
	static Matrix4x4 ScalingMatrix(Vector3 _scale)
	{
		Matrix4x4 temp(_scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, _scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, _scale.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return temp;
	}

	// âÒì]çsóÒ(Xé≤)
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

	// âÒì]çsóÒ(Yé≤)
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

	// âÒì]çsóÒ(Zé≤)
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

	// âÒì]çsóÒ(Z->X->Y)
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

	// âÒì]çsóÒ(Z->X->Y)
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

	// âÒì](îCà”é≤)
	static Matrix4x4 RotationAxisMatrix(Vector3 _axis, float _angle)
	{
		float tempSin = sinf(_angle * (PI_F / 180.0f));
		float tempCos = cosf(_angle * (PI_F / 180.0f));

		Matrix4x4 temp;

		temp.m_11 = tempCos + _axis.x * _axis.x * (1.0f - tempCos);
		temp.m_12 = _axis.x * _axis.y * (1.0f - tempCos) + _axis.z * tempSin;
		temp.m_13 = _axis.x * _axis.z * (1.0f - tempCos) - _axis.y * tempSin;
		temp.m_14 = 0.0f;

		temp.m_21 = _axis.x * _axis.y * (1.0f - tempCos) - _axis.z * tempSin;;
		temp.m_22 = tempCos + _axis.y * _axis.y * (1.0f - tempCos);
		temp.m_23 = _axis.y * _axis.z * (1.0f - tempCos) + _axis.x * tempSin;
		temp.m_24 = 0.0f;

		temp.m_31 = _axis.x * _axis.z * (1.0f - tempCos) + _axis.y * tempSin;
		temp.m_32 = _axis.y * _axis.z * (1.0f - tempCos) - _axis.x * tempSin;
		temp.m_33 = tempCos + _axis.z * _axis.z * (1.0f - tempCos);
		temp.m_34 = 0.0f;

		temp.m_41 = 0.0f;
		temp.m_42 = 0.0f;
		temp.m_43 = 0.0f;
		temp.m_44 = 1.0f;

		return temp;
	}

	// âÒì](ÉèÅ[ÉãÉhXé≤âÒÇË)
	static Matrix4x4 RotationXWorldMatrix(float _angle)
	{
		Matrix4x4 temp = Matrix4x4::RotationAxisMatrix(Vector3(1.0f, 0.0f, 0.0f), _angle);

		return temp;
	}

	// âÒì](ÉèÅ[ÉãÉhYé≤âÒÇË)
	static Matrix4x4 RotationYWorldMatrix(float _angle)
	{
		Matrix4x4 temp = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 1.0f, 0.0f), _angle);

		return temp;
	}

	// âÒì](ÉèÅ[ÉãÉhZé≤âÒÇË)
	static Matrix4x4 RotationZWorldMatrix(float _angle)
	{
		Matrix4x4 temp = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 0.0f, 1.0f), _angle);

		return temp;
	}

	// âÒì](ÉèÅ[ÉãÉhé≤âÒÇË)
	static Matrix4x4 RotationWorldMatrix(float _angleX, float _angleY, float _angleZ)
	{
		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(Vector3(1.0f, 0.0f, 0.0f), _angleX);
		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 1.0f, 0.0f), _angleY);
		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 0.0f, 1.0f), _angleZ);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return temp;
	}

	// âÒì](ÉèÅ[ÉãÉhé≤âÒÇË)
	static Matrix4x4 RotationWorldMatrix(Vector3 _angle)
	{
		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(Vector3(1.0f, 0.0f, 0.0f), _angle.x);
		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 1.0f, 0.0f), _angle.y);
		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 0.0f, 1.0f), _angle.z);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return temp;
	}

	// âÒì](ÉçÅ[ÉJÉãé≤âÒÇË)
	static Matrix4x4 RotationLocalMatrix(Matrix4x4 _mtx, float _angleX, float _angleY, float _angleZ)
	{
		Vector3 axisZ = _mtx.GetAxisZ();

		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(axisZ, _angleZ);

		Vector3 axisX = _mtx.GetAxisX();

		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(axisX, _angleX);

		Vector3 axisY = _mtx.GetAxisY();

		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(axisY, _angleY);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return temp;
	}

	// âÒì](ÉçÅ[ÉJÉãé≤âÒÇË)
	static Matrix4x4 RotationLocalMatirx(Matrix4x4 _mtx, Vector3 _angle)
	{
		Vector3 axisZ = _mtx.GetAxisZ();

		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(axisZ, _angle.z);

		Vector3 axisX = _mtx.GetAxisX();

		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(axisX, _angle.x);

		Vector3 axisY = _mtx.GetAxisY();

		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(axisY, _angle.y);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return temp;
	}

	// ÉrÉÖÅ[ïœä∑çsóÒ
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

	// ìßéãìäâeçsóÒ
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

	// ïΩçsìäâeçsóÒ
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

	// óÎçsóÒ
	static Matrix4x4 ZeroMatrix() 
	{
		Matrix4x4 temp(0.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.0f, 0.0f);

		return temp;
	}

	// ïΩçsà⁄ìÆ
	Matrix4x4& Translation(float _posX, float _posY, float _posZ) 
	{
		Matrix4x4 temp(1.0f,  0.0f,  0.0f,  0.0f,
					   0.0f,  1.0f,  0.0f,  0.0f,
					   0.0f,  0.0f,  1.0f,  0.0f,
					  _posX, _posY, _posZ,  1.0f);

		return *this = temp;
	}

	// ïΩçsà⁄ìÆ
	Matrix4x4& Translation(Vector3 _pos)
	{
		Matrix4x4 temp(1.0f,   0.0f,   0.0f,  0.0f,
					   0.0f,   1.0f,   0.0f,  0.0f,
					   0.0f,   0.0f,   1.0f,  0.0f,
					 _pos.x, _pos.y, _pos.z,  1.0f);

		return *this = temp;
	}

	// ägëÂÅEèkè¨
	Matrix4x4& Scaling(float _scaleX, float _scaleY, float _scaleZ) 
	{
		Matrix4x4 temp(_scaleX,	   0.0f,    0.0f, 0.0f,
						  0.0f, _scaleY,    0.0f, 0.0f,
						  0.0f,    0.0f, _scaleZ, 0.0f,
						  0.0f,    0.0f,    0.0f, 1.0f);

		return *this = temp;
	}

	// ägëÂÅEèkè¨
	Matrix4x4& Scaling(Vector3 _scale)
	{
		Matrix4x4 temp(_scale.x,	 0.0f,	   0.0f, 0.0f,
						   0.0f, _scale.y,	   0.0f, 0.0f,
						   0.0f,	 0.0f, _scale.z, 0.0f,
						   0.0f,	 0.0f,     0.0f, 1.0f);

		return *this = temp;
	}

	// âÒì](Xé≤âÒÇË)
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

	// âÒì](Yé≤âÒÇË)
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

	// âÒì](Zé≤âÒÇË)
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

	// âÒì](Z->X->Y)
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

	// âÒì](Z->X->Y)
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

	// âÒì](îCà”é≤)
	Matrix4x4& RotationAxis(Vector3 _axis, float _angle) 
	{
		float tempSin = sinf(_angle * (PI_F / 180.0f));
		float tempCos = cosf(_angle * (PI_F / 180.0f));

		Matrix4x4 temp;

		temp.m_11 = tempCos + _axis.x * _axis.x * (1 - tempCos);
		temp.m_12 = _axis.x * _axis.y * (1 - tempCos) + _axis.z * tempSin;
		temp.m_13 = _axis.x * _axis.z * (1 - tempCos) - _axis.y * tempSin;
		temp.m_14 = 0.0f;

		temp.m_21 = _axis.x * _axis.y * (1 - tempCos) - _axis.z * tempSin;
		temp.m_22 = tempCos + _axis.y * _axis.y * (1 - tempCos);
		temp.m_23 = _axis.y * _axis.z * (1 - tempCos) + _axis.x * tempSin;
		temp.m_24 = 0.0f;

		temp.m_31 = _axis.x * _axis.z * (1 - tempCos) + _axis.y * tempSin;
		temp.m_32 = _axis.y * _axis.z * (1 - tempCos) - _axis.x * tempSin;
		temp.m_33 = tempCos + _axis.z * _axis.z * (1 - tempCos);
		temp.m_34 = 0.0f;

		temp.m_41 = 0.0f;
		temp.m_42 = 0.0f;
		temp.m_43 = 0.0f;
		temp.m_44 = 1.0f;

		return *this = temp;
	}

	// âÒì](ÉèÅ[ÉãÉhXé≤âÒÇË)
	Matrix4x4& RotationXWorld(float _angle)
	{
		Matrix4x4 temp = Matrix4x4::RotationAxisMatrix(Vector3(1.0f, 0.0f, 0.0f), _angle);

		return *this = temp;
	}

	// âÒì](ÉèÅ[ÉãÉhYé≤âÒÇË)
	Matrix4x4& RotationYWorld(float _angle)
	{
		Matrix4x4 temp = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 1.0f, 0.0f), _angle);

		return *this = temp;
	}

	// âÒì](ÉèÅ[ÉãÉhZé≤âÒÇË)
	Matrix4x4& RotationZWorld(float _angle)
	{
		Matrix4x4 temp = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 0.0f, 1.0f), _angle);

		return *this = temp;
	}

	// âÒì](ÉèÅ[ÉãÉhé≤âÒÇË)
	Matrix4x4& RotationWorld(float _angleX, float _angleY, float _angleZ) 
	{
		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(Vector3(1.0f, 0.0f, 0.0f), _angleX);
		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 1.0f, 0.0f), _angleY);
		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 0.0f, 1.0f), _angleZ);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return *this = temp;
	}

	// âÒì](ÉèÅ[ÉãÉhé≤âÒÇË)
	Matrix4x4& RotationWorld(Vector3 _angle)
	{
		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(Vector3(1.0f, 0.0f, 0.0f), _angle.x);
		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 1.0f, 0.0f), _angle.y);
		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(Vector3(0.0f, 0.0f, 1.0f), _angle.z);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return *this = temp;
	}

	// âÒì](ÉçÅ[ÉJÉãé≤âÒÇË)
	Matrix4x4& RotationLocal(float _angleX, float _angleY, float _angleZ)
	{
		Vector3 axisZ = this->GetAxisZ();
		axisZ.Normalize();

		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(axisZ, _angleZ);

		Vector3 axisX = this->GetAxisX();
		axisX.Normalize();

		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(axisX, _angleX);

		Vector3 axisY = this->GetAxisY();
		axisY.Normalize();

		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(axisY, _angleY);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return *this = temp;
	}

	// âÒì](ÉçÅ[ÉJÉãé≤âÒÇË)
	Matrix4x4& RotationLocal(Vector3 _angle)
	{
		Vector3 axisZ = this->GetAxisZ();
		axisZ.Normalize();

		Matrix4x4 tempZ = Matrix4x4::RotationAxisMatrix(axisZ, _angle.z);

		Vector3 axisX = this->GetAxisX();
		axisX.Normalize();

		Matrix4x4 tempX = Matrix4x4::RotationAxisMatrix(axisX, _angle.x);

		Vector3 axisY = this->GetAxisY();
		axisY.Normalize();

		Matrix4x4 tempY = Matrix4x4::RotationAxisMatrix(axisY, _angle.y);

		Matrix4x4 temp = tempZ;

		temp *= tempX;
		temp *= tempY;

		return *this = temp;
	}

	// Xé≤ÇéÊìæ
	Vector3 GetAxisX() 
	{
		Vector3 temp;

		temp.x = this->m_11;
		temp.y = this->m_12;
		temp.z = this->m_13;

		return temp;
	}

	// Yé≤ÇéÊìæ
	Vector3 GetAxisY()
	{
		Vector3 temp;

		temp.x = this->m_21;
		temp.y = this->m_22;
		temp.z = this->m_23;

		return temp;
	}

	// Zé≤ÇéÊìæ
	Vector3 GetAxisZ()
	{
		Vector3 temp;

		temp.x = this->m_31;
		temp.y = this->m_32;
		temp.z = this->m_33;

		return temp;
	}

	// ÉrÉÖÅ[ïœä∑
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

	// ìßéãìäâeïœä∑
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

	// ïΩçsìäâeïœä∑
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

	// ì]íu
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

	// çsóÒéÆ
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

	// ãtçsóÒ
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

#pragma region Quaternion

struct Quaternion 
{
public:

	float x;
	float y;
	float z;
	float w;

	Quaternion() = default;

	Quaternion(const Quaternion&) = default;
	Quaternion& operator=(const Quaternion&) = default;

	Quaternion(Quaternion&&) = default;
	Quaternion& operator=(Quaternion&&) = default;

	Quaternion(const XMFLOAT4 & _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;
		this->w = _value.w;
	}
	Quaternion& operator= (const XMFLOAT4 & _value) {

		this->x = _value.x;
		this->y = _value.y;
		this->z = _value.z;
		this->w = _value.w;

		return *this;
	}

	Quaternion(const XMVECTOR & _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];
		this->z = _value.m128_f32[2];
		this->w = _value.m128_f32[3];
	}
	Quaternion& operator= (const XMVECTOR & _value) {

		this->x = _value.m128_f32[0];
		this->y = _value.m128_f32[1];
		this->z = _value.m128_f32[2];
		this->w = _value.m128_f32[3];

		return *this;
	}

	operator XMFLOAT4() {

		return XMFLOAT4(x, y, z, w);
	}

	operator XMVECTOR() {

		return XMVECTOR{ x, y, z,w };
	}

	static Quaternion IdentityQuaternion() 
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Quaternion RotationXQuaternion(float _angle)
	{
		Quaternion temp;

		Vector3 tempAxis = Vector3::right();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = tempAxis.x * tempSin;
		temp.y = tempAxis.y * tempSin;
		temp.z = tempAxis.z * tempSin;
		temp.w = tempCos;

		return temp;
	}

	static Quaternion RotationYQuaternion(float _angle)
	{
		Quaternion temp;

		Vector3 tempAxis = Vector3::up();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = tempAxis.x * tempSin;
		temp.y = tempAxis.y * tempSin;
		temp.z = tempAxis.z * tempSin;
		temp.w = tempCos;

		return temp;
	}

	static Quaternion RotationZQuaternion(float _angle)
	{
		Quaternion temp;

		Vector3 tempAxis = Vector3::forward();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = tempAxis.x * tempSin;
		temp.y = tempAxis.y * tempSin;
		temp.z = tempAxis.z * tempSin;
		temp.w = tempCos;

		return temp;
	}

	static Quaternion RotationAxisQuaternion(Vector3 _axis, float _angle)
	{
		Quaternion temp;	

		_axis.Normalize();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = _axis.x * tempSin;
		temp.y = _axis.y * tempSin;
		temp.z = _axis.z * tempSin;
		temp.w = tempCos;

		return temp;
	}

	static Quaternion RotationMatrixQuaternion(Matrix4x4 _mtx)
	{
		float elem[4] =
		{
			_mtx.m_11 - _mtx.m_22 - _mtx.m_33 + 1.0f,
			-_mtx.m_11 + _mtx.m_22 - _mtx.m_33 + 1.0f,
			-_mtx.m_11 - _mtx.m_22 + _mtx.m_33 + 1.0f,
			_mtx.m_11 + _mtx.m_22 + _mtx.m_33 + 1.0f,
		};

		uint32_t biggestindex = 0;

		for (int i = 1; i < 4; ++i)
		{
			if (elem[i] > elem[biggestindex])
			{
				biggestindex = i;
			}
		}

		if (elem[biggestindex] < 0.0f)
			return IdentityQuaternion();

		float v = sqrtf(elem[biggestindex]) * 0.5f;
		float mult = 0.25f / v;

		Quaternion temp;

		switch (biggestindex)
		{
		case 0:

			temp.x = v;
			temp.y = (_mtx.m_12 + _mtx.m_21) * mult;
			temp.z = (_mtx.m_31 + _mtx.m_13) * mult;
			temp.w = (_mtx.m_23 - _mtx.m_32) * mult;

			break;
		case 1:

			temp.x = (_mtx.m_12 + _mtx.m_21) * mult;
			temp.y = v;
			temp.z = (_mtx.m_23 + _mtx.m_32) * mult;
			temp.w = (_mtx.m_31 - _mtx.m_13) * mult;

			break;

		case 2:

			temp.x = (_mtx.m_31 + _mtx.m_13) * mult;
			temp.y = (_mtx.m_23 + _mtx.m_32) * mult;
			temp.z = v;
			temp.w = (_mtx.m_12 - _mtx.m_21) * mult;

			break;

		case 3:

			temp.x = (_mtx.m_23 - _mtx.m_32) * mult;
			temp.y = (_mtx.m_31 - _mtx.m_13) * mult;
			temp.z = (_mtx.m_12 - _mtx.m_21) * mult;
			temp.w = v;

			break;
		}

		return temp;
	}

	Quaternion& RotationX(float _angle)
	{
		Quaternion temp;

		Vector3 tempAxis = Vector3::right();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = tempAxis.x * tempSin;
		temp.y = tempAxis.y * tempSin;
		temp.z = tempAxis.z * tempSin;
		temp.w = tempCos;

		return *this = temp;
	}

	Quaternion& RotationY(float _angle)
	{
		Quaternion temp;

		Vector3 tempAxis = Vector3::up();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = tempAxis.x * tempSin;
		temp.y = tempAxis.y * tempSin;
		temp.z = tempAxis.z * tempSin;
		temp.w = tempCos;

		return *this = temp;
	}

	Quaternion& RotationZ(float _angle)
	{
		Quaternion temp;

		Vector3 tempAxis = Vector3::forward();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = tempAxis.x * tempSin;
		temp.y = tempAxis.y * tempSin;
		temp.z = tempAxis.z * tempSin;
		temp.w = tempCos;

		return *this = temp;
	}

	Quaternion& RotationAxis(Vector3 _axis, float _angle)
	{
		Quaternion temp;

		_axis.Normalize();

		float tempSin = sinf((_angle / 2) * (PI_F / 180.0f));
		float tempCos = cosf((_angle / 2) * (PI_F / 180.0f));

		temp.x = _axis.x * tempSin;
		temp.y = _axis.y * tempSin;
		temp.z = _axis.z * tempSin;
		temp.w = tempCos;

		return *this = temp;
	}

	Quaternion& RotationMatrix(Matrix4x4 _mtx) 
	{
		float elem[4] =
		{
			_mtx.m_11 - _mtx.m_22 - _mtx.m_33 + 1.0f,
			-_mtx.m_11 + _mtx.m_22 - _mtx.m_33 + 1.0f,
			-_mtx.m_11 - _mtx.m_22 + _mtx.m_33 + 1.0f,
			_mtx.m_11 + _mtx.m_22 + _mtx.m_33 + 1.0f,
		};

		uint32_t biggestindex = 0;

		for (int i = 1; i < 4; ++i) 
		{
			if (elem[i] > elem[biggestindex]) 
			{
				biggestindex = i;
			}
		}

		if (elem[biggestindex] < 0.0f)
			return *this;

		float v = sqrtf(elem[biggestindex]) * 0.5f;
		float mult = 0.25f / v;

		Quaternion temp = Quaternion::IdentityQuaternion();

		switch (biggestindex) 
		{
		case 0:

			temp.x = v;
			temp.y = (_mtx.m_12 + _mtx.m_21) * mult;
			temp.z = (_mtx.m_31 + _mtx.m_13) * mult;
			temp.w = (_mtx.m_23 - _mtx.m_32) * mult;

			break;
		case 1:

			temp.x = (_mtx.m_12 + _mtx.m_21) * mult;
			temp.y = v;
			temp.z = (_mtx.m_23 + _mtx.m_32) * mult;
			temp.w = (_mtx.m_31 - _mtx.m_13) * mult;

			break;

		case 2:

			temp.x = (_mtx.m_31 + _mtx.m_13) * mult;
			temp.y = (_mtx.m_23 + _mtx.m_32) * mult;
			temp.z = v;
			temp.w = (_mtx.m_12 - _mtx.m_21) * mult;

			break;

		case 3:

			temp.x = (_mtx.m_23 - _mtx.m_32) * mult;
			temp.y = (_mtx.m_31 - _mtx.m_13) * mult;
			temp.z = (_mtx.m_12 - _mtx.m_21) * mult;
			temp.w = v;

			break;
		}

		return *this = temp;
	}

	constexpr Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	constexpr Quaternion(Vector4 _v) : x(_v.x), y(_v.y), z(_v.z), w(_v.w) {}
};

#pragma endregion


template <class T>  class Property {

public:

	T& _value;

	// Getter
	operator T()
	{
		// getÇ™ê›íËÇ≥ÇÍÇƒÇÍÇŒìoò^Ç≥ÇÍÇΩÇŸÇ§ÇåƒÇ‘
		return this->_value;
	}

	void operator=(const Property& _pro) {

		this->_value = _pro._value;
	};

	// Setter
	void operator =(const T _v)
	{
		_value = _v;
	}
};

class Transform {

	Vector3 Pos;		//ÉèÅ[ÉãÉhÇ≈ÇÃà íu
	Vector3 Angle;		//ZXYÇÃèáÇ≈âÒì]Ç≥ÇπÇÈç€ÇÃÉIÉCÉâÅ[äp
	Vector3 Scale;		//ÉèÅ[ÉãÉhÇ≈ÇÃÉXÉPÅ[Éã

public:

	Property<Vector3> position{ Pos };
	Property<Vector3> scale{ Scale };
	Property<Vector3> angle{ Angle };
};

#endif // !MATH_H
