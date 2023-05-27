#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>
#include <include/project.h>

typedef struct Matrix3 {
    float m0, m3, m6;  // Matrix first row (4 components)
    float m1, m4, m7;  // Matrix second row (4 components)
    float m2, m5, m8; // Matrix third row (4 components)
} Matrix3;

Suite* suite_s21_validate(void);

Vector3 scaleV(Vector3 v, float scale);
Vector3 moveV(Vector3 v, Vector3 move);
Vector3 centerV(Vector3 v1, Vector3 v2);

Matrix3 Matrix3Multiply(Matrix3 a, Matrix3 b) ;
Matrix3 Matrix3RotateX(float angle);
Matrix3 Matrix3RotateY(float angle);
Matrix3 Matrix3RotateZ(float angle);
Vector3 oper(Vector3 vec, Vector3 rotate);

#endif