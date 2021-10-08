#pragma once
#ifndef MATH_H
#define MATH_H

#include <DirectXMath.h>
#include <cmath>
#include <functional>

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
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;

		}m[4][4];
	};


};

#pragma endregion

template <class T>  class Property {

public:

	T& _value;

	operator T()
	{
		// getÇ™ê›íËÇ≥ÇÍÇƒÇÍÇŒìoò^Ç≥ÇÍÇΩÇŸÇ§ÇåƒÇ‘
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

	Vector3 Pos;		//ÉèÅ[ÉãÉhÇ≈ÇÃà íu
	Vector3 Angle;		//ZXYÇÃèáÇ≈âÒì]Ç≥ÇπÇÈç€ÇÃÉIÉCÉâÅ[äp
	Vector3 Scale;		//ÉèÅ[ÉãÉhÇ≈ÇÃÉXÉPÅ[Éã

public:

	Property<Vector3> position{ Pos };
	Property<Vector3> scale{ Scale };
	Property<Vector3> angle{ Angle };
};

#endif // !MATH_H
