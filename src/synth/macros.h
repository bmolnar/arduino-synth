#ifndef SYNTH__MACROS_H_
#define SYNTH__MACROS_H_


#define XLIB_LITERAL_EMPTY()
#define XLIB_LITERAL_COMMA() ,
#define XLIB_LITERAL_NEWLINE() \


#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0 (EVAL0 (EVAL0 (__VA_ARGS__)))
#define EVAL2(...) EVAL1 (EVAL1 (EVAL1 (__VA_ARGS__)))
#define EVAL3(...) EVAL2 (EVAL2 (EVAL2 (__VA_ARGS__)))
#define EVAL4(...) EVAL3 (EVAL3 (EVAL3 (__VA_ARGS__)))
#define EVAL(...)  EVAL4 (EVAL4 (EVAL4 (__VA_ARGS__)))

#define XLIB_XCONCAT(_a,_b) XLIB_CONCAT(_a,_b)
#define XLIB_CONCAT(_a,_b) _a ## _b


#define XLIB_SEQ_0() 
#define XLIB_SEQ_1() 0
#define XLIB_SEQ_2() 0,1
#define XLIB_SEQ_3() 0,1,2
#define XLIB_SEQ_4() 0,1,2,3
#define XLIB_SEQ_5() 0,1,2,3,4
#define XLIB_SEQ_6() 0,1,2,3,4,5
#define XLIB_SEQ_7() 0,1,2,3,4,5,6
#define XLIB_SEQ_8() 0,1,2,3,4,5,6,7
#define XLIB_SEQ_64() \
  0,1,2,3,4,5,6,7,8,9, \
  10,11,12,13,14,15,16,17,18,19, \
  20,21,22,23,24,25,26,27,28,29, \
  30,31,32,33,34,35,36,37,38,39, \
  40,41,42,43,44,45,46,47,48,49, \
  50,51,52,53,54,55,56,57,58,59, \
  60,61,62,63

#define XLIB_SEQ(_n) XLIB_XCONCAT(XLIB_SEQ_, _n)()


#define XLIB_RSEQ_0()
#define XLIB_RSEQ_1() 0
#define XLIB_RSEQ_2() 1,0
#define XLIB_RSEQ_3() 2,1,0
#define XLIB_RSEQ_4() 3,2,1,0
#define XLIB_RSEQ_5() 4,3,2,1,0
#define XLIB_RSEQ_6() 5,4,3,2,1,0
#define XLIB_RSEQ_7() 6,5,4,3,2,1,0
#define XLIB_RSEQ_8() 7,6,5,4,3,2,1,0
#define XLIB_RSEQ_64() \
  63,62,61,60,                   \
  59,58,57,56,55,54,53,52,51,50, \
  49,48,47,46,45,44,43,42,41,40, \
  39,38,37,36,35,34,33,32,31,30, \
  29,28,27,26,25,24,23,22,21,20, \
  19,18,17,16,15,14,13,12,11,10, \
  9,8,7,6,5,4,3,2,1,0

#define XLIB_RSEQ(_n) XLIB_XCONCAT(XLIB_RSEQ_, _n)()


#define XLIB_ARGS_COUNT(...)  XLIB_ARGS_COUNT_(__VA_ARGS__, XLIB_RSEQ_64())
#define XLIB_ARGS_COUNT_(...) XLIB_ARGS_GET64(__VA_ARGS__)

#define XLIB_ARGS_GET1(_N,...) _N
#define XLIB_ARGS_GET2(_1,_N,...) _N
#define XLIB_ARGS_GET3(_1,_2,_N,...) _N
#define XLIB_ARGS_GET4(_1,_2,_3,_N,...) _N
#define XLIB_ARGS_GET5(_1,_2,_3,_4,_N,...) _N
#define XLIB_ARGS_GET6(_1,_2,_3,_4,_5,_N,...) _N
#define XLIB_ARGS_GET7(_1,_2,_3,_4,_5,_6,_N,...) _N
#define XLIB_ARGS_GET8(_1,_2,_3,_4,_5,_6,_7,_N,...) _N
#define XLIB_ARGS_GET64( \
        _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,  \
        _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
        _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
        _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
        _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
        _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
        _61,_62,_63,_N,...) _N



#define XLIB_APPLY(_f, ...) _f (__VA_ARGS__)


/*
#define XLIB_MAP_OUT
#define XLIB_MAP_END(...)
#define XLIB_MAP_GET_END() 0, XLIB_MAP_END
#define XLIB_MAP_NEXT0(_t, _n, ...) _n XLIB_MAP_OUT
#define XLIB_MAP_NEXT1(_t, _n) XLIB_MAP_NEXT0(_t, _n, 0)
#define XLIB_MAP_NEXT(_t, _n)  XLIB_MAP_NEXT1(XLIB_MAP_GET_END _t, _n)
#define XLIB_MAP_SEP_GET_END() 0, XLIB_LITERAL_EMPTY, XLIB_MAP_END
#define XLIB_MAP_SEP(_s, _t) XLIB_ARGS_GET2(XLIB_MAP_SEP_GET_END _t, _s)
#define XLIB_MAP0(_f, _x, _p, ...) _f(_x) XLIB_MAP_SEP(XLIB_LITERAL_COMMA, _p) XLIB_MAP_NEXT(_p, XLIB_MAP1) (_f, _p, __VA_ARGS__)
#define XLIB_MAP1(_f, _x, _p, ...) _f(_x) XLIB_MAP_SEP(XLIB_LITERAL_COMMA, _p) XLIB_MAP_NEXT(_p, XLIB_MAP0) (_f, _p, __VA_ARGS__)
#define XLIB_MAP(_f, ...) EVAL (XLIB_MAP1 (_f, __VA_ARGS__, (), 0))
*/


#define XLIB_MAP_0(_f)
#define XLIB_MAP_1(_f,_1) _f(_1)
#define XLIB_MAP_2(_f,_1,_2) _f(_1), _f(_2)
#define XLIB_MAP_3(_f,_1,_2,_3) _f(_1), _f(_2), _f(_3)
#define XLIB_MAP_4(_f,_1,_2,_3,_4) _f(_1), _f(_2), _f(_3), _f(_4)
#define XLIB_MAP_5(_f,_1,_2,_3,_4,_5) _f(_1), _f(_2), _f(_3), _f(_4), _f(_5)
#define XLIB_MAP_6(_f,_1,_2,_3,_4,_5,_6) _f(_1), _f(_2), _f(_3), _f(_4), _f(_5), _f(_6)
#define XLIB_MAP_7(_f,_1,_2,_3,_4,_5,_6,_7) _f(_1), _f(_2), _f(_3), _f(_4), _f(_5), _f(_6), _f(_7)
#define XLIB_MAP_8(_f,_1,_2,_3,_4,_5,_6,_7,_8) _f(_1), _f(_2), _f(_3), _f(_4), _f(_5), _f(_6), _f(_7), _f(_8)

#define XLIB_MAP_FUNC(_n) XLIB_XCONCAT(XLIB_MAP_, _n)
#define XLIB_MAP2(_n,_f, ...) XLIB_MAP_FUNC(_n) (_f, __VA_ARGS__)
#define XLIB_MAP1(_f, ...) XLIB_MAP2(XLIB_ARGS_COUNT(__VA_ARGS__), _f, __VA_ARGS__)
#define XLIB_MAP(_f, ...) XLIB_MAP1(_f, __VA_ARGS__)



#define XLIB_JOIN_0(_s)
#define XLIB_JOIN_1(_s,_1) _1
#define XLIB_JOIN_2(_s,_1,_2) _1 _s _2
#define XLIB_JOIN_3(_s,_1,_2,_3) _1 _s _2 _s _3
#define XLIB_JOIN_4(_s,_1,_2,_3,_4) _1 _s _2 _s _3 _s _4
#define XLIB_JOIN_5(_s,_1,_2,_3,_4,_5) _1 _s _2 _s _3 _s _4 _s _5
#define XLIB_JOIN_6(_s,_1,_2,_3,_4,_5,_6) _1 _s _2 _s _3 _s _4 _s _5 _s _6
#define XLIB_JOIN_7(_s,_1,_2,_3,_4,_5,_6,_7) _1 _s _2 _s _3 _s _4 _s _5 _s _6 _s _7
#define XLIB_JOIN_8(_s,_1,_2,_3,_4,_5,_6,_7,_8) _1 _s _2 _s _3 _s _4 _s _5 _s _6 _s _7 _s _8

#define XLIB_JOIN_FUNC(_n) XLIB_XCONCAT(XLIB_JOIN_, _n)
#define XLIB_JOIN2(_n,_s, ...) XLIB_JOIN_FUNC(_n) (_s, __VA_ARGS__)
#define XLIB_JOIN1(_s, ...) XLIB_JOIN2(XLIB_ARGS_COUNT(__VA_ARGS__), _s, __VA_ARGS__)
#define XLIB_JOIN(_s, ...) XLIB_JOIN1(_s, __VA_ARGS__)


#endif // SYNTH__MACROS_H_
