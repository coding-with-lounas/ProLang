TITLE  Code_Assembleur
DATA SEGMENT
    a DW ?
    b DW ?
    Max DW ?
    i DW ?
    j DW ?
    k DW ?
    x DW ?
    y DW ?
    z DW ?
    Tabint DW 50 DUP(?)
    Tabfloat DW 30 DUP(?)
    somme DW ?
    moyenne DW ?
    Pi DW ?
    t1 DW ?
    t2 DW ?
    t3 DW ?
    t5 DW ?
    t7 DW ?
    t8 DW ?
    t9 DW ?
    t10 DW ?
    t11 DW ?
    t12 DW ?
    t13 DW ?
    t16 DW ?
    t17 DW ?
    t19 DW ?
    t20 DW ?
    t21 DW ?
    t22 DW ?
    t25 DW ?
    t28 DW ?
    t29 DW ?
    t30 DW ?
    t31 DW ?
    t32 DW ?
    t34 DW ?
    t35 DW ?
    t36 DW ?
    t37 DW ?
    t38 DW ?
    t39 DW ?
    t40 DW ?
    t41 DW ?
    t43 DW ?
    t44 DW ?
    t45 DW ?
    t46 DW ?
    t47 DW ?
    t49 DW ?
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA
MAIN:
    MOV AX, DATA
    MOV DS, AX

etiq_0:
    MOV AX, 10
    MOV x, AX
etiq_1:
    MOV AX, 5
    MOV y, AX
etiq_2:
    MOV AX, 2
    MOV z, AX
etiq_4:
    MOV AX, 2
    ADD AX, Pi
    MOV t1, AX
etiq_5:
    MOV AX, t1
    MOV BX, 2
    MUL BX
    MOV t2, AX
etiq_7:
    MOV AX, 5
    MOV BX, 2
    MUL BX
    MOV t3, AX
etiq_8:
    MOV AX, 10
    ADD AX, t3
    PUSH AX
    MOV SI, 0
    SHL SI, 1
    POP AX
    MOV Tabint[SI], AX
etiq_10:
    MOV AX, t2
    ADD AX, 3
    MOV t5, AX
etiq_11:
    MOV AX, t5
    XOR DX, DX
    MOV BX, 2
    DIV BX
    PUSH AX
    MOV SI, 1
    SHL SI, 1
    POP AX
    MOV Tabfloat[SI], AX
etiq_13:
    MOV AX, 10
    CMP AX, 5
    JG  true_13
    MOV AX, 0
    MOV t7, AX
    JMP end_cmp_13
true_13:
    MOV AX, 1
    MOV t7, AX
end_cmp_13:
etiq_14:
    MOV AX, 10
    ADD AX, 5
    MOV t8, AX
etiq_15:
    MOV AX, 2
    CMP AX, t8
    JL  true_15
    MOV AX, 0
    MOV t9, AX
    JMP end_cmp_15
true_15:
    MOV AX, 1
    MOV t9, AX
end_cmp_15:
etiq_16:
    MOV AX, t7
    AND AX, t9
    MOV t10, AX
etiq_17:
    MOV AX, 5
    CMP AX, 0
    JE  true_17
    MOV AX, 0
    MOV t11, AX
    JMP end_cmp_17
true_17:
    MOV AX, 1
    MOV t11, AX
end_cmp_17:
etiq_18:
    MOV AX, t11
    XOR AX, 1
    MOV t12, AX
etiq_19:
    MOV AX, t10
    OR AX, t12
    MOV t13, AX
etiq_20:
    MOV AX, t13
    CMP AX, 0
    JNE skip_jmp_20
    JMP etiq_46
skip_jmp_20:
etiq_22:
    MOV AX, t8
    ADD AX, 2
    MOV somme, AX
etiq_24:
    MOV AX, 0
    MOV i, AX
etiq_25:
    MOV AX, i
    CMP AX, 10
    JLE true_25
    MOV AX, 0
    MOV t16, AX
    JMP end_cmp_25
true_25:
    MOV AX, 1
    MOV t16, AX
end_cmp_25:
etiq_26:
    MOV AX, t16
    CMP AX, 0
    JNE skip_jmp_26
    JMP etiq_45
skip_jmp_26:
etiq_27:
    MOV BX, i
    SHL BX, 1
    MOV AX, Tabint[BX]
    MOV t17, AX
etiq_28:
    MOV AX, t17
    ADD AX, i
    PUSH AX
    MOV SI, i
    SHL SI, 1
    POP AX
    MOV Tabint[SI], AX
etiq_30:
    MOV AX, i
    CMP AX, 5
    JL  true_30
    MOV AX, 0
    MOV t19, AX
    JMP end_cmp_30
true_30:
    MOV AX, 1
    MOV t19, AX
end_cmp_30:
etiq_31:
    MOV BX, i
    SHL BX, 1
    MOV AX, Tabint[BX]
    MOV t20, AX
etiq_32:
    MOV AX, t20
    CMP AX, 10
    JG  true_32
    MOV AX, 0
    MOV t21, AX
    JMP end_cmp_32
true_32:
    MOV AX, 1
    MOV t21, AX
end_cmp_32:
etiq_33:
    MOV AX, t19
    AND AX, t21
    MOV t22, AX
etiq_34:
    MOV AX, t22
    CMP AX, 0
    JNE skip_jmp_34
    JMP etiq_39
skip_jmp_34:
etiq_36:
    MOV AX, t20
    MOV BX, 1
    MUL BX
    PUSH AX
    MOV SI, i
    SHL SI, 1
    POP AX
    MOV Tabfloat[SI], AX
etiq_38:
    JMP etiq_42
etiq_39:
    MOV BX, i
    SHL BX, 1
    MOV AX, Tabint[BX]
    MOV t25, AX
etiq_40:
    MOV AX, t25
    XOR DX, DX
    MOV BX, 2
    DIV BX
    PUSH AX
    MOV SI, i
    SHL SI, 1
    POP AX
    MOV Tabfloat[SI], AX
etiq_42:
    MOV AX, i
    ADD AX, 1
    MOV i, AX
etiq_44:
    JMP etiq_25
etiq_45:
    JMP etiq_47
etiq_46:
    MOV AX, 0
    MOV somme, AX
etiq_47:
    MOV AX, x
    CMP AX, Max
    JLE true_47
    MOV AX, 0
    MOV t28, AX
    JMP end_cmp_47
true_47:
    MOV AX, 1
    MOV t28, AX
end_cmp_47:
etiq_48:
    MOV AX, y
    CMP AX, 0
    JNE true_48
    MOV AX, 0
    MOV t29, AX
    JMP end_cmp_48
true_48:
    MOV AX, 1
    MOV t29, AX
end_cmp_48:
etiq_49:
    MOV AX, z
    CMP AX, 10
    JL  true_49
    MOV AX, 0
    MOV t30, AX
    JMP end_cmp_49
true_49:
    MOV AX, 1
    MOV t30, AX
end_cmp_49:
etiq_50:
    MOV AX, t29
    OR AX, t30
    MOV t31, AX
etiq_51:
    MOV AX, t28
    AND AX, t31
    MOV t32, AX
etiq_52:
    MOV AX, t32
    CMP AX, 0
    JNE skip_jmp_52
    JMP etiq_69
skip_jmp_52:
etiq_53:
    MOV AX, x
    ADD AX, 1
    MOV x, AX
etiq_55:
    MOV AX, x
    CMP AX, y
    JE  true_55
    MOV AX, 0
    MOV t34, AX
    JMP end_cmp_55
true_55:
    MOV AX, 1
    MOV t34, AX
end_cmp_55:
etiq_56:
    MOV AX, t34
    XOR AX, 1
    MOV t35, AX
etiq_57:
    MOV AX, t35
    CMP AX, 0
    JNE skip_jmp_57
    JMP etiq_68
skip_jmp_57:
etiq_58:
    MOV AX, y
    ADD AX, 1
    MOV t36, AX
etiq_59:
    MOV AX, t36
    MOV y, AX
etiq_60:
    MOV AX, x
    ADD AX, 1
    MOV t37, AX
etiq_61:
    MOV BX, 0
    SHL BX, 1
    MOV AX, Tabint[BX]
    MOV t38, AX
etiq_62:
    MOV BX, 1
    SHL BX, 1
    MOV AX, Tabint[BX]
    MOV t39, AX
etiq_63:
    MOV AX, t38
    ADD AX, t39
    MOV t40, AX
etiq_64:
    MOV AX, x
    SUB AX, t36
    MOV t41, AX
etiq_65:
    MOV AX, t40
    MOV BX, t41
    MUL BX
    PUSH AX
    MOV SI, t37
    SHL SI, 1
    POP AX
    MOV Tabint[SI], AX
etiq_67:
    JMP etiq_55
etiq_68:
    JMP etiq_47
etiq_69:
    MOV AX, 1
    MOV j, AX
etiq_70:
    MOV AX, j
    CMP AX, 20
    JLE true_70
    MOV AX, 0
    MOV t43, AX
    JMP end_cmp_70
true_70:
    MOV AX, 1
    MOV t43, AX
end_cmp_70:
etiq_71:
    MOV AX, t43
    CMP AX, 0
    JNE skip_jmp_71
    JMP etiq_84
skip_jmp_71:
etiq_72:
    MOV AX, j
    SUB AX, 1
    MOV t44, AX
etiq_73:
    MOV BX, t44
    SHL BX, 1
    MOV AX, Tabfloat[BX]
    MOV t45, AX
etiq_74:
    MOV BX, j
    SHL BX, 1
    MOV AX, Tabfloat[BX]
    MOV t46, AX
etiq_75:
    MOV AX, t45
    ADD AX, t46
    MOV t47, AX
etiq_76:
    MOV AX, t47
    XOR DX, DX
    MOV BX, 2
    DIV BX
    PUSH AX
    MOV SI, j
    SHL SI, 1
    POP AX
    MOV Tabfloat[SI], AX
etiq_78:
    MOV BX, j
    SHL BX, 1
    MOV AX, Tabfloat[BX]
    MOV t49, AX
etiq_79:
    MOV AX, moyenne
    ADD AX, t49
    MOV moyenne, AX
etiq_81:
    MOV AX, j
    ADD AX, 1
    MOV j, AX
etiq_83:
    JMP etiq_70
etiq_84:
    MOV AX, moyenne
    XOR DX, DX
    MOV BX, 20
    DIV BX
    MOV moyenne, AX
etiq_86:
    ; IN : lecture de x
etiq_87:
    ; OUT : ecriture de x
etiq_88:
    ; OUT : ecriture de somme
etiq_89:
    ; OUT : ecriture de moyenne
etiq_90:
    MOV AH, 4CH
    INT 21H
CODE ENDS
END MAIN
