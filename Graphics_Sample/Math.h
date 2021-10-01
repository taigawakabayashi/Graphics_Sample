#pragma once
#include <DirectXMath.h>
#include <cmath>
#include <functional>

using namespace DirectX;

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

	Vector2(const XMFLOAT2& value) {

		this->x = value.x;
		this->y = value.y;
	}
	Vector2& operator= (const XMFLOAT2& value) {

		this->x = value.x;
		this->y = value.y;

		return *this;
	}

	Vector2(const XMVECTOR& value) {

		this->x = value.m128_f32[0];
		this->y = value.m128_f32[1];
	}
	Vector2& operator= (const XMVECTOR& value) {

		this->x = value.m128_f32[0];
		this->y = value.m128_f32[1];

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

	bool operator!=(Vector2 v) {

		return (this->x != v.x || this->y != v.y);
	}

	bool operator==(Vector2 v) {

		return (this->x == v.x && this->y == v.y);
	}

	Vector2& operator+=(const Vector2& v) {

		this->x += v.x;
		this->y += v.y;

		return *this;
	}

	Vector2& operator-=(const Vector2& v) {

		this->x -= v.x;
		this->y -= v.y;

		return *this;
	}

	Vector2& operator*=(const Vector2& v) {

		this->x *= v.x;
		this->y *= v.y;

		return *this;
	}

	Vector2& operator*=(const float& v) {

		this->x *= v;
		this->y *= v;

		return *this;
	}

	Vector2& operator/=(const Vector2& v) {

		if (v.x != 0.0f) {

			this->x /= v.x;
		}
		else {

			this->x = static_cast<float>(std::nan(""));
		}

		if (v.y != 0.0f) {

			this->y /= v.y;
		}
		else {

			this->y = static_cast<float>(std::nan(""));
		}

		return *this;
	}

	Vector2& operator/=(const float& v) {

		if (v != 0.0f) {

			this->x /= v;
			this->y /= v;
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
	float NormalizedDot(Vector2 v) {

		Vector2 temp = *this;

		temp.Normalize();
		v.Normalize();

		return (temp.x * v.x) + (temp.y * v.y);
	}

	// ì‡êœ
	float Dot(Vector2 v) {

		return (x * v.x) + (y * v.y);
	}

	// Ç»Ç∑äp(ìxêîäpìx)
	float DegreesAngle(Vector2 v) {

		return XMConvertToDegrees(acosf(NormalizedDot(v)));
	}

	// Ç»Ç∑äp(ÉâÉWÉAÉìäpìx)
	float RadianAngle(Vector2 v) {

		return acosf(NormalizedDot(v));
	}

	constexpr Vector2(float _x, float _y) : x(_x), y(_y) {}
};

Vector2 operator+ (const XMFLOAT2& x, const Vector2& v);
Vector2 operator+ (const Vector2& v, const XMFLOAT2& x);
Vector2 operator+ (const Vector2& v1, const Vector2& v2);

Vector2 operator- (const XMFLOAT2& x, const Vector2& v);
Vector2 operator- (const Vector2& v, const XMFLOAT2& x);
Vector2 operator- (const Vector2& v1, const Vector2& v2);

Vector2 operator* (const XMFLOAT2& x, const Vector2& v);
Vector2 operator* (const Vector2& v, const XMFLOAT2& x);
Vector2 operator* (const float& f, const Vector2& v);
Vector2 operator* (const Vector2& v, const float& f);
Vector2 operator* (const Vector2& v1, const Vector2& v2);

Vector2 operator/ (const XMFLOAT2& x, const Vector2& v);
Vector2 operator/ (const Vector2& v, const XMFLOAT2& x);
Vector2 operator/ (const Vector2& v, const float& f);
Vector2 operator/ (const Vector2& v1, const Vector2& v2);
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

	Vector3(const XMFLOAT3& value) {

		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
	}
	Vector3& operator= (const XMFLOAT3& value) {

		this->x = value.x;
		this->y = value.y;
		this->z = value.z;

		return *this;
	}

	Vector3(const XMVECTOR& value) {

		this->x = value.m128_f32[0];
		this->y = value.m128_f32[1];
		this->z = value.m128_f32[2];
	}
	Vector3& operator= (const XMVECTOR& value) {

		this->x = value.m128_f32[0];
		this->y = value.m128_f32[1];
		this->z = value.m128_f32[2];

		return *this;
	}

	static Vector3 zero() {

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

	bool operator!=(Vector3 v) {

		return (this->x != v.x || this->y != v.y || this->z != v.z);
	}

	bool operator==(Vector3 v) {

		return (this->x == v.x && this->y == v.y && this->z == v.z);
	}

	Vector3& operator+=(const Vector3& v) {

		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}

	Vector3& operator-=(const Vector3& v) {

		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;

		return *this;
	}

	Vector3& operator*=(const Vector3& v) {

		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;

		return *this;
	}

	Vector3& operator*=(const float& v) {

		this->x *= v;
		this->y *= v;
		this->z *= v;

		return *this;
	}

	Vector3& operator/=(const Vector3& v) {

		if (v.x != 0.0f) {

			this->x /= v.x;
		}
		else {

			this->x = static_cast<float>(std::nan(""));
		}

		if (v.y != 0.0f) {

			this->y /= v.y;
		}
		else {

			this->y = static_cast<float>(std::nan(""));
		}

		if (v.z != 0.0f) {

			this->z /= v.z;
		}
		else {

			this->z = static_cast<float>(std::nan(""));
		}

		return *this;
	}

	Vector3& operator/=(const float& v) {

		if (v != 0.0f) {

			this->x /= v;
			this->y /= v;
			this->z /= v;
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
	float NormalizedDot(Vector3 v) {

		Vector3 temp = *this;

		temp.Normalize();
		v.Normalize();

		return (temp.x * v.x) + (temp.y * v.y) + (temp.z * v.z);
	}

	// ì‡êœ
	float Dot(Vector3 v) {

		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	//Å@äOêœ(ê≥ãKâªçœÇ›)
	Vector3 NormalizedCloss(Vector3 v) {

		Vector3 closs = Vector3::zero();
		Vector3 temp = *this;

		temp.Normalize();
		v.Normalize();

		closs.x = (temp.y * v.z - temp.z * v.y);
		closs.y = (temp.z * v.x - temp.x * v.z);
		closs.z = (temp.x * v.y - temp.y * v.x);

		return closs;
	}

	// äOêœ
	Vector3 Closs(Vector3 v) {

		Vector3 closs = Vector3::zero();

		closs.x = (y * v.z - z * v.y);
		closs.y = (z * v.x - x * v.z);
		closs.z = (x * v.y - y * v.x);

		return closs;
	}

	// Ç»Ç∑äp(ìxêîäpìx)
	float DegreesAngle(Vector3 v) {

		return XMConvertToDegrees(acosf(NormalizedDot(v)));
	}

	// Ç»Ç∑äp(ÉâÉWÉAÉìäpìx)
	float RadianAngle(Vector3 v) {

		return acosf(NormalizedDot(v));
	}

	constexpr Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	constexpr Vector3(float _x, float _y) : x(_x), y(_y), z(0) {}
};

Vector3 operator+ (const XMFLOAT3& x, const Vector3& v);
Vector3 operator+ (const Vector3& v, const XMFLOAT3& x);
Vector3 operator+ (const Vector3& v1, const Vector3& v2);

Vector3 operator- (const XMFLOAT3& x, const Vector3& v);
Vector3 operator- (const Vector3& v, const XMFLOAT3& x);
Vector3 operator- (const Vector3& v1, const Vector3& v2);

Vector3 operator* (const XMFLOAT3& x, const Vector3& v);
Vector3 operator* (const Vector3& v, const XMFLOAT3& x);
Vector3 operator* (const float& f, const Vector3& v);
Vector3 operator* (const Vector3& v, const float& f);
Vector3 operator* (const Vector3& v1, const Vector3& v2);

Vector3 operator/ (const XMFLOAT3& x, const Vector3& v);
Vector3 operator/ (const Vector3& v, const XMFLOAT3& x);
Vector3 operator/ (const Vector3& v, const float& f);
Vector3 operator/ (const Vector3& v1, const Vector3& v2);
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

	Vector4(const XMFLOAT4& value) {

		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;
	}
	Vector4& operator= (const XMFLOAT4& value) {

		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;

		return *this;
	}

	Vector4(const XMVECTOR& value) {

		this->x = value.m128_f32[0];
		this->y = value.m128_f32[1];
		this->z = value.m128_f32[2];
		this->w = value.m128_f32[3];
	}
	Vector4& operator= (const XMVECTOR& value) {

		this->x = value.m128_f32[0];
		this->y = value.m128_f32[1];
		this->z = value.m128_f32[2];
		this->w = value.m128_f32[3];

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

	bool operator!=(Vector4 v) {

		return (this->x != v.x || this->y != v.y || this->z != v.z || this->w != v.w);
	}

	bool operator==(Vector4 v) {

		return (this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w);
	}

	Vector4& operator+=(const Vector4& v) {

		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		this->w += v.w;

		return *this;
	}

	Vector4& operator-=(const Vector4& v) {

		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		this->w -= v.w;

		return *this;
	}

	Vector4& operator*=(const Vector4& v) {

		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		this->w *= v.w;

		return *this;
	}

	Vector4& operator*=(const float& v) {

		this->x *= v;
		this->y *= v;
		this->z *= v;
		this->w *= v;

		return *this;
	}

	Vector4& operator/=(const Vector4& v) {

		if (v.x != 0.0f) {

			this->x /= v.x;
		}
		else {

			this->x = static_cast<float>(std::nan(""));
		}

		if (v.y != 0.0f) {

			this->y /= v.y;
		}
		else {

			this->y = static_cast<float>(std::nan(""));
		}

		if (v.z != 0.0f) {

			this->z /= v.z;
		}
		else {

			this->z = static_cast<float>(std::nan(""));
		}

		if (v.w != 0.0f) {

			this->w /= v.w;
		}
		else {

			this->w = static_cast<float>(std::nan(""));
		}

		return *this;
	}

	Vector4& operator/=(const float& v) {

		if (v != 0.0f) {

			this->x /= v;
			this->y /= v;
			this->z /= v;
			this->w /= v;
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
	float NormalizedDot(Vector4 v) {

		Vector4 temp = *this;

		temp.Normalize();
		v.Normalize();

		return (temp.x * v.x) + (temp.y * v.y) + (temp.z * v.z);
	}

	// ì‡êœ
	float Dot(Vector4 v) {

		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	// Ç»Ç∑äp(ìxêîäpìx)
	float DegreesAngle(Vector4 v) {

		return XMConvertToDegrees(acosf(NormalizedDot(v)));
	}

	// Ç»Ç∑äp(ÉâÉWÉAÉìäpìx)
	float RadianAngle(Vector4 v) {

		return acosf(NormalizedDot(v));
	}

	constexpr Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	constexpr Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(0) {}
	constexpr Vector4(float _x, float _y) : x(_x), y(_y), z(0), w(0) {}
};

Vector4 operator+ (const XMFLOAT4& x, const Vector4& v);
Vector4 operator+ (const Vector4& v, const XMFLOAT4& x);
Vector4 operator+ (const Vector4& v1, const Vector4& v2);

Vector4 operator- (const XMFLOAT4& x, const Vector4& v);
Vector4 operator- (const Vector4& v, const XMFLOAT4& x);
Vector4 operator- (const Vector4& v1, const Vector4& v2);

Vector4 operator* (const XMFLOAT4& x, const Vector4& v);
Vector4 operator* (const Vector4& v, const XMFLOAT4& x);
Vector4 operator* (const float& f, const Vector4& v);
Vector4 operator* (const Vector4& v, const float& f);
Vector4 operator* (const Vector4& v1, const Vector4& v2);

Vector4 operator/ (const XMFLOAT4& x, const Vector4& v);
Vector4 operator/ (const Vector4& v, const XMFLOAT4& x);
Vector4 operator/ (const Vector4& v, const float& f);
Vector4 operator/ (const Vector4& v1, const Vector4& v2);
#pragma endregion

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

	Vector2Int(const XMINT2& value) {

		this->x = value.x;
		this->y = value.y;
	}
	Vector2Int& operator= (const XMINT2& value) {

		this->x = value.x;
		this->y = value.y;

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

	bool operator!=(Vector2Int v) {

		return (this->x != v.x || this->y != v.y);
	}

	bool operator==(Vector2Int v) {

		return (this->x == v.x && this->y == v.y);
	}

	Vector2Int& operator+=(const Vector2Int& v) {

		this->x += v.x;
		this->y += v.y;

		return *this;
	}

	Vector2Int& operator-=(const Vector2Int& v) {

		this->x -= v.x;
		this->y -= v.y;

		return *this;
	}

	Vector2Int& operator*=(const Vector2Int& v) {

		this->x *= v.x;
		this->y *= v.y;

		return *this;
	}

	Vector2Int& operator*=(const int32_t& v) {

		this->x *= v;
		this->y *= v;

		return *this;
	}

	Vector2Int& operator/=(const Vector2Int& v) {

		if (v.x != 0) {

			this->x /= v.x;
		}
		else {

			this->x = static_cast<int32_t>(std::nan(""));
		}

		if (v.y != 0) {

			this->y /= v.y;
		}
		else {

			this->y = static_cast<int32_t>(std::nan(""));
		}

		return *this;
	}

	Vector2Int& operator/=(const int32_t& v) {

		if (v != 0) {

			this->x /= v;
			this->y /= v;
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

Vector2Int operator+ (const XMINT2& x, const Vector2Int& v);
Vector2Int operator+ (const Vector2Int& v, const XMINT2& x);
Vector2Int operator+ (const Vector2Int& v1, const Vector2Int& v2);

Vector2Int operator- (const XMINT2& x, const Vector2Int& v);
Vector2Int operator- (const Vector2Int& v, const XMINT2& x);
Vector2Int operator- (const Vector2Int& v1, const Vector2Int& v2);

Vector2Int operator* (const XMINT2& x, const Vector2Int& v);
Vector2Int operator* (const Vector2Int& v, const XMINT2& x);
Vector2Int operator* (const int32_t& f, const Vector2Int& v);
Vector2Int operator* (const Vector2Int& v, const int32_t& f);
Vector2Int operator* (const Vector2Int& v1, const Vector2Int& v2);

Vector2Int operator/ (const XMINT2& x, const Vector2Int& v);
Vector2Int operator/ (const Vector2Int& v, const XMINT2& x);
Vector2Int operator/ (const Vector2Int& v, const int32_t& f);
Vector2Int operator/ (const Vector2Int& v1, const Vector2Int& v2);
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

	Vector3Int(const XMINT3& value) {

		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
	}
	Vector3Int& operator= (const XMINT3& value) {

		this->x = value.x;
		this->y = value.y;
		this->z = value.z;

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

	bool operator!=(Vector3Int v) {

		return (this->x != v.x || this->y != v.y || this->z != v.z);
	}

	bool operator==(Vector3Int v) {

		return (this->x == v.x && this->y == v.y && this->z == v.z);
	}

	Vector3Int& operator+=(const Vector3Int& v) {

		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}

	Vector3Int& operator-=(const Vector3Int& v) {

		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;

		return *this;
	}

	Vector3Int& operator*=(const Vector3Int& v) {

		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;

		return *this;
	}

	Vector3Int& operator*=(const int32_t& v) {

		this->x *= v;
		this->y *= v;
		this->z *= v;

		return *this;
	}

	Vector3Int& operator/=(const Vector3Int& v) {

		if (v.x != 0) {

			this->x /= v.x;
		}
		else {

			this->x = static_cast<int32_t>(std::nan(""));
		}

		if (v.y != 0) {

			this->y /= v.y;
		}
		else {

			this->y = static_cast<int32_t>(std::nan(""));
		}

		if (v.z != 0) {

			this->z /= v.z;
		}
		else {

			this->z = static_cast<int32_t>(std::nan(""));
		}

		return *this;
	}

	Vector3Int& operator/=(const int32_t& v) {

		if (v != 0) {

			this->x /= v;
			this->y /= v;
			this->z /= v;
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

Vector3Int operator+ (const XMINT3& x, const Vector3Int& v);
Vector3Int operator+ (const Vector3Int& v, const XMINT3& x);
Vector3Int operator+ (const Vector3Int& v1, const Vector3Int& v2);

Vector3Int operator- (const XMINT3& x, const Vector3Int& v);
Vector3Int operator- (const Vector3Int& v, const XMINT3& x);
Vector3Int operator- (const Vector3Int& v1, const Vector3Int& v2);

Vector3Int operator* (const XMINT3& x, const Vector3Int& v);
Vector3Int operator* (const Vector3Int& v, const XMINT3& x);
Vector3Int operator* (const int32_t& f, const Vector3Int& v);
Vector3Int operator* (const Vector3Int& v, const int32_t& f);
Vector3Int operator* (const Vector3Int& v1, const Vector3Int& v2);

Vector3Int operator/ (const XMINT3& x, const Vector3Int& v);
Vector3Int operator/ (const Vector3Int& v, const XMINT3& x);
Vector3Int operator/ (const Vector3Int& v, const int32_t& f);
Vector3Int operator/ (const Vector3Int& v1, const Vector3Int& v2);
#pragma endregion

template <class T>  class Property {

public:

	T& value;

	operator T()
	{
		// getÇ™ê›íËÇ≥ÇÍÇƒÇÍÇŒìoò^Ç≥ÇÍÇΩÇŸÇ§ÇåƒÇ‘
		return this->value;
	}

	void operator=(const Property& pro) {

		this->value = pro.value;
	};

	void operator =(const T v)
	{
		value = v;
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