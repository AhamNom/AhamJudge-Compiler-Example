import sympy as sp;

# k = sp.Symbol('k')

# m1 = sp.Matrix([
#     [1, 2 * k, 0, 0],
#     [0, 1, 0, 0],
#     [0, 0, 1, 0],
#     [k, k * k, 0, 1]
# ])
# m2 = sp.Matrix([
#     [1, 0, 0, 0],
#     [0, 1, 1, 0],
#     [0, 0, 1, 0],
#     [0, 0, 0, 1]
# ])

# m = m1 * m2

# m1 = m.subs(k, 'k_1')
# m2 = m.subs(k, 'k_2')

# m = m1 * m2
# # sp.pprint(m)
# # sp.pprint(m1 * m2 * m1 * m2 * m2 * m2 * m1)
# # print(sp.latex(m1 * m2 * m1 * m2 * m2 * m2 * m1))

# print('\n')

# ==========================================

# a, b, c, d, e, f = sp.symbols('a b c d e f')
# x, y, z = sp.symbols('x y z')

# Mat = sp.Matrix([
#     [1, a, b, 0],
#     [0, 1, c, 0],
#     [0, 0, 1, 0],
#     [d, e, f, 1]
# ])
# Vec = sp.Matrix([[
#     x, y, z, 1
# ]])

# sp.pprint(Vec * Mat)

# ==========================================

a1, b1, c1, d1, e1, f1 = sp.symbols('a1 b1 c1 d1 e1 f1')
a2, b2, c2, d2, e2, f2 = sp.symbols('a2 b2 c2 d2 e2 f2')

Mat1 = sp.Matrix([
    [1, a1, b1, 0],
    [0, 1, c1, 0],
    [0, 0, 1, 0],
    [d1, e1, f1, 1]
])
Mat2 = sp.Matrix([
    [1, a2, b2, 0],
    [0, 1, c2, 0],
    [0, 0, 1, 0],
    [d2, e2, f2, 1]
])

sp.pprint(Mat1 * Mat2)
print('\n')

# sp.pprint(sp.Matrix([[ a1 + a2, a1 * c2 + b1 + b2, c1 + c2, (2) * d1, a2 * d1 + (2) * e1, b2 * d1 + c2 * e1 + (2) * f1 ]]))