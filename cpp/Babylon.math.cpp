#ifndef BABYLON_MATH
#define BABYLON_MATH

#include <string>
#include <sstream>

#define tnumber float

#ifdef USE_UNICODE
#define tstring std::wstring
#define tostringstream std::wostringstream
#define S(x) L ## x
#else
#define tstring std::string
#define tostringstream std::ostringstream
#define S(x) x
#endif

class Matrix {
private:
    static Quaternion _tempQuaternion = new Quaternion();
    static Vector3 _xAxis = Vector3.Zero();
    static Vector3 _yAxis = Vector3.Zero();
    static Vector3 _zAxis = Vector3.Zero();
    static unsigned int_updateFlagSeed = 0;
    static Matrix _identityReadOnly = Matrix.Identity();

    bool _isIdentity = false;
    bool _isIdentityDirty = true;
public:
    unsigned int updateFlag;
    tnumber m[16];

public:

    void _markAsUpdated() {
        this->updateFlag = Matrix::_updateFlagSeed++;
        this->_isIdentityDirty = true;
    }

    Matrix() {
        this->_markAsUpdated();
    }

    // Properties

    /**
     * Boolean : True is the matrix is the identity matrix
     */
    bool isIdentity(bool considerAsTextureMatrix = false) {
        if (this->_isIdentityDirty) {
            this->_isIdentityDirty = false;
            if (this->m[0] != 1.0 || this->m[5] != 1.0 || this->m[15] != 1.0) {
                this->_isIdentity = false;
            } else if (this->m[1] != 0.0 || this->m[2] != 0.0 || this->m[3] != 0.0 ||
                    this->m[4] != 0.0 || this->m[6] != 0.0 || this->m[7] != 0.0 ||
                    this->m[8] != 0.0 || this->m[9] != 0.0 || this->m[11] != 0.0 ||
                    this->m[12] != 0.0 || this->m[13] != 0.0 || this->m[14] != 0.0) {
                this->_isIdentity = false;
            } else {
                this->_isIdentity = true;
            }

            if (!considerAsTextureMatrix && this->m[10] != 1.0) {
                this->_isIdentity = false;
            }
        }

        return this->_isIdentity;
    }

    /**
     * Returns the matrix determinant (tnumber).
     */
    tnumber determinant() const {
        tnumber temp1 = (this->m[10] * this->m[15]) - (this->m[11] * this->m[14]);
        tnumber temp2 = (this->m[9] * this->m[15]) - (this->m[11] * this->m[13]);
        tnumber temp3 = (this->m[9] * this->m[14]) - (this->m[10] * this->m[13]);
        tnumber temp4 = (this->m[8] * this->m[15]) - (this->m[11] * this->m[12]);
        tnumber temp5 = (this->m[8] * this->m[14]) - (this->m[10] * this->m[12]);
        tnumber temp6 = (this->m[8] * this->m[13]) - (this->m[9] * this->m[12]);

        return ((((this->m[0] * (((this->m[5] * temp1) - (this->m[6] * temp2)) + (this->m[7] * temp3))) - (this->m[1] * (((this->m[4] * temp1) -
                (this->m[6] * temp4)) + (this->m[7] * temp5)))) + (this->m[2] * (((this->m[4] * temp2) - (this->m[5] * temp4)) + (this->m[7] * temp6)))) -
                (this->m[3] * (((this->m[4] * temp3) - (this->m[5] * temp5)) + (this->m[6] * temp6))));
    }

    // Methods

    /**
     * Returns the matrix underlying array.
     */
    tnumber* toArray() {
        return this->m;
    }

    /**
     * Returns the matrix underlying array.
     */
    tnumber* asArray() {
        return this->toArray();
    }

    /**
     * Inverts in place the Matrix.
     * Returns the Matrix inverted.
     */
    Matrix* invert() {
        this->invertToRef(this);
        return this;
    }

    /**
     * Sets all the matrix elements to zero.
     * Returns the Matrix.
     */
    Matrix* reset() {
        for (int index = 0; index < 16; index++) {
            this->m[index] = 0.0;
        }
        this->_markAsUpdated();
        return this;
    }

    /**
     * Returns a new Matrix as the addition result of the current Matrix and the passed one.
     */
    Matrix* add(const Matrix* other) {
        Matrix* result = new Matrix();
        this->addToRef(other, result);
        return result;
    }

    /**
     * Sets the passed matrix "result" with the ddition result of the current Matrix and the passed one.
     * Returns the Matrix.
     */
    Matrix* addToRef(const Matrix* other, Matrix* result) {
        for (int index = 0; index < 16; index++) {
            result->m[index] = this->m[index] + other->m[index];
        }
        result->_markAsUpdated();
        return this;
    }

    /**
     * Adds in place the passed matrix to the current Matrix.
     * Returns the updated Matrix.
     */
    Matrix* addToSelf(Matrix* other) {
        for (int index = 0; index < 16; index++) {
            this->m[index] += other->m[index];
        }
        this->_markAsUpdated();
        return this;
    }

    /**
     * Sets the passed matrix with the current inverted Matrix.
     * Returns the unmodified current Matrix.
     */
    Matrix* invertToRef(Matrix* other) {
        tnumber l1 = this->m[0];
        tnumber l2 = this->m[1];
        tnumber l3 = this->m[2];
        tnumber l4 = this->m[3];
        tnumber l5 = this->m[4];
        tnumber l6 = this->m[5];
        tnumber l7 = this->m[6];
        tnumber l8 = this->m[7];
        tnumber l9 = this->m[8];
        tnumber l10 = this->m[9];
        tnumber l11 = this->m[10];
        tnumber l12 = this->m[11];
        tnumber l13 = this->m[12];
        tnumber l14 = this->m[13];
        tnumber l15 = this->m[14];
        tnumber l16 = this->m[15];
        tnumber l17 = (l11 * l16) - (l12 * l15);
        tnumber l18 = (l10 * l16) - (l12 * l14);
        tnumber l19 = (l10 * l15) - (l11 * l14);
        tnumber l20 = (l9 * l16) - (l12 * l13);
        tnumber l21 = (l9 * l15) - (l11 * l13);
        tnumber l22 = (l9 * l14) - (l10 * l13);
        tnumber l23 = ((l6 * l17) - (l7 * l18)) + (l8 * l19);
        tnumber l24 = -(((l5 * l17) - (l7 * l20)) + (l8 * l21));
        tnumber l25 = ((l5 * l18) - (l6 * l20)) + (l8 * l22);
        tnumber l26 = -(((l5 * l19) - (l6 * l21)) + (l7 * l22));
        tnumber l27 = 1.0 / ((((l1 * l23) + (l2 * l24)) + (l3 * l25)) + (l4 * l26));
        tnumber l28 = (l7 * l16) - (l8 * l15);
        tnumber l29 = (l6 * l16) - (l8 * l14);
        tnumber l30 = (l6 * l15) - (l7 * l14);
        tnumber l31 = (l5 * l16) - (l8 * l13);
        tnumber l32 = (l5 * l15) - (l7 * l13);
        tnumber l33 = (l5 * l14) - (l6 * l13);
        tnumber l34 = (l7 * l12) - (l8 * l11);
        tnumber l35 = (l6 * l12) - (l8 * l10);
        tnumber l36 = (l6 * l11) - (l7 * l10);
        tnumber l37 = (l5 * l12) - (l8 * l9);
        tnumber l38 = (l5 * l11) - (l7 * l9);
        tnumber l39 = (l5 * l10) - (l6 * l9);

        other->m[0] = l23 * l27;
        other->m[4] = l24 * l27;
        other->m[8] = l25 * l27;
        other->m[12] = l26 * l27;
        other->m[1] = -(((l2 * l17) - (l3 * l18)) + (l4 * l19)) * l27;
        other->m[5] = (((l1 * l17) - (l3 * l20)) + (l4 * l21)) * l27;
        other->m[9] = -(((l1 * l18) - (l2 * l20)) + (l4 * l22)) * l27;
        other->m[13] = (((l1 * l19) - (l2 * l21)) + (l3 * l22)) * l27;
        other->m[2] = (((l2 * l28) - (l3 * l29)) + (l4 * l30)) * l27;
        other->m[6] = -(((l1 * l28) - (l3 * l31)) + (l4 * l32)) * l27;
        other->m[10] = (((l1 * l29) - (l2 * l31)) + (l4 * l33)) * l27;
        other->m[14] = -(((l1 * l30) - (l2 * l32)) + (l3 * l33)) * l27;
        other->m[3] = -(((l2 * l34) - (l3 * l35)) + (l4 * l36)) * l27;
        other->m[7] = (((l1 * l34) - (l3 * l37)) + (l4 * l38)) * l27;
        other->m[11] = -(((l1 * l35) - (l2 * l37)) + (l4 * l39)) * l27;
        other->m[15] = (((l1 * l36) - (l2 * l38)) + (l3 * l39)) * l27;

        other->_markAsUpdated();
        return this;
    }

    /**
     * Inserts the translation vector (using 3 x tnumbers) in the current Matrix.
     * Returns the updated Matrix.
     */
    Matrix* setTranslationFromtnumbers(tnumber x, tnumber y, tnumber z) {
        this->m[12] = x;
        this->m[13] = y;
        this->m[14] = z;
        this->_markAsUpdated();
        return this;
    }

    /**
     * Inserts the translation vector in the current Matrix.
     * Returns the updated Matrix.
     */
    Matrix* setTranslation(const Vector3* vector3) {
        this->m[12] = vector3->x;
        this->m[13] = vector3->y;
        this->m[14] = vector3->z;
        this->_markAsUpdated();
        return this;
    }

    /**
     * Returns a new Vector3 as the extracted translation from the Matrix.
     */
    Vector3* getTranslation() const {
        return new Vector3(this->m[12], this->m[13], this->m[14]);
    }

    /**
     * Fill a Vector3 with the extracted translation from the Matrix.
     */
    Matrix* getTranslationToRef(Vector3* result) {
        result->x = this->m[12];
        result->y = this->m[13];
        result->z = this->m[14];
        return this;
    }

    /**
     * Remove rotation and scaling part from the Matrix.
     * Returns the updated Matrix.
     */
    Matrix* removeRotationAndScaling() {
        this->setRowFromtnumbers(0, 1, 0, 0, 0);
        this->setRowFromtnumbers(1, 0, 1, 0, 0);
        this->setRowFromtnumbers(2, 0, 0, 1, 0);
        return this;
    }

    /**
     * Returns a new Matrix set with the multiplication result of the current Matrix and the passed one.
     */
    Matrix* multiply(Matrix* other) {
        Matrix* result = new Matrix();
        this->multiplyToRef(other, result);
        return result;
    }

    /**
     * Updates the current Matrix from the passed one values.
     * Returns the updated Matrix.
     */
    Matrix* copyFrom(Matrix* other) {
        for (int index = 0; index < 16; index++) {
            this->m[index] = other->m[index];
        }

        this->_markAsUpdated();
        return this;
    }

    /**
     * Populates the passed array from the starting index with the Matrix values.
     * Returns the Matrix.
     */
    Matrix* copyToArray(tnumber* array, unsigned int offset = 0) {
        for (int index = 0; index < 16; index++) {
            array[offset + index] = this->m[index];
        }
        return this;
    }

    /**
     * Sets the passed matrix "result" with the multiplication result of the current Matrix and the passed one.
     */
    Matrix* multiplyToRef(const Matrix* other, Matrix* result) {
        this->multiplyToArray(other, result->m, 0);
        result->_markAsUpdated();
        return this;
    }

    /**
     * Sets the tnumber32Array "result" from the passed index "offset" with the multiplication result of the current Matrix and the passed one.
     */
    Matrix* multiplyToArray(const Matrix* other, tnumber* result, unsigned int offset) {
        tnumber tm0 = this->m[0];
        tnumber tm1 = this->m[1];
        tnumber tm2 = this->m[2];
        tnumber tm3 = this->m[3];
        tnumber tm4 = this->m[4];
        tnumber tm5 = this->m[5];
        tnumber tm6 = this->m[6];
        tnumber tm7 = this->m[7];
        tnumber tm8 = this->m[8];
        tnumber tm9 = this->m[9];
        tnumber tm10 = this->m[10];
        tnumber tm11 = this->m[11];
        tnumber tm12 = this->m[12];
        tnumber tm13 = this->m[13];
        tnumber tm14 = this->m[14];
        tnumber tm15 = this->m[15];

        tnumber om0 = other->m[0];
        tnumber om1 = other->m[1];
        tnumber om2 = other->m[2];
        tnumber om3 = other->m[3];
        tnumber om4 = other->m[4];
        tnumber om5 = other->m[5];
        tnumber om6 = other->m[6];
        tnumber om7 = other->m[7];
        tnumber om8 = other->m[8];
        tnumber om9 = other->m[9];
        tnumber om10 = other->m[10];
        tnumber om11 = other->m[11];
        tnumber om12 = other->m[12];
        tnumber om13 = other->m[13];
        tnumber om14 = other->m[14];
        tnumber om15 = other->m[15];

        result[offset] = tm0 * om0 + tm1 * om4 + tm2 * om8 + tm3 * om12;
        result[offset + 1] = tm0 * om1 + tm1 * om5 + tm2 * om9 + tm3 * om13;
        result[offset + 2] = tm0 * om2 + tm1 * om6 + tm2 * om10 + tm3 * om14;
        result[offset + 3] = tm0 * om3 + tm1 * om7 + tm2 * om11 + tm3 * om15;

        result[offset + 4] = tm4 * om0 + tm5 * om4 + tm6 * om8 + tm7 * om12;
        result[offset + 5] = tm4 * om1 + tm5 * om5 + tm6 * om9 + tm7 * om13;
        result[offset + 6] = tm4 * om2 + tm5 * om6 + tm6 * om10 + tm7 * om14;
        result[offset + 7] = tm4 * om3 + tm5 * om7 + tm6 * om11 + tm7 * om15;

        result[offset + 8] = tm8 * om0 + tm9 * om4 + tm10 * om8 + tm11 * om12;
        result[offset + 9] = tm8 * om1 + tm9 * om5 + tm10 * om9 + tm11 * om13;
        result[offset + 10] = tm8 * om2 + tm9 * om6 + tm10 * om10 + tm11 * om14;
        result[offset + 11] = tm8 * om3 + tm9 * om7 + tm10 * om11 + tm11 * om15;

        result[offset + 12] = tm12 * om0 + tm13 * om4 + tm14 * om8 + tm15 * om12;
        result[offset + 13] = tm12 * om1 + tm13 * om5 + tm14 * om9 + tm15 * om13;
        result[offset + 14] = tm12 * om2 + tm13 * om6 + tm14 * om10 + tm15 * om14;
        result[offset + 15] = tm12 * om3 + tm13 * om7 + tm14 * om11 + tm15 * om15;
        return this;
    }

    /**
     * Boolean : True is the current Matrix and the passed one values are strictly equal.
     */
    bool equals(const Matrix* value)const {
        return value &&
                (this->m[0] == value->m[0] && this->m[1] == value->m[1] && this->m[2] == value->m[2] && this->m[3] == value->m[3] &&
                this->m[4] == value->m[4] && this->m[5] == value->m[5] && this->m[6] == value->m[6] && this->m[7] == value->m[7] &&
                this->m[8] == value->m[8] && this->m[9] == value->m[9] && this->m[10] == value->m[10] && this->m[11] == value->m[11] &&
                this->m[12] == value->m[12] && this->m[13] == value->m[13] && this->m[14] == value->m[14] && this->m[15] == value->m[15]);
    }

    /**
     * Returns a new Matrix from the current Matrix.
     */
    Matrix* clone() const {
        return Matrix::FromValues(this->m[0], this->m[1], this->m[2], this->m[3],
                this->m[4], this->m[5], this->m[6], this->m[7],
                this->m[8], this->m[9], this->m[10], this->m[11],
                this->m[12], this->m[13], this->m[14], this->m[15]);
    }

    /**
     * Returns the string "Matrix"
     */
    static tstring getClassName() {
        return S("Matrix");
    }

    /**
     * Returns the Matrix hash code.
     */
    std::size_t getHashCode() const {
        std::size_t hash = std::hash<tnumber>()(this->m[0]);
        for (int i = 1; i < 16; i++) {
            hash = (hash * 397) ^ (std::hash<tnumber>()(this->m[i]));
        }
        return hash;
    }

    /**
     * Decomposes the current Matrix into :
     * - a scale vector3 passed as a reference to update,
     * - a rotation quaternion passed as a reference to update,
     * - a translation vector3 passed as a reference to update.
     * Returns the boolean `true`.
     */
    bool decompose(Vector3* scale, Quaternion* rotation, Vector3* translation) {
        translation->x = this->m[12];
        translation->y = this->m[13];
        translation->z = this->m[14];

        scale->x = std::sqrt(this->m[0] * this->m[0] + this->m[1] * this->m[1] + this->m[2] * this->m[2]);
        scale->y = std::sqrt(this->m[4] * this->m[4] + this->m[5] * this->m[5] + this->m[6] * this->m[6]);
        scale->z = std::sqrt(this->m[8] * this->m[8] + this->m[9] * this->m[9] + this->m[10] * this->m[10]);

        if (this->determinant() <= 0) {
            scale->y *= -1;
        }

        if (scale->x == 0 || scale->y == 0 || scale->z == 0) {
            rotation->x = 0;
            rotation->y = 0;
            rotation->z = 0;
            rotation->w = 1;
            return false;
        }

        Matrix::FromValuesToRef(
                this->m[0] / scale->x, this->m[1] / scale->x, this->m[2] / scale->x, 0,
                this->m[4] / scale->y, this->m[5] / scale->y, this->m[6] / scale->y, 0,
                this->m[8] / scale->z, this->m[9] / scale->z, this->m[10] / scale->z, 0,
                0, 0, 0, 1, MathTmp::Matrix[0]);
        Quaternion::FromRotationMatrixToRef(MathTmp::Matrix[0], rotation);

        return true;
    }

    /**
     * Returns a new Matrix as the extracted rotation matrix from the current one.
     */
    Matrix* getRotationMatrix() {
        Matrix* result = Matrix::Identity();
        this->getRotationMatrixToRef(result);
        return result;
    }

    /**
     * Extracts the rotation matrix from the current one and sets it as the passed "result".
     * Returns the current Matrix.
     */
    Matrix* getRotationMatrixToRef(Matrix* result) {
        tnumber* m = this->m;

        tnumber xs = m[0] * m[1] * m[2] * m[3] < 0 ? -1 : 1;
        tnumber ys = m[4] * m[5] * m[6] * m[7] < 0 ? -1 : 1;
        tnumber zs = m[8] * m[9] * m[10] * m[11] < 0 ? -1 : 1;

        tnumber sx = xs * std::sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
        tnumber sy = ys * std::sqrt(m[4] * m[4] + m[5] * m[5] + m[6] * m[6]);
        tnumber sz = zs * std::sqrt(m[8] * m[8] + m[9] * m[9] + m[10] * m[10]);

        Matrix::FromValuesToRef(
                m[0] / sx, m[1] / sx, m[2] / sx, 0,
                m[4] / sy, m[5] / sy, m[6] / sy, 0,
                m[8] / sz, m[9] / sz, m[10] / sz, 0,
                0, 0, 0, 1, result);

        return this;
    }

    // Statics

    /**
     * Returns a new Matrix set from the starting index of the passed array.
     */
    static Matrix* FromArray(tnumber* array, unsigned int offset = 0) {
        Matrix* result = new Matrix();
        Matrix::FromArrayToRef(array, offset, result);
        return result;
    }

    /**
     * Sets the passed "result" matrix from the starting index of the passed array.
     */
    static void FromArrayToRef(tnumber* array, unsigned int offset, Matrix* result) {
        for (int index = 0; index < 16; index++) {
            result->m[index] = array[index + offset];
        }
        result->_markAsUpdated();
    }

    /**
     * Sets the passed "result" matrix from the starting index of the passed tnumber32Array by multiplying each element by the tnumber "scale".
     */
    static void Fromtnumber32ArrayToRefScaled(tnumber* array, unsigned int offset, tnumber scale, Matrix* result) {
        for (int index = 0; index < 16; index++) {
            result->m[index] = array[index + offset] * scale;
        }

        result->_markAsUpdated();
    }

    /**
     * Sets the passed matrix "result" with the 16 passed tnumbers.
     */
    static void FromValuesToRef(tnumber initialM11, tnumber initialM12, tnumber initialM13, tnumber initialM14,
            tnumber initialM21, tnumber initialM22, tnumber initialM23, tnumber initialM24,
            tnumber initialM31, tnumber initialM32, tnumber initialM33, tnumber initialM34,
            tnumber initialM41, tnumber initialM42, tnumber initialM43, tnumber initialM44, Matrix* result) {

        result->m[0] = initialM11;
        result->m[1] = initialM12;
        result->m[2] = initialM13;
        result->m[3] = initialM14;
        result->m[4] = initialM21;
        result->m[5] = initialM22;
        result->m[6] = initialM23;
        result->m[7] = initialM24;
        result->m[8] = initialM31;
        result->m[9] = initialM32;
        result->m[10] = initialM33;
        result->m[11] = initialM34;
        result->m[12] = initialM41;
        result->m[13] = initialM42;
        result->m[14] = initialM43;
        result->m[15] = initialM44;

        result->_markAsUpdated();
    }

    /**
     * Returns the index-th row of the current matrix as a new Vector4.
     */
    Vector4* getRow(unsigned int index) {
        if (index < 0 || index > 3) {
            return null;
        }
        unsigned int i = index * 4;
        return new Vector4(this->m[i + 0], this->m[i + 1], this->m[i + 2], this->m[i + 3]);
    }

    /**
     * Sets the index-th row of the current matrix with the passed Vector4 values.
     * Returns the updated Matrix.
     */
    Matrix* setRow(unsigned int index, const Vector4* row) {
        if (index < 0 || index > 3) {
            return this;
        }
        unsigned int i = index * 4;
        this->m[i + 0] = row->x;
        this->m[i + 1] = row->y;
        this->m[i + 2] = row->z;
        this->m[i + 3] = row->w;

        this->_markAsUpdated();

        return this;
    }

    /**
     * Compute the transpose of the matrix.
     * Returns a new Matrix.
     */
    Matrix* transpose() {
        return Matrix::Transpose(this);
    }

    /**
     * Compute the transpose of the matrix.
     * Returns the current matrix.
     */
    Matrix* transposeToRef(Matrix *result) {
        Matrix::TransposeToRef(this, result);
        return this;
    }

    /**
     * Sets the index-th row of the current matrix with the passed 4 x tnumber values.
     * Returns the updated Matrix.
     */
    public setRowFromtnumbers(index : number, x : number, y : number, z : number, w : number) : Matrix{
        if (index < 0 || index > 3) {
            return this;
        }
        var i = index * 4;
        this->m[i + 0] = x;
        this->m[i + 1] = y;
        this->m[i + 2] = z;
        this->m[i + 3] = w;

        this->_markAsUpdated();
        return this;
    }

    /**
     * Static identity matrix to be used as readonly matrix
     * Must not be updated.
     */
    public static get IdentityReadOnly() : Matrix{
        return Matrix._identityReadOnly;
    }

    /**
     * Returns a new Matrix set from the 16 passed tnumbers.
     */
    public static FromValues(initialM11 : number, initialM12 : number, initialM13 : number, initialM14 : number,
            initialM21 : number, initialM22 : number, initialM23 : number, initialM24 : number,
            initialM31 : number, initialM32 : number, initialM33 : number, initialM34 : number,
            initialM41 : number, initialM42 : number, initialM43 : number, initialM44 : number) : Matrix{

        var result = new Matrix();

        result->m[0] = initialM11;
        result->m[1] = initialM12;
        result->m[2] = initialM13;
        result->m[3] = initialM14;
        result->m[4] = initialM21;
        result->m[5] = initialM22;
        result->m[6] = initialM23;
        result->m[7] = initialM24;
        result->m[8] = initialM31;
        result->m[9] = initialM32;
        result->m[10] = initialM33;
        result->m[11] = initialM34;
        result->m[12] = initialM41;
        result->m[13] = initialM42;
        result->m[14] = initialM43;
        result->m[15] = initialM44;

        return result;
    }

    /**
     * Returns a new Matrix composed by the passed scale (vector3), rotation (quaternion) and translation (vector3).
     */
    static Matrix* Compose(Vector3* scale , Quaternion* rotation, Vector3* translation ){
        var result = Matrix.Identity();
        Matrix::ComposeToRef(scale, rotation, translation, result);
        return result;
    }

    /**
     * Update a Matrix with values composed by the passed scale (vector3), rotation (quaternion) and translation (vector3).
     */
	static void ComposeToRef(const Vector3* scale,const Quaternion* rotation, const Vector3* translation, Matrix* result) {
        Matrix.FromValuesToRef(scale->x, 0, 0, 0,
                0, scale->y, 0, 0,
                0, 0, scale->z, 0,
                0, 0, 0, 1, MathTmp::Matrix[1]);

        rotation->toRotationMatrix(MathTmp::Matrix[0]);
        MathTmp::Matrix[1].multiplyToRef(MathTmp::Matrix[0], result);

        result->setTranslation(translation);
    }
    /**
     * Returns a new indentity Matrix.
     */
    static Matrix* Identity() const{
        return Matrix::FromValues(1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);
    }
    /**
     * Sets the passed "result" as an identity matrix.
     */
     static void IdentityToRef(Matrix* result)  {
        Matrix::FromValuesToRef(1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 1.0, result);
    }
    /**
     * Returns a new zero Matrix.
     */
    static Matrix* Zero(){
        return Matrix::FromValues(0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0);
    }
    /**
     * Returns a new rotation matrix for "angle" radians around the X axis->
     */
    static Matrix* RotationX(tnumber angle) {
		Matrix* result = new Matrix();
        Matrix::RotationXToRef(angle, result);
        return result;
    }
    /**
     * Returns a new Matrix as the passed inverted one.
     */
    static Matrix* Invert(const Matrix* source) {
		Matrix* result = new Matrix();
        source->invertToRef(result);
        return result;
    }
    /**
     * Sets the passed matrix "result" as a rotation matrix for "angle" radians around the X axis->
     */
   

    static void RotationXToRef(tnumber angle , Matrix* result) {
        tnumber s = std::sin(angle);
		tnumber c = std::cos(angle);

        result->m[0] = 1.0;
        result->m[15] = 1.0;

        result->m[5] = c;
        result->m[10] = c;
        result->m[9] = -s;
        result->m[6] = s;

        result->m[1] = 0.0;
        result->m[2] = 0.0;
        result->m[3] = 0.0;
        result->m[4] = 0.0;
        result->m[7] = 0.0;
        result->m[8] = 0.0;
        result->m[11] = 0.0;
        result->m[12] = 0.0;
        result->m[13] = 0.0;
        result->m[14] = 0.0;

        result->_markAsUpdated();
    }
    /**
     * Returns a new rotation matrix for "angle" radians around the Y axis->
     */
	Matrix* static RotationY(tnumber angle){
		Matrix* result = new Matrix();
        Matrix::RotationYToRef(angle, result);
        return result;
    }
    /**
     * Sets the passed matrix "result" as a rotation matrix for "angle" radians around the Y axis->
     */
    

           static void RotationYToRef(tnumber angle, Matrix* result){
        tnumber s = std::sin(angle);
        tnumber c = std::cos(angle);

        result->m[5] = 1.0;
        result->m[15] = 1.0;

        result->m[0] = c;
        result->m[2] = -s;
        result->m[8] = s;
        result->m[10] = c;

        result->m[1] = 0.0;
        result->m[3] = 0.0;
        result->m[4] = 0.0;
        result->m[6] = 0.0;
        result->m[7] = 0.0;
        result->m[9] = 0.0;
        result->m[11] = 0.0;
        result->m[12] = 0.0;
        result->m[13] = 0.0;
        result->m[14] = 0.0;

        result->_markAsUpdated();
    }
    /**
     * Returns a new rotation matrix for "angle" radians around the Z axis->
     */
    static Matrix* RotationZ(tnumber angle){
		Matrix* result = new Matrix();
        Matrix::RotationZToRef(angle, result);
        return result;
    }
    /**
     * Sets the passed matrix "result" as a rotation matrix for "angle" radians around the Z axis->
     */
           static void RotationZToRef(tnumber angle, Matrix* result)  {
			   tnumber s = std::sin(angle);
			   tnumber c = std::cos(angle);

        result->m[10] = 1.0;
        result->m[15] = 1.0;

        result->m[0] = c;
        result->m[1] = s;
        result->m[4] = -s;
        result->m[5] = c;

        result->m[2] = 0.0;
        result->m[3] = 0.0;
        result->m[6] = 0.0;
        result->m[7] = 0.0;
        result->m[8] = 0.0;
        result->m[9] = 0.0;
        result->m[11] = 0.0;
        result->m[12] = 0.0;
        result->m[13] = 0.0;
        result->m[14] = 0.0;

        result->_markAsUpdated();
    }
    /**
     * Returns a new rotation matrix for "angle" radians around the passed axis->
     */
    static Matrix* RotationAxis(const Vector3 *axis, tnumber angle){
        Matrix* result = Matrix::Zero();
        Matrix::RotationAxisToRef(axis, angle, result);
        return result;
    }
    /**
     * Sets the passed matrix "result" as a rotation matrix for "angle" radians around the passed axis->
     */

     static void RotationAxisToRef(const Vector3 *axis, tnumber angle,Matrix* result) : void {
        tnumber s = std::sin(-angle);
		tnumber c = std::cos(-angle);
        var c1 = 1 - c;

        axis->normalize();

        result->m[0] = (axis->x * axis->x) * c1 + c;
        result->m[1] = (axis->x * axis->y) * c1 - (axis->z * s);
        result->m[2] = (axis->x * axis->z) * c1 + (axis->y * s);
        result->m[3] = 0.0;

        result->m[4] = (axis->y * axis->x) * c1 + (axis->z * s);
        result->m[5] = (axis->y * axis->y) * c1 + c;
        result->m[6] = (axis->y * axis->z) * c1 - (axis->x * s);
        result->m[7] = 0.0;

        result->m[8] = (axis->z * axis->x) * c1 - (axis->y * s);
        result->m[9] = (axis->z * axis->y) * c1 + (axis->x * s);
        result->m[10] = (axis->z * axis->z) * c1 + c;
        result->m[11] = 0.0;

        result->m[15] = 1.0;

        result->_markAsUpdated();
    }
    /**
     * Returns a new Matrix as a rotation matrix from the Euler angles (y, x, z).
     */
    static Matrix* RotationYawPitchRoll(tnumber yaw, tnumber pitch , tnumber roll ){
		Matrix* result = new Matrix();
        Matrix::RotationYawPitchRollToRef(yaw, pitch, roll, result);
        return result;
    }
    /**
     * Sets the passed matrix "result" as a rotation matrix from the Euler angles (y, x, z).
     */
    static void RotationYawPitchRollToRef(tnumber yaw, tnumber pitch, tnumber roll, Matrix* result){
        Quaternion::RotationYawPitchRollToRef(yaw, pitch, roll, Matrix::_tempQuaternion);
		Matrix::_tempQuaternion.toRotationMatrix(result);
    }
    /**
     * Returns a new Matrix as a scaling matrix from the passed tnumbers (x, y, z).
     */
    public Matrix* Scaling(tnumber x, tnumber y, tnumber z) {
		Matrix* result = Matrix::Zero();
        Matrix::ScalingToRef(x, y, z, result);
        return result;
    }
    /**
     * Sets the passed matrix "result" as a scaling matrix from the passed tnumbers (x, y, z).
     */
     static void ScalingToRef(tnumber x, tnumber y, tnumber z, Matrix* result){
        result->m[0] = x;
        result->m[1] = 0.0;
        result->m[2] = 0.0;
        result->m[3] = 0.0;
        result->m[4] = 0.0;
        result->m[5] = y;
        result->m[6] = 0.0;
        result->m[7] = 0.0;
        result->m[8] = 0.0;
        result->m[9] = 0.0;
        result->m[10] = z;
        result->m[11] = 0.0;
        result->m[12] = 0.0;
        result->m[13] = 0.0;
        result->m[14] = 0.0;
        result->m[15] = 1.0;

        result->_markAsUpdated();
    }
    /**
     * Returns a new Matrix as a translation matrix from the passed tnumbers (x, y, z).
     */
    public Matrix* Translation(tnumber x, tnumber y, tnumber z) {
		Matrix* result = Matrix::Identity();
        Matrix::TranslationToRef(x, y, z, result);
        return result;
    }
    /**
     * Sets the passed matrix "result" as a translation matrix from the passed tnumbers (x, y, z).
     */
    static void ::TranslationToRef(tnumber x, tnumber y, tnumber z, Matrix* result) :  {
        Matrix::FromValuesToRef(1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                x, y, z, 1.0, result);
    }
    /**
     * Returns a new Matrix whose values are the interpolated values for "gradien" (tnumber) between the ones of the matrices "startValue" and "endValue".
     */
    static Matrix* Lerp(Matrix *startValue, Matrix* endValue, tnumber gradient){
		Matrix* result = Matrix::Zero();
        for (int index = 0; index < 16; index++) {
            result->m[index] = startvalue->m[index] * (1.0 - gradient) + endvalue->m[index] * gradient;
        }
        result->_markAsUpdated();
        return result;
    }

    /**
     * Returns a new Matrix whose values are computed by :
     * - decomposing the the "startValue" and "endValue" matrices into their respective scale, rotation and translation matrices,
     * - interpolating for "gradient" (tnumber) the values between each of these decomposed matrices between the start and the end,
     * - recomposing a new matrix from these 3 interpolated scale, rotation and translation matrices.
     */
    static Matrix* DecomposeLerp(const Matrix* startValue, const Matrix* endValue, tnumber gradient) {
		Vector3* startScale = new Vector3(0, 0, 0);
		Quaternion* startRotation = new Quaternion();
		Vector3* startTranslation = new Vector3(0, 0, 0);
        startValue->decompose(startScale, startRotation, startTranslation);

		Vector3* endScale = new Vector3(0, 0, 0);
		Quaternion* endRotation = new Quaternion();
		Vector3* endTranslation = new Vector3(0, 0, 0);
        endValue->decompose(endScale, endRotation, endTranslation);

		Matrix* resultScale = Vector3::Lerp(startScale, endScale, gradient);
		Matrix* resultRotation = Quaternion::Slerp(startRotation, endRotation, gradient);
		Matrix* resultTranslation = Vector3::Lerp(startTranslation, endTranslation, gradient);

        return Matrix::Compose(resultScale, resultRotation, resultTranslation);
    }

    /**
     * Returns a new rotation Matrix used to rotate a mesh so as it looks at the target Vector3, from the eye Vector3, the UP vector3 being orientated like "up".
     * This methods works for a Left-Handed system.
     */
    static Matrix* LookAtLH(const Vector3* eye,const Vector3* target, const Vector3* up) {
		Vector3* result = Matrix::Zero();
        Matrix::LookAtLHToRef(eye, target, up, result);
        return result;
    }

    /**
     * Sets the passed "result" Matrix as a rotation matrix used to rotate a mesh so as it looks at the target Vector3, from the eye Vector3, the UP vector3 being orientated like "up".
     * This methods works for a Left-Handed system.
     */
	static Matrix* LookAtLHToRef(const Vector3* eye, const Vector3* target, const Vector3* up, Matrix* result) {
        // Z axis
        target->subtractToRef(eye, this->_zAxis);
        this->_zaxis->normalize();

        // X axis
        Vector3::CrossToRef(up, this->_zAxis, this->_xAxis);

        if (this->_xaxis->lengthSquared() == 0) {
            this->_xaxis->x = 1.0;
        } else {
            this->_xaxis->normalize();
        }

        // Y axis
        Vector3::CrossToRef(this->_zAxis, this->_xAxis, this->_yAxis);
        this->_yaxis->normalize();

        // Eye angles
        tnumber ex = -Vector3::Dot(this->_xAxis, eye);
		tnumber ey = -Vector3::Dot(this->_yAxis, eye);
		tnumber ez = -Vector3::Dot(this->_zAxis, eye);

        return Matrix::FromValuesToRef(this->_xaxis->x, this->_yaxis->x, this->_zaxis->x, 0,
                this->_xaxis->y, this->_yaxis->y, this->_zaxis->y, 0,
                this->_xaxis->z, this->_yaxis->z, this->_zaxis->z, 0,
                ex, ey, ez, 1, result);
    }

    /**
     * Returns a new rotation Matrix used to rotate a mesh so as it looks at the target Vector3, from the eye Vector3, the UP vector3 being orientated like "up".
     * This methods works for a Right-Handed system.
     */
    static Matrix* LookAtRH(const Vector3* eye, const Vector3* target, const Vector3* up) {
		Vector3* result = Matrix::Zero();
        Matrix::LookAtRHToRef(eye, target, up, result);
        return result;
    }

    /**
     * Sets the passed "result" Matrix as a rotation matrix used to rotate a mesh so as it looks at the target Vector3, from the eye Vector3, the UP vector3 being orientated like "up".
     * This methods works for a Left-Handed system.
     */
	 static void LookAtRHToRef(const Vector3* eye, const Vector3* target, const Vector3* up, Matrix* result)  {
        // Z axis
        eye.subtractToRef(target, this->_zAxis);
        this->_zaxis->normalize();

        // X axis
        Vector3.CrossToRef(up, this->_zAxis, this->_xAxis);

        if (this->_xaxis->lengthSquared() == 0) {
            this->_xaxis->x = 1.0;
        } else {
            this->_xaxis->normalize();
        }

        // Y axis
        Vector3.CrossToRef(this->_zAxis, this->_xAxis, this->_yAxis);
        this->_yaxis->normalize();

        // Eye angles
        var ex = -Vector3.Dot(this->_xAxis, eye);
        var ey = -Vector3.Dot(this->_yAxis, eye);
        var ez = -Vector3.Dot(this->_zAxis, eye);

        return Matrix.FromValuesToRef(this->_xaxis->x, this->_yaxis->x, this->_zaxis->x, 0,
                this->_xaxis->y, this->_yaxis->y, this->_zaxis->y, 0,
                this->_xaxis->z, this->_yaxis->z, this->_zaxis->z, 0,
                ex, ey, ez, 1, result);
    }

    /**
     * Returns a new Matrix as a left-handed orthographic projection matrix computed from the passed tnumbers : width and height of the projection plane, z near and far limits.
     */
    public static OrthoLH(width : number, height : number, znear : number, zfar : number) : Matrix{
        var matrix = Matrix.Zero();
        Matrix.OrthoLHToRef(width, height, znear, zfar, matrix);
        return matrix;
    }
    /**
     * Sets the passed matrix "result" as a left-handed orthographic projection matrix computed from the passed tnumbers : width and height of the projection plane, z near and far limits.
     */
    public

           static OrthoLHToRef(width : number, height : number, znear : number, zfar : number, result : Matrix) : void {
        let n = znear;
        let f = zfar;

        let a = 2.0 / width;
        let b = 2.0 / height;
        let c = 2.0 / (f - n);
        let d = -(f + n) / (f - n);

        BABYLON.Matrix.FromValuesToRef(
                a, 0.0, 0.0, 0.0,
                0.0, b, 0.0, 0.0,
                0.0, 0.0, c, 0.0,
                0.0, 0.0, d, 1.0,
                result
                );
    }
    /**
     * Returns a new Matrix as a left-handed orthographic projection matrix computed from the passed tnumbers : left, right, top and bottom being the coordinates of the projection plane, z near and far limits.
     */
    public static OrthoOffCenterLH(left : number, right : number, bottom : number, top : number, znear : number, zfar : number) : Matrix{
        var matrix = Matrix.Zero();

        Matrix.OrthoOffCenterLHToRef(left, right, bottom, top, znear, zfar, matrix);

        return matrix;
    }
    /**
     * Sets the passed matrix "result" as a left-handed orthographic projection matrix computed from the passed tnumbers : left, right, top and bottom being the coordinates of the projection plane, z near and far limits.
     */
    public

           static OrthoOffCenterLHToRef(left : number, right : number, bottom : number, top : number, znear : number, zfar : number, result : Matrix) : void {
        let n = znear;
        let f = zfar;

        let a = 2.0 / (right - left);
        let b = 2.0 / (top - bottom);
        let c = 2.0 / (f - n);
        let d = -(f + n) / (f - n);
        let i0 = (left + right) / (left - right);
        let i1 = (top + bottom) / (bottom - top);

        BABYLON.Matrix.FromValuesToRef(
                a, 0.0, 0.0, 0.0,
                0.0, b, 0.0, 0.0,
                0.0, 0.0, c, 0.0,
                i0, i1, d, 1.0,
                result
                );
    }
    /**
     * Returns a new Matrix as a right-handed orthographic projection matrix computed from the passed tnumbers : left, right, top and bottom being the coordinates of the projection plane, z near and far limits.
     */
    public static OrthoOffCenterRH(left : number, right : number, bottom : number, top : number, znear : number, zfar : number) : Matrix{
        var matrix = Matrix.Zero();
        Matrix.OrthoOffCenterRHToRef(left, right, bottom, top, znear, zfar, matrix);
        return matrix;
    }
    /**
     * Sets the passed matrix "result" as a right-handed orthographic projection matrix computed from the passed tnumbers : left, right, top and bottom being the coordinates of the projection plane, z near and far limits.
     */
    public

           static OrthoOffCenterRHToRef(left : number, right : number, bottom : number, top : number, znear : number, zfar : number, result : Matrix) : void {
        Matrix.OrthoOffCenterLHToRef(left, right, bottom, top, znear, zfar, result);
        result->m[10] *= -1.0;
    }
    /**
     * Returns a new Matrix as a left-handed perspective projection matrix computed from the passed tnumbers : width and height of the projection plane, z near and far limits.
     */
    public static PerspectiveLH(width : number, height : number, znear : number, zfar : number) : Matrix{
        var matrix = Matrix.Zero();

        let n = znear;
        let f = zfar;

        let a = 2.0 * n / width;
        let b = 2.0 * n / height;
        let c = (f + n) / (f - n);
        let d = -2.0 * f * n / (f - n);

        BABYLON.Matrix.FromValuesToRef(
        a, 0.0, 0.0, 0.0,
        0.0, b, 0.0, 0.0,
        0.0, 0.0, c, 1.0,
        0.0, 0.0, d, 0.0,
        matrix
        );

        return matrix;
    }
    /**
     * Returns a new Matrix as a left-handed perspective projection matrix computed from the passed tnumbers : vertical angle of view (fov), width/height ratio (aspect), z near and far limits.
     */
    public static PerspectiveFovLH(fov : number, aspect : number, znear : number, zfar : number) : Matrix{
        var matrix = Matrix.Zero();
        Matrix.PerspectiveFovLHToRef(fov, aspect, znear, zfar, matrix);
        return matrix;
    }
    /**
     * Sets the passed matrix "result" as a left-handed perspective projection matrix computed from the passed tnumbers : vertical angle of view (fov), width/height ratio (aspect), z near and far limits.
     */
    public

           static PerspectiveFovLHToRef(fov : number, aspect : number, znear : number, zfar : number, result : Matrix, isVerticalFovFixed = true) : void {
        let n = znear;
        let f = zfar;

        let t = 1.0 / (std::tan(fov * 0.5));
        let a = isVerticalFovFixed ? (t / aspect) : t;
        let b = isVerticalFovFixed ? t : (t * aspect);
        let c = (f + n) / (f - n);
        let d = -2.0 * f * n / (f - n);

        BABYLON.Matrix.FromValuesToRef(
                a, 0.0, 0.0, 0.0,
                0.0, b, 0.0, 0.0,
                0.0, 0.0, c, 1.0,
                0.0, 0.0, d, 0.0,
                result
                );
    }
    /**
     * Returns a new Matrix as a right-handed perspective projection matrix computed from the passed tnumbers : vertical angle of view (fov), width/height ratio (aspect), z near and far limits.
     */
    public static PerspectiveFovRH(fov : number, aspect : number, znear : number, zfar : number) : Matrix{
        var matrix = Matrix.Zero();
        Matrix.PerspectiveFovRHToRef(fov, aspect, znear, zfar, matrix);
        return matrix;
    }
    /**
     * Sets the passed matrix "result" as a right-handed perspective projection matrix computed from the passed tnumbers : vertical angle of view (fov), width/height ratio (aspect), z near and far limits.
     */
    public

           static PerspectiveFovRHToRef(fov : number, aspect : number, znear : number, zfar : number, result : Matrix, isVerticalFovFixed = true) : void {
        //alternatively this could be expressed as:
        //    m = PerspectiveFovLHToRef
        //    m[10] *= -1.0;
        //    m[11] *= -1.0;
        let n = znear;
        let f = zfar;

        let t = 1.0 / (std::tan(fov * 0.5));
        let a = isVerticalFovFixed ? (t / aspect) : t;
        let b = isVerticalFovFixed ? t : (t * aspect);
        let c = -(f + n) / (f - n);
        let d = -2 * f * n / (f - n);

        BABYLON.Matrix.FromValuesToRef(
                a, 0.0, 0.0, 0.0,
                0.0, b, 0.0, 0.0,
                0.0, 0.0, c, -1.0,
                0.0, 0.0, d, 0.0,
                result
                );
    }
    /**
     * Sets the passed matrix "result" as a left-handed perspective projection matrix  for WebVR computed from the passed tnumbers : vertical angle of view (fov), width/height ratio (aspect), z near and far limits.
     */
    public

           static PerspectiveFovWebVRToRef(fov :{upDegrees : number, downDegrees : number, leftDegrees : number, rightDegrees : number}, znear : number, zfar : number, result : Matrix, rightHanded = false) : void {

        var rightHandedFactor = rightHanded ? -1 : 1;

        var upTan = std::tan(fov.upDegrees * std::PI / 180.0);
        var downTan = std::tan(fov.downDegrees * std::PI / 180.0);
        var leftTan = std::tan(fov.leftDegrees * std::PI / 180.0);
        var rightTan = std::tan(fov.rightDegrees * std::PI / 180.0);
        var xScale = 2.0 / (leftTan + rightTan);
        var yScale = 2.0 / (upTan + downTan);
        result->m[0] = xScale;
        result->m[1] = result->m[2] = result->m[3] = result->m[4] = 0.0;
        result->m[5] = yScale;
        result->m[6] = result->m[7] = 0.0;
        result->m[8] = ((leftTan - rightTan) * xScale * 0.5)// * rightHandedFactor;
                result->m[9] = -((upTan - downTan) * yScale * 0.5)// * rightHandedFactor;
                //result->m[10] = -(znear + zfar) / (zfar - znear) * rightHandedFactor;
                result->m[10] = -zfar / (znear - zfar);
        result->m[11] = 1.0 * rightHandedFactor;
        result->m[12] = result->m[13] = result->m[15] = 0.0;
        result->m[14] = -(2.0 * zfar * znear) / (zfar - znear);
        // result->m[14] = (znear * zfar) / (znear - zfar);
        result->_markAsUpdated();
    }

    /**
     * Returns the final transformation matrix : world * view * projection * viewport
     */
    public static GetFinalMatrix(viewport : Viewport, world : Matrix, view : Matrix, projection : Matrix, zmin : number, zmax : number) : Matrix{
        var cw = viewport.width;
        var ch = viewport.height;
        var cx = viewport.x;
        var cy = viewport.y;

        var viewportMatrix = Matrix.FromValues(cw / 2.0, 0.0, 0.0, 0.0,
        0.0, -ch / 2.0, 0.0, 0.0,
        0.0, 0.0, zmax - zmin, 0.0,
        cx + cw / 2.0, ch / 2.0 + cy, zmin, 1);

        return world.multiply(view).multiply(projection).multiply(viewportMatrix);
    }

    /**
     * Returns a new tnumber32Array array with 4 elements : the 2x2 matrix extracted from the passed Matrix.
     */
    public static GetAsMatrix2x2(matrix : Matrix) : tnumber32Array{
        return new tnumber32Array([
        matrix.m[0], matrix.m[1],
        matrix.m[4], matrix.m[5]
        ]);
    }
    /**
     * Returns a new tnumber32Array array with 9 elements : the 3x3 matrix extracted from the passed Matrix.
     */
    public static GetAsMatrix3x3(matrix : Matrix) : tnumber32Array{
        return new tnumber32Array([
        matrix.m[0], matrix.m[1], matrix.m[2],
        matrix.m[4], matrix.m[5], matrix.m[6],
        matrix.m[8], matrix.m[9], matrix.m[10]
        ]);
    }

    /**
     * Compute the transpose of the passed Matrix.
     * Returns a new Matrix.
     */
    public static Transpose(matrix : Matrix) : Matrix{
        var result = new Matrix();

        Matrix.TransposeToRef(matrix, result);

        return result;
    }

    /**
     * Compute the transpose of the passed Matrix and store it in the result matrix.
     */
    public

           static TransposeToRef(matrix : Matrix, result : Matrix) : void {
        result->m[0] = matrix.m[0];
        result->m[1] = matrix.m[4];
        result->m[2] = matrix.m[8];
        result->m[3] = matrix.m[12];

        result->m[4] = matrix.m[1];
        result->m[5] = matrix.m[5];
        result->m[6] = matrix.m[9];
        result->m[7] = matrix.m[13];

        result->m[8] = matrix.m[2];
        result->m[9] = matrix.m[6];
        result->m[10] = matrix.m[10];
        result->m[11] = matrix.m[14];

        result->m[12] = matrix.m[3];
        result->m[13] = matrix.m[7];
        result->m[14] = matrix.m[11];
        result->m[15] = matrix.m[15];
    }

    /**
     * Returns a new Matrix as the reflection  matrix across the passed plane.
     */
    public static Reflection(plane : Plane) : Matrix{
        var matrix = new Matrix();
        Matrix.ReflectionToRef(plane, matrix);
        return matrix;
    }

    /**
     * Sets the passed matrix "result" as the reflection matrix across the passed plane.
     */
    public

           static ReflectionToRef(plane : Plane, result : Matrix) : void {
        plane.normalize();
        var x = plane.normal.x;
        var y = plane.normal.y;
        var z = plane.normal.z;
        var temp = -2 * x;
        var temp2 = -2 * y;
        var temp3 = -2 * z;
        result->m[0] = (temp * x) + 1;
        result->m[1] = temp2 * x;
        result->m[2] = temp3 * x;
        result->m[3] = 0.0;
        result->m[4] = temp * y;
        result->m[5] = (temp2 * y) + 1;
        result->m[6] = temp3 * y;
        result->m[7] = 0.0;
        result->m[8] = temp * z;
        result->m[9] = temp2 * z;
        result->m[10] = (temp3 * z) + 1;
        result->m[11] = 0.0;
        result->m[12] = temp * plane.d;
        result->m[13] = temp2 * plane.d;
        result->m[14] = temp3 * plane.d;
        result->m[15] = 1.0;

        result->_markAsUpdated();
    }

    /**
     * Sets the passed matrix "mat" as a rotation matrix composed from the 3 passed  left handed axis->
     */
    public

           static FromXYZAxesToRef(xaxis : Vector3, yaxis : Vector3, zaxis : Vector3, result : Matrix) {

        result->m[0] = xaxis->x;
        result->m[1] = xaxis->y;
        result->m[2] = xaxis->z;

        result->m[3] = 0.0;

        result->m[4] = yaxis->x;
        result->m[5] = yaxis->y;
        result->m[6] = yaxis->z;

        result->m[7] = 0.0;

        result->m[8] = zaxis->x;
        result->m[9] = zaxis->y;
        result->m[10] = zaxis->z;

        result->m[11] = 0.0;

        result->m[12] = 0.0;
        result->m[13] = 0.0;
        result->m[14] = 0.0;

        result->m[15] = 1.0;

        result->_markAsUpdated();
    }

    /**
     * Sets the passed matrix "result" as a rotation matrix according to the passed quaternion.
     */
    public

           static FromQuaternionToRef(quat : Quaternion, result : Matrix) {

        var xx = quat.x * quat.x;
        var yy = quat.y * quat.y;
        var zz = quat.z * quat.z;
        var xy = quat.x * quat.y;
        var zw = quat.z * quat.w;
        var zx = quat.z * quat.x;
        var yw = quat.y * quat.w;
        var yz = quat.y * quat.z;
        var xw = quat.x * quat.w;

        result->m[0] = 1.0 - (2.0 * (yy + zz));
        result->m[1] = 2.0 * (xy + zw);
        result->m[2] = 2.0 * (zx - yw);
        result->m[3] = 0.0;
        result->m[4] = 2.0 * (xy - zw);
        result->m[5] = 1.0 - (2.0 * (zz + xx));
        result->m[6] = 2.0 * (yz + xw);
        result->m[7] = 0.0;
        result->m[8] = 2.0 * (zx + yw);
        result->m[9] = 2.0 * (yz - xw);
        result->m[10] = 1.0 - (2.0 * (yy + xx));
        result->m[11] = 0.0;

        result->m[12] = 0.0;
        result->m[13] = 0.0;
        result->m[14] = 0.0;

        result->m[15] = 1.0;

        result->_markAsUpdated();
    }
}

export class Plane {
    public 
normal:
    Vector3;
    public 
d:
    number;

    /**
     * Creates a Plane object according to the passed tnumbers a, b, c, d and the plane equation : ax + by + cz + d = 0
     */
    constructor(a : number, b : number, c : number, d : number) {
        this->normal = new Vector3(a, b, c);
        this->d = d;
    }

    /**
     * Returns the plane coordinates as a new array of 4 elements [a, b, c, d].
     */
    public asArray() : number[]{
        return[this->normal.x, this->normal.y, this->normal.z, this->d];
    }

    // Methods
    /**
     * Returns a new plane copied from the current Plane.
     */
    public clone() : Plane{
        return new Plane(this->normal.x, this->normal.y, this->normal.z, this->d);
    }
    /**
     * Returns the string "Plane".
     */
    public getClassName() : string{
        return "Plane";
    }
    /**
     * Returns the Plane hash code.
     */
    public getHashCode() : number{
        let hash = this->normal.getHashCode();
        hash = (hash * 397) ^ (this->d || 0);
        return hash;
    }
    /**
     * Normalize the current Plane in place.
     * Returns the updated Plane.
     */
    public normalize() : Plane{
        var norm = (std::sqrt((this->normal.x * this->normal.x) + (this->normal.y * this->normal.y) + (this->normal.z * this->normal.z)));
        var magnitude = 0.0;

        if (norm != 0) {
            magnitude = 1.0 / norm;
        }
        this->normal.x *= magnitude;
        this->normal.y *= magnitude;
        this->normal.z *= magnitude;
        this->d *= magnitude;
        return this;
    }
    /**
     * Returns a new Plane as the result of the transformation of the current Plane by the passed matrix.
     */
    public transform(transformation : Matrix) : Plane{
        var transposedMatrix = Matrix.Transpose(transformation);
        var x = this->normal.x;
        var y = this->normal.y;
        var z = this->normal.z;
        var d = this->d;

        var normalX = (((x * transposedMatrix.m[0]) + (y * transposedMatrix.m[1])) + (z * transposedMatrix.m[2])) + (d * transposedMatrix.m[3]);
        var normalY = (((x * transposedMatrix.m[4]) + (y * transposedMatrix.m[5])) + (z * transposedMatrix.m[6])) + (d * transposedMatrix.m[7]);
        var normalZ = (((x * transposedMatrix.m[8]) + (y * transposedMatrix.m[9])) + (z * transposedMatrix.m[10])) + (d * transposedMatrix.m[11]);
        var finalD = (((x * transposedMatrix.m[12]) + (y * transposedMatrix.m[13])) + (z * transposedMatrix.m[14])) + (d * transposedMatrix.m[15]);

        return new Plane(normalX, normalY, normalZ, finalD);
    }

    /**
     * Returns the dot product (tnumber) of the point coordinates and the plane normal.
     */
    public dotCoordinate(point : Vector3) : number{
        return ((((this->normal.x * point.x) + (this->normal.y * point.y)) + (this->normal.z * point.z)) + this->d);
    }

    /**
     * Updates the current Plane from the plane defined by the three passed points.
     * Returns the updated Plane.
     */
    public copyFromPoints(point1 : Vector3, point2 : Vector3, point3 : Vector3) : Plane{
        var x1 = point2.x - point1.x;
        var y1 = point2.y - point1.y;
        var z1 = point2.z - point1.z;
        var x2 = point3.x - point1.x;
        var y2 = point3.y - point1.y;
        var z2 = point3.z - point1.z;
        var yz = (y1 * z2) - (z1 * y2);
        var xz = (z1 * x2) - (x1 * z2);
        var xy = (x1 * y2) - (y1 * x2);
        var pyth = (std::sqrt((yz * yz) + (xz * xz) + (xy * xy)));
        var invPyth;

        if (pyth != 0) {
            invPyth = 1.0 / pyth;
        } else {
            invPyth = 0.0;
        }

        this->normal.x = yz * invPyth;
        this->normal.y = xz * invPyth;
        this->normal.z = xy * invPyth;
        this->d = -((this->normal.x * point1.x) + (this->normal.y * point1.y) + (this->normal.z * point1.z));

        return this;
    }

    /**
     * Boolean : True is the vector "direction"  is the same side than the plane normal.
     */
    public isFrontFacingTo(direction : Vector3, epsilon : number) : boolean{
        var dot = Vector3.Dot(this->normal, direction);
        return (dot <= epsilon);
    }

    /**
     * Returns the signed distance (tnumber) from the passed point to the Plane.
     */
    public signedDistanceTo(point : Vector3) : number{
        return Vector3.Dot(point, this->normal) + this->d;
    }

    // Statics
    /**
     * Returns a new Plane from the passed array.
     */
    static FromArray(array : ArrayLike<number>) : Plane{
        return new Plane(array[0], array[1], array[2], array[3]);
    }
    /**
     * Returns a new Plane defined by the three passed points.
     */
    static FromPoints(point1 : Vector3, point2 : Vector3, point3 : Vector3) : Plane{
        var result = new Plane(0.0, 0.0, 0.0, 0.0);
        result->copyFromPoints(point1, point2, point3);
        return result;
    }
    /**
     * Returns a new Plane the normal vector to this plane at the passed origin point.
     * Note : the vector "normal" is updated because normalized.
     */
    static FromPositionAndNormal(origin : Vector3, normal : Vector3) : Plane{
        var result = new Plane(0.0, 0.0, 0.0, 0.0);
        normal.normalize();
        result->normal = normal;
        result->d = -(normal.x * origin.x + normal.y * origin.y + normal.z * origin.z);
        return result;
    }

    /**
     * Returns the signed distance between the plane defined by the normal vector at the "origin"" point and the passed other point.
     */
    static SignedDistanceToPlaneFromPositionAndNormal(origin : Vector3, normal : Vector3, point : Vector3) : number{
        var d = -(normal.x * origin.x + normal.y * origin.y + normal.z * origin.z);
        return Vector3.Dot(point, normal) + d;
    }
}

export class Viewport {

    /**
     * Creates a Viewport object located at (x, y) and sized (width, height).
     */
    constructor(public x : number, public y : number, public width : number, public height : number) {
    }

    public toGlobal(renderWidthOrEngine : number | Engine, renderHeight : number) : Viewport{
        if ((<Engine > renderWidthOrEngine).getRenderWidth) {
            var engine = (<Engine > renderWidthOrEngine);
            return this->toGlobal(engine.getRenderWidth(), engine.getRenderHeight());
        }
        let renderWidth = <number>renderWidthOrEngine;
        return new Viewport(this->x * renderWidth, this->y * renderHeight, this->width * renderWidth, this->height * renderHeight);
    }
    /**
     * Returns a new Viewport copied from the current one.
     */
    public clone() : Viewport{
        return new Viewport(this->x, this->y, this->width, this->height);
    }
}

export class Frustum {
    /**
     * Returns a new array of 6 Frustum planes computed by the passed transformation matrix.
     */
    public static GetPlanes(transform : Matrix) : Plane[]{
        var frustumPlanes = [];
        for (var index = 0; index < 6; index++) {
            frustumPlanes.push(new Plane(0.0, 0.0, 0.0, 0.0));
        }
        Frustum.GetPlanesToRef(transform, frustumPlanes);
        return frustumPlanes;
    }

    public

           static GetNearPlaneToRef(transform : Matrix, frustumPlane : Plane) : void {
        frustumPlane.normal.x = transform.m[3] + transform.m[2];
        frustumPlane.normal.y = transform.m[7] + transform.m[6];
        frustumPlane.normal.z = transform.m[11] + transform.m[10];
        frustumPlane.d = transform.m[15] + transform.m[14];
        frustumPlane.normalize();
    }

    public

           static GetFarPlaneToRef(transform : Matrix, frustumPlane : Plane) : void {
        frustumPlane.normal.x = transform.m[3] - transform.m[2];
        frustumPlane.normal.y = transform.m[7] - transform.m[6];
        frustumPlane.normal.z = transform.m[11] - transform.m[10];
        frustumPlane.d = transform.m[15] - transform.m[14];
        frustumPlane.normalize();
    }

    public

           static GetLeftPlaneToRef(transform : Matrix, frustumPlane : Plane) : void {
        frustumPlane.normal.x = transform.m[3] + transform.m[0];
        frustumPlane.normal.y = transform.m[7] + transform.m[4];
        frustumPlane.normal.z = transform.m[11] + transform.m[8];
        frustumPlane.d = transform.m[15] + transform.m[12];
        frustumPlane.normalize();
    }

    public

           static GetRightPlaneToRef(transform : Matrix, frustumPlane : Plane) : void {
        frustumPlane.normal.x = transform.m[3] - transform.m[0];
        frustumPlane.normal.y = transform.m[7] - transform.m[4];
        frustumPlane.normal.z = transform.m[11] - transform.m[8];
        frustumPlane.d = transform.m[15] - transform.m[12];
        frustumPlane.normalize();
    }

    public

           static GetTopPlaneToRef(transform : Matrix, frustumPlane : Plane) : void {
        frustumPlane.normal.x = transform.m[3] - transform.m[1];
        frustumPlane.normal.y = transform.m[7] - transform.m[5];
        frustumPlane.normal.z = transform.m[11] - transform.m[9];
        frustumPlane.d = transform.m[15] - transform.m[13];
        frustumPlane.normalize();
    }

    public

           static GetBottomPlaneToRef(transform : Matrix, frustumPlane : Plane) : void {
        frustumPlane.normal.x = transform.m[3] + transform.m[1];
        frustumPlane.normal.y = transform.m[7] + transform.m[5];
        frustumPlane.normal.z = transform.m[11] + transform.m[9];
        frustumPlane.d = transform.m[15] + transform.m[13];
        frustumPlane.normalize();
    }

    /**
     * Sets the passed array "frustumPlanes" with the 6 Frustum planes computed by the passed transformation matrix.
     */
    public

           static GetPlanesToRef(transform : Matrix, frustumPlanes : Plane[]) : void {
        // Near
        Frustum.GetNearPlaneToRef(transform, frustumPlanes[0]);

        // Far
        Frustum.GetFarPlaneToRef(transform, frustumPlanes[1]);

        // Left
        Frustum.GetLeftPlaneToRef(transform, frustumPlanes[2]);

        // Right
        Frustum.GetRightPlaneToRef(transform, frustumPlanes[3]);

        // Top
        Frustum.GetTopPlaneToRef(transform, frustumPlanes[4]);

        // Bottom
        Frustum.GetBottomPlaneToRef(transform, frustumPlanes[5]);
    }
}

export enum Space {
    LOCAL = 0,
    WORLD = 1,
    BONE = 2
}

export class Axis {
    public static X : Vector3 = new Vector3(1.0, 0.0, 0.0);
    public static Y : Vector3 = new Vector3(0.0, 1.0, 0.0);
    public static Z : Vector3 = new Vector3(0.0, 0.0, 1.0);
};

export class BezierCurve {
    /**
     * Returns the cubic Bezier interpolated value (tnumber) at "t" (tnumber) from the passed x1, y1, x2, y2 tnumbers.
     */
    public static interpolate(t : number, x1 : number, y1 : number, x2 : number, y2 : number) : number{

        // Extract X (which is equal to time here)
        var f0 = 1 - 3 * x2 + 3 * x1;
        var f1 = 3 * x2 - 6 * x1;
        var f2 = 3 * x1;

        var refinedT = t;
        for (var i = 0; i < 5; i++) {
            var refinedT2 = refinedT * refinedT;
            var refinedT3 = refinedT2 * refinedT;

            var x = f0 * refinedT3 + f1 * refinedT2 + f2 * refinedT;
            var slope = 1.0 / (3.0 * f0 * refinedT2 + 2.0 * f1 * refinedT + f2);
            refinedT -= (x - t) * slope;
            refinedT = std::min(1, std::max(0, refinedT));

        }

        // Resolve cubic bezier for the given x
        return 3 * std::pow(1 - refinedT, 2) * refinedT * y1 +
        3 * (1 - refinedT) * std::pow(refinedT, 2) * y2 +
        std::pow(refinedT, 3);
    }
}

export enum Orientation {
    CW = 0,
    CCW = 1
}

export class Angle {
    private 
_radians:
    number;

    /**
     * Creates an Angle object of "radians" radians (tnumber).
     */
    constructor(radians : number) {
        this->_radians = radians;
        if (this->_radians < 0.0) this->_radians += (2.0 * std::PI);
    }

    /**
     * Returns the Angle value in degrees (tnumber).
     */
    public degrees = () = > this->_radians * 180.0 / std::PI;
    /**
     * Returns the Angle value in radians (tnumber).
     */
    public radians = () = > this->_radians;

    /**
     * Returns a new Angle object valued with the angle value in radians between the two passed vectors.
     */
    public static BetweenTwoPoints(a : Vector2, b : Vector2) : Angle{
        var delta = b.subtract(a);
        var theta = std::atan2(delta.y, delta.x);
        return new Angle(theta);
    }

    /**
     * Returns a new Angle object from the passed tnumber in radians.
     */
    public static FromRadians(radians : number) : Angle{
        return new Angle(radians);
    }
    /**
     * Returns a new Angle object from the passed tnumber in degrees.
     */
    public static FromDegrees(degrees : number) : Angle{
        return new Angle(degrees * std::PI / 180.0);
    }
}

export class Arc2 {
centerPoint:
    Vector2;
radius:
    number;
angle:
    Angle;
startAngle:
    Angle;
orientation:
    Orientation;

    /**
     * Creates an Arc object from the three passed points : start, middle and end.
     */
    constructor(public startPoint : Vector2, public midPoint : Vector2, public endPoint : Vector2) {

        var temp = std::pow(midPoint.x, 2) + std::pow(midPoint.y, 2);
        var startToMid = (std::pow(startPoint.x, 2) + std::pow(startPoint.y, 2) - temp) / 2.;
        var midToEnd = (temp - std::pow(endPoint.x, 2) - std::pow(endPoint.y, 2)) / 2.;
        var det = (startPoint.x - midPoint.x) * (midPoint.y - endPoint.y) - (midPoint.x - endPoint.x) * (startPoint.y - midPoint.y);

        this->centerPoint = new Vector2(
                (startToMid * (midPoint.y - endPoint.y) - midToEnd * (startPoint.y - midPoint.y)) / det,
                ((startPoint.x - midPoint.x) * midToEnd - (midPoint.x - endPoint.x) * startToMid) / det
                );

        this->radius = this->centerPoint.subtract(this->startPoint).length();

        this->startAngle = Angle.BetweenTwoPoints(this->centerPoint, this->startPoint);

        var a1 = this->startAngle.degrees();
        var a2 = Angle.BetweenTwoPoints(this->centerPoint, this->midPoint).degrees();
        var a3 = Angle.BetweenTwoPoints(this->centerPoint, this->endPoint).degrees();

        // angles correction
        if (a2 - a1 > +180.0) a2 -= 360.0;
        if (a2 - a1 < -180.0) a2 += 360.0;
        if (a3 - a2 > +180.0) a3 -= 360.0;
        if (a3 - a2 < -180.0) a3 += 360.0;

        this->orientation = (a2 - a1) < 0 ? Orientation.CW : Orientation.CCW;
        this->angle = Angle.FromDegrees(this->orientation == Orientation.CW ? a1 - a3 : a3 - a1);
    }
}

export class Path2 {
    private _points = new Array<Vector2>();
    private _length = 0.0;

    public closed = false;

    /**
     * Creates a Path2 object from the starting 2D coordinates x and y.
     */
    constructor(x : number, y : number) {
        this->_points.push(new Vector2(x, y));
    }

    /**
     * Adds a new segment until the passed coordinates (x, y) to the current Path2.
     * Returns the updated Path2.
     */
    public addLineTo(x : number, y : number) : Path2{
        if (this->closed) {
            //Tools.Error("cannot add lines to closed paths");
            return this;
        }
        var newPoint = new Vector2(x, y);
        var previousPoint = this->_points[this->_points.length - 1];
        this->_points.push(newPoint);
        this->_length += newPoint.subtract(previousPoint).length();
        return this;
    }

    /**
     * Adds _numberOfSegments_ segments according to the arc definition (middle point coordinates, end point coordinates, the arc start point being the current Path2 last point) to the current Path2.
     * Returns the updated Path2.
     */
    public addArcTo(midX : number, midY : number, endX : number, endY : number, numberOfSegments = 36) : Path2{
        if (this->closed) {
            //Tools.Error("cannot add arcs to closed paths");
            return this;
        }
        var startPoint = this->_points[this->_points.length - 1];
        var midPoint = new Vector2(midX, midY);
        var endPoint = new Vector2(endX, endY);

        var arc = new Arc2(startPoint, midPoint, endPoint);

        var increment = arc.angle.radians() / numberOfSegments;
        if (arc.orientation == Orientation.CW) increment *= -1;
        var currentAngle = arc.startAngle.radians() + increment;

        for (var i = 0; i < numberOfSegments; i++) {
            var x = std::cos(currentAngle) * arc.radius + arc.centerPoint.x;
            var y = std::sin(currentAngle) * arc.radius + arc.centerPoint.y;
            this->addLineTo(x, y);
            currentAngle += increment;
        }
        return this;
    }
    /**
     * Closes the Path2.
     * Returns the Path2.
     */
    public close() : Path2{
        this->closed = true;
        return this;
    }
    /**
     * Returns the Path2 total length (tnumber).
     */
    public length() : number{
        var result = this->_length;

        if (!this->closed) {
            var lastPoint = this->_points[this->_points.length - 1];
            var firstPoint = this->_points[0];
            result += (firstPoint.subtract(lastPoint).length());
        }
        return result;
    }

    /**
     * Returns the Path2 internal array of points.
     */
    public getPoints() : Vector2[]{
        return this->_points;
    }

    /**
     * Returns a new Vector2 located at a percentage of the Path2 total length on this path.
     */
    public getPointAtLengthPosition(normalizedLengthPosition : number) : Vector2{
        if (normalizedLengthPosition < 0 || normalizedLengthPosition > 1) {
            //Tools.Error("normalized length position should be between 0 and 1.");
            return Vector2.Zero();
        }

        var lengthPosition = normalizedLengthPosition * this->length();

        var previousOffset = 0;
        for (var i = 0; i < this->_points.length; i++) {
            var j = (i + 1) % this->_points.length;

            var a = this->_points[i];
            var b = this->_points[j];
            var bToA = b.subtract(a);

            var nextOffset = (bToA.length() + previousOffset);
            if (lengthPosition >= previousOffset && lengthPosition <= nextOffset) {
                var dir = bToA.normalize();
                var localOffset = lengthPosition - previousOffset;

                return new Vector2(
                        a.x + (dir.x * localOffset),
                        a.y + (dir.y * localOffset)
                        );
            }
            previousOffset = nextOffset;
        }

        //Tools.Error("internal error");
        return Vector2.Zero();
    }

    /**
     * Returns a new Path2 starting at the coordinates (x, y).
     */
    public static StartingAt(x : number, y : number) : Path2{
        return new Path2(x, y);
    }
}

export class Path3D {
    private _curve = new Array<Vector3>();
    private _distances = new Array<number>();
    private _tangents = new Array<Vector3>();
    private _normals = new Array<Vector3>();
    private _binormals = new Array<Vector3>();
    private 
_raw:
    boolean;

    /**
     * new Path3D(path, normal, raw)
     * Creates a Path3D. A Path3D is a logical math object, so not a mesh.
     * please read the description in the tutorial :  http://doc.babylonjs.com/tutorials/How_to_use_Path3D
     * path : an array of Vector3, the curve axis of the Path3D
     * normal (optional) : Vector3, the first wanted normal to the curve. Ex (0, 1, 0) for a vertical normal.
     * raw (optional, default false) : boolean, if true the returned Path3D isn't normalized. Useful to depict path acceleration or speed.
     */
    constructor(public path : Vector3[], firstNormal : Nullable<Vector3> = null, raw ? : boolean) {
        for (var p = 0; p < path.length; p++) {
            this->_curve[p] = path[p].clone(); // hard copy
        }
        this->_raw = raw || false;
        this->_compute(firstNormal);
    }

    /**
     * Returns the Path3D array of successive Vector3 designing its curve.
     */
    public getCurve() : Vector3[]{
        return this->_curve;
    }

    /**
     * Returns an array populated with tangent vectors on each Path3D curve point.
     */
    public getTangents() : Vector3[]{
        return this->_tangents;
    }


    /**
     * Returns an array populated with normal vectors on each Path3D curve point.
     */
    public getNormals() : Vector3[]{
        return this->_normals;
    }


    /**
     * Returns an array populated with binormal vectors on each Path3D curve point.
     */
    public getBinormals() : Vector3[]{
        return this->_binormals;
    }


    /**
     * Returns an array populated with distances (tnumber) of the i-th point from the first curve point.
     */
    public getDistances() : number[]{
        return this->_distances;
    }


    /**
     * Forces the Path3D tangent, normal, binormal and distance recomputation.
     * Returns the same object updated.
     */
    public update(path : Vector3[], firstNormal : Nullable<Vector3> = null) : Path3D{
        for (var p = 0; p < path.length; p++) {
            this->_curve[p].x = path[p].x;
            this->_curve[p].y = path[p].y;
            this->_curve[p].z = path[p].z;
        }
        this->_compute(firstNormal);
        return this;
    }

    // private function compute() : computes tangents, normals and binormals
    private

            _compute(firstNormal : Nullable<Vector3>) : void {
        var l = this->_curve.length;

        // first and last tangents
        this->_tangents[0] = this->_getFirstNonNullVector(0);
        if (!this->_raw) {
            this->_tangents[0].normalize();
        }
        this->_tangents[l - 1] = this->_curve[l - 1].subtract(this->_curve[l - 2]);
        if (!this->_raw) {
            this->_tangents[l - 1].normalize();
        }

        // normals and binormals at first point : arbitrary vector with _normalVector()
        var tg0 = this->_tangents[0];
        var pp0 = this->_normalVector(this->_curve[0], tg0, firstNormal);
        this->_normals[0] = pp0;
        if (!this->_raw) {
            this->_normals[0].normalize();
        }
        this->_binormals[0] = Vector3.Cross(tg0, this->_normals[0]);
        if (!this->_raw) {
            this->_binormals[0].normalize();
        }
        this->_distances[0] = 0.0;

        // normals and binormals : next points
        var prev : Vector3; // previous vector (segment)
        var cur : Vector3; // current vector (segment)
        var curTang : Vector3; // current tangent
        // previous normal
        var prevBinor : Vector3; // previous binormal
        for (var i = 1; i < l; i++) {
            // tangents
            prev = this->_getLastNonNullVector(i);
            if (i < l - 1) {
                cur = this->_getFirstNonNullVector(i);
                this->_tangents[i] = prev.add(cur);
                this->_tangents[i].normalize();
            }
            this->_distances[i] = this->_distances[i - 1] + prev.length();

            // normals and binormals
            // http://www.cs.cmu.edu/afs/andrew/scs/cs/15-462/web/old/asst2camera.html
            curTang = this->_tangents[i];
            prevBinor = this->_binormals[i - 1];
            this->_normals[i] = Vector3.Cross(prevBinor, curTang);
            if (!this->_raw) {
                this->_normals[i].normalize();
            }
            this->_binormals[i] = Vector3.Cross(curTang, this->_normals[i]);
            if (!this->_raw) {
                this->_binormals[i].normalize();
            }
        }
    }

    // private function getFirstNonNullVector(index)
    // returns the first non null vector from index : curve[index + N].subtract(curve[index])
    private _getFirstNonNullVector(index : number) : Vector3{
        var i = 1;
        var nNVector : Vector3 = this->_curve[index + i].subtract(this->_curve[index]);
        while (nNVector.length() == 0 && index + i + 1 < this->_curve.length) {
            i++;
            nNVector = this->_curve[index + i].subtract(this->_curve[index]);
        }
        return nNVector;
    }

    // private function getLastNonNullVector(index)
    // returns the last non null vector from index : curve[index].subtract(curve[index - N])
    private _getLastNonNullVector(index : number) : Vector3{
        var i = 1;
        var nLVector : Vector3 = this->_curve[index].subtract(this->_curve[index - i]);
        while (nLVector.length() == 0 && index > i + 1) {
            i++;
            nLVector = this->_curve[index].subtract(this->_curve[index - i]);
        }
        return nLVector;
    }

    // private function normalVector(v0, vt, va) :
    // returns an arbitrary point in the plane defined by the point v0 and the vector vt orthogonal to this plane
    // if va is passed, it returns the va projection on the plane orthogonal to vt at the point v0
    private _normalVector(v0 : Vector3, vt : Vector3, va : Nullable<Vector3>) : Vector3{
        var normal0 : Vector3;
        var tgl = vt.length();
        if (tgl == 0.0) {
            tgl = 1.0;
        }

        if (va == undefined || va == null) {
            var point : Vector3;
            if (!Scalar.WithinEpsilon(std::abs(vt.y) / tgl, 1.0, Epsilon)) { // search for a point in the plane
                point = new Vector3(0.0, -1.0, 0.0);
            } else if (!Scalar.WithinEpsilon(std::abs(vt.x) / tgl, 1.0, Epsilon)) {
                point = new Vector3(1.0, 0.0, 0.0);
            } else if (!Scalar.WithinEpsilon(std::abs(vt.z) / tgl, 1.0, Epsilon)) {
                point = new Vector3(0.0, 0.0, 1.0);
            } else {
                point = Vector3.Zero();
            }
            normal0 = Vector3.Cross(vt, point);
        } else {
            normal0 = Vector3.Cross(vt, va);
            Vector3.CrossToRef(normal0, vt, normal0);
        }
        normal0.normalize();
        return normal0;
    }
}

export class Curve3 {
    private 
_points:
    Vector3[];
    private 
_length:
    number = 0.0;

    /**
     * Returns a Curve3 object along a Quadratic Bezier curve : http://doc.babylonjs.com/tutorials/How_to_use_Curve3#quadratic-bezier-curve
     * @param v0 (Vector3) the origin point of the Quadratic Bezier
     * @param v1 (Vector3) the control point
     * @param v2 (Vector3) the end point of the Quadratic Bezier
     * @param nbPoints (integer) the wanted number of points in the curve
     */
    public static CreateQuadraticBezier(v0 : Vector3, v1 : Vector3, v2 : Vector3, nbPoints : number) : Curve3{
        nbPoints = nbPoints > 2 ? nbPoints : 3;
        var bez = new Array<Vector3>();
        var equation = (t : number, val0 : number, val1 : number, val2 : number) = >
        {
            var res = (1.0 - t) * (1.0 - t) * val0 + 2.0 * t * (1.0 - t) * val1 + t * t * val2;
            return res;
        }
        for (var i = 0; i <= nbPoints; i++) {
            bez.push(new Vector3(equation(i / nbPoints, v0.x, v1.x, v2.x), equation(i / nbPoints, v0.y, v1.y, v2.y), equation(i / nbPoints, v0.z, v1.z, v2.z)));
        }
        return new Curve3(bez);
    }

    /**
     * Returns a Curve3 object along a Cubic Bezier curve : http://doc.babylonjs.com/tutorials/How_to_use_Curve3#cubic-bezier-curve
     * @param v0 (Vector3) the origin point of the Cubic Bezier
     * @param v1 (Vector3) the first control point
     * @param v2 (Vector3) the second control point
     * @param v3 (Vector3) the end point of the Cubic Bezier
     * @param nbPoints (integer) the wanted number of points in the curve
     */
    public static CreateCubicBezier(v0 : Vector3, v1 : Vector3, v2 : Vector3, v3 : Vector3, nbPoints : number) : Curve3{
        nbPoints = nbPoints > 3 ? nbPoints : 4;
        var bez = new Array<Vector3>();
        var equation = (t : number, val0 : number, val1 : number, val2 : number, val3 : number) = >
        {
            var res = (1.0 - t) * (1.0 - t) * (1.0 - t) * val0 + 3.0 * t * (1.0 - t) * (1.0 - t) * val1 + 3.0 * t * t * (1.0 - t) * val2 + t * t * t * val3;
            return res;
        }
        for (var i = 0; i <= nbPoints; i++) {
            bez.push(new Vector3(equation(i / nbPoints, v0.x, v1.x, v2.x, v3.x), equation(i / nbPoints, v0.y, v1.y, v2.y, v3.y), equation(i / nbPoints, v0.z, v1.z, v2.z, v3.z)));
        }
        return new Curve3(bez);
    }

    /**
     * Returns a Curve3 object along a Hermite Spline curve : http://doc.babylonjs.com/tutorials/How_to_use_Curve3#hermite-spline
     * @param p1 (Vector3) the origin point of the Hermite Spline
     * @param t1 (Vector3) the tangent vector at the origin point
     * @param p2 (Vector3) the end point of the Hermite Spline
     * @param t2 (Vector3) the tangent vector at the end point
     * @param nbPoints (integer) the wanted number of points in the curve
     */
    public static CreateHermiteSpline(p1 : Vector3, t1 : Vector3, p2 : Vector3, t2 : Vector3, nbPoints : number) : Curve3{
        var hermite = new Array<Vector3>();
        var step = 1.0 / nbPoints;
        for (var i = 0; i <= nbPoints; i++) {
            hermite.push(Vector3.Hermite(p1, t1, p2, t2, i * step));
        }
        return new Curve3(hermite);
    }

    /**
     * Returns a Curve3 object along a CatmullRom Spline curve :
     * @param points (array of Vector3) the points the spline must pass through. At least, four points required.
     * @param nbPoints (integer) the wanted number of points between each curve control points.
     */
    public static CreateCatmullRomSpline(points : Vector3[], nbPoints : number) : Curve3{
        var totalPoints = new Array<Vector3>();
        totalPoints.push(points[0].clone());
        Array.prototype.push.apply(totalPoints, points);
        totalPoints.push(points[points.length - 1].clone());
        var catmullRom = new Array<Vector3>();
        var step = 1.0 / nbPoints;
        var amount = 0.0;
        for (var i = 0; i < totalPoints.length - 3; i++) {
            amount = 0;
            for (var c = 0; c < nbPoints; c++) {
                catmullRom.push(Vector3.CatmullRom(totalPoints[i], totalPoints[i + 1], totalPoints[i + 2], totalPoints[i + 3], amount));
                amount += step
            }
        }
        i--;
        catmullRom.push(Vector3.CatmullRom(totalPoints[i], totalPoints[i + 1], totalPoints[i + 2], totalPoints[i + 3], amount));
        return new Curve3(catmullRom);
    }

    /**
     * A Curve3 object is a logical object, so not a mesh, to handle curves in the 3D geometric space.
     * A Curve3 is designed from a series of successive Vector3.
     * Tuto : http://doc.babylonjs.com/tutorials/How_to_use_Curve3#curve3-object
     */
    constructor(points : Vector3[]) {
        this->_points = points;
        this->_length = this->_computeLength(points);
    }

    /**
     * Returns the Curve3 stored array of successive Vector3
     */
    public

           getPoints() {
        return this->_points;
    }

    /**
     * Returns the computed length (tnumber) of the curve.
     */
    public

           length() {
        return this->_length;
    }

    /**
     * Returns a new instance of Curve3 object : var curve = curveA.continue(curveB);
     * This new Curve3 is built by translating and sticking the curveB at the end of the curveA.
     * curveA and curveB keep unchanged.
     */
    public continue(curve : Curve3) : Curve3{
        var lastPoint = this->_points[this->_points.length - 1];
        var continuedPoints = this->_points.slice();
        var curvePoints = curve.getPoints();
        for (var i = 1; i < curvePoints.length; i++) {
            continuedPoints.push(curvePoints[i].subtract(curvePoints[0]).add(lastPoint));
        }
        var continuedCurve = new Curve3(continuedPoints);
        return continuedCurve;
    }

    private _computeLength(path : Vector3[]) : number{
        var l = 0;
        for (var i = 1; i < path.length; i++) {
            l += (path[i].subtract(path[i - 1])).length();
        }
        return l;
    }
}

// Vertex formats

export class PositionNormalVertex {

    constructor(public position : Vector3 = Vector3.Zero(), public normal : Vector3 = Vector3.Up()) {

    }

    public clone() : PositionNormalVertex{
        return new PositionNormalVertex(this->position.clone(), this->normal.clone());
    }
}

export class PositionNormalTextureVertex {

    constructor(public position : Vector3 = Vector3.Zero(), public normal : Vector3 = Vector3.Up(), public uv : Vector2 = Vector2.Zero()) {

    }

    public clone() : PositionNormalTextureVertex{
        return new PositionNormalTextureVertex(this->position.clone(), this->normal.clone(), this->uv.clone());
    }
}

// Temporary pre-allocated objects for engine internal use
// usage in any internal function :
// var tmp = Tmp.Vector3[0];   <= gets access to the first pre-created Vector3
// There's a Tmp array per object type : int, tnumber, Vector2, Vector3, Vector4, Quaternion, Matrix

export class Tmp {
    public static Color3 : Color3[] = [Color3.Black(), Color3.Black(), Color3.Black()];
    public static Vector2 : Vector2[] = [Vector2.Zero(), Vector2.Zero(), Vector2.Zero()]; // 3 temp Vector2 at once should be enough
    public static Vector3 : Vector3[] = [Vector3.Zero(), Vector3.Zero(), Vector3.Zero(),
    Vector3.Zero(), Vector3.Zero(), Vector3.Zero(), Vector3.Zero(), Vector3.Zero(), Vector3.Zero()]; // 9 temp Vector3 at once should be enough
    public static Vector4 : Vector4[] = [Vector4.Zero(), Vector4.Zero(), Vector4.Zero()]; // 3 temp Vector4 at once should be enough
    public static Quaternion : Quaternion[] = [Quaternion.Zero(), Quaternion.Zero()]; // 2 temp Quaternion at once should be enough
    public static Matrix : Matrix[] = [Matrix.Zero(), Matrix.Zero(),
    Matrix.Zero(), Matrix.Zero(),
    Matrix.Zero(), Matrix.Zero(),
    Matrix.Zero(), Matrix.Zero()]; // 6 temp Matrices at once should be enough
}
// Same as Tmp but not exported to keep it onyl for math functions to avoid conflicts

class MathTmp {
    public static Vector3 : Vector3[] = [Vector3.Zero()];
    public static Matrix : Matrix[] = [Matrix.Zero(), Matrix.Zero()];
    public static Quaternion : Quaternion[] = [Quaternion.Zero()];
}
}


#endif