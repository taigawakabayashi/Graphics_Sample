#include "Math.h"
#pragma region Vector2 operator

// XMFLOAT2 + Vector2
Vector2 operator+ (const XMFLOAT2& x, const Vector2& v) {

	return Vector2(v.x + x.x, v.y + x.y);
}

// Vector2 + XMFLOAT2
Vector2 operator+ (const Vector2& v, const XMFLOAT2& x) {

	return Vector2(v.x + x.x, v.y + x.y);
}

// Vector2 + Vector2
Vector2 operator+ (const Vector2& v1, const Vector2& v2) {

	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

// XMFLOAT2 - Vector2
Vector2 operator- (const XMFLOAT2& x, const Vector2& v) {

	return Vector2(x.x - v.x, x.y - v.y);
}

// Vector2 - XMFLOAT2
Vector2 operator- (const Vector2& v, const XMFLOAT2& x) {

	return Vector2(v.x - x.x, v.y - x.y);
}

// Vector2 - Vector2
Vector2 operator- (const Vector2& v1, const Vector2& v2) {

	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

// XMFLOAT2 * Vector2
Vector2 operator* (const XMFLOAT2& x, const Vector2& v) {

	return Vector2(v.x * x.x, v.y * x.y);
}

// Vector2 * XMFLOAT2
Vector2 operator* (const Vector2& v, const XMFLOAT2& x) {

	return Vector2(v.x * x.x, v.y * x.y);
}

// float * Vector2
Vector2 operator* (const float& f, const Vector2& v) {

	return Vector2(v.x * f, v.y * f);
}

// Vector2 * float;
Vector2 operator* (const Vector2& v, const float& f) {

	return Vector2(v.x * f, v.y * f);
}

// Vector2 * Vector2
Vector2 operator* (const Vector2& v1, const Vector2& v2) {

	return Vector2(v1.x * v2.x, v1.y * v2.y);
}

// XMFLOAT2 / Vector2
Vector2 operator/ (const XMFLOAT2& x, const Vector2& v) {

	Vector2 temp = Vector2::zero();

	if (v.x != 0.0f) {

		temp.x = x.x / v.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (v.y != 0.0f) {

		temp.y = x.y / v.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector2 / XMFLOAT2
Vector2 operator/ (const Vector2& v, const XMFLOAT2& x) {

	Vector2 temp = Vector2::zero();

	if (x.x != 0.0f) {

		temp.x = v.x / x.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (x.y != 0.0f) {

		temp.y = v.y / x.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector2 / float;
Vector2 operator/ (const Vector2& v, const float& f) {

	Vector2 temp = Vector2::zero();

	if (f != 0.0f) {

		temp.x = v.x / f;
		temp.y = v.y / f;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector2 / Vector2
Vector2 operator/ (const Vector2& v1, const Vector2& v2) {

	Vector2 temp = Vector2::zero();

	if (v2.x != 0.0f) {

		temp.x = v1.x / v2.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (v2.y != 0.0f) {

		temp.y = v1.y / v2.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector3 operator

// XMFLOAT3 + Vector3
Vector3 operator+ (const XMFLOAT3& x, const Vector3& v) {

	return Vector3(v.x + x.x, v.y + x.y, v.z + x.z);
}

// Vector3 + XMFLOAT3
Vector3 operator+ (const Vector3& v, const XMFLOAT3& x) {

	return Vector3(v.x + x.x, v.y + x.y, v.z + x.z);
}

// Vector3 + Vector3
Vector3 operator+ (const Vector3& v1, const Vector3& v2) {

	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// XMFLOAT3 - Vector3
Vector3 operator- (const XMFLOAT3& x, const Vector3& v) {

	return Vector3(x.x - v.x, x.y - v.y, x.z - v.z);
}

// Vector3 - XMFLOAT3
Vector3 operator- (const Vector3& v, const XMFLOAT3& x) {

	return Vector3(v.x - x.x, v.y - x.y, v.z - x.z);
}

// Vector3 - Vector3
Vector3 operator- (const Vector3& v1, const Vector3& v2) {

	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

// XMFLOAT3 * Vector3
Vector3 operator* (const XMFLOAT3& x, const Vector3& v) {

	return Vector3(v.x * x.x, v.y * x.y, v.z * x.z);
}

// Vector3 * XMFLOAT3
Vector3 operator* (const Vector3& v, const XMFLOAT3& x) {

	return Vector3(v.x * x.x, v.y * x.y, v.z * x.z);
}

// float * Vector3
Vector3 operator* (const float& f, const Vector3& v) {

	return Vector3(v.x * f, v.y * f, v.z * f);
}

// Vector3 * float;
Vector3 operator* (const Vector3& v, const float& f) {

	return Vector3(v.x * f, v.y * f, v.z * f);
}

// Vector3 * Vector3
Vector3 operator* (const Vector3& v1, const Vector3& v2) {

	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

// XMFLOAT3 / Vector3
Vector3 operator/ (const XMFLOAT3& x, const Vector3& v) {

	Vector3 temp = Vector3::zero();

	if (v.x != 0.0f) {

		temp.x = x.x / v.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (v.y != 0.0f) {

		temp.y = x.y / v.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (v.z != 0.0f) {

		temp.z = x.z / v.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector3 / XMFLOAT3
Vector3 operator/ (const Vector3& v, const XMFLOAT3& x) {

	Vector3 temp = Vector3::zero();

	if (x.x != 0.0f) {

		temp.x = v.x / x.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (x.y != 0.0f) {

		temp.y = v.y / x.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (x.z != 0.0f) {

		temp.z = v.z / x.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector3 / float;
Vector3 operator/ (const Vector3& v, const float& f) {

	Vector3 temp = Vector3::zero();

	if (f != 0.0f) {

		temp.x = v.x / f;
		temp.y = v.y / f;
		temp.z = v.z / f;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
		temp.y = static_cast<float>(std::nan(""));
		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector3 / Vector3
Vector3 operator/ (const Vector3& v1, const Vector3& v2) {

	Vector3 temp = Vector3::zero();

	if (v2.x != 0.0f) {

		temp.x = v1.x / v2.x;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (v2.y != 0.0f) {

		temp.y = v1.y / v2.y;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (v2.z != 0.0f) {

		temp.z = v1.z / v2.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector4 operator

// XMFLOAT4 + Vector4
Vector4 operator+ (const XMFLOAT4& x, const Vector4& v) {

	return Vector4(v.x + x.x, v.y + x.y, v.z + x.z, v.w + x.w);
}

// Vector4 + XMFLOAT4
Vector4 operator+ (const Vector4& v, const XMFLOAT4& x) {

	return Vector4(v.x + x.x, v.y + x.y, v.z + x.z, v.w + x.w);
}

// Vector4 + Vector4
Vector4 operator+ (const Vector4& v1, const Vector4& v2) {

	return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

// XMFLOAT4 - Vector4
Vector4 operator- (const XMFLOAT4& x, const Vector4& v) {

	return Vector4(x.x - v.x, x.y - v.y, x.z - v.z, x.w - v.w);
}

// Vector4 - XMFLOAT4
Vector4 operator- (const Vector4& v, const XMFLOAT4& x) {

	return Vector4(v.x - x.x, v.y - x.y, v.z - x.z, v.w - x.w);
}

// Vector4 - Vector4
Vector4 operator- (const Vector4& v1, const Vector4& v2) {

	return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

// XMFLOAT4 * Vector4
Vector4 operator* (const XMFLOAT4& x, const Vector4& v) {

	return Vector4(v.x * x.x, v.y * x.y, v.z * x.z, v.w * x.w);
}

// Vector4 * XMFLOAT4
Vector4 operator* (const Vector4& v, const XMFLOAT4& x) {

	return Vector4(v.x * x.x, v.y * x.y, v.z * x.z, v.w * x.w);
}

// float * Vector4
Vector4 operator* (const float& f, const Vector4& v) {

	return Vector4(v.x * f, v.y * f, v.z * f, v.w * f);
}

// Vector4 * float;
Vector4 operator* (const Vector4& v, const float& f) {

	return Vector4(v.x * f, v.y * f, v.z * f, v.w * f);
}

// Vector4 * Vector4
Vector4 operator* (const Vector4& v1, const Vector4& v2) {

	return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

// XMFLOAT4 / Vector4
Vector4 operator/ (const XMFLOAT4& x, const Vector4& v) {

	Vector4 temp = Vector4::zero();

	if (v.x != 0.0f) {

		temp.x = x.x / v.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (v.y != 0.0f) {

		temp.y = x.y / v.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (v.z != 0.0f) {

		temp.z = x.z / v.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (v.w != 0.0f) {

		temp.w = x.w / v.w;
	}
	else {

		temp.w = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector4 / XMFLOAT4
Vector4 operator/ (const Vector4& v, const XMFLOAT4& x) {

	Vector4 temp = Vector4::zero();

	if (x.x != 0.0f) {

		temp.x = v.x / x.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (x.y != 0.0f) {

		temp.y = v.y / x.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (x.z != 0.0f) {

		temp.z = v.z / x.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (x.w != 0.0f) {

		temp.w = v.w / x.w;
	}
	else {

		temp.w = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector4 / float;
Vector4 operator/ (const Vector4& v, const float& f) {

	Vector4 temp = Vector4::zero();

	if (f != 0.0f) {

		temp.x = v.x / f;
		temp.y = v.y / f;
		temp.z = v.z / f;
		temp.w = v.w / f;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
		temp.y = static_cast<float>(std::nan(""));
		temp.z = static_cast<float>(std::nan(""));
		temp.w = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector4 / Vector4
Vector4 operator/ (const Vector4& v1, const Vector4& v2) {

	Vector4 temp = Vector4::zero();

	if (v2.x != 0.0f) {

		temp.x = v1.x / v2.x;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (v2.y != 0.0f) {

		temp.y = v1.y / v2.y;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (v2.z != 0.0f) {

		temp.z = v1.z / v2.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (v2.w != 0.0f) {

		temp.w = v1.w / v2.w;
	}
	else {

		temp.w = static_cast<float>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector2Int operator

// XMINT2 + Vector2Int
Vector2Int operator+ (const XMINT2& x, const Vector2Int& v) {

	return Vector2Int(v.x + x.x, v.y + x.y);
}

// Vector2Int + XMINT2
Vector2Int operator+ (const Vector2Int& v, const XMINT2& x) {

	return Vector2Int(v.x + x.x, v.y + x.y);
}

// Vector2Int + Vector2Int
Vector2Int operator+ (const Vector2Int& v1, const Vector2Int& v2) {

	return Vector2Int(v1.x + v2.x, v1.y + v2.y);
}

// XMINT2 - Vector2Int
Vector2Int operator- (const XMINT2& x, const Vector2Int& v) {

	return Vector2Int(x.x - v.x, x.y - v.y);
}

// Vector2Int - XMINT2
Vector2Int operator- (const Vector2Int& v, const XMINT2& x) {

	return Vector2Int(v.x - x.x, v.y - x.y);
}

// Vector2Int - Vector2Int
Vector2Int operator- (const Vector2Int& v1, const Vector2Int& v2) {

	return Vector2Int(v1.x - v2.x, v1.y - v2.y);
}

// XMINT2 * Vector2Int
Vector2Int operator* (const XMINT2& x, const Vector2Int& v) {

	return Vector2Int(v.x * x.x, v.y * x.y);
}

// Vector2Int * XMINT2
Vector2Int operator* (const Vector2Int& v, const XMINT2& x) {

	return Vector2Int(v.x * x.x, v.y * x.y);
}

// int32_t * Vector2Int
Vector2Int operator* (const int32_t& f, const Vector2Int& v) {

	return Vector2Int(v.x * f, v.y * f);
}

// Vector2Int * int32_t;
Vector2Int operator* (const Vector2Int& v, const int32_t& f) {

	return Vector2Int(v.x * f, v.y * f);
}

// Vector2Int * Vector2Int
Vector2Int operator* (const Vector2Int& v1, const Vector2Int& v2) {

	return Vector2Int(v1.x * v2.x, v1.y * v2.y);
}

// XMINT2 / Vector2Int
Vector2Int operator/ (const XMINT2& x, const Vector2Int& v) {

	Vector2Int temp = Vector2Int::zero();

	if (v.x != 0) {

		temp.x = x.x / v.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (v.y != 0) {

		temp.y = x.y / v.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector2Int / XMINT2
Vector2Int operator/ (const Vector2Int& v, const XMINT2& x) {

	Vector2Int temp = Vector2Int::zero();

	if (x.x != 0) {

		temp.x = v.x / x.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (x.y != 0) {

		temp.y = v.y / x.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector2Int / int32_t;
Vector2Int operator/ (const Vector2Int& v, const int32_t& f) {

	Vector2Int temp = Vector2Int::zero();

	if (f != 0) {

		temp.x = v.x / f;
		temp.y = v.y / f;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector2Int / Vector2Int
Vector2Int operator/ (const Vector2Int& v1, const Vector2Int& v2) {

	Vector2Int temp = Vector2Int::zero();

	if (v2.x != 0) {

		temp.x = v1.x / v2.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (v2.y != 0) {

		temp.y = v1.y / v2.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector3Int operator

// XMINT3 + Vector3Int
Vector3Int operator+ (const XMINT3& x, const Vector3Int& v) {

	return Vector3Int(v.x + x.x, v.y + x.y, v.z + x.z);
}

// Vector3Int + XMINT3
Vector3Int operator+ (const Vector3Int& v, const XMINT3& x) {

	return Vector3Int(v.x + x.x, v.y + x.y, v.z + x.z);
}

// Vector3Int + Vector3Int
Vector3Int operator+ (const Vector3Int& v1, const Vector3Int& v2) {

	return Vector3Int(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// XMINT3 - Vector3Int
Vector3Int operator- (const XMINT3& x, const Vector3Int& v) {

	return Vector3Int(x.x - v.x, x.y - v.y, x.z - v.z);
}

// Vector3Int - XMINT3
Vector3Int operator- (const Vector3Int& v, const XMINT3& x) {

	return Vector3Int(v.x - x.x, v.y - x.y, v.z - x.z);
}

// Vector3Int - Vector3Int
Vector3Int operator- (const Vector3Int& v1, const Vector3Int& v2) {

	return Vector3Int(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

// XMINT3 * Vector3Int
Vector3Int operator* (const XMINT3& x, const Vector3Int& v) {

	return Vector3Int(v.x * x.x, v.y * x.y, v.z * x.z);
}

// Vector3Int * XMINT3
Vector3Int operator* (const Vector3Int& v, const XMINT3& x) {

	return Vector3Int(v.x * x.x, v.y * x.y, v.z * x.z);
}

// int32_t * Vector3Int
Vector3Int operator* (const int32_t& f, const Vector3Int& v) {

	return Vector3Int(v.x * f, v.y * f, v.z * f);
}

// Vector3Int * int32_t;
Vector3Int operator* (const Vector3Int& v, const int32_t& f) {

	return Vector3Int(v.x * f, v.y * f, v.z * f);
}

// Vector3Int * Vector3Int
Vector3Int operator* (const Vector3Int& v1, const Vector3Int& v2) {

	return Vector3Int(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

// XMINT3 / Vector3Int
Vector3Int operator/ (const XMINT3& x, const Vector3Int& v) {

	Vector3Int temp = Vector3Int::zero();

	if (v.x != 0) {

		temp.x = x.x / v.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (v.y != 0) {

		temp.y = x.y / v.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	if (v.z != 0) {

		temp.z = x.z / v.z;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector3Int / XMINT3
Vector3Int operator/ (const Vector3Int& v, const XMINT3& x) {

	Vector3Int temp = Vector3Int::zero();

	if (x.x != 0) {

		temp.x = v.x / x.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (x.y != 0) {

		temp.y = v.y / x.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	if (x.z != 0) {

		temp.z = v.z / x.z;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector3Int / int32_t;
Vector3Int operator/ (const Vector3Int& v, const int32_t& f) {

	Vector3Int temp = Vector3Int::zero();

	if (f != 0) {

		temp.x = v.x / f;
		temp.y = v.y / f;
		temp.z = v.z / f;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
		temp.y = static_cast<int32_t>(std::nan(""));
		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector3Int / Vector3Int
Vector3Int operator/ (const Vector3Int& v1, const Vector3Int& v2) {

	Vector3Int temp = Vector3Int::zero();

	if (v2.x != 0) {

		temp.x = v1.x / v2.x;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	if (v2.y != 0) {

		temp.y = v1.y / v2.y;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	if (v2.z != 0) {

		temp.z = v1.z / v2.z;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}
#pragma endregion