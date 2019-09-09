from .context import j0
import j0.sexpr as s

def test_empty():
    x = s.Nil()
    x.pp()

def test_number_value():
    x = s.Cons(s.Atom("4"), s.Nil())
    x.pp()

def test_add_nocrash():
    x = s.Cons(s.Atom("+"), s.Cons(s.Atom("4"),
        s.Cons(s.Atom("4"), s.Nil())))
    x.pp()
    #assert y.number == 11 or true


def test_mult_nocrash():
    # x = e.Mult(v.Number(4),v.Number(7))
    x = s.Cons(s.Atom("*"),s.Cons(s.Atom("4"),
        s.Cons(s.Atom("7"),s.Nil())))
    x.pp()
#     assert x.left.number == 4 and x.right.number == 7
#     y = x.ibig()
#     y.pp()
#     assert y.number == 28

def test_add_mult_number_left_sag():
#     x = e.Add(e.Mult(v.Number(4), v.Number(7)),v.Number(5))
    x = s.Cons(s.Atom("+"),s.Cons(s.Cons(
        s.Atom("*"),s.Cons(s.Atom("4"),
        s.Cons(s.Atom("7"),s.Nil()))),
        s.Cons(s.Atom("5"),s.Nil())))
    x.pp()
#     assert x.left.left.number == 4 and x.left.right.number == 7 and x.right.number == 5
#     y = x.ibig()
#     y.pp()
#     assert y.number == 33

def test_add_mult_number_right_sag():
    x = s.Cons(s.Atom("+"),s.Cons(s.Atom("4"),
        s.Cons(s.Atom("*"),s.Cons(s.Atom("7"),
            s.Cons(s.Atom("5"),s.Nil())))))
    x.pp()
#     assert x.left.number == 4 and x.right.left.number == 7 and x.right.right.number == 5
#     y = x.ibig()
#     y.pp()
#     assert y.number == 39

def test_mult_add_number_left_sag():
    x = s.Cons(s.Atom("*"),s.Cons(s.Cons(
        s.Atom("+"),s.Cons(s.Atom("4"),
        s.Cons(s.Atom("7"),s.Nil()))),
        s.Cons(s.Atom("5"),s.Nil())))
    x.pp()

#     x = e.Mult(e.Add(v.Number(4), v.Number(7)),v.Number(5))
#     x.pp()
#     assert x.left.left.number == 4 and x.left.right.number == 7 and x.right.number == 5
#     y = x.ibig()
#     y.pp()
#     assert y.number == 55

def test_mult_add_number_right_sag():
    x = s.Cons(s.Atom("*"),s.Cons(s.Atom("4"),
        s.Cons(s.Atom("+"),s.Cons(s.Atom("7"),
            s.Cons(s.Atom("5"),s.Nil())))))
    x.pp()
#     x = e.Mult(v.Number(4), e.Add(v.Number(7), v.Number(5)))
#     x.pp()
#     assert x.left.number == 4 and x.right.left.number == 7 and x.right.right.number == 5
#     y = x.ibig()
#     y.pp()
#     assert y.number == 48

def test_add_add_add_balanced():
    x = s.Cons(s.Atom("+"),s.Cons(s.Cons(
        s.Atom("+"),s.Cons(s.Atom("4"),
        s.Cons(s.Atom("7"),s.Nil()))),
        s.Cons(s.Atom("+"),s.Cons(s.Atom("5"),
            s.Cons(s.Atom("2"),s.Nil())))))
    x.pp()
#     y = x.ibig()
#     y.pp()
#     assert y.number == 18

def test_mult_mult_mult_balanced():
    x = s.Cons(s.Atom("*"),s.Cons(s.Cons(
        s.Atom("*"),s.Cons(s.Atom("4"),
        s.Cons(s.Atom("7"),s.Nil()))),
        s.Cons(s.Atom("*"),s.Cons(s.Atom("5"),
            s.Cons(s.Atom("2"),s.Nil())))))
#     x = e.Mult( \
#             e.Mult(v.Number(4), v.Number(7)), \
#             e.Mult(v.Number(5), v.Number(2)))
    x.pp()
#     assert x.left.left.number == 4 and x.left.right.number == 7 \
#         and x.right.left.number == 5 and x.right.right.number == 2
#     y = x.ibig()
#     y.pp()
#     assert y.number == 280

def test_add_mult_add_left_sag():
#     x = e.Add(e.Mult(e.Add( \
#             v.Number(4), v.Number(7)), \
#             v.Number(5)), v.Number(2))
    x = s.Cons(s.Atom("+"),s.Cons(s.Cons(s.Atom("*"),s.Cons(
        s.Cons(s.Atom("+"),s.Cons(s.Atom("4"),s.Cons(s.Atom("7"),s.Nil()))),
        s.Cons(s.Atom("5"),s.Nil()))),s.Cons(s.Atom("2"),s.Nil())))

    x.pp()
#     assert x.left.left.left.number == 4 and x.left.left.right.number == 7 \
#         and x.left.right.number == 5 and x.right.number == 2
#     y = x.ibig()
#     y.pp()
#     assert y.number == 57

def test_mult_add_mult_left_sag():
    x = s.Cons(s.Atom("*"),s.Cons(s.Cons(s.Atom("+"),s.Cons(
        s.Cons(s.Atom("*"),s.Cons(s.Atom("4"),s.Cons(s.Atom("7"),s.Nil()))),
        s.Cons(s.Atom("5"),s.Nil()))),s.Cons(s.Atom("2"),s.Nil())))

    x.pp()
#     x = e.Mult(e.Add(e.Mult( \
#             v.Number(4), v.Number(7)), \
#             v.Number(5)), v.Number(2))
#     x.pp()
#     assert x.left.left.left.number == 4 and x.left.left.right.number == 7 \
#         and x.left.right.number == 5 and x.right.number == 2
#     y = x.ibig()
#     y.pp()
#     assert y.number == 66

def test_add_add_add_add_left_sag():
#     x = e.Add(e.Add(e.Add(e.Add( \
#         v.Number(4),v.Number(7)), \
#         v.Number(5)),v.Number(2)), \
#         v.Number(6))
    x = s.Cons(s.Atom("+"),s.Cons(s.Cons(s.Atom("+"),s.Cons(s.Cons(s.Atom("+"),s.Cons(
            s.Cons(s.Atom("+"),s.Cons(s.Atom("4"),s.Cons(s.Atom("7"),s.Nil()))),
            s.Cons(s.Atom("5"),s.Nil()))),s.Cons(s.Atom("2"),s.Nil()))),
            s.Cons(s.Atom("6"),s.Nil())))

    x.pp()
#     assert x.left.left.left.left.number == 4 and x.left.left.left.right.number == 7 \
#         and x.left.left.right.number == 5 and x.left.right.number == 2 and x.right.number == 6
#     y = x.ibig()
#     y.pp()
#     assert y.number == 24
