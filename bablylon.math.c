#include <stdio.h>
#include <emscripten.h>

typedef struct{
	float x;
	float y;
	float z;
}Vector3;

typedef struct{
	float x;
	float y;
}Vector2;

typedef float Matrix;

EMSCRIPTEN_KEEPALIVE 
void TransformCoordinatesToRef(const Vector3* vector, const Matrix* transformation, Vector3* result) {
	float x = (vector->x * transformation[0]) + (vector->y * transformation[4]) + (vector->z * transformation[8]) + transformation[12];
	float y = (vector->x * transformation[1]) + (vector->y * transformation[5]) + (vector->z * transformation[9]) + transformation[13];
	float z = (vector->x * transformation[2]) + (vector->y * transformation[6]) + (vector->z * transformation[10]) + transformation[14];
	float w = (vector->x * transformation[3]) + (vector->y * transformation[7]) + (vector->z * transformation[11]) + transformation[15];
	result->x = x / w;
	result->y = y / w;
	result->z = z / w;
}
EMSCRIPTEN_KEEPALIVE
void TransformCoordinatesFromFloatsToRef(float x,float y,float z,const Matrix* transformation, Vector3* result) {
	float rx = (x * transformation[0]) + (y * transformation[4]) + (z * transformation[8]) + transformation[12];
	float ry = (x * transformation[1]) + (y * transformation[5]) + (z * transformation[9]) + transformation[13];
	float rz = (x * transformation[2]) + (y * transformation[6]) + (z * transformation[10]) + transformation[14];
	float rw = (x * transformation[3]) + (y * transformation[7]) + (z * transformation[11]) + transformation[15];
	result->x = rx / rw;
	result->x = ry / rw;
	result->x = rz / rw;
}
EMSCRIPTEN_KEEPALIVE
void TransformNormalToRef(const Vector3* vector, const Matrix* transformation, Vector3* result) {
    float x = (vector->x * transformation[0]) + (vector->y * transformation[4]) + (vector->z * transformation[8]);
    float y = (vector->x * transformation[1]) + (vector->y * transformation[5]) + (vector->z * transformation[9]);
    float z = (vector->x * transformation[2]) + (vector->y * transformation[6]) + (vector->z * transformation[10]);
    result->x = x;
    result->y = y;
    result->z = z;
}
EMSCRIPTEN_KEEPALIVE
void TransformNormalFromFloatsToRef(float x,float y,float z,const Matrix* transformation, Vector3* result) {
    result->x = (x * transformation[0]) + (y * transformation[4]) + (z * transformation[8]);
    result->y = (x * transformation[1]) + (y * transformation[5]) + (z * transformation[9]);
    result->z = (x * transformation[2]) + (y * transformation[6]) + (z * transformation[10]);
}
EMSCRIPTEN_KEEPALIVE
void CatmullRomToRef(const Vector3* value1,const Vector3* value2, const Vector3* value3, const Vector3* value4,float amount,Vector3* result) {
    float squared = amount * amount;
    float cubed = amount * squared;

    float x = 0.5 * ((((2.0 * value2->x) + ((-value1->x + value3->x) * amount)) +
        (((((2.0 * value1->x) - (5.0 * value2->x)) + (4.0 * value3->x)) - value4->x) * squared)) +
        ((((-value1->x + (3.0 * value2->x)) - (3.0 * value3->x)) + value4->x) * cubed));

    float y = 0.5 * ((((2.0 * value2->y) + ((-value1->y + value3->y) * amount)) +
        (((((2.0 * value1->y) - (5.0 * value2->y)) + (4.0 * value3->y)) - value4->y) * squared)) +
        ((((-value1->y + (3.0 * value2->y)) - (3.0 * value3->y)) + value4->y) * cubed));

    float z = 0.5 * ((((2.0 * value2->z) + ((-value1->z + value3->z) * amount)) +
        (((((2.0 * value1->z) - (5.0 * value2->z)) + (4.0 * value3->z)) - value4->z) * squared)) +
        ((((-value1->z + (3.0 * value2->z)) - (3.0 * value3->z)) + value4->z) * cubed));

    result->x = x;
 	result->y = y;
    result->z = z;
       
}
EMSCRIPTEN_KEEPALIVE
void ClampToRef(const Vector3* value,const Vector3* min,const Vector3* max,Vector3* result) {
    float x = value->x;
    x = (x > max->x) ? max->x : x;
    x = (x < min->x) ? min->x : x;

    float y = value->y;
    y = (y > max->y) ? max->y : y;
    y = (y < min->y) ? min->y : y;

    float z = value->z;
    z = (z > max->z) ? max->z : z;
    z = (z < min->z) ? min->z : z;

    result->x = x;
 	result->y = y;
    result->z = z;
}
EMSCRIPTEN_KEEPALIVE
void HermiteToRef(const Vector3* value1,const Vector3* tangent1, const Vector3* value2,const Vector3* tangent2, float amount,Vector3* result){
    float squared = amount * amount;
    float cubed = amount * squared;
    float part1 = ((2.0 * cubed) - (3.0 * squared)) + 1.0;
    float part2 = (-2.0 * cubed) + (3.0 * squared);
    float part3 = (cubed - (2.0 * squared)) + amount;
    float part4 = cubed - squared;

    float x = (((value1->x * part1) + (value2->x * part2)) + (tangent1->x * part3)) + (tangent2->x * part4);
    float y = (((value1->y * part1) + (value2->y * part2)) + (tangent1->y * part3)) + (tangent2->y * part4);
    float z = (((value1->z * part1) + (value2->z * part2)) + (tangent1->z * part3)) + (tangent2->z * part4);
    result->x = x;
 	result->y = y;
    result->z = z;
}