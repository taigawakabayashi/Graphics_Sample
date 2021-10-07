#include "Math.h"
#pragma region Vector2 operator

// XMFLOAT2 + Vector2
Vector2 operator+ (const XMFLOAT2& _x, const Vector2& _v) {

	return Vector2(_v.x + _x.x, _v.y + _x.y);
}

// Vector2 + XMFLOAT2
Vector2 operator+ (const Vector2& _v, const XMFLOAT2& _x) {

	return Vector2(_v.x + _x.x, _v.y + _x.y);
}

// Vector2 + Vector2
Vector2 operator+ (const Vector2& _v1, const Vector2& _v2) {

	return Vector2(_v1.x + _v2.x, _v1.y + _v2.y);
}

// XMFLOAT2 - Vector2
Vector2 operator- (const XMFLOAT2& _x, const Vector2& _v) {

	return Vector2(_x.x - _v.x, _x.y - _v.y);
}

// Vector2 - XMFLOAT2
Vector2 operator- (const Vector2& _v, const XMFLOAT2& _x) {

	return Vector2(_v.x - _x.x, _v.y - _x.y);
}

// Vector2 - Vector2
Vector2 operator- (const Vector2& _v1, const Vector2& _v2) {

	return Vector2(_v1.x - _v2.x, _v1.y - _v2.y);
}

// XMFLOAT2 * Vector2
Vector2 operator* (const XMFLOAT2& _x, const Vector2& _v) {

	return Vector2(_v.x * _x.x, _v.y * _x.y);
}

// Vector2 * XMFLOAT2
Vector2 operator* (const Vector2& _v, const XMFLOAT2& _x) {

	return Vector2(_v.x * _x.x, _v.y * _x.y);
}

// float * Vector2
Vector2 operator* (const float& _f, const Vector2& _v) {

	return Vector2(_v.x * _f, _v.y * _f);
}

// Vector2 * float;
Vector2 operator* (const Vector2& _v, const float& _f) {

	return Vector2(_v.x * _f, _v.y * _f);
}

// Vector2 * Vector2
Vector2 operator* (const Vector2& _v1, const Vector2& _v2) {

	return Vector2(_v1.x * _v2.x, _v1.y * _v2.y);
}

// XMFLOAT2 / Vector2
Vector2 operator/ (const XMFLOAT2& _x, const Vector2& _v) {

	Vector2 temp = Vector2::zero();

	if (_v.x != 0.0f) {

		temp.x = _x.x / _v.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (_v.y != 0.0f) {

		temp.y = _x.y / _v.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector2 / XMFLOAT2
Vector2 operator/ (const Vector2& _v, const XMFLOAT2& _x) {

	Vector2 temp = Vector2::zero();

	if (_x.x != 0.0f) {

		temp.x = _v.x / _x.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (_x.y != 0.0f) {

		temp.y = _v.y / _x.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector2 / float;
Vector2 operator/ (const Vector2& _v, const float& _f) {

	Vector2 temp = Vector2::zero();

	if (_f != 0.0f) {

		temp.x = _v.x / _f;
		temp.y = _v.y / _f;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector2 / Vector2
Vector2 operator/ (const Vector2& _v1, const Vector2& _v2) {

	Vector2 temp = Vector2::zero();

	if (_v2.x != 0.0f) {

		temp.x = _v1.x / _v2.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (_v2.y != 0.0f) {

		temp.y = _v1.y / _v2.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector3 operator

// XMFLOAT3 + Vector3
Vector3 operator+ (const XMFLOAT3& _x, const Vector3& _v) {

	return Vector3(_v.x + _x.x, _v.y + _x.y, _v.z + _x.z);
}

// Vector3 + XMFLOAT3
Vector3 operator+ (const Vector3& _v, const XMFLOAT3& _x) {

	return Vector3(_v.x + _x.x, _v.y + _x.y, _v.z + _x.z);
}

// Vector3 + Vector3
Vector3 operator+ (const Vector3& _v1, const Vector3& _v2) {

	return Vector3(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z);
}

// XMFLOAT3 - Vector3
Vector3 operator- (const XMFLOAT3& _x, const Vector3& _v) {

	return Vector3(_x.x - _v.x, _x.y - _v.y, _x.z - _v.z);
}

// Vector3 - XMFLOAT3
Vector3 operator- (const Vector3& _v, const XMFLOAT3& _x) {

	return Vector3(_v.x - _x.x, _v.y - _x.y, _v.z - _x.z);
}

// Vector3 - Vector3
Vector3 operator- (const Vector3& _v1, const Vector3& _v2) {

	return Vector3(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z);
}

// XMFLOAT3 * Vector3
Vector3 operator* (const XMFLOAT3& _x, const Vector3& _v) {

	return Vector3(_v.x * _x.x, _v.y * _x.y, _v.z * _x.z);
}

// Vector3 * XMFLOAT3
Vector3 operator* (const Vector3& _v, const XMFLOAT3& _x) {

	return Vector3(_v.x * _x.x, _v.y * _x.y, _v.z * _x.z);
}

// float * Vector3
Vector3 operator* (const float& _f, const Vector3& _v) {

	return Vector3(_v.x * _f, _v.y * _f, _v.z * _f);
}

// Vector3 * float;
Vector3 operator* (const Vector3& _v, const float& _f) {

	return Vector3(_v.x * _f, _v.y * _f, _v.z * _f);
}

// Vector3 * Vector3
Vector3 operator* (const Vector3& _v1, const Vector3& _v2) {

	return Vector3(_v1.x * _v2.x, _v1.y * _v2.y, _v1.z * _v2.z);
}

// XMFLOAT3 / Vector3
Vector3 operator/ (const XMFLOAT3& _x, const Vector3& _v) {

	Vector3 temp = Vector3::zero();

	if (_v.x != 0.0f) {

		temp.x = _x.x / _v.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (_v.y != 0.0f) {

		temp.y = _x.y / _v.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (_v.z != 0.0f) {

		temp.z = _x.z / _v.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector3 / XMFLOAT3
Vector3 operator/ (const Vector3& _v, const XMFLOAT3& _x) {

	Vector3 temp = Vector3::zero();

	if (_x.x != 0.0f) {

		temp.x = _v.x / _x.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (_x.y != 0.0f) {

		temp.y = _v.y / _x.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (_x.z != 0.0f) {

		temp.z = _v.z / _x.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector3 / float;
Vector3 operator/ (const Vector3& _v, const float& _f) {

	Vector3 temp = Vector3::zero();

	if (_f != 0.0f) {

		temp.x = _v.x / _f;
		temp.y = _v.y / _f;
		temp.z = _v.z / _f;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
		temp.y = static_cast<float>(std::nan(""));
		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector3 / Vector3
Vector3 operator/ (const Vector3& _v1, const Vector3& _v2) {

	Vector3 temp = Vector3::zero();

	if (_v2.x != 0.0f) {

		temp.x = _v1.x / _v2.x;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (_v2.y != 0.0f) {

		temp.y = _v1.y / _v2.y;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (_v2.z != 0.0f) {

		temp.z = _v1.z / _v2.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector4 operator

// XMFLOAT4 + Vector4
Vector4 operator+ (const XMFLOAT4& _x, const Vector4& _v) {

	return Vector4(_v.x + _x.x, _v.y + _x.y, _v.z + _x.z, _v.w + _x.w);
}

// Vector4 + XMFLOAT4
Vector4 operator+ (const Vector4& _v, const XMFLOAT4& _x) {

	return Vector4(_v.x + _x.x, _v.y + _x.y, _v.z + _x.z, _v.w + _x.w);
}

// Vector4 + Vector4
Vector4 operator+ (const Vector4& _v1, const Vector4& _v2) {

	return Vector4(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z, _v1.w + _v2.w);
}

// XMFLOAT4 - Vector4
Vector4 operator- (const XMFLOAT4& _x, const Vector4& _v) {

	return Vector4(_x.x - _v.x, _x.y - _v.y, _x.z - _v.z, _x.w - _v.w);
}

// Vector4 - XMFLOAT4
Vector4 operator- (const Vector4& _v, const XMFLOAT4& _x) {

	return Vector4(_v.x - _x.x, _v.y - _x.y, _v.z - _x.z, _v.w - _x.w);
}

// Vector4 - Vector4
Vector4 operator- (const Vector4& _v1, const Vector4& _v2) {

	return Vector4(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z, _v1.w - _v2.w);
}

// XMFLOAT4 * Vector4
Vector4 operator* (const XMFLOAT4& _x, const Vector4& _v) {

	return Vector4(_v.x * _x.x, _v.y * _x.y, _v.z * _x.z, _v.w * _x.w);
}

// Vector4 * XMFLOAT4
Vector4 operator* (const Vector4& _v, const XMFLOAT4& _x) {

	return Vector4(_v.x * _x.x, _v.y * _x.y, _v.z * _x.z, _v.w * _x.w);
}

// float * Vector4
Vector4 operator* (const float& _f, const Vector4& _v) {

	return Vector4(_v.x * _f, _v.y * _f, _v.z * _f, _v.w * _f);
}

// Vector4 * float;
Vector4 operator* (const Vector4& _v, const float& _f) {

	return Vector4(_v.x * _f, _v.y * _f, _v.z * _f, _v.w * _f);
}

// Vector4 * Vector4
Vector4 operator* (const Vector4& _v1, const Vector4& _v2) {

	return Vector4(_v1.x * _v2.x, _v1.y * _v2.y, _v1.z * _v2.z, _v1.w * _v2.w);
}

// XMFLOAT4 / Vector4
Vector4 operator/ (const XMFLOAT4& _x, const Vector4& _v) {

	Vector4 temp = Vector4::zero();

	if (_v.x != 0.0f) {

		temp.x = _x.x / _v.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (_v.y != 0.0f) {

		temp.y = _x.y / _v.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (_v.z != 0.0f) {

		temp.z = _x.z / _v.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (_v.w != 0.0f) {

		temp.w = _x.w / _v.w;
	}
	else {

		temp.w = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector4 / XMFLOAT4
Vector4 operator/ (const Vector4& _v, const XMFLOAT4& _x) {

	Vector4 temp = Vector4::zero();

	if (_x.x != 0.0f) {

		temp.x = _v.x / _x.x;
	}
	else {

		temp.x = static_cast<float>(std::nan(""));
	}

	if (_x.y != 0.0f) {

		temp.y = _v.y / _x.y;
	}
	else {

		temp.y = static_cast<float>(std::nan(""));
	}

	if (_x.z != 0.0f) {

		temp.z = _v.z / _x.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (_x.w != 0.0f) {

		temp.w = _v.w / _x.w;
	}
	else {

		temp.w = static_cast<float>(std::nan(""));
	}

	return temp;
}

// Vector4 / float;
Vector4 operator/ (const Vector4& _v, const float& _f) {

	Vector4 temp = Vector4::zero();

	if (_f != 0.0f) {

		temp.x = _v.x / _f;
		temp.y = _v.y / _f;
		temp.z = _v.z / _f;
		temp.w = _v.w / _f;
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
Vector4 operator/ (const Vector4& _v1, const Vector4& _v2) {

	Vector4 temp = Vector4::zero();

	if (_v2.x != 0.0f) {

		temp.x = _v1.x / _v2.x;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (_v2.y != 0.0f) {

		temp.y = _v1.y / _v2.y;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (_v2.z != 0.0f) {

		temp.z = _v1.z / _v2.z;
	}
	else {

		temp.z = static_cast<float>(std::nan(""));
	}

	if (_v2.w != 0.0f) {

		temp.w = _v1.w / _v2.w;
	}
	else {

		temp.w = static_cast<float>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector2Int operator

// XMINT2 + Vector2Int
Vector2Int operator+ (const XMINT2& _x, const Vector2Int& _v) {

	return Vector2Int(_v.x + _x.x, _v.y + _x.y);
}

// Vector2Int + XMINT2
Vector2Int operator+ (const Vector2Int& _v, const XMINT2& _x) {

	return Vector2Int(_v.x + _x.x, _v.y + _x.y);
}

// Vector2Int + Vector2Int
Vector2Int operator+ (const Vector2Int& _v1, const Vector2Int& _v2) {

	return Vector2Int(_v1.x + _v2.x, _v1.y + _v2.y);
}

// XMINT2 - Vector2Int
Vector2Int operator- (const XMINT2& _x, const Vector2Int& _v) {

	return Vector2Int(_x.x - _v.x, _x.y - _v.y);
}

// Vector2Int - XMINT2
Vector2Int operator- (const Vector2Int& _v, const XMINT2& _x) {

	return Vector2Int(_v.x - _x.x, _v.y - _x.y);
}

// Vector2Int - Vector2Int
Vector2Int operator- (const Vector2Int& _v1, const Vector2Int& _v2) {

	return Vector2Int(_v1.x - _v2.x, _v1.y - _v2.y);
}

// XMINT2 * Vector2Int
Vector2Int operator* (const XMINT2& _x, const Vector2Int& _v) {

	return Vector2Int(_v.x * _x.x, _v.y * _x.y);
}

// Vector2Int * XMINT2
Vector2Int operator* (const Vector2Int& _v, const XMINT2& _x) {

	return Vector2Int(_v.x * _x.x, _v.y * _x.y);
}

// int32_t * Vector2Int
Vector2Int operator* (const int32_t& f, const Vector2Int& _v) {

	return Vector2Int(_v.x * f, _v.y * f);
}

// Vector2Int * int32_t;
Vector2Int operator* (const Vector2Int& _v, const int32_t& f) {

	return Vector2Int(_v.x * f, _v.y * f);
}

// Vector2Int * Vector2Int
Vector2Int operator* (const Vector2Int& _v1, const Vector2Int& _v2) {

	return Vector2Int(_v1.x * _v2.x, _v1.y * _v2.y);
}

// XMINT2 / Vector2Int
Vector2Int operator/ (const XMINT2& _x, const Vector2Int& _v) {

	Vector2Int temp = Vector2Int::zero();

	if (_v.x != 0) {

		temp.x = _x.x / _v.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (_v.y != 0) {

		temp.y = _x.y / _v.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector2Int / XMINT2
Vector2Int operator/ (const Vector2Int& _v, const XMINT2& _x) {

	Vector2Int temp = Vector2Int::zero();

	if (_x.x != 0) {

		temp.x = _v.x / _x.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (_x.y != 0) {

		temp.y = _v.y / _x.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector2Int / int32_t;
Vector2Int operator/ (const Vector2Int& _v, const int32_t& f) {

	Vector2Int temp = Vector2Int::zero();

	if (f != 0) {

		temp.x = _v.x / f;
		temp.y = _v.y / f;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector2Int / Vector2Int
Vector2Int operator/ (const Vector2Int& _v1, const Vector2Int& _v2) {

	Vector2Int temp = Vector2Int::zero();

	if (_v2.x != 0) {

		temp.x = _v1.x / _v2.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (_v2.y != 0) {

		temp.y = _v1.y / _v2.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}
#pragma endregion

#pragma region Vector3Int operator

// XMINT3 + Vector3Int
Vector3Int operator+ (const XMINT3& _x, const Vector3Int& _v) {

	return Vector3Int(_v.x + _x.x, _v.y + _x.y, _v.z + _x.z);
}

// Vector3Int + XMINT3
Vector3Int operator+ (const Vector3Int& _v, const XMINT3& _x) {

	return Vector3Int(_v.x + _x.x, _v.y + _x.y, _v.z + _x.z);
}

// Vector3Int + Vector3Int
Vector3Int operator+ (const Vector3Int& _v1, const Vector3Int& _v2) {

	return Vector3Int(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z);
}

// XMINT3 - Vector3Int
Vector3Int operator- (const XMINT3& _x, const Vector3Int& _v) {

	return Vector3Int(_x.x - _v.x, _x.y - _v.y, _x.z - _v.z);
}

// Vector3Int - XMINT3
Vector3Int operator- (const Vector3Int& _v, const XMINT3& _x) {

	return Vector3Int(_v.x - _x.x, _v.y - _x.y, _v.z - _x.z);
}

// Vector3Int - Vector3Int
Vector3Int operator- (const Vector3Int& _v1, const Vector3Int& _v2) {

	return Vector3Int(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z);
}

// XMINT3 * Vector3Int
Vector3Int operator* (const XMINT3& _x, const Vector3Int& _v) {

	return Vector3Int(_v.x * _x.x, _v.y * _x.y, _v.z * _x.z);
}

// Vector3Int * XMINT3
Vector3Int operator* (const Vector3Int& _v, const XMINT3& _x) {

	return Vector3Int(_v.x * _x.x, _v.y * _x.y, _v.z * _x.z);
}

// int32_t * Vector3Int
Vector3Int operator* (const int32_t& _i, const Vector3Int& _v) {

	return Vector3Int(_v.x * _i, _v.y * _i, _v.z * _i);
}

// Vector3Int * int32_t;
Vector3Int operator* (const Vector3Int& _v, const int32_t& _i) {

	return Vector3Int(_v.x * _i, _v.y * _i, _v.z * _i);
}

// Vector3Int * Vector3Int
Vector3Int operator* (const Vector3Int& _v1, const Vector3Int& _v2) {

	return Vector3Int(_v1.x * _v2.x, _v1.y * _v2.y, _v1.z * _v2.z);
}

// XMINT3 / Vector3Int
Vector3Int operator/ (const XMINT3& _x, const Vector3Int& _v) {

	Vector3Int temp = Vector3Int::zero();

	if (_v.x != 0) {

		temp.x = _x.x / _v.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (_v.y != 0) {

		temp.y = _x.y / _v.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	if (_v.z != 0) {

		temp.z = _x.z / _v.z;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector3Int / XMINT3
Vector3Int operator/ (const Vector3Int& _v, const XMINT3& _x) {

	Vector3Int temp = Vector3Int::zero();

	if (_x.x != 0) {

		temp.x = _v.x / _x.x;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
	}

	if (_x.y != 0) {

		temp.y = _v.y / _x.y;
	}
	else {

		temp.y = static_cast<int32_t>(std::nan(""));
	}

	if (_x.z != 0) {

		temp.z = _v.z / _x.z;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector3Int / int32_t;
Vector3Int operator/ (const Vector3Int& _v, const int32_t& _i) {

	Vector3Int temp = Vector3Int::zero();

	if (_i != 0) {

		temp.x = _v.x / _i;
		temp.y = _v.y / _i;
		temp.z = _v.z / _i;
	}
	else {

		temp.x = static_cast<int32_t>(std::nan(""));
		temp.y = static_cast<int32_t>(std::nan(""));
		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}

// Vector3Int / Vector3Int
Vector3Int operator/ (const Vector3Int& _v1, const Vector3Int& _v2) {

	Vector3Int temp = Vector3Int::zero();

	if (_v2.x != 0) {

		temp.x = _v1.x / _v2.x;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	if (_v2.y != 0) {

		temp.y = _v1.y / _v2.y;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	if (_v2.z != 0) {

		temp.z = _v1.z / _v2.z;
	}
	else {

		temp.z = static_cast<int32_t>(std::nan(""));
	}

	return temp;
}
#pragma endregion