#ifdef __GFORTRAN__
#define dump_hook1(flag,x1) call print_md5_float_all_c_with_flag(x1, sizeof(x1)/kind(x1), x1, len('x1'), flag, len('flag'));
#define dump_hook1_i(flag, numb, x1) call print_md5_float_all_c_with_flag_and_int(x1, sizeof(x1)/kind(x1), x1, len('x1'), flag, len('flag'), numb);
#else
#define dump_hook1(flag,x1) call print_md5_float_all_c_with_flag(x1, sizeof(x1)/kind(x1), #x1, len(#x1), #flag, len(#flag));
#define dump_hook1_i(flag, numb, x1) call print_md5_float_all_c_with_flag_and_int(x1, sizeof(x1)/kind(x1), #x1, len(#x1), #flag, len(#flag), numb);
#endif

#define dump_hook2(flag,x1,x2) dump_hook1(flag,x1) dump_hook1(flag,x2)

#define dump_hook3(flag,x1,x2,x3) dump_hook1(flag,x1)  dump_hook2(flag,x2,x3)

#define dump_hook4(flag,x1,x2,x3,x4) dump_hook1(flag,x1)   dump_hook3(flag,x2,x3,x4)

#define dump_hook5(flag,x1,x2,x3,x4,x5)   dump_hook1(flag,x1)   dump_hook4(flag,x2,x3,x4,x5)

#define dump_hook6(flag,x1,x2,x3,x4,x5,x6) dump_hook1(flag,x1)   dump_hook5(flag,x2,x3,x4,x5,x6)

#define dump_hook7(flag,x1,x2,x3,x4,x5,x6,x7)  dump_hook1(flag,x1)   dump_hook6(flag,x2,x3,x4,x5,x6,x7)

#define dump_hook8(flag,x1,x2,x3,x4,x5,x6,x7,x8)   dump_hook1(flag,x1)   dump_hook7(flag,x2,x3,x4,x5,x6,x7,x8)

#define dump_hook9(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9)   dump_hook1(flag,x1)   dump_hook8(flag,x2,x3,x4,x5,x6,x7,x8,x9)

#define dump_hook10(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10)  dump_hook1(flag,x1)   dump_hook9(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10)

#define dump_hook11(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11)   dump_hook1(flag,x1)   dump_hook10(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11)

#define dump_hook12(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12)   dump_hook1(flag,x1)   dump_hook11(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12)

#define dump_hook13(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13)   dump_hook1(flag,x1)   dump_hook12(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13)

#define dump_hook14(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14)   dump_hook1(flag,x1)   dump_hook13(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14)

#define dump_hook15(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15)   dump_hook1(flag,x1)   dump_hook14(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15)

#define dump_hook16(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16)   dump_hook1(flag,x1)   dump_hook15(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16)

#define dump_hook17(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17)   dump_hook1(flag,x1)   dump_hook16(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17)

#define dump_hook18(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18)  dump_hook1(flag,x1)   dump_hook17(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18)

#define dump_hook19(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19)   dump_hook1(flag,x1)   dump_hook18(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19)

#define dump_hook20(flag,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20)   dump_hook1(flag,x1)   dump_hook19(flag,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20)

#define dump_hook2_i(flag,numb,x1,x2) dump_hook1_i(flag,numb,x1) dump_hook1_i(flag,numb,x2)

#define dump_hook3_i(flag,numb,x1,x2,x3) dump_hook1_i(flag,numb,x1)  dump_hook2_i(flag,numb,x2,x3)

#define dump_hook4_i(flag,numb,x1,x2,x3,x4) dump_hook1_i(flag,numb,x1)   dump_hook3_i(flag,numb,x2,x3,x4)

#define dump_hook5_i(flag,numb,x1,x2,x3,x4,x5)   dump_hook1_i(flag,numb,x1)   dump_hook4_i(flag,numb,x2,x3,x4,x5)

#define dump_hook6_i(flag,numb,x1,x2,x3,x4,x5,x6) dump_hook1_i(flag,numb,x1)   dump_hook5_i(flag,numb,x2,x3,x4,x5,x6)

#define dump_hook7_i(flag,numb,x1,x2,x3,x4,x5,x6,x7)  dump_hook1_i(flag,numb,x1)   dump_hook6_i(flag,numb,x2,x3,x4,x5,x6,x7)

#define dump_hook8_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8)   dump_hook1_i(flag,numb,x1)   dump_hook7_i(flag,numb,x2,x3,x4,x5,x6,x7,x8)

#define dump_hook9_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9)   dump_hook1_i(flag,numb,x1)   dump_hook8_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9)

#define dump_hook10_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10)  dump_hook1_i(flag,numb,x1)   dump_hook9_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10)

#define dump_hook11_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11)   dump_hook1_i(flag,numb,x1)   dump_hook10_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11)

#define dump_hook12_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12)   dump_hook1_i(flag,numb,x1)   dump_hook11_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12)

#define dump_hook13_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13)   dump_hook1_i(flag,numb,x1)   dump_hook12_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13)

#define dump_hook14_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14)   dump_hook1_i(flag,numb,x1)   dump_hook13_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14)

#define dump_hook15_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15)   dump_hook1_i(flag,numb,x1)   dump_hook14_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15)

#define dump_hook16_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16)   dump_hook1_i(flag,numb,x1)   dump_hook15_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16)

#define dump_hook17_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17)   dump_hook1_i(flag,numb,x1)   dump_hook16_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17)

#define dump_hook18_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18)  dump_hook1_i(flag,numb,x1)   dump_hook17_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18)

#define dump_hook19_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19)   dump_hook1_i(flag,numb,x1)   dump_hook18_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19)

#define dump_hook20_i(flag,numb,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20)   dump_hook1_i(flag,numb,x1)   dump_hook19_i(flag,numb,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20)

