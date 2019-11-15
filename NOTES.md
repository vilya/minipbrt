Notes
=====

Computing a 4x4 Matrix Inverse
------------------------------

The minor of a matrix for row i and column j is what you get when you delete
row i and column j from the matrix.

Determinant of a 2x2 matrix

	a b 
	c d

= `ad - bc`


Determinant of a 3x3 matrix

	a00 a01 a02
	a10 a11 a12
	a20 a21 a22

=
	a00 * det(minor(a, 0, 0)) - a01 * det(minor(a, 0, 1)) + a02 * det(minor(a, 0, 2))

=
	a00 * det(a11 a12   -  a01 * det(a10 a12   +  a02 * det(a10 a11
	          a21 a22)               a20 a22)               a20 a21)

=
	a00 * (a11 * a22 - a12 * a21) 
  - a01 * (a10 * a22 - a12 * a20) 
  + a02 * (a10 * a21 - a11 * a20)



Determinant of a 4x4 matrix a
	a00 a01 a02 a03
	a10 a11 a12 a13
	a20 a21 a22 a23
	a30 a31 a32 a33

= 
	a00 * det(minor(a, 0, 0)) - a01 * det(minor(a, 0, 1)) + a02 * det(minor(a, 0, 2)) - a03 * det(minor(a, 0, 3))

=
	a00 * det(a11 a12 a13   -  a01 * det(a10 a12 a13   + a02 * det(a10 a11 a13   - a03 * det(a10 a11 a12
	          a21 a22 a23                a20 a22 a23               a20 a21 a23               a20 a21 a22
	          a31 a32 a33)               a30 a32 a33)              a30 a31 a33)              a30 a31 a32)

=
	a00 * (a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 * a31))
  - a01 * (a10 * (a22 * a33 - a23 * a32) - a12 * (a20 * a33 - a23 * a30) + a13 * (a20 * a32 - a22 * a30))
  + a02 * (a10 * (a21 * a33 - a23 * a31) - a11 * (a20 * a33 - a23 * a30) + a13 * (a20 * a31 - a21 * a30))
  - a03 * (a10 * (a21 * a32 - a22 * a31) - a11 * (a20 * a32 - a22 * a30) + a12 * (a20 * a31 - a21 * a30))


The cofactor matrix for a 4x4 matrix a is

	+det(minor(a, 0, 0))	-det(minor(a, 0, 1))	+det(minor(a, 0, 2))	-det(minor(a, 0, 3))
	-det(minor(a, 1, 0))	+det(minor(a, 1, 1))	-det(minor(a, 1, 2))	+det(minor(a, 1, 3))
	+det(minor(a, 2, 0))	-det(minor(a, 2, 1))	+det(minor(a, 2, 2))	-det(minor(a, 2, 3))
	-det(minor(a, 3, 0))	+det(minor(a, 3, 1))	-det(minor(a, 3, 2))	+det(minor(a, 3, 3))

Notice that the determinant of a is simply the sum of the elements in the top row.


The "classical adjoint" or "adjugate" is simply the transpose of the cofactor matrix.

The inverse of a 4x4 matrix is the adjugate with every element divided by the determinant.


So inv(a) = 

(1 / det(a)) *

	+det(minor(a, 0, 0))	-det(minor(a, 1, 0))	+det(minor(a, 2, 0))	-det(minor(a, 2, 0))
	-det(minor(a, 0, 1))	+det(minor(a, 1, 1))	-det(minor(a, 2, 1))	+det(minor(a, 2, 1))
	+det(minor(a, 0, 2))	-det(minor(a, 1, 2))	+det(minor(a, 2, 2))	-det(minor(a, 2, 2))
	-det(minor(a, 0, 3))	+det(minor(a, 1, 3))	-det(minor(a, 2, 3))	+det(minor(a, 2, 3))


Denote the minor of a minor of a 4x4 matrix as the 2x2 matrix mab,cd where a
and b are the indices of the rows that remain & c and d are the indices of the
columns that remain.

For the cofactor matrix c

c00 = det(minor(a, 0, 0))
c00 = det(a11 a12 a13
	      a21 a22 a23
	      a31 a32 a33)
c00 = a11 * det(m23,23) - a12 * det(m23,13) + a13 * det(m23,12)

c01 = det(minor(a, 0, 1))
c01 = det(a10 a12 a13
	      a20 a22 a23
	      a30 a32 a33)
c01 = a10 * det(m23,23) - a12 * det(m23,03) + a13 * det(m23,02)

c02 = det(minor(a, 0, 2))
c02 = det(a10 a11 a13
		  a20 a21 a23
		  a30 a31 a33)
c02 = a10 * det(m23,12) - a11 * det(m23,03) + a13 * det(m23,01)

c03 = det(minor(a, 0, 3))
c03 = det(a10 a11 a12
		  a20 a21 a22
		  a30 a31 a32)
c03 = a10 * det(m23,12) - a11 * det(m23,02) + a12 * det(m23,01)

c10 = det(minor(a, 1, 0))
c10 = det(a01 a02 a03
	      a21 a22 a23
	      a31 a32 a33)
c10 = a01 * det(m23,23) - a02 * det(m23,13) + a03 * det(m23,12)

c11 = det(minor(a, 1, 1))
c11 = det(a00 a02 a03
	      a20 a22 a23
	      a30 a32 a33)
c11 = a00 * det(m23,23) - a02 * det(m23,03) + a03 * det(m23,02)

c12 = det(minor(a, 1, 2))
c12 = det(a00 a01 a03
	      a20 a21 a23
	      a30 a31 a33)
c12 = a00 * det(m23,13) - a01 * det(m23,03) + a03 * det(m23,01)

c13 = det(minor(a, 1, 3))
c13 = det(a00 a01 a02
	      a20 a21 a22
	      a30 a31 a32)
c13 = a00 * det(m23,12) - a01 * det(m23,02) + a02 * det(m23,01)

c20 = det(minor(a, 2, 0))
c20 = det(a01 a02 a03
		  a11 a12 a13
		  a31 a32 a33)
c20 = a01 * det(m13,23) - a02 * det(m13,13) + a03 * det(m13,12)

c21 = det(minor(a, 2, 1))
c21 = det(a00 a02 a03
		  a10 a12 a13
		  a30 a32 a33)
c21 = a00 * det(m13,23) - a02 * det(m13,03) + a03 * det(m13,02)

c22 = det(minor(a, 2, 2))
c22 = det(a00 a01 a03
		  a10 a11 a13
		  a30 a31 a33)
c22 = a00 * det(m13,13) - a01 * det(m13,03) + a03 * det(m13,01)

c23 = det(minor(a, 2, 3))
c23 = det(a00 a01 a02
	      a10 a11 a12
	      a30 a31 a32)
c23 = a00 * det(m13,12) - a01 * det(m13,02) + a02 * det(m13,01)

c30 = det(minor(a, 3, 0))
c30 = det(a01 a02 a03
		  a11 a12 a13
		  a21 a22 a23)
c30 = a01 * det(m12,23) - a02 * det(m12,13) + a03 * det(m12,12)

c31 = det(minor(a, 3, 1))
c31 = det(a00 a02 a03
		  a10 a12 a13
		  a20 a22 a23)
c31 = a00 * det(m12,23) - a02 * det(m12,03) + a03 * det(m12,02)

c32 = det(minor(a, 3, 2))
c32 = det(a00 a01 a03
	      a10 a11 a13
	      a20 a21 a23)
c32 = a00 * det(m12,13) - a01 * det(m12,03) + a03 * det(m12,01)

c33 = det(minor(a, 3, 3))
c33 = det(a00 a01 a02
		  a10 a11 a12
		  a20 a21 a22)
c33 = a00 * det(m12,12) - a01 * det(m12,02) + a02 * det(m12,01)



So the cofactor matrix entries are:

	c00 = a11 * det(m23,23) - a12 * det(m23,13) + a13 * det(m23,12)
	c01 = a10 * det(m23,23) - a12 * det(m23,03) + a13 * det(m23,02)
	c02 = a10 * det(m23,12) - a11 * det(m23,03) + a13 * det(m23,01)
	c03 = a10 * det(m23,12) - a11 * det(m23,02) + a12 * det(m23,01)

	c10 = a01 * det(m23,23) - a02 * det(m23,13) + a03 * det(m23,12)
	c11 = a00 * det(m23,23) - a02 * det(m23,03) + a03 * det(m23,02)
	c12 = a00 * det(m23,13) - a01 * det(m23,03) + a03 * det(m23,01)
	c13 = a00 * det(m23,12) - a01 * det(m23,02) + a02 * det(m23,01)

	c20 = a01 * det(m13,23) - a02 * det(m13,13) + a03 * det(m13,12)
	c21 = a00 * det(m13,23) - a02 * det(m13,03) + a03 * det(m13,02)
	c22 = a00 * det(m13,13) - a01 * det(m13,03) + a03 * det(m13,01)
	c23 = a00 * det(m13,12) - a01 * det(m13,02) + a02 * det(m13,01)

	c30 = a01 * det(m12,23) - a02 * det(m12,13) + a03 * det(m12,12)
	c31 = a00 * det(m12,23) - a02 * det(m12,03) + a03 * det(m12,02)
	c32 = a00 * det(m12,13) - a01 * det(m12,03) + a03 * det(m12,01)
	c33 = a00 * det(m12,12) - a01 * det(m12,02) + a02 * det(m12,01)


If we cache the determinants of the 2x2 matrices:

	A = det(m23,23) = 
	B = det(m23,13)
	C = det(m23,12)
	D = det(m23,03)
	E = det(m23,02)
	F = det(m23,01)
	G = det(m13,23)
	H = det(m13,13)
	I = det(m13,12)
	J = det(m13,03)
	K = det(m13,02)
	L = det(m13,01)
	M = det(m12,23)
	N = det(m12,13)
	O = det(m12,12)
	P = det(m12,03)
	Q = det(m12,02)
	R = det(m12,01)

Then we get:

	c00 = +(a11 * A - a12 * B + a13 * C)
	c01 = -(a10 * A - a12 * D + a13 * E)
	c02 = +(a10 * C - a11 * D + a13 * F)
	c03 = -(a10 * C - a11 * E + a12 * F)

	c10 = -(a01 * A - a02 * B + a03 * C)
	c11 = +(a00 * A - a02 * D + a03 * E)
	c12 = -(a00 * B - a01 * D + a03 * F)
	c13 = +(a00 * C - a01 * E + a02 * F)

	c20 = +(a01 * G - a02 * H + a03 * I)
	c21 = -(a00 * G - a02 * J + a03 * K)
	c22 = +(a00 * H - a01 * J + a03 * L)
	c23 = -(a00 * I - a01 * K + a02 * L)

	c30 = -(a01 * M - a02 * N + a03 * O)
	c31 = +(a00 * M - a02 * P + a03 * Q)
	c32 = -(a00 * N - a01 * P + a03 * R)
	c33 = +(a00 * O - a01 * Q + a02 * R)

The determinant of the matrix is the sum of the first row of the cofactor
matrix, which is the first column of the adjugate.
	
So to calculate the inverse:

	inv00 = +(a11 * A - a12 * B + a13 * C)
	inv01 = -(a01 * A - a02 * B + a03 * C)
	inv02 = +(a01 * G - a02 * H + a03 * I)
	inv03 = -(a01 * M - a02 * N + a03 * O)

	inv10 = -(a10 * A - a12 * D + a13 * E)
	inv11 = +(a00 * A - a02 * D + a03 * E)
	inv12 = -(a00 * G - a02 * J + a03 * K)
	inv13 = +(a00 * M - a02 * P + a03 * Q)

	inv20 = +(a10 * C - a11 * D + a13 * F)
	inv21 = -(a00 * B - a01 * D + a03 * F)
	inv22 = +(a00 * H - a01 * J + a03 * L)
	inv23 = -(a00 * N - a01 * P + a03 * R)

	inv30 = -(a10 * C - a11 * E + a12 * F)
	inv31 = +(a00 * C - a01 * E + a02 * F)
	inv32 = -(a00 * I - a01 * K + a02 * L)
	inv33 = +(a00 * O - a01 * Q + a02 * R)

	detA = i00 + i10 + i20 + i30

	inv /= detA
